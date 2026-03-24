; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude AddMd80s-request.msg.html

(cl:defclass <AddMd80s-request> (roslisp-msg-protocol:ros-message)
  ((drive_ids
    :reader drive_ids
    :initarg :drive_ids
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass AddMd80s-request (<AddMd80s-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AddMd80s-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AddMd80s-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<AddMd80s-request> is deprecated: use melew3_msgs-srv:AddMd80s-request instead.")))

(cl:ensure-generic-function 'drive_ids-val :lambda-list '(m))
(cl:defmethod drive_ids-val ((m <AddMd80s-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drive_ids-val is deprecated.  Use melew3_msgs-srv:drive_ids instead.")
  (drive_ids m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AddMd80s-request>) ostream)
  "Serializes a message object of type '<AddMd80s-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drive_ids))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream))
   (cl:slot-value msg 'drive_ids))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AddMd80s-request>) istream)
  "Deserializes a message object of type '<AddMd80s-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AddMd80s-request>)))
  "Returns string type for a service object of type '<AddMd80s-request>"
  "melew3_msgs/AddMd80sRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddMd80s-request)))
  "Returns string type for a service object of type 'AddMd80s-request"
  "melew3_msgs/AddMd80sRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AddMd80s-request>)))
  "Returns md5sum for a message object of type '<AddMd80s-request>"
  "4d3ef511c44dd08dd3627532b66a574c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AddMd80s-request)))
  "Returns md5sum for a message object of type 'AddMd80s-request"
  "4d3ef511c44dd08dd3627532b66a574c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AddMd80s-request>)))
  "Returns full string definition for message of type '<AddMd80s-request>"
  (cl:format cl:nil "uint16[] drive_ids~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AddMd80s-request)))
  "Returns full string definition for message of type 'AddMd80s-request"
  (cl:format cl:nil "uint16[] drive_ids~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AddMd80s-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drive_ids) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AddMd80s-request>))
  "Converts a ROS message object to a list"
  (cl:list 'AddMd80s-request
    (cl:cons ':drive_ids (drive_ids msg))
))
;//! \htmlinclude AddMd80s-response.msg.html

(cl:defclass <AddMd80s-response> (roslisp-msg-protocol:ros-message)
  ((drives_success
    :reader drives_success
    :initarg :drives_success
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil))
   (total_number_of_drives
    :reader total_number_of_drives
    :initarg :total_number_of_drives
    :type cl:fixnum
    :initform 0))
)

(cl:defclass AddMd80s-response (<AddMd80s-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AddMd80s-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AddMd80s-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<AddMd80s-response> is deprecated: use melew3_msgs-srv:AddMd80s-response instead.")))

(cl:ensure-generic-function 'drives_success-val :lambda-list '(m))
(cl:defmethod drives_success-val ((m <AddMd80s-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drives_success-val is deprecated.  Use melew3_msgs-srv:drives_success instead.")
  (drives_success m))

(cl:ensure-generic-function 'total_number_of_drives-val :lambda-list '(m))
(cl:defmethod total_number_of_drives-val ((m <AddMd80s-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:total_number_of_drives-val is deprecated.  Use melew3_msgs-srv:total_number_of_drives instead.")
  (total_number_of_drives m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AddMd80s-response>) ostream)
  "Serializes a message object of type '<AddMd80s-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drives_success))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'drives_success))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'total_number_of_drives)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'total_number_of_drives)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AddMd80s-response>) istream)
  "Deserializes a message object of type '<AddMd80s-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'drives_success) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'drives_success)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream)))))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'total_number_of_drives)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'total_number_of_drives)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AddMd80s-response>)))
  "Returns string type for a service object of type '<AddMd80s-response>"
  "melew3_msgs/AddMd80sResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddMd80s-response)))
  "Returns string type for a service object of type 'AddMd80s-response"
  "melew3_msgs/AddMd80sResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AddMd80s-response>)))
  "Returns md5sum for a message object of type '<AddMd80s-response>"
  "4d3ef511c44dd08dd3627532b66a574c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AddMd80s-response)))
  "Returns md5sum for a message object of type 'AddMd80s-response"
  "4d3ef511c44dd08dd3627532b66a574c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AddMd80s-response>)))
  "Returns full string definition for message of type '<AddMd80s-response>"
  (cl:format cl:nil "bool[] drives_success~%uint16 total_number_of_drives~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AddMd80s-response)))
  "Returns full string definition for message of type 'AddMd80s-response"
  (cl:format cl:nil "bool[] drives_success~%uint16 total_number_of_drives~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AddMd80s-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drives_success) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AddMd80s-response>))
  "Converts a ROS message object to a list"
  (cl:list 'AddMd80s-response
    (cl:cons ':drives_success (drives_success msg))
    (cl:cons ':total_number_of_drives (total_number_of_drives msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'AddMd80s)))
  'AddMd80s-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'AddMd80s)))
  'AddMd80s-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddMd80s)))
  "Returns string type for a service object of type '<AddMd80s>"
  "melew3_msgs/AddMd80s")