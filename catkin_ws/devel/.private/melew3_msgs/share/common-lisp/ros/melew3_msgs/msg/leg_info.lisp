; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-msg)


;//! \htmlinclude leg_info.msg.html

(cl:defclass <leg_info> (roslisp-msg-protocol:ros-message)
  ((position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Point32
    :initform (cl:make-instance 'geometry_msgs-msg:Point32))
   (yaw
    :reader yaw
    :initarg :yaw
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64)))
)

(cl:defclass leg_info (<leg_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <leg_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'leg_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-msg:<leg_info> is deprecated: use melew3_msgs-msg:leg_info instead.")))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <leg_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:position-val is deprecated.  Use melew3_msgs-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <leg_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:yaw-val is deprecated.  Use melew3_msgs-msg:yaw instead.")
  (yaw m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <leg_info>) ostream)
  "Serializes a message object of type '<leg_info>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'yaw) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <leg_info>) istream)
  "Deserializes a message object of type '<leg_info>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'yaw) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<leg_info>)))
  "Returns string type for a message object of type '<leg_info>"
  "melew3_msgs/leg_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'leg_info)))
  "Returns string type for a message object of type 'leg_info"
  "melew3_msgs/leg_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<leg_info>)))
  "Returns md5sum for a message object of type '<leg_info>"
  "d4617fc0ec53327f436a5e22e15be77a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'leg_info)))
  "Returns md5sum for a message object of type 'leg_info"
  "d4617fc0ec53327f436a5e22e15be77a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<leg_info>)))
  "Returns full string definition for message of type '<leg_info>"
  (cl:format cl:nil "geometry_msgs/Point32 position~%std_msgs/Float64 yaw~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'leg_info)))
  "Returns full string definition for message of type 'leg_info"
  (cl:format cl:nil "geometry_msgs/Point32 position~%std_msgs/Float64 yaw~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <leg_info>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'yaw))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <leg_info>))
  "Converts a ROS message object to a list"
  (cl:list 'leg_info
    (cl:cons ':position (position msg))
    (cl:cons ':yaw (yaw msg))
))
