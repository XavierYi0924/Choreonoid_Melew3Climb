; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude enter_control_mode-request.msg.html

(cl:defclass <enter_control_mode-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (CAN_ID
    :reader CAN_ID
    :initarg :CAN_ID
    :type cl:fixnum
    :initform 0)
   (model
    :reader model
    :initarg :model
    :type cl:string
    :initform ""))
)

(cl:defclass enter_control_mode-request (<enter_control_mode-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <enter_control_mode-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'enter_control_mode-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<enter_control_mode-request> is deprecated: use melew3_msgs-srv:enter_control_mode-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <enter_control_mode-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:name-val is deprecated.  Use melew3_msgs-srv:name instead.")
  (name m))

(cl:ensure-generic-function 'CAN_ID-val :lambda-list '(m))
(cl:defmethod CAN_ID-val ((m <enter_control_mode-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:CAN_ID-val is deprecated.  Use melew3_msgs-srv:CAN_ID instead.")
  (CAN_ID m))

(cl:ensure-generic-function 'model-val :lambda-list '(m))
(cl:defmethod model-val ((m <enter_control_mode-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:model-val is deprecated.  Use melew3_msgs-srv:model instead.")
  (model m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <enter_control_mode-request>) ostream)
  "Serializes a message object of type '<enter_control_mode-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CAN_ID)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'model))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'model))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <enter_control_mode-request>) istream)
  "Deserializes a message object of type '<enter_control_mode-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CAN_ID)) (cl:read-byte istream))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'model) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'model) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<enter_control_mode-request>)))
  "Returns string type for a service object of type '<enter_control_mode-request>"
  "melew3_msgs/enter_control_modeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'enter_control_mode-request)))
  "Returns string type for a service object of type 'enter_control_mode-request"
  "melew3_msgs/enter_control_modeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<enter_control_mode-request>)))
  "Returns md5sum for a message object of type '<enter_control_mode-request>"
  "d1a68f1452832714a857b39d4b4ecf8d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'enter_control_mode-request)))
  "Returns md5sum for a message object of type 'enter_control_mode-request"
  "d1a68f1452832714a857b39d4b4ecf8d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<enter_control_mode-request>)))
  "Returns full string definition for message of type '<enter_control_mode-request>"
  (cl:format cl:nil "# CAN_ID of the motor~%string name~%uint8 CAN_ID~%string model~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'enter_control_mode-request)))
  "Returns full string definition for message of type 'enter_control_mode-request"
  (cl:format cl:nil "# CAN_ID of the motor~%string name~%uint8 CAN_ID~%string model~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <enter_control_mode-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     1
     4 (cl:length (cl:slot-value msg 'model))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <enter_control_mode-request>))
  "Converts a ROS message object to a list"
  (cl:list 'enter_control_mode-request
    (cl:cons ':name (name msg))
    (cl:cons ':CAN_ID (CAN_ID msg))
    (cl:cons ':model (model msg))
))
;//! \htmlinclude enter_control_mode-response.msg.html

(cl:defclass <enter_control_mode-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass enter_control_mode-response (<enter_control_mode-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <enter_control_mode-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'enter_control_mode-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<enter_control_mode-response> is deprecated: use melew3_msgs-srv:enter_control_mode-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <enter_control_mode-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:success-val is deprecated.  Use melew3_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <enter_control_mode-response>) ostream)
  "Serializes a message object of type '<enter_control_mode-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <enter_control_mode-response>) istream)
  "Deserializes a message object of type '<enter_control_mode-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<enter_control_mode-response>)))
  "Returns string type for a service object of type '<enter_control_mode-response>"
  "melew3_msgs/enter_control_modeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'enter_control_mode-response)))
  "Returns string type for a service object of type 'enter_control_mode-response"
  "melew3_msgs/enter_control_modeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<enter_control_mode-response>)))
  "Returns md5sum for a message object of type '<enter_control_mode-response>"
  "d1a68f1452832714a857b39d4b4ecf8d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'enter_control_mode-response)))
  "Returns md5sum for a message object of type 'enter_control_mode-response"
  "d1a68f1452832714a857b39d4b4ecf8d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<enter_control_mode-response>)))
  "Returns full string definition for message of type '<enter_control_mode-response>"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'enter_control_mode-response)))
  "Returns full string definition for message of type 'enter_control_mode-response"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <enter_control_mode-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <enter_control_mode-response>))
  "Converts a ROS message object to a list"
  (cl:list 'enter_control_mode-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'enter_control_mode)))
  'enter_control_mode-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'enter_control_mode)))
  'enter_control_mode-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'enter_control_mode)))
  "Returns string type for a service object of type '<enter_control_mode>"
  "melew3_msgs/enter_control_mode")