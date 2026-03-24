/**
 * @file    pattern_generator.hpp
 * @author  Yuta Ishizawa
 * @brief   Riccati方程式を解くための関数群のヘッダ
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef RICCATISOLVER_HPP_
#define RICCATISOLVER_HPP_

#include <Eigen/Dense>
#include <iostream>

class RiccatiSolver {
public:
  static void solveCARE(const Eigen::MatrixXd& Ac, const Eigen::MatrixXd& bc, const Eigen::MatrixXd& Q,
                        const Eigen::MatrixXd& R, Eigen::MatrixXd& K, Eigen::MatrixXd& P);

  static bool solveDAREIteration(const Eigen::MatrixXd& Ad, const Eigen::MatrixXd& Bd, const Eigen::MatrixXd& Q,
                                 const Eigen::MatrixXd& R, Eigen::MatrixXd& P, Eigen::MatrixXd& K,
                                 const double& tolerance = 1.E-5, const uint iter_max = 100000);
};

#endif