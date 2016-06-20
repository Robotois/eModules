#include <node.h>
#include "LCDWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  LCDWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  LCDWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(LCDModule, InitAll)
