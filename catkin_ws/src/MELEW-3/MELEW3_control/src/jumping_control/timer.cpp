#include <MELEW3_control/timer.hpp>
namespace MELEW3_control {
Timer::Timer(){

    MPC_dt = 0.01;
    MPC_count = 5;
    MPC_countor = 0;
    dt = 0.00333333;
}
} // namespace melew3