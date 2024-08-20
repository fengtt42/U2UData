
"use strict";

let Reset = require('./Reset.js')
let Takeoff = require('./Takeoff.js')
let SetLocalPosition = require('./SetLocalPosition.js')
let TakeoffGroup = require('./TakeoffGroup.js')
let LandGroup = require('./LandGroup.js')
let Land = require('./Land.js')
let SetGPSPosition = require('./SetGPSPosition.js')

module.exports = {
  Reset: Reset,
  Takeoff: Takeoff,
  SetLocalPosition: SetLocalPosition,
  TakeoffGroup: TakeoffGroup,
  LandGroup: LandGroup,
  Land: Land,
  SetGPSPosition: SetGPSPosition,
};
