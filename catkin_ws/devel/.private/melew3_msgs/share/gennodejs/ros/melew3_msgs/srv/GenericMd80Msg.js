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

class GenericMd80MsgRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.drive_ids = null;
    }
    else {
      if (initObj.hasOwnProperty('drive_ids')) {
        this.drive_ids = initObj.drive_ids
      }
      else {
        this.drive_ids = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GenericMd80MsgRequest
    // Serialize message field [drive_ids]
    bufferOffset = _arraySerializer.uint16(obj.drive_ids, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GenericMd80MsgRequest
    let len;
    let data = new GenericMd80MsgRequest(null);
    // Deserialize message field [drive_ids]
    data.drive_ids = _arrayDeserializer.uint16(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 2 * object.drive_ids.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/GenericMd80MsgRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c08ac4358e4fa3d3b54deb5b46cf2f78';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16[] drive_ids
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GenericMd80MsgRequest(null);
    if (msg.drive_ids !== undefined) {
      resolved.drive_ids = msg.drive_ids;
    }
    else {
      resolved.drive_ids = []
    }

    return resolved;
    }
};

class GenericMd80MsgResponse {
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
    // Serializes a message object of type GenericMd80MsgResponse
    // Serialize message field [drives_success]
    bufferOffset = _arraySerializer.bool(obj.drives_success, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GenericMd80MsgResponse
    let len;
    let data = new GenericMd80MsgResponse(null);
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
    return 'melew3_msgs/GenericMd80MsgResponse';
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
    const resolved = new GenericMd80MsgResponse(null);
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
  Request: GenericMd80MsgRequest,
  Response: GenericMd80MsgResponse,
  md5sum() { return '6cc3f83949e7e079c4afb6b3b48d05a1'; },
  datatype() { return 'melew3_msgs/GenericMd80Msg'; }
};
