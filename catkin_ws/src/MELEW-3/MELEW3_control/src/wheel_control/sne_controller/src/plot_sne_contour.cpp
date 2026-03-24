/**
 * @file 　 plot_sne_contour.cpp
 * @author  Taisei Suzuki
 * @brief   SNE等高線を描画するプログラム
 * @version 0.1
 * @date    2023-05-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <ros/ros.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../include/sne_controller/matplotlibcpp.h"
namespace plt = matplotlibcpp;

/**
 * @brief SNE等高線の(x, y)座標を設定する関数
 *
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    ロボットの進行方向から見た斜面上方向の角度 [rad]
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
 * @brief SNE等高線を描画する関数
 * @param h     重心高さ [m]
 * @param phi   斜面の傾斜角 [rad]
 * @param xi    ロボットの進行方向から見た斜面上方向の角度 [rad]
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
 * @param xi    ロボットの進行方向から見た斜面上方向の角度 [rad]
 *
 */
void PlotZmp(const double h, const double phi, const double xi) {
  std::map<std::string, std::string> args_ZMP;  //!< ZMPのグラフの設定用マップ

  // 凡例の設定
  args_ZMP = {{"label", "ZMP"}, {"marker", "o"}, {"linestyle", "None"}, {"c", "black"}};

  // ZMPの描画
  plt::plot({-h * tan(phi) * cos(xi)}, {0.0}, args_ZMP);
}

/**
 * @brief 原点とZMPを通る直線を描画する関数
 * @param xi    ロボット座標系から見た斜面上方向の角度 [rad]
 *
 */
void PlotLine(const double xi) {
  const double l = 0.75;  //!< 原点から端までの長さ

  // 直線の描画
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
 * @param xi    ロボットの進行方向から見た斜面上方向の角度 [rad]
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
 *    h   : 重心高さ [m]
 *    phi : 斜面の傾斜角 [deg]
 *    xi  : ロボットの進行方向から見た斜面上方向の角度 [deg]
 *
 *  実行例：
 *    実行例1：rosrun sne_controller plot_sne_contour 0.38 30 60 : h=0.38[m], phi=30[deg], xi=60[deg]のSNE等高線を描画
 *    実行例2：rosrun sne_controller plot_sne_contour 0.38 30    : h=0.38[m], phi=30[deg], xi= 0[deg]のSNE等高線を描画
 *    実行例3：rosrun sne_controller plot_sne_contour 0.38       : h=0.38[m], phi= 0[deg], xi= 0[deg]のSNE等高線を描画
 *    実行例4：rosrun sne_controller plot_sne_contour            : "Argument are too few or too many for this program!"
 *
 */
int main(int argc, char* argv[]) {
  double h = 0.38;   //!< 重心高さ [m]
  double phi = 0.0;  //!< 斜面の傾斜角 [rad]
  double xi = 0.0;   //!< ロボットの進行方向から見た斜面上方向の角度 [rad]

  std::vector<double>      SNE_list = {0.001, 0.005, 0.01, 0.02, 0.04, 0.06,
                                  0.08,  0.10,  0.15, 0.20, 0.25};  //!< 表示するSNEのリスト([m])
  std::vector<std::string> color_list = {
      "#ff0080", "#ff0000", "#ff8000", "#ffff00", "#80ff00", "#00ff00",
      "#00ff80", "#00ffff", "#0080ff", "#0000ff", "#8000ff"};  //!< グラフの色のリスト
  std::vector<double> scale = {-0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5};  //!< 目盛りの値のリスト

  try {
    switch (argc) {
      case 4:
        xi = std::atof(argv[3]) * (M_PI / 180.0);  //!< ロボットの進行方向から見た斜面上方向への角度（[deg]で入力）

      case 3:
        phi = std::atof(argv[2]) * (M_PI / 180.0);  //!< 斜面の傾斜角（[deg]で入力）
        if (phi < 0.0 || phi >= (M_PI / 2.0)) throw "The angle of phi is out of range!";

      case 2:
        h = std::atof(argv[1]);  //!< 重心高さ（[m]で入力）
        if (h <= 0.0) throw "The height of the center of mass is too low!";

        // 図の初期設定
        PlotSettings1();

        // SNE等高線を描画
        for (int k = 0; k < SNE_list.size(); k++) PlotSne(h, phi, xi, SNE_list[k], color_list[k]);

        // ZMPを描画
        PlotZmp(h, phi, xi);

        // 斜面の場合，原点とZMPを通る直線を描画
        if (phi) PlotLine(xi);

        // 図の追加設定
        PlotSettings2(h, phi, xi);

        // 図の目盛りの設定
        plt::xticks(scale, {}, {{"fontsize", "15"}});
        plt::yticks(scale, {}, {{"fontsize", "15"}});

        // 図を表示
        plt::show();

        break;

      // 例外処理
      default:
        throw "Argument are too few or too many for this program!";
    }
  } catch (const char* str) {
    ROS_ERROR("%s", str);
  }
  return (0);
}