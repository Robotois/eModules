var _loops = require('../../Loops'),
    loops = new _loops(),
    sleep = require('sleep');

var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _temp = require('../../TempModule'),
  temp = new _temp(2);

// var _rgb = require('../../RGBModule'),
//   rgb = new _rgb();

lcd.message('Welcome to\nRobotois :D');
sleep.sleep(3);
lcd.clear();

var value = temp.temperature();
lcd.message("Temp [C]: " + value.toFixed(2));

setInterval(()=>{
  value = temp.temperature();

  lcd.setCursor(1,11);
  lcd.message(value.toFixed(2));
},250);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
