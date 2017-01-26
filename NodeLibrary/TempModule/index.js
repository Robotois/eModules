var tModule = require('bindings')('TempModule')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function TemperatureModule(_port, _add = 0){
  EventEmitter.call(this);
  var _self = this;

  this.temp = new tModule(_port, _add);

  process.on('SIGINT', function () {
    _self.temp.release();
  });

  process.on('SIGTERM', function () {
    _self.temp.release();
  });
}

TemperatureModule.prototype.getValue = function(){
  return this.temp.getValue();
}

TemperatureModule.prototype.getBasicValue = function(){
  var value = Math.round(this.temp.getValue() * 100)/100;
  return value;
}

TemperatureModule.prototype.getIntValue = function(){
  return this.temp.getIntValue();
}

TemperatureModule.prototype.enableEvents = function () {
  var _self = this;
  var value;

  setInterval(()=>{ // Tomar mediciones cada 1s
    // value = Math.round(_self.temp.temperature() * 100)/100;
    value = this.getBasicValue();
    _self.emit('Measurement',value);
  }, 200)
}

TemperatureModule.prototype.when = function(value, callback){
  setInterval(()=>{ // Tomar mediciones cada 200ms
    // console.log(Math.round(this.temp.temperature() * 100)/100);
    if (this.temp.getIntValue() == value) {
      callback();
    }
  }, 400)
}

inherits(TemperatureModule,EventEmitter);

module.exports = TemperatureModule;
