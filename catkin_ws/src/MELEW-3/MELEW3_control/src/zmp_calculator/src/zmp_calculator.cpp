/**
 * @file zmp_calculator.cpp
 * @author Yuki Sakai
 * @brief 実ZMPを計測する
 * @version 0.1
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <zmp_calculator/zmp_calculator.hpp>

ZmpCalculator::ZmpCalculator(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param("/zmp/loop_rate", 1000)) {
  FL_ft_sensor_sub_ = nh_.subscribe(pnh.param<std::string>("/FL_ft_sensor_topic_name", "/MELEW3/ForceSensor_foot_FL"),
                                    1, &ZmpCalculator::FLFtSensorCallback, this);
  FR_ft_sensor_sub_ = nh_.subscribe(pnh.param<std::string>("/FR_ft_sensor_topic_name", "/MELEW3/ForceSensor_foot_FR"),
                                    1, &ZmpCalculator::FRFtSensorCallback, this);
  BL_ft_sensor_sub_ = nh_.subscribe(pnh.param<std::string>("/BL_ft_sensor_topic_name", "/MELEW3/ForceSensor_foot_BL"),
                                    1, &ZmpCalculator::BLFtSensorCallback, this);
  BR_ft_sensor_sub_ = nh_.subscribe(pnh.param<std::string>("/BR_ft_sensor_topic_name", "/MELEW3/ForceSensor_foot_BR"),
                                    1, &ZmpCalculator::BRFtSensorCallback, this);
  link_info_sub_ = nh_.subscribe(pnh.param<std::string>("/link_info_topic_name", "/MELEW3/link_info"), 1000,
                                 &ZmpCalculator::LinkInfoCallback, this);
  actual_zmp_pub_ = nh_.advertise<geometry_msgs::PointStamped>(
      pnh.param<std::string>("/actual_zmp_topic_name", "/MELEW3/actual_zmp"), 1);

  /*** メンバ変数の初期化 ***/
  pnh.param<double>("/zmp/dt", dt_, 0.001);
  pnh.param<double>("/zmp/support_area_x_min", support_area_min_.x(), 0.0);
  pnh.param<double>("/zmp/support_area_y_min", support_area_min_.y(), 0.0);
  pnh.param<double>("/zmp/support_area_x_max", support_area_max_.x(), 0.0);
  pnh.param<double>("/zmp/support_area_y_max", support_area_max_.y(), 0.0);
  pnh.param<double>("/zmp/min_contact_force", min_contact_force_, 10.0);
  pnh.param<int>("/zmp/ft_sensor_link_num_FL", ft_sensor_link_num_[FL], 7);
  pnh.param<int>("/zmp/ft_sensor_link_num_FR", ft_sensor_link_num_[FR], 16);
  pnh.param<int>("/zmp/ft_sensor_link_num_BL", ft_sensor_link_num_[BL], 25);
  pnh.param<int>("/zmp/ft_sensor_link_num_BR", ft_sensor_link_num_[BR], 34);

  ft_sensor_link_pos_.resize(LEG_NUM);
  ft_sensor_link_ori_.resize(LEG_NUM);
  ft_sensor_.resize(LEG_NUM);
  leg_is_contact_.resize(LEG_NUM);
  leg_zmp_.resize(LEG_NUM);
  zmp_balance_.resize(LEG_NUM);
  actual_zmp_.Zero();

  for (int i = 0; i < LEG_NUM; i++) {
    ft_sensor_link_pos_[i].Zero();
    ft_sensor_link_ori_[i].Zero();
    leg_is_contact_[i] = false;
    leg_zmp_[i].Zero();
    zmp_balance_[i] = 0.0;
  }

  /*** フィルタクラスの初期化 ***/
  for (int i = 0; i < LEG_NUM * 2; i++) filter[i].init(dt_);
}

/**
 * @brief ZMPを計算する関数
 *
 * @param force_sensor_value  車軸に加わる力
 * @param moment_sensor_value 車軸に加わるモーメント
 * @param actual_zmp          実ZMP
 */
void ZmpCalculator::CalcZmp(const std::vector<Eigen::Vector3d> force_sensor_value,
                            const std::vector<Eigen::Vector3d> moment_sensor_value, Eigen::Vector3d& actual_zmp) {
  /*** 力覚センサから床反力を得て，各脚におけるZMPを計測する ***/
  std::vector<Eigen::Vector3d> F, M;
  F.resize(LEG_NUM);
  M.resize(LEG_NUM);
  for (int i = 0; i < LEG_NUM; i++) {
    /*** 脚の接地状態を変更 ***/
    F[i] = ft_sensor_link_ori_[i] * force_sensor_value[i];
    M[i] = ft_sensor_link_ori_[i] * moment_sensor_value[i];
    leg_is_contact_[i] = (F[i].z() >= min_contact_force_);

    /*** 脚が接地している場合は計測を続ける ***/
    if (leg_is_contact_[i]) {
      /*** 力覚センサの値を絶対座標系から見たものに変換 ***/
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
      leg_zmp_[i] = Eigen::Vector3d(0.0, 0.0, 0.0);  //脚が接地していないときはゼロを返す
    }
  }

  actual_zmp = Eigen::Vector3d(0.0, 0.0, 0.0);  // ZMPの値を初期化

  /*** 力センサのデータが存在するか判定する ***/
  if (LEG_NUM == 2)
    enable_flag = leg_is_contact_[L] || leg_is_contact_[R];
  else if (LEG_NUM == 4)
    enable_flag = leg_is_contact_[FL] || leg_is_contact_[FR] || leg_is_contact_[BL] || leg_is_contact_[BR];

  if (enable_flag) {
    /*** 各脚の計測値をもとにZMPを計測する ***/
    double f_total = 0.0;
    for (int i = 0; i < LEG_NUM; i++) {
      ft_sensor_[i] = std::max(0.0, F[i].z());
      f_total += ft_sensor_[i];
    }
    for (int i = 0; i < LEG_NUM; i++) {
      zmp_balance_[i] = ft_sensor_[i] / f_total;
      actual_zmp += zmp_balance_[i] * (ft_sensor_link_pos_[i] + ft_sensor_link_ori_[i] * leg_zmp_[i]);
    }
  } else {
    /*** 力センサのデータがすべて0のときの処理 ***/
    for (int i = 0; i < LEG_NUM; i++) zmp_balance_[i] = 1.0 / (double)LEG_NUM;
  }
}

/**
 * @brief 実ZMPをPublishする関数
 *
 * @param FL_ft_sensor 左前脚の力センサの値
 * @param FR_ft_sensor 右前脚の力センサの値
 * @param BL_ft_sensor 左後脚の力センサの値
 * @param BR_ft_sensor 左後脚の力センサの値
 * @param actual_zmp   実ZMP
 */
void ZmpCalculator::ZmpCalculatorCallback(const geometry_msgs::WrenchStamped FL_ft_sensor,
                                          const geometry_msgs::WrenchStamped FR_ft_sensor,
                                          const geometry_msgs::WrenchStamped BL_ft_sensor,
                                          const geometry_msgs::WrenchStamped BR_ft_sensor) {
  std::vector<Eigen::Vector3d> force_sensor_value, moment_sensor_value;
  force_sensor_value.resize(LEG_NUM);
  moment_sensor_value.resize(LEG_NUM);
  Eigen::Vector3d FL_force_data, FR_force_data, BL_force_data, BR_force_data;
  Eigen::Vector3d FL_moment_data, FR_moment_data, BL_moment_data, BR_moment_data;
  util.WrenchToVector3d(FL_ft_sensor.wrench, FL_force_data, FL_moment_data);
  util.WrenchToVector3d(FR_ft_sensor.wrench, FR_force_data, FR_moment_data);
  util.WrenchToVector3d(BL_ft_sensor.wrench, BL_force_data, BL_moment_data);
  util.WrenchToVector3d(BR_ft_sensor.wrench, BR_force_data, BR_moment_data);

  force_sensor_value[FL] = filter[FL].LPF(FL_force_data, 10.0);
  force_sensor_value[FR] = filter[FR].LPF(FR_force_data, 10.0);
  force_sensor_value[BL] = filter[BL].LPF(BL_force_data, 10.0);
  force_sensor_value[BR] = filter[BR].LPF(BR_force_data, 10.0);
  moment_sensor_value[FL] = filter[FL + LEG_NUM].LPF(FL_moment_data, 10.0);
  moment_sensor_value[FR] = filter[FR + LEG_NUM].LPF(FR_moment_data, 10.0);
  moment_sensor_value[BL] = filter[BL + LEG_NUM].LPF(BL_moment_data, 10.0);
  moment_sensor_value[BR] = filter[BR + LEG_NUM].LPF(BR_moment_data, 10.0);

  CalcZmp(force_sensor_value, moment_sensor_value, actual_zmp_);

  geometry_msgs::PointStamped pub_actual_zmp_data;

  util.Vector3dToPoint(actual_zmp_, pub_actual_zmp_data.point);
  pub_actual_zmp_data.header.stamp = ros::Time::now();
  pub_actual_zmp_data.header.frame_id = "actual_zmp";
  actual_zmp_pub_.publish(pub_actual_zmp_data);
}

/**
 * @brief zmp_calculatorの制御を回す関数
 *
 */
void ZmpCalculator::Run() {
  // ros::Timerを利用した実装に変更してもいいかも？
  while (nh_.ok()) {
    ZmpCalculatorCallback(FL_ft_sensor_data_, FR_ft_sensor_data_, BL_ft_sensor_data_, BR_ft_sensor_data_);
    ros::spinOnce();
    rate_.sleep();
  }
}

/**
 * @brief 左前脚の力センサの値を一時保存するコールバック関数
 *
 * @param FL_ft_sensor 左前脚の力センサの値
 */
void ZmpCalculator::FLFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& FL_ft_sensor) {
  FL_ft_sensor_data_.header = FL_ft_sensor->header;
  FL_ft_sensor_data_.wrench = FL_ft_sensor->wrench;
}

/**
 * @brief 右前脚の力センサの値を一時保存するコールバック関数
 *
 * @param FR_ft_sensor 右前脚の力センサの値
 */
void ZmpCalculator::FRFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& FR_ft_sensor) {
  FR_ft_sensor_data_.header = FR_ft_sensor->header;
  FR_ft_sensor_data_.wrench = FR_ft_sensor->wrench;
}

/**
 * @brief 左後脚の力センサの値を一時保存するコールバック関数
 *
 * @param BL_ft_sensor 左後脚の力センサの値
 */
void ZmpCalculator::BLFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& BL_ft_sensor) {
  BL_ft_sensor_data_.header = BL_ft_sensor->header;
  BL_ft_sensor_data_.wrench = BL_ft_sensor->wrench;
}

/**
 * @brief 右後脚の力センサの値を一時保存するコールバック関数
 *
 * @param BR_ft_sensor 右後脚の力センサの値
 */
void ZmpCalculator::BRFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& BR_ft_sensor) {
  BR_ft_sensor_data_.header = BR_ft_sensor->header;
  BR_ft_sensor_data_.wrench = BR_ft_sensor->wrench;
}

/**
 * @brief リンク情報を一時保存するコールバック関数
 *
 * @param BR_ft_sensor リンク情報
 */
void ZmpCalculator::LinkInfoCallback(const melew3_msgs::LinkInfoArray::ConstPtr& link_info) {
  link_info_.header = link_info->header;
  link_info_.position = link_info->position;
  link_info_.velocity = link_info->velocity;
  for (int i = 0; i < LEG_NUM; i++)
    util.PoseToMatrix(link_info_.position[ft_sensor_link_num_[i]], ft_sensor_link_pos_[i], ft_sensor_link_ori_[i]);
}