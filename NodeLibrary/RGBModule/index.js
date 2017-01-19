var _rgbModule = require('bindings')('RGBModule');
var hexToRGB = function(hex){
  var r = hex >> 16;
  var g = hex >> 8 & 0xFF;
  var b = hex & 0xFF;
  return [r,g,b];
}
function RGBModule(_add){
  var _self = this;

  this.rgb = new _rgbModule(_add);

  process.on('SIGINT', function () {
    _self.rgb.release();
  });

  process.on('SIGTERM', function () {
    _self.rgb.release();
  });
}

RGBModule.prototype.setRGB = function(_ledNumber,_red,_green,_blue){
  this.rgb.setRGB(_ledNumber,_red,_green,_blue);
};

RGBModule.prototype.blinkRGB = function(_ledNumber,_red,_green,_blue){
  this.rgb.blinkRGB(_ledNumber,_red,_green,_blue);
};

RGBModule.prototype.ledOff = function(){
  this.rgb.ledOff();
}

LEDModule.prototype.turnOn = function (_ledNumber, hexColor) {
  let rgbColor = hexToRGB(color)
  this.rgb.setRGB(_ledNumber, rgbColor[0], rgbColor[1], rgbColor[2]);
};
module.exports = RGBModule;


// var sleep = require('sleep');
//
// var rgbs = rgbModule();
//
// setInterval(function(){
//   rgbs.BlinkRGB(1,128,0,128); // Purple
//   // sleep.sleep(1);
//   // rgbs.ledOff(1); // Purple
// },5000);

// setInterval(function(){
//   rgbs.BlinkRGB(2,128,0,128); // Purple
// },5000);
//
// setInterval(function(){
//   rgbs.BlinkRGB(3,128,0,128); // Purple
// },3000);
//
// rgbs.SetRGB(1,128,0,128); // Purple
// rgbs.SetRGB(2,0,0,0); // dark turquoise
// rgbs.SetRGB(3,0,0,0); // Olive
//
// sleep.sleep(1);
// rgbs.ledOff(1);
// sleep.sleep(1);
// rgbs.SetRGB(1,128,0,128); // Purple
//
// sleep.sleep(1);
// rgbs.ledOff(1);
// sleep.sleep(1);
// rgbs.SetRGB(1,128,0,128); // Purple
//
// sleep.sleep(1);
// rgbs.ledOff(1);
// sleep.sleep(1);
// rgbs.SetRGB(1,128,0,128); // Purple
//
// sleep.sleep(1);
// rgbs.ledOff(1);
// sleep.sleep(1);
// rgbs.SetRGB(1,128,0,128); // Purple
//
// sleep.sleep(1);
// rgbs.ledOff(1);
// sleep.sleep(1);
// rgbs.SetRGB(1,128,0,128); // Purple

// var rgbModule = require('bindings')('RGBModule')
// module.exports = new rgbModule();
