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
  return this.button.read();
};

ButtonModule.prototype.enableEvents = function () {
  var _self = this;
  var prevState = 0,currentState;

  setInterval(()=>{
    currentState = _self.button.read();
    if(currentState !== prevState){
      _self.emit('change', currentState);
      prevState = currentState;
    }
  }, 50); // Tomar mediciones cada 50ms
}

ButtonModule.prototype.when = function(callback){
  const self = this;
  self.enableEvents();
  self.on('change', (state) => {
    if (state) {
      callback();
    }
  });
}

inherits(ButtonModule,EventEmitter);

module.exports = ButtonModule;
