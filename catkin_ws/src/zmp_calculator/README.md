# ZMP_CALCULATOR
## 概要
力覚センサから実ZMPを計測するROSパッケージ  
## 依存関係
- link_poses (シンプルコントローラでの実装が必要)

# zmp_calculator_node
力覚センサの値と位置・姿勢から実ZMPを計算する
## Subscribed Topics
- left_ft_sensor  (geometry_msgs/WrenchStamped)
  - 左脚の力覚センサの値
- right_ft_sensor (geometry_msgs/WrenchStamped)
  - 右脚の力覚センサの値
- link_poses  (geometry_msgs/PoseArray)
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
- ft_sensor_link_num_*  (int, default: 4, 10)
  - 力覚センサが乗っているリンクのID(*: L or R)
### 紐付かないもの
- left_ft_sensor_topic_name (string, default: /MSPARC/ForceSensor_foot_L)
  - 左脚の力覚センサ用トピック名 
- right_ft_sensor_topic_name  (string, default: /MSPARC/ForceSensor_foot_R)
  - 右脚の力覚センサ用トピック名  
- link_poses_topic_name (string, default: /MSPARC/link_poses)
  - 各リンクの位置・姿勢取得用トピック名
- actual_zmp_topic_name (string, default: /actual_zmp)
  - 実ZMPを出力するトピック名 