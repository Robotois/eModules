var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _rotary = require('../../RotaryModule'),
  rotary = new _rotary(1);
rotary.enableEvents();

// rotary.on('Measurement',(_scaledValue)=>{
//   lcd.message(`Value: ${_scaledValue}`);
// });

setInterval(()=>{ // Proceso en estado ocioso
  // lcd.row_1_msg("Value: "+rotary.getValue().toFixed(3));
  // lcd.row_2_msg("basic: "+rotary.getBasicValue());
  lcd.row_1_msg("Value: "+("    "+rotary.getScaledValue()).slice(-4));
  lcd.row_2_msg("basic: "+rotary.getBasicScaledValue());
},100);

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
