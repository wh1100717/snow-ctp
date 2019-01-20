#include <signal.h>
#include <node.h>
#include "WrapMd.h"
#include "WrapTd.h"



namespace ctp
{
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::Value;

void signal_segv(int sig)
{
    printf("catch SIGSEGV\n");
}

void CreateMd(const FunctionCallbackInfo<Value>& args) 
{
    md::WrapMd::NewInstance(args);
}

void CreateTd(const FunctionCallbackInfo<Value>& args) 
{
    td::WrapTd::NewInstance(args);
}


void Init(Local<Object> exports) 
{
    //signal(SIGSEGV, signal_segv);
    md::WrapMd::Init(exports->GetIsolate());
    td::WrapTd::Init(exports->GetIsolate());
    NODE_SET_METHOD(exports, "crmd", CreateMd);
    NODE_SET_METHOD(exports, "crtd", CreateTd);
}

NODE_MODULE(shifctp, Init)

};



