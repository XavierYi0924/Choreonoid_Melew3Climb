/**
 * @file MELEW3_kinematics.h
 * @author Taisei Suzuki
 * @brief
 * @version 1.0
 * @date 2022-05-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MELEW3_KINEMATICS_H_
#define MELEW3_KINEMATICS_H_

#include <ros/ros.h>

#include <Eigen/Dense>

namespace melew3_kinematics {

/**
 * @enum JOINT_parallel
 * Joint number of the robot
 */
enum JOINT_parallel {
  LO_MOTOR,  //!< = 0
  LI_MOTOR,  //!< = 1
  RI_MOTOR,  //!< = 2
  RO_MOTOR,  //!< = 3
  JOINT_NUM  //!< = 4
};

/**
 * @enum JOINT_serial
 * Joint number of the simulation
 */
enum JOINT_serial {
  HIP_YAW,        //!< = 0
  HIP_ROLL,       //!< = 1
  HIP_PITCH,      //!< = 2
  KNEE,           //!< = 3
  LEG_JOINT_NUM,  //!< = 4
};

class MELEW3_Kinematics {
private:
  //! 実機のパラメータ
  double l1_parallel, l2_parallel;  //!< リンク長さ[m]，l1, l2

  const double l_A1 = 0.109;  //!< 点A1，点A4の原点Oからの長さ[m]
  const double l_A2 = 0.049;  //!< 点A2，点A3の原点Oからの長さ[m]
  const double l_B1 = 0.097;  //!< 点B1，点B4の原点Oからの長さ[m]
  const double l_B2 = 0.083;  //!< 点B2，点B3の原点Oからの長さ[m]
  const double l_C = 0.0975;  //!< 点C1，点C2の原点Oからの長さ[m]

  Eigen::Vector3d p_b1 = Eigen::Vector3d::Zero();  //!< 点B1の単位ベクトル，{xB1, yB1, zB1}
  Eigen::Vector3d p_b2 = Eigen::Vector3d::Zero();  //!< 点B2の単位ベクトル，{xB2, yB2, zB2}
  Eigen::Vector3d p_b3 = Eigen::Vector3d::Zero();  //!< 点B3の単位ベクトル，{xB3, yB3, zB3}
  Eigen::Vector3d p_b4 = Eigen::Vector3d::Zero();  //!< 点B4の単位ベクトル，{xB4, yB4, zB4}

  Eigen::Vector3d crossB14 = Eigen::Vector3d::Zero();  //!< p_b1とp_b4の外積
  double          dotB14 = 0.0;                        //!< p_b1とp_b4の内積
  Eigen::Vector3d crossB23 = Eigen::Vector3d::Zero();  //!< p_b2とp_b3の外積
  double          dotB23 = 0.0;                        //!< p_b2とp_b3の内積

  Eigen::Vector3d p_D1 = Eigen::Vector3d::Zero();  //!< 点D1の座標，{xD1, yD1, zD1}
  Eigen::Vector3d p_D2 = Eigen::Vector3d::Zero();  //!< 点D2の座標，{xD2, yD2, zD2}

  Eigen::VectorXd calc_p_D = Eigen::VectorXd::Zero(6);  //!< p_Dの計算に使用する変数

  const double MAXcosDOD = cos(3.0 / 4.0 * M_PI);  //!< 脚の開き角の最大値の余弦
  const double MINcosDOD = cos(M_PI / 9.0);        //!< 脚の開き角の最小値の余弦
  const double MAX_ANGLE = M_PI / 3.0;             //!< モータ角度の最大値
  const double MIN_ANGLE = -(13.0 / 36.0) * M_PI;  //!< モータ角度の最小値

  //! シミュレーションのパラメータ
  double          l1_serial, l2_serial;  //!< リンク長さ[m]，l1, l2
  Eigen::Vector3d hip_to_knee;           //!< 股関節から膝関節への位置ベクトル
  Eigen::Vector3d knee_to_foot;          //!< 膝関節から脚先への位置ベクトル

public:
  const int LEG_DOF = 4;  //!< 脚の自由度数（↑のenumをpublicに落としてもいいかも？）
  const int LEG_NUM = 4;  //!< 脚の本数 (L,Rとしてenumで定義するのもアリ)

  MELEW3_Kinematics();                                //!< デフォルトコンストラクタ
  MELEW3_Kinematics(double, double, double, double);  //!< コンストラクタ

  void init(double, double, double, double);  //!< 各パラメータの初期化

  bool solve_FK_parallel(const Eigen::VectorXd&, Eigen::Vector3d&, double&);  //!< 順運動学計算（実機用）
  bool solve_FK_parallel(const int leg_num, const Eigen::VectorXd& q, Eigen::Vector3d& p,
                         double& psi);  //!< 順運動学計算（実機用，脚番号指定）
  bool solve_IK_parallel(const Eigen::Vector3d&, const double&,
                         Eigen::VectorXd&);  //!< 逆運動学計算（実機用）
  bool solve_IK_parallel(const int leg_num, const Eigen::Vector3d& p, const double& psi,
                         Eigen::VectorXd& q);  //!< 逆運動学計算（実機用，脚番号指定）
  bool solve_FK_serial(const Eigen::VectorXd&, Eigen::Vector3d&, double&);  //!< 順運動学計算（シミュレーション用）
  bool solve_IK_serial(const Eigen::Vector3d&, const double&,
                       Eigen::VectorXd&);  //!< 逆運動学計算（シミュレーション用）
  bool solve_IK_serial(const int leg_num, const Eigen::Vector3d& p, const double& psi,
                       Eigen::VectorXd& q);  //!< 逆運動学計算（シミュレーション用，脚番号指定）
  bool solve_link_position_parallel(const Eigen::VectorXd& q, Eigen::Vector3d& p, double& psi,
                                    std::vector<Eigen::Vector3d>& p_link,
                                    std::vector<double>& q_link);  //!< 各リンクの位置と関節角の計算（実機用）
  bool solve_link_position_parallel(
      const int leg_num, const Eigen::VectorXd& q, Eigen::Vector3d& p, double& psi,
      std::vector<Eigen::Vector3d>& _p_link,
      std::vector<double>& _q_link);  //!< 各リンクの位置と関節角の計算（シミュレーション用）

  bool solve_link_position_serial(const Eigen::VectorXd& q, Eigen::Vector3d& p, double& psi,
                                  std::vector<Eigen::Vector3d>& p_link,
                                  std::vector<double>& q_link);  //!< 各リンクの位置と関節角の計算（シミュレーション用）

  //! 回転行列関係
  Eigen::Matrix3d RotX(double q);
  Eigen::Matrix3d RotY(double q);
  Eigen::Matrix3d RotZ(double q);
};
}  // namespace melew3_kinematics
#endif