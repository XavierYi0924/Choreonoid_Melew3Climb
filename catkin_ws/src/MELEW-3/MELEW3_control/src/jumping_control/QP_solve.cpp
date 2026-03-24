/**
 * @Author: Your name
 * @Date:   2022-11-03 02:46:56
 * @Last Modified by:   Your name
 * @Last Modified time: 2023-01-12 12:11:31
 */

#include <MELEW3_control/QP_solve.hpp>
namespace MELEW3_control {
// QPを解く関数
// 注：eigen行列に各要素を代入してから実行すること
// QP_Variables_Num：最適化変数の数
// QP_Constraints_Num：制約条件の行数
// nWSR：最適化計算の最大回数、その回数計算するとそこで打ち切られる
// cpu_time：最適化計算の制限時間、制限時間に達するとそこで打ち切られる
void QP_solve::qp_solve(int QP_Variables_Num, int QP_Constraints_Num, qpOASES::int_t nWSR, qpOASES::real_t cpu_time){

    // qpOASESの定義
    qpOASES::QProblem myqp(QP_Variables_Num, QP_Constraints_Num);
	  qpOASES::Options options;

    // qpOASESの配列定義
    qpOASES::real_t *qp_H;
    qpOASES::real_t *qp_A;
    qpOASES::real_t *qp_g;
    qpOASES::real_t *qp_lb;
    qpOASES::real_t *qp_ub;
    qpOASES::real_t *qp_lbA;
    qpOASES::real_t *qp_ubA;
    qpOASES::real_t *xOpt;
	  qpOASES::real_t *yOpt;
    qpOASES::real_t *xOpt_ini;

    // メモリを確保
    qp_H = new qpOASES::real_t[QP_Variables_Num * QP_Variables_Num];
    qp_A = new qpOASES::real_t[QP_Constraints_Num * QP_Variables_Num];
    qp_g = new qpOASES::real_t[QP_Variables_Num];
    qp_lb = new qpOASES::real_t[QP_Variables_Num];
    qp_ub = new qpOASES::real_t[QP_Variables_Num];
    qp_lbA = new qpOASES::real_t[QP_Constraints_Num];
    qp_ubA = new qpOASES::real_t[QP_Constraints_Num];
    xOpt = new qpOASES::real_t[QP_Variables_Num];
	  yOpt = new qpOASES::real_t[QP_Variables_Num+QP_Constraints_Num];
    xOpt_ini = new qpOASES::real_t[QP_Variables_Num];

    // eigen行列からqpOASES配列へ変換
    int count = 0;
    for(int i = 0; i < QP_Variables_Num; i++){
        for(int j = 0; j < QP_Variables_Num; j++){
            qp_H[count] = N(i, j);
            count++;
        }
        qp_g[i] = p(i,0);
        qp_lb[i] = lb(i,0);
        qp_ub[i] = ub(i,0);
        xOpt_ini[i] = 0.0;
    }
    count = 0;
    for(int k = 0; k < QP_Constraints_Num; k++){
        for(int l = 0; l < QP_Variables_Num; l++){
            qp_A[count] = consA(k, l);
            count++;
        }
        qp_lbA[k] = lbA(k,0);
        qp_ubA[k] = ubA(k,0);
    }

    // qpOASESの設定
    options.printLevel = qpOASES::PL_NONE;
    myqp.setOptions( options );
    myqp.setPrintLevel( options.printLevel );

    // 時間計測開始
    start = std::chrono::system_clock::now();

    // QP_solve
    qp_exit_flag = myqp.init( qp_H, qp_g, qp_A, qp_lb, qp_ub, qp_lbA, qp_ubA, nWSR, &cpu_time);
    myqp.getPrimalSolution( xOpt );
    myqp.getDualSolution( yOpt );
    
    // 時間計測終了
    end = std::chrono::system_clock::now();
    solve_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);
    // std::cout << "solve_time" << solve_time << std::endl;

    // 結果を保存
    ANS = Eigen::MatrixXd::Zero(QP_Variables_Num, 1);
    for(int l = 0; l < QP_Variables_Num; l++){
        ANS(l,0) = xOpt[l];
    }

    // メモリを解放
    myqp.reset();
    delete[] qp_H;
    delete[] qp_A;
    delete[] qp_g;
    delete[] qp_lb;
    delete[] qp_ub;
    delete[] qp_lbA;
    delete[] qp_ubA;
    delete[] xOpt;
	  delete[] yOpt;
    delete[] xOpt_ini;

}

// シンプルなQPを解く関数
// 注：eigen行列に各要素を代入してから実行すること
// QP_Variables_Num：最適化変数の数
// nWSR：最適化計算の最大回数、その回数計算するとそこで打ち切られる
// cpu_time：最適化計算の制限時間、制限時間に達するとそこで打ち切られる
void Simple_QP_solve::simple_qp_solve(int QP_Variables_Num, qpOASES::int_t nWSR, qpOASES::real_t cpu_time){

    // qpOASESの定義
    qpOASES::QProblemB myqp(QP_Variables_Num);
	  qpOASES::Options options;

    // qpOASESの配列定義
    qpOASES::real_t *qp_H;
    qpOASES::real_t *qp_g;
    qpOASES::real_t *qp_lb;
    qpOASES::real_t *qp_ub;
    qpOASES::real_t *xOpt;
  	qpOASES::real_t *yOpt;
    qpOASES::real_t *xOpt_ini;

    // メモリを確保
    qp_H = new qpOASES::real_t[QP_Variables_Num * QP_Variables_Num];
    qp_g = new qpOASES::real_t[QP_Variables_Num];
    qp_lb = new qpOASES::real_t[QP_Variables_Num];
    qp_ub = new qpOASES::real_t[QP_Variables_Num];
    xOpt = new qpOASES::real_t[QP_Variables_Num];
	  yOpt = new qpOASES::real_t[QP_Variables_Num];
    xOpt_ini = new qpOASES::real_t[QP_Variables_Num];

    // eigen行列からqpOASES配列へ変換
    int count = 0;
    for(int i = 0; i < QP_Variables_Num; i++){
        for(int j = 0; j < QP_Variables_Num; j++){
            qp_H[count] = H(i, j);
            count++;
        }
        qp_g[i] = g(i,0);
        qp_lb[i] = lb(i,0);
        qp_ub[i] = ub(i,0);
        xOpt_ini[i] = 0.0;
    }

    // qpOASESの設定
    options.printLevel = qpOASES::PL_NONE;
    myqp.setOptions( options );
    myqp.setPrintLevel( options.printLevel );

    // 時間計測開始
    start = std::chrono::system_clock::now();

    // QP_solve
    qp_exit_flag = myqp.init( qp_H, qp_g, qp_lb, qp_ub, nWSR, &cpu_time);
    myqp.getPrimalSolution( xOpt );
    myqp.getDualSolution( yOpt );
    
    // 時間計測終了
    end = std::chrono::system_clock::now();
    solve_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);
    // std::cout << "solve_time" << solve_time << std::endl;

    // 結果を保存
    ANS = Eigen::MatrixXd::Zero(QP_Variables_Num, 1);
    for(int l = 0; l < QP_Variables_Num; l++){
        ANS(l,0) = xOpt[l];
    }

    // メモリを解放
    myqp.reset();
    delete[] qp_H;
    delete[] qp_g;
    delete[] qp_lb;
    delete[] qp_ub;
    delete[] xOpt;
	  delete[] yOpt;
    delete[] xOpt_ini;

}
} // namespace melew3