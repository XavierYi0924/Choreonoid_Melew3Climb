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

class AddMd80sRequest {
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
    // Serializes a message object of type AddMd80sRequest
    // Serialize message field [drive_ids]
    bufferOffset = _arraySerializer.uint16(obj.drive_ids, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AddMd80sRequest
    let len;
    let data = new AddMd80sRequest(null);
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
    return 'melew3_msgs/AddMd80sRequest';
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
    const resolved = new AddMd80sRequest(null);
    if (msg.drive_ids !== undefined) {
      resolved.drive_ids = msg.drive_ids;
    }
    else {
      resolved.drive_ids = []
    }

    return resolved;
    }
};

class AddMd80sResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.drives_success = null;
      this.total_number_of_drives = null;
    }
    else {
      if (initObj.hasOwnProperty('drives_success')) {
        this.drives_success = initObj.drives_success
      }
      else {
        this.drives_success = [];
      }
      if (initObj.hasOwnProperty('total_number_of_drives')) {
        this.total_number_of_drives = initObj.total_number_of_drives
      }
      else {
        this.total_number_of_drives = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AddMd80sResponse
    // Serialize message field [drives_success]
    bufferOffset = _arraySerializer.bool(obj.drives_success, buffer, bufferOffset, null);
    // Serialize message field [total_number_of_drives]
    bufferOffset = _serializer.uint16(obj.total_number_of_drives, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AddMd80sResponse
    let len;
    let data = new AddMd80sResponse(null);
    // Deserialize message field [drives_success]
    data.drives_success = _arrayDeserializer.bool(buffer, bufferOffset, null)
    // Deserialize message field [total_number_of_drives]
    data.total_number_of_drives = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.drives_success.length;
    return length + 6;
  }

  static datatype() {
    // Returns string type for a service object
    return 'melew3_msgs/AddMd80sResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'eb11802d8e72df77ab2fa1c8f71e5432';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool[] drives_success
    uint16 total_number_of_drives
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new AddMd80sResponse(null);
    if (msg.drives_success !== undefined) {
      resolved.drives_success = msg.drives_success;
    }
    else {
      resolved.drives_success = []
    }

    if (msg.total_number_of_drives !== undefined) {
      resolved.total_number_of_drives = msg.total_number_of_drives;
    }
    else {
      resolved.total_number_of_drives = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: AddMd80sRequest,
  Response: AddMd80sResponse,
  md5sum() { return '4d3ef511c44dd08dd3627532b66a574c'; },
  datatype() { return 'melew3_msgs/AddMd80s'; }
};
