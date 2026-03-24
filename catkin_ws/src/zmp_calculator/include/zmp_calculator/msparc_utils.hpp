#pragma once

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Wrench.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace mUtil {
class MsparcUtils {
public:
  void Pose2Matrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p, Eigen::Matrix3d& R);
  void Pose2Matrix(const geometry_msgs::Pose pose, Eigen::Matrix3d& R);
  void Pose2Matrix(const geometry_msgs::Pose pose, Eigen::Vector3d& p);
  void Point2Vector(const geometry_msgs::Point point, Eigen::Vector3d& p);
  void Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w, Eigen::Vector3d& v);
  void Twist2Vector(const geometry_msgs::Twist T, Eigen::Vector3d& w);
  void Vector2SkewSymmetricMatrix(const Eigen::Vector3d vec, Eigen::Matrix3d& ssm);
  void WrenchToVector3d(const geometry_msgs::Wrench wrench, Eigen::Vector3d& vec_f, Eigen::Vector3d& vec_m);
  void Quaternion2Matrix(const geometry_msgs::Quaternion q, Eigen::Matrix3d& R);
  void Vector3ToEigenVector(const geometry_msgs::Vector3 v, Eigen::Vector3d& ev);
};
}  // namespace mUtil