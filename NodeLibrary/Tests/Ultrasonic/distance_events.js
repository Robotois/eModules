var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _ultrasonic = require('../../UltrasonicModule'),
  ultrasonic = new _ultrasonic(5);
ultrasonic.enableEvents();

ultrasonic.on('Measurement',(_distance)=>{
  lcd.row_1_msg("Distancia: " + ultrasonic.distToString(_distance));
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
