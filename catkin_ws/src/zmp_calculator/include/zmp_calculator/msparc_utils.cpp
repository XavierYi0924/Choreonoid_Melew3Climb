#include "msparc_utils.hpp"

namespace mUtil {
/**
 * @brief PointをVectorに変換する
 *
 * @param point
 * @param p
 */
void MsparcUtils::Point2Vector(const geometry_msgs::Point point, Eigen::Vector3d& p) {
  p.x() = point.x;
  p.y() = point.y;
  p.z() = point.z;
}

/**
 * @brief geometry_msgs型のPoseからEigenに変換する
 *
 * @param pose
 * @param p
 * @param R
 */
void MsparcUtils::Pose2Matrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p, Eigen::Matrix3d& R) {
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
 * @brief geometry_msgs型のPoseからEigenに変換する
 *
 * @param pose
 * @param R
 */
void MsparcUtils::Pose2Matrix(const geometry_msgs::Pose pose, Eigen::Matrix3d& R) {
  Eigen::Quaterniond q;
  q.x() = pose.orientation.x;
  q.y() = pose.orientation.y;
  q.z() = pose.orientation.z;
  q.w() = pose.orientation.w;

  R = q.normalized().toRotationMatrix();
}

/**
 * @brief geometry_msgs型のPoseからEigenに変換する
 *
 * @param pose
 * @param p
 */
void MsparcUtils::Pose2Matrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p) {
  p.x() = pose.position.x;
  p.y() = pose.position.y;
  p.z() = pose.position.z;
}

/**
 * @brief geometry_msgs型のTwistからEigenに変換
 *
 * @param T
 * @param w
 * @param v
 */
void MsparcUtils::Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w, Eigen::Vector3d& v) {
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
void MsparcUtils::Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w) {
  w.x() = T.angular.x;
  w.y() = T.angular.y;
  w.z() = T.angular.z;
}

/**
 * @brief 3次元ベクトルから歪対象行列を作成する
 *
 * @param vec
 * @param ssm
 */
void MsparcUtils::Vector2SkewSymmetricMatrix(const Eigen::Vector3d vec, Eigen::Matrix3d& ssm) {
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
 * @brief geometry_msgs::Wrench型からEigenのVectorに変換する
 *
 * @param wrench
 * @param vec_f
 * @param vec_m
 */
void MsparcUtils::WrenchToVector3d(const geometry_msgs::Wrench wrench, Eigen::Vector3d& vec_f, Eigen::Vector3d& vec_m) {
  vec_f.x() = wrench.force.x;
  vec_f.y() = wrench.force.y;
  vec_f.z() = wrench.force.z;

  vec_m.x() = wrench.torque.x;
  vec_m.y() = wrench.torque.y;
  vec_m.z() = wrench.torque.z;
}

/**
 * @brief QuaternionからEigenのMatrixに変換する
 *
 * @param q
 * @param R
 */
void MsparcUtils::Quaternion2Matrix(const geometry_msgs::Quaternion q, Eigen::Matrix3d& R) {
  Eigen::Quaterniond eq;
  eq.x() = q.x;
  eq.y() = q.y;
  eq.z() = q.z;
  eq.w() = q.w;

  R = eq.normalized().toRotationMatrix();
}

void MsparcUtils::Vector3ToEigenVector(const geometry_msgs::Vector3 v, Eigen::Vector3d& ev) {
  ev.x() = v.x;
  ev.y() = v.y;
  ev.z() = v.z;
}

}  // namespace mUtil