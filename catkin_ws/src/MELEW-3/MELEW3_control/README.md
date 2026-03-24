# About this package
MELEW3を動かすためのコントローラ関連のパッケージ．  
大別すると以下の2種類のコードが存在．
- ros_controlの仕組みを利用できるようにするコード
- 機体を動かすためのコード

<br>

# MELEW3_controlと周辺ノードとの関係図
![MELEW3_control概念図](https://user-images.githubusercontent.com/40104484/137916515-7092bc0c-10b8-45db-a231-f2216352daad.jpg)


# ros_controlとの連携
実機とシミュレーションを同じコントローラで動かせるようにROS controlを利用．  
関連するファイルは以下の二つ．
- MELEW3_control.cpp
- MELEW3_HWI.cpp (HWI = Hardware Interface)

<br>

# ロボットの初期化方法
1. 「MELEW-2L」フォルダの「README.md」に習ってlaunchファイルを実行する．
2. ```$ rosservice call /MELEW_2L/set_zero_position <joint_name>``` で原点合わせを行う．  
<joint_name>には関節（モータ）名を入力すること．  
また，"ALL"を記入すると全てのモータを一気にゼロ点合わせを行える．

3. ```$ rosservice call /MELEW_2L/servo_setting <joint_name> <true/false>``` で関節のサーボを設定する．  
<joint_name>には関節（モータ）名を入力すること．  
また，"ALL"を記入すると全てのモータを一気にサーボの設定を行える．

4. ```$ rosrun MELEW_2L_control basic_pose``` で基準姿勢へ


# モータの位置を微調節したい場合
```
$ rosservice call /MELEW3/tweak_control <joint_name> <value>
```

- joint_name: 動かしたいモータの名前．rosparamに記載してあるものと同じ名前を入れること．
- value: 動かしたい移動量を指定．ただしデジタル値なので注意．範囲は -128 ~ 127 (Int8の範囲)まで．  
また，マイナスの値を指定する場合は，マイナスの符号が違うものに認識されてしまうので，その前に「--」(ハイフン2つ)をつけること．  
例．
```
$ rosservice call /MELEW3/tweak_control LO_motor -- -100
```

# ロボットを動かすコントローラ
各コントローラのソースコードは「MELEW3_control/src/controllers」フォルダ内にあります．  
The source file of every controller exist in 「MELEW3_control/src/controllers」 folder.

## BaseController.cpp
このクラスは全てのコントローラのテンプレートとなるクラスです．  
コントローラを新規に作成する場合は，このBaseControllerクラスを継承して作成してください．  
This file is the template for all the controllers.  
When creating a new controller, inherit from this class(BaseController) and design a new controller class.

## basic_pose.cpp
現在の状態から基準の姿勢に遷移させるコントローラ．

## move_constant_pose.cpp
現在の状態からある任意の姿勢に遷移させるコントローラ．

## x_sin_wave.cpp
x軸方向に正弦波軌道に屈伸運動させるコントローラ．  
振幅，周期，動作時間等は任意に与えられる．

## y_sin_wave.cpp
y軸方向に正弦波軌道に屈伸運動させるコントローラ．  
振幅，周期，動作時間等は任意に与えられる．

## z_sin_wave.cpp
z軸方向に正弦波軌道に屈伸運動させるコントローラ．  
振幅，周期，動作時間等は任意に与えられる．

## psi_sin_wave.cpp
Yaw軸回りに正弦波軌道に回転させるコントローラ．  
振幅，周期，動作時間等は任意に与えられる．

## offset_x_sin_wave.cpp
脚先に任意のオフセットを与えてx軸方向に正弦波軌道に屈伸運動させるコントローラ．  
振幅，周期，動作時間等，オフセットは任意に与えられる．

## offset_y_sin_wave.cpp
脚先に任意のオフセットを与えてy軸方向に正弦波軌道に屈伸運動させるコントローラ．  
振幅，周期，動作時間等，オフセットは任意に与えられる．

## offset_z_sin_wave.cpp
脚先に任意のオフセットを与えてz軸方向に正弦波軌道に屈伸運動させるコントローラ．  
振幅，周期，動作時間等，オフセットは任意に与えられる．

## offset_psi_sin_wave.cpp
脚先に任意のオフセットを与えてYaw軸回りに正弦波軌道に回転させるコントローラ．  
振幅，周期，動作時間等，オフセットは任意に与えられる．

## stepping_out.cpp
段差へ脚先を踏み出すコントローラ．  
MELEW-2Lの時と同様に3次スプライン補間にて軌道を生成．
