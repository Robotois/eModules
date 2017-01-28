#ifndef BUTTONWRAPPER_H
#define BUTTONWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/Button/Button.h"

class ButtonWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit ButtonWrapper(uint8_t _header);
  ~ButtonWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getValue(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  Button *button;
};

#endif
