cmd_Release/obj.target/RGBModule.node := g++ -shared -pthread -rdynamic  -Wl,-soname=RGBModule.node -o Release/obj.target/RGBModule.node -Wl,--start-group Release/obj.target/RGBModule/RGBModule.o Release/obj.target/RGBModule/RGBWrapper.o Release/obj.target/RGBModule/../../Modules/RGBLEDs/RGBLEDs.o Release/obj.target/RGBModule/../../Libraries/PCA9685/PCA9685.o Release/obj.target/RGBModule/../../Libraries/Timer/AccurateTiming.o -Wl,--end-group -l bcm2835 -l rt