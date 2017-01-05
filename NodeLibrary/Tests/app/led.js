const LED  =  require('../../LEDModule');
const led = new LED(2);
const led2 = new LED(3);
let interval;

led.turnOn();
led2.blink();
// we blink led each second
interval = setInterval(function () {
  led2.blink();
}, 1000);

setTimeout(function () {
  led.turnOff();
  clearInterval(interval);
}, 7000);

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
