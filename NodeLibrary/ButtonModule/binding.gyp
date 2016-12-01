{
  "targets": [
    {
      "target_name": "ButtonModule",
      "sources": [ "ButtonModule.cpp","ButtonWrapper.cpp",
      "../../Modules/Button/Button.cpp",
      "../../Libraries/DigitalIO/DigitalHeader.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
