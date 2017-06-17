var _loops = require('../../Loops'),
    loops = new _loops(),
    sleep = require('sleep');

// var _lcd = require('../../LCDModule'),
//   lcd = new _lcd();

var _rotaryModule = require('../../RotaryModule'),
  rotary = new _rotaryModule(1);

var _servosModule = require('../../ServosModule'),
  servosModule = new _servosModule();

var angleRatio = 180/1024, value = 0, angle = 0;

value = rotary.scaledValue();
angle = (value - 512) * angleRatio;

// lcd.clear();
// lcd.message("Value: " + ('    ' + value).slice(-4) +
//   "\nAngle: " + ("     " + angle.toFixed(2)).slice(-5));

setInterval(function (){
  value = rotary.scaledValue();
  angle = (value - 512) * angleRatio;
  servosModule.setAngle(1,angle);
  // lcd.setCursor(1,7);
  // lcd.message(("    "+ value).slice(-4));
  // lcd.setCursor(2,7);
  // lcd.message(("     " + angle.toFixed(2)).slice(-5));
  // console.log('Value: ' + value + ', Angle: ' + angle);
},1);
