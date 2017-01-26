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

RotaryModule.prototype.basicScaledValue = function (){
  return this.rotary.basicScaledValue();
};

// RotaryModule.prototype.getValue = function(){
//   return this.rotary.value();
// }

RotaryModule.prototype.enableEvents = function () {
  var _self = this;
  var scaledValue;

  setInterval(()=>{ // Tomar mediciones cada 200ms
    // value = Math.round(this.rotary.value() * 100)/100;
    // scaledValue = Math.round(this.scaleFactor * value);
    scaledValue = this.rotary.basicScaledValue();
    _self.emit('Measurement',scaledValue);
  },100)
}

RotaryModule.prototype.when = function(value, callback) {
  // var scaledValue;
  setInterval(()=>{ // Tomar mediciones cada 200ms
    // scaledValue = Math.round(this.rotary.value() * 100)/100;
    // console.log(scaledValue);
    // basicScaledValue = this.rotary.basicScaledValue();
    if (this.rotary.basicScaledValue() == value) {
      callback();
    }
  }, 400)
}

inherits(RotaryModule,EventEmitter);

module.exports = RotaryModule;
