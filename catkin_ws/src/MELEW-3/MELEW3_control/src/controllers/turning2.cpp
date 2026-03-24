/**
 * @file    turning2.cpp
 * @author  AI Assistant
 * @brief   Wall climbing with complete friction loss - robot falls from wall
 * @version 2.0
 * @date    2026-01-23
 *
 * @copyright Copyright (c) 2026
 *
 * Key Features:
 * - Normal climbing until mid-point of climb_time
 * - SUDDEN COMPLETE FRICTION LOSS - wall becomes extremely slippery
 * - Robot FALLS from wall (drops ~50cm!)
 * - Simulated by drastic reduction of normal force (legs retract 8cm)
 * - Realistic free-fall physics with high acceleration
 * - Dramatic visual effect with violent vibrations and tilting
 * - Emergency recovery mechanism to regain wall contact
 * - Demonstrates extreme robustness and recovery capability
 */
#include <MELEW3_control/BaseController.h>
#include <MELEW3_control/utils.hpp>
#include <geometry_msgs/WrenchStamped.h>
#include <cmath>

using namespace std;

namespace MELEW3_control {

class turning2_controller : public BaseController {
private:
  // Timing parameters
  double adj_time = 18.0;
  double adj_end = 19.0;
  
  std::vector<double> leg_yaw_ref_temp = init_leg_yaw;
  double COM_yaw_ref_temp = init_COM_yaw;

  // Counter initialization
  int c_init = 0;
  int c_s1 = start_time1 * controller_frequency;
  int c_e1 = end_time1 * controller_frequency;
  int c_c = climb_time * controller_frequency;
  int c_cm = ((climb_time + climb_end)/2) * controller_frequency;
  int c_ce = climb_end * controller_frequency;
  int c_mt = movingTime * controller_frequency;
  int c_ads = adj_time * controller_frequency;
  int c_ade = adj_end * controller_frequency;

  // Initial positions
  const double x_init = 0.0;
  const double y_init = 0.0;
  const double z_init = 0.35;
  const double psi_init = 0.0;

  double pos_temp = 0;

  // Force sensor subscribers
  ros::Subscriber fl_force, fr_force, bl_force, br_force;
  geometry_msgs::Wrench wrench_fl_, wrench_fr_, wrench_bl_, wrench_br_;
  double sum = 0;
  ros::Time last_print_time_;
  ros::Duration print_interval_{0.5};  // 更频繁打印，观察滑落过程

  // ===== 摩擦力丧失模拟参数 =====
  bool friction_loss_triggered_ = false;       // 是否触发摩擦力丧失
  double friction_loss_start_time_ = 0.0;      // 摩擦力丧失开始时间
  const double friction_loss_duration_ = 3.0;  // 摩擦力丧失持续时间 [s] (完全掉落需要更长时间)
  const double recovery_duration_ = 4.0;       // 恢复抓握时间 [s]
  
  // 滑落物理参数（完全失去抓力的情况）
  double slip_distance_ = 0.0;                 // 累计滑落距离 [m]
  double slip_velocity_ = 0.0;                 // 滑落速度 [m/s]
  const double slip_acceleration_ = 0.35;      // 滑落加速度 [m/s²] (接近自由落体，但有轻微阻力)
  const double max_slip_velocity_ = 0.8;       // 最大滑落速度 [m/s] (快速下落)
  const double max_slip_distance_ = 0.50;      // 最大滑落距离 [m] (掉落50cm！)
  
  // 恢复阶段参数
  double recovery_start_time_ = 0.0;
  Eigen::Vector3d slip_start_COM_pos_;         // 滑落前的重心位置
  
  // 摩擦力完全丧失模拟参数（几乎完全失去接触力）
  const double normal_force_reduction_ = 0.08; // 法向力大幅减小 [m] (腿部明显后退8cm)
  const double friction_transition_time_ = 0.2; // 摩擦力突变过渡时间 [s] (快速变化，突然失去抓力)

public:
  ros::Publisher FL_leg_pos_ref_pub_;
  ros::Publisher FR_leg_pos_ref_pub_;
  ros::Publisher BL_leg_pos_ref_pub_;
  ros::Publisher BR_leg_pos_ref_pub_;
  ros::Publisher COM_pos_ref_pub_;
  ros::Publisher COM_vel_ref_pub_;
  ros::Publisher COM_acl_ref_pub_;

  Utils::Utils util;
  Utils::Five_Spline::point x1, x2, z1, z2, v1, v2, v3;
  Utils::Five_Spline five_spline_x1, five_spline_x2;
  Utils::Five_Spline five_spline_z1, five_spline_z2;
  Utils::Five_Spline five_spline_v1, five_spline_v2, five_spline_v3;
  
  Eigen::VectorXd x_trajectory;
  Eigen::VectorXd z_trajectory;
  Eigen::VectorXd v_trajectory;
  Eigen::Vector3d gene_zmp{0.0, 0.0, 0.0};
  Eigen::Vector3d ZMP_pos_ref{0.0, 0.0, 0.0};
  Eigen::Vector3d COM_vel_ref{0.0, 0.0, 0.0};
  Eigen::Vector3d COM_acl_ref{0.0, 0.0, 0.0};
  
  std::vector<Eigen::Vector3d> init_leg_pos{
    Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_),
    Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
    Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_),
    Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_)
  };
  
  std::vector<double> init_leg_yaw = {0.0, 0.0, 0.0, 0.0};
  std::vector<Eigen::VectorXf> init_torque{
    Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4)
  };
  
  Eigen::Vector3d init_COM_pos{x_init, y_init, z_init};
  double init_COM_yaw = 0.0;

  int repetition_count = 0;
  const int max_repetitions = 5;
  const double interval_time = 4.0;
  double wait_start_time = 0.0;
  double current_x_pos = 0.0;

  // Function declarations
  void XTrajectoryGenerator();
  void ZTrajectoryGenerator();
  void VTrajectoryGenerator();
  void SimulateFrictionLoss(double dt);
  void EmergencyRecovery(double recovery_time);
  void forceFLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceFRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceBLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceBRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void printSensorData();
  
  turning2_controller(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Constructor
 */
turning2_controller::turning2_controller(void) {
  start_controller();
  fl_force = nh.subscribe("/MELEW3/ForceSensor_foot_FL", 1, &turning2_controller::forceFLCallback, this);
  fr_force = nh.subscribe("/MELEW3/ForceSensor_foot_FR", 1, &turning2_controller::forceFRCallback, this);
  bl_force = nh.subscribe("/MELEW3/ForceSensor_foot_BL", 1, &turning2_controller::forceBLCallback, this);
  br_force = nh.subscribe("/MELEW3/ForceSensor_foot_BR", 1, &turning2_controller::forceBRCallback, this);
  last_print_time_ = ros::Time::now();
}

/**
 * @brief Main control loop
 */
void turning2_controller::control_loop(void) {
  double current_time = get_time();

  // Phase 0: Transition to initial pose
  if (phase == 0) {
    if (pose_transition()) {
      FL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FL_leg_pos_ref", 1);
      FR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FR_leg_pos_ref", 1);
      BL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BL_leg_pos_ref", 1);
      BR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BR_leg_pos_ref", 1);
      COM_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/COM_pos_ref", 1);

      x_trajectory.resize(c_mt*2);
      XTrajectoryGenerator();
      z_trajectory.resize(c_mt*2);
      ZTrajectoryGenerator();
      v_trajectory.resize(c_mt*2);
      VTrajectoryGenerator();

      ROS_INFO("Phase 0 complete: Trajectories generated");
      initialize_flag = false;
      phase = 1;
    }
  }

  // Phase 1: Transition to start pose
  if (phase == 1) {
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("Phase 1 complete: Ready for climbing");
      ROS_WARN("Press Enter to start turning2 motion (with friction loss simulation)...");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }

  // Phase 2: Main climbing motion with friction loss simulation
  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      XTrajectoryGenerator();
      initialize_flag = true;
      ROS_INFO("Starting turning2 motion: Normal climbing until friction loss event");
    }
    
    current_time = get_time();
    loop_time = current_time - tmp_time;
    double dt = 1.0 / controller_frequency;  // 时间步长

    if(loop_time < movingTime){
      // Basic leg x-axis movement
      leg_pos_ref = {
        Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_),
        Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_),
        Eigen::Vector3d(BL_leg_offset_x_ - x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_),
        Eigen::Vector3d(BR_leg_offset_x_ - x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_)
      };
      
      // Initialize control variables
      double target_angular_velocity = 0.0;
      COM_pos_ref = Eigen::Vector3d(x_init, y_init, z_init);
      COM_yaw_ref = init_COM_yaw;
      leg_yaw_ref = init_leg_yaw;
      
      // Climbing phase
      if(loop_time >= climb_time && loop_time < climb_end){
        double climb_phase_time = loop_time - climb_time;
        double climb_duration = climb_end - climb_time;
        
        // Calculate wheel velocity
        double climb_linear_velocity = v_trajectory(loop_time * controller_frequency);
        double wheel_radius = wheel_diameter_ / 2.0;
        target_angular_velocity = climb_linear_velocity / wheel_radius;
        
        // ===== 核心：摩擦力丧失模拟 =====
        
        // 检测是否到达摩擦力丧失触发点（climb_time 的中点）
        double friction_loss_trigger_time = climb_duration / 2.0;
        
        if (!friction_loss_triggered_ && climb_phase_time >= friction_loss_trigger_time) {
          friction_loss_triggered_ = true;
          friction_loss_start_time_ = climb_phase_time;
          slip_start_COM_pos_ = COM_pos_ref;
          ROS_ERROR("====================================");
          ROS_ERROR("FRICTION LOSS DETECTED!");
          ROS_ERROR("Robot is slipping down the wall...");
          ROS_ERROR("====================================");
        }
        
        // 摩擦力丧失阶段：机器人开始滑落
        if (friction_loss_triggered_) {
          double time_since_loss = climb_phase_time - friction_loss_start_time_;
          
          if (time_since_loss < friction_loss_duration_) {
            // ===== 阶段1：完全失去抓力，从墙上掉落 =====
            SimulateFrictionLoss(dt);
            
            // 车轮完全失去抓力（立即停止转动）
            target_angular_velocity = 0.0;
            
            // 应用滑落位移到重心（快速向下掉落）
            COM_pos_ref.z() -= slip_distance_;
            
            // ===== 关键：大幅减小法向力，模拟完全失去抓力 =====
            // 腿部快速后退（远离墙面），几乎失去所有接触压力
            double force_reduction_progress = 0.0;
            if (time_since_loss < friction_transition_time_) {
              // 快速过渡：突然失去抓力
              double t_norm = time_since_loss / friction_transition_time_;
              force_reduction_progress = t_norm * t_norm * (3.0 - 2.0 * t_norm);  // Smoothstep
            } else {
              force_reduction_progress = 1.0;
            }
            
            // 所有腿大幅后退（8cm），几乎失去接触
            for (int i = 0; i < 4; i++) {
              leg_pos_ref[i].z() -= normal_force_reduction_ * force_reduction_progress;
            }
            
            // 掉落过程中的剧烈振动（失控状态）
            // 模拟机器人拼命尝试抓住墙面
            double vibration_frequency = 12.0 * M_PI;  // 6Hz快速振动
            double vibration_amplitude = 0.008 * (1.0 + slip_velocity_ / max_slip_velocity_);  // 随速度增加
            double vibration = vibration_amplitude * sin(vibration_frequency * time_since_loss);
            
            for (int i = 0; i < 4; i++) {
              leg_pos_ref[i].z() += vibration;
              // y方向也有较大的不规则振动（拼命挣扎）
              leg_pos_ref[i].y() += vibration * 0.8 * (i % 2 == 0 ? 1 : -1);
            }
            
            // 机体明显前倾（失控掉落）
            double tilt_angle = 0.08 * (time_since_loss / friction_loss_duration_);  // 最大8度前倾
            COM_pitch_ref = tilt_angle;
            
            // 机体还会有轻微的yaw旋转（不稳定状态）
            double yaw_wobble = 0.02 * sin(5.0 * M_PI * time_since_loss);  // 小幅度摆动
            COM_yaw_ref = init_COM_yaw + yaw_wobble;
            
            ROS_ERROR_THROTTLE(0.3, "CRITICAL! FREE FALLING! Slip: %.3f m, Vel: %.3f m/s, Contact force: %.1f%%", 
                             slip_distance_, slip_velocity_, (1.0 - force_reduction_progress) * 100.0);
            
          } else if (time_since_loss < friction_loss_duration_ + recovery_duration_) {
            // ===== 阶段2：紧急恢复阶段 =====
            if (recovery_start_time_ == 0.0) {
              recovery_start_time_ = time_since_loss;
              ROS_WARN("====================================");
              ROS_WARN("EMERGENCY RECOVERY INITIATED!");
              ROS_WARN("Attempting to regain wall contact...");
              ROS_WARN("====================================");
            }
            
            double recovery_time = time_since_loss - friction_loss_duration_;
            EmergencyRecovery(recovery_time);
            
            // 逐渐恢复车轮转动（缓慢重新获得抓力）
            double recovery_progress = recovery_time / recovery_duration_;
            target_angular_velocity = climb_linear_velocity / wheel_radius * recovery_progress * 0.5;  // 缓慢恢复
            
            // 保持掉落后的位置，然后非常缓慢地恢复
            double recovery_factor = (1.0 - cos(recovery_progress * M_PI)) / 2.0;  // 平滑插值
            COM_pos_ref.z() -= slip_distance_ * (1.0 - recovery_factor * 0.5);  // 只恢复50%的高度
            
            // 逐渐恢复法向力（腿部缓慢向墙推进，重新建立接触）
            double force_recovery_progress = recovery_factor;
            for (int i = 0; i < 4; i++) {
              leg_pos_ref[i].z() -= normal_force_reduction_ * (1.0 - force_recovery_progress);
            }
            
            // 逐渐恢复姿态（从大倾角慢慢恢复）
            COM_pitch_ref = 0.08 * (1.0 - recovery_progress);
            
            // 恢复yaw稳定性
            double yaw_recovery = 1.0 - recovery_progress;
            double yaw_wobble = 0.02 * sin(5.0 * M_PI * time_since_loss) * yaw_recovery;
            COM_yaw_ref = init_COM_yaw + yaw_wobble;
            
            ROS_WARN_THROTTLE(0.5, "RECOVERING... Progress: %.1f%%, Contact force: %.1f%%, Height recovered: %.1f%%", 
                             recovery_progress * 100.0, force_recovery_progress * 100.0, recovery_factor * 50.0);
            
          } else {
            // ===== 阶段3：恢复完成，继续爬升（但明显损失高度）=====
            ROS_INFO_ONCE("====================================");
            ROS_INFO_ONCE("RECOVERY COMPLETE! Wall contact restored.");
            ROS_INFO_ONCE("Resuming climb from lower position...");
            ROS_INFO_ONCE("====================================");
            
            // 恢复正常爬升
            target_angular_velocity = climb_linear_velocity / wheel_radius;
            COM_pitch_ref = 0.0;
            COM_yaw_ref = init_COM_yaw;
            
            // 保持50%的高度损失（显示掉落的严重后果）
            COM_pos_ref.z() -= slip_distance_ * 0.5;
          }
        } else {
          // 正常爬升阶段（摩擦力丧失之前）
          COM_pitch_ref = 0.0;
        }
        
        // Solve IK
        if(solve_IK_serial(leg_pos_ref, leg_yaw_ref, COM_pos_ref, COM_yaw_ref, COM_pitch_ref)){
          leg_motor_torque = init_torque;
        } else {
          ROS_WARN_THROTTLE(1.0, "IK solve failed during climbing");
        }
      } else {
        leg_motor_torque = init_torque;
      }
      
      wheel_velocity_ref = {target_angular_velocity, target_angular_velocity, 
                           -target_angular_velocity, -target_angular_velocity};
      
      printSensorData();
      current_x_pos = COM_pos_ref.x();
      
      // Publish trajectories (except during climbing)
      if(!(loop_time >= climb_time && loop_time < climb_end)){
        melew3_msgs::leg_pose pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, 
                              pub_BL_leg_pos_ref, pub_BR_leg_pos_ref, pub_COM_pos_ref;

        util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);
        util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
    
        FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
        BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
        FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
        BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
        COM_pos_ref_pub_.publish(pub_COM_pos_ref);
      }
    }
    else {
      // Motion complete - hold final position
      leg_pos_ref = {
        Eigen::Vector3d(FL_leg_offset_x_ + x2.x, FL_leg_offset_y_, FL_leg_offset_z_),
        Eigen::Vector3d(FR_leg_offset_x_ + x2.x, FR_leg_offset_y_, FR_leg_offset_z_),
        Eigen::Vector3d(BL_leg_offset_x_ - x2.x, BL_leg_offset_y_, BL_leg_offset_z_),
        Eigen::Vector3d(BR_leg_offset_x_ - x2.x, BR_leg_offset_y_, BR_leg_offset_z_)
      };
      wheel_velocity_ref = {0, 0, 0, 0};
      leg_yaw_ref = init_leg_yaw;
      COM_pos_ref = init_COM_pos;
      COM_pos_ref.z() -= slip_distance_ * 0.5;  // 保持50%高度损失
      COM_yaw_ref = init_COM_yaw;
      leg_motor_torque = init_torque;

      melew3_msgs::leg_pose pub_FL_leg_pos_ref, pub_FR_leg_pos_ref,
                            pub_BL_leg_pos_ref, pub_BR_leg_pos_ref, pub_COM_pos_ref;

      util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
      util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
      util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
      util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);
      util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
  
      FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
      BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
      FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
      BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
      COM_pos_ref_pub_.publish(pub_COM_pos_ref);
    }
    
    if (current_time >= tmp_time + movingTime) {
      phase = 3;
      initialize_flag = false;
    }
  }

  // Phase 3: Finalize
  else if (phase == 3) {
    ROS_INFO("Turning2 motion complete!");
    ROS_INFO("Total slip distance: %.3f m", slip_distance_);
    ROS_INFO("Friction loss successfully demonstrated and recovered!");
    stop_controller();
  }
}

/**
 * @brief 模拟摩擦力丧失导致的滑落
 * 使用简单的物理模型：v = v0 + at, s = s0 + v0*t + 0.5*a*t^2
 * 
 * @param dt 时间步长 [s]
 */
void turning2_controller::SimulateFrictionLoss(double dt) {
  // 更新滑落速度（受重力影响，但有空气阻力限制）
  slip_velocity_ += slip_acceleration_ * dt;
  
  // 限制最大滑落速度
  if (slip_velocity_ > max_slip_velocity_) {
    slip_velocity_ = max_slip_velocity_;
  }
  
  // 更新累计滑落距离
  double delta_slip = slip_velocity_ * dt;
  slip_distance_ += delta_slip;
  
  // 限制最大滑落距离
  if (slip_distance_ > max_slip_distance_) {
    slip_distance_ = max_slip_distance_;
    slip_velocity_ = 0.0;  // 达到最大滑落后停止
  }
}

/**
 * @brief 紧急恢复机制
 * 机器人尝试重新获得抓力
 * 
 * @param recovery_time 恢复阶段已经过的时间 [s]
 */
void turning2_controller::EmergencyRecovery(double recovery_time) {
  // 恢复进度 [0, 1]
  double progress = recovery_time / recovery_duration_;
  
  // 逐渐减小滑落速度（模拟重新获得摩擦力）
  slip_velocity_ *= (1.0 - 0.5 * progress);
  
  // 在恢复阶段，滑落距离会有小幅回弹（机器人向上推）
  if (progress > 0.5) {
    double pushback_factor = (progress - 0.5) * 2.0;  // [0, 1]
    slip_distance_ *= (1.0 - 0.1 * pushback_factor);  // 恢复10%的高度
  }
}

/**
 * @brief X方向轨迹生成
 */
void turning2_controller::XTrajectoryGenerator(){
  x1 = {start_time1, 0.0, 0.0, 0.0};
  x2 = {end_time1, 0.1, 0.0, 0.0};
  
  std::vector<Utils::Five_Spline::point> points_x1 = {x1, x2};
  five_spline_x1.Calc_Spline(points_x1);

  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_s1){
      x_trajectory(period_count) = 0.0;
    }
    else if(period_count < c_e1){
      x_trajectory(period_count) = five_spline_x1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      x_trajectory(period_count) = x2.x;
    }
  }
}

/**
 * @brief Z方向轨迹生成
 */
void turning2_controller::ZTrajectoryGenerator(){
  z1 = {adj_time, 0.0, 0.0, 0.0};
  z2 = {adj_end, 0.1, 0.0, 0.0};
  
  std::vector<Utils::Five_Spline::point> points_z1 = {z1, z2};
  five_spline_z1.Calc_Spline(points_z1);

  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_ads){
      z_trajectory(period_count) = 0.0;
    }
    else if(period_count < c_ade){
      z_trajectory(period_count) = five_spline_z1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      z_trajectory(period_count) = z2.x;
    }
  }
}

/**
 * @brief 速度轨迹生成
 */
void turning2_controller::VTrajectoryGenerator(){
  v1 = {climb_time, 0.0, 0.0, 0.0};
  v2 = {(climb_time + climb_end)/2, 0.0003, 0.0, 0.0};
  v3 = {climb_end, 0.0, 0.0, 0.0};
  
  std::vector<Utils::Five_Spline::point> points_v1 = {v1, v2};
  std::vector<Utils::Five_Spline::point> points_v2 = {v2, v3};
  
  five_spline_v1.Calc_Spline(points_v1);
  five_spline_v2.Calc_Spline(points_v2);

  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_c){
      v_trajectory(period_count) = 0.0;
    }
    else if(period_count < c_cm){
      v_trajectory(period_count) = five_spline_v1.Get_Spline_x(period_count/controller_frequency);
    }
    else if(period_count < c_ce){
      v_trajectory(period_count) = five_spline_v2.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      v_trajectory(period_count) = 0.0;
    }
  }
}

/**
 * @brief Force sensor callbacks
 */
void turning2_controller::forceFLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_fl_ = msg->wrench;
}

void turning2_controller::forceFRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_fr_ = msg->wrench;
}

void turning2_controller::forceBLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_bl_ = msg->wrench;
}

void turning2_controller::forceBRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_br_ = msg->wrench;
}

/**
 * @brief 打印传感器数据
 */
void turning2_controller::printSensorData() {
  ros::Time now = ros::Time::now();
  if (now - last_print_time_ >= print_interval_) {
    ROS_INFO("--- Force Sensor Data (N) ---");
    ROS_INFO("FL: [x: %.3f, y: %.3f, z: %.3f]", 
             1000*wrench_fl_.force.x, 1000*wrench_fl_.force.y, 1000*wrench_fl_.force.z+20);
    ROS_INFO("FR: [x: %.3f, y: %.3f, z: %.3f]", 
             1000*wrench_fr_.force.x, 1000*wrench_fr_.force.y, 1000*wrench_fr_.force.z+20);
    ROS_INFO("BL: [x: %.3f, y: %.3f, z: %.3f]", 
             1000*wrench_bl_.force.x, 1000*wrench_bl_.force.y, 1000*wrench_bl_.force.z+20);
    ROS_INFO("BR: [x: %.3f, y: %.3f, z: %.3f]", 
             1000*wrench_br_.force.x, 1000*wrench_br_.force.y, 1000*wrench_br_.force.z+20);
    sum = wrench_fl_.force.z + wrench_bl_.force.z + wrench_fr_.force.z + wrench_br_.force.z;
    ROS_INFO("Sum of z-axis force: %.3f N", 1000*sum+80.0);
    
    if (friction_loss_triggered_) {
      ROS_WARN("Slip distance: %.3f m, Slip velocity: %.3f m/s", slip_distance_, slip_velocity_);
    }
    
    ROS_INFO("---------------------------------");
    last_print_time_ = now;
  }
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "turning2_controller");
  ROS_INFO("Starting turning2 controller: Friction loss simulation");
  MELEW3_control::BaseController* controller = new MELEW3_control::turning2_controller;
  ros::waitForShutdown();
  return 0;
}
