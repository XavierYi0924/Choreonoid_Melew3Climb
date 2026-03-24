/**
 * @file zmp_calculator.cpp
 * @author Yuki Sakai
 * @brief ZMPを計測する
 * @version 0.1
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <zmp_calculator/zmp_calculator.hpp>

ZmpCalculator::ZmpCalculator(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param("/zmp/loop_rate", 10)) {
  left_ft_sensor_sub_ =
      nh_.subscribe(pnh.param<std::string>("/left_ft_sensor_topic_name", "/MSPARC/ForceSensor_foot_L"), 1,
                    &ZmpCalculator::LeftFtSensorCallback, this);
  right_ft_sensor_sub_ =
      nh_.subscribe(pnh.param<std::string>("/right_ft_sensor_topic_name", "/MSPARC/ForceSensor_foot_R"), 1,
                    &ZmpCalculator::RightFtSensorCallback, this);
  link_poses_sub_ = nh_.subscribe(pnh.param<std::string>("/link_poses_topic_name", "/MSPARC/link_poses"), 1,
                                  &ZmpCalculator::LinkPoseCallback, this);
  actual_zmp_pub_ =
      nh_.advertise<geometry_msgs::PointStamped>(pnh.param<std::string>("/actual_zmp_topic_name", "/actual_zmp"), 1);

  // メンバ変数の初期化
  pnh.param<double>("/zmp/dt", dt_, 0.001);
  pnh.param<int>("/zmp/leg_num", leg_num_, 2);
  pnh.param<double>("/zmp/support_area_x_min", support_area_min_.x(), 0.0);
  pnh.param<double>("/zmp/support_area_y_min", support_area_min_.y(), 0.0);
  pnh.param<double>("/zmp/support_area_x_max", support_area_max_.x(), 0.0);
  pnh.param<double>("/zmp/support_area_y_max", support_area_max_.y(), 0.0);
  pnh.param<double>("/zmp/min_contact_force", min_contact_force_, 10.0);
  pnh.param<int>("/zmp/ft_sensor_link_num_L", ft_sensor_link_num_[L], 4);
  pnh.param<int>("/zmp/ft_sensor_link_num_R", ft_sensor_link_num_[R], 10);

  ft_sensor_link_pos_.resize(2);
  ft_sensor_link_pos_[L].Zero();
  ft_sensor_link_pos_[R].Zero();
  ft_sensor_link_ori_.resize(2);
  ft_sensor_link_ori_[L].Zero();
  ft_sensor_link_ori_[R].Zero();

  leg_is_contact_.resize(leg_num_);
  for (int i = 0; i < leg_num_; i++) leg_is_contact_[i] = false;
  leg_zmp_.resize(leg_num_);
  for (int i = 0; i < leg_num_; i++) leg_zmp_[i].Zero();
  zmp_balance_.resize(leg_num_);
  for (int i = 0; i < leg_num_; i++) zmp_balance_[i] = 0.0;

  actual_zmp_.Zero();
}

void ZmpCalculator::CalcZmp(const std::vector<Eigen::Vector3d> force_sensor_value,
                            const std::vector<Eigen::Vector3d> moment_sensor_value, Eigen::Vector3d& actual_zmp) {
  // 力覚センサから床反力を得て，各脚におけるZMPを計測する
  std::vector<Eigen::Vector3d> F, M;
  F.resize(leg_num_);
  M.resize(leg_num_);
  for (int i = 0; i < leg_num_; i++) {
    // 脚の接地状態を変更
    F[i] = ft_sensor_link_ori_[i] * force_sensor_value[i];
    M[i] = ft_sensor_link_ori_[i] * moment_sensor_value[i];
    leg_is_contact_[i] = (F[i].z() >= min_contact_force_);

    // 脚が接地している場合は計測を続ける
    if (leg_is_contact_[i]) {
      // 力覚センサの値を絶対座標系から見たものに変換

      leg_zmp_[i] = Eigen::Vector3d(-M[i].y() / F[i].z(), M[i].x() / F[i].z(), 0.0);

      // 支持領域外にZMPがある場合は，支持領域内に射影する
      // if (leg_zmp_[i].x() > support_area_max_.x()) {
      //   leg_zmp_[i].x() = support_area_max_.x();
      // } else if (leg_zmp_[i].x() < support_area_min_.x()) {
      //   leg_zmp_[i].x() = support_area_min_.x();
      // }
      // if (leg_zmp_[i].y() > support_area_max_.y()) {
      //   leg_zmp_[i].y() = support_area_max_.y();
      // } else if (leg_zmp_[i].y() < support_area_min_.y()) {
      //   leg_zmp_[i].y() = support_area_min_.y();
      // }

    } else {
      // 脚が接地していないときはゼロを返す
      leg_zmp_[i] = Eigen::Vector3d(0.0, 0.0, 0.0);
    }
  }

  // 各脚の計測値をもとにZMPを計測する（2足限定）
  if (leg_num_ == 2) {
    if (!leg_is_contact_[0] && !leg_is_contact_[1]) {
      zmp_balance_[0] = 0.5;
      zmp_balance_[1] = 0.5;
      actual_zmp = Eigen::Vector3d(0.0, 0.0, 0.0);
    } else {
      double f0 = std::max(0.0, F[L].z());
      double f1 = std::max(0.0, F[R].z());
      zmp_balance_[L] = f0 / (f0 + f1);
      zmp_balance_[R] = f1 / (f0 + f1);
      actual_zmp = zmp_balance_[L] * (ft_sensor_link_pos_[L] + ft_sensor_link_ori_[L] * leg_zmp_[L]) +
                   zmp_balance_[R] * (ft_sensor_link_pos_[R] + ft_sensor_link_ori_[R] * leg_zmp_[R]);
    }
  }
}

void ZmpCalculator::ZmpCalculatorCallback(const geometry_msgs::WrenchStamped left_ft_sensor,
                                          const geometry_msgs::WrenchStamped right_ft_sensor) {
  std::vector<Eigen::Vector3d> force_sensor_value, moment_sensor_value;
  force_sensor_value.resize(leg_num_);
  moment_sensor_value.resize(leg_num_);
  Eigen::Vector3d left_force_data, left_moment_data, right_force_data, right_moment_data;
  _WrenchToVector3d(left_ft_sensor, left_force_data, left_moment_data);
  _WrenchToVector3d(right_ft_sensor, right_force_data, right_moment_data);

  force_sensor_value[0] = left_force_data;
  force_sensor_value[1] = right_force_data;
  moment_sensor_value[0] = left_moment_data;
  moment_sensor_value[1] = right_moment_data;

  CalcZmp(force_sensor_value, moment_sensor_value, actual_zmp_);

  geometry_msgs::PointStamped pub_actual_zmp_data;
  // actual_zmp_.x() = zmp_filter_[0](actual_zmp_.x(), dt_);
  // actual_zmp_.y() = zmp_filter_[1](actual_zmp_.y(), dt_);
  _Vector3dToPoint(actual_zmp_, pub_actual_zmp_data.point);
  pub_actual_zmp_data.header.stamp = ros::Time::now();
  pub_actual_zmp_data.header.frame_id = "actual_zmp";
  actual_zmp_pub_.publish(pub_actual_zmp_data);
}

void ZmpCalculator::Run() {
  // ros::Timerを利用した実装に変更してもいいかも？
  while (nh_.ok()) {
    ZmpCalculatorCallback(left_ft_sensor_data_, right_ft_sensor_data_);
    ros::spinOnce();
    rate_.sleep();
  }
}

void ZmpCalculator::_WrenchToVector3d(const geometry_msgs::WrenchStamped ft_sensor, Eigen::Vector3d& force_data,
                                      Eigen::Vector3d& moment_data) {
  force_data.x() = ft_sensor.wrench.force.x;
  force_data.y() = ft_sensor.wrench.force.y;
  force_data.z() = ft_sensor.wrench.force.z;

  moment_data.x() = ft_sensor.wrench.torque.x;
  moment_data.y() = ft_sensor.wrench.torque.y;
  moment_data.z() = ft_sensor.wrench.torque.z;
}

void ZmpCalculator::_Vector3dToPoint(const Eigen::Vector3d actual_zmp, geometry_msgs::Point& point_data) {
  point_data.x = actual_zmp.x();
  point_data.y = actual_zmp.y();
  point_data.z = actual_zmp.z();
}

void ZmpCalculator::LeftFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& left_ft_sensor) {
  left_ft_sensor_data_.header = left_ft_sensor->header;
  left_ft_sensor_data_.wrench = left_ft_sensor->wrench;
}

void ZmpCalculator::RightFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& right_ft_sensor) {
  right_ft_sensor_data_.header = right_ft_sensor->header;
  right_ft_sensor_data_.wrench = right_ft_sensor->wrench;
}

void ZmpCalculator::LinkPoseCallback(const geometry_msgs::PoseArray::ConstPtr& poses) {
  link_poses_.header = poses->header;
  link_poses_.poses = poses->poses;

  ms_util.Point2Vector(poses->poses[ft_sensor_link_num_[L]].position, ft_sensor_link_pos_[L]);
  ms_util.Quaternion2Matrix(poses->poses[ft_sensor_link_num_[L]].orientation, ft_sensor_link_ori_[L]);
  ms_util.Point2Vector(poses->poses[ft_sensor_link_num_[R]].position, ft_sensor_link_pos_[R]);
  ms_util.Quaternion2Matrix(poses->poses[ft_sensor_link_num_[R]].orientation, ft_sensor_link_ori_[R]);
}