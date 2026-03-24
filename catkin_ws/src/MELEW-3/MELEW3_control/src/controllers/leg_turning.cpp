/**
 * @file    leg_turning.cpp
 * @author  
 * @brief   控制机器人通过调整四条腿的YAW角实现转向15度
 * @version 1.1
 * @date    
 *
 * @copyright 
 *
 */
#include <MELEW3_control/BaseController.h>
#include <MELEW3_control/utils.hpp>

using namespace std;

namespace MELEW3_control {

class leg_turning : public BaseController {
private:
  const double turning_rate = M_PI / 36.0;  // 转向速率 [rad/s]，约为0.02618 rad/s，实现15度转向
  const double settingTime = 2.0;            // 过渡到起始姿态的时间 [s]
  const double movingTime = 3.0;            // 转向持续时间 [s]
  const double x_init = 0.0;                 // 初始X位置 [m]
  const double y_init = 0.0;                 // 初始Y位置 [m]
  const double z_init = 0.35;                 // 初始Z位置 [m]
  const double psi_init = 0.0;               // 初始偏航角 [rad]
  double tem_pos = 0.0;

  double loop_time;  // 当前阶段内的时间 [s]
  double tmp_time;   // 时间偏移量 [s]

  Eigen::Vector3d init_COM_pos{x_init, y_init, z_init};    // 初始重心位置
  double init_COM_yaw = psi_init;                         // 初始重心偏航角

public:
  
  ros::Publisher FL_leg_pos_ref_pub_;   //!< 左前腿目标位置发布器
  ros::Publisher FR_leg_pos_ref_pub_;   //!< 右前腿目标位置发布器
  ros::Publisher BL_leg_pos_ref_pub_;   //!< 左后腿目标位置发布器
  ros::Publisher BR_leg_pos_ref_pub_;   //!< 右后腿目标位置发布器
  ros::Publisher COM_pos_ref_pub_;      //!< 重心位置目标发布器

  Utils::Utils util;
  double safty = 0.0;
  Eigen::Vector3d gene_zmp{x_init, y_init, z_init};        //!< 生成的ZMP位置（此处未使用）
  Eigen::Vector3d ZMP_pos_ref{x_init, y_init, z_init};     //!< 目标ZMP位置（此处未使用）
  Eigen::Vector3d COM_vel_ref{x_init, y_init, z_init};     //!< 目标重心速度（此处未使用）
  Eigen::Vector3d COM_acl_ref{x_init, y_init, z_init};     //!< 目标重心加速度（此处未使用）
  
  // 初始腿部位置
  std::vector<Eigen::Vector3d> init_leg_pos{
    Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_),
    Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
    Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_),
    Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_)
  };
  
  std::vector<double> init_leg_yaw = {0.0, 0.0, 0.0, 0.0};  // 初始腿部YAW角度
  
  // 初始扭矩设置
  std::vector<Eigen::VectorXf> init_torque{
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4)
  };
  
  leg_turning(void);
  virtual void control_loop(void) override;
};

leg_turning::leg_turning(void) {
  start_controller();
}

void leg_turning::control_loop(void) {
  double current_time = get_time();
  
  if (phase == 0) {
    if (pose_transition()) {
      FL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FL_leg_pos_ref", 1);
      FR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FR_leg_pos_ref", 1);
      BL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BL_leg_pos_ref", 1);
      BR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BR_leg_pos_ref", 1);
      COM_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/COM_pos_ref", 1);

      ROS_INFO("phase 0 is over");
      initialize_flag = false;
      phase = 1;
    }
  }

  if (phase == 1) {
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase 1 is over");
      ROS_INFO("Enter any button to start turn:");
      char buf;
      std::cin.get(buf);
      phase = 2;
      initialize_flag = false;
    }
  }

  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      initialize_flag = true;
    }

    loop_time = current_time - tmp_time;

    tem_pos = turning_rate * loop_time;

    leg_pos_ref = init_leg_pos;
    COM_yaw_ref = init_COM_yaw;
    COM_pos_ref = init_COM_pos;
    leg_yaw_ref = {tem_pos,tem_pos,-tem_pos,-tem_pos};
    leg_motor_torque = init_torque;

    melew3_msgs::leg_pose  pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
                            pub_COM_pos_ref;

    util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);

    util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);

    FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
    FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
    BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
    BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
    COM_pos_ref_pub_.publish(pub_COM_pos_ref);

    if (current_time >= tmp_time + movingTime) {
      phase = 3;
      initialize_flag = false;
    }
  }

  else if (phase == 3) {
    ROS_INFO("Finished!");
    stop_controller();
  }
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "turning");
  MELEW3_control::BaseController* controller = new MELEW3_control::leg_turning;
  ros::waitForShutdown();
  return 0;
}
