var tModule = require('bindings')('TempModule')

var tempModule = tModule(1);

// console.log("The current Temperature is: "+tempModule.Temperature());

setInterval(function () {
  console.log("The current Temperature is: "+tempModule.Temperature());
},500);
