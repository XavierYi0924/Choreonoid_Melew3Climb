#ifndef AVAILABLE_MOTORS_H_
#define AVAILABLE_MOTORS_H_
#include <string>

// 利用可能なAKシリーズモータ一覧
// 各種パラメータはT-motorのHPから確認のこと（2021/07/15現在：以下のURLから確認可）
// https://store.tmotor.com/images/file/20210428/1619594329348464.pdf
namespace available_motors {
namespace AK10_9 {
static const std::string model_name = "AK10-9";
static constexpr float   P_MIN = -12.5f;
static constexpr float   P_MAX = 12.5f;
static constexpr float   V_MIN = -46.57f;
static constexpr float   V_MAX = 46.57f;
static constexpr float   T_MIN = -18.0f;
static constexpr float   T_MAX = 18.0f;
}  // namespace AK10_9

namespace AK80_9 {
static const std::string model_name = "AK80-9";
static constexpr float   P_MIN = -12.5f;
static constexpr float   P_MAX = 12.5f;
static constexpr float   V_MIN = -25.64f;
static constexpr float   V_MAX = 25.64f;
static constexpr float   T_MIN = -18.0f;
static constexpr float   T_MAX = 18.0f;
}  // namespace AK80_9

namespace AK80_6 {
static const std::string model_name = "AK80-6";
static constexpr float   P_MIN = -12.5f;
static constexpr float   P_MAX = 12.5f;
static constexpr float   V_MIN = -38.2f;
static constexpr float   V_MAX = 38.2f;
static constexpr float   T_MIN = -12.0f;
static constexpr float   T_MAX = 12.0f;
}  // namespace AK80_6

// 旧型のAK10-9
namespace AK10_9_OLD {
static const std::string model_name = "AK10-9_OLD";
static constexpr float   P_MIN = -95.5f;
static constexpr float   P_MAX = 95.5f;
static constexpr float   V_MIN = -12.5f;
static constexpr float   V_MAX = 12.5f;
static constexpr float   T_MIN = -18.0f;
static constexpr float   T_MAX = 18.0f;
}  // namespace AK10_9_OLD

namespace AK80_6_OLD {
static const std::string model_name = "AK80-6_OLD";
static constexpr float   P_MIN = -95.5f;
static constexpr float   P_MAX = 95.5f;
static constexpr float   V_MIN = -22.5f;
static constexpr float   V_MAX = 22.5f;
static constexpr float   T_MIN = -18.0f;
static constexpr float   T_MAX = 18.0f;
}  // namespace AK80_6_OLD
}  // namespace available_motors
#endif