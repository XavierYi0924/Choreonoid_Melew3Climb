; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-msg)


;//! \htmlinclude waypoint.msg.html

(cl:defclass <waypoint> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (time
    :reader time
    :initarg :time
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64))
   (position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (velocity
    :reader velocity
    :initarg :velocity
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (acceleration
    :reader acceleration
    :initarg :acceleration
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (yaw_position
    :reader yaw_position
    :initarg :yaw_position
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64))
   (yaw_velocity
    :reader yaw_velocity
    :initarg :yaw_velocity
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64))
   (yaw_acceleration
    :reader yaw_acceleration
    :initarg :yaw_acceleration
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64)))
)

(cl:defclass waypoint (<waypoint>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <waypoint>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'waypoint)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-msg:<waypoint> is deprecated: use melew3_msgs-msg:waypoint instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:header-val is deprecated.  Use melew3_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:time-val is deprecated.  Use melew3_msgs-msg:time instead.")
  (time m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:position-val is deprecated.  Use melew3_msgs-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:velocity-val is deprecated.  Use melew3_msgs-msg:velocity instead.")
  (velocity m))

(cl:ensure-generic-function 'acceleration-val :lambda-list '(m))
(cl:defmethod acceleration-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:acceleration-val is deprecated.  Use melew3_msgs-msg:acceleration instead.")
  (acceleration m))

(cl:ensure-generic-function 'yaw_position-val :lambda-list '(m))
(cl:defmethod yaw_position-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:yaw_position-val is deprecated.  Use melew3_msgs-msg:yaw_position instead.")
  (yaw_position m))

(cl:ensure-generic-function 'yaw_velocity-val :lambda-list '(m))
(cl:defmethod yaw_velocity-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:yaw_velocity-val is deprecated.  Use melew3_msgs-msg:yaw_velocity instead.")
  (yaw_velocity m))

(cl:ensure-generic-function 'yaw_acceleration-val :lambda-list '(m))
(cl:defmethod yaw_acceleration-val ((m <waypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:yaw_acceleration-val is deprecated.  Use melew3_msgs-msg:yaw_acceleration instead.")
  (yaw_acceleration m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <waypoint>) ostream)
  "Serializes a message object of type '<waypoint>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'time) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'velocity) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'acceleration) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'yaw_position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'yaw_velocity) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'yaw_acceleration) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <waypoint>) istream)
  "Deserializes a message object of type '<waypoint>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'time) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'velocity) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'acceleration) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'yaw_position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'yaw_velocity) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'yaw_acceleration) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<waypoint>)))
  "Returns string type for a message object of type '<waypoint>"
  "melew3_msgs/waypoint")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'waypoint)))
  "Returns string type for a message object of type 'waypoint"
  "melew3_msgs/waypoint")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<waypoint>)))
  "Returns md5sum for a message object of type '<waypoint>"
  "c206810b38430fa29a10e74179d3b4cd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'waypoint)))
  "Returns md5sum for a message object of type 'waypoint"
  "c206810b38430fa29a10e74179d3b4cd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<waypoint>)))
  "Returns full string definition for message of type '<waypoint>"
  (cl:format cl:nil "std_msgs/Header header~%std_msgs/Float64 time # 時刻~%geometry_msgs/Point position # 位置~%geometry_msgs/Point velocity # 速度~%geometry_msgs/Point acceleration # 加速度~%std_msgs/Float64 yaw_position # 操舵角~%std_msgs/Float64 yaw_velocity # 操舵角速度~%std_msgs/Float64 yaw_acceleration # 操舵角加速度~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'waypoint)))
  "Returns full string definition for message of type 'waypoint"
  (cl:format cl:nil "std_msgs/Header header~%std_msgs/Float64 time # 時刻~%geometry_msgs/Point position # 位置~%geometry_msgs/Point velocity # 速度~%geometry_msgs/Point acceleration # 加速度~%std_msgs/Float64 yaw_position # 操舵角~%std_msgs/Float64 yaw_velocity # 操舵角速度~%std_msgs/Float64 yaw_acceleration # 操舵角加速度~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <waypoint>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'time))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'velocity))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'acceleration))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'yaw_position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'yaw_velocity))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'yaw_acceleration))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <waypoint>))
  "Converts a ROS message object to a list"
  (cl:list 'waypoint
    (cl:cons ':header (header msg))
    (cl:cons ':time (time msg))
    (cl:cons ':position (position msg))
    (cl:cons ':velocity (velocity msg))
    (cl:cons ':acceleration (acceleration msg))
    (cl:cons ':yaw_position (yaw_position msg))
    (cl:cons ':yaw_velocity (yaw_velocity msg))
    (cl:cons ':yaw_acceleration (yaw_acceleration msg))
))
