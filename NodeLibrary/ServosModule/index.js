var servosModule = require('bindings')('ServosModule')
var sleep = require('sleep');

var servos = servosModule();

servos.SetAngle(1,0);
sleep.sleep(3);
servos.SetAngle(1,45);
sleep.sleep(3);
servos.SetAngle(1,90);
sleep.sleep(3);
servos.SetAngle(1,45);
sleep.sleep(3);
servos.SetAngle(1,0);
sleep.sleep(3);
servos.SetAngle(1,-45);
sleep.sleep(3);
servos.SetAngle(1,-90);
sleep.sleep(3);
