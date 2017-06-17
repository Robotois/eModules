#ifndef LCDWRAPPER_H
#define LCDWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/LCD/LCDModule.h"

class LCDWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit LCDWrapper(uint8_t _add = 0x00);
  ~LCDWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void message(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void clear(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void home(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setCursor(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void bklBlink(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  LCDModule *lcd;
};

#endif
