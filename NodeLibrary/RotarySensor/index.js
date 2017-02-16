var rSensor = require('bindings')('RotarySensor');
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function RotarySensor(_port,_add = 0){
  EventEmitter.call(this);
  var _self = this;
  this.scaleFactor =  1024/1700;

  this.rotary = new rSensor(_port,_add);

  process.on('SIGINT', function () {
    _self.rotary.release();
  });

  process.on('SIGTERM', function () {
    _self.rotary.release();
  });
}

RotarySensor.prototype.getValue = function(){
  return this.rotary.getValue();
};

RotarySensor.prototype.getBasicValue = function(){
  var value = Math.round(this.rotary.getValue() * 100)/100;
  return value;
};

RotarySensor.prototype.getScaledValue = function (){
  return this.rotary.getScaledValue();
};

RotarySensor.prototype.getBasicScaledValue = function (){
  return this.rotary.getBasicScaledValue();
};

RotarySensor.prototype.enableEvents = function () {
  var _self = this;
  var scaledValue;

  setInterval(()=>{
    scaledValue = this.rotary.getBasicScaledValue();
    _self.emit('Measurement',scaledValue);
  }, 100); // Tomar mediciones cada 100ms
}

RotarySensor.prototype.when = function(value, callback) {
  if (!this.interval) {
    setInterval(()=>{
      console.log('Rotatorio: ' + this.light.getBasicScaledValue());
      if (this.rotary.getBasicScaledValue() == value) {
        callback();
      }
    }, 250); // Tomar mediciones cada 250ms
  }
}

RotarySensor.prototype.release = function (){
  clearInterval(this.interval);
  this.rotary.release();
}

inherits(RotarySensor,EventEmitter);

module.exports = RotarySensor;
