/**
 * @file    walk.cpp
 * @author  Byakko
 * @brief   do a walk motion
 * @version 1.0
 * @date    2024-11-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <MELEW3_control/BaseController.h>

#include <MELEW3_control/utils.hpp>

using namespace std;

namespace MELEW3_control {

class walk : public BaseController {
private:
  double pitch_start_time = 2.0;
  double pitch_end_time = 7.0;
  double wheel_start_time = 0;
  double wheel_end_time = 2;
//2+5(7)+2(9)+5(14)+2(16)
  const double settingTime = 3.0;     // 動作開始姿勢への遷移時間[s]
  const double movingTime = 16.0;     // 動作時間[s]
  const double step_time = 0.5;

  int p_s = pitch_start_time * controller_frequency;
  int p_e = pitch_end_time * controller_frequency;
  int w_s = wheel_start_time * controller_frequency;
  int w_e = wheel_end_time * controller_frequency;
  int mt = step_time * controller_frequency;

  const double x_init = 0.0;                // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;                // y軸ベースリンク初期位置[m]
  const double z_init = 0.4;               // z軸ベースリンク初期位置[m]
  const double psi_leg_init = 0.0;

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]
  double step_loop_time;
  double step_start_time;

  int support_flag;
  int counter;
  double x_offset;
  std::vector<Eigen::Vector3d> prev_leg_pos_ref;

public:
  ros::Publisher FL_leg_pos_ref_pub_;  //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;  //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;  //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;  //!< 右後脚の目標脚先位置用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;     //!< 目標重心位置用パブリッシャー

  Utils::Utils util;
//---------
  Utils::Five_Spline::point pitch1;
  Utils::Five_Spline::point pitch2;
  Utils::Five_Spline five_spline_pitch;
  Eigen::VectorXd pitch_trajectory;

  Utils::Five_Spline::point x1;
  Utils::Five_Spline::point x2;
  Utils::Five_Spline five_spline_x;
  Eigen::VectorXd x_trajectory;
  Eigen::VectorXd x2_trajectory;
  // Eigen::VectorXd z_trajectory;
//---------
  Eigen::Vector3d gene_zmp{x_init, y_init, z_init};     //!< ５次補完ZMP位置を一時保存する変数
  Eigen::Vector3d ZMP_pos_ref{x_init, y_init, z_init};  //!< 目標ZMP位置を一時保存する変数
  Eigen::Vector3d COM_vel_ref{x_init, y_init, z_init};  //!< 目標重心速度を一時保存する変数
  Eigen::Vector3d COM_acl_ref{x_init, y_init, z_init};  //!< 目標重心加速度を一時保存する変数
  std::vector<Eigen::Vector3d> init_leg_pos{            // 初期足部位置
    Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_),
    Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
    Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_),
    Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_)};
  std::vector<double>          init_leg_yaw = {psi_leg_init, psi_leg_init, psi_leg_init, psi_leg_init};  // 初期足部YAW角度
  std::vector<Eigen::VectorXf> init_torque{Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4),
                                           Eigen::VectorXf::Zero(4)};
  Eigen::Vector3d init_COM_pos{x_init, y_init, z_init};        // 初期ベースリンク位置
  double                       init_COM_yaw = 0.0;                    // 初期ベースリンクYAW角度
//----------
  double                       init_COM_pitch = 0.0;                    // 初期ベースリンクPITCH角度
//----------

//----------
  void X_position_generator();
  void x2_position_generator();
  void z_position_generator();
  walk(void);
//----------
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
walk::walk(void) {
  // ROS_WARN("start ready");
  start_controller();
  // ROS_WARN("start");
}

/**
 * @brief
 *
 */
void walk::control_loop(void) {
  double current_time = get_time();
  // Transition to initial pose
  // ROS_WARN("psi_sin loop in");
  if (phase == 0) {
    if (pose_transition()) {
      // ROS_WARN("potra haitta");
      /*** パブリッシャ，サブスクライバの初期化 ***/
      FL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FL_leg_pos_ref", 1);
      FR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FR_leg_pos_ref", 1);
      BL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BL_leg_pos_ref", 1);
      BR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BR_leg_pos_ref", 1);
      COM_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/COM_pos_ref", 1);

      //////-------
      x2_trajectory.resize(mt*2);
      x2_position_generator();
      x_trajectory.resize(mt*2);
      X_position_generator();
      // z_trajectory.resize(mt*2);
      // z_position_generator();

      //////-------

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
      //ROS_WARN("psi_amp: %f, psi_freq: %f", psi_amplitude, psi_frequency);
      ROS_INFO("Enter key to start moving psi sine wave");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }
  // Move walk
  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      step_start_time = get_time();
      step_loop_time = 0;
      counter = 0;
      support_flag = 1;
      x_offset = 0.05;
      prev_leg_pos_ref = leg_pos_ref;
      initialize_flag = true;
    }

    loop_time = current_time - tmp_time;
    step_loop_time = current_time - step_start_time;


    /*
        ここで以下を決定する
        ・足先位置            ：leg_pos_ref
        ・足先YAW角度         ：leg_yaw_ref
        ・ベースリンク位置    ：COM_pos_ref
        ・ベースリンクYAW角度 ：COM_yaw_ref
        ＋ベースリンクPITCH角度：COM_pitch_ref ?
        （World座標系）
    */  
        if (support_flag == 1){
            leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_ - 20*x_trajectory(step_loop_time*controller_frequency)*x_trajectory(step_loop_time*controller_frequency)+x_trajectory(step_loop_time*controller_frequency)),
            Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_ - 20*x_trajectory(step_loop_time*controller_frequency)*x_trajectory(step_loop_time*controller_frequency)+x_trajectory(step_loop_time*controller_frequency)),
            Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_)
            };
        } else {
            leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_ - 20*x_trajectory(step_loop_time*controller_frequency)*x_trajectory(step_loop_time*controller_frequency)+x_trajectory(step_loop_time*controller_frequency)),
            Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_ - 20*x_trajectory(step_loop_time*controller_frequency)*x_trajectory(step_loop_time*controller_frequency)+x_trajectory(step_loop_time*controller_frequency))
            };
        };

    double com_x_avg = (leg_pos_ref[FL].x() + leg_pos_ref[FR].x() + leg_pos_ref[BL].x() + leg_pos_ref[BR].x()) / 4.0;
    // ROS_INFO("com: %d", com_x_avg);
    leg_yaw_ref = init_leg_yaw;
    COM_pos_ref = Eigen::Vector3d(com_x_avg, y_init, z_init);
    COM_yaw_ref = 0.0;
    COM_pitch_ref = 0.0;
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

    // double output = COM_pitch_ref * (180.0 / M_PI);
    // ROS_WARN("COM_pitch_ref: %f", output);
    
    if (step_loop_time >= step_time) {
       counter++;             // 增加步数计数器 
       support_flag = !support_flag;


       step_loop_time = 0;               
       step_start_time = current_time;   // 更新步态周期开始时间
       ROS_INFO("Step count: %d", counter);
    }

    if (counter >= 20){
    phase = 3;
    initialize_flag = false;
  };
  }
  // Finalize
  if (phase == 3) {
    ROS_INFO("Moving walk complete!");
    stop_controller();
  };
}

void walk::x2_position_generator()
{
  // 定义初始和结束位置、速度、加速度
  double x0 = 0.0;         // 起始位置
  double v0 = 0.0;         // 起始速度
  double a0 = 0.0;         // 起始加速度
  double x1 = 0.1;        // 结束位置
  double v1 = 0.0;         // 结束速度
  double a1 = 0.0;         // 结束加速度

  // 计算五次多项式的系数
  double T = 0.5;  // 总轨迹时间

  double a0_coef = x0;
  double a1_coef = v0;
  double a2_coef = a0 / 2.0;
  double a3_coef = (20 * x1 - 20 * x0 - (8 * v1 + 12 * v0) * T - (3 * a0 - a1) * T * T) / (2 * T * T * T);
  double a4_coef = (30 * x0 - 30 * x1 + (14 * v1 + 16 * v0) * T + (3 * a0 - 2 * a1) * T * T) / (2 * T * T * T * T);
  double a5_coef = (12 * x1 - 12 * x0 - (6 * v1 + 6 * v0) * T - (a0 - a1) * T * T) / (2 * T * T * T * T * T);
  
  // 时间步长
  double dt = T / 300.0;

  // 生成 x_trajectory
  for(int period_count = 0; period_count <= 300; period_count++) {
    double t = period_count * dt;  // 当前时刻

    if (t <= T) {
      // 使用五次多项式生成轨迹
      double trajectory = a0_coef + a1_coef * t + a2_coef * pow(t, 2) +
                          a3_coef * pow(t, 3) + a4_coef * pow(t, 4) + a5_coef * pow(t, 5);
      x2_trajectory[period_count] = trajectory;
    } else {
      x2_trajectory[period_count] = x1;  // 超过轨迹时间，位置保持在终点
    }

    // 打印 x_trajectory 的值
    std::cout << "x2_trajectory[" << period_count << "] = " << x2_trajectory(period_count) << std::endl;
  }
}

void walk::X_position_generator()
{
  // 定义初始和结束位置、速度、加速度
  double x0 = 0.0;         // 起始位置
  double v0 = 0.0;         // 起始速度
  double a0 = 0.0;         // 起始加速度
  double x1 = 0.05;        // 结束位置
  double v1 = 0.0;         // 结束速度
  double a1 = 0.0;         // 结束加速度

  // 计算五次多项式的系数
  double T = 0.5;  // 总轨迹时间

  double a0_coef = x0;
  double a1_coef = v0;
  double a2_coef = a0 / 2.0;
  double a3_coef = (20 * x1 - 20 * x0 - (8 * v1 + 12 * v0) * T - (3 * a0 - a1) * T * T) / (2 * T * T * T);
  double a4_coef = (30 * x0 - 30 * x1 + (14 * v1 + 16 * v0) * T + (3 * a0 - 2 * a1) * T * T) / (2 * T * T * T * T);
  double a5_coef = (12 * x1 - 12 * x0 - (6 * v1 + 6 * v0) * T - (a0 - a1) * T * T) / (2 * T * T * T * T * T);

  // 时间步长
  double dt = T / 300.0;

  // 生成 x_trajectory
  for(int period_count = 0; period_count <= 300; period_count++) {
    double t = period_count * dt;  // 当前时刻

    if (t <= T) {
      // 使用五次多项式生成轨迹
      double trajectory = a0_coef + a1_coef * t + a2_coef * pow(t, 2) +
                          a3_coef * pow(t, 3) + a4_coef * pow(t, 4) + a5_coef * pow(t, 5);
      x_trajectory[period_count] = trajectory;
    } else {
      x_trajectory[period_count] = x1;  // 超过轨迹时间，位置保持在终点
    }
    // 打印 x_trajectory 的值
    std::cout << "x_trajectory[" << period_count << "] = " << x_trajectory(period_count) << std::endl;
  }
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "walk");
  // ROS_WARN("psi_sin in");
  MELEW3_control::BaseController* controller = new MELEW3_control::walk;
  ros::waitForShutdown();
  return 0;
}
