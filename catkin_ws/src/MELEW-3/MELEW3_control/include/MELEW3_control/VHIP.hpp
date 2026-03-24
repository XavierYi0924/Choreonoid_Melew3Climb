
#include "param.hpp"
#include "timer.hpp"
#include "Calc_Matrix.hpp"
#include "QP_solve.hpp"
#include <ros/ros.h>

namespace MELEW3_control {
// VHIPモデルでのMPC重心水平方向パターンジェネレータに関するクラス
class VHIP_MPC_PG{
public:

    Eigen::Vector3d CoM_PG;    // PGで生成したCoM位置
    Eigen::Vector3d dCoM_PG;   // PGで生成したCoM速度
    Eigen::Vector3d ddCoM_PG;  // PGで生成したCoM加速度
    Eigen::Vector3d dddCoM_PG; // PGで生成したCoMジャーク
    Eigen::Vector3d ZMP_PG;    // PGで生成した（予測）ZMP位置

    Eigen::MatrixXd xk;   // 現在時刻の状態量行列
    Eigen::MatrixXd uk;   // 現在時刻の最適入力

    // システム行列
    Eigen::MatrixXd Ad;
    Eigen::MatrixXd Bd;
    std::vector<Eigen::MatrixXd> Cd;

    // MPC計算用行列
    Eigen::MatrixXd F ;  
    Eigen::MatrixXd G ;
    Eigen::MatrixXd H ;

    // 重み行列
    Eigen::MatrixXd Wzmp;    // 出力追従誤差重み
    Eigen::MatrixXd Wx;    // 状態追従誤差重み
    Eigen::MatrixXd Wu;    // 入力追従誤差重み 
    Eigen::MatrixXd wzmp;    
    Eigen::MatrixXd wx;    
    Eigen::MatrixXd wu;

    // 目標行列
    Eigen::MatrixXd ZMP_ref;   // 出力の目標行列
    Eigen::MatrixXd X_ref;   // 状態量の目標行列
    Eigen::MatrixXd U_ref;   // 入力の目標行列    
    Eigen::VectorXd zmp_ref;
    Eigen::MatrixXd x_ref;
    Eigen::MatrixXd u_ref;

    // 制約行列
    Eigen::MatrixXd ZMP_max;
    Eigen::MatrixXd X_max;
    Eigen::MatrixXd U_max;
    Eigen::MatrixXd ZMP_min;
    Eigen::MatrixXd X_min;
    Eigen::MatrixXd U_min;
    Eigen::MatrixXd zmp_max;
    Eigen::MatrixXd x_max;
    Eigen::MatrixXd u_max;
    Eigen::MatrixXd zmp_min;
    Eigen::MatrixXd x_min;
    Eigen::MatrixXd u_min;

    QP_solve qp_solve;
    Timer timer;
    Param param;
    Reference ref;

    void Init(Timer timer_, Param param_, Reference ref_);
    void Set_System_Mat(Eigen::VectorXd com_z_tra, Eigen::VectorXd com_ddz_tra);
    void Update_xk(Eigen::Vector3d state);
    void Set_F();
    void Set_G();
    void Set_H();
    void Set_Wz();
    void Set_Wx();
    void Set_Wu();
    void Set_Zref(Eigen::VectorXd ZMP_pgref);
    void Set_Xref(Eigen::Vector3d dCoM_pgref);
    void Set_Uref();
    void Set_Zconstraint(Eigen::VectorXd ZMP_pgref);
    void Set_Zyconstraint(Eigen::VectorXd ZMP_pgref);
    void Set_Xconstraint();
    void Set_Uconstraint();
    void Set_qpOASES_mat();
    void Set_qpOASES_mat2();
    void Set_yqpOASES_mat();
    void Set_yqpOASES_mat2();
    void QP(VHIP_MPC_PG *mpc_);
    
};
}
