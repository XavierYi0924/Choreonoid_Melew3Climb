; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude SetLimitsMd80-request.msg.html

(cl:defclass <SetLimitsMd80-request> (roslisp-msg-protocol:ros-message)
  ((drive_ids
    :reader drive_ids
    :initarg :drive_ids
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0))
   (velocity_limit
    :reader velocity_limit
    :initarg :velocity_limit
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (torque_limit
    :reader torque_limit
    :initarg :torque_limit
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass SetLimitsMd80-request (<SetLimitsMd80-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetLimitsMd80-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetLimitsMd80-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<SetLimitsMd80-request> is deprecated: use melew3_msgs-srv:SetLimitsMd80-request instead.")))

(cl:ensure-generic-function 'drive_ids-val :lambda-list '(m))
(cl:defmethod drive_ids-val ((m <SetLimitsMd80-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drive_ids-val is deprecated.  Use melew3_msgs-srv:drive_ids instead.")
  (drive_ids m))

(cl:ensure-generic-function 'velocity_limit-val :lambda-list '(m))
(cl:defmethod velocity_limit-val ((m <SetLimitsMd80-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:velocity_limit-val is deprecated.  Use melew3_msgs-srv:velocity_limit instead.")
  (velocity_limit m))

(cl:ensure-generic-function 'torque_limit-val :lambda-list '(m))
(cl:defmethod torque_limit-val ((m <SetLimitsMd80-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:torque_limit-val is deprecated.  Use melew3_msgs-srv:torque_limit instead.")
  (torque_limit m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetLimitsMd80-request>) ostream)
  "Serializes a message object of type '<SetLimitsMd80-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drive_ids))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream))
   (cl:slot-value msg 'drive_ids))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'velocity_limit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'velocity_limit))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'torque_limit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'torque_limit))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetLimitsMd80-request>) istream)
  "Deserializes a message object of type '<SetLimitsMd80-request>"
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
  (cl:setf (cl:slot-value msg 'velocity_limit) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'velocity_limit)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'torque_limit) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'torque_limit)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetLimitsMd80-request>)))
  "Returns string type for a service object of type '<SetLimitsMd80-request>"
  "melew3_msgs/SetLimitsMd80Request")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetLimitsMd80-request)))
  "Returns string type for a service object of type 'SetLimitsMd80-request"
  "melew3_msgs/SetLimitsMd80Request")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetLimitsMd80-request>)))
  "Returns md5sum for a message object of type '<SetLimitsMd80-request>"
  "8b812c4224ab59c832e9c192ff752c8d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetLimitsMd80-request)))
  "Returns md5sum for a message object of type 'SetLimitsMd80-request"
  "8b812c4224ab59c832e9c192ff752c8d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetLimitsMd80-request>)))
  "Returns full string definition for message of type '<SetLimitsMd80-request>"
  (cl:format cl:nil "uint16[] drive_ids~%float32[] velocity_limit~%float32[] torque_limit~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetLimitsMd80-request)))
  "Returns full string definition for message of type 'SetLimitsMd80-request"
  (cl:format cl:nil "uint16[] drive_ids~%float32[] velocity_limit~%float32[] torque_limit~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetLimitsMd80-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drive_ids) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'velocity_limit) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'torque_limit) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetLimitsMd80-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetLimitsMd80-request
    (cl:cons ':drive_ids (drive_ids msg))
    (cl:cons ':velocity_limit (velocity_limit msg))
    (cl:cons ':torque_limit (torque_limit msg))
))
;//! \htmlinclude SetLimitsMd80-response.msg.html

(cl:defclass <SetLimitsMd80-response> (roslisp-msg-protocol:ros-message)
  ((drives_success
    :reader drives_success
    :initarg :drives_success
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass SetLimitsMd80-response (<SetLimitsMd80-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetLimitsMd80-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetLimitsMd80-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<SetLimitsMd80-response> is deprecated: use melew3_msgs-srv:SetLimitsMd80-response instead.")))

(cl:ensure-generic-function 'drives_success-val :lambda-list '(m))
(cl:defmethod drives_success-val ((m <SetLimitsMd80-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:drives_success-val is deprecated.  Use melew3_msgs-srv:drives_success instead.")
  (drives_success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetLimitsMd80-response>) ostream)
  "Serializes a message object of type '<SetLimitsMd80-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'drives_success))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'drives_success))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetLimitsMd80-response>) istream)
  "Deserializes a message object of type '<SetLimitsMd80-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetLimitsMd80-response>)))
  "Returns string type for a service object of type '<SetLimitsMd80-response>"
  "melew3_msgs/SetLimitsMd80Response")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetLimitsMd80-response)))
  "Returns string type for a service object of type 'SetLimitsMd80-response"
  "melew3_msgs/SetLimitsMd80Response")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetLimitsMd80-response>)))
  "Returns md5sum for a message object of type '<SetLimitsMd80-response>"
  "8b812c4224ab59c832e9c192ff752c8d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetLimitsMd80-response)))
  "Returns md5sum for a message object of type 'SetLimitsMd80-response"
  "8b812c4224ab59c832e9c192ff752c8d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetLimitsMd80-response>)))
  "Returns full string definition for message of type '<SetLimitsMd80-response>"
  (cl:format cl:nil "bool[] drives_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetLimitsMd80-response)))
  "Returns full string definition for message of type 'SetLimitsMd80-response"
  (cl:format cl:nil "bool[] drives_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetLimitsMd80-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'drives_success) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetLimitsMd80-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetLimitsMd80-response
    (cl:cons ':drives_success (drives_success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetLimitsMd80)))
  'SetLimitsMd80-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetLimitsMd80)))
  'SetLimitsMd80-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetLimitsMd80)))
  "Returns string type for a service object of type '<SetLimitsMd80>"
  "melew3_msgs/SetLimitsMd80")