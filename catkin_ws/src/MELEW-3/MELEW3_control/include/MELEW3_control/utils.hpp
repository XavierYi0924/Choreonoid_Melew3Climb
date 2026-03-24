/**
 * @file    utils.hpp
 * @author  Yuta Ishizawa
 * @brief   よく使う関数群をまとめたプログラムのヘッダ
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Wrench.h>
#include <melew3_msgs/LinkInfoArray.h>
#include <melew3_msgs/leg_pose.h>
#include <sensor_msgs/JointState.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace Utils {
class Utils {
public:
  void PointToVector2d(const geometry_msgs::Point point_data, Eigen::Vector2d& vector_data);
  void PointToVector3d(const geometry_msgs::Point point_data, Eigen::Vector3d& vector_data);
  void LegposeToVector3d(const melew3_msgs::leg_pose leg_pose_data, Eigen::Vector3d& vector_data, double& yaw_data);
  void WrenchToVector3d(const geometry_msgs::Wrench ft_sensor, Eigen::Vector3d& force_data,
                        Eigen::Vector3d& moment_data);
  void Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w, Eigen::Vector3d& v);
  void Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w);
  void JointStateToVector(const sensor_msgs::JointState joint_states_data, Eigen::VectorXd& left_leg_motor_data,
                          Eigen::VectorXd& right_leg_motor_data, Eigen::Vector2d& wheel_pos_data);
  void JointStateToWheelVector(const sensor_msgs::JointState joint_states, Eigen::Vector2d& wheel_pos_data);

  void Vector2dToPoint(const Eigen::Vector2d vector_data, geometry_msgs::Point& point_data);
  void Vector3dToPoint(const Eigen::Vector3d vector_data, geometry_msgs::Point& point_data);
  void Vector3dToLegpose(const Eigen::Vector3d vector_data, const double yaw_data,
                         melew3_msgs::leg_pose& leg_pose_data);
  void VectorToLinkInfoArray(const std::vector<Eigen::Vector3d> position_data,
                             const std::vector<Eigen::Matrix3d> orientation_data,
                             const std::vector<Eigen::Vector3d> linear_data,
                             const std::vector<Eigen::Vector3d> angular_data,
                             melew3_msgs::LinkInfoArray&        link_info_array_data);

  void QuatstampToQuatd(const geometry_msgs::QuaternionStamped quat_geometry_data, Eigen::Quaterniond& quat_eigen_data);
  void QuatToRot(const Eigen::Quaterniond quat_data, Eigen::Matrix3d& rot_matrix_data);
  void QuatToEuler(const Eigen::Quaterniond quat_data, Eigen::Vector3d& euler_data);

  void PoseToMatrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p, Eigen::Matrix3d& R);
  void PoseToMatrix(const geometry_msgs::Pose pose, Eigen::Matrix3d& R);
  void PoseToMatrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p);

  void VectorToSkewSymmetricMatrix(const Eigen::Vector3d vec, Eigen::Matrix3d& ssm);
};

/*** 5次多項式補間用クラス ***/
class Five_Spline {
public:
  /*** 経由点のパラメータ（1次元）***/
  typedef struct {
    double time;  //!< 時刻
    double x;     //!< 位置（1次元）
    double dx;    //!< 速度（1次元）
    double ddx;   //!< 加速度（1次元）
  } point;

  /*** 経由点のパラメータ（3次元）***/
  typedef struct {
    double          time;  //!< 時刻
    Eigen::Vector3d x;     //!< 位置（3次元）
    Eigen::Vector3d dx;    //!< 速度（3次元）
    Eigen::Vector3d ddx;   //!< 加速度（3次元）
  } point3;

  void Calc_Spline(std::vector<point>& point_data);  //!< 5次多項式補間の係数を計算する関数（1次元）
  double Get_Spline_x(double current_time);   //!< 5次多項式で補間した位置を出力する関数（1次元）
  double Get_Spline_dx(double current_time);  //!< 5次多項式で補間した速度を出力する関数（1次元）
  double Get_Spline_ddx(double current_time);  //!< 5次多項式で補間した加速度を出力する関数（1次元）
  void Calc_Spline3(std::vector<point3>& point3_data);  //!< 5次多項式補間の係数を計算する関数（3次元）
  Eigen::Vector3d Get_Spline3_x(double current_time);  //!< 5次多項式で補間した位置を出力する関数（3次元）
  Eigen::Vector3d Get_Spline3_dx(double current_time);  //!< 5次多項式で補間した速度を出力する関数（3次元）
  Eigen::Vector3d Get_Spline3_ddx(double current_time);  //!< 5次多項式で補間した加速度を出力する関数（3次元）

private:
  /*** 始点・終点パラメータ ***/
  double          x_s;     //!< 始点位置（1次元）
  double          x_e;     //!< 終点位置（1次元）
  Eigen::Vector3d x3_s;    //!< 始点位置（3次元）
  Eigen::Vector3d x3_e;    //!< 終点位置（3次元）
  double          dx_s;    //!< 始点速度（1次元）
  double          dx_e;    //!< 終点速度（1次元）
  Eigen::Vector3d dx3_s;   //!< 始点速度（3次元）
  Eigen::Vector3d dx3_e;   //!< 終点速度（3次元）
  double          ddx_s;   //!< 始点加速度（1次元）
  double          ddx_e;   //!< 終点加速度（1次元）
  Eigen::Vector3d ddx3_s;  //!< 始点加速度（3次元）
  Eigen::Vector3d ddx3_e;  //!< 終点加速度（3次元）
  double          t_w;     //!< 補間時間

  double T;  //!< 経過時間

  int current_data_num = 0;  //!< 現在のデータ点の個数を保存する変数
  int count = 0;             //!< 最後の経由点のインデックスを保存する変数（1次元）
  int count3 = 0;            //!< 最後の経由点のインデックスを保存する変数（3次元）

  std::vector<point>  point_;   //!< 経由点の構造体を保存するベクトル（1次元）
  std::vector<point3> point3_;  //!< 経由点の構造体を保存するベクトル（3次元）

  /*** 係数 ***/
  std::vector<double>          n0, n1, n2, n3, n4, n5;
  std::vector<Eigen::Vector3d> n0_3d, n1_3d, n2_3d, n3_3d, n4_3d, n5_3d;
  double                       A1, A2, A3;
  Eigen::Vector3d              A1_3d, A2_3d, A3_3d;
};

}  // namespace Utils