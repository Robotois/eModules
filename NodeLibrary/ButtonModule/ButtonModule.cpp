#include <node.h>
#include "ButtonWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  ButtonWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  ButtonWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(ButtonModule, InitAll)
