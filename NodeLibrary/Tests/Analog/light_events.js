var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _light = require('../../LightModule'),
  light = new _light(3);
light.enableEvents();

light.on('Measurement', (_value,_scaledValue)=> {
  lcd.home();
  lcd.message("Light Value: \n" + _value.toFixed(2));
})

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
