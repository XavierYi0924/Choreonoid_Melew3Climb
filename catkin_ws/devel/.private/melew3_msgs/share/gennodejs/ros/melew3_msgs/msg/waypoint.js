// Auto-generated. Do not edit!

// (in-package melew3_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class waypoint {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.time = null;
      this.position = null;
      this.velocity = null;
      this.acceleration = null;
      this.yaw_position = null;
      this.yaw_velocity = null;
      this.yaw_acceleration = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('time')) {
        this.time = initObj.time
      }
      else {
        this.time = new std_msgs.msg.Float64();
      }
      if (initObj.hasOwnProperty('position')) {
        this.position = initObj.position
      }
      else {
        this.position = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('velocity')) {
        this.velocity = initObj.velocity
      }
      else {
        this.velocity = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('acceleration')) {
        this.acceleration = initObj.acceleration
      }
      else {
        this.acceleration = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('yaw_position')) {
        this.yaw_position = initObj.yaw_position
      }
      else {
        this.yaw_position = new std_msgs.msg.Float64();
      }
      if (initObj.hasOwnProperty('yaw_velocity')) {
        this.yaw_velocity = initObj.yaw_velocity
      }
      else {
        this.yaw_velocity = new std_msgs.msg.Float64();
      }
      if (initObj.hasOwnProperty('yaw_acceleration')) {
        this.yaw_acceleration = initObj.yaw_acceleration
      }
      else {
        this.yaw_acceleration = new std_msgs.msg.Float64();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type waypoint
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [time]
    bufferOffset = std_msgs.msg.Float64.serialize(obj.time, buffer, bufferOffset);
    // Serialize message field [position]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.position, buffer, bufferOffset);
    // Serialize message field [velocity]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.velocity, buffer, bufferOffset);
    // Serialize message field [acceleration]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.acceleration, buffer, bufferOffset);
    // Serialize message field [yaw_position]
    bufferOffset = std_msgs.msg.Float64.serialize(obj.yaw_position, buffer, bufferOffset);
    // Serialize message field [yaw_velocity]
    bufferOffset = std_msgs.msg.Float64.serialize(obj.yaw_velocity, buffer, bufferOffset);
    // Serialize message field [yaw_acceleration]
    bufferOffset = std_msgs.msg.Float64.serialize(obj.yaw_acceleration, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type waypoint
    let len;
    let data = new waypoint(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [time]
    data.time = std_msgs.msg.Float64.deserialize(buffer, bufferOffset);
    // Deserialize message field [position]
    data.position = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [velocity]
    data.velocity = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [acceleration]
    data.acceleration = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [yaw_position]
    data.yaw_position = std_msgs.msg.Float64.deserialize(buffer, bufferOffset);
    // Deserialize message field [yaw_velocity]
    data.yaw_velocity = std_msgs.msg.Float64.deserialize(buffer, bufferOffset);
    // Deserialize message field [yaw_acceleration]
    data.yaw_acceleration = std_msgs.msg.Float64.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 104;
  }

  static datatype() {
    // Returns string type for a message object
    return 'melew3_msgs/waypoint';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c206810b38430fa29a10e74179d3b4cd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    std_msgs/Float64 time # 時刻
    geometry_msgs/Point position # 位置
    geometry_msgs/Point velocity # 速度
    geometry_msgs/Point acceleration # 加速度
    std_msgs/Float64 yaw_position # 操舵角
    std_msgs/Float64 yaw_velocity # 操舵角速度
    std_msgs/Float64 yaw_acceleration # 操舵角加速度
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: std_msgs/Float64
    float64 data
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new waypoint(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.time !== undefined) {
      resolved.time = std_msgs.msg.Float64.Resolve(msg.time)
    }
    else {
      resolved.time = new std_msgs.msg.Float64()
    }

    if (msg.position !== undefined) {
      resolved.position = geometry_msgs.msg.Point.Resolve(msg.position)
    }
    else {
      resolved.position = new geometry_msgs.msg.Point()
    }

    if (msg.velocity !== undefined) {
      resolved.velocity = geometry_msgs.msg.Point.Resolve(msg.velocity)
    }
    else {
      resolved.velocity = new geometry_msgs.msg.Point()
    }

    if (msg.acceleration !== undefined) {
      resolved.acceleration = geometry_msgs.msg.Point.Resolve(msg.acceleration)
    }
    else {
      resolved.acceleration = new geometry_msgs.msg.Point()
    }

    if (msg.yaw_position !== undefined) {
      resolved.yaw_position = std_msgs.msg.Float64.Resolve(msg.yaw_position)
    }
    else {
      resolved.yaw_position = new std_msgs.msg.Float64()
    }

    if (msg.yaw_velocity !== undefined) {
      resolved.yaw_velocity = std_msgs.msg.Float64.Resolve(msg.yaw_velocity)
    }
    else {
      resolved.yaw_velocity = new std_msgs.msg.Float64()
    }

    if (msg.yaw_acceleration !== undefined) {
      resolved.yaw_acceleration = std_msgs.msg.Float64.Resolve(msg.yaw_acceleration)
    }
    else {
      resolved.yaw_acceleration = new std_msgs.msg.Float64()
    }

    return resolved;
    }
};

module.exports = waypoint;
