/**
 * @file    cart_table.hpp
 * @author  Yuta Ishizawa
 * @brief   テーブル・台車型モデルクラスのヘッダ
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CART_TABLE_H_
#define CART_TABLE_H_

#include <Eigen/Dense>
#include <vector>

static constexpr double g = 9.81;

/**
 * @brief テーブル・台車型モデルクラス
 *
 */
class CartTable {
public:
  const int N_system = 3;  // システムの状態次元数
  const int N_input = 1;   // システムの入力次元数
  const int N_ouput = 1;   // システムの出力次元数

  Eigen::MatrixXd xx, xy;  // 状態ベクトル
  Eigen::MatrixXd A;       // システム行列
  Eigen::MatrixXd b;       // 入力係数行列
  Eigen::MatrixXd c;       // 出力係数行列
  double          ux, uy;  // 入力（躍度）
  double          px, py;  // 出力（ZMP）

  void updateState(void);
  void updateOutput(void);
  void updateHeight(double com_height_);

  CartTable(const double com_height_, const double dt_);
};

#endif