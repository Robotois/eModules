var _loops = require('../../Loops'),
    loops = new _loops(),
    sleep = require('sleep');

var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _rotary = require('../../RotaryModule'),
  rotary = new _rotary(1);

var _rgb = require('../../RGBModule'),
  rgb = new _rgb();

lcd.message('Welcome to\nRobotois :D');
sleep.sleep(3);
lcd.clear();

var value = rotary.value();
lcd.message("Value: " + value.toFixed(2));
rgb.setRGB(1,0, 0, 0);
rgb.setRGB(2,0,0,0);
rgb.setRGB(3,0, 0, 0);
rgb.setRGB(4,0, 0, 0);

setInterval(()=>{
  value = rotary.value();

  lcd.setCursor(1,8);
  lcd.message(value.toFixed(2));

  if(value > 0.5 && value < 2){
    rgb.setRGB(1,51, 204, 51);
    rgb.setRGB(2,0,0,0);
    rgb.setRGB(3,0, 0, 0);
    rgb.setRGB(4,0, 0, 0);
  }
  if(value > 2 && value < 3){
    rgb.setRGB(2,255, 153, 51);
    rgb.setRGB(3,0,0,0);
    rgb.setRGB(4,0, 0, 0);
  }
  if(value > 3 && value < 4){
    rgb.setRGB(3,128, 0, 0);
    rgb.setRGB(4,0, 0, 0);
    lcd.bklBlink();
  }
  if(value > 4 ){
    rgb.setRGB(4,255, 0, 0);
    lcd.bklBlink();
  }
},10);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
