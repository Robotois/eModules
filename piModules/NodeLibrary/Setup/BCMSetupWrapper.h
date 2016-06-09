#ifndef BCMSETUPWRAPPER_H
#define BCMSETUPWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>

#include "../../Libraries/BCMSetup/BCMSetup.h"

class BCMSetupWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

  BCMSetup* bcmSetup;
private:
  explicit BCMSetupWrapper();
  ~BCMSetupWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void BCMInit(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void BCMEnd(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;


};
#endif
