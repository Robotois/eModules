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
  return this.button.read();;
};

ButtonModule.prototype.enableEvents = function () {
  var _self = this;
  var prevState = 0,currentState;

  setInterval(()=>{
    currentState = _self.button.read();
    if(currentState !== prevState){
      _self.emit('ButtonChange',currentState);
      prevState = currentState;
    }
  },50);
}

ButtonModule.prototype.when = function(value, callback){
  const self = this;
  var currentState = 0;
  setInterval(()=>{
    currentState = self.button.read();
    if(value == currentState){
      callback();
    }
  }, 50);
}

inherits(ButtonModule,EventEmitter);

module.exports = ButtonModule;
