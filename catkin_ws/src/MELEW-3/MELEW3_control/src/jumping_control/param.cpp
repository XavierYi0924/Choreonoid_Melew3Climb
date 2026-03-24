#include <MELEW3_control/param.hpp>
namespace MELEW3_control {
Param::Param(){
    // mb = 26.8;
    // mw = 4.0;
    mb = 22.6;
    mw = 8.2;
    // mb = 30.8;
    // mw = 0.0;
    m = mb + mw;
    g = 9.80665;
    Hp = 150;
    Hu = 50;
    Stanum = 3;
    Stanum_AM = 5;
    Outnum = 1;
    Inpnum = 1;
    Large_num = 100000000.0;
    w_z = 1e2;
    // w_dx = 1e6;
    w_cam = 1e7;
    // w_dcam = 1e5;
    w_u = 1e0;
    nWSR = 1000;
    cpu_time = 0.005;
    mpc_com_x_generate_flag = false;
    mpc_zmp_max = 0.225;  // set later
    mpc_zmp_min = - 0.225;
    mpc_yzmp_max = 0.15;  // set later
    mpc_yzmp_min = - 0.15;
    stature = 0.25; 

}

} // namespace melew3