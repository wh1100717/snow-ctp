#include "ctp_market.h"

Persistent <Function> CTPMarket::constructor;
int CTPMarket::s_uuid;
std::map<std::string, int> CTPMarket::event_map;
std::map<int, Persistent<Function> > CTPMarket::callback_map;
std::map<int, Persistent<Function> > CTPMarket::fun_rtncb_map;

CTPMarket::CTPMarket(void) {
  logger_cout("ctp_market------>object start init");
  uvMarket = new uv_market();
  logger_cout("ctp_market------>object init successed");
}

CTPMarket::~CTPMarket(void) {
  if (uvMarket) {
    delete uvMarket;
  }
  logger_cout("ctp_market------>object destroyed");
}

void CTPMarket::New(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (event_map.size() == 0)
    initEventMap();

  if (args.IsConstructCall()) {
    CTPMarket *wMarket = new CTPMarket();
    wMarket->Wrap(args.This());
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

void CTPMarket::NewInstance(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  const unsigned argc = 1;
  Local <Value> argv[argc] = {Number::New(isolate, 0)};
  Local <Function> cons = Local<Function>::New(isolate, constructor);
  Local <Context> context = isolate->GetCurrentContext();
  Local <Object> instance = cons->NewInstance(context, argc, argv).ToLocalChecked();
  args.GetReturnValue().Set(instance);
}

void CTPMarket::Init(Isolate *isolate) {
  // Prepare constructor template
  Local <FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "CTPMarket"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "GetTradingDay", GetTradingDay);
  NODE_SET_PROTOTYPE_METHOD(tpl, "Connect", Connect);
  NODE_SET_PROTOTYPE_METHOD(tpl, "On", On);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqUserLogin", ReqUserLogin);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqUserLogout", ReqUserLogout);

  NODE_SET_PROTOTYPE_METHOD(tpl, "SubscribeMarketData", SubscribeMarketData);
  NODE_SET_PROTOTYPE_METHOD(tpl, "UnSubscribeMarketData", UnSubscribeMarketData);
  NODE_SET_PROTOTYPE_METHOD(tpl, "SubscribeForQuoteRsp", SubscribeForQuoteRsp);
  NODE_SET_PROTOTYPE_METHOD(tpl, "UnSubscribeForQuoteRsp", UnSubscribeForQuoteRsp);

  constructor.Reset(isolate, tpl->GetFunction());
}

void CTPMarket::initEventMap() {
  event_map["OnFrontConnected"] = T_ONFRONTCONNECTED;
  event_map["OnFrontDisconnected"] = T_ONFRONTDISCONNECTED;
  event_map["OnHeartBeatWarning"] = T_ONHEARTBEATWARNING;
  event_map["OnRspUserLogin"] = T_ONRSPUSERLOGIN;
  event_map["OnRspUserLogout"] = T_ONRSPUSERLOGOUT;

  event_map["OnRspSubMarketData"] = T_ONRSPSUBMARKETDATA;
  event_map["OnRspUnSubMarketData"] = T_ONRSPUNSUBMARKETDATA;
  event_map["OnRspSubForQuoteRsp"] = T_ONRSPSUBFORQUOTERSP;
  event_map["OnRspUnSubForQuoteRsp"] = T_ONRSPUNSUBFORQUOTERSP;
  event_map["OnRtnDepthMarketData"] = T_ONRTNDEPTHMARKETDATA;
  event_map["OnRtnForQuoteRsp"] = T_ONRTNFORQUOTERSP;

}

void CTPMarket::GetTradingDay(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  CTPMarket *wMarket = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  const char *tradingDay = wMarket->uvMarket->GetTradingDay();
  logger_cout("GetTradingDay:");
  logger_cout(tradingDay);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, tradingDay));
}

void CTPMarket::On(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args[0]->IsUndefined() || args[1]->IsUndefined()) {
    logger_cout("Wrong arguments->event name or function");
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->event name or function")));
    return;
  }

  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());

  Local <String> eventName = args[0]->ToString();
  Local <Function> cb = Local<Function>::Cast(args[1]);

  String::Utf8Value eNameAscii(eventName);

  std::map<std::string, int>::iterator eIt = event_map.find((std::string) * eNameAscii);
  if (eIt == event_map.end()) {
    logger_cout("System has not register this event");
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "System has no register this event")));
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
  obj->uvMarket->On(*eNameAscii, eIt->second, FunCallback);
  return args.GetReturnValue().Set(String::NewFromUtf8(isolate, "finish exec on"));
}

void CTPMarket::Connect(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args[0]->IsUndefined()) {
    logger_cout("Wrong arguments->front addr");
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->front addr")));
    return;
  }
  if (!args[2]->IsNumber() || !args[3]->IsNumber()) {
    logger_cout("Wrong arguments->public or private topic type");
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->public or private topic type")));
    return;
  }
  int uuid = -1;
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
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

  obj->uvMarket->Connect(&pConnectField, uuid, FunRtnCallback);
  return args.GetReturnValue().Set(String::NewFromUtf8(isolate, "finish exec connect"));
}

void CTPMarket::ReqUserLogin(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_market ReqUserLogin------>";

 if(args.Length() < 1 || !args[0]->IsObject()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Error: Object arguments expected")));
    return;
  }
  int uuid = -1;
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  if (!args[1]->IsUndefined() && args[1]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[1]));
    std::string _head = std::string(log);
    logger_cout(_head.append(" uuid is ").append(to_string(uuid)).c_str());
  }

  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();
  Local<Array> props = jsonObj->GetOwnPropertyNames();

  setString(jsonObj, String::NewFromUtf8(isolate, "TradingDay"), req.TradingDay);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "Password"), req.Password);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserProductInfo"), req.UserProductInfo);
  setString(jsonObj, String::NewFromUtf8(isolate, "InterfaceProductInfo"), req.InterfaceProductInfo);
  setString(jsonObj, String::NewFromUtf8(isolate, "ProtocolInfo"), req.ProtocolInfo);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "OneTimePassword"), req.OneTimePassword);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientIPAddress"), req.ClientIPAddress);

  obj->uvMarket->ReqUserLogin(&req, uuid, FunRtnCallback);
  return ;
}

void CTPMarket::ReqUserLogout(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_market ReqUserLogout------>";

 if(args.Length() < 1 || !args[0]->IsObject()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Error: Object arguments expected")));
    return;
  }
  int uuid = -1;
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  if (!args[1]->IsUndefined() && args[1]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[1]));
    std::string _head = std::string(log);
    logger_cout(_head.append(" uuid is ").append(to_string(uuid)).c_str());
  }

  CThostFtdcUserLogoutField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();
  Local<Array> props = jsonObj->GetOwnPropertyNames();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);

  obj->uvMarket->ReqUserLogout(&req, uuid, FunRtnCallback);
  return;
}

void CTPMarket::SubscribeMarketData(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_market SubscribeMarketData------>";

	if (args[0]->IsUndefined() || !args[0]->IsArray()) {
		std::string _head = std::string(log);
		logger_cout(_head.append(" Wrong arguments").c_str());
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

  int uuid = -1;
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  if (!args[1]->IsUndefined() && args[1]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[1]));
    std::string _head = std::string(log);
    logger_cout(_head.append(" uuid is ").append(to_string(uuid)).c_str());
  }

	Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
	char** idArray = new char*[instrumentIDs->Length()];
	
	for (uint32_t i = 0; i < instrumentIDs->Length(); i++) {
		Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
    std::string val = *String::Utf8Value(instrumentId);
		char* id = new char[instrumentId->Length() + 1];
		strcpy(id, val.c_str());
		idArray[i] = id;
		log.append(id).append("|");
	}
	logger_cout(log.c_str());
	obj->uvMarket->SubscribeMarketData(idArray, instrumentIDs->Length(), uuid, FunRtnCallback);
	delete idArray;
  return;
}

void CTPMarket::UnSubscribeMarketData(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_market UnSubscribeMarketData------>";

	if (args[0]->IsUndefined() || !args[0]->IsArray()) {
		std::string _head = std::string(log);
		logger_cout(_head.append(" Wrong arguments").c_str());
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

  int uuid = -1;
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  if (!args[1]->IsUndefined() && args[1]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[1]));
    std::string _head = std::string(log);
    logger_cout(_head.append(" uuid is ").append(to_string(uuid)).c_str());
  }

	Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
	char** idArray = new char*[instrumentIDs->Length()];
	
	for (uint32_t i = 0; i < instrumentIDs->Length(); i++) {
		Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
    std::string val = *String::Utf8Value(instrumentId);
		char* id = new char[instrumentId->Length() + 1];
		strcpy(id, val.c_str());
		idArray[i] = id;
		log.append(id).append("|");
	}
	logger_cout(log.c_str());
	obj->uvMarket->UnSubscribeMarketData(idArray, instrumentIDs->Length(), uuid, FunRtnCallback);
	delete idArray;
  return;
}

void CTPMarket::SubscribeForQuoteRsp(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_market SubscribeForQuoteRsp------>";

	if (args[0]->IsUndefined() || !args[0]->IsArray()) {
		std::string _head = std::string(log);
		logger_cout(_head.append(" Wrong arguments").c_str());
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

  int uuid = -1;
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  if (!args[1]->IsUndefined() && args[1]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[1]));
    std::string _head = std::string(log);
    logger_cout(_head.append(" uuid is ").append(to_string(uuid)).c_str());
  }

	Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
	char** idArray = new char*[instrumentIDs->Length()];
	
	for (uint32_t i = 0; i < instrumentIDs->Length(); i++) {
		Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
    std::string val = *String::Utf8Value(instrumentId);
		char* id = new char[instrumentId->Length() + 1];
		strcpy(id, val.c_str());
		idArray[i] = id;
		log.append(id).append("|");
	}
	logger_cout(log.c_str());
	obj->uvMarket->SubscribeForQuoteRsp(idArray, instrumentIDs->Length(), uuid, FunRtnCallback);
	delete idArray;
  return;
}

void CTPMarket::UnSubscribeForQuoteRsp(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_market UnSubscribeForQuoteRsp------>";

	if (args[0]->IsUndefined() || !args[0]->IsArray()) {
		std::string _head = std::string(log);
		logger_cout(_head.append(" Wrong arguments").c_str());
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

  int uuid = -1;
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  if (!args[1]->IsUndefined() && args[1]->IsFunction()) {
    uuid = ++s_uuid;
    fun_rtncb_map[uuid].Reset(isolate, Local<Function>::Cast(args[1]));
    std::string _head = std::string(log);
    logger_cout(_head.append(" uuid is ").append(to_string(uuid)).c_str());
  }

	Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
	char** idArray = new char*[instrumentIDs->Length()];
	
	for (uint32_t i = 0; i < instrumentIDs->Length(); i++) {
		Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
    std::string val = *String::Utf8Value(instrumentId);
		char* id = new char[instrumentId->Length() + 1];
		strcpy(id, val.c_str());
		idArray[i] = id;
		log.append(id).append("|");
	}
	logger_cout(log.c_str());
	obj->uvMarket->UnSubscribeForQuoteRsp(idArray, instrumentIDs->Length(), uuid, FunRtnCallback);
	delete idArray;
  return;
}

void CTPMarket::Disposed(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  CTPMarket *obj = ObjectWrap::Unwrap<CTPMarket>(args.Holder());
  obj->uvMarket->Disconnect();
  std::map < int, Persistent < Function > > ::iterator
  callback_it = callback_map.begin();
  while (callback_it != callback_map.end()) {
    //callback_it->second.Dispose();
    callback_it++;
  }
  event_map.clear();
  callback_map.clear();
  fun_rtncb_map.clear();
  delete obj->uvMarket;
  obj->uvMarket = NULL;
  logger_cout("wrap_market Disposed------>wrap disposed");
  return ;
}

void CTPMarket::FunCallback(CbRtnField *data) {
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
    case T_ONRSPUSERLOGIN: {
      Local <Value> argv[4];
      pkg_cb_onrspuserlogin(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPUSERLOGOUT: {
      Local <Value> argv[4];
      pkg_cb_onrspuserlogout(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPERROR: {
      Local <Value> argv[3];
      pkg_cb_onrsperror(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 3, argv);
      break;
    }
    case T_ONRSPSUBMARKETDATA: {
      Local <Value> argv[4];
      pkg_cb_onrspsubmarketdata(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPUNSUBMARKETDATA: {
      Local <Value> argv[4];
      pkg_cb_onrspunsubmarketdata(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPSUBFORQUOTERSP: {
      Local <Value> argv[4];
      pkg_cb_onrspsubforquotersp(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPUNSUBFORQUOTERSP: {
      Local <Value> argv[4];
      pkg_cb_onrspunsubforquotersp(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRTNDEPTHMARKETDATA: {
      Local<Value> argv[1];
      pkg_cb_onrtndepthmarketdata(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNFORQUOTERSP: {
      Local<Value> argv[1];
      pkg_cb_onrtnforquotersp(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
  }
}

void CTPMarket::FunRtnCallback(int result, void *baton) {
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

void CTPMarket::pkg_cb_onrspuserlogin(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspUserLoginField *pRspUserLogin = static_cast<CThostFtdcRspUserLoginField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspUserLogin->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LoginTime"), String::NewFromUtf8(isolate, pRspUserLogin->LoginTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspUserLogin->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspUserLogin->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SystemName"), String::NewFromUtf8(isolate, pRspUserLogin->SystemName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pRspUserLogin->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspUserLogin->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MaxOrderRef"), String::NewFromUtf8(isolate, pRspUserLogin->MaxOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SHFETime"), String::NewFromUtf8(isolate, pRspUserLogin->SHFETime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DCETime"), String::NewFromUtf8(isolate, pRspUserLogin->DCETime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CZCETime"), String::NewFromUtf8(isolate, pRspUserLogin->CZCETime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FFEXTime"), String::NewFromUtf8(isolate, pRspUserLogin->FFEXTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "INETime"), String::NewFromUtf8(isolate, pRspUserLogin->INETime));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPMarket::pkg_cb_onrspuserlogout(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcUserLogoutField *pUserLogout = static_cast<CThostFtdcUserLogoutField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pUserLogout->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pUserLogout->UserID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPMarket::pkg_cb_onrspsubmarketdata(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
  	CThostFtdcSpecificInstrumentField *pSpecificInstrument = static_cast<CThostFtdcSpecificInstrumentField*>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPMarket::pkg_cb_onrspunsubmarketdata(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
  	CThostFtdcSpecificInstrumentField *pSpecificInstrument = static_cast<CThostFtdcSpecificInstrumentField*>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPMarket::pkg_cb_onrspsubforquotersp(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
  	CThostFtdcSpecificInstrumentField *pSpecificInstrument = static_cast<CThostFtdcSpecificInstrumentField*>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPMarket::pkg_cb_onrspunsubforquotersp(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
  	CThostFtdcSpecificInstrumentField *pSpecificInstrument = static_cast<CThostFtdcSpecificInstrumentField*>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPMarket::pkg_cb_onrtndepthmarketdata(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
  	CThostFtdcDepthMarketDataField *pDepthMarketData = static_cast<CThostFtdcDepthMarketDataField*>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
		jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pDepthMarketData->TradingDay));
		jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pDepthMarketData->InstrumentID));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pDepthMarketData->ExchangeID));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pDepthMarketData->ExchangeInstID));
		jsonRtn->Set(String::NewFromUtf8(isolate, "LastPrice"), Number::New(isolate, pDepthMarketData->LastPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "PreSettlementPrice"), Number::New(isolate, pDepthMarketData->PreSettlementPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "PreClosePrice"), Number::New(isolate, pDepthMarketData->PreClosePrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "PreOpenInterest"), Number::New(isolate, pDepthMarketData->PreOpenInterest));
		jsonRtn->Set(String::NewFromUtf8(isolate, "OpenPrice"), Number::New(isolate, pDepthMarketData->OpenPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "HighestPrice"), Number::New(isolate, pDepthMarketData->HighestPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "LowestPrice"), Number::New(isolate, pDepthMarketData->LowestPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Int32::New(isolate, pDepthMarketData->Volume));
		jsonRtn->Set(String::NewFromUtf8(isolate, "Turnover"), Number::New(isolate, pDepthMarketData->Turnover));
		jsonRtn->Set(String::NewFromUtf8(isolate, "OpenInterest"), Number::New(isolate, pDepthMarketData->OpenInterest));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ClosePrice"), Number::New(isolate, pDepthMarketData->ClosePrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementPrice"), Number::New(isolate, pDepthMarketData->SettlementPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "UpperLimitPrice"), Number::New(isolate, pDepthMarketData->UpperLimitPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "LowerLimitPrice"), Number::New(isolate, pDepthMarketData->LowerLimitPrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "PreDelta"), Number::New(isolate, pDepthMarketData->PreDelta));
		jsonRtn->Set(String::NewFromUtf8(isolate, "CurrDelta"), Number::New(isolate, pDepthMarketData->CurrDelta));
		jsonRtn->Set(String::NewFromUtf8(isolate, "UpdateTime"), String::NewFromUtf8(isolate, pDepthMarketData->UpdateTime));
		jsonRtn->Set(String::NewFromUtf8(isolate, "UpdateMillisec"), Number::New(isolate, pDepthMarketData->UpdateMillisec));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidPrice1"), Number::New(isolate, pDepthMarketData->BidPrice1));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume1"), Number::New(isolate, pDepthMarketData->BidVolume1));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskPrice1"), Number::New(isolate, pDepthMarketData->AskPrice1));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume1"), Number::New(isolate, pDepthMarketData->AskVolume1));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidPrice2"), Number::New(isolate, pDepthMarketData->BidPrice2));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume2"), Number::New(isolate, pDepthMarketData->BidVolume2));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskPrice2"), Number::New(isolate, pDepthMarketData->AskPrice2));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume2"), Number::New(isolate, pDepthMarketData->AskVolume2));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidPrice3"), Number::New(isolate, pDepthMarketData->BidPrice3));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume3"), Number::New(isolate, pDepthMarketData->BidVolume3));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskPrice3"), Number::New(isolate, pDepthMarketData->AskPrice3));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume3"), Number::New(isolate, pDepthMarketData->AskVolume3));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidPrice4"), Number::New(isolate, pDepthMarketData->BidPrice4));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume4"), Number::New(isolate, pDepthMarketData->BidVolume4));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskPrice4"), Number::New(isolate, pDepthMarketData->AskPrice4));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume4"), Number::New(isolate, pDepthMarketData->AskVolume4));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidPrice5"), Number::New(isolate, pDepthMarketData->BidPrice5));
		jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume5"), Number::New(isolate, pDepthMarketData->BidVolume5));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskPrice5"), Number::New(isolate, pDepthMarketData->AskPrice5));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume5"), Number::New(isolate, pDepthMarketData->AskVolume5));
		jsonRtn->Set(String::NewFromUtf8(isolate, "AveragePrice"), Number::New(isolate, pDepthMarketData->AveragePrice));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDay"), String::NewFromUtf8(isolate, pDepthMarketData->ActionDay));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPMarket::pkg_cb_onrtnforquotersp(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcForQuoteRspField *pForQuoteRspField = static_cast<CThostFtdcForQuoteRspField*>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
		jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pForQuoteRspField->TradingDay));
		jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pForQuoteRspField->InstrumentID));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteSysID"), String::NewFromUtf8(isolate, pForQuoteRspField->ForQuoteSysID));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteTime"), String::NewFromUtf8(isolate, pForQuoteRspField->ForQuoteTime));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDay"), String::NewFromUtf8(isolate, pForQuoteRspField->ActionDay));
		jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pForQuoteRspField->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPMarket::pkg_cb_onrsperror(CbRtnField* data, Local<Value>*cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  *cbArray = Number::New(isolate, data->nRequestID);
  *(cbArray + 1) = Boolean::New(isolate, data->bIsLast);
  *(cbArray + 2) = pkg_rspinfo(data->rspInfo);
  return;
}

Local <Value> CTPMarket::pkg_rspinfo(void *vpRspInfo) {
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
