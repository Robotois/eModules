var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _ultrasonic = require('../../UltrasonicSensor'),
  ultrasonic = new _ultrasonic(1);
// ultrasonic.enableEvents();

// ultrasonic.on('Measurement',(_distance)=>{
//   lcd.row_1_msg("Dist: " + ultrasonic.distToString(_distance));
// });
setInterval(()=>{ // Proceso en estado ocioso
  lcd.row_1_msg("Value: "+ultrasonic.getValue().toFixed(3));
  lcd.row_2_msg("Basic: "+ultrasonic.getBasicValue())
},500);

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
