{
  "targets": [
    {
      "target_name": "LightSensor",
      "sources": [ "LightSensor.cpp","LightWrapper.cpp",
      "../../Modules/AnalogModules/LightSensor.cpp",
      "../../Libraries/ADS1015/ADS1015.cpp",
      "../../Libraries/Timer/AccurateTiming.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
