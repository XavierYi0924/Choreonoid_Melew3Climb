/**
 * @file    zmp_generator.hpp
 * @author  Taisei Suzuki
 * @brief   目標経由点を生成するプログラムファイルのヘッダ
 * @version 0.1
 * @date    2023-05-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <melew3_msgs/waypoint.h>
#include <ros/ros.h>

#include <Eigen/Core>
#include <MELEW3_control/utils.hpp>

/**
 * @brief 目標経由点を生成するクラス
 *
 */
class ZmpGenerator {
public:
  ZmpGenerator(ros::NodeHandle nh, ros::NodeHandle pnh);
  void ZmpGeneratorCallback(const double control_time);
  void Run();

  /*** 経由点情報 ***/
  std::vector<Utils::Five_Spline::point3> zmp_ref;
  std::vector<Utils::Five_Spline::point>  com_yaw_ref;

private:
  /*** ROS関連 ***/
  ros::NodeHandle nh_;      //!< NodeHandle
  ros::Rate       rate_;    //!< 制御周期（デフォルトでは100Hz）
  ros::Time       t_start;  //!< 開始時刻用のタイマー

  /*** パブリッシャー ***/
  ros::Publisher waypoint_ref_pub_;  //!< 目標ZMP位置用パブリッシャー

  /*** 変数関連 ***/
  double              control_time_;   //!< 制御時刻[s]
  double              finish_time;     //!< 終了時刻
  std::vector<double> send_time;       //!< 送信時刻
  int                 send_count = 0;  //!< 送信したデータ数
  XmlRpc::XmlRpcValue params;          //!< 目標経由点を格納する変数

  /*** util関連のクラスの初期化 ***/
  Utils::Utils       util;
  Utils::Five_Spline five_spline_zmp;
};