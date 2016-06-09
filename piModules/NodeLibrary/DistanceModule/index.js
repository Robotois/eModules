var dModule = require('bindings')('DistanceModule')

var distModule = dModule(1);

// console.log("The current Temperature is: "+tempModule.Temperature());

setInterval(function () {
  console.log("The current Temperature is: "+distModule.Distance());
},500);
