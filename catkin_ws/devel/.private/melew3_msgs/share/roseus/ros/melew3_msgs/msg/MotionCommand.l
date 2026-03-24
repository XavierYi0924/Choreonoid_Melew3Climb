;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::MotionCommand)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'MotionCommand (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::MOTIONCOMMAND")
  (make-package "MELEW3_MSGS::MOTIONCOMMAND"))

(in-package "ROS")
;;//! \htmlinclude MotionCommand.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass melew3_msgs::MotionCommand
  :super ros::object
  :slots (_header _drive_ids _target_position _target_velocity _target_torque ))

(defmethod melew3_msgs::MotionCommand
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:drive_ids __drive_ids) (make-array 0 :initial-element 0 :element-type :integer))
    ((:target_position __target_position) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:target_velocity __target_velocity) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:target_torque __target_torque) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _drive_ids __drive_ids)
   (setq _target_position __target_position)
   (setq _target_velocity __target_velocity)
   (setq _target_torque __target_torque)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:drive_ids
   (&optional __drive_ids)
   (if __drive_ids (setq _drive_ids __drive_ids)) _drive_ids)
  (:target_position
   (&optional __target_position)
   (if __target_position (setq _target_position __target_position)) _target_position)
  (:target_velocity
   (&optional __target_velocity)
   (if __target_velocity (setq _target_velocity __target_velocity)) _target_velocity)
  (:target_torque
   (&optional __target_torque)
   (if __target_torque (setq _target_torque __target_torque)) _target_torque)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint16[] _drive_ids
    (* 2    (length _drive_ids)) 4
    ;; float32[] _target_position
    (* 4    (length _target_position)) 4
    ;; float32[] _target_velocity
    (* 4    (length _target_velocity)) 4
    ;; float32[] _target_torque
    (* 4    (length _target_torque)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint16[] _drive_ids
     (write-long (length _drive_ids) s)
     (dotimes (i (length _drive_ids))
       (write-word (elt _drive_ids i) s)
       )
     ;; float32[] _target_position
     (write-long (length _target_position) s)
     (dotimes (i (length _target_position))
       (sys::poke (elt _target_position i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _target_velocity
     (write-long (length _target_velocity) s)
     (dotimes (i (length _target_velocity))
       (sys::poke (elt _target_velocity i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _target_torque
     (write-long (length _target_torque) s)
     (dotimes (i (length _target_torque))
       (sys::poke (elt _target_torque i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint16[] _drive_ids
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _drive_ids (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _drive_ids i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; float32[] _target_position
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _target_position (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _target_position i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _target_velocity
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _target_velocity (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _target_velocity i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _target_torque
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _target_torque (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _target_torque i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get melew3_msgs::MotionCommand :md5sum-) "f3f2b5bb30e5e58d7a8bf6136b909823")
(setf (get melew3_msgs::MotionCommand :datatype-) "melew3_msgs/MotionCommand")
(setf (get melew3_msgs::MotionCommand :definition-)
      "std_msgs/Header header
uint16[] drive_ids
float32[] target_position
float32[] target_velocity
float32[] target_torque
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

")



(provide :melew3_msgs/MotionCommand "f3f2b5bb30e5e58d7a8bf6136b909823")


