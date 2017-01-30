var uSensor = require('bindings')('UltrasonicSensor')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function UltrasonicSensor(_header){
  var _self = this;
  EventEmitter.call(this);

  this.ultrasonic = new uSensor(_header);

  process.on('SIGINT', function () {
    _self.ultrasonic.release();
  });

  process.on('SIGTERM', function () {
    _self.ultrasonic.release();
  });
}

UltrasonicSensor.prototype.getValue = function (){
  return this.ultrasonic.getValue();
}

UltrasonicSensor.prototype.getBasicValue = function (){
  return this.ultrasonic.getBasicValue();
}

UltrasonicSensor.prototype.enableEvents = function(){
  var dist;

  setInterval(()=>{ // Mediciones cada 100ms
    dist = this.getBasicValue();
    this.emit('Measurement',dist);
  },100);
}

UltrasonicSensor.prototype.distToString = function(_dist){
  return ("     " + _dist.toFixed(1).toString()).slice(-5);
};

inherits(UltrasonicSensor,EventEmitter);

UltrasonicSensor.prototype.when = function(value, callback){
  if (!this.interval) {
    setInterval(()=>{ // Tomar mediciones cada 200ms
      console.log(this.ultrasonic.getBasicValue());
      if (this.ultrasonic.getBasicValue() === value) {
        callback();
      }
    }, 500);
  }
}

UltrasonicSensor.prototype.release = function (){
  clearInterval(this.interval);
  this.ultrasonic.release();
}

module.exports = UltrasonicSensor;
