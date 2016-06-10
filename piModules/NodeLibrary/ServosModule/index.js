var servosModule = require('bindings')('ServosModule')

var servos = servosModule();

servos.SetAngle(1,90);
