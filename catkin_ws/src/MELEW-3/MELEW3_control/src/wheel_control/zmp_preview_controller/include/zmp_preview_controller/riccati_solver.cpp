/**
 * @file    pattern_generator.cpp
 * @author  Yuta Ishizawa
 * @brief   Riccati方程式を解くための関数群のヘッダ
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "riccati_solver.hpp"

using namespace std;
using namespace Eigen;

/**
 * @brief   連続時間系でのCARE(Continuous Algebra Riccati Eq)を
 *          有本・ポッター法で解き，最適ゲインKも計算する
 *
 * @param Ac	システム行列
 * @param bc	入力係数行列
 * @param Q
 * @param R
 * @param K
 * @param P
 */
void RiccatiSolver::solveCARE(const MatrixXd& Ac, const MatrixXd& bc, const MatrixXd& Q, const MatrixXd& R, MatrixXd& K,
                              MatrixXd& P) {
  const uint dim_x = Ac.rows();
  const uint dim_u = bc.cols();

  // set Hamilton matrix
  Eigen::MatrixXd Ham = Eigen::MatrixXd::Zero(2 * dim_x, 2 * dim_x);
  Ham << Ac, -bc * R.inverse() * bc.transpose(), -Q, -Ac.transpose();

  // calc eigenvalues and eigenvectors
  Eigen::EigenSolver<Eigen::MatrixXd> Eigs(Ham);

  // check eigen values
  // std::cout << "eigen values：\n" << Eigs.eigenvalues() << std::endl;
  // std::cout << "eigen vectors：\n" << Eigs.eigenvectors() << std::endl;

  // extract stable eigenvectors into 'eigvec'
  Eigen::MatrixXcd eigvec = Eigen::MatrixXcd::Zero(2 * dim_x, dim_x);
  int              j = 0;
  for (int i = 0; i < 2 * dim_x; ++i) {
    if (Eigs.eigenvalues()[i].real() < 0.) {
      eigvec.col(j) = Eigs.eigenvectors().block(0, i, 2 * dim_x, 1);
      ++j;
    }
  }

  // calc P with stable eigen vector matrix
  Eigen::MatrixXcd Vs_1, Vs_2;
  Vs_1 = eigvec.block(0, 0, dim_x, dim_x);
  Vs_2 = eigvec.block(dim_x, 0, dim_x, dim_x);
  P = (Vs_2 * Vs_1.inverse()).real();

  // 最適ゲインKを求める
  K = (R + bc.transpose() * P * bc).inverse() * bc.transpose() * P * Ac;
}

/*  */
//

/**
 * @brief     離散時間系でのDARE(Discrete Algebra Riccati Eq)を繰り返し計算で解く関数
 *            参考リンク: https://github.com/TakaHoribe/Riccati_Solver/blob/master/riccati_solver.cpp
 * @param Ad
 * @param Bd
 * @param Q
 * @param R
 * @param P
 * @param K
 * @param tolerance
 * @param iter_max
 * @return true
 * @return false
 */
bool RiccatiSolver::solveDAREIteration(const Eigen::MatrixXd& Ad, const Eigen::MatrixXd& Bd, const Eigen::MatrixXd& Q,
                                       const Eigen::MatrixXd& R, Eigen::MatrixXd& P, Eigen::MatrixXd& K,
                                       const double& tolerance, const uint iter_max) {
  P = Q;  // initialize

  Eigen::MatrixXd P_next;
  Eigen::MatrixXd AdT = Ad.transpose();
  Eigen::MatrixXd BdT = Bd.transpose();
  Eigen::MatrixXd Rinv = R.inverse();

  double diff;
  for (uint i = 0; i < iter_max; ++i) {
    // -- discrete solver --
    P_next = AdT * P * Ad - AdT * P * Bd * (R + BdT * P * Bd).inverse() * BdT * P * Ad + Q;

    diff = fabs((P_next - P).maxCoeff());
    P = P_next;
    if (diff < tolerance) {
      // std::cout << "iteration mumber = " << i << std::endl;
      K = (R + Bd.transpose() * P * Bd).inverse() * Bd.transpose() * P * Ad;
      return true;
    }
  }
  return false;  // over iteration limit
}

// ToDo: DAREを有本・ポッター法で解く関数の実装