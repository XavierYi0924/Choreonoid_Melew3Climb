#include <MELEW3_control/basic_op.h>

/*** float -> uint ***/
int float_to_uint(float x, float x_min, float x_max, int bits) {
  /*** bitの範囲を与える ***/
  float span = x_max - x_min;
  float offset = x_min;
  return (int)((x - offset) * ((float)((1 << bits) - 1)) / span);
}

/*** uint -> float ***/
float uint_to_float(int x_int, float x_min, float x_max, int bits) {
  /*** bitの範囲を与える ***/
  float span = x_max - x_min;
  float offset = x_min;
  return ((float)x_int) * span / ((float)((1 << bits) - 1)) + offset;
}

/*** rad -> deg ***/
float rad2deg(float rad) { return rad * (180.0f / M_PI); }

/*** deg -> rad ***/
float deg2rad(float deg) { return deg * (M_PI / 180.0f); }

/*** bがtrueなら符号を変える ***/
float signChange(float value, bool b) { return b ? -value : value; }

/*** 無限回転に対応 ***/
float infinite_rot(float value, float x_min, float x_max, float value_pre) {
  double value_range = x_max - x_min;
  int    passing_count = floor((value_pre + x_max) / value_range);
  if ((passing_count * value_range + value) - value_pre < x_min) {
    return passing_count * value_range + value + value_range;
  } else if ((passing_count * value_range + value) - value_pre > x_max) {
    return passing_count * value_range + value - value_range;
  } else {
    return passing_count * value_range + value;
  }
}

/*** 関節のオフセット角度をデジタル値に変換 ***/
int convertOffset(float offset, float x_min, float x_max, int bits) {
  float span = x_max - x_min;
  return (int)((offset / span) * ((float)((1 << bits) - 1)));
}

/*** あるデジタル値を等価な実数値に変換 ***/
/*** デジタル値の移動量を与えた後に等価な実数値での移動量に変換する際に使用 ***/
float uint_to_float_offset(int x_int, float x_min, float x_max, int bits) {
  /*** 一旦絶対値で考え，x_intの符号によって最終的に返す値の符号を変える ***/
  float span = x_max - x_min;
  float delta_p = ((float)abs(x_int)) * span / ((float)((1 << bits) - 1));

  return (x_int > 0) ? delta_p : -delta_p;
}