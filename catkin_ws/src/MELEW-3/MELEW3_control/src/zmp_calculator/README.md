# ZMP_CALCULATOR
## 概要
力覚センサから実ZMPとImaginary ZMP（IZMP）を計測する
## 依存関係
- link_info (シンプルコントローラでの実装が必要)

# zmp_calculator_node
力覚センサの値と位置・姿勢から実ZMPを計算する
## Subscribed Topics
- FL_ft_sensor  (geometry_msgs/WrenchStamped)
  - 左前脚の力覚センサの値
- FR_ft_sensor  (geometry_msgs/WrenchStamped)
  - 右前脚の力覚センサの値
- BL_ft_sensor  (geometry_msgs/WrenchStamped)
  - 左後脚の力覚センサの値
- BR_ft_sensor  (geometry_msgs/WrenchStamped)
  - 右後脚の力覚センサの値
- link_info  (melew3_msgs/LinkInfoArray)
  - 各リンクの位置・姿勢
## Published Topics
- actual_zmp  (geometry_msgs/PointStamped)
  - 計算した実ZMP
## パラメータの設定
### 名前空間(/zmp)に紐づくもの
- loop_rate (double, default: 10)
  - 制御周期   
- leg_num (int, default: 2)
  - 脚数  
- support_area_*_min  (double, default: 0.0)
  - 脚の支持領域の最小値（*: x or y）  
- support_area_*_max  (double, default: 0.0)
  - 脚の支持領域の最大値（*: x or y）  
- min_contact_force (double, default: 10.0)
  - 脚の接地を判定する閾値  
- dt  (double, default: 0.001)
  - タイムステップ
- ft_sensor_link_num_*  (int, default: 7, 16，25，34)
  - 力覚センサが乗っているリンクのID(*: FL or FR or BL or BR)
### 紐付かないもの
- FL_ft_sensor_topic_name (string, default: /MELEW3/ForceSensor_foot_FL)
  - 左前脚の力覚センサ用トピック名 
- FR_ft_sensor_topic_name  (string, default: /MELEW3/ForceSensor_foot_FR)
  - 右前脚の力覚センサ用トピック名  
- BL_ft_sensor_topic_name (string, default: /MELEW3/ForceSensor_foot_BL)
  - 左後脚の力覚センサ用トピック名 
- BR_ft_sensor_topic_name  (string, default: /MELEW3/ForceSensor_foot_BR)
  - 右後脚の力覚センサ用トピック名  
- link_info_topic_name (string, default: /MELEW3/link_info)
  - 各リンクの位置・姿勢取得用トピック名
- actual_zmp_topic_name (string, default: /MELEW3/actual_zmp)
  - 実ZMPを出力するトピック名 

# zmp_calculator_node
ベースリンク位置とIMUの値からImaginary ZMP（IZMP）を計算する
## Subscribed Topics
- imu  (sensor_msgs/imu)
  - IMUセンサの値
- base  (melew3_msgs/Motion)
  - ベースリンク位置
- com  (melew3_msgs/Motion)
  - 重心位置
## Published Topics
- imaginary_zmp  (geometry_msgs/PointStamped)
  - 計算したImaginary ZMP（IZMP）
## パラメータの設定
### 名前空間(/zmp)に紐づくもの
- loop_rate (double, default: 10)
  - 制御周期   
- dt  (double, default: 0.001)
  - タイムステップ
### 紐付かないもの
- imu_topic_name (string, default: /MELEW3/imu)
  - IMU用トピック名 
- base_topic_name  (string, default: /MELEW3/base)
  - ベースリンク位置用トピック名  
- com_topic_name (string, default: /MELEW3/com)
  - 重心位置用トピック名 
- imaginary_zmp_topic_name  (string, default: /MELEW3/imaginary_zmp)
  - IZMPを出力するトピック名  