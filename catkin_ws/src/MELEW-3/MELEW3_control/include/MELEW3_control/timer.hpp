#pragma once

namespace MELEW3_control {
// 時間に関するクラス
class Timer{
public:
    double current_time;        // 現在時刻
    int current_count;          // 現在カウント(1カウント1制御周期)
    int loop_count;
    int delta_count;

    double dt;          // 制御周期
    double MPC_dt;      // MPC周期
    int MPC_count;      // MPC1周期分カウント
    int MPC_countor;    // MPCカウンター

    double MPC_QPsolve_time;    // MPCのQPを解くのに要した時間
    double Stabilizer_QPsolve_time;     // 安定化制御のQPを解くのに要した時間
        
    double t_s;         // start time
    double t_rs;        // running start time
    double t_sqs;       // squat start time
    double t_sq;        // squat time
    double t_js;        // jump start time
    double t_f;         // flying time
    double t_l;         // landing time
    double t_je;        // jump end time
    double t_re;        // running end time
    double t_e;         // end time
    double t_lift;

    int c_ini;
    int c_s;
    int c_rs;
    int c_sqs;
    int c_sq;
    int c_js;
    int c_f;
    int c_l;
    int c_je;
    int c_re;
    int c_e;
    int c_lift;

    int l_ini;
    int l_s;
    int l_rs;
    int l_sqs;
    int l_sq;
    int l_js;
    int l_f;
    int l_l;
    int l_je;
    int l_re;
    int l_e;
    int l_lift;
    Timer();
};
}