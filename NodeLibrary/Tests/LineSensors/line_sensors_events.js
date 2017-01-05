var _line_sensors = require('../../LineSensorsModule'),
    line_sensors = new _line_sensors();
line_sensors.setBackground("Black");
line_sensors.enableEvents();

var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _leds  =  require('../../LEDModule'),
  led1 = new _leds(5),
  led2 = new _leds(6);

/** LCD Display for Sensors status **/
line_sensors.on('Measurement',(_sensors,_line)=>{
  // console.log(_sensors + " " + _line);
  lcd.row_1_msg("Sensores: " + line_sensors.sensorsToString(_sensors));
  lcd.row_2_msg("Linea: " + line_sensors.lineToString(_line));
});

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGINT', function () {
  process.exit();
});

process.on('SIGTERM', function () {
  process.exit();
});
