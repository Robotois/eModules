#include <node.h>
#include "LineSensorsWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  LineSensorsWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  LineSensorsWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(LineSensorsModule, InitAll)
