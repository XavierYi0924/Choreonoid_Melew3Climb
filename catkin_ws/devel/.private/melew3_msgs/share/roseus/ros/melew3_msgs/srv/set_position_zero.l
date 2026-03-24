;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::set_position_zero)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'set_position_zero (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::SET_POSITION_ZERO")
  (make-package "MELEW3_MSGS::SET_POSITION_ZERO"))
(unless (find-package "MELEW3_MSGS::SET_POSITION_ZEROREQUEST")
  (make-package "MELEW3_MSGS::SET_POSITION_ZEROREQUEST"))
(unless (find-package "MELEW3_MSGS::SET_POSITION_ZERORESPONSE")
  (make-package "MELEW3_MSGS::SET_POSITION_ZERORESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::set_position_zeroRequest
  :super ros::object
  :slots (_name ))

(defmethod melew3_msgs::set_position_zeroRequest
  (:init
   (&key
    ((:name __name) "")
    )
   (send-super :init)
   (setq _name (string __name))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass melew3_msgs::set_position_zeroResponse
  :super ros::object
  :slots (_success ))

(defmethod melew3_msgs::set_position_zeroResponse
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

(defclass melew3_msgs::set_position_zero
  :super ros::object
  :slots ())

(setf (get melew3_msgs::set_position_zero :md5sum-) "d08a3b641c2f8680fbdfb1ea2e17a3e1")
(setf (get melew3_msgs::set_position_zero :datatype-) "melew3_msgs/set_position_zero")
(setf (get melew3_msgs::set_position_zero :request) melew3_msgs::set_position_zeroRequest)
(setf (get melew3_msgs::set_position_zero :response) melew3_msgs::set_position_zeroResponse)

(defmethod melew3_msgs::set_position_zeroRequest
  (:response () (instance melew3_msgs::set_position_zeroResponse :init)))

(setf (get melew3_msgs::set_position_zeroRequest :md5sum-) "d08a3b641c2f8680fbdfb1ea2e17a3e1")
(setf (get melew3_msgs::set_position_zeroRequest :datatype-) "melew3_msgs/set_position_zeroRequest")
(setf (get melew3_msgs::set_position_zeroRequest :definition-)
      "# CAN_ID of the motor
string name
---
# Whether if configuration success
bool success
")

(setf (get melew3_msgs::set_position_zeroResponse :md5sum-) "d08a3b641c2f8680fbdfb1ea2e17a3e1")
(setf (get melew3_msgs::set_position_zeroResponse :datatype-) "melew3_msgs/set_position_zeroResponse")
(setf (get melew3_msgs::set_position_zeroResponse :definition-)
      "# CAN_ID of the motor
string name
---
# Whether if configuration success
bool success
")



(provide :melew3_msgs/set_position_zero "d08a3b641c2f8680fbdfb1ea2e17a3e1")


