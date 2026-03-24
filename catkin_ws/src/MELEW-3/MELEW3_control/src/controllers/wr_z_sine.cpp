/**
 * @file    wheel_running.cpp
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

using namespace std;

namespace MELEW3_control {

class wheel_running : public BaseController {
private:
  double start_time = 3.0;
  double end_time = 8.0;
  const double settingTime = 3.0;     // 動作開始姿勢への遷移時間[s]
  const double movingTime = 10.0;     // 動作時間[s]

  int c_init = 0;
  int c_s = start_time * controller_frequency;
  int c_e = end_time * controller_frequency;
  int c_mt = movingTime * controller_frequency;

  const double z_frequency = 0.25;  // 周波数[Hz]
  const double z_amplitude = 0.05;  // 振幅[m]
  const double x_init = 0.0;          // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;          // y軸ベースリンク初期位置[m]
  const double z_init = 0.3;         // z軸ベースリンク初期位置[m]
  const double psi_init = 0.0;        // psi初期位置[rad]

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

public:
  ros::Publisher FL_leg_pos_ref_pub_;  //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;  //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;  //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;  //!< 右後脚の目標脚先位置用パブリッシャー
  ros::Publisher gene_zmp_pub_;        //!< Generated ZMP 位置用パブリッシャー
  ros::Publisher ZMP_pos_ref_pub_;     //!< 目標ZMP位置用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;     //!< 目標重心位置用パブリッシャー
  ros::Publisher COM_vel_ref_pub_;     //!< 目標重心速度用パブリッシャー
  ros::Publisher COM_acl_ref_pub_;     //!< 目標重心加速度用パブリッシャー

  Utils::Utils util;
  Utils::Five_Spline::point x1;
  Utils::Five_Spline::point x2;
  Utils::Five_Spline five_spline_x;
  Eigen::VectorXd x_trajectory;
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

  void XTrajectoryGenerator();   // X direction Trajectory Generayor  

  wheel_running(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
wheel_running::wheel_running(void) {
  // ROS_WARN("start ready");
  start_controller();
  // ROS_WARN("start");
}

/**
 * @brief
 *
 */
void wheel_running::control_loop(void) {
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
      initialize_flag = true;
    }
    loop_time = current_time - tmp_time;
    /*
        ここで以下を決定する
        ・足先位置            ：leg_pos_ref
        ・足先YAW角度         ：leg_yaw_ref
        ・ベースリンク位置    ：COM_pos_ref
        ・ベースリンクYAW角度 ：COM_yaw_ref
        （World座標系）
    */

    if(loop_time < movingTime){

      leg_pos_ref = {
        Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_),
        Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_),
        Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_),
        Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_)
        };
      leg_yaw_ref = init_leg_yaw;
      COM_pos_ref = Eigen::Vector3d(x_trajectory(loop_time*controller_frequency), y_init, z_init + z_amplitude * (1 - cos(2 * M_PI * z_frequency * loop_time)));
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
    else {
      leg_pos_ref = {
        Eigen::Vector3d(FL_leg_offset_x_ + x2.x, FL_leg_offset_y_, FL_leg_offset_z_),
        Eigen::Vector3d(FR_leg_offset_x_ + x2.x, FR_leg_offset_y_, FR_leg_offset_z_),
        Eigen::Vector3d(BL_leg_offset_x_ + x2.x, BL_leg_offset_y_, BL_leg_offset_z_),
        Eigen::Vector3d(BR_leg_offset_x_ + x2.x, BR_leg_offset_y_, BR_leg_offset_z_)
        };
      leg_yaw_ref = init_leg_yaw;
      COM_pos_ref = Eigen::Vector3d(x2.x, y_init, z_init + z_amplitude * (1 - cos(2 * M_PI * z_frequency * movingTime)));
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
      phase = 3;
      initialize_flag = false;
    }
  }

  // Finalize
  else if (phase == 3) {
    ROS_INFO("Moving x sine wave complete!");
    stop_controller();
  }
}

void wheel_running::XTrajectoryGenerator(){
  //** ZMPTG Start **//////////////////////////////////////////////////////////////////////////////

  // 1点目の時刻，位置，速度，加速度を指定
  x1 = {  start_time, 
          0.0, 
          0.0, 
          0.0 };

  // 2点目の時刻，位置，速度，加速度を指定
  x2 = {  end_time,   
          1.0, 
          0.0, 
          0.0 };
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_x = {x1, x2};

  // 5次多項式補間の係数を計算
  five_spline_x.Calc_Spline(points_x);
  
  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_s){
      x_trajectory(period_count) = 0.0;
    }
    else if(period_count < c_e){
      x_trajectory(period_count) = five_spline_x.Get_Spline_x(period_count/controller_frequency);
    }
    else{
       x_trajectory(period_count) = x2.x;
    }
  }
}
}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "wheel_running");
  // ROS_WARN("wheel running");
  MELEW3_control::BaseController* controller = new MELEW3_control::wheel_running;
  ros::waitForShutdown();
  return 0;
}