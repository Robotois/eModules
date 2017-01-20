var _rgbModule = require('bindings')('RGBModule');
var hexToRGB = function(hex){
    const hex = hex.replace('#','');
    const r = parseInt(hex.substring(0,2), 16);
    const g = parseInt(hex.substring(2,4), 16);
    const b = parseInt(hex.substring(4,6), 16);
    return [r,g,b];;
};

function RGBModule(_add){
  var _self = this;

  this.rgb = new _rgbModule(_add);

  process.on('SIGINT', function () {
    _self.rgb.release();
  });

  process.on('SIGTERM', function () {
    _self.rgb.release();
  });
};

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
  const led = ledNumber.replace('led', '') * 1;
  this.rgb.setRGB(led, rgbColor[0], rgbColor[1], rgbColor[2]);
};

module.exports = RGBModule;
