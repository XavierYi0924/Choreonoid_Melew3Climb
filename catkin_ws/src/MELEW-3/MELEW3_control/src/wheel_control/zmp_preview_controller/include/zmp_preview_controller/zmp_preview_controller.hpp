/**
 * @file    preview_control.hpp
 * @author  Yuta Ishizawa
 * @brief   予見制御を行うプログラムファイルのヘッダ
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <geometry_msgs/PointStamped.h>
#include <melew3_msgs/leg_pose.h>
#include <melew3_msgs/waypoint.h>
#include <ros/ros.h>

#include <Eigen/Core>
#include <MELEW3_control/utils.hpp>
#include <fstream>
#include <zmp_generator/zmp_generator.hpp>

#include "pattern_generator.hpp"

/**
 * @brief 予見制御クラス
 *
 */
class PreviewControl {
public:
  PreviewControl(ros::NodeHandle nh, ros::NodeHandle pnh);
  bool   PreviewControlCallback(const double control_time);
  void   Run();
  double GetStopControlTime() { return stop_control_time_; }

  /*** 軌道データ ***/
  std::vector<Eigen::Vector3d> zmp_pos_traj_;      //!< 目標ZMP軌道
  std::vector<Eigen::Vector3d> zmp_vel_traj_;      //!< 目標ZMP速度軌道
  std::vector<Eigen::Vector3d> zmp_acc_traj_;      //!< 目標ZMP加速度軌道
  std::vector<Eigen::Vector3d> com_pos_traj_;      //!< 目標重心軌道
  std::vector<Eigen::Vector3d> com_vel_traj_;      //!< 目標重心速度軌道
  std::vector<Eigen::Vector3d> com_acc_traj_;      //!< 目標重心加速度軌道
  std::vector<double>          com_yaw_pos_traj_;  //!< 目標重心操舵角軌道
  std::vector<double>          com_yaw_vel_traj_;  //!< 目標重心操舵角速度軌道
  std::vector<double>          com_yaw_acc_traj_;  //!< 目標重心操舵角加速度軌道
  std::vector<double>          waypoint_time;

  int how_many_times_ = 0;  //!< 制御回数

private:
  void Init();
  void CalcDifferential(const double control_period, const std::vector<Eigen::Vector3d> position,
                        std::vector<Eigen::Vector3d>& velocity, std::vector<Eigen::Vector3d>& acceleration);
  void CalcZmpTrajectory(std::vector<Utils::Five_Spline::point3> zmp_point_data,
                         std::vector<Utils::Five_Spline::point>  zmp_yaw_point_data);
  void CalcPreviewControl(const bool last_flag);
  void PreviewControlPublisher(const double control_time);

  /*** ROS関連 ***/
  ros::NodeHandle nh_;               //!< NodeHandle
  ros::Rate       rate_;             //!< 制御周期
  ros::Publisher  zmp_pos_ref_pub_;  //!< 目標ZMP位置のパブリッシャー
  ros::Publisher  zmp_vel_ref_pub_;  //!< 目標ZMP速度のパブリッシャー
  ros::Publisher  zmp_acc_ref_pub_;  //!< 目標ZMP加速度のパブリッシャー
  ros::Publisher  com_pos_ref_pub_;  //!< 目標重心位置のパブリッシャー
  ros::Publisher  com_vel_ref_pub_;  //!< 目標重心速度のパブリッシャー
  ros::Publisher  com_acc_ref_pub_;  //!< 目標重心加速度のパブリッシャー

  /*** メッセージ関連 ***/
  melew3_msgs::waypoint       waypoint_ref_;          //!< 目標経由点を一時保存する変数
  melew3_msgs::leg_pose       pub_zmp_pos_ref_data_;  //!< 目標ZMP位置を一時保存する変数
  geometry_msgs::PointStamped pub_zmp_vel_ref_data_;  //!< 目標ZMP速度を一時保存する変数
  geometry_msgs::PointStamped pub_zmp_acc_ref_data_;  //!< 目標ZMP加速度を一時保存する変数
  melew3_msgs::leg_pose       pub_com_pos_ref_data_;  //!< 目標CoM位置を一時保存する変数
  melew3_msgs::leg_pose       pub_com_vel_ref_data_;  //!< 目標CoM速度を一時保存する変数
  melew3_msgs::leg_pose       pub_com_acc_ref_data_;  //!< 目標CoM加速度を一時保存する変数

  /*** 変数関連 ***/
  double loop_rate_;       //!< 制御周波数[Hz]
  double control_period_;  //!< 制御周期[s]
  double sampling_time_;   //!< 予見制御のサンプリングタイム[s]
  double leg_rotate_time_;
  double control_time_;         //!< 制御時刻[s]
  double initial_time_;         //!< 起動時刻[s]
  double start_control_time_;   //!< 制御開始時刻[s]
  double stop_control_time_;    //!< 制御終了時刻[s]
  double max_calculated_time_;  //!< 目標軌道の計算が完了した時刻の最大値[s]

  double com_height_;  //!< 重心高さ[m]
  double Qe_;          //!< 予見制御で使うパラメータQe
  double Ru_;          //!< 予見制御で使うパラメータRu

  /*** util関連のクラスの初期化 ***/
  Utils::Utils       util;
  Utils::Five_Spline five_spline_zmp;

  /*** 経由点情報 ***/
  std::vector<Utils::Five_Spline::point3> waypoint_position;  // (zmp.x(), zmp.y(), com_height)
  std::vector<Utils::Five_Spline::point>  waypoint_yaw;       // (com.yaw())

  /*** 予見制御による重心軌道生成器のクラスの初期化 ***/
  PatternGenerator pg;

  ZmpGenerator zg;
};