{
  "targets": [
    {
      "target_name": "MotorsModule",
      "sources": [ "MotorsModule.cpp","MotorsWrapper.cpp",
      "../../Modules/Motors/Motors.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
