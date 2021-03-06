#include <node.h>
#include "LineSensorsWrapper.h"
#include <string>

using namespace v8;

Persistent<Function> LineSensorsWrapper::constructor;

LineSensorsWrapper::LineSensorsWrapper(uint8_t _add){
  lineSensors = new LineSensors(_add);
}

LineSensorsWrapper::~LineSensorsWrapper(){
  delete lineSensors;
}

void LineSensorsWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LineSensorsWrapper* temp_obj = ObjectWrap::Unwrap<LineSensorsWrapper>(args.Holder());
  delete temp_obj->lineSensors;
}

void LineSensorsWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"LineSensorsWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"readSensors",readSensors);
  NODE_SET_PROTOTYPE_METHOD(tpl,"readSensor",readSensor);
  NODE_SET_PROTOTYPE_METHOD(tpl,"readLine",readLine);
  NODE_SET_PROTOTYPE_METHOD(tpl,"setBackground",setBackground);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);

  constructor.Reset(isolate,tpl->GetFunction());
}

void LineSensorsWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _add = 0x00;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  LineSensorsWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 0:
        obj = new LineSensorsWrapper();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      case 1:
        _add = (uint8_t) args[0]->NumberValue();
        obj = new LineSensorsWrapper(_add);
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

void LineSensorsWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
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

void LineSensorsWrapper::readSensors(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() > 0){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  LineSensorsWrapper* temp_obj = ObjectWrap::Unwrap<LineSensorsWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->lineSensors->readSensors()));
}

void LineSensorsWrapper::readSensor(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  LineSensorsWrapper* temp_obj = ObjectWrap::Unwrap<LineSensorsWrapper>(args.Holder());
  uint8_t _sensorNumber = (uint8_t) args[0]->NumberValue();

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->lineSensors->readSensor(_sensorNumber-1)));
}

void LineSensorsWrapper::readLine(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() > 0){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  LineSensorsWrapper* temp_obj = ObjectWrap::Unwrap<LineSensorsWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->lineSensors->readLine()));
}

void LineSensorsWrapper::setBackground(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments for setBackground...")));
  }

  uint8_t _background;

  LineSensorsWrapper* temp_obj = ObjectWrap::Unwrap<LineSensorsWrapper>(args.Holder());
  String::Utf8Value msg(args[0]->ToString());
  std::string _msg = std::string(*msg);

  if(_msg == "white"){
    _background = LINESENSORS_WHITE_BACKGROUND;
  }else{
    if(_msg == "black"){
      _background = LINESENSORS_BLACK_BACKGROUND;
    }else{
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong background...")));
    }
  }
  temp_obj->lineSensors->setBackground(_background);
  // args.GetReturnValue().Set(Number::New(isolate,));
}
