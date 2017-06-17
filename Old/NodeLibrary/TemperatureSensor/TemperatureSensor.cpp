#include <node.h>
#include "TempWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  TempWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  TempWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(TemperatureSensor, InitAll)
