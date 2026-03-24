/**
 * @file    utils.cpp
 * @author  Yuta Ishizawa
 * @brief   よく使う関数群をまとめたプログラム
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/MELEW3_control/utils.hpp"

namespace Utils {
/**
 * @brief Point型からVector2d型へ変換
 *
 * @param point_data  Point型
 * @param vector_data Vector2d型
 */
void Utils::PointToVector2d(const geometry_msgs::Point point_data, Eigen::Vector2d& vector_data) {
  vector_data.x() = point_data.x;
  vector_data.y() = point_data.y;
}

/**
 * @brief Point型からVector3d型へ変換
 *
 * @param point_data  Point型
 * @param vector_data Vector3d型
 */
void Utils::PointToVector3d(const geometry_msgs::Point point_data, Eigen::Vector3d& vector_data) {
  vector_data.x() = point_data.x;
  vector_data.y() = point_data.y;
  vector_data.z() = point_data.z;
}

/**
 * @brief leg_pose型からVector型へ変換
 *
 * @param point_data  leg_pose型
 * @param vector_data Vector型
 * @param yaw_data yaw角
 */
void Utils::LegposeToVector3d(const melew3_msgs::leg_pose leg_pose_data, Eigen::Vector3d& vector_data,
                              double& yaw_data) {
  PointToVector3d(leg_pose_data.point, vector_data);
  yaw_data = leg_pose_data.yaw.data;
}

/**
 * @brief WrenchStamped型からVector型へ変換
 *
 * @param ft_sensor   WrenchStamped型
 * @param force_data  力のVector型
 * @param moment_data モーメントのVector型
 */
void Utils::WrenchToVector3d(const geometry_msgs::Wrench ft_sensor, Eigen::Vector3d& force_data,
                             Eigen::Vector3d& moment_data) {
  force_data.x() = ft_sensor.force.x;
  force_data.y() = ft_sensor.force.y;
  force_data.z() = ft_sensor.force.z;
  moment_data.x() = ft_sensor.torque.x;
  moment_data.y() = ft_sensor.torque.y;
  moment_data.z() = ft_sensor.torque.z;
}

/**
 * @brief geometry_msgs型のTwistからEigenに変換
 *
 * @param T
 * @param w
 * @param v
 */
void Utils::Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w, Eigen::Vector3d& v) {
  w.x() = T.angular.x;
  w.y() = T.angular.y;
  w.z() = T.angular.z;

  v.x() = T.linear.x;
  v.y() = T.linear.y;
  v.z() = T.linear.z;
}

/**
 * @brief geometry_msgs型のTwistからEigenに変換
 *
 * @param T
 * @param w
 */
void Utils::Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w) {
  w.x() = T.angular.x;
  w.y() = T.angular.y;
  w.z() = T.angular.z;
}

/**
 * @brief JointState型からVector型へ変換
 *
 * @param joint_states_data    JointState型
 * @param left_leg_motor_data  左脚のVector型
 * @param right_leg_motor_data 右脚のVector型
 * @param wheel_pos_data       車輪のVector型
 */
void Utils::JointStateToVector(const sensor_msgs::JointState joint_states_data, Eigen::VectorXd& left_leg_motor_data,
                               Eigen::VectorXd& right_leg_motor_data, Eigen::Vector2d& wheel_pos_data) {
  if (joint_states_data.position.size() >= 10) {
    left_leg_motor_data[0] = joint_states_data.position[0];
    left_leg_motor_data[1] = joint_states_data.position[1];
    left_leg_motor_data[2] = joint_states_data.position[2];
    left_leg_motor_data[3] = joint_states_data.position[3];
    right_leg_motor_data[0] = joint_states_data.position[4];
    right_leg_motor_data[1] = joint_states_data.position[5];
    right_leg_motor_data[2] = joint_states_data.position[6];
    right_leg_motor_data[3] = joint_states_data.position[7];
    wheel_pos_data[0] = joint_states_data.position[8];
    wheel_pos_data[1] = joint_states_data.position[9];
  }
}

/**
 * @brief JointState型から車輪の回転角を取得
 *
 * @param joint_states   JointState型
 * @param wheel_pos_data 車輪の回転角
 */
void Utils::JointStateToWheelVector(const sensor_msgs::JointState joint_states, Eigen::Vector2d& wheel_pos_data) {
  if (joint_states.position.size() >= 10) {
    wheel_pos_data[0] = joint_states.position[8];
    wheel_pos_data[1] = joint_states.position[9];
  }
}

/**
 * @brief Vector2d型からPoint型へ変換
 *
 * @param vector_data Vector型
 * @param point_data  Point型
 */
void Utils::Vector2dToPoint(const Eigen::Vector2d vector_data, geometry_msgs::Point& point_data) {
  point_data.x = vector_data.x();
  point_data.y = vector_data.y();
  point_data.z = 0.0;
}

/**
 * @brief Vector3d型からPoint型へ変換
 *
 * @param vector_data Vector型
 * @param point_data  Point型
 */
void Utils::Vector3dToPoint(const Eigen::Vector3d vector_data, geometry_msgs::Point& point_data) {
  point_data.x = vector_data.x();
  point_data.y = vector_data.y();
  point_data.z = vector_data.z();
}

/**
 * @brief Vector型からleg_pose型へ変換
 *
 * @param vector_data Vector型
 * @param yaw_data yaw角
 * @param point_data  leg_pose型
 */
void Utils::Vector3dToLegpose(const Eigen::Vector3d vector_data, const double yaw_data,
                              melew3_msgs::leg_pose& leg_pose_data) {
  Vector3dToPoint(vector_data, leg_pose_data.point);
  leg_pose_data.yaw.data = yaw_data;
}

/**
 * @brief Vector型からLinkInfoArray型へ変換
 *
 * @param position_data        Vector型の位置
 * @param orientation_data     Matrix型の姿勢（回転行列）
 * @param linear_data          Vector型の速度
 * @param angular_data         Vector型の角速度
 * @param link_info_array_data LinkInfoArray型のデータ
 */

void Utils::VectorToLinkInfoArray(const std::vector<Eigen::Vector3d> position_data,
                                  const std::vector<Eigen::Matrix3d> orientation_data,
                                  const std::vector<Eigen::Vector3d> linear_data,
                                  const std::vector<Eigen::Vector3d> angular_data,
                                  melew3_msgs::LinkInfoArray&        link_info_array_data) {
  for (int i = 0; i < link_info_array_data.position.size(); i++) {
    link_info_array_data.position[i].position.x = position_data[i].x();
    link_info_array_data.position[i].position.y = position_data[i].y();
    link_info_array_data.position[i].position.z = position_data[i].z();

    Eigen::Quaterniond q;
    q = orientation_data[i];

    link_info_array_data.position[i].orientation.w = q.w();
    link_info_array_data.position[i].orientation.x = q.x();
    link_info_array_data.position[i].orientation.y = q.y();
    link_info_array_data.position[i].orientation.z = q.z();

    link_info_array_data.velocity[i].linear.x = linear_data[i].x();
    link_info_array_data.velocity[i].linear.y = linear_data[i].y();
    link_info_array_data.velocity[i].linear.z = linear_data[i].z();

    link_info_array_data.velocity[i].angular.x = angular_data[i].x();
    link_info_array_data.velocity[i].angular.y = angular_data[i].y();
    link_info_array_data.velocity[i].angular.z = angular_data[i].z();
  }
}

/**
 * @brief QuaternionStamped型からQuaterniond型へ変換
 *
 * @param quat_geometry_data QuaternionStamped型
 * @param quat_eigen_data    Quaterniond型
 */
void Utils::QuatstampToQuatd(const geometry_msgs::QuaternionStamped quat_geometry_data,
                             Eigen::Quaterniond&                    quat_eigen_data) {
  quat_eigen_data.x() = quat_geometry_data.quaternion.x;
  quat_eigen_data.y() = quat_geometry_data.quaternion.y;
  quat_eigen_data.z() = quat_geometry_data.quaternion.z;
  quat_eigen_data.w() = quat_geometry_data.quaternion.w;
}

/**
 * @brief クォータニオンから回転行列に変換
 *
 * @param quat_data       クォータニオン
 * @param rot_matrix_data 回転行列
 */
void Utils::QuatToRot(const Eigen::Quaterniond quat_data, Eigen::Matrix3d& rot_matrix_data) {
  double m11, m12, m13, m21, m22, m23, m31, m32, m33;
  m11 = 2 * quat_data.w() * quat_data.w() + 2 * quat_data.x() * quat_data.x() - 1;
  m12 = 2 * quat_data.x() * quat_data.y() - 2 * quat_data.z() * quat_data.w();
  m13 = 2 * quat_data.x() * quat_data.z() + 2 * quat_data.y() * quat_data.w();
  m21 = 2 * quat_data.x() * quat_data.y() + 2 * quat_data.z() * quat_data.w();
  m22 = 2 * quat_data.w() * quat_data.w() + 2 * quat_data.y() * quat_data.y() - 1;
  m23 = 2 * quat_data.y() * quat_data.z() - 2 * quat_data.x() * quat_data.w();
  m31 = 2 * quat_data.x() * quat_data.z() - 2 * quat_data.y() * quat_data.w();
  m32 = 2 * quat_data.y() * quat_data.z() + 2 * quat_data.x() * quat_data.w();
  m33 = 2 * quat_data.w() * quat_data.w() + 2 * quat_data.z() * quat_data.z() - 1;

  rot_matrix_data << m11, m12, m13, m21, m22, m23, m31, m32, m33;
}

/**
 * @brief クォータニオンからオイラー角に変換
 *
 * @param quat_data  クォータニオン
 * @param euler_data オイラー角
 */
void Utils::QuatToEuler(const Eigen::Quaterniond quat_data, Eigen::Vector3d& euler_data) {
  double q0q0 = quat_data.x() * quat_data.x();
  double q0q1 = quat_data.x() * quat_data.y();
  double q0q2 = quat_data.x() * quat_data.z();
  double q0q3 = quat_data.x() * quat_data.w();
  double q1q1 = quat_data.y() * quat_data.y();
  double q1q2 = quat_data.y() * quat_data.z();
  double q1q3 = quat_data.y() * quat_data.w();
  double q2q2 = quat_data.z() * quat_data.z();
  double q2q3 = quat_data.z() * quat_data.w();
  double q3q3 = quat_data.w() * quat_data.w();

  euler_data.x() = atan2(2.0 * (q2q3 + q0q1), q0q0 - q1q1 - q2q2 + q3q3);
  euler_data.y() = asin(2.0 * (q0q2 - q1q3));
  euler_data.z() = atan2(2.0 * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3);
}

/**
 * @brief geometry_msgs型のPoseからEigenに変換
 *
 * @param pose Pose型
 * @param p    Vector3d型
 * @param R    Matrix3d型
 */
void Utils::PoseToMatrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p, Eigen::Matrix3d& R) {
  p.x() = pose.position.x;
  p.y() = pose.position.y;
  p.z() = pose.position.z;

  Eigen::Quaterniond q;
  q.x() = pose.orientation.x;
  q.y() = pose.orientation.y;
  q.z() = pose.orientation.z;
  q.w() = pose.orientation.w;

  R = q.normalized().toRotationMatrix();
}

/**
 * @brief geometry_msgs型のPoseからEigenに変換
 *
 * @param pose Pose型
 * @param R    Matrix3d型
 */
void Utils::PoseToMatrix(const geometry_msgs::Pose pose, Eigen::Matrix3d& R) {
  Eigen::Quaterniond q;
  q.x() = pose.orientation.x;
  q.y() = pose.orientation.y;
  q.z() = pose.orientation.z;
  q.w() = pose.orientation.w;

  R = q.normalized().toRotationMatrix();
}

/**
 * @brief geometry_msgs型のPoseからEigenに変換
 *
 * @param pose Pose型
 * @param p    Vector3d型
 */
void Utils::PoseToMatrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p) {
  p.x() = pose.position.x;
  p.y() = pose.position.y;
  p.z() = pose.position.z;
}

/**
 * @brief 3次元ベクトルから歪対象行列を作成
 *
 * @param vec ベクトル
 * @param ssm 歪対象行列
 */
void Utils::VectorToSkewSymmetricMatrix(const Eigen::Vector3d vec, Eigen::Matrix3d& ssm) {
  ssm(0, 0) = 0.0;
  ssm(0, 1) = -vec.z();
  ssm(0, 2) = vec.y();
  ssm(1, 0) = vec.z();
  ssm(1, 1) = 0.0;
  ssm(1, 2) = -vec.x();
  ssm(2, 0) = -vec.y();
  ssm(2, 1) = vec.x();
  ssm(2, 2) = 0.0;
}

/**
 * @brief 5次多項式補間の係数を計算する関数（1次元）
 *
 */
void Five_Spline::Calc_Spline(std::vector<point>& point_data) {
  current_data_num = point_.size();                                   // 現在のデータ点の個数を保存
  point_.insert(point_.end(), point_data.begin(), point_data.end());  // 経由点データを追加

  /*** 各区間の係数を計算 ***/
  for (int i = std::max(current_data_num, 1); i < point_.size(); i++) {
    /*** パラメータの代入 ***/
    x_s = point_[i - 1].x;                      // 始点位置（1次元）
    dx_s = point_[i - 1].dx;                    // 始点速度（1次元）
    ddx_s = point_[i - 1].ddx;                  // 始点加速度（1次元）
    x_e = point_[i].x;                          // 終点位置（1次元）
    dx_e = point_[i].dx;                        // 終点速度（1次元）
    ddx_e = point_[i].ddx;                      // 終点加速度（1次元）
    t_w = point_[i].time - point_[i - 1].time;  // 補間時間

    /*** 係数の計算 ***/
    A1 = x_e - x_s - dx_s * t_w - 0.5 * ddx_s * t_w * t_w;
    A2 = dx_e - dx_s - ddx_s * t_w;
    A3 = ddx_e - ddx_s;

    n0.push_back(x_s);
    n1.push_back(dx_s);
    n2.push_back(0.5 * ddx_s);
    n3.push_back((10.0 * A1) / pow(t_w, 3) - (4.0 * A2) / pow(t_w, 2) + A3 / (2.0 * t_w));
    n4.push_back((-15.0 * A1) / pow(t_w, 4) + (7.0 * A2) / pow(t_w, 3) - A3 / pow(t_w, 2));
    n5.push_back((6.0 * A1) / pow(t_w, 5) - (3.0 * A2) / pow(t_w, 4) + A3 / (2.0 * pow(t_w, 3)));
  }
}

/**
 * @brief 5次多項式補間の係数を計算する関数（3次元）
 *
 */
void Five_Spline::Calc_Spline3(std::vector<point3>& point3_data) {
  current_data_num = point3_.size();                                      // 現在のデータ点の個数を保存
  point3_.insert(point3_.end(), point3_data.begin(), point3_data.end());  // 経由点データを追加

  /*** 各区間の係数を計算 ***/
  for (int i = std::max(current_data_num, 1); i < point3_.size(); i++) {
    /*** パラメータの代入 ***/
    x3_s = point3_[i - 1].x;                      // 始点位置（3次元）
    dx3_s = point3_[i - 1].dx;                    // 始点速度（3次元）
    ddx3_s = point3_[i - 1].ddx;                  // 始点加速度（3次元）
    x3_e = point3_[i].x;                          // 終点位置（3次元）
    dx3_e = point3_[i].dx;                        // 終点速度（3次元）
    ddx3_e = point3_[i].ddx;                      // 終点加速度（3次元）
    t_w = point3_[i].time - point3_[i - 1].time;  // 補間時間

    /*** 係数の計算 ***/
    A1_3d = x3_e - x3_s - dx3_s * t_w - 0.5 * ddx3_s * t_w * t_w;
    A2_3d = dx3_e - dx3_s - ddx3_s * t_w;
    A3_3d = ddx3_e - ddx3_s;

    n0_3d.push_back(x3_s);
    n1_3d.push_back(dx3_s);
    n2_3d.push_back(0.5 * ddx3_s);
    n3_3d.push_back((10.0 * A1_3d) / pow(t_w, 3) - (4.0 * A2_3d) / pow(t_w, 2) + A3_3d / (2.0 * t_w));
    n4_3d.push_back((-15.0 * A1_3d) / pow(t_w, 4) + (7.0 * A2_3d) / pow(t_w, 3) - A3_3d / pow(t_w, 2));
    n5_3d.push_back((6.0 * A1_3d) / pow(t_w, 5) - (3.0 * A2_3d) / pow(t_w, 4) + A3_3d / (2.0 * pow(t_w, 3)));
  }
}

/**
 * @brief 5次多項式で補間した位置を出力する関数（1次元）
 *
 * @param current_time 現在時刻
 */
double Five_Spline::Get_Spline_x(double current_time) {
  /*** どの区間の補間曲線を使用するか判定 ***/
  while ((current_time - point_[count + 1].time > 0.0) && (count < point_.size())) count++;

  /*** 現在時刻における位置の計算 ***/
  T = current_time - point_[count].time;
  return n5[count] * pow(T, 5) + n4[count] * pow(T, 4) + n3[count] * pow(T, 3) + n2[count] * pow(T, 2) + n1[count] * T +
         n0[count];
}

/**
 * @brief 5次多項式で補間した位置を出力する関数（3次元）
 *
 * @param current_time 現在時刻
 */
Eigen::Vector3d Five_Spline::Get_Spline3_x(double current_time) {
  /*** どの区間の補間曲線を使用するか判定 ***/
  while ((current_time - point3_[count3 + 1].time > 0.0) && (count3 < point_.size())) count3++;

  /*** 現在時刻における位置の計算 ***/
  T = current_time - point3_[count3].time;
  return n5_3d[count3] * pow(T, 5) + n4_3d[count3] * pow(T, 4) + n3_3d[count3] * pow(T, 3) + n2_3d[count3] * pow(T, 2) +
         n1_3d[count3] * T + n0_3d[count3];
}

/**
 * @brief 5次多項式で補間した速度を出力する関数（1次元）
 *
 * @param current_time 現在時刻
 */
double Five_Spline::Get_Spline_dx(double current_time) {
  /*** どの区間の補間曲線を使用するか判定 ***/
  while ((current_time - point_[count + 1].time > 0.0) && (count < point_.size())) count++;

  /*** 現在時刻における速度の計算 ***/
  T = current_time - point_[count].time;
  return 5.0 * n5[count] * pow(T, 4) + 4.0 * n4[count] * pow(T, 3) + 3.0 * n3[count] * pow(T, 2) + 2.0 * n2[count] * T +
         n1[count];
}

/**
 * @brief 5次多項式で補間した速度を出力する関数（3次元）
 *
 * @param current_time 現在時刻
 */
Eigen::Vector3d Five_Spline::Get_Spline3_dx(double current_time) {
  /*** どの区間の補間曲線を使用するか判定 ***/
  while ((current_time - point3_[count3 + 1].time > 0.0) && (count3 < point3_.size())) count3++;

  /*** 現在時刻における速度の計算 ***/
  T = current_time - point3_[count3].time;
  return 5.0 * n5_3d[count3] * pow(T, 4) + 4.0 * n4_3d[count3] * pow(T, 3) + 3.0 * n3_3d[count3] * pow(T, 2) +
         2.0 * n2_3d[count3] * T + n1_3d[count3];
}

/**
 * @brief 5次多項式で補間した加速度を出力する関数（1次元）
 *
 * @param current_time 現在時刻
 */
double Five_Spline::Get_Spline_ddx(double current_time) {
  /*** どの区間の補間曲線を使用するか判定 ***/
  while ((current_time - point_[count + 1].time > 0.0) && (count < point_.size())) count++;

  /*** 現在時刻における速度の計算 ***/
  T = current_time - point_[count].time;
  return 20.0 * n5[count] * pow(T, 3) + 12.0 * n4[count] * pow(T, 2) + 6.0 * n3[count] * T + 2.0 * n2[count];
}

/**
 * @brief 5次多項式で補間した加速度を出力する関数（3次元）
 *
 * @param current_time 現在時刻
 */
Eigen::Vector3d Five_Spline::Get_Spline3_ddx(double current_time) {
  /*** どの区間の補間曲線を使用するか判定 ***/
  while ((current_time - point3_[count3 + 1].time > 0.0) && (count3 < point3_.size())) count3++;

  /*** 現在時刻における速度の計算 ***/
  T = current_time - point3_[count3].time;
  return 20.0 * n5_3d[count3] * pow(T, 3) + 12.0 * n4_3d[count3] * pow(T, 2) + 6.0 * n3_3d[count3] * T +
         2.0 * n2_3d[count3];
}

}  // namespace Utils