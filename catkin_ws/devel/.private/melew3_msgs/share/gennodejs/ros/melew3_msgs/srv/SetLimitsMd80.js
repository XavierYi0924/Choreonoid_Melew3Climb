// Auto-generated. Do not edit!

// (in-package melew3_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetLimitsMd80Request {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.drive_ids = null;
      this.velocity_limit = null;
      this.torque_limit = null;
    }
    else {
      if (initObj.hasOwnProperty('drive_ids')) {
        this.drive_ids = initObj.drive_ids
      }
      else {
        this.drive_ids = [];
      }
      if (initObj.hasOwnProperty('velocity_limit')) {
        this.velocity_limit = initObj.velocity_limit
      }
      else {
        this.velocity_limit = [];
      }
      if (initObj.hasOwnProperty('torque_limit')) {
        this.torque_limit = initObj.torque_limit
      }
      else {
        this.torque_limit = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetLimitsMd80Request
    // Serialize message field [drive_ids]
    bufferOffset = _arraySerializer.uint16(obj.drive_ids, buffer, bufferOffset, null);
    // Serialize message field [velocity_limit]
    bufferOffset = _arraySerializer.float32(obj.velocity_limit, buffer, bufferOffset, null);
    // Serialize message field [torque_limit]
    bufferOffset = _arraySerializer.float32(obj.torque_limit, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetLimitsMd80Request
    let len;
    let data = new SetLimitsMd80Request(null);
    // Deserialize message field [drive_ids]
    data.drive_ids = _arrayDeserializer.uint16(buffer, bufferOffset, null)
    // Deserialize message field [velocity_limit]
    data.velocity_limit = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [torque_limit]
    data.torque_limit = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 2 * object.drive_ids.length;
    length += 4 * object.velocity_limit.length;
    length += 4 * object.torque_limit.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/SetLimitsMd80Request';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b6f95b7a29265a585ed64ff168463201';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16[] drive_ids
    float32[] velocity_limit
    float32[] torque_limit
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetLimitsMd80Request(null);
    if (msg.drive_ids !== undefined) {
      resolved.drive_ids = msg.drive_ids;
    }
    else {
      resolved.drive_ids = []
    }

    if (msg.velocity_limit !== undefined) {
      resolved.velocity_limit = msg.velocity_limit;
    }
    else {
      resolved.velocity_limit = []
    }

    if (msg.torque_limit !== undefined) {
      resolved.torque_limit = msg.torque_limit;
    }
    else {
      resolved.torque_limit = []
    }

    return resolved;
    }
};

class SetLimitsMd80Response {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.drives_success = null;
    }
    else {
      if (initObj.hasOwnProperty('drives_success')) {
        this.drives_success = initObj.drives_success
      }
      else {
        this.drives_success = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetLimitsMd80Response
    // Serialize message field [drives_success]
    bufferOffset = _arraySerializer.bool(obj.drives_success, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetLimitsMd80Response
    let len;
    let data = new SetLimitsMd80Response(null);
    // Deserialize message field [drives_success]
    data.drives_success = _arrayDeserializer.bool(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.drives_success.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/SetLimitsMd80Response';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b30d009cfc0cfb9ca816018e07d4b44a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool[] drives_success
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetLimitsMd80Response(null);
    if (msg.drives_success !== undefined) {
      resolved.drives_success = msg.drives_success;
    }
    else {
      resolved.drives_success = []
    }

    return resolved;
    }
};

module.exports = {
  Request: SetLimitsMd80Request,
  Response: SetLimitsMd80Response,
  md5sum() { return '8b812c4224ab59c832e9c192ff752c8d'; },
  datatype() { return 'melew3_msgs/SetLimitsMd80'; }
};
