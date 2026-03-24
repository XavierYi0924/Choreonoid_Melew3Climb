# MELEW3_description
## パッケージの概要
ROS側で利用するロボットモデル等を管理する

## ディレクトリ構成
.  
├── config    
├── launch  
├── rviz  
├── urdf （URDF形式のロボットモデル）  
│   └── MELEW3_stl （モデルの構成ファイル）  
└── xacro （ロボットモデルxacroでまとめたもの）  

## 開発方法
ロボットモデルにアップデート等があれば，適切に変更する  
ros_controlで利用するhardware_interfaceなどの設定はURDF・xacroで行うので，そのへん参照  
ロボットモデルを作成したり，更新したりした際はlaunchディレクトリ内の"display.launch"などを利用して問題ないか確かめる

## TODO
MELLEWの残骸としていろいろ残っているので，そのへんの整理  
主に，config，rvizディレクトリ周りは整理したい（test_cnoid_ros_controlを参考にディレクトリ構造の変更）