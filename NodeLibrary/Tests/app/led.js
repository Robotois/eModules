const LED  =  require('../../LEDModule');
const led = new LED(2);
// const led2 = new LED(3);

led.turnOff();
// led2.blink();

/*setTimeout(function () {
  led.turnOff();
  led2.turnOff();
}, 20000);*/

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
