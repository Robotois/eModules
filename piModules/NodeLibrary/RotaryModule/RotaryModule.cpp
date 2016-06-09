#include <node.h>
#include "RotaryWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  RotaryWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  RotaryWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(RotaryModule, InitAll)
