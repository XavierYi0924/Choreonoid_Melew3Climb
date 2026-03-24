# ZMP_CALCULATOR
力覚センサから実ZMPを計測するROSパッケージ  
TODO：出力する結果は座標系が適当なので，足先位置，センサ姿勢が取得できるように修正
# How to use
パラメータを設定後，zmp_calculator_nodeを起動する
## パラメータの設定
configディレクトリ内のparam.yamlにてパラメータの設定を行う  
loop_rate: 制御周期  
left_ft_sensor_topic_name: 左脚の力覚センサ用トピック名  
right_ft_sensor_topic_name: 右脚の力覚センサ用トピック名  
actual_zmp_topic_name: 出力するトピック名  
leg_num: 脚数  
support_area_◯_min: 脚の支持領域の最小値（x,y）  
support_area_◯_max: 脚の支持領域の最大値（x,y）  
min_contact_force: 脚の接地を判定する閾値  
