#ifndef RGBWRAPPER_H
#define RGBWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/RGBLEDs/RGBLEDs.h"

class RGBWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit RGBWrapper(uint8_t _add = 0x00);
  ~RGBWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setRGB(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void blinkRGB(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ledOff(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void allOff(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  RGBLEDs *rgb;
};

#endif
