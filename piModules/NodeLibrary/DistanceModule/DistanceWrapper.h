#ifndef DISTANCEWRAPPER_H
#define DISTANCEWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../../Modules/AnalogModules/OpticalDistanceSensor.h"

class DistanceWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit DistanceWrapper(uint8_t _port = 0x01, uint8_t _addr = 0x00);
  ~DistanceWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Distance(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  OpticalDistanceSensor *distSensor;
};

#endif
