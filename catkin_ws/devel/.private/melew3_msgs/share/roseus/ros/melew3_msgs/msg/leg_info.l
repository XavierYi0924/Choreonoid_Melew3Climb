;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::leg_info)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'leg_info (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::LEG_INFO")
  (make-package "MELEW3_MSGS::LEG_INFO"))

(in-package "ROS")
;;//! \htmlinclude leg_info.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass melew3_msgs::leg_info
  :super ros::object
  :slots (_position _yaw ))

(defmethod melew3_msgs::leg_info
  (:init
   (&key
    ((:position __position) (instance geometry_msgs::Point32 :init))
    ((:yaw __yaw) (instance std_msgs::Float64 :init))
    )
   (send-super :init)
   (setq _position __position)
   (setq _yaw __yaw)
   self)
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:yaw
   (&rest __yaw)
   (if (keywordp (car __yaw))
       (send* _yaw __yaw)
     (progn
       (if __yaw (setq _yaw (car __yaw)))
       _yaw)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point32 _position
    (send _position :serialization-length)
    ;; std_msgs/Float64 _yaw
    (send _yaw :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point32 _position
       (send _position :serialize s)
     ;; std_msgs/Float64 _yaw
       (send _yaw :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point32 _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; std_msgs/Float64 _yaw
     (send _yaw :deserialize buf ptr-) (incf ptr- (send _yaw :serialization-length))
   ;;
   self)
  )

(setf (get melew3_msgs::leg_info :md5sum-) "d4617fc0ec53327f436a5e22e15be77a")
(setf (get melew3_msgs::leg_info :datatype-) "melew3_msgs/leg_info")
(setf (get melew3_msgs::leg_info :definition-)
      "geometry_msgs/Point32 position
std_msgs/Float64 yaw
================================================================================
MSG: geometry_msgs/Point32
# This contains the position of a point in free space(with 32 bits of precision).
# It is recommeded to use Point wherever possible instead of Point32.  
# 
# This recommendation is to promote interoperability.  
#
# This message is designed to take up less space when sending
# lots of points at once, as in the case of a PointCloud.  

float32 x
float32 y
float32 z
================================================================================
MSG: std_msgs/Float64
float64 data
")



(provide :melew3_msgs/leg_info "d4617fc0ec53327f436a5e22e15be77a")


