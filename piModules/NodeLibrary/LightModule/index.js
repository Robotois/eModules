var lModule = require('bindings')('LightModule')

var lightModule = lModule(1);

setInterval(function () {
  console.log("Light measurement: " + lightModule.Light() + ", Scaled Light:" + lightModule.ScaledLight());
},500);
