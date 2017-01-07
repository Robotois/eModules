var lModule = require('bindings')('LightModule')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function LightModule(_port, _add = 0){
  EventEmitter.call(this);
  var _self = this;
  this.scaleFactor =  1024/1700;

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

LightModule.prototype.getValue = function(){
  return this.light.scaledLight();
}

LightModule.prototype.enableEvents = function (){
  var _self = this;
  var value, scaledValue;

  setInterval(()=>{ // Tomar mediciones cada 200ms
    value = Math.round(this.light.light() * 100)/100;
    scaledValue = Math.round(this.scaleFactor * value);
    _self.emit('Measurement',value,scaledValue);
  }, 200)
}
LightModule.prototype.when = function(value, callback){
  setInterval(()=>{ // Tomar mediciones cada 200ms
    console.log(this.light.scaledLight());
    if (this.light.scaledLight() == value) {
      callback();
    }
  }, 100)
}

inherits(LightModule,EventEmitter);

module.exports = LightModule;
