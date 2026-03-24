/**
 * @file    MELEW3_trajectory_generator.cpp
 * @author  Taisei Suzuki
 * @brief   4脚車輪ロボットの軌道を生成するプログラム（テスト用）
 * @version 0.1
 * @date    2023-04-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MELEW3_control/MELEW3_trajectory_generator.hpp>

/**
 * @brief コンストラクタ
 *
 * @param nh  ノードハンドル
 * @param pnh プライベートノードハンドル
 */
MELEW3TrajectoryGenerator::MELEW3TrajectoryGenerator(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param<double>("loop_rate", 1000)) {
  /*** パブリッシャ，サブスクライバの初期化 ***/
  FL_leg_pos_ref_pub_ = nh_.advertise<melew3_msgs::leg_pose>(
      pnh.param<std::string>("FL_leg_pos_ref_pub_topic_name", "/FL_leg_pos_ref"), 1);
  FR_leg_pos_ref_pub_ = nh_.advertise<melew3_msgs::leg_pose>(
      pnh.param<std::string>("FR_leg_pos_ref_pub_topic_name", "/FR_leg_pos_ref"), 1);
  BL_leg_pos_ref_pub_ = nh_.advertise<melew3_msgs::leg_pose>(
      pnh.param<std::string>("BL_leg_pos_ref_pub_topic_name", "/BL_leg_pos_ref"), 1);
  BR_leg_pos_ref_pub_ = nh_.advertise<melew3_msgs::leg_pose>(
      pnh.param<std::string>("BR_leg_pos_ref_pub_topic_name", "/BR_leg_pos_ref"), 1);
  COM_pos_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("COM_pos_ref_pub_topic_name", "/COM_pos_ref"), 1);

  /*** メンバ変数の初期化 ***/
  ros::Time start_time = ros::Time::now();
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

  FL_leg_pos_ref_pre << FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_;
  FR_leg_pos_ref_pre << FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_;
  BL_leg_pos_ref_pre << BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_;
  BR_leg_pos_ref_pre << BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_;
  COM_pos_ref_pre << 0.0, 0.0, 0.34641016;
}

/**
 * @brief 4脚車輪ロボットの軌道をパブリッシュする関数
 *
 */
void MELEW3TrajectoryGenerator::MELEW3TrajectoryGeneratorCallback() {
  double time = (ros::Time::now() - start_time).toSec();

  /*** 脚先軌道と重心軌道を設定 ***/
  if (time < 10.0) {
    FL_leg_pos_ref = Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
    FR_leg_pos_ref = Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
    BL_leg_pos_ref = Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
    BR_leg_pos_ref = Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);
    FL_leg_yaw_ref = 0.0;
    FR_leg_yaw_ref = 0.0;
    BL_leg_yaw_ref = 0.0;
    BR_leg_yaw_ref = 0.0;

    COM_pos_ref = Eigen::Vector3d(0.0, 0.0, 0.41441016);
    COM_yaw_ref = 0.0;
  } else {
    FL_leg_pos_ref = Eigen::Vector3d(0.0 * (time - 10.0), 0.0, 0.0) +
                     Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
    FR_leg_pos_ref = Eigen::Vector3d(0.0 * (time - 10.0), 0.0, 0.0) +
                     Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
    BL_leg_pos_ref = Eigen::Vector3d(0.0 * (time - 10.0), 0.0, 0.0) +
                     Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
    BR_leg_pos_ref = Eigen::Vector3d(0.0 * (time - 10.0), 0.0, 0.0) +
                     Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);
    FL_leg_yaw_ref = 0.0;
    FR_leg_yaw_ref = 0.0;
    BL_leg_yaw_ref = 0.0;
    BR_leg_yaw_ref = 0.0;

    COM_pos_ref = Eigen::Vector3d(0.0 * (time - 10.0), 0.0, 0.0) + Eigen::Vector3d(0.0, 0.0, 0.41441016) +
                  Eigen::Vector3d(0.0, 0.0, 0.04 * sin(M_PI * time));
    COM_yaw_ref = 0.0;

    /*
    const double xy_frequency = 0.50;  // xy方向の円運動の周波数[Hz]
    const double z_frequency = 0.20;   // z方向の単振動の周波数[Hz]
    const double amplitude = 0.09;     // 振幅[m]

    FL_leg_pos_ref =
        Eigen::Vector3d(amplitude * sin(2 * M_PI * z_frequency * time) * cos(2 * M_PI * xy_frequency * time),
                        amplitude * sin(2 * M_PI * z_frequency * time) * sin(2 * M_PI * xy_frequency * time),
                        amplitude * (1 - cos(2 * M_PI * z_frequency * time))) +
        Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
    FR_leg_pos_ref =
        Eigen::Vector3d(amplitude * sin(2 * M_PI * z_frequency * time) * cos(2 * M_PI * xy_frequency * time),
                        amplitude * sin(2 * M_PI * z_frequency * time) * sin(2 * M_PI * xy_frequency * time),
                        amplitude * (1 - cos(2 * M_PI * z_frequency * time))) +
        Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
    BL_leg_pos_ref =
        Eigen::Vector3d(amplitude * sin(2 * M_PI * z_frequency * time) * cos(2 * M_PI * xy_frequency * time),
                        amplitude * sin(2 * M_PI * z_frequency * time) * sin(2 * M_PI * xy_frequency * time),
                        amplitude * (1 - cos(2 * M_PI * z_frequency * time))) +
        Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
    BR_leg_pos_ref =
        Eigen::Vector3d(amplitude * sin(2 * M_PI * z_frequency * time) * cos(2 * M_PI * xy_frequency * time),
                        amplitude * sin(2 * M_PI * z_frequency * time) * sin(2 * M_PI * xy_frequency * time),
                        amplitude * (1 - cos(2 * M_PI * z_frequency * time))) +
        Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);
    FL_leg_yaw_ref = 0.0;
    FR_leg_yaw_ref = 0.0;
    BL_leg_yaw_ref = 0.0;
    BR_leg_yaw_ref = 0.0;

    COM_pos_ref = Eigen::Vector3d(0.0, 0.0, 0.41441016);
    COM_yaw_ref = 0.0;
    */
  }
  /*** 1個前の目標脚先位置と目標重心位置の保存 ***/
  FL_leg_pos_ref_pre = FL_leg_pos_ref;
  FR_leg_pos_ref_pre = FR_leg_pos_ref;
  BL_leg_pos_ref_pre = BL_leg_pos_ref;
  BR_leg_pos_ref_pre = BR_leg_pos_ref;
  COM_pos_ref_pre = COM_pos_ref;

  /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
  if (sim_flag_) {
    melew3_msgs::leg_pose pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
        pub_COM_pos_ref;

    util.Vector3dToLegpose(FL_leg_pos_ref, FL_leg_yaw_ref, pub_FL_leg_pos_ref);
    util.Vector3dToLegpose(FR_leg_pos_ref, FR_leg_yaw_ref, pub_FR_leg_pos_ref);
    util.Vector3dToLegpose(BL_leg_pos_ref, BL_leg_yaw_ref, pub_BL_leg_pos_ref);
    util.Vector3dToLegpose(BR_leg_pos_ref, BR_leg_yaw_ref, pub_BR_leg_pos_ref);
    util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);

    FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
    FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
    BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
    BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
    COM_pos_ref_pub_.publish(pub_COM_pos_ref);
  } else {
    ROS_ERROR("sim_flag is not true !");
  }
}

/**
 * @brief  4脚車輪ロボットの軌道を生成するプログラムを回す関数
 *
 */
void MELEW3TrajectoryGenerator::Run() {
  while (nh_.ok()) {
    MELEW3TrajectoryGeneratorCallback();
    ros::spinOnce();
    rate_.sleep();
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "MELEW3TrajectoryGeneratorNode");
  ros::NodeHandle            nh;
  ros::NodeHandle            pnh("~");
  MELEW3TrajectoryGenerator MELEW3TrajectoryGenerator(nh, pnh);
  MELEW3TrajectoryGenerator.Run();
  return 0;
}