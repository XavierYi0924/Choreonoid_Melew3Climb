/**
 * @file motor_status.h
 * @author Taisei Suzuki
 * @brief
 * @version 1.0
 * @date 2023-08-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef MOTOR_STATUS_H_
#define MOTOR_STATUS_H_
#include <stdint.h>

#include <string>

// number of bits
#define POSITION_BIT_NUM 16
#define VELOCITY_BIT_NUM 12
#define EFFORT_BIT_NUM 12
#define KP_BIT_NUM 12
#define KD_BIT_NUM 12
#define MAX_OUTPUT_BIT_NUM 12

// Motor Configuration Commands
enum configuration { ENTER_CONTROL_MODE, EXIT_CONTROL_MODE, SET_POSITION_TO_ZERO, INITIALIZE_LOCK };

// 実数で0に対応する値
#define CENTER_POSITION 32768
#define CENTER_VELOCITY 2048
#define CENTER_EFFORT 2048

static constexpr double KP_MAX = 500.0f;
static constexpr double KP_MIN = 0.0f;
static constexpr double KD_MAX = 5.0f;
static constexpr double KD_MIN = 0.0f;

struct motor_status {
  std::string name;        // モータ名前
  std::string model;       // モータ型番
  uint16_t    can_id = 0;  // モータのCAN_ID．初期値は0．

  bool servo_mode = false;        // サーボ状態
  bool isExceedLimit = false;     // 可動角を超えているかどうか？（現在未使用）
  bool inverseDirection = false;  // モータと出力軸の正方向が逆か？

  // Maximum/Minimum value of position, velocity, effort
  double P_MAX, P_MIN;
  double V_MAX, V_MIN;
  double T_MAX, T_MIN;

  // 可動角
  float upper_limit;           // 上限可動角[rad]
  float lower_limit;           // 下限可動角[rad]
  bool  isLimitExist = false;  // 無限回転可能かそうでないか？

  float max_output;

  double position = 0.0;
  double velocity = 0.0;
  double effort = 0.0;

  double error = 0.0;   // モータの原点と関節の原点の誤差値．初期値は0．
  double offset = 0.0;  // モータのゼロ点合わせ位置と実際のゼロ点との差

  double position_raw = 0.0;  // モータ角度[rad]
  double velocity_raw = 0.0;
  double effort_raw = 0.0;

  double position_ref = 0.0;  // 目標出力軸角度[rad]
  double position_ref_old = 0.0;
  double velocity_ref = 0.0;
  double effort_ref = 0.0;

  int position_overflow_count = 0;  // 上限下限を超えた回数(現在未使用)
  int velocity_overflow_count = 0;
  int effort_overflow_count = 0;

  double Kp = 0.0;
  double Kd = 0.0;
};

#endif
