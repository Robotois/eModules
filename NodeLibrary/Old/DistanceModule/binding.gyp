{
  "targets": [
    {
      "target_name": "DistanceModule",
      "sources": [ "DistanceModule.cpp","DistanceWrapper.cpp",
      "../../Modules/AnalogModules/OpticalDistanceSensor.cpp",
      "../../Libraries/ADS1015/ADS1015.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
