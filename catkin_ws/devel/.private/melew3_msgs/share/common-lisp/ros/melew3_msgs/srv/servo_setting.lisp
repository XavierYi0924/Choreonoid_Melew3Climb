; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude servo_setting-request.msg.html

(cl:defclass <servo_setting-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (servo
    :reader servo
    :initarg :servo
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass servo_setting-request (<servo_setting-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <servo_setting-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'servo_setting-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<servo_setting-request> is deprecated: use melew3_msgs-srv:servo_setting-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <servo_setting-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:name-val is deprecated.  Use melew3_msgs-srv:name instead.")
  (name m))

(cl:ensure-generic-function 'servo-val :lambda-list '(m))
(cl:defmethod servo-val ((m <servo_setting-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:servo-val is deprecated.  Use melew3_msgs-srv:servo instead.")
  (servo m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <servo_setting-request>) ostream)
  "Serializes a message object of type '<servo_setting-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'servo) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <servo_setting-request>) istream)
  "Deserializes a message object of type '<servo_setting-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'servo) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<servo_setting-request>)))
  "Returns string type for a service object of type '<servo_setting-request>"
  "melew3_msgs/servo_settingRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'servo_setting-request)))
  "Returns string type for a service object of type 'servo_setting-request"
  "melew3_msgs/servo_settingRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<servo_setting-request>)))
  "Returns md5sum for a message object of type '<servo_setting-request>"
  "40ae7cc676163ebf2724cc24e1fb1718")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'servo_setting-request)))
  "Returns md5sum for a message object of type 'servo_setting-request"
  "40ae7cc676163ebf2724cc24e1fb1718")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<servo_setting-request>)))
  "Returns full string definition for message of type '<servo_setting-request>"
  (cl:format cl:nil "# CAN_ID of the motor~%string name~%bool servo~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'servo_setting-request)))
  "Returns full string definition for message of type 'servo_setting-request"
  (cl:format cl:nil "# CAN_ID of the motor~%string name~%bool servo~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <servo_setting-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <servo_setting-request>))
  "Converts a ROS message object to a list"
  (cl:list 'servo_setting-request
    (cl:cons ':name (name msg))
    (cl:cons ':servo (servo msg))
))
;//! \htmlinclude servo_setting-response.msg.html

(cl:defclass <servo_setting-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass servo_setting-response (<servo_setting-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <servo_setting-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'servo_setting-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<servo_setting-response> is deprecated: use melew3_msgs-srv:servo_setting-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <servo_setting-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:success-val is deprecated.  Use melew3_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <servo_setting-response>) ostream)
  "Serializes a message object of type '<servo_setting-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <servo_setting-response>) istream)
  "Deserializes a message object of type '<servo_setting-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<servo_setting-response>)))
  "Returns string type for a service object of type '<servo_setting-response>"
  "melew3_msgs/servo_settingResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'servo_setting-response)))
  "Returns string type for a service object of type 'servo_setting-response"
  "melew3_msgs/servo_settingResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<servo_setting-response>)))
  "Returns md5sum for a message object of type '<servo_setting-response>"
  "40ae7cc676163ebf2724cc24e1fb1718")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'servo_setting-response)))
  "Returns md5sum for a message object of type 'servo_setting-response"
  "40ae7cc676163ebf2724cc24e1fb1718")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<servo_setting-response>)))
  "Returns full string definition for message of type '<servo_setting-response>"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'servo_setting-response)))
  "Returns full string definition for message of type 'servo_setting-response"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <servo_setting-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <servo_setting-response>))
  "Converts a ROS message object to a list"
  (cl:list 'servo_setting-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'servo_setting)))
  'servo_setting-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'servo_setting)))
  'servo_setting-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'servo_setting)))
  "Returns string type for a service object of type '<servo_setting>"
  "melew3_msgs/servo_setting")