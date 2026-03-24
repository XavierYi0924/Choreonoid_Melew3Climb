// Auto-generated. Do not edit!

// (in-package melew3_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let motor_info = require('../msg/motor_info.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class robot_configRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motor = null;
    }
    else {
      if (initObj.hasOwnProperty('motor')) {
        this.motor = initObj.motor
      }
      else {
        this.motor = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_configRequest
    // Serialize message field [motor]
    // Serialize the length for message field [motor]
    bufferOffset = _serializer.uint32(obj.motor.length, buffer, bufferOffset);
    obj.motor.forEach((val) => {
      bufferOffset = motor_info.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_configRequest
    let len;
    let data = new robot_configRequest(null);
    // Deserialize message field [motor]
    // Deserialize array length for message field [motor]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.motor = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.motor[i] = motor_info.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.motor.forEach((val) => {
      length += motor_info.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/robot_configRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2c92bad7cfc0d8a1f6189c76b43a561a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Information for robot to be passed to the microcontroller
    melew3_msgs/motor_info[] motor
    
    ================================================================================
    MSG: melew3_msgs/motor_info
    # Information for the motor to use
    string name
    uint8 can_id
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_configRequest(null);
    if (msg.motor !== undefined) {
      resolved.motor = new Array(msg.motor.length);
      for (let i = 0; i < resolved.motor.length; ++i) {
        resolved.motor[i] = motor_info.Resolve(msg.motor[i]);
      }
    }
    else {
      resolved.motor = []
    }

    return resolved;
    }
};

class robot_configResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motor_quantity = null;
      this.checksum = null;
    }
    else {
      if (initObj.hasOwnProperty('motor_quantity')) {
        this.motor_quantity = initObj.motor_quantity
      }
      else {
        this.motor_quantity = 0;
      }
      if (initObj.hasOwnProperty('checksum')) {
        this.checksum = initObj.checksum
      }
      else {
        this.checksum = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_configResponse
    // Serialize message field [motor_quantity]
    bufferOffset = _serializer.uint8(obj.motor_quantity, buffer, bufferOffset);
    // Serialize message field [checksum]
    bufferOffset = _serializer.uint8(obj.checksum, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_configResponse
    let len;
    let data = new robot_configResponse(null);
    // Deserialize message field [motor_quantity]
    data.motor_quantity = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [checksum]
    data.checksum = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/robot_configResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bdd1d5c3a24f0bb18e3657f15e56ddf5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 motor_quantity
    uint8 checksum
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_configResponse(null);
    if (msg.motor_quantity !== undefined) {
      resolved.motor_quantity = msg.motor_quantity;
    }
    else {
      resolved.motor_quantity = 0
    }

    if (msg.checksum !== undefined) {
      resolved.checksum = msg.checksum;
    }
    else {
      resolved.checksum = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: robot_configRequest,
  Response: robot_configResponse,
  md5sum() { return 'd0ea6905ae3e9bf592297d448a99911d'; },
  datatype() { return 'melew3_msgs/robot_config'; }
};
