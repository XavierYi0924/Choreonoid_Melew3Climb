; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-msg)


;//! \htmlinclude leg_info_set.msg.html

(cl:defclass <leg_info_set> (roslisp-msg-protocol:ros-message)
  ((leg
    :reader leg
    :initarg :leg
    :type (cl:vector melew3_msgs-msg:leg_info)
   :initform (cl:make-array 0 :element-type 'melew3_msgs-msg:leg_info :initial-element (cl:make-instance 'melew3_msgs-msg:leg_info))))
)

(cl:defclass leg_info_set (<leg_info_set>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <leg_info_set>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'leg_info_set)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-msg:<leg_info_set> is deprecated: use melew3_msgs-msg:leg_info_set instead.")))

(cl:ensure-generic-function 'leg-val :lambda-list '(m))
(cl:defmethod leg-val ((m <leg_info_set>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:leg-val is deprecated.  Use melew3_msgs-msg:leg instead.")
  (leg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <leg_info_set>) ostream)
  "Serializes a message object of type '<leg_info_set>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'leg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'leg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <leg_info_set>) istream)
  "Deserializes a message object of type '<leg_info_set>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'leg) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'leg)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'melew3_msgs-msg:leg_info))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<leg_info_set>)))
  "Returns string type for a message object of type '<leg_info_set>"
  "melew3_msgs/leg_info_set")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'leg_info_set)))
  "Returns string type for a message object of type 'leg_info_set"
  "melew3_msgs/leg_info_set")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<leg_info_set>)))
  "Returns md5sum for a message object of type '<leg_info_set>"
  "60a0c1f02ecf6d55f23aa1de78f2fe2b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'leg_info_set)))
  "Returns md5sum for a message object of type 'leg_info_set"
  "60a0c1f02ecf6d55f23aa1de78f2fe2b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<leg_info_set>)))
  "Returns full string definition for message of type '<leg_info_set>"
  (cl:format cl:nil "# 脚先位置のpub用~%melew3_msgs/leg_info[] leg~%================================================================================~%MSG: melew3_msgs/leg_info~%geometry_msgs/Point32 position~%std_msgs/Float64 yaw~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'leg_info_set)))
  "Returns full string definition for message of type 'leg_info_set"
  (cl:format cl:nil "# 脚先位置のpub用~%melew3_msgs/leg_info[] leg~%================================================================================~%MSG: melew3_msgs/leg_info~%geometry_msgs/Point32 position~%std_msgs/Float64 yaw~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <leg_info_set>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'leg) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <leg_info_set>))
  "Converts a ROS message object to a list"
  (cl:list 'leg_info_set
    (cl:cons ':leg (leg msg))
))
