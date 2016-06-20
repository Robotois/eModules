{
  "targets": [
    {
      "target_name": "RGBModule",
      "sources": [ "RGBModule.cpp","RGBWrapper.cpp",
      "../../Modules/RGBLEDs/RGBLEDs.cpp",
      "../../Libraries/PCA9685/PCA9685.cpp",
      "../../Libraries/Timer/AccurateTiming.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
