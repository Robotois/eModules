var _line_sensors = require('../../LineSensorsModule'),
    line_sensors = new _line_sensors();
// line_sensors.setBackground("black");
line_sensors.enableEvents();

// setInterval(() => {
//   console.log("Sensores: " + line_sensors.readSensors());
//   console.log("Linea: " + line_sensors.readLine());
// },1000);

line_sensors.on('change',(_line,_sensors)=>{
  console.log("Linea: " + _line);
  console.log("Sensores: " + line_sensors.sensorsToString(_sensors));
});

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGINT', function () {
  process.exit();
});

process.on('SIGTERM', function () {
  process.exit();
});
