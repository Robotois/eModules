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
  this.lcd.home();
  this.lcd.message(_msg);
}

LCDModule.prototype.row_1_msg = function(_msg){
  this.message(_msg);
};

LCDModule.prototype.row_2_msg = function(_msg){
  this.lcd.setCursor(2,1); // Posicionarse en el renglon 2 y columna 1
  this.lcd.message(_msg);
};

LCDModule.prototype.setCursor = function(row,col){
  this.lcd.setCursor(row,col);
}

LCDModule.prototype.clear = function(){
  this.lcd.clear();
}

LCDModule.prototype.home = function(){
  this.lcd.home();
}

LCDModule.prototype.blink = function(){
  this.lcd.bklBlink();
}

module.exports = LCDModule;
//
// var lcd = lcdModule();
//
// // console.log("The current Temperature is: "+tempModule.Temperature());
//
// console.log("Sending message: "+lcd.Message("Welcome to \nRobotois :D"));
