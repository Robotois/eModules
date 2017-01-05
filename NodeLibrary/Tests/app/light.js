const LIGHT = require('../../LightModule');
const light = new LIGHT(2);

let value = light.scaledLight();
console.log(value);

setInterval(()=>{
  value = light.scaledLight();
  console.log(value);
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
