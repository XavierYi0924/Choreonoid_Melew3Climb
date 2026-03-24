# How to create MELEW3 controller
 新しくコントローラを作成する場合は，「MELEW3_control::BaseController」クラスを派生させたコントローラクラスを作成してください．
 
その際，派生先のコンストラクタ内で`start_controller()`関数を呼び出すようにしてください．
これを実行することにより，各種topicをPublishする関数が定期的に実行されるようになります．

また，コントローラを停止させたい場合は`stop_controller()`関数を呼び出してください．
直ちにコントローラノードが停止されます．


# How to control MELEW3
ロボットの脚先位置`Eigen::Vector3d leg_pos_ref`と，脚先ヨー角`psi_ref`変数に値を書き込むと，裏で実行している関数からロボットを制御することが出来ます．
ただし，**絶対に連続な目標軌道を与えるよう**にしてください．
不連続な軌道を与えると，最悪ロボットが暴走します．
