var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _temp = require('../../TemperatureSensor'),
  temp = new _temp(2);
temp.enableEvents();

// temp.on('Measurement',(_value)=>{
//   lcd.message("Temp [C]: " + _value);
// });

setInterval(()=>{ // Proceso en estado ocioso
  // lcd.row_1_msg("Temp: " + temp.getValue().toFixed(3));
  // lcd.row_2_msg("Basic: " + temp.getBasicValue());
  // var intValue = temp.getIntValue();
  // console.log(intValue);
  lcd.row_1_msg("Temp: " + temp.getValue().toFixed(3));
  lcd.row_2_msg("Int: " + temp.getIntValue());
},250);

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
