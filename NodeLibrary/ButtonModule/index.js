var buttonModule = require('bindings')('ButtonModule');
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function ButtonModule(header){
  EventEmitter.call(this);
  var _self = this;
  this.button = new buttonModule(header);

  process.on('SIGINT', function () {
    _self.button.release();
    process.exit();
  });

  process.on('SIGTERM', function () {
    _self.button.release();
    process.exit();
  });
}

ButtonModule.prototype.read = function () {
  var value = this.button.read();
  return value;
};

ButtonModule.prototype.enableEvents = function () {
  var _self = this;
  var prevState = 0;

  function run(_prevState){
    var currentState = _self.button.read();
    if(currentState !== _prevState){
      // console.log(currentState);
      _self.emit('ButtonChange',currentState);
    }

    setImmediate(run,currentState);
  }

  run(prevState);
}

inherits(ButtonModule,EventEmitter);

module.exports = ButtonModule;
