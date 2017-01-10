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

RotaryModule.prototype.value = function(){
  return this.rotary.value();
};

RotaryModule.prototype.scaledValue = function (){
  return this.rotary.scaledValue();
};

RotaryModule.prototype.getValue = function(){
  return this.rotary.value();
}

RotaryModule.prototype.enableEvents = function () {
  var _self = this;
  var value, scaledValue;

  setInterval(()=>{ // Tomar mediciones cada 200ms
    value = Math.round(this.rotary.value() * 100)/100;
    scaledValue = Math.round(this.scaleFactor * value);
    _self.emit('Measurement',value,scaledValue);
  },200)
}

RotaryModule.prototype.when = function(value, callback) {
  var value, scaledValue;
  setInterval(()=>{ // Tomar mediciones cada 200ms
    value = Math.round(this.rotary.value() * 100)/100;
    scaledValue = Math.round(this.scaleFactor * value);
    console.log(scaledValue);
    if (scaledValue == value) {
      callback();
    }
  }, 400)
}

inherits(RotaryModule,EventEmitter);

module.exports = RotaryModule;
