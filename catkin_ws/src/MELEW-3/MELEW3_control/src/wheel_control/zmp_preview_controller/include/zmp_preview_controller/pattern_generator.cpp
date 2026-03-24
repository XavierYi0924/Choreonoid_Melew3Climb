/**
 * @file    pattern_generator.cpp
 * @author  Yuta Ishizawa
 * @brief   予見制御による重心軌道生成器
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "pattern_generator.hpp"
/**
 * @brief Construct a new Pattern Generator:: Pattern Generator object
 *
 * @param com_height    : 目標重心高さ
 * @param sampling_time : サンプリング時間
 * @param preview_time  : 予見時間
 */
PatternGenerator::PatternGenerator(double com_height, double sampling_time, double preview_time)
    : com_height_(com_height),
      t_sampling_(sampling_time),
      t_preview_(preview_time),
      preview_controller(com_height_, t_sampling_, t_preview_) {}

/**
 * @brief 目標ZMP軌道から重心軌道を生成する関数
 *
 * @param zmp       目標とするZMP軌道
 * @param com       生成した重心軌道．原点からスタートするので適宜オフセットを設定すること
 * @param Qe        予見制御でのZMP誤差に対するゲイン
 * @param Ru        入力に対するゲイン
 * @param last_flag 終了時の処理かどうかを判定するフラグ
 */
void PatternGenerator::generate(std::vector<Eigen::Vector3d>& zmp, std::vector<Eigen::Vector3d>& com, double Qe,
                                double Ru, bool last_flag) {
  preview_controller.calculateParameter(Qe, Ru, com_height_);  // 予見制御クラスの初期化

  /*** 重心高さを格納 ***/
  for (int i = com_height_vector.size(); i < zmp.size(); i++) com_height_vector.push_back(zmp[i].z());

  for (int k_time = com.size(); k_time < zmp.size(); k_time++) {
    /*** 目標重心高さが変化した場合，ゲインを再計算 ***/
    if (std::abs(zmp[k_time].z() - com_height_pre) > 0.01) {
      preview_controller.calculateParameter(Qe, Ru, zmp[k_time].z());
      com_height_pre = zmp[k_time].z();
    }

    /*** 目標重心軌道を計算し，1個前の重心高さを更新 ***/
    if (!preview_controller.execute(k_time, zmp, com, com_height_vector, last_flag)) break;
  }
}

/**
 * @brief 目標ZMP軌道から重心軌道を生成する関数（比較手法）
 *
 * @param zmp       目標とするZMP軌道
 * @param com       生成した重心軌道．原点からスタートするので適宜オフセットを設定すること
 * @param Qe        予見制御でのZMP誤差に対するゲイン
 * @param Ru        入力に対するゲイン
 * @param last_flag 終了時の処理かどうかを判定するフラグ
 */
void PatternGenerator::notgenerate(std::vector<Eigen::Vector3d>& zmp, std::vector<Eigen::Vector3d>& com,
                                   bool last_flag) {
  /*** 重心高さを格納 ***/
  for (int i = com_height_vector.size(); i < zmp.size(); i++) com_height_vector.push_back(zmp[i].z());
  /*** 目標重心軌道を計算 ***/
  for (int k_time = com.size(); k_time < zmp.size(); k_time++) {
    if (!(k_time + (int)(t_preview_ / t_sampling_) <= zmp.size() | last_flag)) break;
    com.emplace_back(zmp[k_time]);
  }
}