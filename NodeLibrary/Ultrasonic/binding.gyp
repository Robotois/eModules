{
  "targets": [
    {
      "target_name": "UltrasonicModule",
      "sources": [ "UltrasonicModule.cpp","UltrasonicWrapper.cpp",
      "../../Modules/Ultrasonic/UltrasonicSensor.cpp",
      "../../Libraries/DigitalIO/DigitalHeader.cpp",
      "../../Libraries/Timer/AccurateTiming.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
