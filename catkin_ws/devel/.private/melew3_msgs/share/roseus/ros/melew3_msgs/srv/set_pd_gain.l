;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::set_pd_gain)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'set_pd_gain (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::SET_PD_GAIN")
  (make-package "MELEW3_MSGS::SET_PD_GAIN"))
(unless (find-package "MELEW3_MSGS::SET_PD_GAINREQUEST")
  (make-package "MELEW3_MSGS::SET_PD_GAINREQUEST"))
(unless (find-package "MELEW3_MSGS::SET_PD_GAINRESPONSE")
  (make-package "MELEW3_MSGS::SET_PD_GAINRESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::set_pd_gainRequest
  :super ros::object
  :slots (_mode ))

(defmethod melew3_msgs::set_pd_gainRequest
  (:init
   (&key
    ((:mode __mode) nil)
    )
   (send-super :init)
   (setq _mode __mode)
   self)
  (:mode
   (&optional (__mode :null))
   (if (not (eq __mode :null)) (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; bool _mode
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _mode
       (if _mode (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _mode
     (setq _mode (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass melew3_msgs::set_pd_gainResponse
  :super ros::object
  :slots (_success ))

(defmethod melew3_msgs::set_pd_gainResponse
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

(defclass melew3_msgs::set_pd_gain
  :super ros::object
  :slots ())

(setf (get melew3_msgs::set_pd_gain :md5sum-) "a585292d7f5827a6441e76e5026dbae6")
(setf (get melew3_msgs::set_pd_gain :datatype-) "melew3_msgs/set_pd_gain")
(setf (get melew3_msgs::set_pd_gain :request) melew3_msgs::set_pd_gainRequest)
(setf (get melew3_msgs::set_pd_gain :response) melew3_msgs::set_pd_gainResponse)

(defmethod melew3_msgs::set_pd_gainRequest
  (:response () (instance melew3_msgs::set_pd_gainResponse :init)))

(setf (get melew3_msgs::set_pd_gainRequest :md5sum-) "a585292d7f5827a6441e76e5026dbae6")
(setf (get melew3_msgs::set_pd_gainRequest :datatype-) "melew3_msgs/set_pd_gainRequest")
(setf (get melew3_msgs::set_pd_gainRequest :definition-)
      "# enable/disable
bool mode
---
# Whether if configuration success
bool success
")

(setf (get melew3_msgs::set_pd_gainResponse :md5sum-) "a585292d7f5827a6441e76e5026dbae6")
(setf (get melew3_msgs::set_pd_gainResponse :datatype-) "melew3_msgs/set_pd_gainResponse")
(setf (get melew3_msgs::set_pd_gainResponse :definition-)
      "# enable/disable
bool mode
---
# Whether if configuration success
bool success
")



(provide :melew3_msgs/set_pd_gain "a585292d7f5827a6441e76e5026dbae6")


