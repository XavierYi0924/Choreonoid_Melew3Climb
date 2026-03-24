;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::enter_control_mode)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'enter_control_mode (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::ENTER_CONTROL_MODE")
  (make-package "MELEW3_MSGS::ENTER_CONTROL_MODE"))
(unless (find-package "MELEW3_MSGS::ENTER_CONTROL_MODEREQUEST")
  (make-package "MELEW3_MSGS::ENTER_CONTROL_MODEREQUEST"))
(unless (find-package "MELEW3_MSGS::ENTER_CONTROL_MODERESPONSE")
  (make-package "MELEW3_MSGS::ENTER_CONTROL_MODERESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::enter_control_modeRequest
  :super ros::object
  :slots (_name _CAN_ID _model ))

(defmethod melew3_msgs::enter_control_modeRequest
  (:init
   (&key
    ((:name __name) "")
    ((:CAN_ID __CAN_ID) 0)
    ((:model __model) "")
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _CAN_ID (round __CAN_ID))
   (setq _model (string __model))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:CAN_ID
   (&optional __CAN_ID)
   (if __CAN_ID (setq _CAN_ID __CAN_ID)) _CAN_ID)
  (:model
   (&optional __model)
   (if __model (setq _model __model)) _model)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; uint8 _CAN_ID
    1
    ;; string _model
    4 (length _model)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; uint8 _CAN_ID
       (write-byte _CAN_ID s)
     ;; string _model
       (write-long (length _model) s) (princ _model s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint8 _CAN_ID
     (setq _CAN_ID (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; string _model
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _model (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass melew3_msgs::enter_control_modeResponse
  :super ros::object
  :slots (_success ))

(defmethod melew3_msgs::enter_control_modeResponse
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

(defclass melew3_msgs::enter_control_mode
  :super ros::object
  :slots ())

(setf (get melew3_msgs::enter_control_mode :md5sum-) "d1a68f1452832714a857b39d4b4ecf8d")
(setf (get melew3_msgs::enter_control_mode :datatype-) "melew3_msgs/enter_control_mode")
(setf (get melew3_msgs::enter_control_mode :request) melew3_msgs::enter_control_modeRequest)
(setf (get melew3_msgs::enter_control_mode :response) melew3_msgs::enter_control_modeResponse)

(defmethod melew3_msgs::enter_control_modeRequest
  (:response () (instance melew3_msgs::enter_control_modeResponse :init)))

(setf (get melew3_msgs::enter_control_modeRequest :md5sum-) "d1a68f1452832714a857b39d4b4ecf8d")
(setf (get melew3_msgs::enter_control_modeRequest :datatype-) "melew3_msgs/enter_control_modeRequest")
(setf (get melew3_msgs::enter_control_modeRequest :definition-)
      "# CAN_ID of the motor
string name
uint8 CAN_ID
string model
---
# Whether if configuration success
bool success
")

(setf (get melew3_msgs::enter_control_modeResponse :md5sum-) "d1a68f1452832714a857b39d4b4ecf8d")
(setf (get melew3_msgs::enter_control_modeResponse :datatype-) "melew3_msgs/enter_control_modeResponse")
(setf (get melew3_msgs::enter_control_modeResponse :definition-)
      "# CAN_ID of the motor
string name
uint8 CAN_ID
string model
---
# Whether if configuration success
bool success
")



(provide :melew3_msgs/enter_control_mode "d1a68f1452832714a857b39d4b4ecf8d")


