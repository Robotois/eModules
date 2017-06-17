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

var leds = require('./index');
var Gpio = require('onoff').Gpio,
  button1 = new Gpio(DigitalHeader1_1, 'in', 'both');
var EventEmitter = require('events').EventEmitter;

function ButtonModule(header) {
  EventEmitter.call(this);
  var button1,button2;
  switch (header) {
    case DigitalHeader1:
      button1 = new Gpio(DigitalHeader1_1,'in', 'both');
      button2 = new Gpio(DigitalHeader1_2,'in', 'both');
      break;
    case DigitalHeader2:
      button1 = new Gpio(DigitalHeader2_1, 'in', 'both');
      button2 = new Gpio(DigitalHeader2_2, 'in', 'both');
      break;
    case DigitalHeader3:
      button1 = new Gpio(DigitalHeader3_1, 'in', 'both');
      button2 = new Gpio(DigitalHeader3_2, 'in', 'both');
      break;
    case DigitalHeader4:
      button1 = new Gpio(DigitalHeader4_1, 'in', 'both');
      button2 = new Gpio(DigitalHeader4_2, 'in', 'both');
      break;
    default:
      console.log("Error selecting the digital Header...");
  }

  process.on('SIGINT', function () {
    // console.log('Unexporting leds');
    button1.unexport();
    button2.unexport();
    process.exit();
  });
}

ledModule = new leds(2);

ledModule.button1_watch('buttonChange');

button1.watch(function (err, value) {
  if (err) {
    throw err;
  }
  console.log("Current Button Value: " + value + ", Inverted value: " +(!value|0));
  emitter.emit('buttonChange',!value|0);
});
