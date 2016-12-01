var lModule = require('bindings')('LightModule')

function LightModule(_port, _add = 0){
  var _self = this;

  this.light = new lModule(_port,_add);

  process.on('SIGINT', function () {
    _self.light.release();
  });

  process.on('SIGTERM', function () {
    _self.light.release();
  });
}

LightModule.prototype.light = function(){
  return this.light.light();
}

LightModule.prototype.scaledLight = function(){
  return this.light.scaledLight();
}

module.exports = LightModule;
// var lightModule = lModule(1);
//
// setInterval(function () {
//   console.log("Light measurement: " + lightModule.Light() + ", Scaled Light:" + lightModule.ScaledLight());
// },500);
