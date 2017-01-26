#include <node.h>
#include "LightWrapper.h"

using namespace v8;

Persistent<Function> LightWrapper::constructor;

LightWrapper::LightWrapper(uint8_t _port, uint8_t _addr){
  lightSensor = new LightSensor(_addr);
  lightSensor->selectPort(_port);
}

LightWrapper::~LightWrapper(){
  delete lightSensor;
}

void LightWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LightWrapper* temp_obj = ObjectWrap::Unwrap<LightWrapper>(args.Holder());

  delete temp_obj->lightSensor;
}

void LightWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"LightWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"getValue",getValue);
  // NODE_SET_PROTOTYPE_METHOD(tpl,"getBasicValue",getBasicValue);
  NODE_SET_PROTOTYPE_METHOD(tpl,"getScaledValue",getScaledValue);
  NODE_SET_PROTOTYPE_METHOD(tpl,"basicScaledValue",basicScaledValue);

  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);

  constructor.Reset(isolate,tpl->GetFunction());
}

void LightWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _addr = 0x00, _port = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  // printf("Args Count: %d\n",args.Length());
  LightWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 1: // Only the BCMWrapper is passed
        _port = (uint8_t) args[0]->NumberValue();
        obj = new LightWrapper(_port);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      case 2:
        _port = (uint8_t) args[0]->NumberValue();
        _addr = (uint8_t) args[1]->NumberValue();
        obj = new LightWrapper(_port,_addr);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      default:
        isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    if(_argc > 2){
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
    Local<Value>* argv = new Local<Value>[_argc];
    for(uint8_t i = 0; i < _argc; i++){
      argv[i] = args[i];
    }
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(_argc, argv));
  }
}

void LightWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // printf("Args Count: %d\n",_argc);
  if(_argc > 2){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }
  Handle<Value>* argv = new Handle<Value>[_argc];
  for(uint8_t i = 0; i < _argc; i++){
    argv[i] = args[i];
  }
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(_argc, argv);

  args.GetReturnValue().Set(instance);
}

void LightWrapper::getValue(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LightWrapper* temp_obj = ObjectWrap::Unwrap<LightWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->lightSensor->getValue()));
}

// void LightWrapper::getBasicValue(const FunctionCallbackInfo<Value>& args){
//   Isolate* isolate = Isolate::GetCurrent();
//   HandleScope scope(isolate);
//
//   LightWrapper* temp_obj = ObjectWrap::Unwrap<LightWrapper>(args.Holder());
//
//   args.GetReturnValue().Set(Number::New(isolate,temp_obj->lightSensor->getBasicValue()));
// }

void LightWrapper::getScaledValue(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LightWrapper* temp_obj = ObjectWrap::Unwrap<LightWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->lightSensor->getScaledValue()));
}

void LightWrapper::basicScaledValue(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LightWrapper* temp_obj = ObjectWrap::Unwrap<LightWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->lightSensor->basicScaledValue()));
}
