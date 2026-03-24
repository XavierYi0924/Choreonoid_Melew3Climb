/**
 * @file BaseController.h
 * @author Hayato Ota
 * @brief
 * @version 1.0
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MMELEW3_BASECONTROLLER_H_
#define MELEW3_BASECONTROLLER_H_

#include <MELEW3_control/Interpolator.h>
#include <MELEW3_control/basic_op.h>
#include <dynamic_reconfigure/client.h>
#include <melew3_control/joint_pd_gainConfig.h>
#include <melew3_msgs/MotionCommand.h>
#include <melew3_msgs/leg_info_set.h>
#include <melew3_msgs/leg_pose.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <mutex>

#include "../src/MELEW3_kinematics/MELEW3_Kinematics.h"

namespace MELEW3_control {

enum JOINT : int {
  FL1_MOTOR,       // = 0
  FL2_MOTOR,       // = 1
  FL3_MOTOR,       // = 2
  FL4_MOTOR,       // = 3
  FR1_MOTOR,       // = 4
  FR2_MOTOR,       // = 5
  FR3_MOTOR,       // = 6
  FR4_MOTOR,       // = 7
  BL1_MOTOR,       // = 8
  BL2_MOTOR,       // = 9
  BL3_MOTOR,       // = 10
  BL4_MOTOR,       // = 11
  BR1_MOTOR,       // = 12
  BR2_MOTOR,       // = 13
  BR3_MOTOR,       // = 14
  BR4_MOTOR,       // = 15
  WHEEL_FL_MOTOR,  // = 16
  WHEEL_FR_MOTOR,  // = 17
  WHEEL_BL_MOTOR,  // = 18
  WHEEL_BR_MOTOR,  // = 19
  JOINT_NUM        // = 20
};
enum LR : int { FL, FR, BL, BR };

enum LEG : int {
  FL_LEG,  // = 0
  FR_LEG,  // = 1
  BL_LEG,  // = 2
  BR_LEG,  // = 3
  LEG_NUM  // = 4
};

enum JOINT_serial {
  HIP_YAW,        //!< = 0
  HIP_ROLL,       //!< = 1
  HIP_PITCH,      //!< = 2
  KNEE,           //!< = 3
  LEG_JOINT_NUM,  //!< = 4
};

enum ONE_LEG_JOINT {
  HIP_YAW_JOINT,            //!< = 0
  HIP_ROLL_JOINT,           //!< = 1
  HIP_PITCH_JOINT,          //!< = 2
  KNEE_JOINT,               //!< = 3
  WHEEL_JOINT,              //!< = 4
  ONE_LEG_JOINT_NUM         //!< = 5
};
class BaseController {
private:
  
  // static constexpr double controller_frequency = 350.0;  // loop frequency [Hz]
  bool angle_mode = true;  // どうしても角度ベースで動かしたいときに使用
  melew3_kinematics::MELEW3_Kinematics melew3Kinematics;

  ros::Publisher leg_pos_pub;
  ros::Publisher leg_pos_ref_pub;
  ros::Publisher leg_FL_position_controller_pub_;  //!< 左前脚モータ用パブリッシャー
  ros::Publisher leg_FR_position_controller_pub_;  //!< 右前脚モータ用パブリッシャー
  ros::Publisher leg_BL_position_controller_pub_;  //!< 左後脚モータ用パブリッシャー
  ros::Publisher leg_BR_position_controller_pub_;  //!< 右後脚モータ用パブリッシャー
  ros::Publisher wheel_controller_pub_;            //!< 車輪モータ用パブリッシャー

  ros::Publisher FL_leg_motion_cmd_pub_;  //!< 実機モータ用HWIへのパブリッシャー
  ros::Publisher FR_leg_motion_cmd_pub_;  //!< 実機モータ用HWIへのパブリッシャー
  ros::Publisher BL_leg_motion_cmd_pub_;  //!< 実機モータ用HWIへのパブリッシャー
  ros::Publisher BR_leg_motion_cmd_pub_;  //!< 実機モータ用HWIへのパブリッシャー
  ros::Publisher wheel_motion_cmd_pub_;   //!< 実機モータ用HWIへのパブリッシャー

  std::string               leg_pos_topic_name = "leg_pos";
  std::string               leg_pos_ref_topic_name = "leg_pos_ref";
  melew3_msgs::leg_info_set leg_pos_data;
  melew3_msgs::leg_info_set leg_pos_ref_data;

  ros::Subscriber   joint_state_sub;
  ros::Subscriber   imu_data_sub;
  ros::Subscriber   FL_joint_state_sub;
  ros::Subscriber   FR_joint_state_sub;
  ros::Subscriber   BL_joint_state_sub;
  ros::Subscriber   BR_joint_state_sub;
  ros::AsyncSpinner spinner;
  std::mutex        joint_states_mutex;
  ros::Time         t_start;

  Eigen::VectorXd                      qref;       // Target joint position vector
  Eigen::VectorXd                      q_init;     // Initial joint position vector on starting controller
  Eigen::VectorXd                      q_current;  // Current joint position vector
  Eigen::Vector3d                      left_leg_pos_current;
  Eigen::Vector3d                      right_leg_pos_current;
  double                               left_psi_current;
  double                               right_psi_current;
  cnoid::Interpolator<Eigen::VectorXd> joint_Interpolator;

  // Angles of basical pose of MELEW3
  const double default_z = -0.3266;
  const double default_psi = 0.0;

  /* parameters used for Kinematics calculation */
  Eigen::Vector3d p_b1 = Eigen::Vector3d::Zero();      //!< 点B1の単位ベクトル，{xB1, yB1, zB1}
  Eigen::Vector3d p_b2 = Eigen::Vector3d::Zero();      //!< 点B2の単位ベクトル，{xB2, yB2, zB2}
  Eigen::Vector3d p_b3 = Eigen::Vector3d::Zero();      //!< 点B3の単位ベクトル，{xB3, yB3, zB3}
  Eigen::Vector3d p_b4 = Eigen::Vector3d::Zero();      //!< 点B4の単位ベクトル，{xB4, yB4, zB4}
  Eigen::Vector3d p_D1 = Eigen::Vector3d::Zero();      //!< 点D1の座標，{xD1, yD1, zD1}
  Eigen::Vector3d p_D2 = Eigen::Vector3d::Zero();      //!< 点D2の座標，{xD2, yD2, zD2}
  Eigen::Vector3d crossB14 = Eigen::Vector3d::Zero();  //!< p_b1とp_b4の外積
  double          dotB14 = 0.0;                        //!< p_b1とp_b4の内積
  Eigen::Vector3d crossB23 = Eigen::Vector3d::Zero();  //!< p_b2とp_b3の外積
  double          dotB23 = 0.0;                        //!< p_b2とp_b3の内積
  const double    MAXcosDOD = cos(3.0 / 4.0 * M_PI);
  const double    MINcosDOD = cos(M_PI / 9.0);
  const double    MAXangle = M_PI / 3.0;
  const double    MINangle = -(13.0 / 36.0) * M_PI;
  Eigen::VectorXd c;   // 逆運動学計算に使用する変数
  Eigen::Vector2d l;   // 点D1，D2の座標，{{xD1, yD1, zD1},{xD2, yD2, zD2}}
  Eigen::MatrixXd pD;  // リンク長さ[m]，(l1, l2)

  void init(void);
  void load(void);
  void send_command_sim(void);
  void send_command_real(void);


  void read_state(const sensor_msgs::JointState::ConstPtr&);
  void FL_read_state(const sensor_msgs::JointState::ConstPtr&);
  void FR_read_state(const sensor_msgs::JointState::ConstPtr&);
  void BL_read_state(const sensor_msgs::JointState::ConstPtr&);
  void BR_read_state(const sensor_msgs::JointState::ConstPtr&);
  void read_imu(const sensor_msgs::Imu::ConstPtr&);
  void loop(const ros::TimerEvent&);

protected:
  static constexpr double controller_frequency = 300.0;  // loop frequency [Hz]
  ros::NodeHandle nh;
  ros::NodeHandle pnh;
  ros::Timer      timer;

  // To change PD gain of joints
  dynamic_reconfigure::Client<MELEW3_control::joint_pd_gainConfig> gain_client;
  MELEW3_control::joint_pd_gainConfig                              gain_config;

  // Manipulate Variables
  Eigen::Quaterniond                   imu_quaternion;              // IMUのクォータニオン情報
  Eigen::Vector3d                      imu_euler;                   // IMUのオイラー角情報
  double                               left_migration_length_ref;   // 左車輪の目標走行距離
  double                               right_migration_length_ref;  // 右車輪の目標走行距離
  cnoid::Interpolator<Eigen::Vector3d> leg_Interpolator;

  bool initialize_flag;
  int  phase = 0;

  void start_timer(void);
  void stop_timer(void);
  void start_controller(void);
  void stop_controller(void);

  // Move to desired position
  // (if arguments are not set, default position is selected)
  double default_moving_time = 1.0;
  bool   pose_transition(void);
  bool   pose_transition(const std::vector<Eigen::Vector3d>& leg_pos, const std::vector<double>& leg_yaw,
                         Eigen::Vector3d& COM_pos, const double& COM_yaw, const double& move_time);
  void   wheel_vel_limit(const double&, const double&, double&);
  void   wheel_control(const double&, const double&, Eigen::VectorXd&);
  void   change_PD_gain(uint8_t, double, double);

  double dt = 1.0 / controller_frequency;  // 1ステップあたりの時間
  double wheel_diameter_ = 0.136;          //!< 車輪径[m]
  double FL_leg_offset_x_ = 0.25;          //!< ベースリンク→左前股関節のx軸オフセット距離[m]
  double FL_leg_offset_y_ = 0.20;          //!< ベースリンク→左前股関節のy軸オフセット距離[m]
  double FL_leg_offset_z_ = 0.0;           //!< ベースリンク→左前股関節のz軸オフセット距離[m]
  double FR_leg_offset_x_ = 0.25;          //!< ベースリンク→右前股関節のx軸オフセット距離[m]
  double FR_leg_offset_y_ = -0.20;         //!< ベースリンク→右前股関節のy軸オフセット距離[m]
  double FR_leg_offset_z_ = 0.0;           //!< ベースリンク→右後股関節のz軸オフセット距離[m]
  double BL_leg_offset_x_ = -0.25;         //!< ベースリンク→左後股関節のx軸オフセット距離[m]
  double BL_leg_offset_y_ = 0.20;          //!< ベースリンク→左後股関節のy軸オフセット距離[m]
  double BL_leg_offset_z_ = 0.0;           //!< ベースリンク→左後股関節のz軸オフセット距離[m]
  double BR_leg_offset_x_ = -0.25;         //!< ベースリンク→右後股関節のx軸オフセット距離[m]
  double BR_leg_offset_y_ = -0.20;         //!< ベースリンク→右後股関節のy軸オフセット距離[m]
  double BR_leg_offset_z_ = 0.0;           //!< ベースリンク→右後股関節のz軸オフセット距離[m]


  double start_time1 = 2.0;
  double end_time1 = 4.0;
  double climb_time = 4.2;
  double climb_end = 34.0;
  const double settingTime = 2.0;     // 動作開始姿勢への遷移時間[s]
  const double movingTime = 35.0;     // 動作時間[s]
  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

  /*** 必要な変数の定義 ***/
  std::vector<Eigen::Vector3d> leg_pos_ref;      //!< 目標脚先位置
  std::vector<Eigen::Vector3d> leg_pos_ref_pre;  //!< 目標脚先位置
  Eigen::Vector3d              COM_pos_ref;      //!< 目標重心位置
  std::vector<Eigen::Vector3d> leg_pos_cmd;      //!< 目標脚先相対位置
  std::vector<double>          leg_yaw_ref;      //!< 目標脚先操舵角
  double                       COM_yaw_ref;      //!< 目標重心操舵角
  //--------
  double                       COM_pitch_ref=0.0;      //!< 目標重心操舵角
  //--------
  std::vector<Eigen::VectorXf> leg_motor_vel;
  std::vector<Eigen::VectorXf> leg_motor_torque;
  Eigen::VectorXf              wheel_motor_vel;
  Eigen::VectorXf              wheel_motor_torque;

  std::vector<double>          leg_yaw_cmd;               //!< 目標脚先相対操舵角
  std::vector<double>          migration_length_cmd;      //!< 目標車輪走行距離
  std::vector<double>          migration_length_cmd_pre;  //!< 目標車輪走行距離
  std::vector<Eigen::VectorXd> leg_angle_cmd;             //!< 目標脚部モータ角度
  std::vector<Eigen::VectorXd> leg_angle_cmd_pre;         //!< pre?目標脚部モータ角度
  Eigen::VectorXd              joint_num;
  Eigen::VectorXf              joint_numf;
  std::vector<double>          wheel_pos_cmd;      //!< 目標車輪部モータ角度
  std::vector<double>          wheel_pos_cmd_pre;  //!< 目標車輪部モータ角度
  std::vector<Eigen::Vector3d> leg_offset;         //!<ベースリンク→股関節のオフセット距離[m]
  std::vector<int>             move_direction;     //!< 車輪の進行方向

  bool sim_flag;  //!< Simulationの判定フラグ
  bool ik_flag;   //!< 逆運動学の判定フラグ
  bool fl_leg_disabled_;

public:
  BaseController(void);
  ~BaseController();

  double get_time(void);
  bool   solve_FK(const Eigen::VectorXd& q, Eigen::Vector3d& left_leg_pos, Eigen::Vector3d& right_leg_pos,
                  double& left_psi, double& right_psi);
//------------
  bool   solve_IK_parallel(const std::vector<Eigen::Vector3d>& leg_pos_ref, const std::vector<double>& leg_yaw_ref,
                           Eigen::Vector3d& com_pos_ref, const double& COM_yaw_ref,  const double& COM_pitch_ref);
  bool   solve_IK_serial(const std::vector<Eigen::Vector3d>& leg_pos_ref, const std::vector<double>& leg_yaw_ref,
                         Eigen::Vector3d& com_pos_ref, const double& COM_yaw_ref,  const double& COM_pitch_ref);
//------------
  void   calc_vel(const std::vector<Eigen::VectorXd>& angle_cmd, const std::vector<Eigen::VectorXd>& angle_cmd_pre,
                  const std::vector<double>& wheel_cmd, const std::vector<double>& wheel_cmd_pre);

  // Please override this function in derived class and
  // manipulate "leg_pos_ref" vector to control MELEW3
  virtual void control_loop(void) = 0;
//-----------------
  std::vector<double> wheel_velocity_ref;
//-----------------
};

}  // namespace MELEW3_control

#endif  // MELEW3_BASECONTROLLER_H_