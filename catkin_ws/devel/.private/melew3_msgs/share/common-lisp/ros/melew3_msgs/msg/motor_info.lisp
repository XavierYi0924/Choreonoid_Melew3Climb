; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-msg)


;//! \htmlinclude motor_info.msg.html

(cl:defclass <motor_info> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (can_id
    :reader can_id
    :initarg :can_id
    :type cl:fixnum
    :initform 0))
)

(cl:defclass motor_info (<motor_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <motor_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'motor_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-msg:<motor_info> is deprecated: use melew3_msgs-msg:motor_info instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <motor_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:name-val is deprecated.  Use melew3_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'can_id-val :lambda-list '(m))
(cl:defmethod can_id-val ((m <motor_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-msg:can_id-val is deprecated.  Use melew3_msgs-msg:can_id instead.")
  (can_id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <motor_info>) ostream)
  "Serializes a message object of type '<motor_info>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'can_id)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <motor_info>) istream)
  "Deserializes a message object of type '<motor_info>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'can_id)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<motor_info>)))
  "Returns string type for a message object of type '<motor_info>"
  "melew3_msgs/motor_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'motor_info)))
  "Returns string type for a message object of type 'motor_info"
  "melew3_msgs/motor_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<motor_info>)))
  "Returns md5sum for a message object of type '<motor_info>"
  "210d22ee910a155365074b193e163d8b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'motor_info)))
  "Returns md5sum for a message object of type 'motor_info"
  "210d22ee910a155365074b193e163d8b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<motor_info>)))
  "Returns full string definition for message of type '<motor_info>"
  (cl:format cl:nil "# Information for the motor to use~%string name~%uint8 can_id~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'motor_info)))
  "Returns full string definition for message of type 'motor_info"
  (cl:format cl:nil "# Information for the motor to use~%string name~%uint8 can_id~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <motor_info>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <motor_info>))
  "Converts a ROS message object to a list"
  (cl:list 'motor_info
    (cl:cons ':name (name msg))
    (cl:cons ':can_id (can_id msg))
))
