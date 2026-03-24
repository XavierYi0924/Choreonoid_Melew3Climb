; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude robot_config-request.msg.html

(cl:defclass <robot_config-request> (roslisp-msg-protocol:ros-message)
  ((motor
    :reader motor
    :initarg :motor
    :type (cl:vector melew3_msgs-msg:motor_info)
   :initform (cl:make-array 0 :element-type 'melew3_msgs-msg:motor_info :initial-element (cl:make-instance 'melew3_msgs-msg:motor_info))))
)

(cl:defclass robot_config-request (<robot_config-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_config-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_config-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<robot_config-request> is deprecated: use melew3_msgs-srv:robot_config-request instead.")))

(cl:ensure-generic-function 'motor-val :lambda-list '(m))
(cl:defmethod motor-val ((m <robot_config-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:motor-val is deprecated.  Use melew3_msgs-srv:motor instead.")
  (motor m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_config-request>) ostream)
  "Serializes a message object of type '<robot_config-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'motor))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'motor))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_config-request>) istream)
  "Deserializes a message object of type '<robot_config-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'motor) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'motor)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'melew3_msgs-msg:motor_info))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_config-request>)))
  "Returns string type for a service object of type '<robot_config-request>"
  "melew3_msgs/robot_configRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_config-request)))
  "Returns string type for a service object of type 'robot_config-request"
  "melew3_msgs/robot_configRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_config-request>)))
  "Returns md5sum for a message object of type '<robot_config-request>"
  "d0ea6905ae3e9bf592297d448a99911d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_config-request)))
  "Returns md5sum for a message object of type 'robot_config-request"
  "d0ea6905ae3e9bf592297d448a99911d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_config-request>)))
  "Returns full string definition for message of type '<robot_config-request>"
  (cl:format cl:nil "# Information for robot to be passed to the microcontroller~%melew3_msgs/motor_info[] motor~%~%================================================================================~%MSG: melew3_msgs/motor_info~%# Information for the motor to use~%string name~%uint8 can_id~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_config-request)))
  "Returns full string definition for message of type 'robot_config-request"
  (cl:format cl:nil "# Information for robot to be passed to the microcontroller~%melew3_msgs/motor_info[] motor~%~%================================================================================~%MSG: melew3_msgs/motor_info~%# Information for the motor to use~%string name~%uint8 can_id~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_config-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'motor) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_config-request>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_config-request
    (cl:cons ':motor (motor msg))
))
;//! \htmlinclude robot_config-response.msg.html

(cl:defclass <robot_config-response> (roslisp-msg-protocol:ros-message)
  ((motor_quantity
    :reader motor_quantity
    :initarg :motor_quantity
    :type cl:fixnum
    :initform 0)
   (checksum
    :reader checksum
    :initarg :checksum
    :type cl:fixnum
    :initform 0))
)

(cl:defclass robot_config-response (<robot_config-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_config-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_config-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<robot_config-response> is deprecated: use melew3_msgs-srv:robot_config-response instead.")))

(cl:ensure-generic-function 'motor_quantity-val :lambda-list '(m))
(cl:defmethod motor_quantity-val ((m <robot_config-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:motor_quantity-val is deprecated.  Use melew3_msgs-srv:motor_quantity instead.")
  (motor_quantity m))

(cl:ensure-generic-function 'checksum-val :lambda-list '(m))
(cl:defmethod checksum-val ((m <robot_config-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:checksum-val is deprecated.  Use melew3_msgs-srv:checksum instead.")
  (checksum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_config-response>) ostream)
  "Serializes a message object of type '<robot_config-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_quantity)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'checksum)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_config-response>) istream)
  "Deserializes a message object of type '<robot_config-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_quantity)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_config-response>)))
  "Returns string type for a service object of type '<robot_config-response>"
  "melew3_msgs/robot_configResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_config-response)))
  "Returns string type for a service object of type 'robot_config-response"
  "melew3_msgs/robot_configResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_config-response>)))
  "Returns md5sum for a message object of type '<robot_config-response>"
  "d0ea6905ae3e9bf592297d448a99911d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_config-response)))
  "Returns md5sum for a message object of type 'robot_config-response"
  "d0ea6905ae3e9bf592297d448a99911d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_config-response>)))
  "Returns full string definition for message of type '<robot_config-response>"
  (cl:format cl:nil "uint8 motor_quantity~%uint8 checksum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_config-response)))
  "Returns full string definition for message of type 'robot_config-response"
  (cl:format cl:nil "uint8 motor_quantity~%uint8 checksum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_config-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_config-response>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_config-response
    (cl:cons ':motor_quantity (motor_quantity msg))
    (cl:cons ':checksum (checksum msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'robot_config)))
  'robot_config-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'robot_config)))
  'robot_config-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_config)))
  "Returns string type for a service object of type '<robot_config>"
  "melew3_msgs/robot_config")