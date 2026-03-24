#pragma once

#include <ros/ros.h>

#include <Eigen/Core>

/**
 * @brief フィルタに関するクラス
 *
 */
class Filter {
public:
  Filter();
  Filter(double dt);
  void            init(const double dt);
  double          LPF(const double raw_data, const double fc);
  Eigen::Vector3d LPF(const Eigen::Vector3d raw_data, const double fc);

private:
  double dt_ = 0.0;  //!< 制御周期

  double          x_double = 0.0;                      //!< double型のデータを保存する変数
  Eigen::Vector3d x_vector = Eigen::Vector3d::Zero();  //!< Eigen::Vector3d型のデータを保存する変数
};