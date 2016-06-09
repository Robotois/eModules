{
  "targets": [
    {
      "target_name": "LCDModule",
      "sources": [ "LCDModule.cpp","LCDWrapper.cpp",
      "../../Modules/LCD/LCDModule.cpp",
      "../../Libraries/MCP23008/MCP23008.cpp",
      "../../Libraries/Timer/AccurateTiming.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
