#include <node.h>
#include "BCMSetupWrapper.h"

using namespace v8;

Persistent<Function> BCMSetupWrapper::constructor;

BCMSetupWrapper::BCMSetupWrapper(){
  bcmSetup = new BCMSetup();
}

BCMSetupWrapper::~BCMSetupWrapper(){
  delete bcmSetup;
}

void BCMSetupWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"BCMSetupWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"BCMInit",BCMInit);
  NODE_SET_PROTOTYPE_METHOD(tpl,"BCMEnd",BCMEnd);

  constructor.Reset(isolate,tpl->GetFunction());
}

void BCMSetupWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    BCMSetupWrapper* obj = new BCMSetupWrapper();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    // const int argc = 0;
    // Local<Value> argv[argc];
    Local<Function> cons = Local<Function>::New(isolate,constructor);
    args.GetReturnValue().Set(cons->NewInstance());
  }
}

void BCMSetupWrapper::NewInstance(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Local<Function> cons = Local<Function>::New(isolate,constructor);
  Local<Object> instance = cons->NewInstance();
  args.GetReturnValue().Set(instance);
}

void BCMSetupWrapper::BCMInit(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BCMSetupWrapper* obj = ObjectWrap::Unwrap<BCMSetupWrapper>(args.Holder());
  uint8_t value= obj->bcmSetup->bcm_init();
  args.GetReturnValue().Set(Number::New(isolate,value));
}

void BCMSetupWrapper::BCMEnd(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BCMSetupWrapper* obj = ObjectWrap::Unwrap<BCMSetupWrapper>(args.Holder());
  obj->bcmSetup->bcm_end();
  args.GetReturnValue().Set(Number::New(isolate,0));
}
