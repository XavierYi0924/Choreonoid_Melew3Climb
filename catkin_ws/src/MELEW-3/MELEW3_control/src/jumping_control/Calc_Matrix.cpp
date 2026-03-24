#include <MELEW3_control/Calc_Matrix.hpp>

namespace MELEW3_control {
// 行列のn乗を計算する関数
Eigen::MatrixXd PowMat(Eigen::MatrixXd A, int i){
    if (A.rows() != A.cols()){
        std::cout << "正方行列でないため計算できません" << std::endl; 
        return A;
    }
    Eigen::MatrixXd B = Eigen::MatrixXd::Identity(A.rows(),A.cols());
    for ( int j = 0; j < i; j++){
        B = B * A;
    }
    return B;
}

// 交代行列に変換する関数
Eigen::Matrix3d Alternative(Eigen::Vector3d a){

    Eigen::Matrix3d a_alter;
    a_alter << 0.0, -a.z(),  a.y(),
             a.z(),    0.0, -a.x(),
            -a.y(),  a.x(),    0.0;

    return a_alter;

}

// 2項積を計算する関数
Eigen::Matrix3d Dyadic(Eigen::Vector3d a){

    // 交代行列、歪対称行列に変換
    Eigen::Matrix3d a_alter = Alternative(a);
    
    return a_alter.transpose() * a_alter;

}

// 一般化逆行列を計算する関数
Eigen::MatrixXd Generalized_Inverse(Eigen::MatrixXd A){

    // std::cout << "A: " << std::endl << A << std::endl;
    Eigen::JacobiSVD<Eigen::MatrixXd> SVD(A, Eigen::ComputeFullU | Eigen::ComputeFullV);
    // std::cout << "U: " <<  std::endl << SVD.matrixU() << std::endl;
    // std::cout << "S: " <<  std::endl << SVD.singularValues()  << std::endl;
    // std::cout << "V: " <<  std::endl << SVD.matrixV() << std::endl;

    Eigen::VectorXd S = SVD.singularValues();
    S = S.array().inverse();

    // 一般化逆行列の変数名は Ainv 
    Eigen::MatrixXd Ainv = SVD.matrixV() * S.asDiagonal()  * SVD.matrixU().transpose();

    // A と A+ をかけると単位行列になる
    // Eigen::MatrixXd check = Ainv * A;
    // std::cout << "check" << std::endl << check << std::endl;

    return Ainv;

}

// ヒューマノイドロボット、p.85
Eigen::Vector3d Rot_to_w(Eigen::Matrix3d R){

    Eigen::Vector3d e1;
    e1 << R(2,1) - R(1,2), R(0,2) - R(2,0), R(1,0) - R(0,1);
    double norm_e1 = sqrt(e1(0)*e1(0) + e1(1)*e1(1) + e1(2)*e1(2));

    Eigen::Vector3d ans;
    if (norm_e1 > 1e-10){
        ans = ( atan2(norm_e1, R(0,0) + R(1,1) + R(2,2) - 1.0 ) / norm_e1 ) * e1;
    }
    else if ((R(0,0) > 0.0) && (R(1,1) > 0.0) && (R(2,2) > 0.0)){
        ans = Eigen::Vector3d::Zero();
    }
    else{
        Eigen::Vector3d r;
        r << R(0,0)+1.0, R(1,1)+1.0, R(2,2)+1.0;
        ans = M_PI/2.0 * r;
    }

    return ans;

}

void PrintMat(const char *str, double a){

    std::string print(str);

    std::cout << print << std::endl << a << std::endl;

}

void PrintMat(const char *str, Eigen::MatrixXd A){

    std::string print(str);

    std::cout << print << std::endl << A << std::endl;

}
} // namespace melew3