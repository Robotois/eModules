#include <node.h>
#include "LightWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  LightWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  LightWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(LightSensor, InitAll)
