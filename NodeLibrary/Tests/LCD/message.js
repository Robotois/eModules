var _lcd = require('../../LCDModule'),
  lcd = new _lcd();

var count = 0

setInterval(()=>{
    // lcd.message("Hola, estoy\ncontando: " + count);
    lcd.message("Hola, estoy contando: " + count);
    count += 1;
},2000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
