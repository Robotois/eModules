var tModule = require('bindings')('TempModule')

function TemperatureModule(_port, _add = 0){
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

module.exports = TemperatureModule;


// var tempModule = tModule(1);

// console.log("The current Temperature is: "+tempModule.Temperature());

// setInterval(function () {
//   console.log("The current Temperature is: "+tempModule.Temperature());
// },500);
