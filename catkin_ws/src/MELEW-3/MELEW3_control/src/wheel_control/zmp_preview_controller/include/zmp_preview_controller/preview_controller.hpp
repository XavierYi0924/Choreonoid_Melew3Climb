/**
 * @file    pattern_generator.hpp
 * @author  Yuta Ishizawa
 * @brief   予見制御に関するクラスのヘッダ
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef PREVIEW_CONTROLLER_H_
#define PREVIEW_CONTROLLER_H_

#define DEBUG 0

#include <Eigen/Dense>

#include "cart_table.hpp"
#include "riccati_solver.hpp"

/* Default values */
static constexpr double default_Qe = 1;
static constexpr double default_Ru = 1e-2;
static constexpr double default_preview_time = 1.0;  // 何秒先を見るか

class PreviewController {
private:
  int    N_preview;
  double com_height;

  /* サーボ拡大系でのシステム行列 */
  Eigen::MatrixXd A_tilde;  // システム行列(拡大系)
  Eigen::MatrixXd b_tilde;  // 入力係数行列(拡大系)
  Eigen::MatrixXd c_tilde;  // 出力係数行列(拡大系)
  Eigen::MatrixXd Q_tilde;  // 出力誤差・状態に対する重み行列(拡大系)
  Eigen::MatrixXd R;        // 入力に対する重み行列
  Eigen::MatrixXd K;        // 最適ゲイン
  Eigen::MatrixXd P;        // Riccati方程式の解(拡大系)

  /* 最適予見制御 */
  Eigen::MatrixXd Gi;        // ZMP誤差に対するゲイン
  Eigen::MatrixXd Gx;        // 状態フィードバックゲイン
  Eigen::MatrixXd Gd;        // 予見ゲイン
  Eigen::MatrixXd Ac_tilde;  // 拡大系での閉ループシステム行列
  Eigen::MatrixXd I_tilde;
  Eigen::MatrixXd X_tilde;

  CartTable model;  // テーブル・台車型モデル

public:
  void calculateParameter(double Qe, double Ru, double com_height_);
  bool execute(int k_time, const std::vector<Eigen::Vector3d> zmp, std::vector<Eigen::Vector3d>& com,
               std::vector<double>& com_height_trajectory, bool last_flag);
  PreviewController(double com_height, double dt, double t_preview);
};

#endif