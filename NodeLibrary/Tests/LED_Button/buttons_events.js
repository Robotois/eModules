var _led  =  require('../../LEDModule'),
  led = new _led(2);

var _buttons = require('../../ButtonModule'),
  buttons = new _buttons(1);
buttons.enableEvents();

buttons.on('change',(_state) => {
  led.write(_state);
});

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
