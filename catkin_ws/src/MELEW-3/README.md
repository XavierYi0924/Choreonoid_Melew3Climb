# MELEW-3
**ME**iji **LE**g **W**heeled-robot - No. **3**

## 概要
4脚車輪ロボット「**MELEW-3**」用のコントローラ  

## 対応環境
Ubuntu 20.04  
ROS Noetic  
Choreonoid 1.8（開発版）

## ブランチ構成
- **main**：メインのブランチ
- **develop**：開発用ブランチ
  - develop-taisei：車輪走行シミュレーション用ブランチ
  - develop-taka：跳躍シミュレーション用ブランチ
  - develop-yoshinobu：歩行シミュレーション用ブランチ
- **experiment**：実験用ブランチ
  - experiment-jump：跳躍実験用ブランチ
  - experiment-walk：歩行実験用ブランチ
  - experiment-wheel：車輪走行実験用ブランチ

## インストール方法
$ `roscd`  
~/catkin_ws/src$ `git clone git@github.com:IRL-Meiji/MELEW-3.git`  
~/catkin_ws/src$ `roscd melew3`  
~/catkin_ws/src/MELEW-3/MELEW3$ `bash melew3_pkg.sh`  
~/catkin_ws/src/MELEW-3/MELEW3$ `catkin build melew3`

歩行用のコントローラを使用する場合は以下のコマンドを入力  
~/catkin_ws/src$ `git clone git@github.com:IRL-Meiji/MSPARC2.git`  
~/catkin_ws/src$ `catkin build`  

## 手順書　～起動から動作生成まで～

### <下準備>
#### １．PC，NUC，Raspberry Pi×4の電源を入れる

#### ２．PCとNUC，PCとRaspberry Piをssh接続
  ターミナルはこのPCのものと分けることを推奨  

##### ＜NUC＞  
  $ `ssh lw-nuc01@192.168.0.105`  
  成功したら[lw-nuc01@lwnuc01:~ $]と表示される

##### ＜raspberrypi-FL＞  
  $ `ssh irl-FL@192.168.0.101`  
  成功したら[irl@raspberrypi-FL:~ $]と表示される
  
##### ＜raspberrypi-FR＞  
  $ `ssh irl-FR@192.168.0.102`  
  成功したら[irl@raspberrypi-FR:~ $]と表示される

##### ＜raspberrypi-BL＞  
  $ `ssh irl-BL@192.168.0.103`  
  成功したら[irl@raspberrypi-BL:~ $]と表示される
  
##### ＜raspberrypi-BR＞  
  $ `ssh irl-BR@192.168.0.104`  
  成功したら[irl@raspberrypi-BR:~ $]と表示される

##### ＜CUIでNUCの電源を落とす方法＞  
  $ `sudo poweroff`

### <起動>
#### １．安定化電源の電源を入れる（アウトプット）

#### ２．ROSノードの立ち上げ
  ターミナルを起動後，下記の順にコマンドを入力

##### ＜laptopのターミナル＞  
  $ `roslaunch melew3_control melew3_control_laptop.launch`

##### ＜NUCのターミナル＞  
  $ `roslaunch xsens_mti_driver xsens_mti_node.launch`  
  IMUに接続できない場合は，以下のコマンドを入力してから再度実行する  
  $ `sudo chmod 777 /dev/ttyUSB0`

##### ＜raspberrypi-FLのターミナル＞  
  $ `rosrun candle_ros candle_ros_FL_node SPI 8M`

##### ＜raspberrypi-FRのターミナル＞  
  $ `rosrun candle_ros candle_ros_FR_node SPI 8M`

##### ＜raspberrypi-BLのターミナル＞  
  $ `rosrun candle_ros candle_ros_BL_node SPI 8M`

##### ＜raspberrypi-BRのターミナル＞  
  $ `rosrun candle_ros candle_ros_BR_node SPI 8M`

##### ＜laptopのターミナル＞  
  $ `roslaunch melew3_control melew3_motor_setting.launch`  
  Raspberry Piで[ROS_WARN]が表示されたら再度実行する

#### ３．原点出し
  新規にターミナルを起動後，下記コマンドを入力

##### ＜全てのモータを一気に設定する場合＞ 
  $ `rosservice call /MELEW3/set_position_to_zero ALL`
	
##### ＜各脚のモータを設定する場合＞  
  $ `rosservice call /MELEW3/set_position_to_zero FL`  
  $ `rosservice call /MELEW3/set_position_to_zero FR`  
  $ `rosservice call /MELEW3/set_position_to_zero BL`  
  $ `rosservice call /MELEW3/set_position_to_zero BR`  

##### ＜各モータごとに設定する場合＞  
  $ `rosservice call /MELEW3/set_position_to_zero FL1_motor`  
  $ `rosservice call /MELEW3/set_position_to_zero wheel_FL_motor`  
  
  成功したら[success: True]と表示される  

#### ４．サーボON
##### ＜全てのモータを一気に設定する場合＞  
  $ `rosservice call /MELEW3/servo_setting ALL 1`  

##### ＜各脚のモータを設定する場合＞  
  $ `rosservice call /MELEW3/servo_setting FL 1`  
  $ `rosservice call /MELEW3/servo_setting FR 1`  
  $ `rosservice call /MELEW3/servo_setting BL 1`  
  $ `rosservice call /MELEW3/servo_setting BR 1`  
  
  ＜各モータごとに設定する場合＞  
  $ `rosservice call /MELEW3/servo_setting FL1_motor 1`  
  $ `rosservice call /MELEW3/servo_setting wheel_FL_motor 1`  
  
  成功したら[success: True]と表示される  
  
#### ５．動作生成
  $ `rosrun melew3_control【ノード名】`  
  
  ＊注意＊  
  $ `rosrun melew3_control`  
	この時に「Tab」を2回押すと実行可能なノード名が表示される

### ＜その他＞	
#### ～データの保存方法～
  ＜例＞  
  $ `rosbag record -a -O 2024-02-20_022.bag`

  ＊注意＊  
	オプション機能 -a：全てのトピック（メッセージ）を計測  
	オプション機能 -O(オウ)：名前の指定  
    .bag：計測データの保存形式を指定  
	起動した瞬間から計測開始，停止する場所は「ctrl＋C」でプログラムを計測終了

#### ～計測データを可視化する方法～
  ＜例＞  
  $ `rosrun plotjuggler plotjuggler`

  ＊注意＊  
	File -> data：確認したいbagデータを選択  
	Timeseries List ->：確認したいトピックを選択しグラフにドラッグするとグラフが表示  
	右上の×を選択するとグラフの表示が消える 

#### ～リアルタイムでデータを可視化する方法～
  ＜例＞   
  $ `rqt_plot 【トピック名】`

  ＊注意＊    
	計測したいトピック名を指定するとグラフが表示される  
	「ctrl＋C」もしくはrqt_plotの終了でプログラムを計測終了

#### 〜モータのPDゲインを変更する方法〜
  1. rqt_reconfigureの画面上で「Refresh」を押し,「MELEW3」「MELEW3_control」の順に選択  
  2. モータのサーボをONにすると，現在のPDゲインの値がrqt_reconfigureに表示される  
  3. rqt_reconfigure上でPDゲインを変更  
  4. rqt_reconfigureの「Send」にチェックを入れる  

#### ～ファイルの中身を変更する方法～
  1. VSCodeで変更したいファイルを選択  
  2. ファイルの中身を変更してファイルを保存  
  3. VSCode下側のタブに以下を入力してビルド  
  $ `catkin build melew3_control`

## 手順書　～実験終了から電源を落とす～
### １．実行中のプログラムを切る  
  起動中のターミナルを選択し，「ctrl＋C」でプログラムを強制終了

### ２．電源を切る，アウトプット
  ＊注意＊  
  動作しているプログラムがないことを確認してから行う

## **シミュレーションの開始から停止までの操作方法**
1. `roslaunch melew3_control melew3_control.launch` でChoreonoidとros_controlを起動
2. Choreonoidのシミュレーション開始ボタンを押す
3. MELEW-3と同様に $ `rosrun melew3_control【ノード名】` でロボットの動作生成を行う
