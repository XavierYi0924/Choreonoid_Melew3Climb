/**
 * @file    sne_controller.hpp
 * @author  Taisei Suzuki
 * @brief   SNEを用いて目標脚先軌道を生成するプログラムファイルのヘッダ
 * @version 0.1
 * @date    2023-05-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <melew3_msgs/leg_pose.h>
#include <melew3_msgs/waypoint.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include <Eigen/Dense>
#include <MELEW3_control/utils.hpp>
#include <cmath>
#include <zmp_preview_controller/zmp_preview_controller.hpp>

#include "nonlinear_equation_solver.hpp"

/**
 * @brief SNEを用いて目標脚先軌道を生成するクラス
 *
 */
class SneController {
public:
  SneController(ros::NodeHandle nh, ros::NodeHandle pnh);
  bool SneControllerCallback(const double control_time);
  void Run();

  Eigen::Vector3d              zmp_pos;
  Eigen::Vector3d              com_pos;
  double                       com_yaw;
  std::vector<Eigen::Vector3d> leg_pos;
  std::vector<double>          leg_yaw;

private:
  void Init();
  void CalcSneContour(const double SNE, const double theta, double& x, double& y);
  void CalcSupportPolygon();
  void CalcPointOfTangency(const int num);
  bool CalcMovement(const int num);
  void SneControllerPublisher();

  /*** ROS関連 ***/
  ros::NodeHandle nh_;                  //!< NodeHandle
  ros::Rate       rate_;                //!< 制御周期
  ros::Publisher  FL_leg_pos_ref_pub_;  //!< 左前脚の目標脚先軌道用パブリッシャー
  ros::Publisher  FR_leg_pos_ref_pub_;  //!< 左後脚の目標脚先軌道用パブリッシャー
  ros::Publisher  BL_leg_pos_ref_pub_;  //!< 右前脚の目標脚先軌道用パブリッシャー
  ros::Publisher  BR_leg_pos_ref_pub_;  //!< 右後脚の目標脚先軌道用パブリッシャー

  /*** メッセージ関連 ***/
  melew3_msgs::leg_pose zmp_pos_ref_;              //!< 目標ZMP軌道を一時保存する変数
  melew3_msgs::leg_pose com_pos_ref_;              //!< 目標重心軌道を一時保存する変数
  melew3_msgs::leg_pose pub_FL_leg_pos_ref_data_;  //!< 左前脚の目標脚先軌道を一時保存する変数
  melew3_msgs::leg_pose pub_FR_leg_pos_ref_data_;  //!< 左後脚の目標脚先軌道を一時保存する変数
  melew3_msgs::leg_pose pub_BL_leg_pos_ref_data_;  //!< 右前脚の目標脚先軌道を一時保存する変数
  melew3_msgs::leg_pose pub_BR_leg_pos_ref_data_;  //!< 右後脚の目標脚先軌道を一時保存する変数

  enum leg_num { FL, FR, BL, BR, LEG_NUM };  //!< 脚の番号

  double              loop_rate_;           //!< 制御周波数[Hz]
  double              sampling_time_;       //!< 予見制御のサンプリングタイム[s]
  double              start_control_time_;  //!< 制御開始時刻[s]
  std::vector<double> SNE_threshold;        //!< SNEの閾値 (x,y) [m]
  double              h;                    //!< 重心高さ [m]
  double              phi;                  //!< 斜面の傾斜角 [rad]
  double              xi;                   //!< 斜面上方向の偏角 [rad]
  double              d_leg;                //!< ロボットの長さ [m]
  double              b_leg;                //!< ロボットの幅 [m]
  double              l_limit;              //!< 脚長制限 [m]

  Eigen::Vector3d                           ZMP;                     //!< ZMP [m]
  std::vector<Eigen::Vector3d>              foot;                    //!< 目標脚先位置 [m]
  std::vector<Eigen::Vector3d>              support_porigon_vector;  //!< 支持多角形の方向ベクトル
  std::vector<std::vector<Eigen::Vector3d>> x_p;                     //!< 接点座標 (x,y) [m]
  std::vector<std::vector<double>>          x_p1;                    //!< ZMPから接点までの変位 (x,y) [m]
  std::vector<double>                       move_distance;           //!< 移動距離(x,y) [m]
  std::vector<double>                       move_distance_pre;
  Eigen::Vector3d                           com_pos_pre;
  std::vector<Eigen::Vector3d>              leg_pos_pre;
  std::vector<double>                       leg_yaw_pre;
  double                                    com_height_;  //!< 重心高さ[m]

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

  const double      judge_num = 2;  //!< 支持多角形の傾きの種類（支持多角形が長方形の場合は2）
  std::vector<bool> SNE_flag;       //!< SNEの閾値が適切か判定する変数

  /*** util関連のクラスの初期化 ***/
  Utils::Utils util;

  PreviewControl pc;
};