#include <node.h>
#include "UltrasonicWrapper.h"

using namespace v8;

Persistent<Function> UltrasonicWrapper::constructor;

UltrasonicWrapper::UltrasonicWrapper(uint8_t _header){
  ultrasonic = new UltrasonicSensor(_header);
}

UltrasonicWrapper::~UltrasonicWrapper(){
  delete ultrasonic;
}

void UltrasonicWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  UltrasonicWrapper* temp_obj = ObjectWrap::Unwrap<UltrasonicWrapper>(args.Holder());

  delete temp_obj->ultrasonic;
}

void UltrasonicWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"UltrasonicWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"distance",distance);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);
  // NODE_SET_PROTOTYPE_METHOD(tpl,"BCMEnd",BCMEnd);
  // tpl->PrototypeTemplate()->Set(Nan::New("temperature").ToLocalChecked(),
  //   Nan::New<v8::FunctionTemplate>(Temperature)->GetFunction());

  constructor.Reset(isolate,tpl->GetFunction());
}

void UltrasonicWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _header = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  UltrasonicWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 1:
        _header = (uint8_t) args[0]->NumberValue();
        obj = new UltrasonicWrapper(_header);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      default:
        isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    if(_argc > 1){
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

void UltrasonicWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // printf("Args Count: %d\n",_argc);
  if(_argc > 1){
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

void UltrasonicWrapper::distance(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  UltrasonicWrapper* temp_obj = ObjectWrap::Unwrap<UltrasonicWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->ultrasonic->getDistance()));
}

// void Temperature(){
//   OpticalDistanceSensor temp;
//   temp.selectPort(3);
//   printf("Temp Input: %0.2f\n",temp.getTemperature());
// }
