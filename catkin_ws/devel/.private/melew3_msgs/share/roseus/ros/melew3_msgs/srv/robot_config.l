;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::robot_config)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'robot_config (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::ROBOT_CONFIG")
  (make-package "MELEW3_MSGS::ROBOT_CONFIG"))
(unless (find-package "MELEW3_MSGS::ROBOT_CONFIGREQUEST")
  (make-package "MELEW3_MSGS::ROBOT_CONFIGREQUEST"))
(unless (find-package "MELEW3_MSGS::ROBOT_CONFIGRESPONSE")
  (make-package "MELEW3_MSGS::ROBOT_CONFIGRESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::robot_configRequest
  :super ros::object
  :slots (_motor ))

(defmethod melew3_msgs::robot_configRequest
  (:init
   (&key
    ((:motor __motor) ())
    )
   (send-super :init)
   (setq _motor __motor)
   self)
  (:motor
   (&rest __motor)
   (if (keywordp (car __motor))
       (send* _motor __motor)
     (progn
       (if __motor (setq _motor (car __motor)))
       _motor)))
  (:serialization-length
   ()
   (+
    ;; melew3_msgs/motor_info[] _motor
    (apply #'+ (send-all _motor :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; melew3_msgs/motor_info[] _motor
     (write-long (length _motor) s)
     (dolist (elem _motor)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; melew3_msgs/motor_info[] _motor
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _motor (let (r) (dotimes (i n) (push (instance melew3_msgs::motor_info :init) r)) r))
     (dolist (elem- _motor)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass melew3_msgs::robot_configResponse
  :super ros::object
  :slots (_motor_quantity _checksum ))

(defmethod melew3_msgs::robot_configResponse
  (:init
   (&key
    ((:motor_quantity __motor_quantity) 0)
    ((:checksum __checksum) 0)
    )
   (send-super :init)
   (setq _motor_quantity (round __motor_quantity))
   (setq _checksum (round __checksum))
   self)
  (:motor_quantity
   (&optional __motor_quantity)
   (if __motor_quantity (setq _motor_quantity __motor_quantity)) _motor_quantity)
  (:checksum
   (&optional __checksum)
   (if __checksum (setq _checksum __checksum)) _checksum)
  (:serialization-length
   ()
   (+
    ;; uint8 _motor_quantity
    1
    ;; uint8 _checksum
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _motor_quantity
       (write-byte _motor_quantity s)
     ;; uint8 _checksum
       (write-byte _checksum s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _motor_quantity
     (setq _motor_quantity (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _checksum
     (setq _checksum (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass melew3_msgs::robot_config
  :super ros::object
  :slots ())

(setf (get melew3_msgs::robot_config :md5sum-) "d0ea6905ae3e9bf592297d448a99911d")
(setf (get melew3_msgs::robot_config :datatype-) "melew3_msgs/robot_config")
(setf (get melew3_msgs::robot_config :request) melew3_msgs::robot_configRequest)
(setf (get melew3_msgs::robot_config :response) melew3_msgs::robot_configResponse)

(defmethod melew3_msgs::robot_configRequest
  (:response () (instance melew3_msgs::robot_configResponse :init)))

(setf (get melew3_msgs::robot_configRequest :md5sum-) "d0ea6905ae3e9bf592297d448a99911d")
(setf (get melew3_msgs::robot_configRequest :datatype-) "melew3_msgs/robot_configRequest")
(setf (get melew3_msgs::robot_configRequest :definition-)
      "# Information for robot to be passed to the microcontroller
melew3_msgs/motor_info[] motor

================================================================================
MSG: melew3_msgs/motor_info
# Information for the motor to use
string name
---
uint8 motor_quantity
uint8 checksum
")

(setf (get melew3_msgs::robot_configResponse :md5sum-) "d0ea6905ae3e9bf592297d448a99911d")
(setf (get melew3_msgs::robot_configResponse :datatype-) "melew3_msgs/robot_configResponse")
(setf (get melew3_msgs::robot_configResponse :definition-)
      "# Information for robot to be passed to the microcontroller
melew3_msgs/motor_info[] motor

================================================================================
MSG: melew3_msgs/motor_info
# Information for the motor to use
string name
---
uint8 motor_quantity
uint8 checksum
")



(provide :melew3_msgs/robot_config "d0ea6905ae3e9bf592297d448a99911d")


