const Rotatory = require('../../RotaryModule');
const Temperature = require('../../TempModule');
const Light = require('../../LightModule');

const rotatory = new Rotatory(1);
const temperature = new Temperature(2);
const light = new Light(3);

setInterval(function () {
  console.log('Valor de rotatorio: ' + rotatory.getValue());
  console.log('Valor de temperature: ' + temperature.getValue());
  console.log('Valor de luz: ' + light.getValue());
  console.log('====================================');
}, 1000);

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
