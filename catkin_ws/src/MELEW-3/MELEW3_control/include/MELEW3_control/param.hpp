#pragma once
#include <iostream>
#include <vector>

#include "Calc_Matrix.hpp"

#define deg_to_rad 3.14159265 / 180.0
// 脚に存在する関節

enum JOINT : int { HIP_YAW, HIP_ROLL, HIP_PITCH, KNEE, WHEEL, JOINT_NUM };

enum LEG_FL_PARALLEL : int {
  FL1,
  FL2,
  FL3,
  FL4,
  SINGLE_LEG_JOINT_NUM  // 1脚の自由度数
};

enum LEG_FR_PARALLEL : int {
  FR1 = SINGLE_LEG_JOINT_NUM,
  FR2,
  FR3,
  FR4,
  DOUBLE_LEG_JOINT_NUM  // 2脚の自由度数
};

enum LEG_BL_PARALLEL : int {
  BL1 = DOUBLE_LEG_JOINT_NUM,
  BL2,
  BL3,
  BL4,
  TRIPLE_LEG_JOINT_NUM  // 3脚の自由度数
};

enum LEG_BR_PARALLEL : int {
  BR1 = TRIPLE_LEG_JOINT_NUM,
  BR2,
  BR3,
  BR4,
  QUADRUPLE_LEG_JOINT_NUM  // 4脚の自由度数
};

enum WHEEL : int {
  WHEEL_FL = QUADRUPLE_LEG_JOINT_NUM,
  WHEEL_FR,
  WHEEL_BL,
  WHEEL_BR,
  TOTAL_JOINT_NUM  // すべての自由度数
};

enum LEG_FL_SERIAL : int { HIP_YAW_FL, HIP_ROLL_FL, HIP_PITCH_FL, KNEE_FL };

enum LEG_FR_SERIAL : int { HIP_YAW_FR = SINGLE_LEG_JOINT_NUM, HIP_ROLL_FR, HIP_PITCH_FR, KNEE_FR };

enum LEG_BL_SERIAL : int { HIP_YAW_BL = DOUBLE_LEG_JOINT_NUM, HIP_ROLL_BL, HIP_PITCH_BL, KNEE_BL };

enum LEG_BR_SERIAL : int { HIP_BR = TRIPLE_LEG_JOINT_NUM, HIP_ROLL_BR, HIP_PITCH_BR, KNEE_BR };

enum LR : int { FL, FR, BL, BR, LEG_NUM };

enum LEG_FL_CONTROL : int {
  HIP_YAW_FL_CONTROLLER,
  HIP_ROLL_FL_CONTROLLER,
  HIP_PITCH_FL_CONTROLLER,
  KNEE_FL_CONTROLLER,
};

enum LEG_FR_CONTROL : int {
  HIP_YAW_FR_CONTROLLER,
  HIP_ROLL_FR_CONTROLLER,
  HIP_PITCH_FR_CONTROLLER,
  KNEE_FR_CONTROLLER,
};

enum LEG_BL_CONTROL : int {
  HIP_YAW_BL_CONTROLLER,
  HIP_ROLL_BL_CONTROLLER,
  HIP_PITCH_BL_CONTROLLER,
  KNEE_BL_CONTROLLER,
};

enum LEG_BR_CONTROL : int {
  HIP_YAW_BR_CONTROLLER,
  HIP_ROLL_BR_CONTROLLER,
  HIP_PITCH_BR_CONTROLLER,
  KNEE_BR_CONTROLLER,
};

enum WHEEL_CONTROL : int {
  WHEEL_FL_CONTROLLER,
  WHEEL_FR_CONTROLLER,
  WHEEL_BL_CONTROLLER,
  WHEEL_BR_CONTROLLER,
};

enum LINK_PARALLEL : int {
  BASE_PARALLEL,
  BODY_PARALLEL,
  A1_PARALLEL,
  A2_PARALLEL,
  A3_PARALLEL,
  A4_PARALLEL,
  B1_PARALLEL,
  B2_PARALLEL,
  B3_PARALLEL,
  B4_PARALLEL,
  C1_PARALLEL,
  C2_PARALLEL,
  D1_PARALLEL,
  D2_PARALLEL,
  WHEEL_PARALLEL
};
const int LINK_NUM_PARALLEL = WHEEL_PARALLEL;

enum LINK_SERIAL : int {
  BASE_SERIAL,
  BODY_SERIAL,
  HIP_YAW_SERIAL,
  HIP_ROLL_SERIAL,
  HIP_PITCH_SERIAL,
  KNEE_SERIAL,
  WHEEL_SERIAL
};
const int LINK_NUM_SERIAL = WHEEL_SERIAL;

namespace MELEW3_control {
// ロボットや制御のパラメータ・ゲインなどを管理するクラス
class Param {
public:
  //シミュレーション関連
  double g;                // 重力加速度
  int    total_count_num;  // シミュレーションの全カウント数
  double stature;          // half of robot length
  double obs_h;
  double s_dist;
  double mb;
  double mw;
  double m;
  // MPC関連
  int    Hp;         // 予測ホライズン
  int    Hu;         // 制御ホライズン
  int    Stanum;     // 状態量変数の数
  int    Stanum_AM;  // 状態量変数の数
  int    Inpnum;     // 入力変数の数
  int    Outnum;     // 出力変数の数
  double Large_num;  // 非常に大きな数
  double w_z;        // 出力重み
  double w_dx;       // 状態量重み
  double w_ddx;
  double w_cam;
  double w_dcam;
  double w_u;       // 入力重み
  int    nWSR;      // 大きくすると正確にQPを解く(?)
  double cpu_time;  // QPを解くときの制限時間
  bool   mpc_com_x_generate_flag;
  double mpc_zmp_max;
  double mpc_zmp_min;
  double mpc_yzmp_max;
  double mpc_yzmp_min;

  Param();
};

// 目標値を管理するクラス
class Reference {
public:
  Eigen::Vector3d dCoM_pg;    // pgに入力する目標速度
  Eigen::VectorXd zmp_pgref;  // XTG > VHIP

  double x_s;
  double x_f;  // 跳躍時の目標水平重心位置
  double x_l;
  double x_e;  // 終了時の目標水平重心位置

  double y_s;
  double y_f;  // 跳躍時の目標水平y重心位置
  double y_l;
  double y_e;  // 終了時の目標水平y重心位置

  double z_s;  // 跳躍動作開始重心鉛直高さ
  double z_sq;
  double z_f;  // 跳躍時重心鉛直高さ
  double z_l;  // 着地時重心鉛直高さ
  double z_e;
  double z_ref;  // 重心跳躍高さ

  double dx_f;   // 浮遊期中の目標水平速度
  double dy_f;   // 浮遊期中の目標水平速度
  double dz_f;   // 跳躍時鉛直重心速度
  double dz_ft;  // 跳躍時鉛直重心速度(For Trajectory)

  // オフライン目標軌道
  std::vector<Eigen::Vector3d> CoM;  // 目標重心軌道
  std::vector<Eigen::Vector3d> dCoM;
  std::vector<Eigen::Vector3d> ddCoM;
  std::vector<Eigen::Vector3d> dddCoM;
  std::vector<Eigen::Vector3d> AM;  // 目標重心角運動量
  std::vector<Eigen::Vector3d> dAM;
  std::vector<Eigen::Vector3d> ddAM;
  std::vector<Eigen::Vector3d> ZMP;
  std::vector<Eigen::Vector3d> gene_zmp;
  std::vector<Eigen::Vector3d> FL_foot;  // 足先軌道
  std::vector<Eigen::Vector3d> FR_foot;  // 足先軌道
  std::vector<Eigen::Vector3d> BL_foot;  // 足先軌道
  std::vector<Eigen::Vector3d> BR_foot;  // 足先軌道
};
}  // namespace MELEW3_control