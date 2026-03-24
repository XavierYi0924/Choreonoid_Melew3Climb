; Auto-generated. Do not edit!


(cl:in-package melew3_msgs-srv)


;//! \htmlinclude set_pd_gain-request.msg.html

(cl:defclass <set_pd_gain-request> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass set_pd_gain-request (<set_pd_gain-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_pd_gain-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_pd_gain-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<set_pd_gain-request> is deprecated: use melew3_msgs-srv:set_pd_gain-request instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <set_pd_gain-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:mode-val is deprecated.  Use melew3_msgs-srv:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_pd_gain-request>) ostream)
  "Serializes a message object of type '<set_pd_gain-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'mode) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_pd_gain-request>) istream)
  "Deserializes a message object of type '<set_pd_gain-request>"
    (cl:setf (cl:slot-value msg 'mode) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_pd_gain-request>)))
  "Returns string type for a service object of type '<set_pd_gain-request>"
  "melew3_msgs/set_pd_gainRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_pd_gain-request)))
  "Returns string type for a service object of type 'set_pd_gain-request"
  "melew3_msgs/set_pd_gainRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_pd_gain-request>)))
  "Returns md5sum for a message object of type '<set_pd_gain-request>"
  "a585292d7f5827a6441e76e5026dbae6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_pd_gain-request)))
  "Returns md5sum for a message object of type 'set_pd_gain-request"
  "a585292d7f5827a6441e76e5026dbae6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_pd_gain-request>)))
  "Returns full string definition for message of type '<set_pd_gain-request>"
  (cl:format cl:nil "# enable/disable~%bool mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_pd_gain-request)))
  "Returns full string definition for message of type 'set_pd_gain-request"
  (cl:format cl:nil "# enable/disable~%bool mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_pd_gain-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_pd_gain-request>))
  "Converts a ROS message object to a list"
  (cl:list 'set_pd_gain-request
    (cl:cons ':mode (mode msg))
))
;//! \htmlinclude set_pd_gain-response.msg.html

(cl:defclass <set_pd_gain-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass set_pd_gain-response (<set_pd_gain-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_pd_gain-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_pd_gain-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name melew3_msgs-srv:<set_pd_gain-response> is deprecated: use melew3_msgs-srv:set_pd_gain-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <set_pd_gain-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader melew3_msgs-srv:success-val is deprecated.  Use melew3_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_pd_gain-response>) ostream)
  "Serializes a message object of type '<set_pd_gain-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_pd_gain-response>) istream)
  "Deserializes a message object of type '<set_pd_gain-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_pd_gain-response>)))
  "Returns string type for a service object of type '<set_pd_gain-response>"
  "melew3_msgs/set_pd_gainResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_pd_gain-response)))
  "Returns string type for a service object of type 'set_pd_gain-response"
  "melew3_msgs/set_pd_gainResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_pd_gain-response>)))
  "Returns md5sum for a message object of type '<set_pd_gain-response>"
  "a585292d7f5827a6441e76e5026dbae6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_pd_gain-response)))
  "Returns md5sum for a message object of type 'set_pd_gain-response"
  "a585292d7f5827a6441e76e5026dbae6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_pd_gain-response>)))
  "Returns full string definition for message of type '<set_pd_gain-response>"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_pd_gain-response)))
  "Returns full string definition for message of type 'set_pd_gain-response"
  (cl:format cl:nil "# Whether if configuration success~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_pd_gain-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_pd_gain-response>))
  "Converts a ROS message object to a list"
  (cl:list 'set_pd_gain-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'set_pd_gain)))
  'set_pd_gain-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'set_pd_gain)))
  'set_pd_gain-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_pd_gain)))
  "Returns string type for a service object of type '<set_pd_gain>"
  "melew3_msgs/set_pd_gain")