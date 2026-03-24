/**
 * @file    dancing.cpp
 * @author  Yuta Ishizawa
 * @brief   Move z sine wave
 * @version 1.0
 * @date    2022-11-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <MELEW3_control/BaseController.h>
#include <MELEW3_control/utils.hpp>

using namespace std;

namespace MELEW3_control {

class dancing : public BaseController {
private:
  const double z_frequency = 2;                            // 周波数[Hz]
  const double z_amplitude = 0.005;                            // 振幅[m]
  const double settingTime = 2.0;                             // 動作開始姿勢への遷移時間[s]
  const double movingTime = 10.0;                             // 動作時間[s]
  const double x_init = 0.0;                                  // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;                                  // y軸ベースリンク初期位置[m]
  const double z_init = 0.4;                                  // z軸ベースリンク初期位置[m]
  const double psi_init = 0.0;                                // psi初期位置[rad]
  
  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

  Eigen::Vector3d left_p_init;   // 動作開始姿勢
  Eigen::Vector3d right_p_init;  // 動作開始姿勢

public:
  
  ros::Publisher FL_leg_pos_ref_pub_;   //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;   //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;   //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;   //!< 右後脚の目標脚先位置用パブリッシャー
  ros::Publisher gene_zmp_pub_;         //!< Generated ZMP 位置用パブリッシャー
  ros::Publisher ZMP_pos_ref_pub_;      //!< 目標ZMP位置用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;      //!< 目標重心位置用パブリッシャー
  ros::Publisher COM_vel_ref_pub_;      //!< 目標重心速度用パブリッシャー
  ros::Publisher COM_acl_ref_pub_;      //!< 目標重心加速度用パブリッシャー

  Utils::Utils util;
  double safty = 0.0;
  Eigen::Vector3d gene_zmp{x_init, y_init, z_init};        //!< ５次補完ZMP位置を一時保存する変数
  Eigen::Vector3d ZMP_pos_ref{x_init, y_init, z_init};     //!< 目標ZMP位置を一時保存する変数
  Eigen::Vector3d COM_vel_ref{x_init, y_init, z_init};     //!< 目標重心速度を一時保存する変数
  Eigen::Vector3d COM_acl_ref{x_init, y_init, z_init};     //!< 目標重心加速度を一時保存する変数
  std::vector<Eigen::Vector3d> init_leg_pos{                              // 初期足部位置
    Eigen::Vector3d(FL_leg_offset_x_ + safty, FL_leg_offset_y_ + safty, FL_leg_offset_z_),
    Eigen::Vector3d(FR_leg_offset_x_ + safty, FR_leg_offset_y_ - safty, FR_leg_offset_z_),
    Eigen::Vector3d(BL_leg_offset_x_ - safty, BL_leg_offset_y_ + safty, BL_leg_offset_z_),
    Eigen::Vector3d(BR_leg_offset_x_ - safty, BR_leg_offset_y_ - safty, BR_leg_offset_z_)
  };
  std::vector<double> init_leg_yaw = {0.0, 0.0, 0.0, 0.0};                // 初期足部YAW角度
  std::vector<Eigen::VectorXf> init_torque{
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4)
  };
  Eigen::Vector3d init_COM_pos{x_init, y_init, z_init};                   // 初期ベースリンク位置
  double init_COM_yaw = 0.0;                                              // 初期ベースリンクYAW角度

  dancing(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
dancing::dancing(void) {
  start_controller();
}

/**
 * @brief
 *
 */
void dancing::control_loop(void) {
  double current_time = get_time();
  // Transition to initial pose
  if (phase == 0) {
    if (pose_transition()) {
        /*** パブリッシャ，サブスクライバの初期化 ***/
      FL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FL_leg_pos_ref", 1);
      FR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FR_leg_pos_ref", 1);
      BL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BL_leg_pos_ref", 1);
      BR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BR_leg_pos_ref", 1);
      gene_zmp_pub_ = nh.advertise<melew3_msgs::leg_pose>("/gene_zmp_test", 1);
      ZMP_pos_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/ZMP_pos_ref_test", 1);
      COM_pos_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_pos_ref", 1);
      COM_vel_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_vel_ref", 1);
      COM_acl_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_acl_ref", 1);

      ROS_INFO("phase0 end");
      initialize_flag = false;
      phase = 1;
    }
  }

  // Transition to start pose
  if (phase == 1) {
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase1 end");
      ROS_WARN("z_amp: %f, z_freq: %f", z_amplitude, z_frequency);
      ROS_INFO("Enter key to start moving z sine wave");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }

  // Move z sine wave
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
    if(loop_time < 1 / (2 * z_frequency)){
      leg_pos_ref = { Eigen::Vector3d(FL_leg_offset_x_ + safty, FL_leg_offset_y_ + safty, FL_leg_offset_z_ + z_amplitude * (1 - cos(2 * M_PI * z_frequency * loop_time))),
                      Eigen::Vector3d(FR_leg_offset_x_ + safty, FR_leg_offset_y_ - safty, FR_leg_offset_z_),
                      Eigen::Vector3d(BL_leg_offset_x_ - safty, BL_leg_offset_y_ + safty, BL_leg_offset_z_),
                      Eigen::Vector3d(BR_leg_offset_x_ - safty, BR_leg_offset_y_ - safty, BR_leg_offset_z_ + z_amplitude * (1 - cos(2 * M_PI * z_frequency * loop_time)))
                    };
    }
    else{
      leg_pos_ref = { Eigen::Vector3d(FL_leg_offset_x_ + safty, FL_leg_offset_y_ + safty, FL_leg_offset_z_ + z_amplitude * (1 - cos(2 * M_PI * z_frequency * loop_time))),
                      Eigen::Vector3d(FR_leg_offset_x_ + safty, FR_leg_offset_y_ - safty, FR_leg_offset_z_ + z_amplitude * (1 - cos(2 * M_PI * z_frequency * loop_time - M_PI))),
                      Eigen::Vector3d(BL_leg_offset_x_ - safty, BL_leg_offset_y_ + safty, BL_leg_offset_z_ + z_amplitude * (1 - cos(2 * M_PI * z_frequency * loop_time - M_PI ))),
                      Eigen::Vector3d(BR_leg_offset_x_ - safty, BR_leg_offset_y_ - safty, BR_leg_offset_z_ + z_amplitude * (1 - cos(2 * M_PI * z_frequency * loop_time)))
                    };
    }
    leg_yaw_ref = init_leg_yaw;
    COM_pos_ref = init_COM_pos;
    COM_yaw_ref = init_COM_yaw;
    leg_motor_torque = init_torque;

    /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
    melew3_msgs::leg_pose  pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
                            pub_COM_pos_ref, pub_COM_vel_ref, pub_COM_acl_ref, pub_gene_zmp, pub_ZMP_pos_ref;

    util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);

    util.Vector3dToLegpose(gene_zmp, COM_yaw_ref, pub_gene_zmp);
    util.Vector3dToLegpose(ZMP_pos_ref, COM_yaw_ref, pub_ZMP_pos_ref);
    util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
    util.Vector3dToLegpose(COM_vel_ref, COM_yaw_ref, pub_COM_vel_ref);
    util.Vector3dToLegpose(COM_acl_ref, COM_yaw_ref, pub_COM_acl_ref);

    FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
    BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
    FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
    BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
    gene_zmp_pub_.publish(pub_gene_zmp);
    ZMP_pos_ref_pub_.publish(pub_ZMP_pos_ref);
    COM_pos_ref_pub_.publish(pub_COM_pos_ref);
    COM_vel_ref_pub_.publish(pub_COM_vel_ref);
    COM_acl_ref_pub_.publish(pub_COM_acl_ref);

    if (current_time >= tmp_time + movingTime) {
      phase = 3;
      initialize_flag = false;
    }
  }

  // Finalize
  else if (phase == 3) {
    ROS_INFO("Moving z sine wave complete!");
    stop_controller();
  }
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "dancing");
  MELEW3_control::BaseController* controller = new MELEW3_control::dancing;
  ros::waitForShutdown();
  return 0;
}
