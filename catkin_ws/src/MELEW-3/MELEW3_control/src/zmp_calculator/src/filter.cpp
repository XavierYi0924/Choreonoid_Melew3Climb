/**
 * @file filter.cpp
 * @author Taisei Suzuki
 * @brief フィルタ処理を行う
 * @version 0.1
 * @date 2023-11-01
 *
 * @copyFR CopyFR (c) 2023
 *
 */

#include <zmp_calculator/filter.hpp>

Filter::Filter(){};
Filter::Filter(double dt = 0.001) { dt_ = dt; };

/**
 * @brief クラスの初期化を行う関数
 *
 * @param dt 制御周期
 */
void Filter::init(const double dt) { dt_ = dt; }

/**
 * @brief ローパスフィルタの処理を行う関数
 *
 * @param raw_data フィルタ前のデータ
 * @param fc       カットオフ周波数
 */
double Filter::LPF(const double raw_data, const double fc) {
  x_double += (fc * dt_) * (raw_data - x_double);
  return x_double;
}

/**
 * @brief ローパスフィルタの処理を行う関数
 *
 * @param raw_data フィルタ前のデータ
 * @param fc       カットオフ周波数
 */
Eigen::Vector3d Filter::LPF(const Eigen::Vector3d raw_data, const double fc) {
  x_vector += (fc * dt_) * (raw_data - x_vector);
  return x_vector;
}