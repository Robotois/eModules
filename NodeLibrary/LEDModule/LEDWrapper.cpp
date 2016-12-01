#include <node.h>
#include "LEDWrapper.h"

using namespace v8;

Persistent<Function> LEDWrapper::constructor;

LEDWrapper::LEDWrapper(uint8_t _header){
  led = new LED(_header);
}

LEDWrapper::~LEDWrapper(){
  delete led;
}

void LEDWrapper::release(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LEDWrapper* temp_obj = ObjectWrap::Unwrap<LEDWrapper>(args.Holder());

  delete temp_obj->led;
}

void LEDWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"LEDWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"write",write);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);
  // NODE_SET_PROTOTYPE_METHOD(tpl,"BCMEnd",BCMEnd);
  // tpl->PrototypeTemplate()->Set(Nan::New("temperature").ToLocalChecked(),
  //   Nan::New<v8::FunctionTemplate>(Temperature)->GetFunction());

  constructor.Reset(isolate,tpl->GetFunction());
}

void LEDWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _header = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  // printf("Args Count: %d\n",args.Length());
  LEDWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    if(_argc == 1){
      _header = (uint8_t) args[0]->NumberValue();
      obj = new LEDWrapper(_header);
      obj->Wrap(args.This());
      args.GetReturnValue().Set(args.This());
    }else{
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments...")));
      return;
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    if(_argc != 1){
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments...")));
      return;
    }
    Local<Value>* argv = new Local<Value>[_argc];
    for(uint8_t i = 0; i < _argc; i++){
      argv[i] = args[i];
    }
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(_argc, argv));
  }
}

void LEDWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // printf("Args Count: %d\n",_argc);
  if(_argc != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
    return;
  }
  Handle<Value>* argv = new Handle<Value>[_argc];
  for(uint8_t i = 0; i < _argc; i++){
    argv[i] = args[i];
  }
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(_argc, argv);

  args.GetReturnValue().Set(instance);
}

void LEDWrapper::write(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments for Motor Module...")));
  }

  int8_t state = (int8_t) args[0]->NumberValue();

  LEDWrapper* temp_obj = ObjectWrap::Unwrap<LEDWrapper>(args.Holder());
  temp_obj->led->write(state);
  // args.GetReturnValue().Set(Number::New(isolate,temp_obj->led->read()));
}

// void Temperature(){
//   OpticalDistanceSensor temp;
//   temp.selectPort(3);
//   printf("Temp Input: %0.2f\n",temp.getTemperature());
// }
