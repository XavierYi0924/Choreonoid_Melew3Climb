; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude GenericMd80Msg-request.msg.html

(cl:defclass <GenericMd80Msg-request> (roslisp-msg-protocol:ros-message)
  ((drive_ids
    :reader drive_ids
    :initarg :drive_ids
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass GenericMd80Msg-request (<GenericMd80Msg-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GenericMd80Msg-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GenericMd80Msg-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<GenericMd80Msg-request> is deprecated: use melew3_msgs-srv:GenericMd80Msg-request instead.")))

(cl:ensure-generic-function 'drive_ids-val :lambda-list '(m))
(cl:defmethod drive_ids-val ((m <GenericMd80Msg-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drive_ids-val is deprecated.  Use melew3_msgs-srv:drive_ids instead.")
  (drive_ids m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GenericMd80Msg-request>) ostream)
  "Serializes a message object of type '<GenericMd80Msg-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drive_ids))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream))
   (cl:slot-value msg 'drive_ids))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GenericMd80Msg-request>) istream)
  "Deserializes a message object of type '<GenericMd80Msg-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'drive_ids) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'drive_ids)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GenericMd80Msg-request>)))
  "Returns string type for a service object of type '<GenericMd80Msg-request>"
  "melew3_msgs/GenericMd80MsgRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GenericMd80Msg-request)))
  "Returns string type for a service object of type 'GenericMd80Msg-request"
  "melew3_msgs/GenericMd80MsgRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GenericMd80Msg-request>)))
  "Returns md5sum for a message object of type '<GenericMd80Msg-request>"
  "6cc3f83949e7e079c4afb6b3b48d05a1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GenericMd80Msg-request)))
  "Returns md5sum for a message object of type 'GenericMd80Msg-request"
  "6cc3f83949e7e079c4afb6b3b48d05a1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GenericMd80Msg-request>)))
  "Returns full string definition for message of type '<GenericMd80Msg-request>"
  (cl:format cl:nil "uint16[] drive_ids~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GenericMd80Msg-request)))
  "Returns full string definition for message of type 'GenericMd80Msg-request"
  (cl:format cl:nil "uint16[] drive_ids~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GenericMd80Msg-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drive_ids) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GenericMd80Msg-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GenericMd80Msg-request
    (cl:cons ':drive_ids (drive_ids msg))
))
;//! \htmlinclude GenericMd80Msg-response.msg.html

(cl:defclass <GenericMd80Msg-response> (roslisp-msg-protocol:ros-message)
  ((drives_success
    :reader drives_success
    :initarg :drives_success
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass GenericMd80Msg-response (<GenericMd80Msg-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GenericMd80Msg-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GenericMd80Msg-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<GenericMd80Msg-response> is deprecated: use melew3_msgs-srv:GenericMd80Msg-response instead.")))

(cl:ensure-generic-function 'drives_success-val :lambda-list '(m))
(cl:defmethod drives_success-val ((m <GenericMd80Msg-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drives_success-val is deprecated.  Use melew3_msgs-srv:drives_success instead.")
  (drives_success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GenericMd80Msg-response>) ostream)
  "Serializes a message object of type '<GenericMd80Msg-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drives_success))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'drives_success))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GenericMd80Msg-response>) istream)
  "Deserializes a message object of type '<GenericMd80Msg-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'drives_success) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'drives_success)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GenericMd80Msg-response>)))
  "Returns string type for a service object of type '<GenericMd80Msg-response>"
  "melew3_msgs/GenericMd80MsgResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GenericMd80Msg-response)))
  "Returns string type for a service object of type 'GenericMd80Msg-response"
  "melew3_msgs/GenericMd80MsgResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GenericMd80Msg-response>)))
  "Returns md5sum for a message object of type '<GenericMd80Msg-response>"
  "6cc3f83949e7e079c4afb6b3b48d05a1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GenericMd80Msg-response)))
  "Returns md5sum for a message object of type 'GenericMd80Msg-response"
  "6cc3f83949e7e079c4afb6b3b48d05a1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GenericMd80Msg-response>)))
  "Returns full string definition for message of type '<GenericMd80Msg-response>"
  (cl:format cl:nil "bool[] drives_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GenericMd80Msg-response)))
  "Returns full string definition for message of type 'GenericMd80Msg-response"
  (cl:format cl:nil "bool[] drives_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GenericMd80Msg-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drives_success) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GenericMd80Msg-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GenericMd80Msg-response
    (cl:cons ':drives_success (drives_success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GenericMd80Msg)))
  'GenericMd80Msg-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GenericMd80Msg)))
  'GenericMd80Msg-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GenericMd80Msg)))
  "Returns string type for a service object of type '<GenericMd80Msg>"
  "melew3_msgs/GenericMd80Msg")