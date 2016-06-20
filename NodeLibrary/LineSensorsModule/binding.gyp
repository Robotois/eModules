{
  "targets": [
    {
      "target_name": "LineSensorsModule",
      "sources": [ "LineSensorsModule.cpp","LineSensorsWrapper.cpp",
      "../../Modules/LineSensors/LineSensors.cpp",
      "../../Libraries/MCP23008/MCP23008.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
