#include <node.h>
#include "LCDWrapper.h"

using namespace v8;

Persistent<Function> LCDWrapper::constructor;

LCDWrapper::LCDWrapper(uint8_t _add){
  lcd = new LCDModule(_add);
}

LCDWrapper::~LCDWrapper(){
  // delete lcd;
}

void LCDWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LCDWrapper* temp_obj = ObjectWrap::Unwrap<LCDWrapper>(args.Holder());
  temp_obj->lcd->release();
  delete temp_obj->lcd;
}

void LCDWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"LCDWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"message",message);
  NODE_SET_PROTOTYPE_METHOD(tpl,"clear",clear);
  NODE_SET_PROTOTYPE_METHOD(tpl,"home",home);
  NODE_SET_PROTOTYPE_METHOD(tpl,"setCursor",setCursor);
  NODE_SET_PROTOTYPE_METHOD(tpl,"bklBlink",bklBlink);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);

  constructor.Reset(isolate,tpl->GetFunction());
}

void LCDWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _add = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  LCDWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 0:
        obj = new LCDWrapper();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      case 1:
        _add = (uint8_t) args[0]->NumberValue();
        obj = new LCDWrapper(_add);
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

void LCDWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
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

void LCDWrapper::message(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LCDWrapper* temp_obj = ObjectWrap::Unwrap<LCDWrapper>(args.Holder());
  String::Utf8Value msg(args[0]->ToString());
  std::string _msg = std::string(*msg);

  temp_obj->lcd->message(_msg);
  // args.GetReturnValue().Set(Number::New(isolate,temp_obj->lcd->message(_msg)));
}

void LCDWrapper::clear(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LCDWrapper* temp_obj = ObjectWrap::Unwrap<LCDWrapper>(args.Holder());
  temp_obj->lcd->clear();
}

void LCDWrapper::bklBlink(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LCDWrapper* temp_obj = ObjectWrap::Unwrap<LCDWrapper>(args.Holder());
  temp_obj->lcd->bklBlink();
}

void LCDWrapper::home(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LCDWrapper* temp_obj = ObjectWrap::Unwrap<LCDWrapper>(args.Holder());
  temp_obj->lcd->home();
}

void LCDWrapper::setCursor(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LCDWrapper* temp_obj = ObjectWrap::Unwrap<LCDWrapper>(args.Holder());

  uint8_t _argc = args.Length(), col, row;
  // printf("Args Count: %d\n",_argc);
  if(_argc != 2){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments to set cursor in the LCD Module...")));
  }
  row = (uint8_t) (args[0]->NumberValue() - 1);
  col = (uint8_t) (args[1]->NumberValue() - 1);
  if(col > 39 or row > 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments to set cursor in the LCD Module...")));
  }
  temp_obj->lcd->setCursor(row,col);
  // args.GetReturnValue().Set(Number::New(isolate,temp_obj->lcd->message(_msg)));
}
