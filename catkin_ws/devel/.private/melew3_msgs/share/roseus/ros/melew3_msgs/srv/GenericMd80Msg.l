;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::GenericMd80Msg)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'GenericMd80Msg (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::GENERICMD80MSG")
  (make-package "MELEW3_MSGS::GENERICMD80MSG"))
(unless (find-package "MELEW3_MSGS::GENERICMD80MSGREQUEST")
  (make-package "MELEW3_MSGS::GENERICMD80MSGREQUEST"))
(unless (find-package "MELEW3_MSGS::GENERICMD80MSGRESPONSE")
  (make-package "MELEW3_MSGS::GENERICMD80MSGRESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::GenericMd80MsgRequest
  :super ros::object
  :slots (_drive_ids ))

(defmethod melew3_msgs::GenericMd80MsgRequest
  (:init
   (&key
    ((:drive_ids __drive_ids) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _drive_ids __drive_ids)
   self)
  (:drive_ids
   (&optional __drive_ids)
   (if __drive_ids (setq _drive_ids __drive_ids)) _drive_ids)
  (:serialization-length
   ()
   (+
    ;; uint16[] _drive_ids
    (* 2    (length _drive_ids)) 4
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
   ;;
   self)
  )

(defclass melew3_msgs::GenericMd80MsgResponse
  :super ros::object
  :slots (_drives_success ))

(defmethod melew3_msgs::GenericMd80MsgResponse
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

(defclass melew3_msgs::GenericMd80Msg
  :super ros::object
  :slots ())

(setf (get melew3_msgs::GenericMd80Msg :md5sum-) "6cc3f83949e7e079c4afb6b3b48d05a1")
(setf (get melew3_msgs::GenericMd80Msg :datatype-) "melew3_msgs/GenericMd80Msg")
(setf (get melew3_msgs::GenericMd80Msg :request) melew3_msgs::GenericMd80MsgRequest)
(setf (get melew3_msgs::GenericMd80Msg :response) melew3_msgs::GenericMd80MsgResponse)

(defmethod melew3_msgs::GenericMd80MsgRequest
  (:response () (instance melew3_msgs::GenericMd80MsgResponse :init)))

(setf (get melew3_msgs::GenericMd80MsgRequest :md5sum-) "6cc3f83949e7e079c4afb6b3b48d05a1")
(setf (get melew3_msgs::GenericMd80MsgRequest :datatype-) "melew3_msgs/GenericMd80MsgRequest")
(setf (get melew3_msgs::GenericMd80MsgRequest :definition-)
      "uint16[] drive_ids
---
bool[] drives_success
")

(setf (get melew3_msgs::GenericMd80MsgResponse :md5sum-) "6cc3f83949e7e079c4afb6b3b48d05a1")
(setf (get melew3_msgs::GenericMd80MsgResponse :datatype-) "melew3_msgs/GenericMd80MsgResponse")
(setf (get melew3_msgs::GenericMd80MsgResponse :definition-)
      "uint16[] drive_ids
---
bool[] drives_success
")



(provide :melew3_msgs/GenericMd80Msg "6cc3f83949e7e079c4afb6b3b48d05a1")


