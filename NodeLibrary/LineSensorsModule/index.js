var LineSensors = require('bindings')('LineSensorsModule')
module.exports = LineSensors;
// var lineSensors = LineSensors();
//
// setInterval(function () {
//   console.log("Sensors: "+lineSensors.ReadSensors() + ", Sensor 1: " + lineSensors.ReadSensor(1) + ", Line: " + lineSensors.ReadLine());
// },500);
