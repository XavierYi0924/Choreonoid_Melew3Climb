; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude SetModeMd80s-request.msg.html

(cl:defclass <SetModeMd80s-request> (roslisp-msg-protocol:ros-message)
  ((drive_ids
    :reader drive_ids
    :initarg :drive_ids
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0))
   (mode
    :reader mode
    :initarg :mode
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element "")))
)

(cl:defclass SetModeMd80s-request (<SetModeMd80s-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetModeMd80s-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetModeMd80s-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<SetModeMd80s-request> is deprecated: use melew3_msgs-srv:SetModeMd80s-request instead.")))

(cl:ensure-generic-function 'drive_ids-val :lambda-list '(m))
(cl:defmethod drive_ids-val ((m <SetModeMd80s-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drive_ids-val is deprecated.  Use melew3_msgs-srv:drive_ids instead.")
  (drive_ids m))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <SetModeMd80s-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:mode-val is deprecated.  Use melew3_msgs-srv:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetModeMd80s-request>) ostream)
  "Serializes a message object of type '<SetModeMd80s-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drive_ids))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream))
   (cl:slot-value msg 'drive_ids))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'mode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'mode))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetModeMd80s-request>) istream)
  "Deserializes a message object of type '<SetModeMd80s-request>"
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
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'mode) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'mode)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetModeMd80s-request>)))
  "Returns string type for a service object of type '<SetModeMd80s-request>"
  "melew3_msgs/SetModeMd80sRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetModeMd80s-request)))
  "Returns string type for a service object of type 'SetModeMd80s-request"
  "melew3_msgs/SetModeMd80sRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetModeMd80s-request>)))
  "Returns md5sum for a message object of type '<SetModeMd80s-request>"
  "631d9a748d9039ca34b51f2d88d432cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetModeMd80s-request)))
  "Returns md5sum for a message object of type 'SetModeMd80s-request"
  "631d9a748d9039ca34b51f2d88d432cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetModeMd80s-request>)))
  "Returns full string definition for message of type '<SetModeMd80s-request>"
  (cl:format cl:nil "uint16[] drive_ids~%string[] mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetModeMd80s-request)))
  "Returns full string definition for message of type 'SetModeMd80s-request"
  (cl:format cl:nil "uint16[] drive_ids~%string[] mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetModeMd80s-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drive_ids) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'mode) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetModeMd80s-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetModeMd80s-request
    (cl:cons ':drive_ids (drive_ids msg))
    (cl:cons ':mode (mode msg))
))
;//! \htmlinclude SetModeMd80s-response.msg.html

(cl:defclass <SetModeMd80s-response> (roslisp-msg-protocol:ros-message)
  ((drives_success
    :reader drives_success
    :initarg :drives_success
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass SetModeMd80s-response (<SetModeMd80s-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetModeMd80s-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetModeMd80s-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<SetModeMd80s-response> is deprecated: use melew3_msgs-srv:SetModeMd80s-response instead.")))

(cl:ensure-generic-function 'drives_success-val :lambda-list '(m))
(cl:defmethod drives_success-val ((m <SetModeMd80s-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drives_success-val is deprecated.  Use melew3_msgs-srv:drives_success instead.")
  (drives_success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetModeMd80s-response>) ostream)
  "Serializes a message object of type '<SetModeMd80s-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drives_success))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'drives_success))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetModeMd80s-response>) istream)
  "Deserializes a message object of type '<SetModeMd80s-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetModeMd80s-response>)))
  "Returns string type for a service object of type '<SetModeMd80s-response>"
  "melew3_msgs/SetModeMd80sResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetModeMd80s-response)))
  "Returns string type for a service object of type 'SetModeMd80s-response"
  "melew3_msgs/SetModeMd80sResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetModeMd80s-response>)))
  "Returns md5sum for a message object of type '<SetModeMd80s-response>"
  "631d9a748d9039ca34b51f2d88d432cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetModeMd80s-response)))
  "Returns md5sum for a message object of type 'SetModeMd80s-response"
  "631d9a748d9039ca34b51f2d88d432cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetModeMd80s-response>)))
  "Returns full string definition for message of type '<SetModeMd80s-response>"
  (cl:format cl:nil "bool[] drives_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetModeMd80s-response)))
  "Returns full string definition for message of type 'SetModeMd80s-response"
  (cl:format cl:nil "bool[] drives_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetModeMd80s-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drives_success) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetModeMd80s-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetModeMd80s-response
    (cl:cons ':drives_success (drives_success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetModeMd80s)))
  'SetModeMd80s-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetModeMd80s)))
  'SetModeMd80s-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetModeMd80s)))
  "Returns string type for a service object of type '<SetModeMd80s>"
  "melew3_msgs/SetModeMd80s")