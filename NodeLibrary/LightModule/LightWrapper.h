#ifndef LIGHTWRAPPER_H
#define LIGHTWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/AnalogModules/LightSensor.h"

class LightWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit LightWrapper(uint8_t _port = 0x01, uint8_t _addr = 0x00);
  ~LightWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  // static void getBasicValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getScaledValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getBasicScaledValue(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  LightSensor *lightSensor;
};

#endif
