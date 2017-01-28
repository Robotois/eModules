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

// RotarySensor.prototype.getValue = function(){
//   return this.rotary.value();
// }

RotarySensor.prototype.enableEvents = function () {
  var _self = this;
  var scaledValue;

  setInterval(()=>{ // Tomar mediciones cada 200ms
    // value = Math.round(this.rotary.value() * 100)/100;
    // scaledValue = Math.round(this.scaleFactor * value);
    scaledValue = this.rotary.getBasicScaledValue();
    _self.emit('Measurement',scaledValue);
  },100)
}

RotarySensor.prototype.when = function(value, callback) {
  // var scaledValue;
  setInterval(()=>{ // Tomar mediciones cada 200ms
    // scaledValue = Math.round(this.rotary.value() * 100)/100;
    // console.log(scaledValue);
    // basicScaledValue = this.rotary.basicScaledValue();
    if (this.rotary.getBasicScaledValue() == value) {
      callback();
    }
  }, 250)
}

RotarySensor.prototype.release = function (){
  this.rotary.release();
}

inherits(RotarySensor,EventEmitter);

module.exports = RotarySensor;
