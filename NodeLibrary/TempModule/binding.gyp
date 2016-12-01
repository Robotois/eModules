{
  "targets": [
    {
      "target_name": "TempModule",
      "sources": [ "TempModule.cpp","TempWrapper.cpp",
      "../../Modules/AnalogModules/TemperatureSensor.cpp",
      "../../Libraries/ADS1015/ADS1015.cpp",
      "../../Libraries/Timer/AccurateTiming.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
