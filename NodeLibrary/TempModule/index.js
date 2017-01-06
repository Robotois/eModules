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
  return this.temp.temperature();
}

TemperatureModule.prototype.enableEvents = function () {
  var _self = this;
  var value;

  setInterval(()=>{ // Tomar mediciones cada 1s
    value = Math.round(_self.temp.temperature() * 100)/100;
    _self.emit('Measurement',value);
  },200)
}

TemperatureModule.prototype.when = function(value, callback){
  setInterval(()=>{ // Tomar mediciones cada 200ms
    console.log(this.temp.temperature());
    if (this.temp.temperature() === value) {
      callback();
    }
  }, 100)
}

inherits(TemperatureModule,EventEmitter);

module.exports = TemperatureModule;
