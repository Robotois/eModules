var _loops = require('../../Loops'),
    loops = new _loops(),
    sleep = require('sleep');

var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _light = require('../../LightModule'),
  light = new _light(3);

lcd.message('Welcome to\nRobotois :D');
sleep.sleep(3);
lcd.clear();

var value = light.scaledLight();
lcd.message("Light: " + value);

setInterval(()=>{
  value = light.scaledLight();

  lcd.setCursor(1,7);
  lcd.message(("    " + value).slice(-4));
},250);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
