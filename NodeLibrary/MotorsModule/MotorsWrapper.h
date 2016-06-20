#ifndef MOTORSWRAPPER_H
#define MOTORSWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/Motors/Motors.h"

class MotorsWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit MotorsWrapper(uint8_t _add = 0x00);
  ~MotorsWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void LeftMotorPWM(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LeftMotorStop(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void RightMotorPWM(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void RightMotorStop(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void DrivePWM(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void MotorsStop(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  Motors *motors;
};

#endif
