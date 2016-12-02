var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var _temp = require('../../TempModule'),
  temp = new _temp(2);
temp.enableEvents();

temp.on('Measurement',(_value)=>{
  lcd.home();
  lcd.message("Temp [C]: " + _value.toFixed(2));
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
