;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::leg_info_set)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'leg_info_set (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::LEG_INFO_SET")
  (make-package "MELEW3_MSGS::LEG_INFO_SET"))

(in-package "ROS")
;;//! \htmlinclude leg_info_set.msg.html


(defclass melew3_msgs::leg_info_set
  :super ros::object
  :slots (_leg ))

(defmethod melew3_msgs::leg_info_set
  (:init
   (&key
    ((:leg __leg) ())
    )
   (send-super :init)
   (setq _leg __leg)
   self)
  (:leg
   (&rest __leg)
   (if (keywordp (car __leg))
       (send* _leg __leg)
     (progn
       (if __leg (setq _leg (car __leg)))
       _leg)))
  (:serialization-length
   ()
   (+
    ;; melew3_msgs/leg_info[] _leg
    (apply #'+ (send-all _leg :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; melew3_msgs/leg_info[] _leg
     (write-long (length _leg) s)
     (dolist (elem _leg)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; melew3_msgs/leg_info[] _leg
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _leg (let (r) (dotimes (i n) (push (instance melew3_msgs::leg_info :init) r)) r))
     (dolist (elem- _leg)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get melew3_msgs::leg_info_set :md5sum-) "60a0c1f02ecf6d55f23aa1de78f2fe2b")
(setf (get melew3_msgs::leg_info_set :datatype-) "melew3_msgs/leg_info_set")
(setf (get melew3_msgs::leg_info_set :definition-)
      "# 脚先位置のpub用
melew3_msgs/leg_info[] leg
================================================================================
MSG: melew3_msgs/leg_info
geometry_msgs/Point32 position
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



(provide :melew3_msgs/leg_info_set "60a0c1f02ecf6d55f23aa1de78f2fe2b")


