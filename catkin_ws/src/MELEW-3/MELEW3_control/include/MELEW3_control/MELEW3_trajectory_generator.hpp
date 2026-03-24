/**
 * @file    MELEW3_trajectory_generator.hpp
 * @author  Taisei Suzuki
 * @brief   4脚車輪ロボットの軌道を生成するプログラムのヘッダ（テスト用）
 * @version 0.1
 * @date    2023-04-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <melew3_msgs/leg_pose.h>
#include <ros/ros.h>

#include <Eigen/Core>

#include "utils.hpp"

/**
 * @brief 4脚車輪ロボットの軌道を生成するクラス
 *
 */
class MELEW3TrajectoryGenerator {
public:
  MELEW3TrajectoryGenerator(ros::NodeHandle nh, ros::NodeHandle pnh);

  void MELEW3TrajectoryGeneratorCallback();
  void Run();

private:
  /*** ROS関連 ***/
  ros::NodeHandle nh_;    //!< NodeHandle
  ros::Rate       rate_;  //!< 制御周期

  ros::Publisher FL_leg_pos_ref_pub_;  //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;  //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;  //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;  //!< 右後脚の目標脚先位置用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;     //!< 目標重心位置用パブリッシャー

  /*** メッセージ関連 ***/
  Eigen::Vector3d FL_leg_pos_ref;  //!< 左前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d FR_leg_pos_ref;  //!< 右前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d BL_leg_pos_ref;  //!< 左前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d BR_leg_pos_ref;  //!< 右前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d COM_pos_ref;     //!< 目標重心位置を一時保存する変数

  Eigen::Vector3d FL_leg_pos_ref_pre;  //!< 左前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d FR_leg_pos_ref_pre;  //!< 右前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d BL_leg_pos_ref_pre;  //!< 左前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d BR_leg_pos_ref_pre;  //!< 右前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d COM_pos_ref_pre;     //!< 1個前の目標重心位置を一時保存する変数

  double FL_leg_yaw_ref;  //!< 左前脚の目標Yaw角位置を一時保存する変数
  double FR_leg_yaw_ref;  //!< 右前脚の目標Yaw角位置を一時保存する変数
  double BL_leg_yaw_ref;  //!< 左後脚の目標Yaw角位置を一時保存する変数
  double BR_leg_yaw_ref;  //!< 右後脚の目標Yaw角位置を一時保存する変数
  double COM_yaw_ref;     //!< 重心の目標Yaw角位置を一時保存する変数

  /*** 変数関連 ***/
  ros::Time start_time;        //!< 開始時刻を保存する変数
  bool      sim_flag_;         //!< シミュレーションか否か
  double    wheel_diameter_;   //!< 車輪径[m]
  double    FL_leg_offset_x_;  //!< ベースリンク→左前股関節のx軸オフセット距離[m]
  double    FL_leg_offset_y_;  //!< ベースリンク→左前股関節のy軸オフセット距離[m]
  double    FL_leg_offset_z_;  //!< ベースリンク→左前股関節のz軸オフセット距離[m]
  double    FR_leg_offset_x_;  //!< ベースリンク→右前股関節のx軸オフセット距離[m]
  double    FR_leg_offset_y_;  //!< ベースリンク→右前股関節のy軸オフセット距離[m]
  double    FR_leg_offset_z_;  //!< ベースリンク→右後股関節のz軸オフセット距離[m]
  double    BL_leg_offset_x_;  //!< ベースリンク→左後股関節のx軸オフセット距離[m]
  double    BL_leg_offset_y_;  //!< ベースリンク→左後股関節のy軸オフセット距離[m]
  double    BL_leg_offset_z_;  //!< ベースリンク→左後股関節のz軸オフセット距離[m]
  double    BR_leg_offset_x_;  //!< ベースリンク→右後股関節のx軸オフセット距離[m]
  double    BR_leg_offset_y_;  //!< ベースリンク→右後股関節のy軸オフセット距離[m]
  double    BR_leg_offset_z_;  //!< ベースリンク→右後股関節のz軸オフセット距離[m]

  /*** util関連 ***/
  Utils::Utils util;
};