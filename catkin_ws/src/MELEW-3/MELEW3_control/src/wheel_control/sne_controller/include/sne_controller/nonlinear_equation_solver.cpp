/**
 * @file    nonlinear_equation_solver.cpp
 * @author  Taisei Suzuki
 * @brief   非線形関数を解くプログラムファイル
 * @version 0.1
 * @date    2023-05-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "nonlinear_equation_solver.hpp"

NonlinearEquationSolver::NonlinearEquationSolver() {
  dx = 0.0;
  step_width = 0.0;
}

/**
 * @brief 関数f(x)の時間微分f'(x)を返す関数
 *
 * @param x x
 *
 */
double NonlinearEquationSolver::df(const double x) { return (f(x + step_width) - f(x)) / step_width; }

/**
 * @brief ニュートン法を用いて非線形方程式f(x)=0を解く関数（最大ステップ幅指定なし）
 *
 * @param x              x
 * @param epsilon        ステップ幅
 * @param max_iterations 最大反復回数
 *
 */
bool NonlinearEquationSolver::newton_solve(double& x, const double epsilon, const int max_iterations) {
  for (int i = 0; i < max_iterations; i++) {
    step_width = epsilon;                           // ステップ幅を更新
    dx = -f(x) / df(x);                             // ニュートン法による移動量dxを計算
    x += dx;                                        // xの値を更新
    if (std::fabs(f(x)) < step_width) return true;  // 収束判定
  }
  return false;  // 収束しなかった場合はfalseを返す
}

/**
 * @brief ニュートン法を用いて非線形方程式f(x)=0を解く関数（最大ステップ幅指定あり）
 *
 * @param x              x
 * @param epsilon        ステップ幅
 * @param max_iterations 最大反復回数
 * @param max_step       最大ステップ幅（オプション）
 *
 */
bool NonlinearEquationSolver::newton_solve(double& x, const double epsilon, const int max_iterations,
                                           const double max_step) {
  for (int i = 0; i < max_iterations; i++) {
    step_width = epsilon;  // ステップ幅を更新
    dx = -f(x) / df(x);    // ニュートン法による移動量dxを計算

    // xの値を更新（ステップ幅を-max_stepからmax_stepに制限）
    if (std::fabs(dx) < max_step)
      x += dx;
    else
      x += max_step * ((dx > 0.0) - (dx < 0.0));

    if (std::fabs(f(x)) < step_width) return true;  // 収束判定
  }
  return false;  // 収束しなかった場合はfalseを返す
}

/**
 * @brief Construct a new SneEquationSolver1::SneEquationSolver1 object
 *
 * @param _h   重心高さ [m]
 * @param _phi 斜面の傾斜角 [rad]
 * @param _SNE SNE [m]
 * @param _a_angle   SNE等高線の接線の角度 [rad]
 *
 */
SneEquationSolver1::SneEquationSolver1(const double _h, const double _phi, const double _SNE, const double _a_angle) {
  h = _h;
  phi = _phi;
  SNE = _SNE;
  a_angle = _a_angle;
}

/**
 * @brief 関数f(x)の値を返す関数
 *
 * @param x x
 *
 */
double SneEquationSolver1::f(double x) const {
  double eq1 = (SNE + h * cos(phi)) * 2 * sin(x) * cos(x) * sin(phi);
  double eq2 = -sin(x) * (2 * cos(x) * cos(x) * sin(phi) * sin(phi) + cos(phi) * cos(phi));
  double eq3 = -(SNE + h * cos(phi)) * (cos(x) * cos(x) - sin(x) * sin(x)) * sin(phi);
  double eq4 = -cos(x) * (2 * sin(x) * sin(x) * sin(phi) * sin(phi) - 1);
  double eq5 = (SNE * (SNE + 2 * h * cos(phi))) / (cos(x) * cos(x) * sin(phi) * sin(phi) + cos(phi) * cos(phi));
  return atan((eq3 + eq4 * sqrt(eq5)) / (eq1 + eq2 * sqrt(eq5))) - a_angle;
}