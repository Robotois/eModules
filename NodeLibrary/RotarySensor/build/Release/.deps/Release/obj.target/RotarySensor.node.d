cmd_Release/obj.target/RotarySensor.node := g++ -shared -pthread -rdynamic  -Wl,-soname=RotarySensor.node -o Release/obj.target/RotarySensor.node -Wl,--start-group Release/obj.target/RotarySensor/RotarySensor.o Release/obj.target/RotarySensor/RotaryWrapper.o Release/obj.target/RotarySensor/../../Modules/AnalogModules/RotarySensor.o Release/obj.target/RotarySensor/../../Libraries/ADS1015/ADS1015.o Release/obj.target/RotarySensor/../../Libraries/Timer/AccurateTiming.o -Wl,--end-group -l bcm2835 -l rt
