const Light = require('../../LightModule');
const Led  =  require('../../LEDModule');

const light = new Light(3);
const led = new LED(5);

light.when('medir', 30, function () {
    led.blink();
});

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
