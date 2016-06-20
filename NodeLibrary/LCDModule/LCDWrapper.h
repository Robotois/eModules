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
  explicit LCDWrapper(uint8_t _add = 0x01);
  ~LCDWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Message(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  LCDModule *lcd;
};

#endif
