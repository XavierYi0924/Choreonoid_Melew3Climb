/**
 * @file    MELEW3_ik_calculator.cpp
 * @author  Taisei Suzuki
 * @brief   逆運動学計算するプログラム
 * @version 0.1
 * @date    2023-04-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MELEW3_control/MELEW3_ik_calculator.hpp>

/**
 * @brief コンストラクタ
 *
 * @param nh  ノードハンドル
 * @param pnh プライベートノードハンドル
 */
MELEW3IKCalculator::MELEW3IKCalculator(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param<double>("loop_rate", 100)) {
  /*** パブリッシャ，サブスクライバの初期化 ***/
  FL_leg_pos_ref_sub_ = nh_.subscribe(pnh.param<std::string>("FL_leg_pos_ref_topic_name", "/FL_leg_pos_ref"), 1,
                                      &MELEW3IKCalculator::_FLLegPosRefCallback, this);
  FR_leg_pos_ref_sub_ = nh_.subscribe(pnh.param<std::string>("FR_leg_pos_ref_topic_name", "/FR_leg_pos_ref"), 1,
                                      &MELEW3IKCalculator::_FRLegPosRefCallback, this);
  BL_leg_pos_ref_sub_ = nh_.subscribe(pnh.param<std::string>("BL_leg_pos_ref_topic_name", "/BL_leg_pos_ref"), 1,
                                      &MELEW3IKCalculator::_BLLegPosRefCallback, this);
  BR_leg_pos_ref_sub_ = nh_.subscribe(pnh.param<std::string>("BR_leg_pos_ref_topic_name", "/BR_leg_pos_ref"), 1,
                                      &MELEW3IKCalculator::_BRLegPosRefCallback, this);
  COM_pos_ref_sub_ = nh_.subscribe(pnh.param<std::string>("COM_pos_ref_topic_name", "/COM_pos_ref"), 1,
                                   &MELEW3IKCalculator::_COMPosRefCallback, this);

  leg_FL_position_controller_pub_ = nh_.advertise<std_msgs::Float64MultiArray>(
      pnh.param<std::string>("leg_FL_position_controller_pub_topic_name",
                             "/MELEW3/leg_FL_position_controller/command"),
      1);
  leg_FR_position_controller_pub_ = nh_.advertise<std_msgs::Float64MultiArray>(
      pnh.param<std::string>("leg_FR_position_controller_pub_topic_name",
                             "/MELEW3/leg_FR_position_controller/command"),
      1);
  leg_BL_position_controller_pub_ = nh_.advertise<std_msgs::Float64MultiArray>(
      pnh.param<std::string>("leg_BL_position_controller_pub_topic_name",
                             "/MELEW3/leg_BL_position_controller/command"),
      1);
  leg_BR_position_controller_pub_ = nh_.advertise<std_msgs::Float64MultiArray>(
      pnh.param<std::string>("leg_BR_position_controller_pub_topic_name",
                             "/MELEW3/leg_BR_position_controller/command"),
      1);
  wheel_controller_pub_ = nh_.advertise<std_msgs::Float64MultiArray>(
      pnh.param<std::string>("wheel_controller_pub_topic_name", "/MELEW3/wheel_controller/command"), 1);

  /*** 運動学クラスの初期化 ***/
  melew3Kinematics.init(0.20, 0.20, 0.20, 0.20);

  /*** メンバ変数の初期化 ***/
  pnh.param<bool>("sim_flag", sim_flag_, true);
  pnh.param<double>("wheel_diameter", wheel_diameter_, 0.136);
  pnh.param<double>("FL_leg_offset_x", FL_leg_offset_x_, 0.25);
  pnh.param<double>("FL_leg_offset_y", FL_leg_offset_y_, 0.20);
  pnh.param<double>("FL_leg_offset_z", FL_leg_offset_z_, 0.0);
  pnh.param<double>("FR_leg_offset_x", FR_leg_offset_x_, 0.25);
  pnh.param<double>("FR_leg_offset_y", FR_leg_offset_y_, -0.20);
  pnh.param<double>("FR_leg_offset_z", FR_leg_offset_z_, 0.0);
  pnh.param<double>("BL_leg_offset_x", BL_leg_offset_x_, -0.25);
  pnh.param<double>("BL_leg_offset_y", BL_leg_offset_y_, 0.20);
  pnh.param<double>("BL_leg_offset_z", BL_leg_offset_z_, 0.0);
  pnh.param<double>("BR_leg_offset_x", BR_leg_offset_x_, -0.25);
  pnh.param<double>("BR_leg_offset_y", BR_leg_offset_y_, -0.20);
  pnh.param<double>("BR_leg_offset_z", BR_leg_offset_z_, 0.0);
  leg_pos_ref_pre.resize(LEG_NUM);
  migration_length_cmd_pre.resize(LEG_NUM);
  leg_offset.resize(LEG_NUM);
  leg_offset[FL] = Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
  leg_offset[FR] = Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
  leg_offset[BL] = Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
  leg_offset[BR] = Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);
  leg_pos_ref_pre = leg_offset;
}

/**
 * @brief 逆運動学計算したものをパブリッシュする関数
 *
 * @param FL_leg_pos_ref_ 左前脚の目標脚先位置[m]
 * @param FR_leg_pos_ref_ 右前脚の目標脚先位置[m]
 * @param BL_leg_pos_ref_ 左後脚の目標脚先位置[m]
 * @param BR_leg_pos_ref_ 右後脚の目標脚先位置[m]
 * @param COM_pos_ref_    目標重心位置[m]
 */
void MELEW3IKCalculator::MELEW3IKCalculatorCallback(const melew3_msgs::leg_pose FL_leg_pos_ref_,
                                                      const melew3_msgs::leg_pose FR_leg_pos_ref_,
                                                      const melew3_msgs::leg_pose BL_leg_pos_ref_,
                                                      const melew3_msgs::leg_pose BR_leg_pos_ref_,
                                                      const melew3_msgs::leg_pose COM_pos_ref_) {
  /*** 必要な変数の定義 ***/
  std::vector<Eigen::Vector3d> leg_pos_ref(LEG_NUM);           //!< 目標脚先位置
  Eigen::Vector3d              COM_pos_ref;                    //!< 目標重心位置
  std::vector<Eigen::Vector3d> leg_pos_cmd(LEG_NUM);           //!< 目標脚先相対位置
  std::vector<double>          leg_yaw_ref(LEG_NUM);           //!< 目標脚先操舵角
  double                       COM_yaw_ref;                    //!< 目標重心操舵角
  std::vector<double>          leg_yaw_cmd(LEG_NUM);           //!< 目標脚先相対操舵角
  std::vector<int>             move_direction(LEG_NUM);        //!< 車輪の進行方向
  std::vector<double>          migration_length_cmd(LEG_NUM);  //!< 目標車輪走行距離
  std::vector<Eigen::VectorXd> leg_angle_cmd(LEG_NUM,
                                             Eigen::VectorXd((int)SINGLE_LEG_JOINT_NUM));  //!< 目標脚部モータ角度
  std::vector<double>          wheel_pos_cmd(LEG_NUM);  //!< 目標車輪部モータ角度

  double dx, dz;   //!< 目標脚先位置の移動量
  bool   ik_flag;  //!< 逆運動学の判定フラグ

  /*** Point型をVector型に変換 ***/
  util.LegposeToVector3d(FL_leg_pos_ref_, leg_pos_ref[FL], leg_yaw_ref[FL]);
  util.LegposeToVector3d(FR_leg_pos_ref_, leg_pos_ref[FR], leg_yaw_ref[FR]);
  util.LegposeToVector3d(BL_leg_pos_ref_, leg_pos_ref[BL], leg_yaw_ref[BL]);
  util.LegposeToVector3d(BR_leg_pos_ref_, leg_pos_ref[BR], leg_yaw_ref[BR]);
  util.LegposeToVector3d(COM_pos_ref_, COM_pos_ref, COM_yaw_ref);

  if (leg_pos_ref[FL].x() || leg_pos_ref[FR].x() || leg_pos_ref[BL].x() || leg_pos_ref[BR].x()) {
    ik_flag = true;
    for (int i = 0; i < LEG_NUM; i++) {
      /*** 脚先の相対位置を計算 ***/
      leg_pos_cmd[i] =
          (leg_pos_ref[i] - COM_pos_ref) +
          melew3Kinematics.RotZ(COM_yaw_ref) * (-leg_offset[i] + Eigen::Vector3d(0.0, 0.0, wheel_diameter_ / 2.0));

      leg_yaw_cmd[i] = leg_yaw_ref[i] - COM_yaw_ref;

      move_direction[i] = ((leg_pos_ref[i] - leg_pos_ref_pre[i]).x() > 0.0) -
                          ((leg_pos_ref[i] - leg_pos_ref_pre[i]).x() < 0.0);  // 車輪の進行方向を設定

      /*** 逆運動学計算（実機の場合はserialをparallelに変更するのを忘れずに） ***/
      ik_flag *= melew3Kinematics.solve_IK_serial(i, leg_pos_cmd[i], leg_yaw_cmd[i], leg_angle_cmd[i]);
    }

    if (ik_flag) {
      for (int i = 0; i < LEG_NUM; i++) {
        /*** 車輪走行距離の計算（後で変更するかも）***/
        migration_length_cmd[i] =
            (double)move_direction[i] * (leg_pos_ref[i] - leg_pos_ref_pre[i]).norm() + migration_length_cmd_pre[i];

        /*** 車輪の目標関節角の計算（後で変更するかも）***/
        wheel_pos_cmd[i] =
            migration_length_cmd[i] / (wheel_diameter_ / 2.0) - (leg_angle_cmd[i][HIP_PITCH] + leg_angle_cmd[i][KNEE]);
      }

      /*** 1個前の目標脚先位置と目標車輪位置の保存 ***/
      leg_pos_ref_pre = leg_pos_ref;
      migration_length_cmd_pre = migration_length_cmd;

      /*** 逆運動学計算したものをパブリッシュ ***/
      if (sim_flag_) {
        std_msgs::Float64MultiArray pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
            pub_wheel_pos_cmd;
        pub_FL_leg_pos_ref.data.resize(SINGLE_LEG_JOINT_NUM);
        pub_FR_leg_pos_ref.data.resize(SINGLE_LEG_JOINT_NUM);
        pub_BL_leg_pos_ref.data.resize(SINGLE_LEG_JOINT_NUM);
        pub_BR_leg_pos_ref.data.resize(SINGLE_LEG_JOINT_NUM);
        pub_wheel_pos_cmd.data.resize(SINGLE_LEG_JOINT_NUM);

        for (int i = 0; i < SINGLE_LEG_JOINT_NUM; i++) {
          pub_FL_leg_pos_ref.data[i] = leg_angle_cmd[FL][i];
          pub_FR_leg_pos_ref.data[i] = leg_angle_cmd[FR][i];
          pub_BL_leg_pos_ref.data[i] = leg_angle_cmd[BL][i];
          pub_BR_leg_pos_ref.data[i] = leg_angle_cmd[BR][i];
          pub_wheel_pos_cmd.data[i] = wheel_pos_cmd[i];
        }

        leg_FL_position_controller_pub_.publish(pub_FL_leg_pos_ref);
        leg_FR_position_controller_pub_.publish(pub_FR_leg_pos_ref);
        leg_BL_position_controller_pub_.publish(pub_BL_leg_pos_ref);
        leg_BR_position_controller_pub_.publish(pub_BR_leg_pos_ref);
        wheel_controller_pub_.publish(pub_wheel_pos_cmd);
      } else {
        ROS_ERROR("sim_flag is not true !");
      }
    }
  }
}

/**
 * @brief  逆運動学計算を回す関数
 *
 */
void MELEW3IKCalculator::Run() {
  while (nh_.ok()) {
    MELEW3IKCalculatorCallback(FL_leg_pos_ref_, FR_leg_pos_ref_, BL_leg_pos_ref_, BR_leg_pos_ref_, COM_pos_ref_);
    ros::spinOnce();
    rate_.sleep();
  }
}

/**
 * @brief 左前脚目標脚先位置を一時保存するコールバック関数
 *
 * @param FL_leg_pos_ref
 */
void MELEW3IKCalculator::_FLLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& FL_leg_pos_ref) {
  FL_leg_pos_ref_.header = FL_leg_pos_ref->header;
  FL_leg_pos_ref_.point = FL_leg_pos_ref->point;
  FL_leg_pos_ref_.yaw = FL_leg_pos_ref->yaw;
}

/**
 * @brief 右前脚目標脚先位置を一時保存するコールバック関数
 *
 * @param FR_leg_pos_ref
 */
void MELEW3IKCalculator::_FRLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& FR_leg_pos_ref) {
  FR_leg_pos_ref_.header = FR_leg_pos_ref->header;
  FR_leg_pos_ref_.point = FR_leg_pos_ref->point;
  FR_leg_pos_ref_.yaw = FR_leg_pos_ref->yaw;
}

/**
 * @brief 左後脚目標脚先位置を一時保存するコールバック関数
 *
 * @param BL_leg_pos_ref
 */
void MELEW3IKCalculator::_BLLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& BL_leg_pos_ref) {
  BL_leg_pos_ref_.header = BL_leg_pos_ref->header;
  BL_leg_pos_ref_.point = BL_leg_pos_ref->point;
  BL_leg_pos_ref_.yaw = BL_leg_pos_ref->yaw;
}

/**
 * @brief 右後脚目標脚先位置を一時保存するコールバック関数
 *
 * @param BR_leg_pos_ref
 */
void MELEW3IKCalculator::_BRLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& BR_leg_pos_ref) {
  BR_leg_pos_ref_.header = BR_leg_pos_ref->header;
  BR_leg_pos_ref_.point = BR_leg_pos_ref->point;
  BR_leg_pos_ref_.yaw = BR_leg_pos_ref->yaw;
}

/**
 * @brief 目標重心位置を一時保存するコールバック関数
 *
 * @param COM_pos_ref
 */
void MELEW3IKCalculator::_COMPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& COM_pos_ref) {
  COM_pos_ref_.header = COM_pos_ref->header;
  COM_pos_ref_.point = COM_pos_ref->point;
  COM_pos_ref_.yaw = COM_pos_ref->yaw;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "MELEW3IKCalculatorNode");
  ros::NodeHandle     nh;
  ros::NodeHandle     pnh("~");
  MELEW3IKCalculator MELEW3IKCalculator(nh, pnh);
  MELEW3IKCalculator.Run();
  return 0;
}