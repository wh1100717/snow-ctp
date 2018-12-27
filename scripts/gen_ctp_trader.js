const fs = require('fs')
const path = require('path')

const ctp_field = require('./ctp_struct')

const tpl_h = `
#ifndef CTP_TRADER_H
#define CTP_TRADER_H

#include <inttypes.h> /* strtoimax */
#include <iostream>
#include <string>
#include <node.h>
#include <node_object_wrap.h>

#include "ctp_utils.h"
#include "uv_trader.h"
#include "ThostFtdcUserApiDataType.h"

using namespace v8;

class CTPTrader : public node::ObjectWrap {
public:
  CTPTrader(void);
  ~CTPTrader(void);

  static void Init(Isolate* isolate);
  static void NewInstance(const FunctionCallbackInfo<Value>& args);
  static void Disposed(const FunctionCallbackInfo<Value>& args);
  static void GetTradingDay(const FunctionCallbackInfo<Value>& args);
  static void On(const FunctionCallbackInfo<Value>& args);
  static void Connect(const FunctionCallbackInfo<Value>& args);
{$$1}
private:
  static Local<Value> pkg_rspinfo(void *vpRspInfo);

  uv_trader* uvTrader;
  static int s_uuid;
  static void FunCallback(CbRtnField *data);
  static void FunRtnCallback(int result, void* baton);
  static Persistent<Function> constructor;
  static std::map<std::string, int> event_map;
  static std::map<int, Persistent<Function> > callback_map;
  static std::map<int, Persistent<Function> > fun_rtncb_map;

  static void initEventMap();
  static void New(const FunctionCallbackInfo<Value>& args);
{$$2}
};

#endif
`

const tpl_cpp = `
#include "ctp_trader.h"

Persistent <Function> CTPTrader::constructor;
int CTPTrader::s_uuid;
std::map<std::string, int> CTPTrader::event_map;
std::map<int, Persistent<Function> > CTPTrader::callback_map;
std::map<int, Persistent<Function> > CTPTrader::fun_rtncb_map;

CTPTrader::CTPTrader(void) {
  logger_cout("ctp_trader------>object start init");
  uvTrader = new uv_trader();
  logger_cout("ctp_trader------>object init successed");
}

CTPTrader::~CTPTrader(void) {
  if (uvTrader) {
    delete uvTrader;
  }
  logger_cout("ctp_trader------>object destroyed");
}

void CTPTrader::New(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (event_map.size() == 0)
    initEventMap();

  if (args.IsConstructCall()) {
    CTPTrader *wTrader = new CTPTrader();
    wTrader->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    const int argc = 1;
    Local <Value> argv[argc] = {Number::New(isolate, 0)};
    Local <Function> cons = Local<Function>::New(isolate, constructor);
    Local <Context> context = isolate->GetCurrentContext();
    Local <Object> instance = cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(instance);
  }
}

void CTPTrader::NewInstance(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  const unsigned argc = 1;
  Local <Value> argv[argc] = {Number::New(isolate, 0)};
  Local <Function> cons = Local<Function>::New(isolate, constructor);
  Local <Context> context = isolate->GetCurrentContext();
  Local <Object> instance = cons->NewInstance(context, argc, argv).ToLocalChecked();
  args.GetReturnValue().Set(instance);
}

void CTPTrader::Init(Isolate *isolate) {
  // Prepare constructor template
  Local <FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "CTPTrader"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "GetTradingDay", GetTradingDay);
  NODE_SET_PROTOTYPE_METHOD(tpl, "Connect", Connect);
  NODE_SET_PROTOTYPE_METHOD(tpl, "On", On);
{$$1}
  constructor.Reset(isolate, tpl->GetFunction());
}

void CTPTrader::initEventMap() {
{$$2}
}

void CTPTrader::GetTradingDay(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  CTPTrader *wTrader = ObjectWrap::Unwrap<CTPTrader>(args.Holder());
  const char *tradingDay = wTrader->uvTrader->GetTradingDay();
  logger_cout("GetTradingDay:");
  logger_cout(tradingDay);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, tradingDay));
}

void CTPTrader::On(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args[0]->IsUndefined() || args[1]->IsUndefined()) {
    logger_cout("Wrong arguments->event name or function");
    isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->event name or function")));
    return;
  }

  CTPTrader *obj = ObjectWrap::Unwrap<CTPTrader>(args.Holder());

  Local <String> eventName = args[0]->ToString();
  Local <Function> cb = Local<Function>::Cast(args[1]);

  String::Utf8Value eNameAscii(eventName);

  std::map<std::string, int>::iterator eIt = event_map.find((std::string) * eNameAscii);
  if (eIt == event_map.end()) {
    logger_cout("System has not register this event");
    isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "System has no register this event")));
    return;
  }

  std::map < int, Persistent < Function > > ::iterator
  cIt = callback_map.find(eIt->second);
  if (cIt != callback_map.end()) {
    logger_cout("Callback is defined before");
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Callback is defined before")));
    return;
  }

  callback_map[eIt->second].Reset(isolate, cb);
  obj->uvTrader->On(*eNameAscii, eIt->second, FunCallback);
  return args.GetReturnValue().Set(String::NewFromUtf8(isolate, "finish exec on"));
}

void CTPTrader::Connect(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args[0]->IsUndefined()) {
    logger_cout("Wrong arguments->front addr");
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->front addr")));
    return;
  }
  if (!args[2]->IsNumber() || !args[3]->IsNumber()) {
    logger_cout("Wrong arguments->public or private topic type");
    isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->public or private topic type")));
    return;
  }
  int uuid = -1;
  CTPTrader *obj = ObjectWrap::Unwrap<CTPTrader>(args.Holder());
  if (!args[4]->IsUndefined() && args[4]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[4]));
    logger_cout(to_string(uuid).append("|uuid").c_str());
  }

  Local <String> frontAddr = args[0]->ToString();
  Local <String> szPath = args[1]->IsUndefined() ? String::NewFromUtf8(isolate, "t") : args[0]->ToString();
  String::Utf8Value addrUtf8(frontAddr);
  String::Utf8Value pathUtf8(szPath);
  int publicTopicType = args[2]->Int32Value();
  int privateTopicType = args[3]->Int32Value();

  UVConnectField pConnectField;
  memset(&pConnectField, 0, sizeof(pConnectField));
  strcpy(pConnectField.front_addr, ((std::string) * addrUtf8).c_str());
  strcpy(pConnectField.szPath, ((std::string) * pathUtf8).c_str());
  pConnectField.public_topic_type = publicTopicType;
  pConnectField.private_topic_type = privateTopicType;
  logger_cout(((std::string) * addrUtf8).append("|addrUtf8").c_str());
  logger_cout(((std::string) * pathUtf8).append("|pathUtf8").c_str());
  logger_cout(to_string(publicTopicType).append("|publicTopicType").c_str());
  logger_cout(to_string(privateTopicType).append("|privateTopicType").c_str());

  obj->uvTrader->Connect(&pConnectField, uuid, FunRtnCallback);
  return args.GetReturnValue().Set(String::NewFromUtf8(isolate, "finish exec connect"));
}
{$$3}
void CTPTrader::Disposed(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  CTPTrader *obj = ObjectWrap::Unwrap<CTPTrader>(args.Holder());
  obj->uvTrader->Disconnect();
  std::map < int, Persistent < Function > > ::iterator
  callback_it = callback_map.begin();
  while (callback_it != callback_map.end()) {
    //callback_it->second.Dispose();
    callback_it++;
  }
  event_map.clear();
  callback_map.clear();
  fun_rtncb_map.clear();
  delete obj->uvTrader;
  obj->uvTrader = NULL;
  logger_cout("wrap_trader Disposed------>wrap disposed");
  return ;
}

void CTPTrader::FunCallback(CbRtnField *data) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  std::map<int, Persistent<Function>>::iterator cIt = callback_map.find(data->eFlag);
  if (cIt == callback_map.end()) return;

  switch (data->eFlag) {
    case T_ONFRONTCONNECTED: {
      Local <Value> argv[1] = {Undefined(isolate)};
      Local <Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONFRONTDISCONNECTED: {
      Local <Value> argv[1] = {Integer::New(isolate, data->nReason)};
      Local <Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
{$$4}
    case T_ONRSPERROR: {
      Local <Value> argv[3];
      pkg_cb_onrsperror(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 3, argv);
      break;
    }
  }
}

void CTPTrader::FunRtnCallback(int result, void *baton) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LookupCtpApiBaton *tmp = static_cast<LookupCtpApiBaton *>(baton);
  if (tmp->uuid != -1) {
    std::map < int, Persistent < Function > > ::iterator
    it = fun_rtncb_map.find(tmp->uuid);

    const unsigned argc = 2;
    Local <Value> argv[argc] = {Integer::New(isolate, tmp->nResult), Integer::New(isolate, tmp->iRequestID)};

    Local <Function> fn = Local<Function>::New(isolate, it->second);
    fn->Call(isolate->GetCurrentContext()->Global(), argc, argv);
    it->second.Reset();
    fun_rtncb_map.erase(tmp->uuid);
  }
}
{$$5}
void CTPTrader::pkg_cb_onrsperror(CbRtnField* data, Local<Value>*cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  *cbArray = Number::New(isolate, data->nRequestID);
  *(cbArray + 1) = Boolean::New(isolate, data->bIsLast);
  *(cbArray + 2) = pkg_rspinfo(data->rspInfo);
  return;
}

Local <Value> CTPTrader::pkg_rspinfo(void *vpRspInfo) {
  Isolate *isolate = Isolate::GetCurrent();
  if (vpRspInfo) {
    CThostFtdcRspInfoField *pRspInfo = static_cast<CThostFtdcRspInfoField *>(vpRspInfo);
    Local <Object> jsonInfo = Object::New(isolate);
    jsonInfo->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspInfo->ErrorID));
    jsonInfo->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspInfo->ErrorMsg));
    return jsonInfo;
  }
  else {
    return Local<Value>::New(isolate, Undefined(isolate));
  }
}
`

const gen_h = (reqFuncs, resFuncs, base_file_dir) => {
  let rpl_1 = ''
  let rpl_2 = ''
  for (const reqFunc of reqFuncs) {
    rpl_1 += `  static void ${reqFunc[0]}(const FunctionCallbackInfo<Value>& args);\n`
  }
  for (const resFunc of resFuncs) {
    rpl_2 += `  static void pkg_cb_${resFunc[0].toLowerCase()}(CbRtnField* data, Local<Value>*cbArray);\n`
  }
  fs.writeFileSync(path.join(base_file_dir, './cpp/ctp_trader.h'), tpl_h.replace('{$$1}', rpl_1).replace('{$$2}', rpl_2))
}

const gen_c = (reqFuncs, resFuncs, base_file_dir) => {
  let rpl_1 = ''
  let rpl_2 = ''
  let rpl_3 = ''
  let rpl_4 = ''
  let rpl_5 = ''
  const filter_resFunc = ['OnFrontConnected', 'OnFrontDisconnected', 'OnHeartBeatWarning', 'OnRspError']

  for (const reqFunc of reqFuncs) {
    rpl_1 += `  NODE_SET_PROTOTYPE_METHOD(tpl, "${reqFunc[0]}", ${reqFunc[0]});\n`
  }

  for (const resFunc of resFuncs) {
    rpl_2 += `  event_map["${resFunc[0]}"] = T_${resFunc[0].toUpperCase()};\n`
  }

  const tpl_rpl_3 = `
void CTPTrader::{$func_name}(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader {$func_name}------>";

 if(args.Length() < 1 || !args[0]->IsObject()) {
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Error: Object arguments expected")));
    return;
  }
  int uuid = -1;
  CTPTrader *obj = ObjectWrap::Unwrap<CTPTrader>(args.Holder());
  if (!args[1]->IsUndefined() && args[1]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[1]));
    std::string _head = std::string(log);
    logger_cout(_head.append(" uuid is ").append(to_string(uuid)).c_str());
  }

  {$CTHostFtdcFieldType} req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

{$set_req}
  obj->uvTrader->{$func_name}(&req, uuid, FunRtnCallback);
  return ;
}
`
  for (const reqFunc of reqFuncs) {
    let rpl_3_1 = ''
    const func_name = reqFunc[0]
    const params = reqFunc[1].split(',').map(x => x.trim())
    const CTHostFtdcField = params[0]
    const CTHostFtdcFieldType = CTHostFtdcField.split(' ')[0]
    for (const field_key in ctp_field[CTHostFtdcFieldType]) {
      const field_type = ctp_field[CTHostFtdcFieldType][field_key]
      if (field_key === 'TThostFtdcBrokerIDType') {
        console.log(field_type, field_key)
      }
      if (field_type === 'int') {
        rpl_3_1 += `  setInt(jsonObj, String::NewFromUtf8(isolate, "${field_key}"), &req.${field_key});\n`
      } else if (field_type === 'double') {
        rpl_3_1 += `  setDouble(jsonObj, String::NewFromUtf8(isolate, "${field_key}"), &req.${field_key});\n`
      } else if (field_type === 'char') {
        rpl_3_1 += `  setChar(jsonObj, String::NewFromUtf8(isolate, "${field_key}"), &req.${field_key});\n`
      } else if (field_type === 'string') {
        rpl_3_1 += `  setString(jsonObj, String::NewFromUtf8(isolate, "${field_key}"), req.${field_key});\n`
      }
    }
    rpl_3 += tpl_rpl_3.replace('{$CTHostFtdcFieldType}', CTHostFtdcFieldType).replace('{$set_req}', rpl_3_1).split('{$func_name}').join(func_name)
  }

  for (const resFunc of resFuncs) {
    const func_name = resFunc[0]
    if (filter_resFunc.indexOf(func_name) >= 0) continue
    const cb_enum = `T_${resFunc[0].toUpperCase()}`
    const params = resFunc[1].split(',').map(x => x.trim())
    rpl_4 += `    case ${cb_enum}: {
      Local <Value> argv[${params.length}];
      pkg_cb_${func_name.toLowerCase()}(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), ${params.length}, argv);
      break;
    }
`
  }

  for (const resFunc of resFuncs) {
    const func_name = resFunc[0]
    if (filter_resFunc.indexOf(func_name) >= 0) continue
    const params = resFunc[1].split(',').map(x => x.trim())
    const CTHostFtdcField = params[0]
    const CTHostFtdcFieldType = CTHostFtdcField.split(' ')[0]
    const CTHostFtdcFieldValue = CTHostFtdcField.split(' ')[1].replace('*', '')
    let set_res = `
void CTPTrader::pkg_cb_${func_name.toLowerCase()}(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    ${CTHostFtdcFieldType} *${CTHostFtdcFieldValue} = static_cast<${CTHostFtdcFieldType} *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
`
    for (const field_key in ctp_field[CTHostFtdcFieldType]) {
      const field_type = ctp_field[CTHostFtdcFieldType][field_key]
      if (field_type === 'int') {
        set_res += `    jsonRtn->Set(String::NewFromUtf8(isolate, "${field_key}"), Number::New(isolate, ${CTHostFtdcFieldValue}->${field_key}));\n`
      } else if (field_type === 'double') {
        set_res += `    jsonRtn->Set(String::NewFromUtf8(isolate, "${field_key}"), Number::New(isolate, ${CTHostFtdcFieldValue}->${field_key}));\n`
      } else if (field_type === 'char') {
        set_res += `    jsonRtn->Set(String::NewFromUtf8(isolate, "${field_key}"), String::NewFromUtf8(isolate, charto_string(${CTHostFtdcFieldValue}->${field_key}).c_str()));\n`
      } else if (field_type === 'string') {
        set_res += `    jsonRtn->Set(String::NewFromUtf8(isolate, "${field_key}"), String::NewFromUtf8(isolate, ${CTHostFtdcFieldValue}->${field_key}));\n`
      }
    }
    set_res += '    *cbArray = jsonRtn;\n  } else {\n    *cbArray = Local<Value>::New(isolate, Undefined(isolate));\n  }\n'
    if (params.length === 2) {
      set_res += '  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);\n'
    } else if (params.length === 4) {
      set_res += '  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);\n  *(cbArray + 2) = Number::New(isolate, data->nRequestID);\n  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);\n'
    }
    set_res += '  return;\n}\n'
    rpl_5 += set_res
  }

  fs.writeFileSync(path.join(base_file_dir, './cpp/ctp_trader.cpp'), tpl_cpp.replace('{$$1}', rpl_1).replace('{$$2}', rpl_2).replace('{$$3}', rpl_3).replace('{$$4}', rpl_4).replace('{$$5}', rpl_5))
}

module.exports = (reqFuncs, resFuncs, base_file_dir) => {
  gen_h(reqFuncs, resFuncs, base_file_dir)
  gen_c(reqFuncs, resFuncs, base_file_dir)
}
