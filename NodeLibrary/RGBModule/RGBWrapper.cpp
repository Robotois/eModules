#include <node.h>
#include "RGBWrapper.h"

using namespace v8;

Persistent<Function> RGBWrapper::constructor;

RGBWrapper::RGBWrapper(uint8_t _add){
  rgb = new RGBLEDs(_add);
}

RGBWrapper::~RGBWrapper(){
  delete rgb;
}

void RGBWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  RGBWrapper* temp_obj = ObjectWrap::Unwrap<RGBWrapper>(args.Holder());

  delete temp_obj->rgb;
}

void RGBWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"RGBWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"setRGB",setRGB);
  NODE_SET_PROTOTYPE_METHOD(tpl,"blinkRGB",blinkRGB);
  NODE_SET_PROTOTYPE_METHOD(tpl,"ledOff",ledOff);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);

  constructor.Reset(isolate,tpl->GetFunction());
}

void RGBWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _add = 0x00;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  RGBWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 0:
        obj = new RGBWrapper();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      case 1:
        _add = (uint8_t) args[0]->NumberValue();
        obj = new RGBWrapper(_add);
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

void RGBWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
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

void RGBWrapper::setRGB(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // - It is required four arguments: LedNumber, RedCode, GreenCode and BlueCode
  // - The RGB code can take values in the range of 0 - 255 for each channel
  if(_argc != 4){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  uint8_t ledNumber = (uint8_t) args[0]->NumberValue(),
    redCode = (uint8_t) args[1]->NumberValue(),
    greenCode = (uint8_t) args[2]->NumberValue(),
    blueCode = (uint8_t) args[3]->NumberValue();

  RGBWrapper* temp_obj = ObjectWrap::Unwrap<RGBWrapper>(args.Holder());
  temp_obj->rgb->setRGB(ledNumber,redCode,greenCode,blueCode);
  // args.GetReturnValue().Set();
}

void RGBWrapper::blinkRGB(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // - It is required four arguments: LedNumber, RedCode, GreenCode and BlueCode
  // - The RGB code can take values in the range of 0 - 255 for each channel
  if(_argc != 4){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  uint8_t ledNumber = (uint8_t) args[0]->NumberValue(),
    redCode = (uint8_t) args[1]->NumberValue(),
    greenCode = (uint8_t) args[2]->NumberValue(),
    blueCode = (uint8_t) args[3]->NumberValue();

  RGBWrapper* temp_obj = ObjectWrap::Unwrap<RGBWrapper>(args.Holder());
  temp_obj->rgb->blinkRGB(ledNumber,redCode,greenCode,blueCode);
  // args.GetReturnValue().Set();
}

void RGBWrapper::ledOff(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // - It is required four arguments: LedNumber, RedCode, GreenCode and BlueCode
  // - The RGB code can take values in the range of 0 - 255 for each channel
  if(_argc != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  uint8_t ledNumber = (uint8_t) args[0]->NumberValue();

  RGBWrapper* temp_obj = ObjectWrap::Unwrap<RGBWrapper>(args.Holder());
  temp_obj->rgb->ledOff(ledNumber);
  // args.GetReturnValue().Set();
}
