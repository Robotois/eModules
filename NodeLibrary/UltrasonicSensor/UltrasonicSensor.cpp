#include <node.h>
#include "UltrasonicWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  UltrasonicWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  UltrasonicWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(UltrasonicSensor, InitAll)
