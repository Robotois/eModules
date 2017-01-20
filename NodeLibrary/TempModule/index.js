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

TemperatureModule.prototype.temperature = function (){
  return this.temp.temperature();
}

TemperatureModule.prototype.getValue = function(){
  return Math.round(this.temp.temperature() * 100)/100;
}

TemperatureModule.prototype.enableEvents = function () {
  var _self = this;
  var value;

  setInterval(()=>{ // Tomar mediciones cada 1s
    value = Math.round(_self.temp.temperature() * 100)/100;
    _self.emit('Measurement',value);
  }, 1000)
}

TemperatureModule.prototype.when = function(value, callback){
  setInterval(()=>{ // Tomar mediciones cada 200ms
    console.log(Math.round(this.temp.temperature() * 100)/100);
    if ((Math.round(this.temp.temperature() * 100)/100) == value) {
      callback();
    }
  }, 400)
}

inherits(TemperatureModule,EventEmitter);

module.exports = TemperatureModule;
