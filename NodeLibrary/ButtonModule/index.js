var Gpio = require('onoff').Gpio;
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

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

function ButtonModule(header){
  EventEmitter.call(this);
  var _self = this;
  // var button1,button2;
  switch (header) {
    case DigitalHeader1:
      this.button1 = new Gpio(DigitalHeader1_1,  'in', 'both');
      this.button2 = new Gpio(DigitalHeader1_2,  'in', 'both');
      break;
    case DigitalHeader2:
      this.button1 = new Gpio(DigitalHeader2_1,  'in', 'both');
      this.button2 = new Gpio(DigitalHeader2_2,  'in', 'both');
      break;
    case DigitalHeader3:
      this.button1 = new Gpio(DigitalHeader3_1,  'in', 'both');
      this.button2 = new Gpio(DigitalHeader3_2,  'in', 'both');
      break;
    case DigitalHeader4:
      this.button1 = new Gpio(DigitalHeader4_1,  'in', 'both');
      this.button2 = new Gpio(DigitalHeader4_2,  'in', 'both');
      break;
    default:
      console.log("Error selecting the digital Header...");
  }

  process.on('SIGINT', function () {
    // console.log('Unexporting buttons');
    _self.button1.unexport();
    _self.button2.unexport();
    process.exit();
  });

  process.on('SIGTERM', function () {
    console.log('[Buttons] => SIGTERM: Unexporting buttons');
    _self.button1.unexport();
    _self.button2.unexport();
    process.exit();
  });

  this.button1.watch(function (err, value) {
    if (err) {
      throw err;
    }
    console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
    // button1.writeSync(!value|0);
    _self.eventEmitter.emit('button1_change',!value|0);
  });

  this.button2.watch(function (err, value) {
    if (err) {
      throw err;
    }
    console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
    // button1.writeSync(!value|0);
    _self.eventEmitter.emit('button2_change',!value|0);
  });
}

// ButtonModule.prototype.setEventEmitter = function (_eventEmitter) {
//   this.eventEmitter = _eventEmitter;
//   var _self = this;
//
//   this.button1.watch(function (err, value) {
//     if (err) {
//       throw err;
//     }
//     // console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
//     // button1.writeSync(!value|0);
//     _self.eventEmitter.emit('button1Change',!value|0);
//   });
//
//   this.button2.watch(function (err, value) {
//     if (err) {
//       throw err;
//     }
//     // console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
//     // button1.writeSync(!value|0);
//     _self.eventEmitter.emit('button2Change',!value|0);
//   });
// };

ButtonModule.prototype.readButton1 = function () {
  var value = this.button1.readSync();
  return !value|0;
};

ButtonModule.prototype.readButton2 = function () {
  var value = this.button2.readSync();
  return !value|0;
};

inherits(ButtonModule,EventEmitter);

module.exports = ButtonModule;

// var Gpio = require('onoff').Gpio,
//   button1 = new Gpio(DigitalHeader2_1,  'in', 'both'),
//   button2 = new Gpio(DigitalHeader2_2,  'in', 'both'),
//   button1 = new Gpio(DigitalHeader1_1, 'in', 'both'),
//   button2 = new Gpio(DigitalHeader1_2, 'in', 'both');
//
// button1.watch(function (err, value) {
//   if (err) {
//     throw err;
//   }
//   // console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
//   button1.writeSync(!value|0);
// });
//
// button2.watch(function (err, value) {
//   if (err) {
//     throw err;
//   }
//   // console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
//   button2.writeSync(!value|0);
// });
//
// process.on('SIGINT', function () {
//   button1.unexport();
//   button1.unexport();
//   button2.unexport();
//   button2.unexport();
// });
