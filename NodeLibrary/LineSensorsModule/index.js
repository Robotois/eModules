var _lineSensors = require('bindings')('LineSensorsModule')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function LineSensorsModule(_add = 0){
  EventEmitter.call(this);
  var _self = this;

  this.line = new _lineSensors(_add);

  process.on('SIGINT', function () {
    _self.line.release();
  });

  process.on('SIGTERM', function () {
    _self.line.release();
  });
}

LineSensorsModule.prototype.readSensors = function(){
  return this.line.readSensors();
}

LineSensorsModule.prototype.readSensor = function(_sensor){
  return this.line.readSensor(_sensor);
}

LineSensorsModule.prototype.readLine = function(){
  return this.line.readLine();
}

LineSensorsModule.prototype.setBackground = function(_str){
  this.line.setBackground(_str);
}

LineSensorsModule.prototype.enableEvents = function(){
  var sensors, line;// cumSum = 0,avg = 0.0,i = 0;

  setInterval(()=>{ // Medicionies cada 100ms
    sensors = this.readSensors();
    line = this.readLine();
    this.emit('Measurement', sensors,line);
  },100);
}

LineSensorsModule.prototype.sensorsToString = function(_sensors){
  return ("00000" + _sensors.toString(2)).slice(-5);
};

LineSensorsModule.prototype.lineToString = function(_line){
  return ("     " + _line.toFixed(1).toString()).slice(-5);
};

inherits(LineSensorsModule,EventEmitter);

module.exports = LineSensorsModule;
// var lineSensors = LineSensors();
//
// setInterval(function () {
//   console.log("Sensors: "+lineSensors.ReadSensors() + ", Sensor 1: " + lineSensors.ReadSensor(1) + ", Line: " + lineSensors.ReadLine());
// },500);
