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
  explicit RGBWrapper(uint8_t _add = 0x01);
  ~RGBWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SetRGB(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  RGBLEDs *rgb;
};

#endif
