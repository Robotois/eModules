var lcdModule = require('bindings')('LCDModule');
var sleep = require('sleep');

function LCDModule(_add = 0) {
  var self = this;
  this.lcd = new lcdModule(_add);

  process.on('SIGINT', function () {
    self.lcd.release();
  });

  process.on('SIGTERM', function () {
    self.lcd.release();
  });
}

LCDModule.prototype.message = function(_msg) {
  this.lcd.message(_msg);
}

LCDModule.prototype.setCursor = function(row,col) {
  this.lcd.setCursor(row,col);
}

LCDModule.prototype.clear = function() {
  this.lcd.clear();
}

LCDModule.prototype.home = function() {
  this.lcd.home();
}

LCDModule.prototype.blink = function() {
  var interval = setInterval(()=>{
    this.lcd.bklBlink();
  }, 300);

  setTimeout(() => {
    clearInterval(interval);
  }, 2000);
}

LCDModule.prototype.setText = function(msg) {
  this.reset();
  this.message(msg);
}

LCDModule.prototype.reset = function(msg) {
  this.clear();
  this.home();
}

module.exports = LCDModule;
