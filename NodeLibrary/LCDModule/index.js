var lcdModule = require('bindings')('LCDModule'),
    sleep = require('sleep');

function LCDModule(_add = 0){
  var _self = this;

  this.lcd = new lcdModule(_add);

  this.lcd.message('Welcome to\nRobotois :D');
  sleep.sleep(2);
  this.lcd.clear();

  process.on('SIGINT', function () {
    _self.lcd.release();
  });

  process.on('SIGTERM', function () {
    _self.lcd.release();
  });
}

LCDModule.prototype.message = function(_msg){
  this.lcd.message(_msg);
}

LCDModule.prototype.setCursor = function(row,col){
  this.lcd.setCursor(row,col);
}

LCDModule.prototype.clear = function(){
  this.lcd.clear();
}

LCDModule.prototype.home = function(){
  this.lcd.home();
}

LCDModule.prototype.bklBlink = function(){
  this.lcd.bklBlink();
}

LCDModule.prototype.setText = function(msg){
  this.lcd.message(msg);
}

module.exports = LCDModule;
