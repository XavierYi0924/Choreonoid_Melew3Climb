; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-msg)


;//! \htmlinclude leg_pose.msg.html

(cl:defclass <leg_pose> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (point
    :reader point
    :initarg :point
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (yaw
    :reader yaw
    :initarg :yaw
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64)))
)

(cl:defclass leg_pose (<leg_pose>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <leg_pose>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'leg_pose)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-msg:<leg_pose> is deprecated: use melew3_msgs-msg:leg_pose instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <leg_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:header-val is deprecated.  Use melew3_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'point-val :lambda-list '(m))
(cl:defmethod point-val ((m <leg_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:point-val is deprecated.  Use melew3_msgs-msg:point instead.")
  (point m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <leg_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:yaw-val is deprecated.  Use melew3_msgs-msg:yaw instead.")
  (yaw m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <leg_pose>) ostream)
  "Serializes a message object of type '<leg_pose>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'point) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'yaw) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <leg_pose>) istream)
  "Deserializes a message object of type '<leg_pose>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'point) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'yaw) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<leg_pose>)))
  "Returns string type for a message object of type '<leg_pose>"
  "melew3_msgs/leg_pose")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'leg_pose)))
  "Returns string type for a message object of type 'leg_pose"
  "melew3_msgs/leg_pose")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<leg_pose>)))
  "Returns md5sum for a message object of type '<leg_pose>"
  "76cd62e084d757e7a87b11d4ad219459")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'leg_pose)))
  "Returns md5sum for a message object of type 'leg_pose"
  "76cd62e084d757e7a87b11d4ad219459")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<leg_pose>)))
  "Returns full string definition for message of type '<leg_pose>"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point point~%std_msgs/Float64 yaw~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'leg_pose)))
  "Returns full string definition for message of type 'leg_pose"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point point~%std_msgs/Float64 yaw~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <leg_pose>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'point))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'yaw))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <leg_pose>))
  "Converts a ROS message object to a list"
  (cl:list 'leg_pose
    (cl:cons ':header (header msg))
    (cl:cons ':point (point msg))
    (cl:cons ':yaw (yaw msg))
))
