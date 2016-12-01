var rModule = require('bindings')('RotaryModule');

function RotaryModule(_port,_add = 0){
  var _self = this;
  // console.log(_port, _add);
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

module.exports = RotaryModule;
// var rModule = require('bindings')('RotaryModule');
// var rotaryModule = rModule(1);
//
// // console.log("The current Temperature is: "+tempModule.Temperature());
//
// setInterval(function () {
//   console.log("Rotary measurement: " + rotaryModule.Value() + ", Scaled Rotary:" + rotaryModule.ScaledValue());
// },500);
