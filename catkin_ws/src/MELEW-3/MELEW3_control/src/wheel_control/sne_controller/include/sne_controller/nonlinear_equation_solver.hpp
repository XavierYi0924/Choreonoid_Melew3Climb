/**
 * @file    nonlinear_equation_solver.hpp
 * @author  Taisei Suzuki
 * @brief   非線形関数を解くプログラムファイルのヘッダ
 * @version 0.1
 * @date    2023-05-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cmath>
#include <iostream>

/**
 * @brief 非線形関数を解くクラス
 *
 */
class NonlinearEquationSolver {
public:
  /*** 関数 ***/
  virtual double f(const double x) const = 0;  //!<非線形方程式f(x)=0の関数f(x)を返す関数
  bool           newton_solve(double& x, const double epsilon, const int max_iterations);
  bool           newton_solve(double& x, const double epsilon, const int max_iterations, const double max_step);
  NonlinearEquationSolver();

private:
  /*** 関数 ***/
  double df(const double x);

  /*** 変数 ***/
  double dx;          //!< 移動量dx
  double step_width;  //!< ステップ幅
};

/**
 * @brief SNE等高線の傾きaの位置における媒介変数θを計算するクラス（傾きが存在する場合）
 *
 */
class SneEquationSolver1 : public NonlinearEquationSolver {
public:
  /* ニュートン法を適用する非線形関数f(x) */
  double f(double x) const override;

  /* コンストラクタ */
  SneEquationSolver1(const double _h, const double _phi, const double _SNE, const double _a);

private:
  /* 使用する変数 */
  double h;        //!< 重心高さ [m]
  double phi;      //!< 斜面の傾斜角 [rad]
  double SNE;      //!< SNE [m]
  double a_angle;  //!< SNE等高線の傾き角
};