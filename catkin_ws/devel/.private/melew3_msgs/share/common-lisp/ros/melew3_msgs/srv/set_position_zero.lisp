; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude set_position_zero-request.msg.html

(cl:defclass <set_position_zero-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform ""))
)

(cl:defclass set_position_zero-request (<set_position_zero-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_position_zero-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_position_zero-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<set_position_zero-request> is deprecated: use melew3_msgs-srv:set_position_zero-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <set_position_zero-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:name-val is deprecated.  Use melew3_msgs-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_position_zero-request>) ostream)
  "Serializes a message object of type '<set_position_zero-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_position_zero-request>) istream)
  "Deserializes a message object of type '<set_position_zero-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_position_zero-request>)))
  "Returns string type for a service object of type '<set_position_zero-request>"
  "melew3_msgs/set_position_zeroRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_position_zero-request)))
  "Returns string type for a service object of type 'set_position_zero-request"
  "melew3_msgs/set_position_zeroRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_position_zero-request>)))
  "Returns md5sum for a message object of type '<set_position_zero-request>"
  "d08a3b641c2f8680fbdfb1ea2e17a3e1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_position_zero-request)))
  "Returns md5sum for a message object of type 'set_position_zero-request"
  "d08a3b641c2f8680fbdfb1ea2e17a3e1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_position_zero-request>)))
  "Returns full string definition for message of type '<set_position_zero-request>"
  (cl:format cl:nil "# CAN_ID of the motor~%string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_position_zero-request)))
  "Returns full string definition for message of type 'set_position_zero-request"
  (cl:format cl:nil "# CAN_ID of the motor~%string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_position_zero-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_position_zero-request>))
  "Converts a ROS message object to a list"
  (cl:list 'set_position_zero-request
    (cl:cons ':name (name msg))
))
;//! \htmlinclude set_position_zero-response.msg.html

(cl:defclass <set_position_zero-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass set_position_zero-response (<set_position_zero-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_position_zero-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_position_zero-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<set_position_zero-response> is deprecated: use melew3_msgs-srv:set_position_zero-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <set_position_zero-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:success-val is deprecated.  Use melew3_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_position_zero-response>) ostream)
  "Serializes a message object of type '<set_position_zero-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_position_zero-response>) istream)
  "Deserializes a message object of type '<set_position_zero-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_position_zero-response>)))
  "Returns string type for a service object of type '<set_position_zero-response>"
  "melew3_msgs/set_position_zeroResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_position_zero-response)))
  "Returns string type for a service object of type 'set_position_zero-response"
  "melew3_msgs/set_position_zeroResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_position_zero-response>)))
  "Returns md5sum for a message object of type '<set_position_zero-response>"
  "d08a3b641c2f8680fbdfb1ea2e17a3e1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_position_zero-response)))
  "Returns md5sum for a message object of type 'set_position_zero-response"
  "d08a3b641c2f8680fbdfb1ea2e17a3e1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_position_zero-response>)))
  "Returns full string definition for message of type '<set_position_zero-response>"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_position_zero-response)))
  "Returns full string definition for message of type 'set_position_zero-response"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_position_zero-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_position_zero-response>))
  "Converts a ROS message object to a list"
  (cl:list 'set_position_zero-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'set_position_zero)))
  'set_position_zero-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'set_position_zero)))
  'set_position_zero-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_position_zero)))
  "Returns string type for a service object of type '<set_position_zero>"
  "melew3_msgs/set_position_zero")