var uModule = require('bindings')('UltrasonicModule')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function UltrasonicModule(_header){
  var _self = this;
  EventEmitter.call(this);

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

UltrasonicModule.prototype.enableEvents = function(){
  var dist;

  setInterval(()=>{ // Mediciones cada 100ms
    dist = this.distance();
    this.emit('Measurement',dist);
  },100);
}

UltrasonicModule.prototype.distToString = function(_dist){
  return ("     " + _dist.toFixed(1).toString()).slice(-5);
};

inherits(UltrasonicModule,EventEmitter);

UltrasonicModule.prototype.when = function(value, callback){
  setInterval(()=>{ // Tomar mediciones cada 200ms
    console.log(this.ultrasonic.distance());
    if (this.ultrasonic.distance() === value) {
      callback();
    }
  }, 400)
}

module.exports = UltrasonicModule;
