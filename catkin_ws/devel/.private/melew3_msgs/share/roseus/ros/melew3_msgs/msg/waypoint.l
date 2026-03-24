;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::waypoint)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'waypoint (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::WAYPOINT")
  (make-package "MELEW3_MSGS::WAYPOINT"))

(in-package "ROS")
;;//! \htmlinclude waypoint.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass melew3_msgs::waypoint
  :super ros::object
  :slots (_header _time _position _velocity _acceleration _yaw_position _yaw_velocity _yaw_acceleration ))

(defmethod melew3_msgs::waypoint
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:time __time) (instance std_msgs::Float64 :init))
    ((:position __position) (instance geometry_msgs::Point :init))
    ((:velocity __velocity) (instance geometry_msgs::Point :init))
    ((:acceleration __acceleration) (instance geometry_msgs::Point :init))
    ((:yaw_position __yaw_position) (instance std_msgs::Float64 :init))
    ((:yaw_velocity __yaw_velocity) (instance std_msgs::Float64 :init))
    ((:yaw_acceleration __yaw_acceleration) (instance std_msgs::Float64 :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _time __time)
   (setq _position __position)
   (setq _velocity __velocity)
   (setq _acceleration __acceleration)
   (setq _yaw_position __yaw_position)
   (setq _yaw_velocity __yaw_velocity)
   (setq _yaw_acceleration __yaw_acceleration)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:time
   (&rest __time)
   (if (keywordp (car __time))
       (send* _time __time)
     (progn
       (if __time (setq _time (car __time)))
       _time)))
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:velocity
   (&rest __velocity)
   (if (keywordp (car __velocity))
       (send* _velocity __velocity)
     (progn
       (if __velocity (setq _velocity (car __velocity)))
       _velocity)))
  (:acceleration
   (&rest __acceleration)
   (if (keywordp (car __acceleration))
       (send* _acceleration __acceleration)
     (progn
       (if __acceleration (setq _acceleration (car __acceleration)))
       _acceleration)))
  (:yaw_position
   (&rest __yaw_position)
   (if (keywordp (car __yaw_position))
       (send* _yaw_position __yaw_position)
     (progn
       (if __yaw_position (setq _yaw_position (car __yaw_position)))
       _yaw_position)))
  (:yaw_velocity
   (&rest __yaw_velocity)
   (if (keywordp (car __yaw_velocity))
       (send* _yaw_velocity __yaw_velocity)
     (progn
       (if __yaw_velocity (setq _yaw_velocity (car __yaw_velocity)))
       _yaw_velocity)))
  (:yaw_acceleration
   (&rest __yaw_acceleration)
   (if (keywordp (car __yaw_acceleration))
       (send* _yaw_acceleration __yaw_acceleration)
     (progn
       (if __yaw_acceleration (setq _yaw_acceleration (car __yaw_acceleration)))
       _yaw_acceleration)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; std_msgs/Float64 _time
    (send _time :serialization-length)
    ;; geometry_msgs/Point _position
    (send _position :serialization-length)
    ;; geometry_msgs/Point _velocity
    (send _velocity :serialization-length)
    ;; geometry_msgs/Point _acceleration
    (send _acceleration :serialization-length)
    ;; std_msgs/Float64 _yaw_position
    (send _yaw_position :serialization-length)
    ;; std_msgs/Float64 _yaw_velocity
    (send _yaw_velocity :serialization-length)
    ;; std_msgs/Float64 _yaw_acceleration
    (send _yaw_acceleration :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; std_msgs/Float64 _time
       (send _time :serialize s)
     ;; geometry_msgs/Point _position
       (send _position :serialize s)
     ;; geometry_msgs/Point _velocity
       (send _velocity :serialize s)
     ;; geometry_msgs/Point _acceleration
       (send _acceleration :serialize s)
     ;; std_msgs/Float64 _yaw_position
       (send _yaw_position :serialize s)
     ;; std_msgs/Float64 _yaw_velocity
       (send _yaw_velocity :serialize s)
     ;; std_msgs/Float64 _yaw_acceleration
       (send _yaw_acceleration :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; std_msgs/Float64 _time
     (send _time :deserialize buf ptr-) (incf ptr- (send _time :serialization-length))
   ;; geometry_msgs/Point _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; geometry_msgs/Point _velocity
     (send _velocity :deserialize buf ptr-) (incf ptr- (send _velocity :serialization-length))
   ;; geometry_msgs/Point _acceleration
     (send _acceleration :deserialize buf ptr-) (incf ptr- (send _acceleration :serialization-length))
   ;; std_msgs/Float64 _yaw_position
     (send _yaw_position :deserialize buf ptr-) (incf ptr- (send _yaw_position :serialization-length))
   ;; std_msgs/Float64 _yaw_velocity
     (send _yaw_velocity :deserialize buf ptr-) (incf ptr- (send _yaw_velocity :serialization-length))
   ;; std_msgs/Float64 _yaw_acceleration
     (send _yaw_acceleration :deserialize buf ptr-) (incf ptr- (send _yaw_acceleration :serialization-length))
   ;;
   self)
  )

(setf (get melew3_msgs::waypoint :md5sum-) "c206810b38430fa29a10e74179d3b4cd")
(setf (get melew3_msgs::waypoint :datatype-) "melew3_msgs/waypoint")
(setf (get melew3_msgs::waypoint :definition-)
      "std_msgs/Header header
std_msgs/Float64 time # 時刻
geometry_msgs/Point position # 位置
geometry_msgs/Point velocity # 速度
geometry_msgs/Point acceleration # 加速度
std_msgs/Float64 yaw_position # 操舵角
std_msgs/Float64 yaw_velocity # 操舵角速度
std_msgs/Float64 yaw_acceleration # 操舵角加速度
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: std_msgs/Float64
float64 data
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :melew3_msgs/waypoint "c206810b38430fa29a10e74179d3b4cd")


