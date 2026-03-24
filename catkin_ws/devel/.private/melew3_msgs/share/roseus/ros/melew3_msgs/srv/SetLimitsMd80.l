;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::SetLimitsMd80)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'SetLimitsMd80 (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::SETLIMITSMD80")
  (make-package "MELEW3_MSGS::SETLIMITSMD80"))
(unless (find-package "MELEW3_MSGS::SETLIMITSMD80REQUEST")
  (make-package "MELEW3_MSGS::SETLIMITSMD80REQUEST"))
(unless (find-package "MELEW3_MSGS::SETLIMITSMD80RESPONSE")
  (make-package "MELEW3_MSGS::SETLIMITSMD80RESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::SetLimitsMd80Request
  :super ros::object
  :slots (_drive_ids _velocity_limit _torque_limit ))

(defmethod melew3_msgs::SetLimitsMd80Request
  (:init
   (&key
    ((:drive_ids __drive_ids) (make-array 0 :initial-element 0 :element-type :integer))
    ((:velocity_limit __velocity_limit) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:torque_limit __torque_limit) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _drive_ids __drive_ids)
   (setq _velocity_limit __velocity_limit)
   (setq _torque_limit __torque_limit)
   self)
  (:drive_ids
   (&optional __drive_ids)
   (if __drive_ids (setq _drive_ids __drive_ids)) _drive_ids)
  (:velocity_limit
   (&optional __velocity_limit)
   (if __velocity_limit (setq _velocity_limit __velocity_limit)) _velocity_limit)
  (:torque_limit
   (&optional __torque_limit)
   (if __torque_limit (setq _torque_limit __torque_limit)) _torque_limit)
  (:serialization-length
   ()
   (+
    ;; uint16[] _drive_ids
    (* 2    (length _drive_ids)) 4
    ;; float32[] _velocity_limit
    (* 4    (length _velocity_limit)) 4
    ;; float32[] _torque_limit
    (* 4    (length _torque_limit)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16[] _drive_ids
     (write-long (length _drive_ids) s)
     (dotimes (i (length _drive_ids))
       (write-word (elt _drive_ids i) s)
       )
     ;; float32[] _velocity_limit
     (write-long (length _velocity_limit) s)
     (dotimes (i (length _velocity_limit))
       (sys::poke (elt _velocity_limit i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _torque_limit
     (write-long (length _torque_limit) s)
     (dotimes (i (length _torque_limit))
       (sys::poke (elt _torque_limit i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16[] _drive_ids
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _drive_ids (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _drive_ids i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; float32[] _velocity_limit
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _velocity_limit (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _velocity_limit i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _torque_limit
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _torque_limit (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _torque_limit i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(defclass melew3_msgs::SetLimitsMd80Response
  :super ros::object
  :slots (_drives_success ))

(defmethod melew3_msgs::SetLimitsMd80Response
  (:init
   (&key
    ((:drives_success __drives_success) (let (r) (dotimes (i 0) (push nil r)) r))
    )
   (send-super :init)
   (setq _drives_success __drives_success)
   self)
  (:drives_success
   (&optional __drives_success)
   (if __drives_success (setq _drives_success __drives_success)) _drives_success)
  (:serialization-length
   ()
   (+
    ;; bool[] _drives_success
    (* 1    (length _drives_success)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool[] _drives_success
     (write-long (length _drives_success) s)
     (dotimes (i (length _drives_success))
       (if (elt _drives_success i) (write-byte -1 s) (write-byte 0 s))
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool[] _drives_success
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _drives_success (make-list n))
     (dotimes (i n)
     (setf (elt _drives_success i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;;
   self)
  )

(defclass melew3_msgs::SetLimitsMd80
  :super ros::object
  :slots ())

(setf (get melew3_msgs::SetLimitsMd80 :md5sum-) "8b812c4224ab59c832e9c192ff752c8d")
(setf (get melew3_msgs::SetLimitsMd80 :datatype-) "melew3_msgs/SetLimitsMd80")
(setf (get melew3_msgs::SetLimitsMd80 :request) melew3_msgs::SetLimitsMd80Request)
(setf (get melew3_msgs::SetLimitsMd80 :response) melew3_msgs::SetLimitsMd80Response)

(defmethod melew3_msgs::SetLimitsMd80Request
  (:response () (instance melew3_msgs::SetLimitsMd80Response :init)))

(setf (get melew3_msgs::SetLimitsMd80Request :md5sum-) "8b812c4224ab59c832e9c192ff752c8d")
(setf (get melew3_msgs::SetLimitsMd80Request :datatype-) "melew3_msgs/SetLimitsMd80Request")
(setf (get melew3_msgs::SetLimitsMd80Request :definition-)
      "uint16[] drive_ids
float32[] velocity_limit
float32[] torque_limit
---
bool[] drives_success
")

(setf (get melew3_msgs::SetLimitsMd80Response :md5sum-) "8b812c4224ab59c832e9c192ff752c8d")
(setf (get melew3_msgs::SetLimitsMd80Response :datatype-) "melew3_msgs/SetLimitsMd80Response")
(setf (get melew3_msgs::SetLimitsMd80Response :definition-)
      "uint16[] drive_ids
float32[] velocity_limit
float32[] torque_limit
---
bool[] drives_success
")



(provide :melew3_msgs/SetLimitsMd80 "8b812c4224ab59c832e9c192ff752c8d")


