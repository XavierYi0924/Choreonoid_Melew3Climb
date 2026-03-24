;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::AddMd80s)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'AddMd80s (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::ADDMD80S")
  (make-package "MELEW3_MSGS::ADDMD80S"))
(unless (find-package "MELEW3_MSGS::ADDMD80SREQUEST")
  (make-package "MELEW3_MSGS::ADDMD80SREQUEST"))
(unless (find-package "MELEW3_MSGS::ADDMD80SRESPONSE")
  (make-package "MELEW3_MSGS::ADDMD80SRESPONSE"))

(in-package "ROS")





(defclass melew3_msgs::AddMd80sRequest
  :super ros::object
  :slots (_drive_ids ))

(defmethod melew3_msgs::AddMd80sRequest
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

(defclass melew3_msgs::AddMd80sResponse
  :super ros::object
  :slots (_drives_success _total_number_of_drives ))

(defmethod melew3_msgs::AddMd80sResponse
  (:init
   (&key
    ((:drives_success __drives_success) (let (r) (dotimes (i 0) (push nil r)) r))
    ((:total_number_of_drives __total_number_of_drives) 0)
    )
   (send-super :init)
   (setq _drives_success __drives_success)
   (setq _total_number_of_drives (round __total_number_of_drives))
   self)
  (:drives_success
   (&optional __drives_success)
   (if __drives_success (setq _drives_success __drives_success)) _drives_success)
  (:total_number_of_drives
   (&optional __total_number_of_drives)
   (if __total_number_of_drives (setq _total_number_of_drives __total_number_of_drives)) _total_number_of_drives)
  (:serialization-length
   ()
   (+
    ;; bool[] _drives_success
    (* 1    (length _drives_success)) 4
    ;; uint16 _total_number_of_drives
    2
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
     ;; uint16 _total_number_of_drives
       (write-word _total_number_of_drives s)
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
   ;; uint16 _total_number_of_drives
     (setq _total_number_of_drives (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(defclass melew3_msgs::AddMd80s
  :super ros::object
  :slots ())

(setf (get melew3_msgs::AddMd80s :md5sum-) "4d3ef511c44dd08dd3627532b66a574c")
(setf (get melew3_msgs::AddMd80s :datatype-) "melew3_msgs/AddMd80s")
(setf (get melew3_msgs::AddMd80s :request) melew3_msgs::AddMd80sRequest)
(setf (get melew3_msgs::AddMd80s :response) melew3_msgs::AddMd80sResponse)

(defmethod melew3_msgs::AddMd80sRequest
  (:response () (instance melew3_msgs::AddMd80sResponse :init)))

(setf (get melew3_msgs::AddMd80sRequest :md5sum-) "4d3ef511c44dd08dd3627532b66a574c")
(setf (get melew3_msgs::AddMd80sRequest :datatype-) "melew3_msgs/AddMd80sRequest")
(setf (get melew3_msgs::AddMd80sRequest :definition-)
      "uint16[] drive_ids
---
bool[] drives_success
uint16 total_number_of_drives
")

(setf (get melew3_msgs::AddMd80sResponse :md5sum-) "4d3ef511c44dd08dd3627532b66a574c")
(setf (get melew3_msgs::AddMd80sResponse :datatype-) "melew3_msgs/AddMd80sResponse")
(setf (get melew3_msgs::AddMd80sResponse :definition-)
      "uint16[] drive_ids
---
bool[] drives_success
uint16 total_number_of_drives
")



(provide :melew3_msgs/AddMd80s "4d3ef511c44dd08dd3627532b66a574c")


