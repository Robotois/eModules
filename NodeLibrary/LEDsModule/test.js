var leds = require('./index');
var buttons = require('../ButtonModule/index');

const EventEmitter = require('events');
class MyEmitter extends EventEmitter {}
const myEmitter = new MyEmitter();

ledModule = new leds(2);
// ledModule.setEventEmitter(myEmitter);
buttonModule = new buttons(1);
// buttonModule.setEventEmitter(myEmitter);
// buttonModule.enableEvents();

// ledModule.led1_watch('button1Change');
// ledModule.led2_watch('button2Change');


setInterval(function (){
  console.log(buttonModule.readButton1());
},1000)
