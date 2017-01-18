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

UltrasonicModule.prototype.when = function(value, callback){
  setInterval(()=>{ // Tomar mediciones cada 200ms
    console.log(this.ultrasonic.distance());
    if (this.ultrasonic.distance() === value) {
      callback();
    }
  }, 400)
}

module.exports = UltrasonicModule;
