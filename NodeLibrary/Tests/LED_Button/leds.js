var _leds  =  require('../LEDModule'),
  leds = new _leds(2);
var _buttons = require('../ButtonModule'),
  buttons = new _buttons(1);

var _loops = require('../loops'),
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

setInterval(()=>{
  // console.log(buttons.readButton());
  leds.led_blink();
},1000);

process.on('SIGINT', function () {
  // leds.unexport();
  process.exit();
});

process.on('SIGTERM', function () {
  // leds.unexport();
  // buttons.unexport();
  process.exit();
});
