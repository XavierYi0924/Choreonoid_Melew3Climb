;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::servo_setting)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'servo_setting (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::SERVO_SETTING")
  (make-package "MELEW3_MSGS::SERVO_SETTING"))
(unless (find-package "MELEW3_MSGS::SERVO_SETTINGREQUEST")
  (make-package "MELEW3_MSGS::SERVO_SETTINGREQUEST"))
(unless (find-package "MELEW3_MSGS::SERVO_SETTINGRESPONSE")
  (make-package "MELEW3_MSGS::SERVO_SETTINGRESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::servo_settingRequest
  :super ros::object
  :slots (_name _servo ))

(defmethod melew3_msgs::servo_settingRequest
  (:init
   (&key
    ((:name __name) "")
    ((:servo __servo) nil)
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _servo __servo)
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:servo
   (&optional (__servo :null))
   (if (not (eq __servo :null)) (setq _servo __servo)) _servo)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; bool _servo
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; bool _servo
       (if _servo (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _servo
     (setq _servo (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass melew3_msgs::servo_settingResponse
  :super ros::object
  :slots (_success ))

(defmethod melew3_msgs::servo_settingResponse
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

(defclass melew3_msgs::servo_setting
  :super ros::object
  :slots ())

(setf (get melew3_msgs::servo_setting :md5sum-) "40ae7cc676163ebf2724cc24e1fb1718")
(setf (get melew3_msgs::servo_setting :datatype-) "melew3_msgs/servo_setting")
(setf (get melew3_msgs::servo_setting :request) melew3_msgs::servo_settingRequest)
(setf (get melew3_msgs::servo_setting :response) melew3_msgs::servo_settingResponse)

(defmethod melew3_msgs::servo_settingRequest
  (:response () (instance melew3_msgs::servo_settingResponse :init)))

(setf (get melew3_msgs::servo_settingRequest :md5sum-) "40ae7cc676163ebf2724cc24e1fb1718")
(setf (get melew3_msgs::servo_settingRequest :datatype-) "melew3_msgs/servo_settingRequest")
(setf (get melew3_msgs::servo_settingRequest :definition-)
      "# CAN_ID of the motor
string name
bool servo
---
# Whether if configuration success
bool success
")

(setf (get melew3_msgs::servo_settingResponse :md5sum-) "40ae7cc676163ebf2724cc24e1fb1718")
(setf (get melew3_msgs::servo_settingResponse :datatype-) "melew3_msgs/servo_settingResponse")
(setf (get melew3_msgs::servo_settingResponse :definition-)
      "# CAN_ID of the motor
string name
bool servo
---
# Whether if configuration success
bool success
")



(provide :melew3_msgs/servo_setting "40ae7cc676163ebf2724cc24e1fb1718")


