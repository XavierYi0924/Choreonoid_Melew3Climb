/**
 * @file    wheel_running_several.cpp
 * @author  Taisei Suzuki
 * @brief   Move x sine wave
 * @version 1.0
 * @date    2024-01-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <MELEW3_control/BaseController.h>

#include <MELEW3_control/utils.hpp>

#include <geometry_msgs/WrenchStamped.h>

using namespace std;

namespace MELEW3_control {

class wheel_running_several : public BaseController {
private:
  // double start_time1 = 2.0;
  // double end_time1 = 4.0;
  // double climb_time = 4.2;
  // double climb_end = 13.0;
  double adj_time = 18.0;
  double adj_end = 19.0;
  // const double settingTime = 2.0;     // 動作開始姿勢への遷移時間[s]
  // const double movingTime = 15.0;     // 動作時間[s]
  
  std::vector<double>  leg_yaw_ref_temp = init_leg_yaw;
  double COM_yaw_ref_temp = init_COM_yaw;

  int c_init = 0;
  int c_s1 = start_time1 * controller_frequency;
  int c_e1 = end_time1 * controller_frequency;
  int c_c = climb_time * controller_frequency;
  int c_cm = ((climb_time + climb_end)/2) * controller_frequency;
  int c_ce = climb_end * controller_frequency;
  int c_mt = movingTime * controller_frequency;
  int c_ads = adj_time * controller_frequency;
  int c_ade = adj_end * controller_frequency;

  const double x_init = 0.0;          // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;          // y軸ベースリンク初期位置[m]
  const double z_init = 0.35;         // z軸ベースリンク初期位置[m]
  const double psi_init = 0.0;        // psi初期位置[rad]

  // double loop_time;  // phase内の時間[s]
  // double tmp_time;   // 時間のオフセット記録[s]
  double pos_temp = 0;

  //----------------Topic reading--------------//
  ros::Subscriber fl_force, fr_force, bl_force, br_force;
  geometry_msgs::Wrench wrench_fl_, wrench_fr_, wrench_bl_, wrench_br_;
  double sum = 0;
  ros::Time last_print_time_;
  ros::Duration print_interval_{1.0}; 
  //-------------------end--------------------//


public:
  ros::Publisher FL_leg_pos_ref_pub_;  //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;  //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;  //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;  //!< 右後脚の目標(loop_time*controller_frequency)用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;     //!< 目標重心位置用パブリッシャー
  ros::Publisher COM_vel_ref_pub_;     //!< 目標重心速度用パブリッシャー
  ros::Publisher COM_acl_ref_pub_;     //!< 目標重心加速度用パブリッシャー

  Utils::Utils util;
  Utils::Five_Spline::point x1;
  Utils::Five_Spline::point x2;
  Utils::Five_Spline::point z1;
  Utils::Five_Spline::point z2;
  Utils::Five_Spline::point v1;
  Utils::Five_Spline::point v2;
  Utils::Five_Spline::point v3;
  Utils::Five_Spline five_spline_x1;
  Utils::Five_Spline five_spline_x2;
  Utils::Five_Spline five_spline_z1;
  Utils::Five_Spline five_spline_z2;
  Utils::Five_Spline five_spline_v1;
  Utils::Five_Spline five_spline_v2;
  Utils::Five_Spline five_spline_v3;
  Eigen::VectorXd x_trajectory;
  Eigen::VectorXd z_trajectory;
  Eigen::VectorXd v_trajectory;
  Eigen::Vector3d gene_zmp{0.0, 0.0, 0.0};     //!< ５次補完ZMP位置を一時保存する変数
  Eigen::Vector3d ZMP_pos_ref{0.0, 0.0, 0.0};  //!< 目標ZMP位置を一時保存する変数
  Eigen::Vector3d COM_vel_ref{0.0, 0.0, 0.0};  //!< 目標重心速度を一時保存する変数
  Eigen::Vector3d COM_acl_ref{0.0, 0.0, 0.0};  //!< 目標重心加速度を一時保存する変数
  std::vector<Eigen::Vector3d> init_leg_pos{            // 初期足部位置
                                            Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_),
                                            Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
                                            Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_),
                                            Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_)};
  std::vector<double>          init_leg_yaw = {0.0, 0.0, 0.0, 0.0};  // 初期足部YAW角度
  std::vector<Eigen::VectorXf> init_torque{Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4),
                                           Eigen::VectorXf::Zero(4)};
  Eigen::Vector3d              init_COM_pos{x_init, y_init, z_init};  // 初期ベースリンク位置
  double                       init_COM_yaw = 0.0;                    // 初期ベースリンクYAW角度


  int repetition_count = 0;            // 当前已完成的重复次数
  const int max_repetitions = 5;       // 最大重复次数
  const double interval_time = 4.0;    // 每次重复之间的间隔时间（秒）
  double wait_start_time = 0.0;        // 等待间隔的开始时间
  double current_x_pos = 0.0;

  void XTrajectoryGenerator();   // X direction Trajectory Generayor  
  void ZTrajectoryGenerator();
  void VTrajectoryGenerator();
  void ClimbingSinWaveGenerator();  // 添加：在climbing阶段生成sin wave轨迹
  double ClimbingSinWaveGenerator_helper(double climb_phase_time, double climb_duration, double sin_amplitude);  // 辅助函数

  void forceFLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceFRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceBLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void forceBRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg);
  void printSensorData();
  wheel_running_several(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
wheel_running_several::wheel_running_several(void) {
  // ROS_WARN("start ready");
  start_controller();
  // ROS_WARN("start");
  fl_force = nh.subscribe("/MELEW3/ForceSensor_foot_FL", 1, &wheel_running_several::forceFLCallback, this);
  fr_force = nh.subscribe("/MELEW3/ForceSensor_foot_FR", 1, &wheel_running_several::forceFRCallback, this);
  bl_force = nh.subscribe("/MELEW3/ForceSensor_foot_BL", 1, &wheel_running_several::forceBLCallback, this);
  br_force = nh.subscribe("/MELEW3/ForceSensor_foot_BR", 1, &wheel_running_several::forceBRCallback, this);
  last_print_time_ = ros::Time::now();
}

/**
 * @brief
 *
 */
void wheel_running_several::control_loop(void) {
  double current_time = get_time();
  // Transition to initial pose
  // ROS_WARN("xsin loop in");
  if (phase == 0) {
    if (pose_transition()) {
      // ROS_WARN("potra haitta");
      /*** パブリッシャ，サブスクライバの初期化 ***/
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

      ROS_INFO("phase0 end");
      initialize_flag = false;
      phase = 1;
    }
    // ROS_WARN("Through");
  }

  // Transition to start pose
  if (phase == 1) {
    // ROS_WARN("phase1 in");
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase1 end");
      ROS_INFO("Enter key to start moving wheel running");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }

  // Move x sine wave
  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      XTrajectoryGenerator();
      initialize_flag = true;
    }
    current_time = get_time();
    loop_time = current_time - tmp_time;

    if(loop_time < movingTime){
      leg_pos_ref = {
        Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency) , FL_leg_offset_y_, FL_leg_offset_z_ ),
        Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency) , FR_leg_offset_y_, FR_leg_offset_z_ ),
        Eigen::Vector3d(BL_leg_offset_x_ - x_trajectory(loop_time*controller_frequency) , BL_leg_offset_y_, BL_leg_offset_z_ ),
        Eigen::Vector3d(BR_leg_offset_x_ - x_trajectory(loop_time*controller_frequency) , BR_leg_offset_y_, BR_leg_offset_z_ )
        };
      
      //----------------wheel control & leg control in climbing phase--------------------//
      double target_angular_velocity = 0.0;
      COM_pos_ref = Eigen::Vector3d(x_init, y_init, z_init);
      COM_yaw_ref = init_COM_yaw;
      leg_yaw_ref = init_leg_yaw;
      
      if(loop_time >= climb_time && loop_time < climb_end){
        // 计算车轮速度
        double climb_linear_velocity = v_trajectory(loop_time * controller_frequency);
        double wheel_radius = wheel_diameter_ / 2.0;
        target_angular_velocity = climb_linear_velocity / wheel_radius;
        
        // 对角线对称的sin wave腿部轨迹（保持重心不动，提高稳定性）
        double climb_phase_time = loop_time - climb_time; 
        double climb_duration = climb_end - climb_time;     
        double sin_frequency = 0.2 * M_PI;  // 固定频率（rad/s），与上升时长无关
        double sin_amplitude = 0.03;  // 转向幅度[m]
        
        // 计算两条对角线的sin wave（相位相反）
        double sin_wave_diagonal1 = sin_amplitude * sin(sin_frequency * climb_phase_time);      // 对角线1：0→π
        double sin_wave_diagonal2 = -sin_wave_diagonal1;                                         // 对角线2：π→0（相反）
        
        // 对角线对称运动：FL和BR同向，FR和BL反向
        // 这样可以保证重心保持在中心，四腿平衡
        leg_pos_ref[FL].y() = FL_leg_offset_y_ + sin_wave_diagonal1;  // 左前：+Y方向
        leg_pos_ref[BR].y() = BR_leg_offset_y_ + sin_wave_diagonal2;  // 右后：+Y方向（对角线1）
        leg_pos_ref[FR].y() = FR_leg_offset_y_ + sin_wave_diagonal1;  // 右前：-Y方向
        leg_pos_ref[BL].y() = BL_leg_offset_y_ + sin_wave_diagonal2;  // 左后：-Y方向（对角线2）
        
        if(solve_IK_serial(leg_pos_ref, leg_yaw_ref, COM_pos_ref, COM_yaw_ref, COM_pitch_ref)){
          ROS_DEBUG("Climbing phase: Diagonal symmetric leg motion applied, IK solved successfully");
          leg_motor_torque = init_torque;
        } else {
          ROS_WARN("Climbing phase: IK solve failed");
        }
      } else {
        leg_motor_torque = init_torque;
      }
      
      wheel_velocity_ref = {target_angular_velocity, target_angular_velocity, -target_angular_velocity, -target_angular_velocity};
      //---------------------end-------------------------//
      printSensorData();
      current_x_pos = COM_pos_ref.x();
      
      if(!(loop_time >= climb_time && loop_time < climb_end)){
        /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
        melew3_msgs::leg_pose pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
            pub_COM_pos_ref;

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
      leg_pos_ref = {
        Eigen::Vector3d(FL_leg_offset_x_ + x2.x , FL_leg_offset_y_, FL_leg_offset_z_),
        Eigen::Vector3d(FR_leg_offset_x_ + x2.x , FR_leg_offset_y_, FR_leg_offset_z_),
        Eigen::Vector3d(BL_leg_offset_x_ - x2.x , BL_leg_offset_y_, BL_leg_offset_z_),
        Eigen::Vector3d(BR_leg_offset_x_ - x2.x , BR_leg_offset_y_, BR_leg_offset_z_)
        };
      wheel_velocity_ref = {0,0,0,0};
      leg_yaw_ref = init_leg_yaw;
      COM_pos_ref = init_COM_pos;
      COM_yaw_ref = init_COM_yaw;
      leg_motor_torque = init_torque;

      /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
      melew3_msgs::leg_pose pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
          pub_COM_pos_ref;

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
      phase = 3; // Go to loop phase
      initialize_flag = false;  // 2点目の時刻，位置，速度，加速度を指定
    }
  }

  // Finalize
  else if (phase == 3) {
    ROS_INFO("Climbing complete!");
    stop_controller();
  }
}

void wheel_running_several::XTrajectoryGenerator(){
  //** ZMPTG Start **//////////////////////////////////////////////////////////////////////////////

  // 1点目の時刻，位置，速度，加速度を指定
  x1 = {  start_time1, 
          0.0, 
          0.0, 
          0.0 };

  x2 = {  end_time1,   
          0.1, 
          0.0, 
          0.0 };
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_x1 = {x1, x2};

  // 5次多項式補間の係数を計算
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
    // printf("%lf ", x_trajectory(period_count));
  }
}

void wheel_running_several::ZTrajectoryGenerator(){
  //** ZMPTG Start **//////////////////////////////////////////////////////////////////////////////

  // 1点目の時刻，位置，速度，加速度を指定
  z1 = {  adj_time, 
          0.0, 
          0.0, 
          0.0 };

  z2 = {  adj_end,   
          0.1, 
          0.0, 
          0.0 };
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_z1 = {z1, z2};

  // 5次多項式補間の係数を計算
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
    // printf("%lf ", x_trajectory(period_count));
  }
}

void wheel_running_several::VTrajectoryGenerator(){
  //** ZMPTG Start **//////////////////////////////////////////////////////////////////////////////

  // 1点目の時刻，位置，速度，加速度を指定
  v1 = {  climb_time, 
          0.0, 
          0.0, 
          0.0 };

  v2 = {  (climb_time + climb_end)/2,   
          0.0003, 
          0.0, 
          0.0 };

  v3 = {  climb_end,   
        0.0, 
        0.0, 
        0.0 };
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_v1 = {v1, v2};
  std::vector<Utils::Five_Spline::point> points_v2 = {v2, v3};
  // 5次多項式補間の係数を計算
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
    // printf("%lf ", x_trajectory(period_count));
  }
}

void wheel_running_several::forceFLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_fl_ = msg->wrench;
}

void wheel_running_several::forceFRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_fr_ = msg->wrench;
}

void wheel_running_several::forceBLCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_bl_ = msg->wrench;
}

void wheel_running_several::forceBRCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
  wrench_br_ = msg->wrench;
}

void wheel_running_several::printSensorData() {
  ros::Time now = ros::Time::now();
  if (now - last_print_time_ >= print_interval_) {

    ROS_INFO("--- Force Sensor Data (N) ---");
    ROS_INFO("FL: [x: %.3f, y: %.3f, z: %.3f]", 1000*wrench_fl_.force.x, 1000*wrench_fl_.force.y, 1000*wrench_fl_.force.z+20);
    ROS_INFO("FR: [x: %.3f, y: %.3f, z: %.3f]", 1000*wrench_fr_.force.x, 1000*wrench_fr_.force.y, 1000*wrench_fr_.force.z+20);
    ROS_INFO("BL: [x: %.3f, y: %.3f, z: %.3f]", 1000*wrench_bl_.force.x, 1000*wrench_bl_.force.y, 1000*wrench_bl_.force.z+20);
    ROS_INFO("BR: [x: %.3f, y: %.3f, z: %.3f]", 1000*wrench_br_.force.x, 1000*wrench_br_.force.y, 1000*wrench_br_.force.z+20);
    sum = wrench_fl_.force.z+wrench_bl_.force.z+wrench_fr_.force.z+wrench_br_.force.z;
    ROS_INFO("Sum of the z-axis force: %.3f]", 1000*sum+80.0);
    ROS_INFO("---------------------------------");

    last_print_time_ = now; // 更新上次打印的时间
  }
}

/**
 * @brief 在climbing阶段生成sin wave腿部轨迹的辅助函数
 * 
 * @param climb_phase_time 当前在climbing阶段内的时间[s]
 * @param climb_duration climbing阶段总时长[s]
 * @param sin_amplitude sin wave振幅[m]
 * @return double sin wave位移值[m]
 */
double wheel_running_several::ClimbingSinWaveGenerator_helper(double climb_phase_time, double climb_duration, double sin_amplitude) {
  double sin_frequency = 2.0 * M_PI / climb_duration;  // 频率：在climbing时间内完成一个周期
  return sin_amplitude * sin(sin_frequency * climb_phase_time);
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "wheel_running_several");
  // ROS_WARN("wheel running");
  MELEW3_control::BaseController* controller = new MELEW3_control::wheel_running_several;
  ros::waitForShutdown();
  return 0;
}