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

//-----------------------------------------------------------

class MotionCommand {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.drive_ids = null;
      this.target_position = null;
      this.target_velocity = null;
      this.target_torque = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('drive_ids')) {
        this.drive_ids = initObj.drive_ids
      }
      else {
        this.drive_ids = [];
      }
      if (initObj.hasOwnProperty('target_position')) {
        this.target_position = initObj.target_position
      }
      else {
        this.target_position = [];
      }
      if (initObj.hasOwnProperty('target_velocity')) {
        this.target_velocity = initObj.target_velocity
      }
      else {
        this.target_velocity = [];
      }
      if (initObj.hasOwnProperty('target_torque')) {
        this.target_torque = initObj.target_torque
      }
      else {
        this.target_torque = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MotionCommand
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [drive_ids]
    bufferOffset = _arraySerializer.uint16(obj.drive_ids, buffer, bufferOffset, null);
    // Serialize message field [target_position]
    bufferOffset = _arraySerializer.float32(obj.target_position, buffer, bufferOffset, null);
    // Serialize message field [target_velocity]
    bufferOffset = _arraySerializer.float32(obj.target_velocity, buffer, bufferOffset, null);
    // Serialize message field [target_torque]
    bufferOffset = _arraySerializer.float32(obj.target_torque, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MotionCommand
    let len;
    let data = new MotionCommand(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [drive_ids]
    data.drive_ids = _arrayDeserializer.uint16(buffer, bufferOffset, null)
    // Deserialize message field [target_position]
    data.target_position = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [target_velocity]
    data.target_velocity = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [target_torque]
    data.target_torque = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 2 * object.drive_ids.length;
    length += 4 * object.target_position.length;
    length += 4 * object.target_velocity.length;
    length += 4 * object.target_torque.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'melew3_msgs/MotionCommand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f3f2b5bb30e5e58d7a8bf6136b909823';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    uint16[] drive_ids
    float32[] target_position
    float32[] target_velocity
    float32[] target_torque
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MotionCommand(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.drive_ids !== undefined) {
      resolved.drive_ids = msg.drive_ids;
    }
    else {
      resolved.drive_ids = []
    }

    if (msg.target_position !== undefined) {
      resolved.target_position = msg.target_position;
    }
    else {
      resolved.target_position = []
    }

    if (msg.target_velocity !== undefined) {
      resolved.target_velocity = msg.target_velocity;
    }
    else {
      resolved.target_velocity = []
    }

    if (msg.target_torque !== undefined) {
      resolved.target_torque = msg.target_torque;
    }
    else {
      resolved.target_torque = []
    }

    return resolved;
    }
};

module.exports = MotionCommand;
