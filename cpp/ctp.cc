#include <node.h>
#include <uv.h>
#include "ctp_trader.h"
#include "ctp_market.h"

using namespace v8;

bool islog;//log?

void CreateTrader(const FunctionCallbackInfo<Value>& args) {
  CTPTrader::NewInstance(args);
}

void CreateMarket(const FunctionCallbackInfo<Value>& args) {
  CTPMarket::NewInstance(args);
}

void Settings(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (!args[0]->IsUndefined() && args[0]->IsObject()) {
    Local<Object> setting = args[0]->ToObject();
    Local<Value> log = setting->Get(String::NewFromUtf8(isolate, "log"));
    if (!log->IsUndefined()) {
      islog = log->BooleanValue();
    }
  }

  args.GetReturnValue().Set(Undefined(isolate));
}

void Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  CTPTrader::Init(isolate);
  CTPMarket::Init(isolate);

  NODE_SET_METHOD(exports, "createTrader", CreateTrader);
  NODE_SET_METHOD(exports, "CreateMarket", CreateMarket);
  NODE_SET_METHOD(exports, "settings", Settings);
}

NODE_MODULE(ctp, Init)
