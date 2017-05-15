var _loops = require('../../Loops'),
    loops = new _loops(),
    sleep = require('sleep'),
    _line_sensors = require('../../LineSensorsModule'),
    line_sensors = new _line_sensors();

var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _leds  =  require('../../LEDModule'),
  led1 = new _leds(5),
  led2 = new _leds(6);

/** Hexadecimal/Binary value for sensors status **/
// setInterval(()=>{
//   console.log("Sensors[hex]: " + line_sensors.readSensors().toString(16) +
//   ", Sensors[dec]: " + line_sensors.readLine() +
//   ", Sensors[bin]: " + ("000000" + line_sensors.readSensors().toString(2)).slice(-6) );
// },1000);

// /** Single Sensor Status **/
// setInterval(()=>{
//   console.log("Sensor[2]: " + line_sensors.ReadSensor(2));
// },1000);

/** Hexadecimal/Binary value for sensors status **/
// setInterval(()=>{
//   console.log("Sensors[hex]: " + line_sensors.ReadSensors().toString(16) +
//   ", Sensors[dec]: " + line_sensors.ReadLine() +
//   ", Sensors[bin]: " + ("000000" + line_sensors.ReadSensors().toString(2)).slice(-6) );
// },1000);

/** LCD Display for Sensors status **/
var currentValue = line_sensors.readSensors(),
  prevValue = currentValue;
var currentLine = line_sensors.readLine(),
  prevLine = currentLine;

lcd.message("Sensors: " + ("000000" + line_sensors.readSensors().toString(2)).slice(-6) +
  "\nLine: " + ("    " + (currentLine.toFixed(2)-200).toString()).slice(-4));

setInterval(()=>{
  currentValue = line_sensors.readSensors();
  currentLine = line_sensors.readLine();
  console.log("Line: " + currentLine);
  if(currentValue != prevValue){
    lcd.setCursor(1,10);
    lcd.message(("000000" + line_sensors.readSensors().toString(2)).slice(-6));
    prevValue = currentValue;
  }
  if(currentLine != prevLine){
    lcd.setCursor(2,7);
    lcd.message(('      ' + (currentLine.toFixed(2)-200)).slice(-4));
    prevLine = currentLine;
  }
},500);

// var currentLine = line_sensors.readLine(),
//   prevLine = currentLine;
//
// setInterval(()=>{
//   currentLine = line_sensors.readLine() - 200;
//   if(currentLine == 0){
//     led1.write(1);
//     led2.write(1);
//   }
//   if(currentLine < 0){
//     led1.write(1);
//     led2.write(0);
//   }
//   if(currentLine > 0){
//     led1.write(0);
//     led2.write(1);
//   }
// },100);

process.on('SIGINT', function () {
  // leds.unexport();
  // buttons.unexport();
  process.exit();
});

process.on('SIGTERM', function () {
  // leds.unexport();
  // buttons.unexport();
  process.exit();
});
