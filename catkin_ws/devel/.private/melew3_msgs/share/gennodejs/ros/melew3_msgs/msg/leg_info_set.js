// Auto-generated. Do not edit!

// (in-package melew3_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let leg_info = require('./leg_info.js');

//-----------------------------------------------------------

class leg_info_set {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.leg = null;
    }
    else {
      if (initObj.hasOwnProperty('leg')) {
        this.leg = initObj.leg
      }
      else {
        this.leg = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type leg_info_set
    // Serialize message field [leg]
    // Serialize the length for message field [leg]
    bufferOffset = _serializer.uint32(obj.leg.length, buffer, bufferOffset);
    obj.leg.forEach((val) => {
      bufferOffset = leg_info.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type leg_info_set
    let len;
    let data = new leg_info_set(null);
    // Deserialize message field [leg]
    // Deserialize array length for message field [leg]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.leg = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.leg[i] = leg_info.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 20 * object.leg.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'melew3_msgs/leg_info_set';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '60a0c1f02ecf6d55f23aa1de78f2fe2b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 脚先位置のpub用
    melew3_msgs/leg_info[] leg
    ================================================================================
    MSG: melew3_msgs/leg_info
    geometry_msgs/Point32 position
    std_msgs/Float64 yaw
    ================================================================================
    MSG: geometry_msgs/Point32
    # This contains the position of a point in free space(with 32 bits of precision).
    # It is recommeded to use Point wherever possible instead of Point32.  
    # 
    # This recommendation is to promote interoperability.  
    #
    # This message is designed to take up less space when sending
    # lots of points at once, as in the case of a PointCloud.  
    
    float32 x
    float32 y
    float32 z
    ================================================================================
    MSG: std_msgs/Float64
    float64 data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new leg_info_set(null);
    if (msg.leg !== undefined) {
      resolved.leg = new Array(msg.leg.length);
      for (let i = 0; i < resolved.leg.length; ++i) {
        resolved.leg[i] = leg_info.Resolve(msg.leg[i]);
      }
    }
    else {
      resolved.leg = []
    }

    return resolved;
    }
};

module.exports = leg_info_set;
