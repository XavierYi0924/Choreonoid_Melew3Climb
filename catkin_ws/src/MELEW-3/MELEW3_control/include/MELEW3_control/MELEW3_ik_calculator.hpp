/**
 * @file    MELEW3_ik_calculator.hpp
 * @author  Taisei Suzuki
 * @brief   逆運動学計算するプログラムのヘッダ
 * @version 0.1
 * @date    2023-04-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <melew3_msgs/leg_pose.h>
#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>

#include <Eigen/Core>
#include <MELEW3_control/param.hpp>
#include <MELEW3_control/utils.hpp>

#include "../src/MELEW3_kinematics/MELEW3_Kinematics.h"

/**
 * @brief 逆運動学を解くクラス
 *
 */
class MELEW3IKCalculator {
public:
  MELEW3IKCalculator(ros::NodeHandle nh, ros::NodeHandle pnh);

  void MELEW3IKCalculatorCallback(const melew3_msgs::leg_pose FL_leg_pos_ref_,
                                   const melew3_msgs::leg_pose FR_leg_pos_ref_,
                                   const melew3_msgs::leg_pose BL_leg_pos_ref_,
                                   const melew3_msgs::leg_pose BR_leg_pos_ref_,
                                   const melew3_msgs::leg_pose COM_pos_ref_);
  void Run();

private:
  void _FLLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& FL_leg_pos_ref);
  void _FRLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& FR_leg_pos_ref);
  void _BLLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& BL_leg_pos_ref);
  void _BRLegPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& BR_leg_pos_ref);
  void _COMPosRefCallback(const melew3_msgs::leg_pose::ConstPtr& COM_pos_ref);

  /*** ROS関連 ***/
  ros::NodeHandle nh_;                  //!< NodeHandle
  ros::Rate       rate_;                //!< 制御周期
  ros::Subscriber FL_leg_pos_ref_sub_;  //!< 左前脚の目標脚先位置用サブスクライバー
  ros::Subscriber FR_leg_pos_ref_sub_;  //!< 右前脚の目標脚先位置用サブスクライバー
  ros::Subscriber BL_leg_pos_ref_sub_;  //!< 左後脚の目標脚先位置用サブスクライバー
  ros::Subscriber BR_leg_pos_ref_sub_;  //!< 右後脚の目標脚先位置用サブスクライバー
  ros::Subscriber COM_pos_ref_sub_;     //!< 目標重心位置用サブスクライバー

  ros::Publisher leg_FL_position_controller_pub_;  //!< 左前脚モータ用パブリッシャー
  ros::Publisher leg_FR_position_controller_pub_;  //!< 右前脚モータ用パブリッシャー
  ros::Publisher leg_BL_position_controller_pub_;  //!< 左後脚モータ用パブリッシャー
  ros::Publisher leg_BR_position_controller_pub_;  //!< 右後脚モータ用パブリッシャー
  ros::Publisher wheel_controller_pub_;            //!< 車輪モータ用パブリッシャー

  /*** メッセージ関連 ***/
  melew3_msgs::leg_pose FL_leg_pos_ref_;  //!< 左前脚の目標脚先位置を一時保存する変数
  melew3_msgs::leg_pose FR_leg_pos_ref_;  //!< 右前脚の目標脚先位置を一時保存する変数
  melew3_msgs::leg_pose BL_leg_pos_ref_;  //!< 左前脚の目標脚先位置を一時保存する変数
  melew3_msgs::leg_pose BR_leg_pos_ref_;  //!< 右前脚の目標脚先位置を一時保存する変数
  melew3_msgs::leg_pose COM_pos_ref_;     //!< 目標重心位置を一時保存する変数

  std::vector<Eigen::Vector3d> leg_pos_ref_pre;  //!< 脚の1個前の目標脚先位置を一時保存する変数
  std::vector<double>          leg_yaw_ref_pre;  //!< 脚の1個前の目標脚先位置を一時保存する変数
  std::vector<double> migration_length_cmd_pre;  //!< 1個前の目標車輪走行距離を一時保存する変数

  /*** 変数関連 ***/
  bool   sim_flag_;                         //!< シミュレーションか否か
  double wheel_diameter_;                   //!< 車輪径[m]
  double FL_leg_offset_x_;                  //!< ベースリンク→左前股関節のx軸オフセット距離[m]
  double FL_leg_offset_y_;                  //!< ベースリンク→左前股関節のy軸オフセット距離[m]
  double FL_leg_offset_z_;                  //!< ベースリンク→左前股関節のz軸オフセット距離[m]
  double FR_leg_offset_x_;                  //!< ベースリンク→右前股関節のx軸オフセット距離[m]
  double FR_leg_offset_y_;                  //!< ベースリンク→右前股関節のy軸オフセット距離[m]
  double FR_leg_offset_z_;                  //!< ベースリンク→右後股関節のz軸オフセット距離[m]
  double BL_leg_offset_x_;                  //!< ベースリンク→左後股関節のx軸オフセット距離[m]
  double BL_leg_offset_y_;                  //!< ベースリンク→左後股関節のy軸オフセット距離[m]
  double BL_leg_offset_z_;                  //!< ベースリンク→左後股関節のz軸オフセット距離[m]
  double BR_leg_offset_x_;                  //!< ベースリンク→右後股関節のx軸オフセット距離[m]
  double BR_leg_offset_y_;                  //!< ベースリンク→右後股関節のy軸オフセット距離[m]
  double BR_leg_offset_z_;                  //!< ベースリンク→右後股関節のz軸オフセット距離[m]
  std::vector<Eigen::Vector3d> leg_offset;  //!<ベースリンク→股関節のオフセット距離[m]

  /*** 運動学関連 ***/
  melew3_kinematics::MELEW3_Kinematics melew3Kinematics;

  /*** util関連 ***/
  Utils::Utils util;
};