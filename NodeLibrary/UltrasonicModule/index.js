var uModule = require('bindings')('UltrasonicModule')

function UltrasonicModule(_header){
  var _self = this;

  this.ultrasonic = new uModule(_header);

  process.on('SIGINT', function () {
    _self.ultrasonic.release();
  });

  process.on('SIGTERM', function () {
    _self.ultrasonic.release();
  });
}

UltrasonicModule.prototype.distance = function (){
  return this.ultrasonic.distance();
}

module.exports = UltrasonicModule;

// var distModule = uModule(1);

// console.log("The current Temperature is: "+tempModule.Temperature());

// setInterval(function () {
//   console.log("The current Distance is: "+distModule.Distance());
// },500);
