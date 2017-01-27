var rModule = require('bindings')('RotaryModule');
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function RotaryModule(_port,_add = 0){
  EventEmitter.call(this);
  var _self = this;
  this.scaleFactor =  1024/1700;

  this.rotary = new rModule(_port,_add);

  process.on('SIGINT', function () {
    _self.rotary.release();
  });

  process.on('SIGTERM', function () {
    _self.rotary.release();
  });
}

RotaryModule.prototype.getValue = function(){
  return this.rotary.getValue();
};

RotaryModule.prototype.getBasicValue = function(){
  var value = Math.round(this.rotary.getValue() * 100)/100;
  return value;
};

RotaryModule.prototype.getScaledValue = function (){
  return this.rotary.getScaledValue();
};

RotaryModule.prototype.getBasicScaledValue = function (){
  return this.rotary.getBasicScaledValue();
};

RotaryModule.prototype.enableEvents = function () {
  var _self = this;
  var scaledValue;

  setInterval(()=>{
    scaledValue = this.rotary.getBasicScaledValue();
    _self.emit('Measurement',scaledValue);
  }, 100); // Tomar mediciones cada 100ms
}

RotaryModule.prototype.when = function(value, callback) {
  setInterval(()=>{
    console.log(this.rotary.getBasicScaledValue());
    if (this.rotary.getBasicScaledValue() == value) {
      callback();
    }
  }, 250); // Tomar mediciones cada 250ms

}

inherits(RotaryModule,EventEmitter);

module.exports = RotaryModule;
