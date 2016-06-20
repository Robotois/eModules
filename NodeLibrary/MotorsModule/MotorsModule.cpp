#include <node.h>
#include "MotorsWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  MotorsWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  MotorsWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(MotorsModule, InitAll)
