var _lineSensors = require('bindings')('LineSensorsModule')

function LineSensorsModule(_add = 0){
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
  return this.line.setBackground(_str);
}

module.exports = LineSensorsModule;
// var lineSensors = LineSensors();
//
// setInterval(function () {
//   console.log("Sensors: "+lineSensors.ReadSensors() + ", Sensor 1: " + lineSensors.ReadSensor(1) + ", Line: " + lineSensors.ReadLine());
// },500);
