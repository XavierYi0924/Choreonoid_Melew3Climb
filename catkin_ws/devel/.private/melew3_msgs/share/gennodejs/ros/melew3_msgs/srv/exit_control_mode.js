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

class exit_control_modeRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.CAN_ID = null;
    }
    else {
      if (initObj.hasOwnProperty('CAN_ID')) {
        this.CAN_ID = initObj.CAN_ID
      }
      else {
        this.CAN_ID = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type exit_control_modeRequest
    // Serialize message field [CAN_ID]
    bufferOffset = _serializer.uint8(obj.CAN_ID, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type exit_control_modeRequest
    let len;
    let data = new exit_control_modeRequest(null);
    // Deserialize message field [CAN_ID]
    data.CAN_ID = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/exit_control_modeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f930db358785fbbc5d2a0424c4fb00c8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # CAN_ID of the motor
    uint8 CAN_ID
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new exit_control_modeRequest(null);
    if (msg.CAN_ID !== undefined) {
      resolved.CAN_ID = msg.CAN_ID;
    }
    else {
      resolved.CAN_ID = 0
    }

    return resolved;
    }
};

class exit_control_modeResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type exit_control_modeResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type exit_control_modeResponse
    let len;
    let data = new exit_control_modeResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/exit_control_modeResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '358e233cde0c8a8bcfea4ce193f8fc15';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Whether if configuration success
    bool success
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new exit_control_modeResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: exit_control_modeRequest,
  Response: exit_control_modeResponse,
  md5sum() { return 'd34ae0ac05d13cf23c6d78c27795e4e8'; },
  datatype() { return 'melew3_msgs/exit_control_mode'; }
};
