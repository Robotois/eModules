{
  "targets": [
    {
      "target_name": "RotaryModule",
      "sources": [ "RotaryModule.cpp","RotaryWrapper.cpp",
      "../../Modules/AnalogModules/RotarySensor.cpp",
      "../../Libraries/ADS1015/ADS1015.cpp",
      "../../Libraries/Timer/AccurateTiming.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
