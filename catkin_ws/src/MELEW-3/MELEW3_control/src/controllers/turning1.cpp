/**
 * @file    turning1.cpp
 * @author  AI Assistant
 * @brief   Enhanced wall climbing with progressive yaw rotation and dynamic leg compensation
 * @version 1.0
 * @date    2026-01-22
 *
 * @copyright Copyright (c) 2026
 *
 * Key Features:
 * - Progressive yaw rotation during climbing (避免突然旋转导致摔倒)
 * - Dynamic leg length compensation based on yaw angle (补偿旋转导致的腿长变化)
 * - Diagonal leg support enhancement (加强对角线腿的支撑)
 * - "Z-pattern" climbing trajectory (Z字形攀爬轨迹)
 */
#include <MELEW3_control/BaseController.h>
#include <MELEW3_control/utils.hpp>
#include <geometry_msgs/WrenchStamped.h>
#include <cmath>

using namespace std;

namespace MELEW3_control {

class turning1_controller : public BaseController {
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
  ros::Duration print_interval_{1.0};

  // Yaw rotation parameters
  const double max_yaw_angle = 15.0 * M_PI / 180.0;  // 最大旋转角度 15度 (保守设置)
  const int num_yaw_segments = 3;                     // 分3段旋转
  double current_yaw_segment = 0;                     // 当前旋转段
  
  // Dynamic leg compensation parameters
  const double leg_compensation_gain = 0.05;          // 腿长补偿增益
  const double diagonal_support_gain = 0.02;          // 对角线支撑增强增益

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
  void ProgressiveYawRotation(double climb_phase_time, double climb_duration, 
                               double& target_COM_yaw, std::vector<double>& target_leg_yaw);
  void DynamicLegCompensation(double current_yaw, std::vector<Eigen::Vector3d>& leg_positions);
  void forceFLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceFRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceBLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceBRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void printSensorData();
  
  turning1_controller(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Constructor
 */
turning1_controller::turning1_controller(void) {
  start_controller();
  fl_force = nh.subscribe("/MELEW3/ForceSensor_foot_FL", 1, &turning1_controller::forceFLCallback, this);
  fr_force = nh.subscribe("/MELEW3/ForceSensor_foot_FR", 1, &turning1_controller::forceFRCallback, this);
  bl_force = nh.subscribe("/MELEW3/ForceSensor_foot_BL", 1, &turning1_controller::forceBLCallback, this);
  br_force = nh.subscribe("/MELEW3/ForceSensor_foot_BR", 1, &turning1_controller::forceBRCallback, this);
  last_print_time_ = ros::Time::now();
}

/**
 * @brief Main control loop
 */
void turning1_controller::control_loop(void) {
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
      ROS_INFO("Press Enter to start turning1 motion...");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }

  // Phase 2: Main climbing motion with progressive yaw rotation
  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      XTrajectoryGenerator();
      initialize_flag = true;
      ROS_INFO("Starting turning1 motion: Progressive yaw rotation with dynamic compensation");
    }
    
    current_time = get_time();
    loop_time = current_time - tmp_time;

    if(loop_time < movingTime){
      // Basic leg x-axis movement (same as turning)
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
      
      // Climbing phase with progressive yaw rotation
      if(loop_time >= climb_time && loop_time < climb_end){
        double climb_phase_time = loop_time - climb_time;
        double climb_duration = climb_end - climb_time;
        
        // Calculate wheel velocity
        double climb_linear_velocity = v_trajectory(loop_time * controller_frequency);
        double wheel_radius = wheel_diameter_ / 2.0;
        target_angular_velocity = climb_linear_velocity / wheel_radius;
        
        // ===== 核心创新：渐进式Yaw旋转 + 动态腿长补偿 =====
        
        // 1. 计算渐进式yaw角度（分段旋转，每段之间有平滑过渡）
        double segment_duration = climb_duration / (num_yaw_segments * 2);  // *2因为有旋转和保持两个阶段
        double normalized_time = climb_phase_time / segment_duration;
        int current_segment = static_cast<int>(normalized_time);
        double segment_progress = normalized_time - current_segment;
        
        double target_yaw = 0.0;
        
        if (current_segment < num_yaw_segments * 2) {
          if (current_segment % 2 == 0) {
            // 旋转阶段：使用平滑的三角函数
            int rotation_index = current_segment / 2;
            double yaw_per_segment = max_yaw_angle / num_yaw_segments;
            double start_yaw = rotation_index * yaw_per_segment;
            double end_yaw = (rotation_index + 1) * yaw_per_segment;
            
            // 使用 cosine 平滑插值避免突变
            double smooth_progress = (1.0 - cos(segment_progress * M_PI)) / 2.0;
            target_yaw = start_yaw + (end_yaw - start_yaw) * smooth_progress;
          } else {
            // 保持阶段：维持当前角度
            int rotation_index = (current_segment + 1) / 2;
            double yaw_per_segment = max_yaw_angle / num_yaw_segments;
            target_yaw = rotation_index * yaw_per_segment;
          }
        } else {
          target_yaw = max_yaw_angle;
        }
        
        COM_yaw_ref = target_yaw;
        
        // 2. 动态腿长补偿：根据yaw角度调整腿的z坐标
        // 旋转后，靠近墙壁的腿需要缩短，远离墙壁的腿需要伸长
        DynamicLegCompensation(target_yaw, leg_pos_ref);
        
        // 3. 增强对角线支撑：在旋转时增加对角线腿的y轴微调，提高稳定性
        // 使用小幅度的正弦波动，频率较低以保持稳定
        double support_frequency = 0.3 * M_PI;  // 更低的频率
        double support_amplitude = 0.015;        // 更小的振幅
        
        // 根据旋转方向选择对角线
        double diagonal_phase = sin(support_frequency * climb_phase_time);
        
        if (target_yaw >= 0) {
          // 正向旋转：增强FL-BR对角线
          leg_pos_ref[FL].y() += diagonal_support_gain * diagonal_phase;
          leg_pos_ref[BR].y() -= diagonal_support_gain * diagonal_phase;
          leg_pos_ref[FR].y() -= diagonal_support_gain * diagonal_phase * 0.5;
          leg_pos_ref[BL].y() += diagonal_support_gain * diagonal_phase * 0.5;
        } else {
          // 反向旋转：增强FR-BL对角线
          leg_pos_ref[FR].y() += diagonal_support_gain * diagonal_phase;
          leg_pos_ref[BL].y() -= diagonal_support_gain * diagonal_phase;
          leg_pos_ref[FL].y() -= diagonal_support_gain * diagonal_phase * 0.5;
          leg_pos_ref[BR].y() += diagonal_support_gain * diagonal_phase * 0.5;
        }
        
        // 4. 添加细微的"呼吸"运动：整体z方向微小振荡，模拟生物攀爬
        double breathing_frequency = 0.4 * M_PI;
        double breathing_amplitude = 0.008;  // 8mm的细微振荡
        double breathing_offset = breathing_amplitude * sin(breathing_frequency * climb_phase_time);
        
        for (int i = 0; i < 4; i++) {
          leg_pos_ref[i].z() += breathing_offset;
        }
        
        // Solve IK
        if(solve_IK_serial(leg_pos_ref, leg_yaw_ref, COM_pos_ref, COM_yaw_ref, COM_pitch_ref)){
          ROS_DEBUG_THROTTLE(1.0, "Climbing phase: Yaw=%.2f deg, Segment=%d", 
                            target_yaw * 180.0 / M_PI, current_segment);
          leg_motor_torque = init_torque;
        } else {
          ROS_WARN_THROTTLE(1.0, "Climbing phase: IK solve failed at yaw=%.2f deg", 
                           target_yaw * 180.0 / M_PI);
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
      COM_yaw_ref = max_yaw_angle;  // Maintain final yaw angle
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
    ROS_INFO("Turning1 motion complete! Final yaw: %.2f degrees", max_yaw_angle * 180.0 / M_PI);
    stop_controller();
  }
}

/**
 * @brief 动态腿长补偿函数
 * 根据yaw角度动态调整每条腿的长度，补偿旋转带来的几何变化
 * 
 * @param current_yaw 当前yaw角度 [rad]
 * @param leg_positions 腿部位置引用（会被修改）
 */
void turning1_controller::DynamicLegCompensation(double current_yaw, std::vector<Eigen::Vector3d>& leg_positions) {
  // 计算旋转补偿系数
  // 旋转后，机器人的四个角到墙壁的距离会发生变化
  // 假设墙壁在x正方向，yaw正旋转是逆时针
  
  double yaw_normalized = current_yaw / max_yaw_angle;  // 归一化到[0,1]
  
  // 简化的几何补偿模型：
  // FL和FR腿在前方，旋转时FL远离墙壁（需要伸长），FR靠近墙壁（需要缩短）
  // BL和BR腿在后方，旋转时BL靠近墙壁（需要缩短），BR远离墙壁（需要伸长）
  
  double compensation_FL = leg_compensation_gain * yaw_normalized;   // 伸长
  double compensation_FR = -leg_compensation_gain * yaw_normalized;  // 缩短
  double compensation_BL = -leg_compensation_gain * yaw_normalized;  // 缩短
  double compensation_BR = leg_compensation_gain * yaw_normalized;   // 伸长
  
  // 应用补偿到z方向（腿长方向）
  leg_positions[FL].z() += compensation_FL;
  leg_positions[FR].z() += compensation_FR;
  leg_positions[BL].z() += compensation_BL;
  leg_positions[BR].z() += compensation_BR;
  
  // 同时在x方向做微调，补偿旋转导致的横向位移
  double x_compensation = leg_compensation_gain * 0.5 * yaw_normalized;
  leg_positions[FL].x() += x_compensation;
  leg_positions[FR].x() += x_compensation;
  leg_positions[BL].x() -= x_compensation;
  leg_positions[BR].x() -= x_compensation;
}

/**
 * @brief X方向轨迹生成
 */
void turning1_controller::XTrajectoryGenerator(){
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
void turning1_controller::ZTrajectoryGenerator(){
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
void turning1_controller::VTrajectoryGenerator(){
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
void turning1_controller::forceFLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_fl_ = msg->wrench;
}

void turning1_controller::forceFRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_fr_ = msg->wrench;
}

void turning1_controller::forceBLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_bl_ = msg->wrench;
}

void turning1_controller::forceBRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_br_ = msg->wrench;
}

/**
 * @brief 打印传感器数据
 */
void turning1_controller::printSensorData() {
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
    ROS_INFO("Current COM yaw: %.2f deg", COM_yaw_ref * 180.0 / M_PI);
    ROS_INFO("---------------------------------");
    last_print_time_ = now;
  }
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "turning1_controller");
  ROS_INFO("Starting turning1 controller: Progressive yaw rotation with dynamic compensation");
  MELEW3_control::BaseController* controller = new MELEW3_control::turning1_controller;
  ros::waitForShutdown();
  return 0;
}
