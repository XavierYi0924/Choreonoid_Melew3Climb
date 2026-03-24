/**
 * @file 　 plot_sne_contour3.cpp
 * @author  Taisei Suzuki
 * @brief   SNE等高線を用いて修正した支持多角形を描画するプログラム
 * @version 0.1
 * @date    2023-05-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <sne_controller/plot_sne_contour3.hpp>
namespace plt = matplotlibcpp;

/**
 * @brief Construct a new PlotSneContour::PlotSneContour object
 *
 * @param nh  ノードハンドル
 * @param pnh プライベートノードハンドル
 *
 */
PlotSneContour::PlotSneContour(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param("/sn/loop_rate", 100)) {
  // 変数の初期化
  d_leg = pnh.param("/sn/d_leg", 0.50);
  b_leg = pnh.param("/sn/b_leg", 0.40);
  phase = 0;

  // ベクトルの初期化
  SNE_threshold.resize(judge_num);
  foot.resize(LEG_NUM);
  x_p.resize(judge_num);
  x_p1.resize(judge_num);
  SNE_flag.resize(judge_num);
}

/**
 * @brief SNE等高線の(x, y)座標を設定する関数
 *
 * @param SNE   SNE [m]
 * @param theta 媒介変数θ [rad]
 * @param x     SNE等高線のx座標 [m]
 * @param y     SNE等高線のy座標 [m]
 *
 */
void PlotSneContour::CalcSneContour(const double SNE, const double theta, double& x, double& y) {
  //!< d(θ)の計算式
  const double d = (-(SNE + h * cos(phi)) * sin(phi) * cos(theta) +
                    sqrt(SNE * (SNE + 2.0 * h * cos(phi)) * (1.0 - sin(phi) * sin(phi) * sin(theta) * sin(theta)))) /
                   (cos(phi) * cos(phi));
  // (x, y)を計算
  x = d * cos(theta + xi);
  y = d * sin(theta + xi);
}

/**
 * @brief ZMPを計算する関数
 *
 */
void PlotSneContour::CalcZmp() {
  ZMP = Eigen::AngleAxisd(xi, Eigen::Vector3d::UnitZ()) * Eigen::Vector3d(-h * tan(phi), 0.0, 0.0);
}

/**
 * @brief 目標脚先位置と支持多角形の方向ベクトルを計算する関数
 *
 */
void PlotSneContour::CalcSupportPolygon() {
  std::vector<Eigen::Vector3d> p_foot(LEG_NUM);  //!< ZMPに対する脚先の相対位置 [m]

  // ZMPに対する脚先の相対位置を計算
  p_foot[FL] = Eigen::Vector3d(d_leg / 2.0, b_leg / 2.0, 0);
  p_foot[FR] = Eigen::Vector3d(d_leg / 2.0, -b_leg / 2.0, 0);
  p_foot[BL] = Eigen::Vector3d(-d_leg / 2.0, b_leg / 2.0, 0);
  p_foot[BR] = Eigen::Vector3d(-d_leg / 2.0, -b_leg / 2.0, 0);

  for (int i = 0; i < LEG_NUM; i++) foot[i] = p_foot[i] + ZMP;          // 目標脚先位置を計算
  support_porigon_vector = {foot[FL] - foot[FR], foot[FL] - foot[BL]};  // 支持多角形の方向ベクトルを定義
}

/**
 * @brief SNE等高線上の任意の傾きの接点を計算する関数
 *
 * @param num x_pのインデックス
 *
 */
void PlotSneContour::CalcPointOfTangency(const int num) {
  double                    a_angle;                             //!< 支持多角形の直線の偏角
  const std::vector<double> theta = {M_PI * 0.75, M_PI * 1.25};  //!< 角度θの初期値
  std::vector<double>       x0;                                  //!< 初期推測値
  double                    x, y;                                //!< 接点の(x, y)座標 [m]
  const double              epsilon = 1e-6;                      //!< ステップ幅
  const int                 max_iterations = 100;                //!< 最大反復回数
  const double              max_step = 0.1;                      //!< 最大ステップ幅

  // 支持多角形の直線の偏角を設定
  a_angle = atan(support_porigon_vector[num].y() / support_porigon_vector[num].x()) - xi;
  while (a_angle > M_PI / 2.0) a_angle -= M_PI;
  while (a_angle < -M_PI / 2.0) a_angle += M_PI;

  // 傾き(dy/dx)が定義可能な場合
  if (std::fabs(cos(a_angle)) > epsilon) {
    SneEquationSolver1 solver1(h, phi, SNE_threshold[num], a_angle);  // ニュートン法で角度θを計算するクラスを生成
    x0 = theta;                                                       // 初期値を設定

    for (int j = 0; j < x0.size(); j++) {
      if (solver1.newton_solve(x0[j], epsilon, max_iterations, max_step)) {  // 角度θを計算
        CalcSneContour(SNE_threshold[num], x0[j], x, y);                     // SNE等高線の(x, y)座標を計算
        x_p[num].push_back(Eigen::Vector3d(x, y, 0.0));                      // 接点座標を保存
      }
    }

    // 傾き(dy/dx)が定義不可能な場合
  } else {
    if (phi) {
      // 斜面の傾斜がある場合の角度θの解析解
      x0 = {acos(sqrt((SNE_threshold[num] * cos(phi)) / (2.0 * h)) / sin(phi)), M_PI,
            (2.0 * M_PI) - acos(sqrt((SNE_threshold[num] * cos(phi)) / (2.0 * h)) / sin(phi))};
    } else {
      x0 = {0.0, M_PI};  // 斜面の傾斜がない場合の角度θの解析解
    }

    for (int j = 0; j < x0.size(); j++) {
      CalcSneContour(SNE_threshold[num], x0[j], x, y);  // SNE等高線の(x, y)座標を計算
      x_p[num].push_back(Eigen::Vector3d(x, y, 0.0));   // 接点座標を保存
    }
  }
}

/**
 * @brief 支持多角形の修正量を計算する関数
 *
 * @param num x_pのインデックス
 *
 */
void PlotSneContour::CalcMovement(const int num) {
  std::vector<double> move_distance(judge_num);  //!< 移動距離(x,y) [m]
  double x1_max, x1_min;  //!< ZMPから支持線に向けて引いた位置ベクトルの，支持線に直交する成分 [m]

  for (int j = 0; j < x_p[num].size(); j++) {
    // ZMPから接点に向けて引いた位置ベクトルの，支持線に直交する成分を抽出
    x_p1[num].push_back(support_porigon_vector[1 - num].dot(x_p[num][j] - ZMP) /
                        support_porigon_vector[1 - num].norm());
  }

  // ZMPから支持線に向けて引いた位置ベクトルの，支持線に直交する成分を抽出（最大値）
  x1_max = support_porigon_vector[1 - num].dot(foot[FL] - ZMP) / support_porigon_vector[1 - num].norm();
  // ZMPから支持線に向けて引いた位置ベクトルの，支持線に直交する成分を抽出（最小値）
  x1_min = support_porigon_vector[1 - num].dot(foot[BR] - ZMP) / support_porigon_vector[1 - num].norm();

  // // 支持多角形を移動できないときの処理
  // if ((x1_max - x1_min) <
  //     (*max_element(x_p1[num].begin(), x_p1[num].end()) - *min_element(x_p1[num].begin(), x_p1[num].end()))) {
  //   ROS_ERROR("Can not move support polygon!");
  //   SNE_flag[num] = false;
  // }

  // else {
  // 支持多角形の移動量の計算
  x_p1[num].push_back(x1_max);
  x_p1[num].push_back(x1_min);
  // move_distance[num] = (*max_element(x_p1[num].begin(), x_p1[num].end()) - x1_max) +
  //                      (*min_element(x_p1[num].begin(), x_p1[num].end()) - x1_min);
  move_distance[num] = (*min_element(x_p1[num].begin(), x_p1[num].end()) - x1_min);

  // 支持多角形を移動
  for (int k = 0; k < LEG_NUM; k++)
    foot[k] += move_distance[num] * (support_porigon_vector[1 - num] / support_porigon_vector[1 - num].norm());
  SNE_flag[num] = true;
  //}

  // x_p，x_p1をリセット
  x_p[num].erase(x_p[num].begin(), x_p[num].end());
  x_p1[num].erase(x_p1[num].begin(), x_p1[num].end());
}

/**
 * @brief SNE等高線を描画する関数
 *
 */
void PlotSneContour::PlotSne() {
  const int                          n = 361;   //!< グラフの点の数
  double                             theta;     //!< 媒介変数θ [rad]
  std::vector<double>                x(n);      //!< SNE等高線のx座標 [m]
  std::vector<double>                y(n);      //!< SNE等高線のy座標 [m]
  std::map<std::string, std::string> args_SNE;  //!< SNEのグラフの設定用マップ

  for (int k = 0; k < SNE_list.size(); k++) {
    std::stringstream label_str;  //!< 図の凡例の文字列

    // SNE等高線(x,y)の計算
    for (int i = 0; i < n; i++) {
      theta = (double)i * (M_PI / 180.0);
      CalcSneContour(SNE_list[k], theta, x[i], y[i]);
    }

    // 凡例の設定
    label_str << "SNE=" << std::setprecision(3) << SNE_list[k] << "[m]";
    args_SNE = {{"label", label_str.str()}, {"c", color_list[k]}};

    plt::plot(x, y, args_SNE);  // SNE等高線の描画
  }
}

/**
 * @brief ZMPを描画する関数
 *
 */
void PlotSneContour::PlotZmp() {
  std::map<std::string, std::string> args_ZMP = {
      {"label", "ZMP"}, {"marker", "o"}, {"linestyle", "None"}, {"c", "gold"}};  //!< ZMPのグラフの設定用マップ
  plt::plot({ZMP.x()}, {ZMP.y()}, args_ZMP);                                     // ZMPの描画
}

/**
 * @brief 支持多角形を描画する関数
 *
 */
void PlotSneContour::PlotSupportPolygon(const int count) {
  std::vector<double>                             x(LEG_NUM);  //!< 支持多角形のx座標 [m]
  std::vector<double>                             y(LEG_NUM);  //!< 支持多角形のy座標 [m]
  std::vector<std::map<std::string, std::string>> args_foot = {
      {{"marker", "o"}, {"linestyle", "--"}, {"c", "red"}},
      {{"marker", "o"}, {"linestyle", "-"}, {"c", "red"}}};  //!< ZMPのグラフの設定用マップ

  // 支持多角形の(x,y)座標を生成
  x = {foot[FL].x(), foot[FR].x(), foot[BR].x(), foot[BL].x(), foot[FL].x()};
  y = {foot[FL].y(), foot[FR].y(), foot[BR].y(), foot[BL].y(), foot[FL].y()};

  plt::plot(x, y, args_foot[count]);  // 支持多角形の描画
}

/**
 * @brief SNE等高線上の任意の傾きの接点を描画する関数
 *
 * @param num x_pのインデックス
 *
 */
void PlotSneContour::PlotPointOfTangency(const int num) {
  std::map<std::string, std::string> args_PoT = {
      {"marker", "o"}, {"linestyle", "None"}, {"c", "k"}};  //!< 接点のグラフの設定用マップ
  for (int j = 0; j < x_p[num].size(); j++)
    plt::plot({x_p[num][j].x()}, {x_p[num][j].y()}, args_PoT);  // 接点座標を描画
}

/**
 * @brief 原点とZMPを通る直線を描画する関数
 *
 */
void PlotSneContour::PlotLine() {
  const double l = 0.75;                                                      //!< 原点から端までの長さ
  plt::plot({-l * cos(xi), l * cos(xi)}, {-l * sin(xi), l * sin(xi)}, "k-");  // グラフを描画
}

/**
 * @brief 図の初期設定を行う関数
 *
 */
void PlotSneContour::PlotSettings1() {
  plt::figure_size(960, 960);                  // 図のサイズを指定
  plt::set_aspect_equal();                     // アスペクト比を1に設定
  plt::xlabel("x [m]", {{"fontsize", "20"}});  // x軸のラベルの設定
  plt::ylabel("y [m]", {{"fontsize", "20"}});  // y軸のラベルの設定
  plt::xlim(-0.50, 0.50);                      // x軸のグラフの範囲の指定
  plt::ylim(-0.50, 0.50);                      // y軸のグラフの範囲の指定
  plt::grid(true);                             // グリッドを追加
}

/**
 * @brief 図の追加設定を行う関数
 *
 */
void PlotSneContour::PlotSettings2() {
  std::stringstream title;  //!< 図のタイトルの文字列

  // タイトルの設定
  title << "SNE Contour (h=" << std::setprecision(3) << h << "[m], φ=" << std::setprecision(3) << phi * (180.0 / M_PI)
        << "[deg], ξ=" << std::setprecision(3) << xi * (180.0 / M_PI) << "[deg])";
  plt::title(title.str(), {{"fontsize", "20"}});

  plt::legend({{"loc", "best"}});  // 図の凡例の設定
}

/**
 * @brief SNE等高線を用いて修正した支持多角形を描画する関数
 *
 */
void PlotSneContour::PlotSneContourCallback() {
  // 値の入力
  if (phase == 0) {
    std::vector<double> buf(5);  //!< 入力値

    try {
      ROS_INFO("Input the following values and press Enter key!");
      ROS_INFO("(1) SNE_x [m] : SNE threshold of in x-direction");
      ROS_INFO("(2) SNE_y [m] : SNE threshold of in y-direction");
      ROS_INFO("(3) h     [m] : Height of center of mass");
      ROS_INFO("(4) phi [deg] : Angle of slope");
      ROS_INFO("(5) xi  [deg] : Angle in upward direction of slope");
      ROS_INFO("Example input : 0.02 0.01 0.38 30 60");
      std::cin >> buf[0] >> buf[1] >> buf[2] >> buf[3] >> buf[4];  // 値の入力

      // 例外処理
      if (buf[0] <= 0.0) throw "SNE_x [m] is too low!";
      if (buf[1] <= 0.0) throw "SNE_y [m] is too low!";
      if (buf[2] <= 0.0) throw "h [m] is too low!";
      if (buf[3] < 0.0 || buf[3] >= 90.0) throw "phi [deg] is out of range!";

      // 入力された値を変数に格納
      SNE_threshold[0] = buf[0];
      SNE_threshold[1] = buf[1];
      h = buf[2];
      phi = buf[3] * (M_PI / 180.0);
      xi = buf[4] * (M_PI / 180.0);
      phase = 1;

    } catch (const char* str) {
      ROS_ERROR("%s", str);
      phase = 2;
    }
  }

  // 支持多角形の描画
  if (phase == 1) {
    PlotSettings1();        // 図の初期設定
    PlotSne();              // SNE等高線を描画
    CalcZmp();              // ZMPを計算
    if (phi) PlotLine();    // 斜面の場合，原点とZMPを通る直線を描画
    CalcSupportPolygon();   // 目標脚先位置を計算
    PlotSupportPolygon(0);  // 支持多角形の描画
    PlotZmp();              // ZMPを描画

    for (int i = 0; i < judge_num; i++) {
      CalcPointOfTangency(i);  // SNE等高線上の任意の傾きの接点を計算
      PlotPointOfTangency(i);  // SNE等高線上の任意の傾きの接点を描画
      CalcMovement(i);         // 支持多角形の修正量を計算
    }
    ROS_INFO("SNE_threshold (x,y) [m] : (%.3f, %.3f)", SNE_threshold[0], SNE_threshold[1]);

    while ((SNE_flag[0] & SNE_flag[1]) == 0) {
      for (int i = 0; i < judge_num; i++) {
        if (SNE_flag[i] == false) {
          SNE_threshold[i] -= 0.001;  // 支持多角形が移動できない場合，SNEの閾値を小さくする
          CalcPointOfTangency(i);     // SNE等高線上の任意の傾きの接点を計算
          PlotPointOfTangency(i);     // SNE等高線上の任意の傾きの接点を描画
          CalcMovement(i);            // 支持多角形の修正量を計算
        }
      }
      ROS_INFO("SNE_threshold (x,y) [m] : (%.3f, %.3f)", SNE_threshold[0], SNE_threshold[1]);
    }

    PlotSupportPolygon(1);                         // 支持多角形の描画
    PlotSettings2();                               // 図の追加設定
    plt::xticks(scale, {}, {{"fontsize", "15"}});  // x軸の目盛りの設定
    plt::yticks(scale, {}, {{"fontsize", "15"}});  // y軸の目盛りの設定
    plt::show();                                   // 図を表示
    phase = 2;
  }

  // 終了処理
  if (phase == 2) {
    ROS_INFO("Finish the controller!");
    ros::shutdown();
  }
}

/**
 * @brief SNE等高線を用いて修正した支持多角形を描画する関数
 *
 */
void PlotSneContour::Run() {
  while (nh_.ok()) {
    PlotSneContourCallback();
    ros::spinOnce();
    rate_.sleep();
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "PlotSneContourNode");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  PlotSneContour PlotSneContour(nh, pnh);
  PlotSneContour.Run();

  return 0;
}
