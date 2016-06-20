var lcdModule = require('bindings')('LCDModule')

var lcd = lcdModule();

// console.log("The current Temperature is: "+tempModule.Temperature());

console.log("Sending message: "+lcd.Message("Welcome to \nRobotois :D"));
