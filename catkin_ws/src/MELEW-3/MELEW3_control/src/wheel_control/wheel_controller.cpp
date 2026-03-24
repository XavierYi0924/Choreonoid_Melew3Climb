/**
 * @file    wheel_controller.cpp
 * @author  Taisei Suzuki
 * @brief   Move z sine wave
 * @version 1.0
 * @date    2023-09-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <MELEW3_control/BaseController.h>

#include "sne_controller/include/sne_controller/sne_controller.hpp"

using namespace std;

namespace MELEW3_control {

class wheel_controller : public BaseController {
private:
  const double z_frequency = 0.25;      // 周波数[Hz]
  const double z_amplitude = 0.05;      // 振幅[m]
  const double settingTime = 2.0;       // 動作開始姿勢への遷移時間[s]
  const double movingTime = 25.0;       // 動作時間[s]
  const double x_init = 0.0;            // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;            // y軸ベースリンク初期位置[m]
  const double z_init = 0.41441016151;  // z軸ベースリンク初期位置[m]
  const double psi_init = 0.0;          // psi初期位置[rad]
  int          count = 0;

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

  Eigen::Vector3d left_p_init;   // 動作開始姿勢
  Eigen::Vector3d right_p_init;  // 動作開始姿勢

  SneController sne;

  std::vector<Eigen::Vector3d> init_leg_pos_pre{// 初期足部位置
                                                Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_),
                                                Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
                                                Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_),
                                                Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_)};
  std::vector<double>          init_leg_yaw_pre = {0.0, 0.0, 0.0, 0.0};   // 初期足部YAW角度
  Eigen::Vector3d              init_COM_pos_pre{x_init, y_init, z_init};  // 初期ベースリンク位置
  double                       init_COM_yaw_pre = 0.0;                    // 初期ベースリンクYAW角度

public:
  std::vector<Eigen::Vector3d> init_leg_pos{// 初期足部位置
                                            Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_),
                                            Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
                                            Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_),
                                            Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_)};
  std::vector<double>          init_leg_yaw = {0.0, 0.0, 0.0, 0.0};   // 初期足部YAW角度
  Eigen::Vector3d              init_COM_pos{x_init, y_init, z_init};  // 初期ベースリンク位置
  double                       init_COM_yaw = 0.0;                    // 初期ベースリンクYAW角度

  wheel_controller(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
wheel_controller::wheel_controller(void) : sne(nh, pnh) { start_controller(); }

/**
 * @brief
 *
 */
void wheel_controller::control_loop(void) {
  double current_time = get_time();
  // Transition to initial pose
  if (phase == 0) {
    if (pose_transition()) {
      ROS_INFO("phase0 end");
      initialize_flag = false;
      phase = 1;
    }
  }

  // Transition to start pose
  if (phase == 1) {
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase1 end");
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
    if (count % 5 == 0)
      if (sne.SneControllerCallback(loop_time)) {
        leg_pos_ref = sne.leg_pos;
        leg_yaw_ref = sne.leg_yaw;
        COM_pos_ref = sne.com_pos;
        COM_yaw_ref = sne.com_yaw;
      } else {
        phase = 3;
        initialize_flag = false;
      }

    count++;
  }

  // Finalize
  else if (phase == 3) {
    ROS_INFO("Moving z sine wave complete!");
    stop_controller();
  }
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "wheel_controller");
  MELEW3_control::BaseController* controller = new MELEW3_control::wheel_controller;
  ros::waitForShutdown();
  return 0;
}
