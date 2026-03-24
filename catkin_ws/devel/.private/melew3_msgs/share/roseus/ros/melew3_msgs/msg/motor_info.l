;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::motor_info)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'motor_info (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::MOTOR_INFO")
  (make-package "MELEW3_MSGS::MOTOR_INFO"))

(in-package "ROS")
;;//! \htmlinclude motor_info.msg.html


(defclass melew3_msgs::motor_info
  :super ros::object
  :slots (_name _can_id ))

(defmethod melew3_msgs::motor_info
  (:init
   (&key
    ((:name __name) "")
    ((:can_id __can_id) 0)
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _can_id (round __can_id))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:can_id
   (&optional __can_id)
   (if __can_id (setq _can_id __can_id)) _can_id)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; uint8 _can_id
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; uint8 _can_id
       (write-byte _can_id s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint8 _can_id
     (setq _can_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get melew3_msgs::motor_info :md5sum-) "210d22ee910a155365074b193e163d8b")
(setf (get melew3_msgs::motor_info :datatype-) "melew3_msgs/motor_info")
(setf (get melew3_msgs::motor_info :definition-)
      "# Information for the motor to use
string name
uint8 can_id
")



(provide :melew3_msgs/motor_info "210d22ee910a155365074b193e163d8b")


