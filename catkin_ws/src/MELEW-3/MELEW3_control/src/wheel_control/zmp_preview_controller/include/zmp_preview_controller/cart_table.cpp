/**
 * @file    cart_table.cpp
 * @author  Yuta Ishizawa
 * @brief   テーブル・台車型モデルクラス
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "cart_table.hpp"

CartTable::CartTable(const double com_height_, const double dt_)
    : xx(N_system, 1), xy(N_system, 1), A(N_system, N_system), b(N_system, N_input), c(N_ouput, N_system) {
  // システムの状態空間表現に関する計算
  A(0, 0) = 1.0;
  A(0, 1) = dt_;
  A(0, 2) = (dt_ * dt_) / 2.0;
  A(1, 0) = 0.0;
  A(1, 1) = 1.0;
  A(1, 2) = dt_;
  A(2, 0) = 0.0;
  A(2, 1) = 0.0;
  A(2, 2) = 1.0;

  b(0, 0) = (dt_ * dt_ * dt_) / 6.0;
  b(1, 0) = (dt_ * dt_) / 2.0;
  b(2, 0) = dt_;

  c(0, 0) = 1.0;
  c(0, 1) = 0.0;
  c(0, 2) = -com_height_ / g;
};

void CartTable::updateState(void) {
  xx = A * xx + b * ux;
  xy = A * xy + b * uy;
}

void CartTable::updateOutput(void) {
  px = (c * xx)(0);
  py = (c * xy)(0);
}

void CartTable::updateHeight(double com_height_) { c(0, 2) = -com_height_ / g; }