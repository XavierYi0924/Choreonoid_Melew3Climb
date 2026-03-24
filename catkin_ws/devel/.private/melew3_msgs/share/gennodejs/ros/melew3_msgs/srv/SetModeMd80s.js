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

class SetModeMd80sRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.drive_ids = null;
      this.mode = null;
    }
    else {
      if (initObj.hasOwnProperty('drive_ids')) {
        this.drive_ids = initObj.drive_ids
      }
      else {
        this.drive_ids = [];
      }
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetModeMd80sRequest
    // Serialize message field [drive_ids]
    bufferOffset = _arraySerializer.uint16(obj.drive_ids, buffer, bufferOffset, null);
    // Serialize message field [mode]
    bufferOffset = _arraySerializer.string(obj.mode, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetModeMd80sRequest
    let len;
    let data = new SetModeMd80sRequest(null);
    // Deserialize message field [drive_ids]
    data.drive_ids = _arrayDeserializer.uint16(buffer, bufferOffset, null)
    // Deserialize message field [mode]
    data.mode = _arrayDeserializer.string(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 2 * object.drive_ids.length;
    object.mode.forEach((val) => {
      length += 4 + _getByteLength(val);
    });
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/SetModeMd80sRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '32851f8d0659651d7f7ff111ae45e731';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16[] drive_ids
    string[] mode
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetModeMd80sRequest(null);
    if (msg.drive_ids !== undefined) {
      resolved.drive_ids = msg.drive_ids;
    }
    else {
      resolved.drive_ids = []
    }

    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = []
    }

    return resolved;
    }
};

class SetModeMd80sResponse {
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
    // Serializes a message object of type SetModeMd80sResponse
    // Serialize message field [drives_success]
    bufferOffset = _arraySerializer.bool(obj.drives_success, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetModeMd80sResponse
    let len;
    let data = new SetModeMd80sResponse(null);
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
    return 'melew3_msgs/SetModeMd80sResponse';
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
    const resolved = new SetModeMd80sResponse(null);
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
  Request: SetModeMd80sRequest,
  Response: SetModeMd80sResponse,
  md5sum() { return '631d9a748d9039ca34b51f2d88d432cb'; },
  datatype() { return 'melew3_msgs/SetModeMd80s'; }
};
