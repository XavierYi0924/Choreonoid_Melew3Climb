;; Auto-generated. Do not edit!


(when (boundp 'melew3_msgs::FallAvoidanceMotion)
  (if (not (find-package "MELEW3_MSGS"))
    (make-package "MELEW3_MSGS"))
  (shadow 'FallAvoidanceMotion (find-package "MELEW3_MSGS")))
(unless (find-package "MELEW3_MSGS::FALLAVOIDANCEMOTION")
  (make-package "MELEW3_MSGS::FALLAVOIDANCEMOTION"))
(unless (find-package "MELEW3_MSGS::FALLAVOIDANCEMOTIONREQUEST")
  (make-package "MELEW3_MSGS::FALLAVOIDANCEMOTIONREQUEST"))
(unless (find-package "MELEW3_MSGS::FALLAVOIDANCEMOTIONRESPONSE")
  (make-package "MELEW3_MSGS::FALLAVOIDANCEMOTIONRESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))




(defclass melew3_msgs::FallAvoidanceMotionRequest
  :super ros::object
  :slots (_desired_angles _support_foot ))

(defmethod melew3_msgs::FallAvoidanceMotionRequest
  (:init
   (&key
    ((:desired_angles __desired_angles) (instance std_msgs::Float64MultiArray :init))
    ((:support_foot __support_foot) nil)
    )
   (send-super :init)
   (setq _desired_angles __desired_angles)
   (setq _support_foot __support_foot)
   self)
  (:desired_angles
   (&rest __desired_angles)
   (if (keywordp (car __desired_angles))
       (send* _desired_angles __desired_angles)
     (progn
       (if __desired_angles (setq _desired_angles (car __desired_angles)))
       _desired_angles)))
  (:support_foot
   (&optional (__support_foot :null))
   (if (not (eq __support_foot :null)) (setq _support_foot __support_foot)) _support_foot)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float64MultiArray _desired_angles
    (send _desired_angles :serialization-length)
    ;; bool _support_foot
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float64MultiArray _desired_angles
       (send _desired_angles :serialize s)
     ;; bool _support_foot
       (if _support_foot (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float64MultiArray _desired_angles
     (send _desired_angles :deserialize buf ptr-) (incf ptr- (send _desired_angles :serialization-length))
   ;; bool _support_foot
     (setq _support_foot (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass melew3_msgs::FallAvoidanceMotionResponse
  :super ros::object
  :slots (_success _message ))

(defmethod melew3_msgs::FallAvoidanceMotionResponse
  (:init
   (&key
    ((:success __success) nil)
    ((:message __message) "")
    )
   (send-super :init)
   (setq _success __success)
   (setq _message (string __message))
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ;; string _message
    4 (length _message)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass melew3_msgs::FallAvoidanceMotion
  :super ros::object
  :slots ())

(setf (get melew3_msgs::FallAvoidanceMotion :md5sum-) "737f56379c2098cadb78a35625cbbf12")
(setf (get melew3_msgs::FallAvoidanceMotion :datatype-) "melew3_msgs/FallAvoidanceMotion")
(setf (get melew3_msgs::FallAvoidanceMotion :request) melew3_msgs::FallAvoidanceMotionRequest)
(setf (get melew3_msgs::FallAvoidanceMotion :response) melew3_msgs::FallAvoidanceMotionResponse)

(defmethod melew3_msgs::FallAvoidanceMotionRequest
  (:response () (instance melew3_msgs::FallAvoidanceMotionResponse :init)))

(setf (get melew3_msgs::FallAvoidanceMotionRequest :md5sum-) "737f56379c2098cadb78a35625cbbf12")
(setf (get melew3_msgs::FallAvoidanceMotionRequest :datatype-) "melew3_msgs/FallAvoidanceMotionRequest")
(setf (get melew3_msgs::FallAvoidanceMotionRequest :definition-)
      "std_msgs/Float64MultiArray desired_angles  # 目標姿勢を満たす関節角度
bool support_foot # 支持脚（false：左脚，true：右脚）

================================================================================
MSG: std_msgs/Float64MultiArray
# Please look at the MultiArrayLayout message definition for
# documentation on all multiarrays.

MultiArrayLayout  layout        # specification of data layout
float64[]         data          # array of data


================================================================================
MSG: std_msgs/MultiArrayLayout
# The multiarray declares a generic multi-dimensional array of a
# particular data type.  Dimensions are ordered from outer most
# to inner most.

MultiArrayDimension[] dim # Array of dimension properties
uint32 data_offset        # padding elements at front of data

# Accessors should ALWAYS be written in terms of dimension stride
# and specified outer-most dimension first.
# 
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
#
# A standard, 3-channel 640x480 image with interleaved color channels
# would be specified as:
#
# dim[0].label  = \"height\"
# dim[0].size   = 480
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
# dim[1].label  = \"width\"
# dim[1].size   = 640
# dim[1].stride = 3*640 = 1920
# dim[2].label  = \"channel\"
# dim[2].size   = 3
# dim[2].stride = 3
#
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.

================================================================================
MSG: std_msgs/MultiArrayDimension
string label   # label of given dimension
uint32 size    # size of given dimension (in type units)
---
bool success
string message
")

(setf (get melew3_msgs::FallAvoidanceMotionResponse :md5sum-) "737f56379c2098cadb78a35625cbbf12")
(setf (get melew3_msgs::FallAvoidanceMotionResponse :datatype-) "melew3_msgs/FallAvoidanceMotionResponse")
(setf (get melew3_msgs::FallAvoidanceMotionResponse :definition-)
      "std_msgs/Float64MultiArray desired_angles  # 目標姿勢を満たす関節角度
bool support_foot # 支持脚（false：左脚，true：右脚）

================================================================================
MSG: std_msgs/Float64MultiArray
# Please look at the MultiArrayLayout message definition for
# documentation on all multiarrays.

MultiArrayLayout  layout        # specification of data layout
float64[]         data          # array of data


================================================================================
MSG: std_msgs/MultiArrayLayout
# The multiarray declares a generic multi-dimensional array of a
# particular data type.  Dimensions are ordered from outer most
# to inner most.

MultiArrayDimension[] dim # Array of dimension properties
uint32 data_offset        # padding elements at front of data

# Accessors should ALWAYS be written in terms of dimension stride
# and specified outer-most dimension first.
# 
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
#
# A standard, 3-channel 640x480 image with interleaved color channels
# would be specified as:
#
# dim[0].label  = \"height\"
# dim[0].size   = 480
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
# dim[1].label  = \"width\"
# dim[1].size   = 640
# dim[1].stride = 3*640 = 1920
# dim[2].label  = \"channel\"
# dim[2].size   = 3
# dim[2].stride = 3
#
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.

================================================================================
MSG: std_msgs/MultiArrayDimension
string label   # label of given dimension
uint32 size    # size of given dimension (in type units)
---
bool success
string message
")



(provide :melew3_msgs/FallAvoidanceMotion "737f56379c2098cadb78a35625cbbf12")


