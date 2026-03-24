/**
 * @file    plot_sne_contour3.hpp
 * @author  Taisei Suzuki
 * @brief   SNE等高線を用いて修正した支持多角形を描画するプログラム
 * @version 0.1
 * @date    2023-05-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <ros/ros.h>

#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "matplotlibcpp.h"
#include "nonlinear_equation_solver.hpp"

/**
 * @brief SNEを用いて目標脚先軌道を生成するクラス
 *
 */
class PlotSneContour {
public:
  PlotSneContour(ros::NodeHandle nh, ros::NodeHandle pnh);
  void CalcSneContour(const double SNE, const double theta, double& x, double& y);
  void CalcZmp();
  void CalcSupportPolygon();
  void CalcPointOfTangency(const int num);
  void CalcMovement(const int num);
  void PlotSne();
  void PlotZmp();
  void PlotSupportPolygon(const int count);
  void PlotPointOfTangency(const int num);
  void PlotLine();
  void PlotSettings1();
  void PlotSettings2();
  void PlotSneContourCallback();
  void Run();

private:
  /*** ROS関連 ***/
  ros::NodeHandle nh_;    //!< NodeHandle
  ros::Rate       rate_;  //!< 制御周期（デフォルトでは100Hz）
  int             phase;  //!< 動作モード

  /*** 変数関連 ***/
  enum leg_num { FL, FR, BL, BR, LEG_NUM };  //!< 脚の番号

  std::vector<double> SNE_threshold;  //!< SNEの閾値 (x,y) [m]
  double              h;              //!< 重心高さ [m]
  double              phi;            //!< 斜面の傾斜角 [rad]
  double              xi;             //!< 斜面上方向の偏角 [rad]
  double              d_leg;          //!< ロボットの長さ [m]
  double              b_leg;          //!< ロボットの幅 [m]

  Eigen::Vector3d                           ZMP;                     //!< ZMP [m]
  std::vector<Eigen::Vector3d>              foot;                    //!< 目標脚先位置 [m]
  std::vector<Eigen::Vector3d>              support_porigon_vector;  //!< 支持多角形の方向ベクトル
  std::vector<std::vector<Eigen::Vector3d>> x_p;                     //!< 接点座標 (x,y) [m]
  std::vector<std::vector<double>>          x_p1;                    //!< ZMPから接点までの変位 (x,y) [m]

  const double      judge_num = 2;  //!< 支持多角形の傾きの種類（支持多角形が長方形の場合は2）
  std::vector<bool> SNE_flag;       //!< SNEの閾値が適切か判定する変数
  std::vector<double>      SNE_list = {0.001, 0.005, 0.01, 0.02, 0.04, 0.06,
                                  0.08,  0.10,  0.15, 0.20, 0.25};  //!< 表示するSNEのリスト([m])
  std::vector<std::string> color_list = {
      "#ff0080", "#ff0000", "#ff8000", "#ffff00", "#80ff00", "#00ff00",
      "#00ff80", "#00ffff", "#0080ff", "#0000ff", "#8000ff"};  //!< グラフの色のリスト
  std::vector<double> scale = {-0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5};  //!< 目盛りの値のリスト
};