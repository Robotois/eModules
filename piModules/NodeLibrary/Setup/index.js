var BCMSetup = require('bindings')('BCMConfig')

var bcm_obj = BCMSetup();
console.log("BCM Initialization: "+bcm_obj.BCMInit());

bcm_obj.BCMEnd();
