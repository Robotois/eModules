#ifndef LEDWRAPPER_H
#define LEDWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/LED/LED.h"

class LEDWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit LEDWrapper(uint8_t _header);
  ~LEDWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void write(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  LED *led;
};

#endif
