#include <node.h>
#include "ButtonWrapper.h"

using namespace v8;

Persistent<Function> ButtonWrapper::constructor;

ButtonWrapper::ButtonWrapper(uint8_t _header){
  button = new Button(_header);
}

ButtonWrapper::~ButtonWrapper(){
  delete button;
}

void ButtonWrapper::release(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ButtonWrapper* temp_obj = ObjectWrap::Unwrap<ButtonWrapper>(args.Holder());

  delete temp_obj->button;
}


void ButtonWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"ButtonWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"read",read);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);
  // NODE_SET_PROTOTYPE_METHOD(tpl,"BCMEnd",BCMEnd);
  // tpl->PrototypeTemplate()->Set(Nan::New("temperature").ToLocalChecked(),
  //   Nan::New<v8::FunctionTemplate>(Temperature)->GetFunction());

  constructor.Reset(isolate,tpl->GetFunction());
}

void ButtonWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _header = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  // printf("Args Count: %d\n",args.Length());
  ButtonWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    if(_argc == 1){
      _header = (uint8_t) args[0]->NumberValue();
      obj = new ButtonWrapper(_header);
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

void ButtonWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
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

void ButtonWrapper::read(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ButtonWrapper* temp_obj = ObjectWrap::Unwrap<ButtonWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->button->read()));
}

// void Temperature(){
//   OpticalDistanceSensor temp;
//   temp.selectPort(3);
//   printf("Temp Input: %0.2f\n",temp.getTemperature());
// }
