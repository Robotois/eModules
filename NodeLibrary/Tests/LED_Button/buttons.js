var _led  =  require('../../LEDModule'),
  led = new _led(2);
var _buttons = require('../../ButtonModule'),
  buttons = new _buttons(1);
var _loops = require('../../Loops'),
  loops = new _loops();

// loops.forever(()=>{
//   leds.setLED(buttons.readButton());
// })

// loops.while(
//   () => {return true}, // - stop contidion
//   () => { // - while body
//     // console.log(buttons.readButton1());
//     leds.setLED1(buttons.readButton1());
//     leds.setLED2(buttons.readButton2());
//   });
//

// loops.while(
//   () => {return true}, // - stop contidion
//   () => { // - while body
//     // console.log(buttons.readButton1());
//     leds.setLED1(buttons.readButton1());
//     leds.setLED2(buttons.readButton2());
//   });

buttons.enableEvents();
buttons.on('ButtonChange',(_state) => {
  console.log('Change Event: ' + _state);
  led.write(_state);
});

// setInterval(()=>{
//   console.log(buttons.readButton());
//   // leds.led_blink();
// },2000);
