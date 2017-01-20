var _rgbModule = require('bindings')('RGBModule');

function hexToR(h) { return parseInt((cutHex(h)).substring(0,2), 16); }
function hexToG(h) { return parseInt((cutHex(h)).substring(2,4), 16); }
function hexToB(h) { return parseInt((cutHex(h)).substring(4,6), 16); }
function cutHex(h) { return (h.charAt(0)=="#") ? h.substring(1,7) : h; }

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
  const led = ledNumber.replace('led', '') * 1;
  this.rgb.setRGB(led, hexToR(hexColor), hexToG(hexColor), hexToB(hexColor));
};

module.exports = RGBModule;
