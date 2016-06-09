var setup = require('./Setup/build/Release/Setup.node')
var TempModule = require('./TempModule/build/Release/TempModule')

console.log(setup.bcm_init());

var tempModule = TempModule(1);
console.log("The current Temperature is: "+tempModule.temperature());

setup.bcm_end();
