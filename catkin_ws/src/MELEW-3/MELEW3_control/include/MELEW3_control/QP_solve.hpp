#pragma once
#include <qpOASES.hpp>
#include "param.hpp"
#include "math.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <stdlib.h>
#include <iostream>
#include <chrono>

namespace MELEW3_control {
// QPソルバーに関するクラス
class QP_solve{
public:
    //qpOASES用eigen行列
    Eigen::MatrixXd N;    // 二次計画問題のN
    Eigen::MatrixXd p;   
    Eigen::MatrixXd lb;
    Eigen::MatrixXd ub;
    Eigen::MatrixXd lbA;
    Eigen::MatrixXd ubA;
    Eigen::MatrixXd consA;

    // QPを解いた結果を格納する行列
    Eigen::MatrixXd ANS;

    // 時間計測用
    std::chrono::system_clock::time_point start, end;
    double solve_time;

    qpOASES::int_t qp_exit_flag;

    void qp_solve(int QP_Variables_Num, int QP_Constraints_Num, qpOASES::int_t nWSR, qpOASES::real_t cpu_time);

};

// シンプルなQPソルバーに関するクラス
class Simple_QP_solve{
public:
    //qpOASES用eigen行列
    Eigen::MatrixXd H;    // 二次計画問題のH
    Eigen::MatrixXd g;   
    Eigen::MatrixXd lb;
    Eigen::MatrixXd ub;

    // QPを解いた結果を格納する行列
    Eigen::MatrixXd ANS;

    // 時間計測用
    std::chrono::system_clock::time_point start, end;
    double solve_time;

    qpOASES::int_t qp_exit_flag;

    void simple_qp_solve(int QP_Variables_Num, qpOASES::int_t nWSR, qpOASES::real_t cpu_time);

};
}