; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude FallAvoidanceMotion-request.msg.html

(cl:defclass <FallAvoidanceMotion-request> (roslisp-msg-protocol:ros-message)
  ((desired_angles
    :reader desired_angles
    :initarg :desired_angles
    :type std_msgs-msg:Float64MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float64MultiArray))
   (support_foot
    :reader support_foot
    :initarg :support_foot
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass FallAvoidanceMotion-request (<FallAvoidanceMotion-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FallAvoidanceMotion-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FallAvoidanceMotion-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<FallAvoidanceMotion-request> is deprecated: use melew3_msgs-srv:FallAvoidanceMotion-request instead.")))

(cl:ensure-generic-function 'desired_angles-val :lambda-list '(m))
(cl:defmethod desired_angles-val ((m <FallAvoidanceMotion-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:desired_angles-val is deprecated.  Use melew3_msgs-srv:desired_angles instead.")
  (desired_angles m))

(cl:ensure-generic-function 'support_foot-val :lambda-list '(m))
(cl:defmethod support_foot-val ((m <FallAvoidanceMotion-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:support_foot-val is deprecated.  Use melew3_msgs-srv:support_foot instead.")
  (support_foot m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FallAvoidanceMotion-request>) ostream)
  "Serializes a message object of type '<FallAvoidanceMotion-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'desired_angles) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'support_foot) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FallAvoidanceMotion-request>) istream)
  "Deserializes a message object of type '<FallAvoidanceMotion-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'desired_angles) istream)
    (cl:setf (cl:slot-value msg 'support_foot) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FallAvoidanceMotion-request>)))
  "Returns string type for a service object of type '<FallAvoidanceMotion-request>"
  "melew3_msgs/FallAvoidanceMotionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FallAvoidanceMotion-request)))
  "Returns string type for a service object of type 'FallAvoidanceMotion-request"
  "melew3_msgs/FallAvoidanceMotionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FallAvoidanceMotion-request>)))
  "Returns md5sum for a message object of type '<FallAvoidanceMotion-request>"
  "737f56379c2098cadb78a35625cbbf12")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FallAvoidanceMotion-request)))
  "Returns md5sum for a message object of type 'FallAvoidanceMotion-request"
  "737f56379c2098cadb78a35625cbbf12")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FallAvoidanceMotion-request>)))
  "Returns full string definition for message of type '<FallAvoidanceMotion-request>"
  (cl:format cl:nil "std_msgs/Float64MultiArray desired_angles  # 目標姿勢を満たす関節角度~%bool support_foot # 支持脚（false：左脚，true：右脚）~%~%================================================================================~%MSG: std_msgs/Float64MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float64[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FallAvoidanceMotion-request)))
  "Returns full string definition for message of type 'FallAvoidanceMotion-request"
  (cl:format cl:nil "std_msgs/Float64MultiArray desired_angles  # 目標姿勢を満たす関節角度~%bool support_foot # 支持脚（false：左脚，true：右脚）~%~%================================================================================~%MSG: std_msgs/Float64MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float64[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FallAvoidanceMotion-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'desired_angles))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FallAvoidanceMotion-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FallAvoidanceMotion-request
    (cl:cons ':desired_angles (desired_angles msg))
    (cl:cons ':support_foot (support_foot msg))
))
;//! \htmlinclude FallAvoidanceMotion-response.msg.html

(cl:defclass <FallAvoidanceMotion-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (message
    :reader message
    :initarg :message
    :type cl:string
    :initform ""))
)

(cl:defclass FallAvoidanceMotion-response (<FallAvoidanceMotion-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FallAvoidanceMotion-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FallAvoidanceMotion-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<FallAvoidanceMotion-response> is deprecated: use melew3_msgs-srv:FallAvoidanceMotion-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <FallAvoidanceMotion-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:success-val is deprecated.  Use melew3_msgs-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <FallAvoidanceMotion-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:message-val is deprecated.  Use melew3_msgs-srv:message instead.")
  (message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FallAvoidanceMotion-response>) ostream)
  "Serializes a message object of type '<FallAvoidanceMotion-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FallAvoidanceMotion-response>) istream)
  "Deserializes a message object of type '<FallAvoidanceMotion-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FallAvoidanceMotion-response>)))
  "Returns string type for a service object of type '<FallAvoidanceMotion-response>"
  "melew3_msgs/FallAvoidanceMotionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FallAvoidanceMotion-response)))
  "Returns string type for a service object of type 'FallAvoidanceMotion-response"
  "melew3_msgs/FallAvoidanceMotionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FallAvoidanceMotion-response>)))
  "Returns md5sum for a message object of type '<FallAvoidanceMotion-response>"
  "737f56379c2098cadb78a35625cbbf12")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FallAvoidanceMotion-response)))
  "Returns md5sum for a message object of type 'FallAvoidanceMotion-response"
  "737f56379c2098cadb78a35625cbbf12")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FallAvoidanceMotion-response>)))
  "Returns full string definition for message of type '<FallAvoidanceMotion-response>"
  (cl:format cl:nil "bool success~%string message~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FallAvoidanceMotion-response)))
  "Returns full string definition for message of type 'FallAvoidanceMotion-response"
  (cl:format cl:nil "bool success~%string message~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FallAvoidanceMotion-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'message))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FallAvoidanceMotion-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FallAvoidanceMotion-response
    (cl:cons ':success (success msg))
    (cl:cons ':message (message msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FallAvoidanceMotion)))
  'FallAvoidanceMotion-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FallAvoidanceMotion)))
  'FallAvoidanceMotion-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FallAvoidanceMotion)))
  "Returns string type for a service object of type '<FallAvoidanceMotion>"
  "melew3_msgs/FallAvoidanceMotion")