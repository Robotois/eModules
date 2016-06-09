{
  "targets": [
    {
      "target_name": "BCMConfig",
      "sources": [ "BCMConfig.cpp","BCMSetupWrapper.cpp",
      "../../Libraries/BCMSetup/BCMSetup.cpp" ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
