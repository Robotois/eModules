#ifndef ULTRASONICWRAPPER_H
#define ULTRASONICWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/Ultrasonic/UltrasonicSensor.h"

class UltrasonicWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit UltrasonicWrapper(uint8_t _header);
  ~UltrasonicWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getBasicValue(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  UltrasonicSensor *ultrasonic;
};

#endif
