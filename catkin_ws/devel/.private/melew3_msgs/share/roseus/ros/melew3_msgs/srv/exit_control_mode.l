;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::exit_control_mode)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'exit_control_mode (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::EXIT_CONTROL_MODE")
  (make-package "MELEW3_MSGS::EXIT_CONTROL_MODE"))
(unless (find-package "MELEW3_MSGS::EXIT_CONTROL_MODEREQUEST")
  (make-package "MELEW3_MSGS::EXIT_CONTROL_MODEREQUEST"))
(unless (find-package "MELEW3_MSGS::EXIT_CONTROL_MODERESPONSE")
  (make-package "MELEW3_MSGS::EXIT_CONTROL_MODERESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::exit_control_modeRequest
  :super ros::object
  :slots (_CAN_ID ))

(defmethod melew3_msgs::exit_control_modeRequest
  (:init
   (&key
    ((:CAN_ID __CAN_ID) 0)
    )
   (send-super :init)
   (setq _CAN_ID (round __CAN_ID))
   self)
  (:CAN_ID
   (&optional __CAN_ID)
   (if __CAN_ID (setq _CAN_ID __CAN_ID)) _CAN_ID)
  (:serialization-length
   ()
   (+
    ;; uint8 _CAN_ID
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _CAN_ID
       (write-byte _CAN_ID s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _CAN_ID
     (setq _CAN_ID (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass melew3_msgs::exit_control_modeResponse
  :super ros::object
  :slots (_success ))

(defmethod melew3_msgs::exit_control_modeResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass melew3_msgs::exit_control_mode
  :super ros::object
  :slots ())

(setf (get melew3_msgs::exit_control_mode :md5sum-) "d34ae0ac05d13cf23c6d78c27795e4e8")
(setf (get melew3_msgs::exit_control_mode :datatype-) "melew3_msgs/exit_control_mode")
(setf (get melew3_msgs::exit_control_mode :request) melew3_msgs::exit_control_modeRequest)
(setf (get melew3_msgs::exit_control_mode :response) melew3_msgs::exit_control_modeResponse)

(defmethod melew3_msgs::exit_control_modeRequest
  (:response () (instance melew3_msgs::exit_control_modeResponse :init)))

(setf (get melew3_msgs::exit_control_modeRequest :md5sum-) "d34ae0ac05d13cf23c6d78c27795e4e8")
(setf (get melew3_msgs::exit_control_modeRequest :datatype-) "melew3_msgs/exit_control_modeRequest")
(setf (get melew3_msgs::exit_control_modeRequest :definition-)
      "# CAN_ID of the motor
uint8 CAN_ID
---
# Whether if configuration success
bool success
")

(setf (get melew3_msgs::exit_control_modeResponse :md5sum-) "d34ae0ac05d13cf23c6d78c27795e4e8")
(setf (get melew3_msgs::exit_control_modeResponse :datatype-) "melew3_msgs/exit_control_modeResponse")
(setf (get melew3_msgs::exit_control_modeResponse :definition-)
      "# CAN_ID of the motor
uint8 CAN_ID
---
# Whether if configuration success
bool success
")



(provide :melew3_msgs/exit_control_mode "d34ae0ac05d13cf23c6d78c27795e4e8")


