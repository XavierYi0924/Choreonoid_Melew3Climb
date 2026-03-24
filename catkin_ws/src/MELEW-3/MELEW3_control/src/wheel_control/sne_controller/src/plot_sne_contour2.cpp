/**
 * @file 　 plot_sne_contour2.cpp
 * @author  Taisei Suzuki
 * @brief   SNE等高線の接点を描画するプログラム
 * @version 0.1
 * @date    2023-05-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <ros/ros.h>

#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../include/sne_controller/matplotlibcpp.h"
#include "../include/sne_controller/nonlinear_equation_solver.hpp"
namespace plt = matplotlibcpp;

enum leg_num { FL, FR, BL, BR, LEG_NUM };  //!< 脚の番号

/**
 * @brief SNE等高線の(x, y)座標を設定する関数
 *
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 * @param SNE   SNE [m]
 * @param theta 媒介変数θ [rad]
 * @param x     SNE等高線のx座標 [m]
 * @param y     SNE等高線のy座標 [m]
 *
 */
void CalcSneContour(const double h, const double phi, const double xi, const double SNE, const double theta, double& x,
                    double& y) {
  //!< d(θ)の計算式
  const double d = (-(SNE + h * cos(phi)) * sin(phi) * cos(theta) +
                    sqrt(SNE * (SNE + 2 * h * cos(phi)) * (1 - sin(phi) * sin(phi) * sin(theta) * sin(theta)))) /
                   (cos(phi) * cos(phi));

  // (x, y)を計算
  x = d * cos(theta + xi);
  y = d * sin(theta + xi);
}

/**
 * @brief ZMPを計算する関数
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 * @param ZMP   ZMP [m]
 *
 */
void CalcZmp(const double h, const double phi, const double xi, Eigen::Vector3d& ZMP) {
  // ZMPを計算
  ZMP = Eigen::AngleAxisd(xi, Eigen::Vector3d::UnitZ()) * Eigen::Vector3d(-h * tan(phi), 0.0, 0.0);
}

/**
 * @brief 目標脚先位置を計算する関数
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 * @param d_leg 脚の前後方向の長さ [m]
 * @param b_leg 脚幅 [m]
 * @param foot  目標脚先位置 [m]
 *
 */
void CalcSupportPolygon(const double h, const double phi, const double xi, const double d_leg, const double b_leg,
                        std::vector<Eigen::Vector3d>& foot) {
  Eigen::Vector3d              ZMP;              //!< ZMP [m]
  std::vector<Eigen::Vector3d> p_foot(LEG_NUM);  //!< ZMPに対する脚先の相対位置 [m]
  foot.resize(LEG_NUM);

  // ZMPに対する脚先の相対位置を計算
  p_foot[FL] = Eigen::Vector3d(d_leg / 2.0, b_leg / 2.0, 0);
  p_foot[FR] = Eigen::Vector3d(d_leg / 2.0, -b_leg / 2.0, 0);
  p_foot[BL] = Eigen::Vector3d(-d_leg / 2.0, b_leg / 2.0, 0);
  p_foot[BR] = Eigen::Vector3d(-d_leg / 2.0, -b_leg / 2.0, 0);

  // ZMPを計算
  CalcZmp(h, phi, xi, ZMP);

  // 目標脚先位置を計算
  for (int i = 0; i < LEG_NUM; i++) foot[i] = p_foot[i] + ZMP;
}

/**
 * @brief SNE等高線を描画する関数
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 * @param SNE   SNE [m]
 * @param color 線の色
 *
 */
void PlotSne(const double h, const double phi, const double xi, const double SNE, const std::string color) {
  const int                          n = 361;    //!< グラフの点の数
  double                             theta;      //!< 媒介変数θ [rad]
  std::vector<double>                x(n);       //!< SNE等高線のx座標 [m]
  std::vector<double>                y(n);       //!< SNE等高線のy座標 [m]
  std::map<std::string, std::string> args_SNE;   //!< SNEのグラフの設定用マップ
  std::stringstream                  label_str;  //!< 図の凡例の文字列

  // SNE等高線(x,y)の計算
  for (int i = 0; i < n; i++) {
    theta = (double)i * (M_PI / 180.0);
    CalcSneContour(h, phi, xi, SNE, theta, x[i], y[i]);
  }

  // 凡例の設定
  label_str << "SNE=" << std::setprecision(3) << SNE << "[m]";
  args_SNE = {{"label", label_str.str()}, {"c", color}};

  // SNE等高線の描画
  plt::plot(x, y, args_SNE);
}

/**
 * @brief ZMPを描画する関数
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 *
 */
void PlotZmp(const double h, const double phi, const double xi) {
  Eigen::Vector3d                    ZMP;       //!< ZMP
  std::map<std::string, std::string> args_ZMP;  //!< ZMPのグラフの設定用マップ

  // ZMPを計算
  CalcZmp(h, phi, xi, ZMP);

  // 凡例の設定
  args_ZMP = {{"label", "ZMP"}, {"marker", "o"}, {"linestyle", "None"}, {"c", "gold"}};

  // ZMPの描画
  plt::plot({ZMP.x()}, {ZMP.y()}, args_ZMP);
}

/**
 * @brief 支持多角形を描画する関数
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 * @param d_leg 脚の前後方向の長さ [m]
 * @param b_leg 脚幅 [m]
 *
 */
void PlotSupportPolygon(const double h, const double phi, const double xi, const double d_leg, const double b_leg) {
  std::vector<Eigen::Vector3d>       foot;        //!< 目標脚先位置 [m]
  std::vector<double>                x(LEG_NUM);  //!< 支持多角形のx座標 [m]
  std::vector<double>                y(LEG_NUM);  //!< 支持多角形のy座標 [m]
  std::map<std::string, std::string> args_foot;   //!< ZMPのグラフの設定用マップ

  // 目標脚先位置を計算
  CalcSupportPolygon(h, phi, xi, d_leg, b_leg, foot);

  // 支持多角形の(x,y)座標を生成
  x = {foot[FL].x(), foot[FR].x(), foot[BR].x(), foot[BL].x(), foot[FL].x()};
  y = {foot[FL].y(), foot[FR].y(), foot[BR].y(), foot[BL].y(), foot[FL].y()};

  // 凡例の設定
  args_foot = {{"marker", "o"}, {"linestyle", "--"}, {"c", "red"}};

  // 支持多角形の描画
  plt::plot(x, y, args_foot);
}

/**
 * @brief SNE等高線上の任意の傾きの接点を計算し描画する関数
 * @param SNE_threshold   SNEの閾値 [m]
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 * @param d_leg 脚の前後方向の長さ [m]
 * @param b_leg 脚幅 [m]
 * @param foot  目標脚先位置 [m]
 *
 */
void PlotPointOfTangency(const double SNE_threshold, const double h, const double phi, const double xi,
                         const double d_leg, const double b_leg) {
  double                             a_angle;                             //!< 支持多角形の直線の偏角
  const std::vector<double>          theta = {M_PI * 0.75, M_PI * 1.25};  //!< 角度θの初期値
  std::vector<double>                x0;                                  //!< 初期推測値
  const double                       epsilon = 1e-6;                      //!< ステップ幅
  const int                          max_iterations = 100;                //!< 最大反復回数
  const double                       max_step = 0.1;                      //!< 最大ステップ幅
  std::vector<Eigen::Vector3d>       foot;                                //!< 目標脚先位置 [m]
  double                             x, y;                                //!< 接点の(x, y)座標 [m]
  std::vector<Eigen::Vector3d>       support_porigon;                     //!< 支持多角形の方向ベクトル
  std::map<std::string, std::string> args_PoT;                            //!< 接点のグラフの設定用マップ

  // 目標脚先位置を計算
  CalcSupportPolygon(h, phi, xi, d_leg, b_leg, foot);

  // 支持多角形の方向ベクトルを定義
  support_porigon = {foot[FR] - foot[FL], foot[FL] - foot[BL]};

  // 凡例の設定
  args_PoT = {{"marker", "o"}, {"linestyle", "None"}, {"c", "k"}};

  for (int i = 0; i < support_porigon.size(); i++) {
    // 支持多角形の直線の偏角を設定
    a_angle = atan(support_porigon[i].y() / support_porigon[i].x()) - xi;
    while (a_angle > M_PI / 2.0) a_angle -= M_PI;
    while (a_angle < -M_PI / 2.0) a_angle += M_PI;

    // 傾き(dy/dx)が定義可能な場合
    if (std::fabs(cos(a_angle)) > epsilon) {
      SneEquationSolver1 solver1(h, phi, SNE_threshold, a_angle);  // ニュートン法で角度θを計算するクラスを生成
      x0 = theta;                                                  // 初期値を設定

      for (int j = 0; j < x0.size(); j++) {
        // 角度θを計算
        if (solver1.newton_solve(x0[j], epsilon, max_iterations, max_step)) {
          // SNE等高線の(x, y)座標を計算
          CalcSneContour(h, phi, xi, SNE_threshold, x0[j], x, y);

          // 接点座標を描画
          plt::plot({x}, {y}, args_PoT);
        }
      }

      // 傾き(dy/dx)が定義不可能な場合
    } else {
      if (phi) {
        // 斜面の傾斜がある場合の角度θの解析解
        x0 = {acos(sqrt((SNE_threshold * cos(phi)) / (2.0 * h)) / sin(phi)), M_PI,
              (2.0 * M_PI) - acos(sqrt((SNE_threshold * cos(phi)) / (2.0 * h)) / sin(phi))};
      } else {
        x0 = {0.0, M_PI};  // 斜面の傾斜がない場合の角度θの解析解
      }

      for (int j = 0; j < x0.size(); j++) {
        // SNE等高線の(x, y)座標を計算
        CalcSneContour(h, phi, xi, SNE_threshold, x0[j], x, y);

        // 接点座標を描画
        plt::plot({x}, {y}, args_PoT);
      }
    }
  }
}

/**
 * @brief 原点とZMPを通る直線を描画する関数
 * @param xi    ロボット座標系から見た斜面上方向の角度 [rad]
 *
 */
void PlotLine1(const double xi) {
  const double l = 0.75;  //!< 原点から端までの長さ

  // グラフを描画
  plt::plot({-l * cos(xi), l * cos(xi)}, {-l * sin(xi), l * sin(xi)}, "k-");
}

/**
 * @brief 図の初期設定を行う関数
 *
 */
void PlotSettings1() {
  // 図のサイズを指定
  plt::figure_size(960, 960);

  // アスペクト比を1に設定
  plt::set_aspect_equal();

  // ラベルの設定
  plt::xlabel("x [m]", {{"fontsize", "20"}});
  plt::ylabel("y [m]", {{"fontsize", "20"}});

  // グラフの範囲の指定
  plt::xlim(-0.50, 0.50);
  plt::ylim(-0.50, 0.50);

  // グリッドを追加
  plt::grid(true);
}

/**
 * @brief 図の追加設定を行う関数
 *
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    斜面上方向の偏角 [rad]
 *
 */
void PlotSettings2(const double h, const double phi, const double xi) {
  std::stringstream title;  //!< 図のタイトルの文字列

  // タイトルの設定
  title << "SNE Contour (h=" << std::setprecision(3) << h << "[m], φ=" << std::setprecision(3) << phi * (180.0 / M_PI)
        << "[deg], ξ=" << std::setprecision(3) << xi * (180.0 / M_PI) << "[deg])";
  plt::title(title.str(), {{"fontsize", "20"}});

  // 図の凡例の設定
  plt::legend({{"loc", "best"}});
}

/**
 * @brief メインの関数
 * @param argc 引数の数
 * @param argv 引数のベクトル
 *
 * @details
 *  入力可能な引数：
 *    SNE : SNEの閾値 [m]
 *    h   : 重心高さ [m]
 *    phi : 斜面の傾斜角 [deg]
 *    xi  : ロボットの進行方向から見た斜面上方向の角度 [deg]
 *
 *  実行例：
 *    実行例1：rosrun sne_controller plot_sne_contour2 0.01 0.38 30 60
 *             : h=0.38[m], phi=30[deg], xi=60[deg]のSNE等高線とSNE=0.01[m]における接点を描画を描画
 *    実行例2：rosrun sne_controller plot_sne_contour2 0.01 0.38 30
 *             : h=0.38[m], phi=30[deg], xi= 0[deg]のSNE等高線とSNE=0.01[m]における接点を描画を描画
 *    実行例3：rosrun sne_controller plot_sne_contour2 0.01 0.38
 *             : h=0.38[m], phi= 0[deg], xi= 0[deg]のSNE等高線とSNE=0.01[m]における接点を描画を描画
 *    実行例4：rosrun sne_controller plot_sne_contour2
 *             : "Argument are too few or too many for this program!"
 *
 */
int main(int argc, char* argv[]) {
  double SNE_threshold = 0.001;  //!< SNEの閾値 [m]
  double h = 0.38;               //!< 重心高さ [m]
  double phi = 0.0;              //!< 斜面の傾斜角 [rad]
  double xi = 0.0;               //!< 斜面上方向の偏角 [rad]
  double d_leg = 0.500;          //!< ロボットの長さ [m]
  double b_leg = 0.400;          //!< ロボットの幅 [m]

  std::vector<double>      SNE_list = {0.001, 0.005, 0.01, 0.02, 0.04, 0.06,
                                  0.08,  0.10,  0.15, 0.20, 0.25};  //!< 表示するSNEのリスト([m])
  std::vector<std::string> color_list = {
      "#ff0080", "#ff0000", "#ff8000", "#ffff00", "#80ff00", "#00ff00",
      "#00ff80", "#00ffff", "#0080ff", "#0000ff", "#8000ff"};  //!< グラフの色のリスト
  std::vector<double> scale = {-0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5};  //!< 目盛りの値のリスト

  try {
    switch (argc) {
      case 5:
        xi = std::atof(argv[4]) * (M_PI / 180.0);  //!< 斜面上方向の偏角（[deg]で入力）

      case 4:
        phi = std::atof(argv[3]) * (M_PI / 180.0);  //!< 斜面の傾斜角（[deg]で入力）
        if (phi < 0.0 || phi >= (M_PI / 2.0)) throw "The angle of phi is out of range!";

      case 3:
        h = std::atof(argv[2]);  //!< 重心高さ（[m]で入力）
        if (h <= 0.0) throw "The height of the center of mass is too low!";

        SNE_threshold = std::atof(argv[1]);  //!< SNEの閾値（[m]で入力）
        if (SNE_threshold <= 0.0) throw "The threshold of SNE is too low!";
        {
          // 図の初期設定
          PlotSettings1();

          // SNE等高線を描画
          for (int k = 0; k < SNE_list.size(); k++) PlotSne(h, phi, xi, SNE_list[k], color_list[k]);

          // 斜面の場合，原点とZMPを通る直線を描画
          if (phi) PlotLine1(xi);

          // 支持多角形の描画
          PlotSupportPolygon(h, phi, xi, d_leg, b_leg);

          // ZMPを描画
          PlotZmp(h, phi, xi);

          // SNE等高線上の任意の傾きの接点を描画
          PlotPointOfTangency(SNE_threshold, h, phi, xi, d_leg, b_leg);

          // 図の追加設定
          PlotSettings2(h, phi, xi);

          // 図の目盛りの設定
          plt::xticks(scale, {}, {{"fontsize", "15"}});
          plt::yticks(scale, {}, {{"fontsize", "15"}});

          // 図を表示
          plt::show();

          break;
        }
      // 例外処理
      default:
        throw "Argument are too few or too many for this program!";
    }
  } catch (const char* str) {
    ROS_ERROR("%s", str);
  }
  return (0);
}