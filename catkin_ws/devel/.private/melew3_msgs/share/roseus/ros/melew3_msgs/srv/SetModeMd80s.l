;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::SetModeMd80s)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'SetModeMd80s (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::SETMODEMD80S")
  (make-package "MELEW3_MSGS::SETMODEMD80S"))
(unless (find-package "MELEW3_MSGS::SETMODEMD80SREQUEST")
  (make-package "MELEW3_MSGS::SETMODEMD80SREQUEST"))
(unless (find-package "MELEW3_MSGS::SETMODEMD80SRESPONSE")
  (make-package "MELEW3_MSGS::SETMODEMD80SRESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::SetModeMd80sRequest
  :super ros::object
  :slots (_drive_ids _mode ))

(defmethod melew3_msgs::SetModeMd80sRequest
  (:init
   (&key
    ((:drive_ids __drive_ids) (make-array 0 :initial-element 0 :element-type :integer))
    ((:mode __mode) (let (r) (dotimes (i 0) (push "" r)) r))
    )
   (send-super :init)
   (setq _drive_ids __drive_ids)
   (setq _mode __mode)
   self)
  (:drive_ids
   (&optional __drive_ids)
   (if __drive_ids (setq _drive_ids __drive_ids)) _drive_ids)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; uint16[] _drive_ids
    (* 2    (length _drive_ids)) 4
    ;; string[] _mode
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _mode)) 4
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
     ;; string[] _mode
     (write-long (length _mode) s)
     (dolist (elem _mode)
       (write-long (length elem) s) (princ elem s)
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
   ;; string[] _mode
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _mode (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _mode i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;;
   self)
  )

(defclass melew3_msgs::SetModeMd80sResponse
  :super ros::object
  :slots (_drives_success ))

(defmethod melew3_msgs::SetModeMd80sResponse
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

(defclass melew3_msgs::SetModeMd80s
  :super ros::object
  :slots ())

(setf (get melew3_msgs::SetModeMd80s :md5sum-) "631d9a748d9039ca34b51f2d88d432cb")
(setf (get melew3_msgs::SetModeMd80s :datatype-) "melew3_msgs/SetModeMd80s")
(setf (get melew3_msgs::SetModeMd80s :request) melew3_msgs::SetModeMd80sRequest)
(setf (get melew3_msgs::SetModeMd80s :response) melew3_msgs::SetModeMd80sResponse)

(defmethod melew3_msgs::SetModeMd80sRequest
  (:response () (instance melew3_msgs::SetModeMd80sResponse :init)))

(setf (get melew3_msgs::SetModeMd80sRequest :md5sum-) "631d9a748d9039ca34b51f2d88d432cb")
(setf (get melew3_msgs::SetModeMd80sRequest :datatype-) "melew3_msgs/SetModeMd80sRequest")
(setf (get melew3_msgs::SetModeMd80sRequest :definition-)
      "uint16[] drive_ids
string[] mode
---
bool[] drives_success
")

(setf (get melew3_msgs::SetModeMd80sResponse :md5sum-) "631d9a748d9039ca34b51f2d88d432cb")
(setf (get melew3_msgs::SetModeMd80sResponse :datatype-) "melew3_msgs/SetModeMd80sResponse")
(setf (get melew3_msgs::SetModeMd80sResponse :definition-)
      "uint16[] drive_ids
string[] mode
---
bool[] drives_success
")



(provide :melew3_msgs/SetModeMd80s "631d9a748d9039ca34b51f2d88d432cb")


