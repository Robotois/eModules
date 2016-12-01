var _loops = require('../../Loops'),
    loops = new _loops(),
    sleep = require('sleep');

var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _ultrasonic = require('../../UltrasonicModule'),
  ultrasonic = new _ultrasonic(5);

lcd.message('Welcome to\nRobotois :D');
sleep.sleep(3);
lcd.clear();

var value = ultrasonic.distance();
lcd.message("Dist [cm]: " + value.toFixed(2));

setInterval(()=>{
  value = ultrasonic.distance();
  console.log(("     " + value.toFixed(1)).slice(-5));
  lcd.setCursor(1,12);
  lcd.message(("     " + value.toFixed(1)).slice(-5));
},250);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
