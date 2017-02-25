var tSensor = require('bindings')('TemperatureSensor')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function TemperatureSensor(_port, _add = 0){
  EventEmitter.call(this);
  var _self = this;

  this.temp = new tSensor(_port, _add);

  process.on('SIGINT', function () {
    _self.temp.release();
  });

  process.on('SIGTERM', function () {
    _self.temp.release();
  });
}

TemperatureSensor.prototype.getValue = function(){
  return this.temp.getValue();
}

TemperatureSensor.prototype.getBasicValue = function(){
  var value = Math.round(this.temp.getValue() * 100)/100;
  return value;
}

TemperatureSensor.prototype.getIntValue = function(){
  return this.temp.getIntValue();
}

TemperatureSensor.prototype.enableEvents = function () {
  var _self = this;
  var value;

  setInterval(()=>{
    value = this.getBasicValue();
    _self.emit('Measurement',value);
  }, 200); // Tomar mediciones cada 200 ms
}

TemperatureSensor.prototype.when = function(value, callback){
  if (!this.interval) {
    this.interval = setInterval(()=>{ // Tomar mediciones cada 200ms
      console.log('Temperatura: ' + this.temp.getIntValue());
      if (this.temp.getIntValue() == value) {
        callback();
      }
    }, 400); // Tomar mediciones cada 400ms
  }
}

TemperatureSensor.prototype.release = function() {
  clearInterval(this.interval);
  this.temp.release();
}

inherits(TemperatureSensor,EventEmitter);

module.exports = TemperatureSensor;
