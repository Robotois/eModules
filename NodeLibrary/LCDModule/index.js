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
  this.interval = setInterval(()=>{ // Proceso en estado ocioso
    this.lcd.bklBlink();
  }, 300);
}

LCDModule.prototype.setText = function(msg) {
  this.lcd.clear();
  this.lcd.home();
  this.lcd.message(msg);
}

LCDModule.prototype.reset = function(msg) {
  if (this.interval) {
    clearInterval(this.interval);
  }
  this.lcd.clear();
}

module.exports = LCDModule;
