#include "MELEW3_Kinematics.h"

namespace melew3_kinematics {

/**
 * @brief Construct a new MELEW3_Kinematics::MELEW3_Kinematics object
 *
 */
MELEW3_Kinematics::MELEW3_Kinematics(double l1r, double l2r, double l1s, double l2s) {
  l1_parallel = l1r;
  l2_parallel = l2r;
  l1_serial = l1s;
  l2_serial = l2s;
}

/**
 * @brief Construct a new MELEW3_Kinematics::MELEW3_Kinematics object
 *
 */
MELEW3_Kinematics::MELEW3_Kinematics() {
  l1_parallel = 0.0;
  l2_parallel = 0.0;
  l1_serial = 0.0;
  l2_serial = 0.0;

  p_b1 = Eigen::Vector3d::Zero();
  p_b2 = Eigen::Vector3d::Zero();
  p_b3 = Eigen::Vector3d::Zero();
  p_b4 = Eigen::Vector3d::Zero();
  p_D1 = Eigen::Vector3d::Zero();
  p_D2 = Eigen::Vector3d::Zero();
  calc_p_D = Eigen::VectorXd::Zero(6);
}

void MELEW3_Kinematics::init(double _l1_parallel, double _l2_parallel, double _l1_serial, double _l2_serial) {
  l1_parallel = _l1_parallel;
  l2_parallel = _l2_parallel;
  l1_serial = _l1_serial;
  l2_serial = _l2_serial;
  ROS_INFO("MELEW3_Kinematics: Initialization complete");
}

/**
 * @brief Calculate forward kinematics of the robot from current joint angle
 *
 * @param q     : Joint angle vector
 * @param p     : Answer of forward kinematics
 * @param psi   : Target yaw angle
 * @return true :
 * @return false:
 */
bool MELEW3_Kinematics::solve_FK_parallel(const Eigen::VectorXd& q, Eigen::Vector3d& p, double& psi) {
  return solve_FK_parallel(0, q, p, psi);
}

/**
 * @brief Calculate forward kinematics of the robot from current joint angle
 *
 * @param leg_num : Leg number (FL:0, FR:1, BL:2, BR:3)
 * @param q     : Joint angle vector
 * @param p     : Answer of forward kinematics
 * @param psi   : Target yaw angle
 * @return true :
 * @return false:
 */
bool MELEW3_Kinematics::solve_FK_parallel(const int leg_num, const Eigen::VectorXd& q, Eigen::Vector3d& p,
                                          double& psi) {
  try {
    //! 点B1，B2，B3，B4の単位ベクトルの計算
    p_b1 << sqrt(3) / 2 * cos(q[LO_MOTOR]), 0.5, -sqrt(3) / 2 * sin(q[LO_MOTOR]);
    p_b2 << -sqrt(3) / 2 * cos(q[LI_MOTOR]), 0.5, sqrt(3) / 2 * sin(q[LI_MOTOR]);
    p_b3 << -sqrt(3) / 2 * cos(q[RI_MOTOR]), -0.5, sqrt(3) / 2 * sin(q[RI_MOTOR]);
    p_b4 << sqrt(3) / 2 * cos(q[RO_MOTOR]), -0.5, -sqrt(3) / 2 * sin(q[RO_MOTOR]);

    //! 外積と内積の計算
    crossB14 = p_b1.cross(p_b4);
    dotB14 = p_b1.dot(p_b4);
    crossB23 = p_b2.cross(p_b3);
    dotB23 = p_b2.dot(p_b3);

    if (leg_num == 0 || leg_num == 1) {
      //! 前脚の場合の処理
      //! 点D1，D2の座標の計算
      p_D1 = (crossB14.cross(0.5 * (p_b1 - p_b4)) + sqrt(((-0.5 - dotB14) * (dotB14 - 1))) * crossB14) /
             (crossB14.norm() * crossB14.norm()) * l1_parallel;
      p_D2 = (crossB23.cross(0.5 * (p_b2 - p_b3)) - sqrt(((-0.5 - dotB23) * (dotB23 - 1))) * crossB23) /
             (crossB23.norm() * crossB23.norm()) * l2_parallel;

      //! 球面リンク部の例外処理（点B1〜点B4の位置で逆膝にならないようにする）
      if (p_D1.z() >= std::max(p_b1.z(), p_b4.z()) * l1_parallel) throw "Can not calculate coordinate of D1!";
      if (p_D2.z() >= std::max(p_b2.z(), p_b3.z()) * l2_parallel) throw "Can not calculate coordinate of D2!";
    } else if (leg_num == 2 || leg_num == 3) {
      //! 後脚の場合の処理
      //! 点D1，D2の座標の計算
      p_D1 = (crossB23.cross(0.5 * (p_b2 - p_b3)) - sqrt(((-0.5 - dotB23) * (dotB23 - 1))) * crossB23) /
             (crossB23.norm() * crossB23.norm()) * l1_parallel;
      p_D2 = (crossB14.cross(0.5 * (p_b1 - p_b4)) + sqrt(((-0.5 - dotB14) * (dotB14 - 1))) * crossB14) /
             (crossB14.norm() * crossB14.norm()) * l2_parallel;

      //! 球面リンク部の例外処理（点B1〜点B4の位置で逆膝にならないようにする）
      if (p_D1.z() >= std::max(p_b2.z(), p_b3.z()) * l1_parallel) throw "Can not calculate coordinate of D1!";
      if (p_D2.z() >= std::max(p_b1.z(), p_b4.z()) * l2_parallel) throw "Can not calculate coordinate of D2!";
    } else
      throw "The value of leg_num is out of range!";

    //! 脚先（点F）の(x, y, z)座標とYaw角の計算
    for (int j = 0; j < 3; j++) p(j) = p_D1(j) * (l2_parallel / l1_parallel) + p_D2(j);
    psi = -atan((p_D1.y() * p_D2.z() - p_D1.z() * p_D2.y()) / (p_D1.z() * p_D2.x() - p_D1.x() * p_D2.z()));

    return true;

  } catch (const char* str) {
    //! 例外処理
    ROS_ERROR("%s", str);
    ROS_ERROR("[MELEW3_Kinematics] Can not calculate forward kinematics!");
    return false;
  }
}

/**
 * @brief Calculate inverse kinematics of the robot from target foot position and yaw angle
 *
 * @param p     : Target foot position
 * @param psi   : Target yaw angle
 * @param q     : Answer of inverse kinematics
 * @return true
 * @return false
 */
bool MELEW3_Kinematics::solve_IK_parallel(const Eigen::Vector3d& p, const double& psi, Eigen::VectorXd& q) {
  return solve_IK_parallel(0, p, psi, q);
}

/**
 * @brief Calculate inverse kinematics of the robot from target foot position and yaw angle
 *
 * @param leg_num : Leg number (FL:0, FR:1, BL:2, BR:3)
 * @param p     : Target foot position
 * @param psi   : Target yaw angle
 * @param q     : Answer of inverse kinematics
 * @return true
 * @return false
 */
bool MELEW3_Kinematics::solve_IK_parallel(const int leg_num, const Eigen::Vector3d& p, const double& psi,
                                          Eigen::VectorXd& q) {
  Eigen::VectorXd q_past = q;

  try {
    //! 変数calc_p_Dの計算
    calc_p_D(0) = p.x() * p.x() + p.y() * p.y() + p.z() * p.z();
    calc_p_D(1) = p.x() + p.y() * tan(psi);
    calc_p_D(2) = (p.y() - p.x() * tan(psi)) * p.y() / p.z() + p.z();
    calc_p_D(3) = (p.y() - p.x() * tan(psi)) * p.x() / p.z() - p.z() * tan(psi);
    calc_p_D(4) = (p.y() - p.x() * tan(psi)) / p.z();
    calc_p_D(5) = 1.0 + tan(psi) * tan(psi) + calc_p_D(4) * calc_p_D(4);

    if (leg_num == 0 || leg_num == 1) {
      //! 前脚の場合の処理
      //! 点D2の座標の導出
      p_D2.x() = (calc_p_D(0) * (calc_p_D(1) + calc_p_D(3) * calc_p_D(4)) +
                  calc_p_D(2) *
                      sqrt(4.0 * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)) *
                               l2_parallel * l2_parallel -
                           calc_p_D(0) * calc_p_D(0) * calc_p_D(5))) /
                 (2.0 * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)));
      p_D2.z() =
          (calc_p_D(0) *
               (calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3) - calc_p_D(1) * calc_p_D(3) * calc_p_D(4)) -
           calc_p_D(1) * calc_p_D(2) *
               sqrt(4.0 * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)) *
                        l2_parallel * l2_parallel -
                    calc_p_D(0) * calc_p_D(0) * calc_p_D(5))) /
          (2.0 * calc_p_D(2) * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)));
      p_D2.y() = p_D2.x() * tan(psi) + ((p.y() - p.x() * tan(psi)) / p.z()) * p_D2.z();

      //! 点D1の座標の導出
      for (int i = 0; i < 3; i++) p_D1(i) = (l1_parallel / l2_parallel) * (p(i) - p_D2(i));

      //! モータ回転角qの導出
      if (p_D1.x() >= 0) {  //!< xD1>=0
        q(LO_MOTOR) = -asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) -
                      asin(sqrt(2.0 * (l1_parallel + 2.0 * p_D1.y()) / (3.0 * (l1_parallel + p_D1.y()))));
        q(RO_MOTOR) = -asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) -
                      asin(sqrt(2.0 * (l1_parallel - 2.0 * p_D1.y()) / (3.0 * (l1_parallel - p_D1.y()))));
      } else {  //!< xD1<0
        q(LO_MOTOR) = M_PI + asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) -
                      asin(sqrt(2.0 * (l1_parallel + 2.0 * p_D1.y()) / (3.0 * (l1_parallel + p_D1.y()))));
        q(RO_MOTOR) = M_PI + asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) -
                      asin(sqrt(2.0 * (l1_parallel - 2.0 * p_D1.y()) / (3.0 * (l1_parallel - p_D1.y()))));
      }

      if (p_D2.x() <= 0) {  //!< xD2<=0
        q(LI_MOTOR) = asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) +
                      asin(sqrt(2.0 * (l2_parallel + 2.0 * p_D2.y()) / (3.0 * (l2_parallel + p_D2.y()))));
        q(RI_MOTOR) = asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) +
                      asin(sqrt(2.0 * (l2_parallel - 2.0 * p_D2.y()) / (3.0 * (l2_parallel - p_D2.y()))));
      } else {  //!< xD2>0
        q(LI_MOTOR) = -M_PI - asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) +
                      asin(sqrt(2.0 * (l2_parallel + 2.0 * p_D2.y()) / (3.0 * (l2_parallel + p_D2.y()))));
        q(RI_MOTOR) = -M_PI - asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) +
                      asin(sqrt(2.0 * (l2_parallel - 2.0 * p_D2.y()) / (3.0 * (l2_parallel - p_D2.y()))));
      }
    } else if (leg_num == 2 || leg_num == 3) {
      //! 後脚の場合の処理
      //! 点D2の座標の導出
      p_D2.x() = (calc_p_D(0) * (calc_p_D(1) + calc_p_D(3) * calc_p_D(4)) -
                  calc_p_D(2) *
                      sqrt(4.0 * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)) *
                               l2_parallel * l2_parallel -
                           calc_p_D(0) * calc_p_D(0) * calc_p_D(5))) /
                 (2.0 * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)));
      p_D2.z() =
          (calc_p_D(0) *
               (calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3) - calc_p_D(1) * calc_p_D(3) * calc_p_D(4)) +
           calc_p_D(1) * calc_p_D(2) *
               sqrt(4.0 * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)) *
                        l2_parallel * l2_parallel -
                    calc_p_D(0) * calc_p_D(0) * calc_p_D(5))) /
          (2.0 * calc_p_D(2) * (calc_p_D(1) * calc_p_D(1) + calc_p_D(2) * calc_p_D(2) + calc_p_D(3) * calc_p_D(3)));
      p_D2.y() = p_D2.x() * tan(psi) + ((p.y() - p.x() * tan(psi)) / p.z()) * p_D2.z();

      //! 点D1の座標の導出
      for (int i = 0; i < 3; i++) p_D1(i) = (l1_parallel / l2_parallel) * (p(i) - p_D2(i));

      //! モータ回転角qの導出
      if (p_D2.x() >= 0) {  //!< xD2>=0
        q(LO_MOTOR) = -asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) -
                      asin(sqrt(2.0 * (l2_parallel + 2.0 * p_D2.y()) / (3.0 * (l2_parallel + p_D2.y()))));
        q(RO_MOTOR) = -asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) -
                      asin(sqrt(2.0 * (l2_parallel - 2.0 * p_D2.y()) / (3.0 * (l2_parallel - p_D2.y()))));
      } else {  //!< xD2<0
        q(LO_MOTOR) = M_PI + asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) -
                      asin(sqrt(2.0 * (l2_parallel + 2.0 * p_D2.y()) / (3.0 * (l2_parallel + p_D2.y()))));
        q(RO_MOTOR) = M_PI + asin(p_D2.z() / sqrt(l2_parallel * l2_parallel - p_D2.y() * p_D2.y())) -
                      asin(sqrt(2.0 * (l2_parallel - 2.0 * p_D2.y()) / (3.0 * (l2_parallel - p_D2.y()))));
      }

      if (p_D1.x() <= 0) {  //!< xD1<=0
        q(LI_MOTOR) = asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) +
                      asin(sqrt(2.0 * (l1_parallel + 2.0 * p_D1.y()) / (3.0 * (l1_parallel + p_D1.y()))));
        q(RI_MOTOR) = asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) +
                      asin(sqrt(2.0 * (l1_parallel - 2.0 * p_D1.y()) / (3.0 * (l1_parallel - p_D1.y()))));
      } else {  //!< xD1>0
        q(LI_MOTOR) = -M_PI - asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) +
                      asin(sqrt(2.0 * (l1_parallel + 2.0 * p_D1.y()) / (3.0 * (l1_parallel + p_D1.y()))));
        q(RI_MOTOR) = -M_PI - asin(p_D1.z() / sqrt(l1_parallel * l1_parallel - p_D1.y() * p_D1.y())) +
                      asin(sqrt(2.0 * (l1_parallel - 2.0 * p_D1.y()) / (3.0 * (l1_parallel - p_D1.y()))));
      }
    } else
      throw "The value of leg_num is out of range!";

    //! 例外処理
    //! モータ回転角qの値が1つでも実数でない場合falseを返す
    if (isnan(q(LO_MOTOR)) + isnan(q(LI_MOTOR)) + isnan(q(2)) + isnan(q(RO_MOTOR)))
      throw "One or more answers has nan value!";

    //! (∠D1 O D2)の大きさがπ/9より小さいか(3/4)πより大きい場合falseを返す
    if (((p_D1.dot(p_D2) / (l1_parallel * l2_parallel)) > MINcosDOD) ||
        ((p_D1.dot(p_D2) / (l1_parallel * l2_parallel)) < MAXcosDOD))
      throw "Angle of (D1-O-D2) is less than pi/9, or larger than (3/4)pi!";

    //! モータ回転角qの値が1つでも-(13/36)πより小さいか(13/36)πより大きい場合falseを返す
    if (((q.array() < MIN_ANGLE).any()) || ((q.array() > MAX_ANGLE).any()))
      throw "One or more answers is less than -(13/36)pi, or larger than (13/36)pi!";

    // 脚先のz座標が-0.15mより大きい場合falseを返す
    if (p.z() > -0.15) throw "Z-coordinate of leg exceeds -0.15m!";

    return true;

  } catch (const char* str) {
    //! 例外処理
    ROS_ERROR("%s", str);
    ROS_ERROR("[MELEW3_Kinematics] Can not calculate inverse kinematics!");
    q = q_past;
    return false;
  }
}

/**
 * @brief Calculate forward kinematics of the simulation from current joint angle
 *
 * @param q     : Joint angle vector
 * @param p     : Answer of forward kinematics
 * @param psi   : Target yaw angle
 * @return true :
 * @return false:
 */
bool MELEW3_Kinematics::solve_FK_serial(const Eigen::VectorXd& q, Eigen::Vector3d& p, double& psi) {
  hip_to_knee << 0, 0, -l1_serial;   //!< 股関節から膝関節への行列
  knee_to_foot << 0, 0, -l2_serial;  //!< 膝関節から脚先への行列

  //! 順運動学の計算
  p = RotZ(q[HIP_YAW]) * RotX(q[HIP_ROLL]) * RotY(q[HIP_PITCH]) * (hip_to_knee + RotY(q[KNEE]) * knee_to_foot);
  psi = q[HIP_YAW];
  return true;
}

/**
 * @brief Calculate inverse kinematics of the simulation from target foot position and yaw angle
 *
 * @param p     : Target foot position
 * @param psi   : Target yaw angle
 * @param q     : Answer of inverse kinematics
 * @return true
 * @return false
 */
bool MELEW3_Kinematics::solve_IK_serial(const Eigen::Vector3d& p, const double& psi, Eigen::VectorXd& q) {
  return solve_IK_serial(0, p, psi, q);
}

/**
 * @brief Calculate inverse kinematics of the simulation from target foot position and yaw angle
 *
 * @param leg_num : Leg number (FL:0, FR:1, BL:2, BR:3)
 * @param p       : Target foot position
 * @param psi     : Target yaw angle
 * @param q       : Answer of inverse kinematics
 * @return true
 * @return false
 */
bool MELEW3_Kinematics::solve_IK_serial(const int leg_num, const Eigen::Vector3d& p, const double& psi,
                                        Eigen::VectorXd& q) {
  try {
    //! 例外処理
    double L = p.norm();
    if (L >= l1_serial + l2_serial) throw "Too far from hip to foot!";
    if (L < sqrt(l1_serial * l2_serial * (2.0 - sqrt(2.0)))) throw "Too close from hip to foot!";

    //! 逆運動学の計算
    Eigen::Vector3d p0 = RotZ(psi).inverse() * p;
    q[HIP_YAW] = psi;
    q[HIP_ROLL] = atan2(p0.y(), -p0.z());

    if (leg_num == 0 || leg_num == 1) {
      //! 前脚の場合の処理
      q[HIP_PITCH] = -atan2(p0.x(), std::hypot(p0.y(), p0.z())) +
                     acos((L * L + l1_serial * l1_serial - l2_serial * l2_serial) / (2.0 * L * l1_serial));
      q[KNEE] = -M_PI + acos((l1_serial * l1_serial + l2_serial * l2_serial - L * L) / (2.0 * l1_serial * l2_serial));
    } else if (leg_num == 2 || leg_num == 3) {
      //! 後脚の場合の処理
      q[HIP_PITCH] = -atan2(p0.x(), std::hypot(p0.y(), p0.z())) -
                     acos((L * L + l1_serial * l1_serial - l2_serial * l2_serial) / (2.0 * L * l1_serial));
      q[KNEE] = M_PI - acos((l1_serial * l1_serial + l2_serial * l2_serial - L * L) / (2.0 * l1_serial * l2_serial));
    } else
      throw "The value of leg_num is out of range!";

    return true;

  } catch (const char* str) {
    //! 例外処理
    ROS_ERROR("%s", str);
    ROS_ERROR("[MELEW3_Kinematics] Can not calculate inverse kinematics!");
    return false;
  }
}

/**
 * @brief Calculate link position and joint angle of the robot
 *
 * @param leg_num : Leg number (FL:0, FR:1, BL:2, BR:3)
 * @param q       : Joint angle vector
 * @param p       : Answer of forward kinematics
 * @param psi     : Target yaw angle
 * @param _p_link  : Link position
 * @param _q_link  : Link angle
 * @return true
 * @return false
 */
bool MELEW3_Kinematics::solve_link_position_parallel(const Eigen::VectorXd& q, Eigen::Vector3d& p, double& psi,
                                                     std::vector<Eigen::Vector3d>& _p_link,
                                                     std::vector<double>&          _q_link) {
  return solve_link_position_parallel(0, q, p, psi, _p_link, _q_link);
}

/**
 * @brief Calculate link position and joint angle of the robot
 *
 * @param leg_num : Leg number (FL:0, FR:1, BL:2, BR:3)
 * @param q       : Joint angle vector
 * @param p       : Answer of forward kinematics
 * @param psi     : Target yaw angle
 * @param _p_link  : Link position
 * @param _q_link  : Link angle
 * @return true
 * @return false
 */
bool MELEW3_Kinematics::solve_link_position_parallel(const int leg_num, const Eigen::VectorXd& q, Eigen::Vector3d& p,
                                                     double& psi, std::vector<Eigen::Vector3d>& _p_link,
                                                     std::vector<double>& _q_link) {
  //! 実機の順運動学計算
  try {
    if (solve_FK_parallel(q, p, psi)) {
      //! 各リンクの座標の計算
      _p_link.resize(14);
      _p_link[0] << 0.0, 0.0, 0.0;
      _p_link[1] << 0.0, l_A1, 0.0;
      _p_link[2] << 0.0, l_A2, 0.0;
      _p_link[3] << 0.0, -l_A2, 0.0;
      _p_link[4] << 0.0, -l_A1, 0.0;
      _p_link[5] << p_b1.x() * l_B1, p_b1.y() * l_B1, p_b1.z() * l_B1;
      _p_link[6] << p_b2.x() * l_B2, p_b2.y() * l_B2, p_b2.z() * l_B2;
      _p_link[7] << p_b3.x() * l_B2, p_b3.y() * l_B2, p_b3.z() * l_B2;
      _p_link[8] << p_b4.x() * l_B1, p_b4.y() * l_B1, p_b4.z() * l_B1;
      _p_link[9] << (l_C / l1_parallel) * p_D1.x(), (l_C / l1_parallel) * p_D1.y(), (l_C / l1_parallel) * p_D1.z();
      _p_link[10] << (l_C / l2_parallel) * p_D2.x(), (l_C / l2_parallel) * p_D2.y(), (l_C / l2_parallel) * p_D2.z();
      _p_link[11] << p_D1.x(), p_D1.y(), p_D1.z();
      _p_link[12] << p_D2.x(), p_D2.y(), p_D2.z();
      _p_link[13] << p.x(), p.y(), p.z();

      //! 各リンクの関節角の計算
      _q_link.resize(14);
      _q_link[0] = 0.0;
      for (int i = 1; i <= 4; i++) _q_link[i] = q[i - 1];
      Eigen::Vector3d vD1 = (p_D1.cross(p_D2)).normalized();
      Eigen::Vector3d vD2 = (p_D2.cross(p_D1)).normalized();

      if (leg_num == 0 || leg_num == 1) {
        //! 前脚の場合の処理
        Eigen::Vector3d vb1 = (p_b1.cross(p_D1)).normalized();
        Eigen::Vector3d vb2 = (p_b2.cross(p_D2)).normalized();
        _q_link[5] = acos((l1_parallel - 4.0 * p_D1.y()) / (3.0 * l1_parallel));
        _q_link[6] = -acos((l2_parallel - 4.0 * p_D2.y()) / (3.0 * l2_parallel));
        _q_link[7] = -acos((l2_parallel + 4.0 * p_D2.y()) / (3.0 * l2_parallel));
        _q_link[8] = acos((l1_parallel + 4.0 * p_D1.y()) / (3.0 * l1_parallel));
        _q_link[9] = acos(vb1.dot(vD1));
        _q_link[10] = -acos(vb2.dot(vD2));
        _q_link[11] = acos(p_D1.dot(p_D2) / (l1_parallel * l2_parallel));
        _q_link[12] = -acos(p_D1.dot(p_D2) / (l1_parallel * l2_parallel));
      } else if (leg_num == 2 || leg_num == 3) {
        //! 後脚の場合の処理
        Eigen::Vector3d vb1 = (p_b1.cross(p_D2)).normalized();
        Eigen::Vector3d vb2 = (p_b2.cross(p_D1)).normalized();
        _q_link[5] = acos((l2_parallel - 4.0 * p_D2.y()) / (3.0 * l2_parallel));
        _q_link[6] = -acos((l1_parallel - 4.0 * p_D1.y()) / (3.0 * l1_parallel));
        _q_link[7] = -acos((l1_parallel + 4.0 * p_D1.y()) / (3.0 * l1_parallel));
        _q_link[8] = acos((l2_parallel + 4.0 * p_D2.y()) / (3.0 * l2_parallel));
        _q_link[9] = -acos(vb2.dot(vD1));
        _q_link[10] = acos(vb1.dot(vD2));
        _q_link[11] = -acos(p_D1.dot(p_D2) / (l1_parallel * l2_parallel));
        _q_link[12] = acos(p_D1.dot(p_D2) / (l1_parallel * l2_parallel));
      } else
        throw "The value of leg_num is out of range!";

      _q_link[13] = 0.0;

    } else
      throw "";

    return true;

  } catch (const char* str) {
    ROS_ERROR("%s", str);
    ROS_ERROR("[MELEW3_Kinematics] Cannot calculate joint angles!");
    return false;
  }
}

/**
 * @brief Calculate link position and joint angle of the simulation
 *
 * @param q       : Joint angle vector
 * @param p       : Answer of forward kinematics
 * @param psi     : Target yaw angle
 * @param _p_link  : Link position
 * @param _q_link  : Link angle
 * @return true
 * @return false
 */
bool MELEW3_Kinematics::solve_link_position_serial(const Eigen::VectorXd& q, Eigen::Vector3d& p, double& psi,
                                                   std::vector<Eigen::Vector3d>& _p_link,
                                                   std::vector<double>&          _q_link) {
  //! シミュレーションの順運動学計算
  if (solve_FK_serial(q, p, psi)) {
    //! 各リンクの座標の計算
    _p_link.resize(6);
    for (int i = 0; i <= 3; i++) _p_link[i] << 0.0, 0.0, 0.0;
    _p_link[4] = RotZ(q[0]) * RotX(q[1]) * RotY(q[2]) * Eigen::Vector3d(0, 0, -l1_serial);
    _p_link[5] << p.x(), p.y(), p.z();

    //! 各リンクの関節角の計算
    _q_link.resize(6);
    _q_link[0] = 0.0;
    for (int i = 1; i <= 4; i++) _q_link[i] = q[i - 1];
    _q_link[5] = 0.0;
    return true;
  } else
    return false;
}

/**
 * @brief Calculate the rotation matrix around X-axis
 *
 * @param q   : Rotation angle around X-axis
 * @param r   : Rotation matrix around X-axis
 * @return r
 */
Eigen::Matrix3d MELEW3_Kinematics::RotX(double q) {
  Eigen::Matrix3d r;
  r = Eigen::AngleAxisd(q, Eigen::Vector3d::UnitX());
  return r;
}

/**
 * @brief Calculate the rotation matrix around Y-axis
 *
 * @param q   : Rotation angle around Y-axis
 * @param r   : Rotation matrix around Y-axis
 * @return r
 */
Eigen::Matrix3d MELEW3_Kinematics::RotY(double q) {
  Eigen::Matrix3d r;
  r = Eigen::AngleAxisd(q, Eigen::Vector3d::UnitY());
  return r;
}

/**
 * @brief Calculate the rotation matrix around Z-axis
 *
 * @param q   : Rotation angle around Z-axis
 * @param r   : Rotation matrix around Z-axis
 * @return r
 */
Eigen::Matrix3d MELEW3_Kinematics::RotZ(double q) {
  Eigen::Matrix3d r;
  r = Eigen::AngleAxisd(q, Eigen::Vector3d::UnitZ());
  return r;
}

}  // namespace melew3_kinematics