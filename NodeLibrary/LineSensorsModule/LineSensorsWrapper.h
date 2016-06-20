#ifndef LINESENSORSWRAPPER_H
#define LINESENSORSWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/LineSensors/LineSensors.h"

class LineSensorsWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit LineSensorsWrapper(uint8_t _add = 0x00);
  ~LineSensorsWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ReadSensors(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ReadSensor(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ReadLine(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SetBackground(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  LineSensors *lineSensors;
};

#endif
