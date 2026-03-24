/**
 * @file    slide.cpp
 * @author  Byakko
 * @brief   do a slide motion on ground
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

class slide : public BaseController {
private:
  double pitch_start_time = 2.0;
  double pitch_end_time = 7.0;
  double wheel_start_time = 0;
  double wheel_end_time = 2;

  const double settingTime = 3.0;     // 動作開始姿勢への遷移時間[s]
  const double movingTime = 16.0;     // 動作時間[s]
  const double step_time = 1.0;

  int p_s = pitch_start_time * controller_frequency;
  int p_e = pitch_end_time * controller_frequency;
  int w_s = wheel_start_time * controller_frequency;
  int w_e = wheel_end_time * controller_frequency;
  int mt = step_time * controller_frequency;

  const double x_init = 0.0;                // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;                // y軸ベースリンク初期位置[m]
  const double z_init = 0.35;               // z軸ベースリンク初期位置[m]
  const double psi_leg_init = 0.0;

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]
  double step_loop_time;
  double step_start_time;
  double leg_x_offset;

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
  Eigen::VectorXd z_trajectory;
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
  slide(void);
//----------
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
slide::slide(void) {
  // ROS_WARN("start ready");
  start_controller();
  // ROS_WARN("start");
}

/**
 * @brief
 *
 */
void slide::control_loop(void) {
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
      ROS_INFO("Enter key to start sliding");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }
  // Move slide
  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      step_start_time = get_time();
      step_loop_time = 0;
      counter = 0;
      support_flag = 1;
      prev_leg_pos_ref = leg_pos_ref;
      initialize_flag = true;
      leg_x_offset = 0.0;
    }

    loop_time = current_time - tmp_time;
    step_loop_time = current_time - step_start_time;



    // 修改这里改变滑动的步幅
    if (step_loop_time>0.5){
      leg_x_offset = 0.15;
      } else {
        leg_x_offset = step_loop_time / 3.333;  // 0.5/3.3333=0.15
      };


   switch (counter)
   {
   case 0: case 10:
    leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(FR_leg_offset_x_ + leg_x_offset/2, FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(BL_leg_offset_x_ + leg_x_offset/2, BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_)
            };
    break;

    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        if (support_flag == 1){
            leg_pos_ref = {
            Eigen::Vector3d(prev_leg_pos_ref[0].x(), FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(prev_leg_pos_ref[1].x() + leg_x_offset, FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(prev_leg_pos_ref[2].x() + leg_x_offset, BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(prev_leg_pos_ref[3].x(), BR_leg_offset_y_, BR_leg_offset_z_)
            };
        } else {
            leg_pos_ref = {
            Eigen::Vector3d(prev_leg_pos_ref[0].x() + leg_x_offset, FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(prev_leg_pos_ref[1].x(), FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(prev_leg_pos_ref[2].x(), BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(prev_leg_pos_ref[3].x() + leg_x_offset, BR_leg_offset_y_, BR_leg_offset_z_)
            };
        };
    break;
    
    default:
    leg_pos_ref = {
        Eigen::Vector3d(FL_leg_offset_x_+ leg_x_offset * counter, FL_leg_offset_y_, FL_leg_offset_z_),
        Eigen::Vector3d(FR_leg_offset_x_+ leg_x_offset * counter, FR_leg_offset_y_, FR_leg_offset_z_),
        Eigen::Vector3d(BL_leg_offset_x_+ leg_x_offset * counter, BL_leg_offset_y_, BL_leg_offset_z_),
        Eigen::Vector3d(BR_leg_offset_x_+ leg_x_offset * counter, BR_leg_offset_y_, BR_leg_offset_z_)
        };
    break;
   }

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

    
    if (step_loop_time >= (step_time)) {
       counter++;             // 增加步数计数器 
       support_flag = !support_flag;

       for (size_t i = 0; i < leg_pos_ref.size(); ++i) {
            prev_leg_pos_ref[i] = leg_pos_ref[i];
        }

       for (size_t i = 0; i < prev_leg_pos_ref.size(); ++i) {
            ROS_INFO("Step %d - Leg %zu Position: x = %f, y = %f, z = %f",
                    counter, i, prev_leg_pos_ref[i].x(), prev_leg_pos_ref[i].y(), prev_leg_pos_ref[i].z());
        }
       step_loop_time = 0.0;               
       step_start_time = current_time;   // 更新步态周期开始时间
       ROS_INFO("Step count: %d", counter);
    }

    if (counter >= 10){
    phase = 3;
    initialize_flag = false;
  };
  }
  // Finalize
  if (phase == 3) {
    ROS_INFO("Moving slide complete!");
    stop_controller();
  };
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "slide");
  // ROS_WARN("psi_sin in");
  MELEW3_control::BaseController* controller = new MELEW3_control::slide;
  ros::waitForShutdown();
  return 0;
}
