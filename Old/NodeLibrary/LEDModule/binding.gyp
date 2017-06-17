{
  "targets": [
    {
      "target_name": "LEDModule",
      "sources": [ "LEDModule.cpp","LEDWrapper.cpp",
      "../../Modules/LED/LED.cpp",
      "../../Libraries/DigitalIO/DigitalHeader.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
