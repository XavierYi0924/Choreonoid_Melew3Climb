#include <MELEW3_control/VHIP_AM.hpp>
namespace MELEW3_control {
// 時刻、パラメータ、目標値を更新して行列を初期化する関数
void VHIP_CAM_MPC_PG::Init(Timer timer_, Param param_, Reference ref_){
    // 時刻とパラメータの更新
    timer = timer_;
    param = param_;
    ref = ref_;

    // 行列の初期化
    CoM_PG = Eigen::Vector3d::Zero();
    dCoM_PG = Eigen::Vector3d::Zero();
    ddCoM_PG = Eigen::Vector3d::Zero();
    dddCoM_PG = Eigen::Vector3d::Zero();
    CAM_PG = Eigen::Vector3d::Zero();
    dCAM_PG = Eigen::Vector3d::Zero();
    ddCAM_PG = Eigen::Vector3d::Zero();
    ZMP_PG = Eigen::Vector3d::Zero();
    xk = Eigen::VectorXd::Zero(param.Stanum_AM);

    Ad = Eigen::MatrixXd::Zero(param.Stanum_AM, param.Stanum_AM);
    Bd = Eigen::MatrixXd::Zero(param.Stanum_AM, param.Inpnum);
    Cd.assign(param.Hp+1, Eigen::MatrixXd::Zero(param.Outnum, param.Stanum_AM));

    F = Eigen::MatrixXd::Zero(param.Stanum_AM*param.Hp, param.Stanum_AM);  
    G = Eigen::MatrixXd::Zero(param.Stanum_AM*param.Hp, param.Inpnum*param.Hu);
    H = Eigen::MatrixXd::Zero(param.Outnum*param.Hp, param.Stanum_AM*param.Hp);

    Wzmp = Eigen::MatrixXd::Zero(param.Outnum*param.Hp, param.Outnum*param.Hp);    // 出力追従誤差重み
    Wx = Eigen::MatrixXd::Zero(param.Stanum_AM*param.Hp, param.Stanum_AM*param.Hp);    // 状態追従誤差重み
    Wu = Eigen::MatrixXd::Zero(param.Inpnum*param.Hu, param.Inpnum*param.Hu);    // 入力追従誤差重み 
    wzmp = Eigen::MatrixXd::Zero(param.Outnum, 1);    
    wx = Eigen::MatrixXd::Zero(param.Stanum_AM, 1);    
    wu = Eigen::MatrixXd::Zero(param.Inpnum, 1);

    ZMP_ref = Eigen::MatrixXd::Zero(param.Outnum*param.Hp, 1);
    X_ref = Eigen::MatrixXd::Zero(param.Stanum_AM*param.Hp, 1);
    U_ref = Eigen::MatrixXd::Zero(param.Inpnum*param.Hu, 1);
    zmp_ref = Eigen::MatrixXd::Zero(param.Outnum, 1);
    x_ref = Eigen::MatrixXd::Zero(param.Stanum_AM, 1);
    u_ref = Eigen::MatrixXd::Zero(param.Inpnum, 1);

    ZMP_max = Eigen::MatrixXd::Zero(param.Outnum*param.Hp, 1);
    X_max = Eigen::MatrixXd::Zero(param.Stanum_AM*param.Hp, 1);
    U_max = Eigen::MatrixXd::Zero(param.Inpnum*param.Hu, 1);
    ZMP_min = Eigen::MatrixXd::Zero(param.Outnum*param.Hp, 1);
    X_min = Eigen::MatrixXd::Zero(param.Stanum_AM*param.Hp, 1);
    U_min = Eigen::MatrixXd::Zero(param.Inpnum*param.Hu, 1);
    zmp_max = Eigen::MatrixXd::Zero(param.Outnum, 1);
    x_max = Eigen::MatrixXd::Zero(param.Stanum_AM, 1);
    u_max = Eigen::MatrixXd::Zero(param.Inpnum, 1);
    zmp_min = Eigen::MatrixXd::Zero(param.Outnum, 1);
    x_min = Eigen::MatrixXd::Zero(param.Stanum_AM, 1);
    u_min = Eigen::MatrixXd::Zero(param.Inpnum, 1);

}

// システム行列をセットする関数
void VHIP_CAM_MPC_PG::Set_System_Mat(Eigen::VectorXd com_z_tra, Eigen::VectorXd com_ddz_tra){

     // 行列の要素へ代入
    Ad << 1.0, timer.MPC_dt, pow(timer.MPC_dt, 2)*0.5, 0.0,          0.0,
          0.0,          1.0,             timer.MPC_dt, 0.0,          0.0, 
          0.0,          0.0,                      1.0, 0.0,          0.0,
          0.0,          0.0,                      0.0, 1.0, timer.MPC_dt,
          0.0,          0.0,                      0.0, 0.0,          1.0;       

    Bd << pow(timer.MPC_dt,3)/6.0,                     0.0,
          pow(timer.MPC_dt,2)/2.0,                     0.0,
                     timer.MPC_dt,                     0.0,
                              0.0, pow(timer.MPC_dt,2)/2.0,
                              0.0,            timer.MPC_dt;

    double g = param.g;
    double m = param.m;
    for(int i = 0; i <= param.Hp; i++){
        double z = ref.CoM[(timer.loop_count + i) * timer.MPC_count].z();
        double ddz = ref.ddCoM[(timer.loop_count + i) * timer.MPC_count].z();
        double alpha = - z / (g + ddz);
        double beta = - 1 / (m * (g + ddz));
        Cd[i] << 1.0, 0.0, alpha, 0.0, beta;
        // PrintMat("Cd[i]",Cd[i]);
    }

}

// xkを更新する関数
void VHIP_CAM_MPC_PG::Update_xk(Eigen::VectorXd state){

    xk = state;

}

void VHIP_CAM_MPC_PG::Set_F(){

    for(int i = 0; i < param.Hp; i++){
        F.block(param.Stanum_AM*i, 0, param.Stanum_AM, param.Stanum_AM) = PowMat(Ad, i+1);
    }

}

void VHIP_CAM_MPC_PG::Set_G(){

    for(int i = 0; i < param.Hp; i++){
        if(i == 0){
            G.block(0, 0, param.Stanum_AM, param.Inpnum) = Bd;
        }
        else{
            G.block(i*param.Stanum_AM, 0, param.Stanum_AM, param.Inpnum) = PowMat(Ad, i)*Bd;
            for(int j = 1; j < param.Hu-1; j++){
                G.block(i*param.Stanum_AM, j*param.Inpnum, param.Stanum_AM, param.Inpnum) = G.block((i-1)*param.Stanum_AM, (j-1)*param.Inpnum, param.Stanum_AM, param.Inpnum);        
            }
            G.block(i*param.Stanum_AM, (param.Hu-1)*param.Inpnum, param.Stanum_AM, param.Inpnum) = G.block((i-1)*param.Stanum_AM, (param.Hu-2)*param.Inpnum, param.Stanum_AM, param.Inpnum) 
                                                                + G.block((i-1)*param.Stanum_AM, (param.Hu-1)*param.Inpnum, param.Stanum_AM, param.Inpnum);
        }
    }

}

void VHIP_CAM_MPC_PG::Set_H(){
    
    for(int i = 0; i < param.Hp; i++){
        H.block(param.Outnum*i, param.Stanum_AM*i, param.Outnum, param.Stanum_AM) = Cd[i+1];
    }

}

// 出力誤差重み行列に重みを代入する関数
void VHIP_CAM_MPC_PG::Set_Wz(){

    wzmp << param.w_z;

    for(int i = 0; i < param.Hp; i++){
        for(int j = 0; j < param.Outnum; j++){
            Wzmp(param.Outnum*i+j, param.Outnum*i+j) = wzmp(j,0);
        }
    }

}

// 状態量誤差重み行列に重みを代入する関数
void VHIP_CAM_MPC_PG::Set_Wx(){

    wx << 0.0, 0.0, 0.0, param.w_cam, 0.0;

    for(int i = 0; i < param.Hp; i++){
        for(int j = 0; j < param.Stanum_AM; j++){
            Wx(param.Stanum_AM*i+j, param.Stanum_AM*i+j) = wx(j,0);
        }
    }

}

// 入力誤差重み行列に重みを代入する関数
void VHIP_CAM_MPC_PG::Set_Wu(){

    wu << param.w_u, param.w_u;

    for(int i = 0; i < param.Hu; i++){
        for(int j = 0; j < param.Inpnum; j++){
            Wu(param.Inpnum*i+j, param.Inpnum*i+j) = wu(j,0);
        }
    }

}

// 目標出力行列に目標値を代入する関数
void VHIP_CAM_MPC_PG::Set_Zref(Eigen::VectorXd ZMP_pgref){

    zmp_ref = ZMP_pgref;

    for(int i = 0; i < param.Hp; i++){
        ZMP_ref(i,0)= zmp_ref[i];
    }

}

// 目標状態行列に目標値を代入する関数
void VHIP_CAM_MPC_PG::Set_Xref(){

    x_ref << 0.0, 0.0, 0.0, 0.0, 0.0;

    for(int i = 0; i < param.Hp; i++){
        X_ref.block(param.Stanum_AM*i, 0, param.Stanum_AM, 1) = x_ref;
    }

}

// 目標入力行列に目標値を代入する関数
void VHIP_CAM_MPC_PG::Set_Uref(){

    u_ref << 0.0, 0.0;

    for(int i = 0; i < param.Hu; i++){
        U_ref.block(param.Inpnum*i, 0, param.Inpnum, 1) = u_ref;
    }

}

// 出力に関する制約行列を生成する関数
void VHIP_CAM_MPC_PG::Set_Zconstraint(Eigen::VectorXd ZMP_pgref){

    for(int i = 0; i < param.Hp; i++){
        zmp_max << ZMP_pgref[i] + param.mpc_zmp_max;
        zmp_min << ZMP_pgref[i] + param.mpc_zmp_min;        
        ZMP_max.block(param.Outnum*i, 0, param.Outnum, 1) = zmp_max;
        ZMP_min.block(param.Outnum*i, 0, param.Outnum, 1) = zmp_min;
    }

}

// 出力に関する制約行列を生成する関数
void VHIP_CAM_MPC_PG::Set_Zyconstraint(Eigen::VectorXd ZMP_pgref){

    for(int i = 0; i < param.Hp; i++){
        zmp_max << ZMP_pgref[i] + param.mpc_yzmp_max;
        zmp_min << ZMP_pgref[i] + param.mpc_yzmp_min;        
        ZMP_max.block(param.Outnum*i, 0, param.Outnum, 1) = zmp_max;
        ZMP_min.block(param.Outnum*i, 0, param.Outnum, 1) = zmp_min;
    }

}

// 状態に関する制約行列を生成する関数
void VHIP_CAM_MPC_PG::Set_Xconstraint(){

    x_max << param.Large_num, param.Large_num, param.Large_num, param.Large_num, param.Large_num;
    x_min << -param.Large_num, -param.Large_num, -param.Large_num, -param.Large_num, -param.Large_num;

    for(int i = 0; i < param.Hp; i++){
        X_max.block(param.Stanum_AM*i, 0, param.Stanum_AM, 1) = x_max;
        X_min.block(param.Stanum_AM*i, 0, param.Stanum_AM, 1) = x_min;
    }

}

// 入力に関する制約行列を生成する関数
void VHIP_CAM_MPC_PG::Set_Uconstraint(){

    u_max << param.Large_num, param.Large_num;
    u_min << -param.Large_num, -param.Large_num;

    for(int i = 0; i < param.Hu; i++){
        U_max.block(param.Inpnum*i, 0, param.Inpnum, 1) = u_max;
        U_min.block(param.Inpnum*i, 0, param.Inpnum, 1) = u_min;
    }

}

// 評価関数と制約条件をqpに変換し、qpOASES用の行列を作る関数
void VHIP_CAM_MPC_PG::Set_qpOASES_mat(){

    // 評価関数の変換
    qp_solve.N = (H*G).transpose()*Wzmp*H*G + Wu + G.transpose()*Wx*G;
    qp_solve.p = (H*G).transpose()*Wzmp*(H*F*xk - ZMP_ref) + G.transpose()*Wx*F*xk;

    // 制約
    qp_solve.lb = U_min;
    qp_solve.ub = U_max;

    Eigen::VectorXd lbA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::VectorXd ubA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::MatrixXd consA = Eigen::MatrixXd::Zero(param.Hp * param.Outnum + param.Stanum_AM, param.Hu * param.Inpnum);
    lbA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_min - H*F * xk;
    ubA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_max - H*F * xk;
    consA.block(0,0,param.Hp * param.Outnum, param.Hu * param.Inpnum)  = H*G;
    Eigen::MatrixXd L = Eigen::MatrixXd::Zero(param.Stanum_AM, param.Stanum_AM*param.Hp);
    L.block(0, param.Stanum_AM*param.Hp-param.Stanum_AM, param.Stanum_AM, param.Stanum_AM) = Eigen::MatrixXd::Identity(param.Stanum_AM,param.Stanum_AM);
    Eigen::VectorXd x_f_ref = Eigen::VectorXd::Zero(param.Stanum_AM);
    x_f_ref << ref.x_f - ref.dx_f*timer.MPC_dt, ref.dx_f, 0.0, 0.0, 0.0;
    lbA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_f_ref - L*F*xk;
    ubA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_f_ref - L*F*xk;
    consA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, param.Hu * param.Inpnum)  = L*G;
    qp_solve.lbA = lbA;
    qp_solve.ubA = ubA;
    qp_solve.consA = consA;

}

// 評価関数と制約条件をqpに変換し、qpOASES用の行列を作る関数
void VHIP_CAM_MPC_PG::Set_qpOASES_mat2(){

    // 評価関数の変換
    qp_solve.N = (H*G).transpose()*Wzmp*H*G + Wu + G.transpose()*Wx*G;
    qp_solve.p = (H*G).transpose()*Wzmp*(H*F*xk - ZMP_ref) + G.transpose()*Wx*F*xk;

    // 制約
    qp_solve.lb = U_min;
    qp_solve.ub = U_max;

    Eigen::VectorXd lbA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::VectorXd ubA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::MatrixXd consA = Eigen::MatrixXd::Zero(param.Hp * param.Outnum + param.Stanum_AM, param.Hu * param.Inpnum);
    lbA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_min - H*F * xk;
    ubA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_max - H*F * xk;
    consA.block(0,0,param.Hp * param.Outnum, param.Hu * param.Inpnum)  = H*G;
    Eigen::MatrixXd L = Eigen::MatrixXd::Zero(param.Stanum_AM, param.Stanum_AM*param.Hp);
    L.block(0, param.Stanum_AM*param.Hp-param.Stanum_AM, param.Stanum_AM, param.Stanum_AM) = Eigen::MatrixXd::Identity(param.Stanum_AM,param.Stanum_AM);
    Eigen::VectorXd x_e_ref = Eigen::VectorXd::Zero(param.Stanum_AM);
    x_e_ref << ref.x_e, 0.0, 0.0, 0.0, 0.0;
    lbA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_e_ref - L*F*xk;
    ubA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_e_ref - L*F*xk;
    consA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, param.Hu * param.Inpnum)  = L*G;
    qp_solve.lbA = lbA;
    qp_solve.ubA = ubA;
    qp_solve.consA = consA;

}

// QPを解いて運動パターンを生成する
void VHIP_CAM_MPC_PG::QP(VHIP_CAM_MPC_PG *mpc_){
    VHIP_CAM_MPC_PG *mpc;
    mpc = mpc_;
    int QP_Variables_Num = param.Hu * param.Inpnum; // QP変数の数
    int QP_Constraints_Num = param.Hp * param.Outnum + param.Stanum_AM;   // 制約の数

    // QPを解く
    // std::cout << "t : " <<  timer.current_time <<" QP_Variables_Num : " << QP_Variables_Num << std::endl;
    qp_solve.qp_solve(QP_Variables_Num, QP_Constraints_Num, 1000, 1.0);

    // // 運動パターン格納
    Eigen::MatrixXd preview_X = F*xk + G*qp_solve.ANS;
    Eigen::MatrixXd preview_Z = H*preview_X;
    mpc->CoM_PG.x() = preview_X(0,0);
    mpc->dCoM_PG.x() = preview_X(1,0);
    mpc->ddCoM_PG.x() = preview_X(2,0);
    mpc->CAM_PG.y() = preview_X(3,0);
    mpc->dCAM_PG.y() = preview_X(4,0);
    mpc->dddCoM_PG.x() = qp_solve.ANS(0,0);
    mpc->ddCAM_PG.y() = qp_solve.ANS(1,0);
    mpc->ZMP_PG.x() = preview_Z(0,0);
}

//// For Y Direction ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 評価関数と制約条件をqpに変換し、qpOASES用の行列を作る関数
void VHIP_CAM_MPC_PG::Set_yqpOASES_mat(){

    // 評価関数の変換
    qp_solve.N = (H*G).transpose()*Wzmp*H*G + Wu + G.transpose()*Wx*G;
    qp_solve.p = (H*G).transpose()*Wzmp*(H*F*xk - ZMP_ref) + G.transpose()*Wx*F*xk;

    // 制約
    qp_solve.lb = U_min;
    qp_solve.ub = U_max;

    Eigen::VectorXd lbA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::VectorXd ubA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::MatrixXd consA = Eigen::MatrixXd::Zero(param.Hp * param.Outnum + param.Stanum_AM, param.Hu * param.Inpnum);
    lbA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_min - H*F * xk;
    ubA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_max - H*F * xk;
    consA.block(0,0,param.Hp * param.Outnum, param.Hu * param.Inpnum)  = H*G;
    Eigen::MatrixXd L = Eigen::MatrixXd::Zero(param.Stanum_AM, param.Stanum_AM*param.Hp);
    L.block(0, param.Stanum_AM*param.Hp-param.Stanum_AM, param.Stanum_AM, param.Stanum_AM) = Eigen::MatrixXd::Identity(param.Stanum_AM,param.Stanum_AM);
    Eigen::VectorXd x_f_ref = Eigen::VectorXd::Zero(param.Stanum_AM);
    x_f_ref << ref.y_f - ref.dy_f*timer.MPC_dt, ref.dy_f, 0.0, 0.0, 0.0;
    lbA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_f_ref - L*F*xk;
    ubA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_f_ref - L*F*xk;
    consA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, param.Hu * param.Inpnum)  = L*G;
    qp_solve.lbA = lbA;
    qp_solve.ubA = ubA;
    qp_solve.consA = consA;

}

// 評価関数と制約条件をqpに変換し、qpOASES用の行列を作る関数
void VHIP_CAM_MPC_PG::Set_yqpOASES_mat2(){

    // 評価関数の変換
    qp_solve.N = (H*G).transpose()*Wzmp*H*G + Wu + G.transpose()*Wx*G;
    qp_solve.p = (H*G).transpose()*Wzmp*(H*F*xk - ZMP_ref) + G.transpose()*Wx*F*xk;

    // 制約
    qp_solve.lb = U_min;
    qp_solve.ub = U_max;

    Eigen::VectorXd lbA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::VectorXd ubA = Eigen::VectorXd::Zero(param.Hp * param.Outnum + param.Stanum_AM);
    Eigen::MatrixXd consA = Eigen::MatrixXd::Zero(param.Hp * param.Outnum + param.Stanum_AM, param.Hu * param.Inpnum);
    lbA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_min - H*F * xk;
    ubA.block(0,0,param.Hp * param.Outnum, 1) = ZMP_max - H*F * xk;
    consA.block(0,0,param.Hp * param.Outnum, param.Hu * param.Inpnum)  = H*G;
    Eigen::MatrixXd L = Eigen::MatrixXd::Zero(param.Stanum_AM, param.Stanum_AM*param.Hp);
    L.block(0, param.Stanum_AM*param.Hp-param.Stanum_AM, param.Stanum_AM, param.Stanum_AM) = Eigen::MatrixXd::Identity(param.Stanum_AM,param.Stanum_AM);
    Eigen::VectorXd x_e_ref = Eigen::VectorXd::Zero(param.Stanum_AM);
    x_e_ref << ref.y_e, 0.0, 0.0, 0.0, 0.0;
    lbA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_e_ref - L*F*xk;
    ubA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, 1) = x_e_ref - L*F*xk;
    consA.block(param.Hp * param.Outnum, 0, param.Stanum_AM, param.Hu * param.Inpnum)  = L*G;
    qp_solve.lbA = lbA;
    qp_solve.ubA = ubA;
    qp_solve.consA = consA;

}
} // namespace melew3