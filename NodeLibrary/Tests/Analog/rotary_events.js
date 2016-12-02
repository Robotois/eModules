var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _rotary = require('../../RotaryModule'),
  rotary = new _rotary(1);
rotary.enableEvents();

rotary.on('Measurement',(_value,_scaledValue)=>{
  lcd.home();
  lcd.message(`Value: ${_value.toFixed(2)}`);
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
