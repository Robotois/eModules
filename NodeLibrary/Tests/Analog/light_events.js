var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _light = require('../../LightModule'),
  light = new _light(3);
light.enableEvents();

// light.on('Measurement', (_scaledValue)=> {
//   // lcd.message("Light Value: \n" + _scaledValue);
//   // lcd.row_1_msg("Light Value: " + _scaledValue)
//   lcd.row_2_msg("Light Value: " + _scaledValue)
// })

setInterval(()=>{ // Proceso en estado ocioso
    // lcd.row_1_msg("value: " + light.getValue().toFixed(3));
    // lcd.row_2_msg("basic: " + light.getBasicValue());
    lcd.row_1_msg("Scaled: " + ("   "+light.getScaledValue()).slice(-4));
    lcd.row_2_msg("basic: " + light.getBasicScaledValue());
},1000);


setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
