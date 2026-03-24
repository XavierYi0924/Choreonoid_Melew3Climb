#ifndef BASIC_OP_H_
#define BASIC_OP_H_

#include <algorithm>
#include <cmath>

int float_to_uint(float x, float x_min, float x_max, int bits);  // xmin~xmaxの間でbitsビットの量子化を行う
float uint_to_float(int x_int, float x_min, float x_max, int bits);

float rad2deg(float rad);
float deg2rad(float deg);

float signChange(float value, bool b);  // bがTrueならvalueの符号を反転させる

float infinite_rot(float value, float x_min, float x_max, float value_pre);

// 実数値offsetをデジタル値に変換するための関数
// デジタル値を等価な
int   convertOffset(float offset, float x_min, float x_max, int bits);
float uint_to_float_offset(int x_int, float x_min, float x_max, int bits);

// 値を範囲内に収める
template <typename T>
T clamp(T value, T min, T max) {
  return std::max(std::min(value, max), min);
}

#endif