#include <node.h>
#include "LEDWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  LEDWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  LEDWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(LEDModule, InitAll)
