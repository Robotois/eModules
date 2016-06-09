#include <node.h>
#include "DistanceWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  DistanceWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  DistanceWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(LightModule, InitAll)
