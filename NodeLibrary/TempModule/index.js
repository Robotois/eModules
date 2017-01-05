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

TemperatureModule.prototype.enableEvents = function () {
  var _self = this;
  var value;

  setInterval(()=>{ // Tomar mediciones cada 1s
    value = Math.round(_self.temp.temperature() * 100)/100;
    // if(currentValue !== prevValue){ // Se emiten mediciones cuando el valor actual es diferente al previo
    _self.emit('Measurement',value);
        // prevValue = currentValue;
    // }
  },1000)
}

TemperatureModule.prototype.when = function(temp,callback){
  if()
}

inherits(TemperatureModule,EventEmitter);

module.exports = TemperatureModule;


// var tempModule = tModule(1);

// console.log("The current Temperature is: "+tempModule.Temperature());

// setInterval(function () {
//   console.log("The current Temperature is: "+tempModule.Temperature());
// },500);
