#include <node.h>
#include "RGBWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  RGBWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  RGBWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(RGBModule, InitAll)
