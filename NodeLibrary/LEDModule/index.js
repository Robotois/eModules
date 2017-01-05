var ledModule = require('bindings')('LEDModule');
var sleep = require('sleep');

function LEDModule(header){
  var _self = this;
  this.led = new ledModule(header);

  process.on('SIGINT', function () {
    _self.led.release();
    process.exit();
  });

  process.on('SIGTERM', function () {
    _self.led.release();
    process.exit();
  });
}

LEDModule.prototype.write = function (ledValue) {
  this.led.write(ledValue);
};

LEDModule.prototype.led_blink = function () {
  this.led.write(1);
  sleep.usleep(300000);
  this.led.write(0);
};

module.exports = LEDModule;