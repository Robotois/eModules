{
  "targets": [
    {
      "target_name": "UltrasonicSensor",
      "sources": [ "UltrasonicSensor.cpp","UltrasonicWrapper.cpp",
      "../../Modules/Ultrasonic/UltrasonicSensor.cpp",
      "../../Libraries/DigitalIO/DigitalHeader.cpp",
      "../../Libraries/Timer/AccurateTiming.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
