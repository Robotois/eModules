#include <node.h>
#include "BCMSetupWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  BCMSetupWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module){
  BCMSetupWrapper::Init();

  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(BCMConfig,InitAll);
