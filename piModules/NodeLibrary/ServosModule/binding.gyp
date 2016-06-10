{
  "targets": [
    {
      "target_name": "ServosModule",
      "sources": [ "ServosModule.cpp","ServosWrapper.cpp",
      "../../Modules/Servos/Servos.cpp",
      "../../Libraries/PCA9685/PCA9685.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
