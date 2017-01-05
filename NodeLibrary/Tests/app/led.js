const LED  =  require('../../LEDModule'),
  led = new LED(2);

led.write(1);

setInterval(()=>{ // Proceso en estado ocioso
  true;
},10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
