; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude exit_control_mode-request.msg.html

(cl:defclass <exit_control_mode-request> (roslisp-msg-protocol:ros-message)
  ((CAN_ID
    :reader CAN_ID
    :initarg :CAN_ID
    :type cl:fixnum
    :initform 0))
)

(cl:defclass exit_control_mode-request (<exit_control_mode-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <exit_control_mode-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'exit_control_mode-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<exit_control_mode-request> is deprecated: use melew3_msgs-srv:exit_control_mode-request instead.")))

(cl:ensure-generic-function 'CAN_ID-val :lambda-list '(m))
(cl:defmethod CAN_ID-val ((m <exit_control_mode-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:CAN_ID-val is deprecated.  Use melew3_msgs-srv:CAN_ID instead.")
  (CAN_ID m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <exit_control_mode-request>) ostream)
  "Serializes a message object of type '<exit_control_mode-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CAN_ID)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <exit_control_mode-request>) istream)
  "Deserializes a message object of type '<exit_control_mode-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CAN_ID)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<exit_control_mode-request>)))
  "Returns string type for a service object of type '<exit_control_mode-request>"
  "melew3_msgs/exit_control_modeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'exit_control_mode-request)))
  "Returns string type for a service object of type 'exit_control_mode-request"
  "melew3_msgs/exit_control_modeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<exit_control_mode-request>)))
  "Returns md5sum for a message object of type '<exit_control_mode-request>"
  "d34ae0ac05d13cf23c6d78c27795e4e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'exit_control_mode-request)))
  "Returns md5sum for a message object of type 'exit_control_mode-request"
  "d34ae0ac05d13cf23c6d78c27795e4e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<exit_control_mode-request>)))
  "Returns full string definition for message of type '<exit_control_mode-request>"
  (cl:format cl:nil "# CAN_ID of the motor~%uint8 CAN_ID~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'exit_control_mode-request)))
  "Returns full string definition for message of type 'exit_control_mode-request"
  (cl:format cl:nil "# CAN_ID of the motor~%uint8 CAN_ID~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <exit_control_mode-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <exit_control_mode-request>))
  "Converts a ROS message object to a list"
  (cl:list 'exit_control_mode-request
    (cl:cons ':CAN_ID (CAN_ID msg))
))
;//! \htmlinclude exit_control_mode-response.msg.html

(cl:defclass <exit_control_mode-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass exit_control_mode-response (<exit_control_mode-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <exit_control_mode-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'exit_control_mode-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<exit_control_mode-response> is deprecated: use melew3_msgs-srv:exit_control_mode-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <exit_control_mode-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:success-val is deprecated.  Use melew3_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <exit_control_mode-response>) ostream)
  "Serializes a message object of type '<exit_control_mode-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <exit_control_mode-response>) istream)
  "Deserializes a message object of type '<exit_control_mode-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<exit_control_mode-response>)))
  "Returns string type for a service object of type '<exit_control_mode-response>"
  "melew3_msgs/exit_control_modeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'exit_control_mode-response)))
  "Returns string type for a service object of type 'exit_control_mode-response"
  "melew3_msgs/exit_control_modeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<exit_control_mode-response>)))
  "Returns md5sum for a message object of type '<exit_control_mode-response>"
  "d34ae0ac05d13cf23c6d78c27795e4e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'exit_control_mode-response)))
  "Returns md5sum for a message object of type 'exit_control_mode-response"
  "d34ae0ac05d13cf23c6d78c27795e4e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<exit_control_mode-response>)))
  "Returns full string definition for message of type '<exit_control_mode-response>"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'exit_control_mode-response)))
  "Returns full string definition for message of type 'exit_control_mode-response"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <exit_control_mode-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <exit_control_mode-response>))
  "Converts a ROS message object to a list"
  (cl:list 'exit_control_mode-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'exit_control_mode)))
  'exit_control_mode-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'exit_control_mode)))
  'exit_control_mode-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'exit_control_mode)))
  "Returns string type for a service object of type '<exit_control_mode>"
  "melew3_msgs/exit_control_mode")