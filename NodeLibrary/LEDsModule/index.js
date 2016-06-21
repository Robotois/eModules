var Gpio = require('onoff').Gpio;
// var EventEmitter = require('events').EventEmitter;
// var inherits = require('util').inherits;

var DigitalHeader1 = 1;
var DigitalHeader1_1 = 5; // 3.3v Logic IO
var DigitalHeader1_2 = 6; // 3.3v Logic IO
var DigitalHeader2 = 2;
var DigitalHeader2_1 = 12; // 3.3v Logic IO
var DigitalHeader2_2 = 13; // 3.3v Logic IO
var DigitalHeader3 = 3;
var DigitalHeader3_1 = 16; // 3.3v Logic IO
var DigitalHeader3_2 = 19; // 3.3v Logic IO
var DigitalHeader4 = 4;
var DigitalHeader4_1 = 20; // 3.3v Logic IO
var DigitalHeader4_2 = 26; // 3.3v Logic IO

function LEDModule(header){
  // EventEmitter.call(this);
  var _self = this;
  // var led1,led2;
  switch (header) {
    case DigitalHeader1:
      this.led1 = new Gpio(DigitalHeader1_1, 'low');
      this.led2 = new Gpio(DigitalHeader1_2, 'low');
      break;
    case DigitalHeader2:
      this.led1 = new Gpio(DigitalHeader2_1, 'low');
      this.led2 = new Gpio(DigitalHeader2_2, 'low');
      break;
    case DigitalHeader3:
      this.led1 = new Gpio(DigitalHeader3_1, 'low');
      this.led2 = new Gpio(DigitalHeader3_2, 'low');
      break;
    case DigitalHeader4:
      this.led1 = new Gpio(DigitalHeader4_1, 'low');
      this.led2 = new Gpio(DigitalHeader4_2, 'low');
      break;
    default:
      console.log("Error selecting the digital Header...");
  }

  process.on('SIGINT', function () {
    _self.led1.unexport();
    _self.led2.unexport();
    process.exit();
  });

  process.on('SIGTERM', function () {
    console.log('[LEDs] => SIGTERM: Unexporting LEDs');
    _self.led1.unexport();
    _self.led2.unexport();
    process.exit();
  });
}

// inherits(LEDModule,EventEmitter);

// LEDModule.prototype.setEventEmitter = function (_eventEmitter) {
//   this.eventEmitter = _eventEmitter;
// };

// LEDModule.prototype.led1_watch = function (eventName) {
//   var _self = this;
//   // console.log('Setting event: ' + eventName);
//   // console.log(this);
//   this.eventEmitter.on(eventName,function (ledValue){
//     // console.log(ledValue,_self);
//     _self.led1.writeSync(ledValue);
//   });
// };

LEDModule.prototype.setLED1 = function (ledValue) {
  this.led1.writeSync(ledValue);
};

LEDModule.prototype.setLED2 = function (ledValue) {
  this.led2.writeSync(ledValue);
};

// LEDModule.prototype.led2_watch = function (eventName) {
//   var _self = this;
//   // console.log('Setting event: ' + eventName);
//   // console.log(this);
//   this.eventEmitter.on(eventName,function (ledValue){
//     // console.log(ledValue,_self);
//     _self.led2.writeSync(ledValue);
//   });
// };

module.exports = LEDModule;

// var Gpio = require('onoff').Gpio,
//   led1 = new Gpio(DigitalHeader2_1, 'low'),
//   led2 = new Gpio(DigitalHeader2_2, 'low'),
//   button1 = new Gpio(DigitalHeader1_1, 'in', 'both'),
//   button2 = new Gpio(DigitalHeader1_2, 'in', 'both');
//
// button1.watch(function (err, value) {
//   if (err) {
//     throw err;
//   }
//   // console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
//   led1.writeSync(!value|0);
// });
//
// button2.watch(function (err, value) {
//   if (err) {
//     throw err;
//   }
//   // console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
//   led2.writeSync(!value|0);
// });
//
// process.on('SIGINT', function () {
//   led1.unexport();
//   button1.unexport();
//   led2.unexport();
//   button2.unexport();
// });
