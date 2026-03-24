/**
 * @file izmp_calculator.cpp
 * @author Taisei Suzuki
 * @brief Imaginary ZMP（IZMP）を計測する
 * @version 0.1
 * @date 2023-11-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <zmp_calculator/izmp_calculator.hpp>

IzmpCalculator::IzmpCalculator(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param("/zmp/loop_rate", 1000)) {
  imu_sub_ =
      nh_.subscribe(pnh.param<std::string>("/imu_topic_name", "/MELEW3/imu"), 1, &IzmpCalculator::ImuCallback, this);
  base_sub_ =
      nh_.subscribe(pnh.param<std::string>("/base_topic_name", "/MELEW3/base"), 1, &IzmpCalculator::BaseCallback, this);
  com_sub_ =
      nh_.subscribe(pnh.param<std::string>("/com_topic_name", "/MELEW3/com"), 1, &IzmpCalculator::ComCallback, this);
  imaginary_zmp_pub_ = nh_.advertise<geometry_msgs::PointStamped>(
      pnh.param<std::string>("/imaginary_zmp_topic_name", "/MELEW3/imaginary_zmp"), 1);

  /*** メンバ変数の初期化 ***/
  pnh.param<double>("/zmp/dt", dt_, 0.001);
  imaginary_zmp_.Zero();

  /*** フィルタクラスの初期化 ***/
  for (int i = 0; i < LEG_NUM; i++) filter[i].init(dt_);
}

/**
 * @brief Imaginary ZMP（IZMP）を計算する関数
 *
 * @param base_position     ベースリンク位置
 * @param base_acceleration ベースリンク角速度
 * @param com_position      重心位置
 * @param imaginary_zmp     Imaginary ZMP（IZMP）
 */
void IzmpCalculator::CalcIzmp(const Eigen::Vector3d base_position, const Eigen::Vector3d base_acceleration,
                              const Eigen::Vector3d com_position, Eigen::Vector3d& imaginary_zmp) {
  /*** Imaginary ZMPを計算する ***/
  double x = com_position.x() - base_acceleration.x() / (g + base_acceleration.z()) * base_position.z();
  double y = com_position.y() - base_acceleration.y() / (g + base_acceleration.y()) * base_position.y();

  imaginary_zmp = Eigen::Vector3d(x, y, 0.0);
}

/**
 * @brief Imaginary ZMP（IZMP）をPublishする関数
 *
 * @param Imu  IMUセンサの値
 * @param Base ベースリンク位置
 * @param Com  重心位置
 */
void IzmpCalculator::IzmpCalculatorCallback(const sensor_msgs::Imu Imu, const melew3_msgs::Motion Base,
                                            const melew3_msgs::Motion Com) {
  Eigen::Vector3d base_position;      //!< ベースリンク位置
  Eigen::Matrix3d base_orientation;   //!< ベースリンク姿勢
  Eigen::Vector3d base_acceleration;  //!< ベースリンク加速度
  Eigen::Vector3d com_position;       //!< 重心位置

  util.PointToVector3d(Base.point, base_position);  // ベースリンク位置を格納

  /*** ベースリンク姿勢を格納 ***/
  Eigen::Quaterniond q;
  q.x() = Imu.orientation.x;
  q.y() = Imu.orientation.y;
  q.z() = Imu.orientation.z;
  q.w() = Imu.orientation.w;
  base_orientation = q.normalized().toRotationMatrix();

  /*** ベースリンク加速度を格納 ***/
  base_acceleration =
      base_orientation * Eigen::Vector3d(imu_data_.linear_acceleration.x, imu_data_.linear_acceleration.y,
                                         imu_data_.linear_acceleration.z);

  util.PointToVector3d(Com.point, com_position);  // 重心位置を格納

  CalcIzmp(base_position, base_acceleration, com_position, imaginary_zmp_);  // IZMPを計算

  /*** 計算したIZMPをPublishする ***/
  geometry_msgs::PointStamped pub_imaginary_zmp_data;
  util.Vector3dToPoint(imaginary_zmp_, pub_imaginary_zmp_data.point);
  pub_imaginary_zmp_data.header.stamp = ros::Time::now();
  pub_imaginary_zmp_data.header.frame_id = "imaginary_zmp";
  imaginary_zmp_pub_.publish(pub_imaginary_zmp_data);
}

/**
 * @brief izmp_calculatorの制御を回す関数
 *
 */
void IzmpCalculator::Run() {
  // ros::Timerを利用した実装に変更してもいいかも？
  while (nh_.ok()) {
    IzmpCalculatorCallback(imu_data_, base_data_, com_data_);
    ros::spinOnce();
    rate_.sleep();
  }
}

/**
 * @brief IMUセンサの値を一時保存するコールバック関数
 *
 * @param Imu IMUセンサの値
 */
void IzmpCalculator::ImuCallback(const sensor_msgs::Imu::ConstPtr& Imu) {
  imu_data_.header = Imu->header;
  imu_data_.orientation = Imu->orientation;
  imu_data_.angular_velocity = Imu->angular_velocity;
  imu_data_.linear_acceleration = Imu->linear_acceleration;
}

/**
 * @brief ベースリンク位置を一時保存するコールバック関数
 *
 * @param Base ベースリンク位置
 */
void IzmpCalculator::BaseCallback(const melew3_msgs::Motion::ConstPtr& Base) {
  base_data_.header = Base->header;
  base_data_.point = Base->point;
  base_data_.linear = Base->linear;
}

/**
 * @brief 重心位置を一時保存するコールバック関数
 *
 * @param Com 重心位置
 */
void IzmpCalculator::ComCallback(const melew3_msgs::Motion::ConstPtr& Com) {
  com_data_.header = Com->header;
  com_data_.point = Com->point;
  com_data_.linear = Com->linear;
}
