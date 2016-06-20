#include <node.h>
#include "MotorsWrapper.h"

using namespace v8;

Persistent<Function> MotorsWrapper::constructor;

MotorsWrapper::MotorsWrapper(uint8_t _add){
  motors = new Motors(_add);
}

MotorsWrapper::~MotorsWrapper(){
  delete motors;
}

void MotorsWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"MotorsWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"LeftMotorPWM",LeftMotorPWM);
  NODE_SET_PROTOTYPE_METHOD(tpl,"LeftMotorStop",LeftMotorStop);
  NODE_SET_PROTOTYPE_METHOD(tpl,"RightMotorPWM",RightMotorPWM);
  NODE_SET_PROTOTYPE_METHOD(tpl,"RightMotorStop",RightMotorStop);
  NODE_SET_PROTOTYPE_METHOD(tpl,"DrivePWM",DrivePWM);
  NODE_SET_PROTOTYPE_METHOD(tpl,"MotorsStop",MotorsStop);

  constructor.Reset(isolate,tpl->GetFunction());
}

void MotorsWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _add = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  MotorsWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 0:
        obj = new MotorsWrapper();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      case 1:
        _add = (uint8_t) args[0]->NumberValue();
        obj = new MotorsWrapper(_add);
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

void MotorsWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
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

void MotorsWrapper::LeftMotorPWM(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  int16_t pwm = (int16_t) args[0]->NumberValue();

  MotorsWrapper* temp_obj = ObjectWrap::Unwrap<MotorsWrapper>(args.Holder());
  temp_obj->motors->maPWM(pwm);
}

void MotorsWrapper::RightMotorPWM(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  int16_t pwm = (int16_t) args[0]->NumberValue();

  MotorsWrapper* temp_obj = ObjectWrap::Unwrap<MotorsWrapper>(args.Holder());
  temp_obj->motors->mbPWM(pwm);
}

void MotorsWrapper::DrivePWM(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc != 2){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  int16_t left_pwm = (int16_t) args[0]->NumberValue(),
    right_pwm = (int16_t) args[1]->NumberValue();

  MotorsWrapper* temp_obj = ObjectWrap::Unwrap<MotorsWrapper>(args.Holder());
  temp_obj->motors->drivePWMs(left_pwm,right_pwm);
}

void MotorsWrapper::LeftMotorStop(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc > 0){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  MotorsWrapper* temp_obj = ObjectWrap::Unwrap<MotorsWrapper>(args.Holder());
  temp_obj->motors->maControl(MOTORS_STOP);
}

void MotorsWrapper::RightMotorStop(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc > 0){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  MotorsWrapper* temp_obj = ObjectWrap::Unwrap<MotorsWrapper>(args.Holder());
  temp_obj->motors->mbControl(MOTORS_STOP);
}

void MotorsWrapper::MotorsStop(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc > 0){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  MotorsWrapper* temp_obj = ObjectWrap::Unwrap<MotorsWrapper>(args.Holder());
  temp_obj->motors->motorsControl(MOTORS_STOP,MOTORS_STOP);
}
