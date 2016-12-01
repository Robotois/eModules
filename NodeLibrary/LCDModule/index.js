var lcdModule = require('bindings')('LCDModule');
function LCDModule(_add = 0){
  var _self = this;

  this.lcd = new lcdModule(_add);

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

module.exports = LCDModule;
//
// var lcd = lcdModule();
//
// // console.log("The current Temperature is: "+tempModule.Temperature());
//
// console.log("Sending message: "+lcd.Message("Welcome to \nRobotois :D"));
