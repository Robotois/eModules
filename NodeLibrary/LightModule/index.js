var lModule = require('bindings')('LightModule')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function LightModule(_port, _add = 0){
  EventEmitter.call(this);
  var _self = this;
  
  this.light = new lModule(_port,_add);

  process.on('SIGINT', function () {
    _self.light.release();
  });

  process.on('SIGTERM', function () {
    _self.light.release();
  });
}

/**
  Devuelve el valor de la señal medida por el sensor, este valor va de 0-5, y tiene puntos decimales.
  La resolución es de 11 bits.
**/
LightModule.prototype.getValue = function(){
  return this.light.getValue();
}

LightModule.prototype.getBasicValue = function(){ // Rounded
  var value = Math.round(this.light.getValue() * 100)/100
  return value;
}

LightModule.prototype.getScaledValue = function(){
  return this.light.getScaledValue();
}

LightModule.prototype.getBasicScaledValue = function(){
  return this.light.getBasicScaledValue();
}

LightModule.prototype.enableEvents = function (){
  var _self = this;
  var scaledValue;

  setInterval(()=>{
    scaledValue = this.light.getBasicScaledValue();
    _self.emit('Measurement',scaledValue);
  }, 250); // Tomar mediciones cada 250ms
}

LightModule.prototype.when = function(value, callback){
  setInterval(()=>{
    console.log(this.light.getBasicScaledValue());
    if (this.light.getBasicScaledValue() == value) {
      callback();
    }
  }, 250); // Tomar mediciones cada 250ms
}

inherits(LightModule,EventEmitter);

module.exports = LightModule;
