/**
 * @file    pattern_generator.cpp
 * @author  Yuta Ishizawa
 * @brief   予見制御に関するクラス
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "preview_controller.hpp"

using namespace Eigen;

/**
 * @brief Construct a new Preview Controller:: Preview Controller object
 *
 * @param com_height : 重心高さ（一定）
 * @param dt         : 制御周期
 * @param t_preview  : 予見時間
 */
PreviewController::PreviewController(double com_height_, double dt, double t_preview)
    : N_preview((int)(t_preview / dt)),
      com_height(com_height_),
      A_tilde(4, 4),
      b_tilde(4, 1),
      c_tilde(1, 4),
      Q_tilde(4, 4),
      R(1, 1),
      Gi(1, 1),
      Gx(1, 3),
      I_tilde(4, 1),
      model(com_height_, dt) {}

/**
 * @brief 予見制御に使用するパラメータを計算する
 *
 * @param Qe          : 予見制御でのZMP誤差に対するゲイン
 * @param Ru          : 入力に対するゲイン
 * @param com_height_ : 重心高さ
 */
void PreviewController::calculateParameter(double Qe, double Ru, double com_height_) {
  model.updateHeight(com_height_);

  /*** サーボ拡大系の諸計算 ***/
  A_tilde(0, 0) = 1.0;
  A_tilde.topRightCorner(1, 3) = model.c * model.A;
  A_tilde.bottomLeftCorner(3, 1) = MatrixXd::Zero(3, 1);
  A_tilde.bottomRightCorner(3, 3) = model.A;

  b_tilde.block<1, 1>(0, 0) = model.c * model.b;
  b_tilde.block<3, 1>(1, 0) = model.b;
  b_tilde(1, 0) = 0;

  c_tilde << 1.0, 0.0, 0.0, 0.0;

  Q_tilde = MatrixXd::Zero(4, 4);
  Q_tilde(0, 0) = Qe;

  R(0, 0) = Ru;

  /*** 最適ゲインK, Riccati方程式の解Pの計算 ***/
  if (!RiccatiSolver::solveDAREIteration(A_tilde, b_tilde, Q_tilde, R, P, K)) {
    std::cout << "solveRiccati failed!" << std::endl;
  }

  /*** 最適予見制御に関する諸計算 ***/
  Gi(0, 0) = K(0, 0);
  Gx = K.block<1, 3>(0, 1);

  Gd.resize(1, N_preview);
  Gd(0, 0) = -Gi(0, 0);

  Ac_tilde = A_tilde - b_tilde * K;

  I_tilde << 1.0, 0.0, 0.0, 0.0;
  X_tilde = -Ac_tilde.transpose() * P * I_tilde;

  for (int i = 1; i < N_preview; i++) {
    MatrixXd temp = R + b_tilde.transpose() * P * b_tilde;
    Gd.block<1, 1>(0, i) = temp.inverse() * b_tilde.transpose() * X_tilde;
    X_tilde = Ac_tilde.transpose() * X_tilde;
  }
}

/**
 * @brief 時刻kにおける目標ZMPからそれを満たすような入力を計算し，重心軌道を生成する
 *
 * @param k_time                : 離散時刻
 * @param zmp                   : 目標ZMP
 * @param com                   : 重心位置
 * @param com_height_trajectory : 目標重心高さ
 * @param last_flag             : 終了時の処理かどうかを判定するフラグ
 */
bool PreviewController::execute(int k_time, const std::vector<Eigen::Vector3d> zmp, std::vector<Eigen::Vector3d>& com,
                                std::vector<double>& com_height_trajectory, bool last_flag) {
  /*** 必要な変数の設定 ***/
  double preview_x = 0.0;
  double preview_y = 0.0;

  if (!(k_time + N_preview <= zmp.size() | last_flag))
    return false;        // 目標ZMP軌道のデータが不足している場合，falseを返す
  model.updateOutput();  // 出力の更新

  for (int j = 0; j < N_preview; j++) {
    // 予見するときにout-of-rangeになってしまうのを防ぐ
    if ((unsigned)k_time + j < zmp.size()) {
      preview_x += Gd(j) * zmp[k_time + j].x();
      preview_y += Gd(j) * zmp[k_time + j].y();
    } else {
      preview_x += Gd(j) * zmp.back().x();
      preview_y += Gd(j) * zmp.back().y();
    }
  }

  /*** 出力uの計算 ***/
  model.ux = -Gi(0) * (zmp[k_time].x() - model.px) - (Gx * model.xx)(0) - preview_x;
  model.uy = -Gi(0) * (zmp[k_time].y() - model.py) - (Gx * model.xy)(0) - preview_y;

  model.updateState();                                                        // 状態の更新
  com.emplace_back(model.xx(0), model.xy(0), com_height_trajectory[k_time]);  // CoM軌道を逐次作成
  return true;
}