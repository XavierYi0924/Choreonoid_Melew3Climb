/**
 * @file    pattern_generator.hpp
 * @author  Yuta Ishizawa
 * @brief   予見制御による重心軌道生成器のヘッダ
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "preview_controller.hpp"

class PatternGenerator {
private:
  double com_height_;  //!< 目標重心高さ[m]
  double t_sampling_;  //!< サンプリング時間[s]
  double t_preview_;   //!< 予見時間[s]

  double              com_height_pre;     //!< 1個前の目標重心高さ[m]
  std::vector<double> com_height_vector;  //!< 目標重心高さをまとめたベクトル

  PreviewController preview_controller;  //!< 予見制御クラス

public:
  void generate(std::vector<Eigen::Vector3d>& zmp, std::vector<Eigen::Vector3d>& com, double Qe, double Ru,
                bool last_flag);
  void notgenerate(std::vector<Eigen::Vector3d>& zmp, std::vector<Eigen::Vector3d>& com, bool last_flag);
  PatternGenerator(double com_height, double sampling_time, double preview_time);
};