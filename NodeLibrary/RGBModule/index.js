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

// - Implementar la funcion turnOn => ["Nombre del led", "color en hexa"]

RGBModule.prototype.setRGB = function(_ledNumber,_red,_green,_blue){
  this.rgb.setRGB(_ledNumber,_red,_green,_blue);
};

RGBModule.prototype.blinkRGB = function(_ledNumber,_red,_green,_blue){
  this.rgb.blinkRGB(_ledNumber,_red,_green,_blue);
};

RGBModule.prototype.ledOff = function(){
  this.rgb.ledOff();
}

RGBModule.prototype.turnOn = function (ledNumber, hexColor) {
  let rgbColor = hexToRGB(hexColor);
  this.rgb.setRGB(ledNumber.replace('led', ''), rgbColor[0], rgbColor[1], rgbColor[2]);
};

module.exports = RGBModule;
