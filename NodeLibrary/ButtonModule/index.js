var buttonModule = require('bindings')('ButtonModule');
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function ButtonModule(header){
  EventEmitter.call(this);
  var _self = this;
  this.button = new buttonModule(header);

  process.on('SIGINT', function () {
    _self.button.release();
    // process.exit();
  });

  process.on('SIGTERM', function () {
    _self.button.release();
    // process.exit();
  });
}

ButtonModule.prototype.getValue = function () {
  return this.button.getValue();
};

ButtonModule.prototype.enableEvents = function () {
  var _self = this;
  var prevState = 0,currentState;

  setInterval(()=>{
    currentState = _self.button.getValue();
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
    console.log('Botón: ' + state);
    if (state) {
      callback();
    }
  });
}

ButtonModule.prototype.release = function () {
    this.button.release();
}

inherits(ButtonModule,EventEmitter);

module.exports = ButtonModule;
