
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqAuthenticate", ReqAuthenticate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqUserLogin", ReqUserLogin);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqUserLogout", ReqUserLogout);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqUserPasswordUpdate", ReqUserPasswordUpdate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqTradingAccountPasswordUpdate", ReqTradingAccountPasswordUpdate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqOrderInsert", ReqOrderInsert);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqParkedOrderInsert", ReqParkedOrderInsert);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqParkedOrderAction", ReqParkedOrderAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqOrderAction", ReqOrderAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQueryMaxOrderVolume", ReqQueryMaxOrderVolume);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqSettlementInfoConfirm", ReqSettlementInfoConfirm);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqRemoveParkedOrder", ReqRemoveParkedOrder);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqRemoveParkedOrderAction", ReqRemoveParkedOrderAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqExecOrderInsert", ReqExecOrderInsert);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqExecOrderAction", ReqExecOrderAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqForQuoteInsert", ReqForQuoteInsert);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQuoteInsert", ReqQuoteInsert);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQuoteAction", ReqQuoteAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqBatchOrderAction", ReqBatchOrderAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqOptionSelfCloseInsert", ReqOptionSelfCloseInsert);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqOptionSelfCloseAction", ReqOptionSelfCloseAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqCombActionInsert", ReqCombActionInsert);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryOrder", ReqQryOrder);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryTrade", ReqQryTrade);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInvestorPosition", ReqQryInvestorPosition);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryTradingAccount", ReqQryTradingAccount);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInvestor", ReqQryInvestor);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryTradingCode", ReqQryTradingCode);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInstrumentMarginRate", ReqQryInstrumentMarginRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInstrumentCommissionRate", ReqQryInstrumentCommissionRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryExchange", ReqQryExchange);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryProduct", ReqQryProduct);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInstrument", ReqQryInstrument);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryDepthMarketData", ReqQryDepthMarketData);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQrySettlementInfo", ReqQrySettlementInfo);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryTransferBank", ReqQryTransferBank);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInvestorPositionDetail", ReqQryInvestorPositionDetail);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryNotice", ReqQryNotice);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQrySettlementInfoConfirm", ReqQrySettlementInfoConfirm);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInvestorPositionCombineDetail", ReqQryInvestorPositionCombineDetail);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryCFMMCTradingAccountKey", ReqQryCFMMCTradingAccountKey);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryEWarrantOffset", ReqQryEWarrantOffset);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInvestorProductGroupMargin", ReqQryInvestorProductGroupMargin);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryExchangeMarginRate", ReqQryExchangeMarginRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryExchangeMarginRateAdjust", ReqQryExchangeMarginRateAdjust);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryExchangeRate", ReqQryExchangeRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQrySecAgentACIDMap", ReqQrySecAgentACIDMap);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryProductExchRate", ReqQryProductExchRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryProductGroup", ReqQryProductGroup);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryMMInstrumentCommissionRate", ReqQryMMInstrumentCommissionRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryMMOptionInstrCommRate", ReqQryMMOptionInstrCommRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInstrumentOrderCommRate", ReqQryInstrumentOrderCommRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQrySecAgentTradingAccount", ReqQrySecAgentTradingAccount);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQrySecAgentCheckMode", ReqQrySecAgentCheckMode);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryOptionInstrTradeCost", ReqQryOptionInstrTradeCost);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryOptionInstrCommRate", ReqQryOptionInstrCommRate);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryExecOrder", ReqQryExecOrder);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryForQuote", ReqQryForQuote);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryQuote", ReqQryQuote);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryOptionSelfClose", ReqQryOptionSelfClose);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryInvestUnit", ReqQryInvestUnit);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryCombInstrumentGuard", ReqQryCombInstrumentGuard);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryCombAction", ReqQryCombAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryTransferSerial", ReqQryTransferSerial);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryAccountregister", ReqQryAccountregister);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryContractBank", ReqQryContractBank);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryParkedOrder", ReqQryParkedOrder);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryParkedOrderAction", ReqQryParkedOrderAction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryTradingNotice", ReqQryTradingNotice);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryBrokerTradingParams", ReqQryBrokerTradingParams);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQryBrokerTradingAlgos", ReqQryBrokerTradingAlgos);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQueryCFMMCTradingAccountToken", ReqQueryCFMMCTradingAccountToken);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqFromBankToFutureByFuture", ReqFromBankToFutureByFuture);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqFromFutureToBankByFuture", ReqFromFutureToBankByFuture);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReqQueryBankAccountMoneyByFuture", ReqQueryBankAccountMoneyByFuture);

  constructor.Reset(isolate, tpl->GetFunction());
}

void CTPTrader::initEventMap() {
  event_map["OnFrontConnected"] = T_ONFRONTCONNECTED;
  event_map["OnFrontDisconnected"] = T_ONFRONTDISCONNECTED;
  event_map["OnHeartBeatWarning"] = T_ONHEARTBEATWARNING;
  event_map["OnRspAuthenticate"] = T_ONRSPAUTHENTICATE;
  event_map["OnRspUserLogin"] = T_ONRSPUSERLOGIN;
  event_map["OnRspUserLogout"] = T_ONRSPUSERLOGOUT;
  event_map["OnRspUserPasswordUpdate"] = T_ONRSPUSERPASSWORDUPDATE;
  event_map["OnRspTradingAccountPasswordUpdate"] = T_ONRSPTRADINGACCOUNTPASSWORDUPDATE;
  event_map["OnRspOrderInsert"] = T_ONRSPORDERINSERT;
  event_map["OnRspParkedOrderInsert"] = T_ONRSPPARKEDORDERINSERT;
  event_map["OnRspParkedOrderAction"] = T_ONRSPPARKEDORDERACTION;
  event_map["OnRspOrderAction"] = T_ONRSPORDERACTION;
  event_map["OnRspQueryMaxOrderVolume"] = T_ONRSPQUERYMAXORDERVOLUME;
  event_map["OnRspSettlementInfoConfirm"] = T_ONRSPSETTLEMENTINFOCONFIRM;
  event_map["OnRspRemoveParkedOrder"] = T_ONRSPREMOVEPARKEDORDER;
  event_map["OnRspRemoveParkedOrderAction"] = T_ONRSPREMOVEPARKEDORDERACTION;
  event_map["OnRspExecOrderInsert"] = T_ONRSPEXECORDERINSERT;
  event_map["OnRspExecOrderAction"] = T_ONRSPEXECORDERACTION;
  event_map["OnRspForQuoteInsert"] = T_ONRSPFORQUOTEINSERT;
  event_map["OnRspQuoteInsert"] = T_ONRSPQUOTEINSERT;
  event_map["OnRspQuoteAction"] = T_ONRSPQUOTEACTION;
  event_map["OnRspBatchOrderAction"] = T_ONRSPBATCHORDERACTION;
  event_map["OnRspOptionSelfCloseInsert"] = T_ONRSPOPTIONSELFCLOSEINSERT;
  event_map["OnRspOptionSelfCloseAction"] = T_ONRSPOPTIONSELFCLOSEACTION;
  event_map["OnRspCombActionInsert"] = T_ONRSPCOMBACTIONINSERT;
  event_map["OnRspQryOrder"] = T_ONRSPQRYORDER;
  event_map["OnRspQryTrade"] = T_ONRSPQRYTRADE;
  event_map["OnRspQryInvestorPosition"] = T_ONRSPQRYINVESTORPOSITION;
  event_map["OnRspQryTradingAccount"] = T_ONRSPQRYTRADINGACCOUNT;
  event_map["OnRspQryInvestor"] = T_ONRSPQRYINVESTOR;
  event_map["OnRspQryTradingCode"] = T_ONRSPQRYTRADINGCODE;
  event_map["OnRspQryInstrumentMarginRate"] = T_ONRSPQRYINSTRUMENTMARGINRATE;
  event_map["OnRspQryInstrumentCommissionRate"] = T_ONRSPQRYINSTRUMENTCOMMISSIONRATE;
  event_map["OnRspQryExchange"] = T_ONRSPQRYEXCHANGE;
  event_map["OnRspQryProduct"] = T_ONRSPQRYPRODUCT;
  event_map["OnRspQryInstrument"] = T_ONRSPQRYINSTRUMENT;
  event_map["OnRspQryDepthMarketData"] = T_ONRSPQRYDEPTHMARKETDATA;
  event_map["OnRspQrySettlementInfo"] = T_ONRSPQRYSETTLEMENTINFO;
  event_map["OnRspQryTransferBank"] = T_ONRSPQRYTRANSFERBANK;
  event_map["OnRspQryInvestorPositionDetail"] = T_ONRSPQRYINVESTORPOSITIONDETAIL;
  event_map["OnRspQryNotice"] = T_ONRSPQRYNOTICE;
  event_map["OnRspQrySettlementInfoConfirm"] = T_ONRSPQRYSETTLEMENTINFOCONFIRM;
  event_map["OnRspQryInvestorPositionCombineDetail"] = T_ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL;
  event_map["OnRspQryCFMMCTradingAccountKey"] = T_ONRSPQRYCFMMCTRADINGACCOUNTKEY;
  event_map["OnRspQryEWarrantOffset"] = T_ONRSPQRYEWARRANTOFFSET;
  event_map["OnRspQryInvestorProductGroupMargin"] = T_ONRSPQRYINVESTORPRODUCTGROUPMARGIN;
  event_map["OnRspQryExchangeMarginRate"] = T_ONRSPQRYEXCHANGEMARGINRATE;
  event_map["OnRspQryExchangeMarginRateAdjust"] = T_ONRSPQRYEXCHANGEMARGINRATEADJUST;
  event_map["OnRspQryExchangeRate"] = T_ONRSPQRYEXCHANGERATE;
  event_map["OnRspQrySecAgentACIDMap"] = T_ONRSPQRYSECAGENTACIDMAP;
  event_map["OnRspQryProductExchRate"] = T_ONRSPQRYPRODUCTEXCHRATE;
  event_map["OnRspQryProductGroup"] = T_ONRSPQRYPRODUCTGROUP;
  event_map["OnRspQryMMInstrumentCommissionRate"] = T_ONRSPQRYMMINSTRUMENTCOMMISSIONRATE;
  event_map["OnRspQryMMOptionInstrCommRate"] = T_ONRSPQRYMMOPTIONINSTRCOMMRATE;
  event_map["OnRspQryInstrumentOrderCommRate"] = T_ONRSPQRYINSTRUMENTORDERCOMMRATE;
  event_map["OnRspQrySecAgentTradingAccount"] = T_ONRSPQRYSECAGENTTRADINGACCOUNT;
  event_map["OnRspQrySecAgentCheckMode"] = T_ONRSPQRYSECAGENTCHECKMODE;
  event_map["OnRspQryOptionInstrTradeCost"] = T_ONRSPQRYOPTIONINSTRTRADECOST;
  event_map["OnRspQryOptionInstrCommRate"] = T_ONRSPQRYOPTIONINSTRCOMMRATE;
  event_map["OnRspQryExecOrder"] = T_ONRSPQRYEXECORDER;
  event_map["OnRspQryForQuote"] = T_ONRSPQRYFORQUOTE;
  event_map["OnRspQryQuote"] = T_ONRSPQRYQUOTE;
  event_map["OnRspQryOptionSelfClose"] = T_ONRSPQRYOPTIONSELFCLOSE;
  event_map["OnRspQryInvestUnit"] = T_ONRSPQRYINVESTUNIT;
  event_map["OnRspQryCombInstrumentGuard"] = T_ONRSPQRYCOMBINSTRUMENTGUARD;
  event_map["OnRspQryCombAction"] = T_ONRSPQRYCOMBACTION;
  event_map["OnRspQryTransferSerial"] = T_ONRSPQRYTRANSFERSERIAL;
  event_map["OnRspQryAccountregister"] = T_ONRSPQRYACCOUNTREGISTER;
  event_map["OnRspError"] = T_ONRSPERROR;
  event_map["OnRtnOrder"] = T_ONRTNORDER;
  event_map["OnRtnTrade"] = T_ONRTNTRADE;
  event_map["OnErrRtnOrderInsert"] = T_ONERRRTNORDERINSERT;
  event_map["OnErrRtnOrderAction"] = T_ONERRRTNORDERACTION;
  event_map["OnRtnInstrumentStatus"] = T_ONRTNINSTRUMENTSTATUS;
  event_map["OnRtnBulletin"] = T_ONRTNBULLETIN;
  event_map["OnRtnTradingNotice"] = T_ONRTNTRADINGNOTICE;
  event_map["OnRtnErrorConditionalOrder"] = T_ONRTNERRORCONDITIONALORDER;
  event_map["OnRtnExecOrder"] = T_ONRTNEXECORDER;
  event_map["OnErrRtnExecOrderInsert"] = T_ONERRRTNEXECORDERINSERT;
  event_map["OnErrRtnExecOrderAction"] = T_ONERRRTNEXECORDERACTION;
  event_map["OnErrRtnForQuoteInsert"] = T_ONERRRTNFORQUOTEINSERT;
  event_map["OnRtnQuote"] = T_ONRTNQUOTE;
  event_map["OnErrRtnQuoteInsert"] = T_ONERRRTNQUOTEINSERT;
  event_map["OnErrRtnQuoteAction"] = T_ONERRRTNQUOTEACTION;
  event_map["OnRtnForQuoteRsp"] = T_ONRTNFORQUOTERSP;
  event_map["OnRtnCFMMCTradingAccountToken"] = T_ONRTNCFMMCTRADINGACCOUNTTOKEN;
  event_map["OnErrRtnBatchOrderAction"] = T_ONERRRTNBATCHORDERACTION;
  event_map["OnRtnOptionSelfClose"] = T_ONRTNOPTIONSELFCLOSE;
  event_map["OnErrRtnOptionSelfCloseInsert"] = T_ONERRRTNOPTIONSELFCLOSEINSERT;
  event_map["OnErrRtnOptionSelfCloseAction"] = T_ONERRRTNOPTIONSELFCLOSEACTION;
  event_map["OnRtnCombAction"] = T_ONRTNCOMBACTION;
  event_map["OnErrRtnCombActionInsert"] = T_ONERRRTNCOMBACTIONINSERT;
  event_map["OnRspQryContractBank"] = T_ONRSPQRYCONTRACTBANK;
  event_map["OnRspQryParkedOrder"] = T_ONRSPQRYPARKEDORDER;
  event_map["OnRspQryParkedOrderAction"] = T_ONRSPQRYPARKEDORDERACTION;
  event_map["OnRspQryTradingNotice"] = T_ONRSPQRYTRADINGNOTICE;
  event_map["OnRspQryBrokerTradingParams"] = T_ONRSPQRYBROKERTRADINGPARAMS;
  event_map["OnRspQryBrokerTradingAlgos"] = T_ONRSPQRYBROKERTRADINGALGOS;
  event_map["OnRspQueryCFMMCTradingAccountToken"] = T_ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN;
  event_map["OnRtnFromBankToFutureByBank"] = T_ONRTNFROMBANKTOFUTUREBYBANK;
  event_map["OnRtnFromFutureToBankByBank"] = T_ONRTNFROMFUTURETOBANKBYBANK;
  event_map["OnRtnRepealFromBankToFutureByBank"] = T_ONRTNREPEALFROMBANKTOFUTUREBYBANK;
  event_map["OnRtnRepealFromFutureToBankByBank"] = T_ONRTNREPEALFROMFUTURETOBANKBYBANK;
  event_map["OnRtnFromBankToFutureByFuture"] = T_ONRTNFROMBANKTOFUTUREBYFUTURE;
  event_map["OnRtnFromFutureToBankByFuture"] = T_ONRTNFROMFUTURETOBANKBYFUTURE;
  event_map["OnRtnRepealFromBankToFutureByFutureManual"] = T_ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL;
  event_map["OnRtnRepealFromFutureToBankByFutureManual"] = T_ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL;
  event_map["OnRtnQueryBankBalanceByFuture"] = T_ONRTNQUERYBANKBALANCEBYFUTURE;
  event_map["OnErrRtnBankToFutureByFuture"] = T_ONERRRTNBANKTOFUTUREBYFUTURE;
  event_map["OnErrRtnFutureToBankByFuture"] = T_ONERRRTNFUTURETOBANKBYFUTURE;
  event_map["OnErrRtnRepealBankToFutureByFutureManual"] = T_ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL;
  event_map["OnErrRtnRepealFutureToBankByFutureManual"] = T_ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL;
  event_map["OnErrRtnQueryBankBalanceByFuture"] = T_ONERRRTNQUERYBANKBALANCEBYFUTURE;
  event_map["OnRtnRepealFromBankToFutureByFuture"] = T_ONRTNREPEALFROMBANKTOFUTUREBYFUTURE;
  event_map["OnRtnRepealFromFutureToBankByFuture"] = T_ONRTNREPEALFROMFUTURETOBANKBYFUTURE;
  event_map["OnRspFromBankToFutureByFuture"] = T_ONRSPFROMBANKTOFUTUREBYFUTURE;
  event_map["OnRspFromFutureToBankByFuture"] = T_ONRSPFROMFUTURETOBANKBYFUTURE;
  event_map["OnRspQueryBankAccountMoneyByFuture"] = T_ONRSPQUERYBANKACCOUNTMONEYBYFUTURE;
  event_map["OnRtnOpenAccountByBank"] = T_ONRTNOPENACCOUNTBYBANK;
  event_map["OnRtnCancelAccountByBank"] = T_ONRTNCANCELACCOUNTBYBANK;
  event_map["OnRtnChangeAccountByBank"] = T_ONRTNCHANGEACCOUNTBYBANK;

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

void CTPTrader::ReqAuthenticate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqAuthenticate------>";

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

  CThostFtdcReqAuthenticateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserProductInfo"), req.UserProductInfo);
  setString(jsonObj, String::NewFromUtf8(isolate, "AuthCode"), req.AuthCode);

  obj->uvTrader->ReqAuthenticate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqUserLogin(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqUserLogin------>";

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

  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

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

  obj->uvTrader->ReqUserLogin(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqUserLogout(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqUserLogout------>";

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

  CThostFtdcUserLogoutField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);

  obj->uvTrader->ReqUserLogout(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqUserPasswordUpdate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqUserPasswordUpdate------>";

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

  CThostFtdcUserPasswordUpdateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OldPassword"), req.OldPassword);
  setString(jsonObj, String::NewFromUtf8(isolate, "NewPassword"), req.NewPassword);

  obj->uvTrader->ReqUserPasswordUpdate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqTradingAccountPasswordUpdate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqTradingAccountPasswordUpdate------>";

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

  CThostFtdcTradingAccountPasswordUpdateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OldPassword"), req.OldPassword);
  setString(jsonObj, String::NewFromUtf8(isolate, "NewPassword"), req.NewPassword);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);

  obj->uvTrader->ReqTradingAccountPasswordUpdate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqOrderInsert(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqOrderInsert------>";

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

  CThostFtdcInputOrderField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OrderRef"), req.OrderRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "OrderPriceType"), &req.OrderPriceType);
  setChar(jsonObj, String::NewFromUtf8(isolate, "Direction"), &req.Direction);
  setString(jsonObj, String::NewFromUtf8(isolate, "CombOffsetFlag"), req.CombOffsetFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "CombHedgeFlag"), req.CombHedgeFlag);
  setInt(jsonObj, String::NewFromUtf8(isolate, "VolumeTotalOriginal"), &req.VolumeTotalOriginal);
  setChar(jsonObj, String::NewFromUtf8(isolate, "TimeCondition"), &req.TimeCondition);
  setString(jsonObj, String::NewFromUtf8(isolate, "GTDDate"), req.GTDDate);
  setChar(jsonObj, String::NewFromUtf8(isolate, "VolumeCondition"), &req.VolumeCondition);
  setInt(jsonObj, String::NewFromUtf8(isolate, "MinVolume"), &req.MinVolume);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ContingentCondition"), &req.ContingentCondition);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ForceCloseReason"), &req.ForceCloseReason);
  setInt(jsonObj, String::NewFromUtf8(isolate, "IsAutoSuspend"), &req.IsAutoSuspend);
  setString(jsonObj, String::NewFromUtf8(isolate, "BusinessUnit"), req.BusinessUnit);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "UserForceClose"), &req.UserForceClose);
  setInt(jsonObj, String::NewFromUtf8(isolate, "IsSwapOrder"), &req.IsSwapOrder);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientID"), req.ClientID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqOrderInsert(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqParkedOrderInsert(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqParkedOrderInsert------>";

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

  CThostFtdcParkedOrderField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OrderRef"), req.OrderRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "OrderPriceType"), &req.OrderPriceType);
  setChar(jsonObj, String::NewFromUtf8(isolate, "Direction"), &req.Direction);
  setString(jsonObj, String::NewFromUtf8(isolate, "CombOffsetFlag"), req.CombOffsetFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "CombHedgeFlag"), req.CombHedgeFlag);
  setInt(jsonObj, String::NewFromUtf8(isolate, "VolumeTotalOriginal"), &req.VolumeTotalOriginal);
  setChar(jsonObj, String::NewFromUtf8(isolate, "TimeCondition"), &req.TimeCondition);
  setString(jsonObj, String::NewFromUtf8(isolate, "GTDDate"), req.GTDDate);
  setChar(jsonObj, String::NewFromUtf8(isolate, "VolumeCondition"), &req.VolumeCondition);
  setInt(jsonObj, String::NewFromUtf8(isolate, "MinVolume"), &req.MinVolume);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ContingentCondition"), &req.ContingentCondition);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ForceCloseReason"), &req.ForceCloseReason);
  setInt(jsonObj, String::NewFromUtf8(isolate, "IsAutoSuspend"), &req.IsAutoSuspend);
  setString(jsonObj, String::NewFromUtf8(isolate, "BusinessUnit"), req.BusinessUnit);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "UserForceClose"), &req.UserForceClose);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ParkedOrderID"), req.ParkedOrderID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "UserType"), &req.UserType);
  setChar(jsonObj, String::NewFromUtf8(isolate, "Status"), &req.Status);
  setInt(jsonObj, String::NewFromUtf8(isolate, "ErrorID"), &req.ErrorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ErrorMsg"), req.ErrorMsg);
  setInt(jsonObj, String::NewFromUtf8(isolate, "IsSwapOrder"), &req.IsSwapOrder);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientID"), req.ClientID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqParkedOrderInsert(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqParkedOrderAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqParkedOrderAction------>";

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

  CThostFtdcParkedOrderActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "OrderActionRef"), &req.OrderActionRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "OrderRef"), req.OrderRef);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FrontID"), &req.FrontID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OrderSysID"), req.OrderSysID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ActionFlag"), &req.ActionFlag);
  setInt(jsonObj, String::NewFromUtf8(isolate, "VolumeChange"), &req.VolumeChange);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ParkedOrderActionID"), req.ParkedOrderActionID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "UserType"), &req.UserType);
  setChar(jsonObj, String::NewFromUtf8(isolate, "Status"), &req.Status);
  setInt(jsonObj, String::NewFromUtf8(isolate, "ErrorID"), &req.ErrorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ErrorMsg"), req.ErrorMsg);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqParkedOrderAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqOrderAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqOrderAction------>";

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

  CThostFtdcInputOrderActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "OrderActionRef"), &req.OrderActionRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "OrderRef"), req.OrderRef);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FrontID"), &req.FrontID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OrderSysID"), req.OrderSysID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ActionFlag"), &req.ActionFlag);
  setInt(jsonObj, String::NewFromUtf8(isolate, "VolumeChange"), &req.VolumeChange);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqOrderAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQueryMaxOrderVolume(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQueryMaxOrderVolume------>";

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

  CThostFtdcQueryMaxOrderVolumeField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "Direction"), &req.Direction);
  setChar(jsonObj, String::NewFromUtf8(isolate, "OffsetFlag"), &req.OffsetFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setInt(jsonObj, String::NewFromUtf8(isolate, "MaxVolume"), &req.MaxVolume);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQueryMaxOrderVolume(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqSettlementInfoConfirm(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqSettlementInfoConfirm------>";

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

  CThostFtdcSettlementInfoConfirmField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ConfirmDate"), req.ConfirmDate);
  setString(jsonObj, String::NewFromUtf8(isolate, "ConfirmTime"), req.ConfirmTime);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SettlementID"), &req.SettlementID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);

  obj->uvTrader->ReqSettlementInfoConfirm(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqRemoveParkedOrder(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqRemoveParkedOrder------>";

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

  CThostFtdcRemoveParkedOrderField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ParkedOrderID"), req.ParkedOrderID);

  obj->uvTrader->ReqRemoveParkedOrder(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqRemoveParkedOrderAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqRemoveParkedOrderAction------>";

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

  CThostFtdcRemoveParkedOrderActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ParkedOrderActionID"), req.ParkedOrderActionID);

  obj->uvTrader->ReqRemoveParkedOrderAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqExecOrderInsert(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqExecOrderInsert------>";

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

  CThostFtdcInputExecOrderField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExecOrderRef"), req.ExecOrderRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "Volume"), &req.Volume);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BusinessUnit"), req.BusinessUnit);
  setChar(jsonObj, String::NewFromUtf8(isolate, "OffsetFlag"), &req.OffsetFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ActionType"), &req.ActionType);
  setChar(jsonObj, String::NewFromUtf8(isolate, "PosiDirection"), &req.PosiDirection);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ReservePositionFlag"), &req.ReservePositionFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "CloseFlag"), &req.CloseFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientID"), req.ClientID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqExecOrderInsert(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqExecOrderAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqExecOrderAction------>";

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

  CThostFtdcInputExecOrderActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "ExecOrderActionRef"), &req.ExecOrderActionRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExecOrderRef"), req.ExecOrderRef);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FrontID"), &req.FrontID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExecOrderSysID"), req.ExecOrderSysID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ActionFlag"), &req.ActionFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqExecOrderAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqForQuoteInsert(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqForQuoteInsert------>";

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

  CThostFtdcInputForQuoteField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ForQuoteRef"), req.ForQuoteRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqForQuoteInsert(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQuoteInsert(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQuoteInsert------>";

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

  CThostFtdcInputQuoteField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "QuoteRef"), req.QuoteRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "AskVolume"), &req.AskVolume);
  setInt(jsonObj, String::NewFromUtf8(isolate, "BidVolume"), &req.BidVolume);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BusinessUnit"), req.BusinessUnit);
  setChar(jsonObj, String::NewFromUtf8(isolate, "AskOffsetFlag"), &req.AskOffsetFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BidOffsetFlag"), &req.BidOffsetFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "AskHedgeFlag"), &req.AskHedgeFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BidHedgeFlag"), &req.BidHedgeFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "AskOrderRef"), req.AskOrderRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "BidOrderRef"), req.BidOrderRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "ForQuoteSysID"), req.ForQuoteSysID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientID"), req.ClientID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqQuoteInsert(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQuoteAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQuoteAction------>";

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

  CThostFtdcInputQuoteActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "QuoteActionRef"), &req.QuoteActionRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "QuoteRef"), req.QuoteRef);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FrontID"), &req.FrontID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "QuoteSysID"), req.QuoteSysID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ActionFlag"), &req.ActionFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientID"), req.ClientID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqQuoteAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqBatchOrderAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqBatchOrderAction------>";

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

  CThostFtdcInputBatchOrderActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "OrderActionRef"), &req.OrderActionRef);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FrontID"), &req.FrontID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqBatchOrderAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqOptionSelfCloseInsert(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqOptionSelfCloseInsert------>";

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

  CThostFtdcInputOptionSelfCloseField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OptionSelfCloseRef"), req.OptionSelfCloseRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "Volume"), &req.Volume);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BusinessUnit"), req.BusinessUnit);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientID"), req.ClientID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqOptionSelfCloseInsert(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqOptionSelfCloseAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqOptionSelfCloseAction------>";

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

  CThostFtdcInputOptionSelfCloseActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "OptionSelfCloseActionRef"), &req.OptionSelfCloseActionRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "OptionSelfCloseRef"), req.OptionSelfCloseRef);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FrontID"), &req.FrontID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OptionSelfCloseSysID"), req.OptionSelfCloseSysID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ActionFlag"), &req.ActionFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqOptionSelfCloseAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqCombActionInsert(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqCombActionInsert------>";

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

  CThostFtdcInputCombActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CombActionRef"), req.CombActionRef);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "Direction"), &req.Direction);
  setInt(jsonObj, String::NewFromUtf8(isolate, "Volume"), &req.Volume);
  setChar(jsonObj, String::NewFromUtf8(isolate, "CombDirection"), &req.CombDirection);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "IPAddress"), req.IPAddress);
  setString(jsonObj, String::NewFromUtf8(isolate, "MacAddress"), req.MacAddress);

  obj->uvTrader->ReqCombActionInsert(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryOrder(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryOrder------>";

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

  CThostFtdcQryOrderField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OrderSysID"), req.OrderSysID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeStart"), req.InsertTimeStart);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeEnd"), req.InsertTimeEnd);

  obj->uvTrader->ReqQryOrder(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryTrade(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryTrade------>";

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

  CThostFtdcQryTradeField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeID"), req.TradeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeTimeStart"), req.TradeTimeStart);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeTimeEnd"), req.TradeTimeEnd);

  obj->uvTrader->ReqQryTrade(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInvestorPosition(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInvestorPosition------>";

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

  CThostFtdcQryInvestorPositionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryInvestorPosition(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryTradingAccount(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryTradingAccount------>";

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

  CThostFtdcQryTradingAccountField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BizType"), &req.BizType);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);

  obj->uvTrader->ReqQryTradingAccount(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInvestor(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInvestor------>";

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

  CThostFtdcQryInvestorField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);

  obj->uvTrader->ReqQryInvestor(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryTradingCode(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryTradingCode------>";

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

  CThostFtdcQryTradingCodeField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ClientID"), req.ClientID);

  obj->uvTrader->ReqQryTradingCode(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInstrumentMarginRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInstrumentMarginRate------>";

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

  CThostFtdcQryInstrumentMarginRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryInstrumentMarginRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInstrumentCommissionRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInstrumentCommissionRate------>";

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

  CThostFtdcQryInstrumentCommissionRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryInstrumentCommissionRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryExchange(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryExchange------>";

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

  CThostFtdcQryExchangeField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryExchange(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryProduct(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryProduct------>";

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

  CThostFtdcQryProductField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "ProductID"), req.ProductID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "ProductClass"), &req.ProductClass);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryProduct(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInstrument(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInstrument------>";

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

  CThostFtdcQryInstrumentField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeInstID"), req.ExchangeInstID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ProductID"), req.ProductID);

  obj->uvTrader->ReqQryInstrument(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryDepthMarketData(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryDepthMarketData------>";

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

  CThostFtdcQryDepthMarketDataField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryDepthMarketData(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQrySettlementInfo(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQrySettlementInfo------>";

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

  CThostFtdcQrySettlementInfoField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradingDay"), req.TradingDay);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);

  obj->uvTrader->ReqQrySettlementInfo(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryTransferBank(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryTransferBank------>";

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

  CThostFtdcQryTransferBankField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BankID"), req.BankID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankBrchID"), req.BankBrchID);

  obj->uvTrader->ReqQryTransferBank(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInvestorPositionDetail(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInvestorPositionDetail------>";

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

  CThostFtdcQryInvestorPositionDetailField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryInvestorPositionDetail(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryNotice(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryNotice------>";

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

  CThostFtdcQryNoticeField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);

  obj->uvTrader->ReqQryNotice(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQrySettlementInfoConfirm(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQrySettlementInfoConfirm------>";

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

  CThostFtdcQrySettlementInfoConfirmField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);

  obj->uvTrader->ReqQrySettlementInfoConfirm(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInvestorPositionCombineDetail(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInvestorPositionCombineDetail------>";

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

  CThostFtdcQryInvestorPositionCombineDetailField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CombInstrumentID"), req.CombInstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryInvestorPositionCombineDetail(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryCFMMCTradingAccountKey(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryCFMMCTradingAccountKey------>";

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

  CThostFtdcQryCFMMCTradingAccountKeyField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);

  obj->uvTrader->ReqQryCFMMCTradingAccountKey(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryEWarrantOffset(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryEWarrantOffset------>";

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

  CThostFtdcQryEWarrantOffsetField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);

  obj->uvTrader->ReqQryEWarrantOffset(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInvestorProductGroupMargin(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInvestorProductGroupMargin------>";

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

  CThostFtdcQryInvestorProductGroupMarginField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ProductGroupID"), req.ProductGroupID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryInvestorProductGroupMargin(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryExchangeMarginRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryExchangeMarginRate------>";

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

  CThostFtdcQryExchangeMarginRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryExchangeMarginRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryExchangeMarginRateAdjust(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryExchangeMarginRateAdjust------>";

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

  CThostFtdcQryExchangeMarginRateAdjustField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);

  obj->uvTrader->ReqQryExchangeMarginRateAdjust(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryExchangeRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryExchangeRate------>";

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

  CThostFtdcQryExchangeRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "FromCurrencyID"), req.FromCurrencyID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ToCurrencyID"), req.ToCurrencyID);

  obj->uvTrader->ReqQryExchangeRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQrySecAgentACIDMap(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQrySecAgentACIDMap------>";

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

  CThostFtdcQrySecAgentACIDMapField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);

  obj->uvTrader->ReqQrySecAgentACIDMap(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryProductExchRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryProductExchRate------>";

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

  CThostFtdcQryProductExchRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "ProductID"), req.ProductID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryProductExchRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryProductGroup(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryProductGroup------>";

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

  CThostFtdcQryProductGroupField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "ProductID"), req.ProductID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryProductGroup(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryMMInstrumentCommissionRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryMMInstrumentCommissionRate------>";

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

  CThostFtdcQryMMInstrumentCommissionRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);

  obj->uvTrader->ReqQryMMInstrumentCommissionRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryMMOptionInstrCommRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryMMOptionInstrCommRate------>";

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

  CThostFtdcQryMMOptionInstrCommRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);

  obj->uvTrader->ReqQryMMOptionInstrCommRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInstrumentOrderCommRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInstrumentOrderCommRate------>";

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

  CThostFtdcQryInstrumentOrderCommRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);

  obj->uvTrader->ReqQryInstrumentOrderCommRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQrySecAgentTradingAccount(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQrySecAgentTradingAccount------>";

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

  CThostFtdcQryTradingAccountField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BizType"), &req.BizType);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);

  obj->uvTrader->ReqQrySecAgentTradingAccount(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQrySecAgentCheckMode(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQrySecAgentCheckMode------>";

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

  CThostFtdcQrySecAgentCheckModeField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);

  obj->uvTrader->ReqQrySecAgentCheckMode(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryOptionInstrTradeCost(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryOptionInstrTradeCost------>";

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

  CThostFtdcQryOptionInstrTradeCostField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "HedgeFlag"), &req.HedgeFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryOptionInstrTradeCost(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryOptionInstrCommRate(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryOptionInstrCommRate------>";

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

  CThostFtdcQryOptionInstrCommRateField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryOptionInstrCommRate(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryExecOrder(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryExecOrder------>";

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

  CThostFtdcQryExecOrderField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExecOrderSysID"), req.ExecOrderSysID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeStart"), req.InsertTimeStart);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeEnd"), req.InsertTimeEnd);

  obj->uvTrader->ReqQryExecOrder(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryForQuote(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryForQuote------>";

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

  CThostFtdcQryForQuoteField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeStart"), req.InsertTimeStart);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeEnd"), req.InsertTimeEnd);

  obj->uvTrader->ReqQryForQuote(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryQuote(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryQuote------>";

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

  CThostFtdcQryQuoteField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "QuoteSysID"), req.QuoteSysID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeStart"), req.InsertTimeStart);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeEnd"), req.InsertTimeEnd);

  obj->uvTrader->ReqQryQuote(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryOptionSelfClose(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryOptionSelfClose------>";

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

  CThostFtdcQryOptionSelfCloseField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "OptionSelfCloseSysID"), req.OptionSelfCloseSysID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeStart"), req.InsertTimeStart);
  setString(jsonObj, String::NewFromUtf8(isolate, "InsertTimeEnd"), req.InsertTimeEnd);

  obj->uvTrader->ReqQryOptionSelfClose(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryInvestUnit(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryInvestUnit------>";

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

  CThostFtdcQryInvestUnitField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);

  obj->uvTrader->ReqQryInvestUnit(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryCombInstrumentGuard(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryCombInstrumentGuard------>";

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

  CThostFtdcQryCombInstrumentGuardField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryCombInstrumentGuard(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryCombAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryCombAction------>";

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

  CThostFtdcQryCombActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryCombAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryTransferSerial(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryTransferSerial------>";

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

  CThostFtdcQryTransferSerialField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankID"), req.BankID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);

  obj->uvTrader->ReqQryTransferSerial(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryAccountregister(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryAccountregister------>";

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

  CThostFtdcQryAccountregisterField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankID"), req.BankID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankBranchID"), req.BankBranchID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);

  obj->uvTrader->ReqQryAccountregister(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryContractBank(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryContractBank------>";

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

  CThostFtdcQryContractBankField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankID"), req.BankID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankBrchID"), req.BankBrchID);

  obj->uvTrader->ReqQryContractBank(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryParkedOrder(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryParkedOrder------>";

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

  CThostFtdcQryParkedOrderField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryParkedOrder(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryParkedOrderAction(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryParkedOrderAction------>";

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

  CThostFtdcQryParkedOrderActionField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);

  obj->uvTrader->ReqQryParkedOrderAction(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryTradingNotice(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryTradingNotice------>";

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

  CThostFtdcQryTradingNoticeField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);

  obj->uvTrader->ReqQryTradingNotice(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryBrokerTradingParams(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryBrokerTradingParams------>";

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

  CThostFtdcQryBrokerTradingParamsField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);

  obj->uvTrader->ReqQryBrokerTradingParams(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQryBrokerTradingAlgos(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQryBrokerTradingAlgos------>";

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

  CThostFtdcQryBrokerTradingAlgosField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "ExchangeID"), req.ExchangeID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InstrumentID"), req.InstrumentID);

  obj->uvTrader->ReqQryBrokerTradingAlgos(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQueryCFMMCTradingAccountToken(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQueryCFMMCTradingAccountToken------>";

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

  CThostFtdcQueryCFMMCTradingAccountTokenField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "InvestorID"), req.InvestorID);

  obj->uvTrader->ReqQueryCFMMCTradingAccountToken(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqFromBankToFutureByFuture(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqFromBankToFutureByFuture------>";

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

  CThostFtdcReqTransferField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "TradeCode"), req.TradeCode);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankID"), req.BankID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankBranchID"), req.BankBranchID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerBranchID"), req.BrokerBranchID);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeDate"), req.TradeDate);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeTime"), req.TradeTime);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankSerial"), req.BankSerial);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradingDay"), req.TradingDay);
  setInt(jsonObj, String::NewFromUtf8(isolate, "PlateSerial"), &req.PlateSerial);
  setChar(jsonObj, String::NewFromUtf8(isolate, "LastFragment"), &req.LastFragment);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CustomerName"), req.CustomerName);
  setChar(jsonObj, String::NewFromUtf8(isolate, "IdCardType"), &req.IdCardType);
  setString(jsonObj, String::NewFromUtf8(isolate, "IdentifiedCardNo"), req.IdentifiedCardNo);
  setChar(jsonObj, String::NewFromUtf8(isolate, "CustType"), &req.CustType);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankAccount"), req.BankAccount);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankPassWord"), req.BankPassWord);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "Password"), req.Password);
  setInt(jsonObj, String::NewFromUtf8(isolate, "InstallID"), &req.InstallID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FutureSerial"), &req.FutureSerial);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "VerifyCertNoFlag"), &req.VerifyCertNoFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "FeePayFlag"), &req.FeePayFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "Message"), req.Message);
  setString(jsonObj, String::NewFromUtf8(isolate, "Digest"), req.Digest);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankAccType"), &req.BankAccType);
  setString(jsonObj, String::NewFromUtf8(isolate, "DeviceID"), req.DeviceID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankSecuAccType"), &req.BankSecuAccType);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerIDByBank"), req.BrokerIDByBank);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankSecuAcc"), req.BankSecuAcc);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankPwdFlag"), &req.BankPwdFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "SecuPwdFlag"), &req.SecuPwdFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "OperNo"), req.OperNo);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "TID"), &req.TID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "TransferStatus"), &req.TransferStatus);

  obj->uvTrader->ReqFromBankToFutureByFuture(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqFromFutureToBankByFuture(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqFromFutureToBankByFuture------>";

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

  CThostFtdcReqTransferField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "TradeCode"), req.TradeCode);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankID"), req.BankID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankBranchID"), req.BankBranchID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerBranchID"), req.BrokerBranchID);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeDate"), req.TradeDate);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeTime"), req.TradeTime);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankSerial"), req.BankSerial);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradingDay"), req.TradingDay);
  setInt(jsonObj, String::NewFromUtf8(isolate, "PlateSerial"), &req.PlateSerial);
  setChar(jsonObj, String::NewFromUtf8(isolate, "LastFragment"), &req.LastFragment);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CustomerName"), req.CustomerName);
  setChar(jsonObj, String::NewFromUtf8(isolate, "IdCardType"), &req.IdCardType);
  setString(jsonObj, String::NewFromUtf8(isolate, "IdentifiedCardNo"), req.IdentifiedCardNo);
  setChar(jsonObj, String::NewFromUtf8(isolate, "CustType"), &req.CustType);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankAccount"), req.BankAccount);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankPassWord"), req.BankPassWord);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "Password"), req.Password);
  setInt(jsonObj, String::NewFromUtf8(isolate, "InstallID"), &req.InstallID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FutureSerial"), &req.FutureSerial);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "VerifyCertNoFlag"), &req.VerifyCertNoFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "FeePayFlag"), &req.FeePayFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "Message"), req.Message);
  setString(jsonObj, String::NewFromUtf8(isolate, "Digest"), req.Digest);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankAccType"), &req.BankAccType);
  setString(jsonObj, String::NewFromUtf8(isolate, "DeviceID"), req.DeviceID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankSecuAccType"), &req.BankSecuAccType);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerIDByBank"), req.BrokerIDByBank);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankSecuAcc"), req.BankSecuAcc);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankPwdFlag"), &req.BankPwdFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "SecuPwdFlag"), &req.SecuPwdFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "OperNo"), req.OperNo);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "TID"), &req.TID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "TransferStatus"), &req.TransferStatus);

  obj->uvTrader->ReqFromFutureToBankByFuture(&req, uuid, FunRtnCallback);
  return ;
}

void CTPTrader::ReqQueryBankAccountMoneyByFuture(const FunctionCallbackInfo <Value> &args) {
  Isolate *isolate = args.GetIsolate();
  std::string log = "ctp_trader ReqQueryBankAccountMoneyByFuture------>";

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

  CThostFtdcReqQueryAccountField req;
  memset(&req, 0, sizeof(req));

  Local<Object> jsonObj = args[0]->ToObject();

  setString(jsonObj, String::NewFromUtf8(isolate, "TradeCode"), req.TradeCode);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankID"), req.BankID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankBranchID"), req.BankBranchID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerID"), req.BrokerID);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerBranchID"), req.BrokerBranchID);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeDate"), req.TradeDate);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradeTime"), req.TradeTime);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankSerial"), req.BankSerial);
  setString(jsonObj, String::NewFromUtf8(isolate, "TradingDay"), req.TradingDay);
  setInt(jsonObj, String::NewFromUtf8(isolate, "PlateSerial"), &req.PlateSerial);
  setChar(jsonObj, String::NewFromUtf8(isolate, "LastFragment"), &req.LastFragment);
  setInt(jsonObj, String::NewFromUtf8(isolate, "SessionID"), &req.SessionID);
  setString(jsonObj, String::NewFromUtf8(isolate, "CustomerName"), req.CustomerName);
  setChar(jsonObj, String::NewFromUtf8(isolate, "IdCardType"), &req.IdCardType);
  setString(jsonObj, String::NewFromUtf8(isolate, "IdentifiedCardNo"), req.IdentifiedCardNo);
  setChar(jsonObj, String::NewFromUtf8(isolate, "CustType"), &req.CustType);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankAccount"), req.BankAccount);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankPassWord"), req.BankPassWord);
  setString(jsonObj, String::NewFromUtf8(isolate, "AccountID"), req.AccountID);
  setString(jsonObj, String::NewFromUtf8(isolate, "Password"), req.Password);
  setInt(jsonObj, String::NewFromUtf8(isolate, "FutureSerial"), &req.FutureSerial);
  setInt(jsonObj, String::NewFromUtf8(isolate, "InstallID"), &req.InstallID);
  setString(jsonObj, String::NewFromUtf8(isolate, "UserID"), req.UserID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "VerifyCertNoFlag"), &req.VerifyCertNoFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "CurrencyID"), req.CurrencyID);
  setString(jsonObj, String::NewFromUtf8(isolate, "Digest"), req.Digest);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankAccType"), &req.BankAccType);
  setString(jsonObj, String::NewFromUtf8(isolate, "DeviceID"), req.DeviceID);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankSecuAccType"), &req.BankSecuAccType);
  setString(jsonObj, String::NewFromUtf8(isolate, "BrokerIDByBank"), req.BrokerIDByBank);
  setString(jsonObj, String::NewFromUtf8(isolate, "BankSecuAcc"), req.BankSecuAcc);
  setChar(jsonObj, String::NewFromUtf8(isolate, "BankPwdFlag"), &req.BankPwdFlag);
  setChar(jsonObj, String::NewFromUtf8(isolate, "SecuPwdFlag"), &req.SecuPwdFlag);
  setString(jsonObj, String::NewFromUtf8(isolate, "OperNo"), req.OperNo);
  setInt(jsonObj, String::NewFromUtf8(isolate, "RequestID"), &req.RequestID);
  setInt(jsonObj, String::NewFromUtf8(isolate, "TID"), &req.TID);

  obj->uvTrader->ReqQueryBankAccountMoneyByFuture(&req, uuid, FunRtnCallback);
  return ;
}

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
    case T_ONRSPAUTHENTICATE: {
      Local <Value> argv[4];
      pkg_cb_onrspauthenticate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
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
    case T_ONRSPUSERPASSWORDUPDATE: {
      Local <Value> argv[4];
      pkg_cb_onrspuserpasswordupdate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPTRADINGACCOUNTPASSWORDUPDATE: {
      Local <Value> argv[4];
      pkg_cb_onrsptradingaccountpasswordupdate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPORDERINSERT: {
      Local <Value> argv[4];
      pkg_cb_onrsporderinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPPARKEDORDERINSERT: {
      Local <Value> argv[4];
      pkg_cb_onrspparkedorderinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPPARKEDORDERACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspparkedorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPORDERACTION: {
      Local <Value> argv[4];
      pkg_cb_onrsporderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQUERYMAXORDERVOLUME: {
      Local <Value> argv[4];
      pkg_cb_onrspquerymaxordervolume(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPSETTLEMENTINFOCONFIRM: {
      Local <Value> argv[4];
      pkg_cb_onrspsettlementinfoconfirm(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPREMOVEPARKEDORDER: {
      Local <Value> argv[4];
      pkg_cb_onrspremoveparkedorder(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPREMOVEPARKEDORDERACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspremoveparkedorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPEXECORDERINSERT: {
      Local <Value> argv[4];
      pkg_cb_onrspexecorderinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPEXECORDERACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspexecorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPFORQUOTEINSERT: {
      Local <Value> argv[4];
      pkg_cb_onrspforquoteinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQUOTEINSERT: {
      Local <Value> argv[4];
      pkg_cb_onrspquoteinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQUOTEACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspquoteaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPBATCHORDERACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspbatchorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPOPTIONSELFCLOSEINSERT: {
      Local <Value> argv[4];
      pkg_cb_onrspoptionselfcloseinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPOPTIONSELFCLOSEACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspoptionselfcloseaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPCOMBACTIONINSERT: {
      Local <Value> argv[4];
      pkg_cb_onrspcombactioninsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYORDER: {
      Local <Value> argv[4];
      pkg_cb_onrspqryorder(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYTRADE: {
      Local <Value> argv[4];
      pkg_cb_onrspqrytrade(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINVESTORPOSITION: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinvestorposition(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYTRADINGACCOUNT: {
      Local <Value> argv[4];
      pkg_cb_onrspqrytradingaccount(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINVESTOR: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinvestor(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYTRADINGCODE: {
      Local <Value> argv[4];
      pkg_cb_onrspqrytradingcode(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINSTRUMENTMARGINRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinstrumentmarginrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINSTRUMENTCOMMISSIONRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinstrumentcommissionrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYEXCHANGE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryexchange(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYPRODUCT: {
      Local <Value> argv[4];
      pkg_cb_onrspqryproduct(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINSTRUMENT: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinstrument(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYDEPTHMARKETDATA: {
      Local <Value> argv[4];
      pkg_cb_onrspqrydepthmarketdata(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYSETTLEMENTINFO: {
      Local <Value> argv[4];
      pkg_cb_onrspqrysettlementinfo(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYTRANSFERBANK: {
      Local <Value> argv[4];
      pkg_cb_onrspqrytransferbank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINVESTORPOSITIONDETAIL: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinvestorpositiondetail(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYNOTICE: {
      Local <Value> argv[4];
      pkg_cb_onrspqrynotice(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYSETTLEMENTINFOCONFIRM: {
      Local <Value> argv[4];
      pkg_cb_onrspqrysettlementinfoconfirm(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinvestorpositioncombinedetail(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYCFMMCTRADINGACCOUNTKEY: {
      Local <Value> argv[4];
      pkg_cb_onrspqrycfmmctradingaccountkey(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYEWARRANTOFFSET: {
      Local <Value> argv[4];
      pkg_cb_onrspqryewarrantoffset(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINVESTORPRODUCTGROUPMARGIN: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinvestorproductgroupmargin(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYEXCHANGEMARGINRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryexchangemarginrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYEXCHANGEMARGINRATEADJUST: {
      Local <Value> argv[4];
      pkg_cb_onrspqryexchangemarginrateadjust(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYEXCHANGERATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryexchangerate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYSECAGENTACIDMAP: {
      Local <Value> argv[4];
      pkg_cb_onrspqrysecagentacidmap(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYPRODUCTEXCHRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryproductexchrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYPRODUCTGROUP: {
      Local <Value> argv[4];
      pkg_cb_onrspqryproductgroup(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYMMINSTRUMENTCOMMISSIONRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqrymminstrumentcommissionrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYMMOPTIONINSTRCOMMRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqrymmoptioninstrcommrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINSTRUMENTORDERCOMMRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinstrumentordercommrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYSECAGENTTRADINGACCOUNT: {
      Local <Value> argv[4];
      pkg_cb_onrspqrysecagenttradingaccount(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYSECAGENTCHECKMODE: {
      Local <Value> argv[4];
      pkg_cb_onrspqrysecagentcheckmode(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYOPTIONINSTRTRADECOST: {
      Local <Value> argv[4];
      pkg_cb_onrspqryoptioninstrtradecost(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYOPTIONINSTRCOMMRATE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryoptioninstrcommrate(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYEXECORDER: {
      Local <Value> argv[4];
      pkg_cb_onrspqryexecorder(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYFORQUOTE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryforquote(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYQUOTE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryquote(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYOPTIONSELFCLOSE: {
      Local <Value> argv[4];
      pkg_cb_onrspqryoptionselfclose(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYINVESTUNIT: {
      Local <Value> argv[4];
      pkg_cb_onrspqryinvestunit(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYCOMBINSTRUMENTGUARD: {
      Local <Value> argv[4];
      pkg_cb_onrspqrycombinstrumentguard(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYCOMBACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspqrycombaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYTRANSFERSERIAL: {
      Local <Value> argv[4];
      pkg_cb_onrspqrytransferserial(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYACCOUNTREGISTER: {
      Local <Value> argv[4];
      pkg_cb_onrspqryaccountregister(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRTNORDER: {
      Local <Value> argv[1];
      pkg_cb_onrtnorder(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNTRADE: {
      Local <Value> argv[1];
      pkg_cb_onrtntrade(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONERRRTNORDERINSERT: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnorderinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNORDERACTION: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONRTNINSTRUMENTSTATUS: {
      Local <Value> argv[1];
      pkg_cb_onrtninstrumentstatus(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNBULLETIN: {
      Local <Value> argv[1];
      pkg_cb_onrtnbulletin(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNTRADINGNOTICE: {
      Local <Value> argv[1];
      pkg_cb_onrtntradingnotice(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNERRORCONDITIONALORDER: {
      Local <Value> argv[1];
      pkg_cb_onrtnerrorconditionalorder(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNEXECORDER: {
      Local <Value> argv[1];
      pkg_cb_onrtnexecorder(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONERRRTNEXECORDERINSERT: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnexecorderinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNEXECORDERACTION: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnexecorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNFORQUOTEINSERT: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnforquoteinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONRTNQUOTE: {
      Local <Value> argv[1];
      pkg_cb_onrtnquote(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONERRRTNQUOTEINSERT: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnquoteinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNQUOTEACTION: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnquoteaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONRTNFORQUOTERSP: {
      Local <Value> argv[1];
      pkg_cb_onrtnforquotersp(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNCFMMCTRADINGACCOUNTTOKEN: {
      Local <Value> argv[1];
      pkg_cb_onrtncfmmctradingaccounttoken(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONERRRTNBATCHORDERACTION: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnbatchorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONRTNOPTIONSELFCLOSE: {
      Local <Value> argv[1];
      pkg_cb_onrtnoptionselfclose(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONERRRTNOPTIONSELFCLOSEINSERT: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnoptionselfcloseinsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNOPTIONSELFCLOSEACTION: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnoptionselfcloseaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONRTNCOMBACTION: {
      Local <Value> argv[1];
      pkg_cb_onrtncombaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONERRRTNCOMBACTIONINSERT: {
      Local <Value> argv[2];
      pkg_cb_onerrrtncombactioninsert(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONRSPQRYCONTRACTBANK: {
      Local <Value> argv[4];
      pkg_cb_onrspqrycontractbank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYPARKEDORDER: {
      Local <Value> argv[4];
      pkg_cb_onrspqryparkedorder(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYPARKEDORDERACTION: {
      Local <Value> argv[4];
      pkg_cb_onrspqryparkedorderaction(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYTRADINGNOTICE: {
      Local <Value> argv[4];
      pkg_cb_onrspqrytradingnotice(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYBROKERTRADINGPARAMS: {
      Local <Value> argv[4];
      pkg_cb_onrspqrybrokertradingparams(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQRYBROKERTRADINGALGOS: {
      Local <Value> argv[4];
      pkg_cb_onrspqrybrokertradingalgos(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN: {
      Local <Value> argv[4];
      pkg_cb_onrspquerycfmmctradingaccounttoken(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRTNFROMBANKTOFUTUREBYBANK: {
      Local <Value> argv[1];
      pkg_cb_onrtnfrombanktofuturebybank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNFROMFUTURETOBANKBYBANK: {
      Local <Value> argv[1];
      pkg_cb_onrtnfromfuturetobankbybank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNREPEALFROMBANKTOFUTUREBYBANK: {
      Local <Value> argv[1];
      pkg_cb_onrtnrepealfrombanktofuturebybank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNREPEALFROMFUTURETOBANKBYBANK: {
      Local <Value> argv[1];
      pkg_cb_onrtnrepealfromfuturetobankbybank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNFROMBANKTOFUTUREBYFUTURE: {
      Local <Value> argv[1];
      pkg_cb_onrtnfrombanktofuturebyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNFROMFUTURETOBANKBYFUTURE: {
      Local <Value> argv[1];
      pkg_cb_onrtnfromfuturetobankbyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL: {
      Local <Value> argv[1];
      pkg_cb_onrtnrepealfrombanktofuturebyfuturemanual(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL: {
      Local <Value> argv[1];
      pkg_cb_onrtnrepealfromfuturetobankbyfuturemanual(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNQUERYBANKBALANCEBYFUTURE: {
      Local <Value> argv[1];
      pkg_cb_onrtnquerybankbalancebyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONERRRTNBANKTOFUTUREBYFUTURE: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnbanktofuturebyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNFUTURETOBANKBYFUTURE: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnfuturetobankbyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnrepealbanktofuturebyfuturemanual(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnrepealfuturetobankbyfuturemanual(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONERRRTNQUERYBANKBALANCEBYFUTURE: {
      Local <Value> argv[2];
      pkg_cb_onerrrtnquerybankbalancebyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 2, argv);
      break;
    }
    case T_ONRTNREPEALFROMBANKTOFUTUREBYFUTURE: {
      Local <Value> argv[1];
      pkg_cb_onrtnrepealfrombanktofuturebyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNREPEALFROMFUTURETOBANKBYFUTURE: {
      Local <Value> argv[1];
      pkg_cb_onrtnrepealfromfuturetobankbyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRSPFROMBANKTOFUTUREBYFUTURE: {
      Local <Value> argv[4];
      pkg_cb_onrspfrombanktofuturebyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPFROMFUTURETOBANKBYFUTURE: {
      Local <Value> argv[4];
      pkg_cb_onrspfromfuturetobankbyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRSPQUERYBANKACCOUNTMONEYBYFUTURE: {
      Local <Value> argv[4];
      pkg_cb_onrspquerybankaccountmoneybyfuture(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 4, argv);
      break;
    }
    case T_ONRTNOPENACCOUNTBYBANK: {
      Local <Value> argv[1];
      pkg_cb_onrtnopenaccountbybank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNCANCELACCOUNTBYBANK: {
      Local <Value> argv[1];
      pkg_cb_onrtncancelaccountbybank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }
    case T_ONRTNCHANGEACCOUNTBYBANK: {
      Local <Value> argv[1];
      pkg_cb_onrtnchangeaccountbybank(data, argv);
      Local<Function> fn = Local<Function>::New(isolate, cIt->second);
      fn->Call(isolate->GetCurrentContext()->Global(), 1, argv);
      break;
    }

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

void CTPTrader::pkg_cb_onrspauthenticate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspAuthenticateField *pRspAuthenticateField = static_cast<CThostFtdcRspAuthenticateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspAuthenticateField->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspAuthenticateField->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pRspAuthenticateField->UserProductInfo));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspuserlogin(CbRtnField *data, Local <Value> *cbArray) {
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

void CTPTrader::pkg_cb_onrspuserlogout(CbRtnField *data, Local <Value> *cbArray) {
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

void CTPTrader::pkg_cb_onrspuserpasswordupdate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate = static_cast<CThostFtdcUserPasswordUpdateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pUserPasswordUpdate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pUserPasswordUpdate->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OldPassword"), String::NewFromUtf8(isolate, pUserPasswordUpdate->OldPassword));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NewPassword"), String::NewFromUtf8(isolate, pUserPasswordUpdate->NewPassword));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrsptradingaccountpasswordupdate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate = static_cast<CThostFtdcTradingAccountPasswordUpdateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTradingAccountPasswordUpdate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pTradingAccountPasswordUpdate->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OldPassword"), String::NewFromUtf8(isolate, pTradingAccountPasswordUpdate->OldPassword));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NewPassword"), String::NewFromUtf8(isolate, pTradingAccountPasswordUpdate->NewPassword));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pTradingAccountPasswordUpdate->CurrencyID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrsporderinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputOrderField *pInputOrder = static_cast<CThostFtdcInputOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pInputOrder->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderPriceType"), String::NewFromUtf8(isolate, charto_string(pInputOrder->OrderPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pInputOrder->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombOffsetFlag"), String::NewFromUtf8(isolate, pInputOrder->CombOffsetFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombHedgeFlag"), String::NewFromUtf8(isolate, pInputOrder->CombHedgeFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotalOriginal"), Number::New(isolate, pInputOrder->VolumeTotalOriginal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TimeCondition"), String::NewFromUtf8(isolate, charto_string(pInputOrder->TimeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "GTDDate"), String::NewFromUtf8(isolate, pInputOrder->GTDDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeCondition"), String::NewFromUtf8(isolate, charto_string(pInputOrder->VolumeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinVolume"), Number::New(isolate, pInputOrder->MinVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ContingentCondition"), String::NewFromUtf8(isolate, charto_string(pInputOrder->ContingentCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForceCloseReason"), String::NewFromUtf8(isolate, charto_string(pInputOrder->ForceCloseReason).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsAutoSuspend"), Number::New(isolate, pInputOrder->IsAutoSuspend));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserForceClose"), Number::New(isolate, pInputOrder->UserForceClose));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsSwapOrder"), Number::New(isolate, pInputOrder->IsSwapOrder));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pInputOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pInputOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspparkedorderinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcParkedOrderField *pParkedOrder = static_cast<CThostFtdcParkedOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pParkedOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pParkedOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pParkedOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pParkedOrder->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pParkedOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderPriceType"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->OrderPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombOffsetFlag"), String::NewFromUtf8(isolate, pParkedOrder->CombOffsetFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombHedgeFlag"), String::NewFromUtf8(isolate, pParkedOrder->CombHedgeFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotalOriginal"), Number::New(isolate, pParkedOrder->VolumeTotalOriginal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TimeCondition"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->TimeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "GTDDate"), String::NewFromUtf8(isolate, pParkedOrder->GTDDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeCondition"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->VolumeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinVolume"), Number::New(isolate, pParkedOrder->MinVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ContingentCondition"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->ContingentCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForceCloseReason"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->ForceCloseReason).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsAutoSuspend"), Number::New(isolate, pParkedOrder->IsAutoSuspend));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pParkedOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pParkedOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserForceClose"), Number::New(isolate, pParkedOrder->UserForceClose));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pParkedOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParkedOrderID"), String::NewFromUtf8(isolate, pParkedOrder->ParkedOrderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserType"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->UserType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Status"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->Status).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pParkedOrder->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pParkedOrder->ErrorMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsSwapOrder"), Number::New(isolate, pParkedOrder->IsSwapOrder));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pParkedOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pParkedOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pParkedOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pParkedOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pParkedOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspparkedorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcParkedOrderActionField *pParkedOrderAction = static_cast<CThostFtdcParkedOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pParkedOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pParkedOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionRef"), Number::New(isolate, pParkedOrderAction->OrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pParkedOrderAction->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pParkedOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pParkedOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pParkedOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pParkedOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pParkedOrderAction->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pParkedOrderAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeChange"), Number::New(isolate, pParkedOrderAction->VolumeChange));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pParkedOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pParkedOrderAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParkedOrderActionID"), String::NewFromUtf8(isolate, pParkedOrderAction->ParkedOrderActionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserType"), String::NewFromUtf8(isolate, charto_string(pParkedOrderAction->UserType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Status"), String::NewFromUtf8(isolate, charto_string(pParkedOrderAction->Status).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pParkedOrderAction->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pParkedOrderAction->ErrorMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pParkedOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pParkedOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrsporderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputOrderActionField *pInputOrderAction = static_cast<CThostFtdcInputOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionRef"), Number::New(isolate, pInputOrderAction->OrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pInputOrderAction->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pInputOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pInputOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pInputOrderAction->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pInputOrderAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeChange"), Number::New(isolate, pInputOrderAction->VolumeChange));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputOrderAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspquerymaxordervolume(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume = static_cast<CThostFtdcQueryMaxOrderVolumeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pQueryMaxOrderVolume->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pQueryMaxOrderVolume->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pQueryMaxOrderVolume->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pQueryMaxOrderVolume->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OffsetFlag"), String::NewFromUtf8(isolate, charto_string(pQueryMaxOrderVolume->OffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pQueryMaxOrderVolume->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MaxVolume"), Number::New(isolate, pQueryMaxOrderVolume->MaxVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pQueryMaxOrderVolume->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspsettlementinfoconfirm(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm = static_cast<CThostFtdcSettlementInfoConfirmField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ConfirmDate"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->ConfirmDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ConfirmTime"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->ConfirmTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pSettlementInfoConfirm->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->CurrencyID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspremoveparkedorder(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder = static_cast<CThostFtdcRemoveParkedOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRemoveParkedOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pRemoveParkedOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParkedOrderID"), String::NewFromUtf8(isolate, pRemoveParkedOrder->ParkedOrderID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspremoveparkedorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction = static_cast<CThostFtdcRemoveParkedOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRemoveParkedOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pRemoveParkedOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParkedOrderActionID"), String::NewFromUtf8(isolate, pRemoveParkedOrderAction->ParkedOrderActionID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspexecorderinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputExecOrderField *pInputExecOrder = static_cast<CThostFtdcInputExecOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputExecOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputExecOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputExecOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderRef"), String::NewFromUtf8(isolate, pInputExecOrder->ExecOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputExecOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pInputExecOrder->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputExecOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputExecOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OffsetFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->OffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionType"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->ActionType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PosiDirection"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->PosiDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ReservePositionFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->ReservePositionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CloseFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->CloseFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputExecOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pInputExecOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pInputExecOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputExecOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputExecOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputExecOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspexecorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputExecOrderActionField *pInputExecOrderAction = static_cast<CThostFtdcInputExecOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputExecOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputExecOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderActionRef"), Number::New(isolate, pInputExecOrderAction->ExecOrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderRef"), String::NewFromUtf8(isolate, pInputExecOrderAction->ExecOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputExecOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pInputExecOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pInputExecOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputExecOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderSysID"), String::NewFromUtf8(isolate, pInputExecOrderAction->ExecOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrderAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputExecOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputExecOrderAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputExecOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputExecOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspforquoteinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputForQuoteField *pInputForQuote = static_cast<CThostFtdcInputForQuoteField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputForQuote->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputForQuote->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputForQuote->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteRef"), String::NewFromUtf8(isolate, pInputForQuote->ForQuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputForQuote->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputForQuote->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputForQuote->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputForQuote->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspquoteinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputQuoteField *pInputQuote = static_cast<CThostFtdcInputQuoteField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputQuote->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputQuote->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputQuote->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteRef"), String::NewFromUtf8(isolate, pInputQuote->QuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputQuote->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume"), Number::New(isolate, pInputQuote->AskVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume"), Number::New(isolate, pInputQuote->BidVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputQuote->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputQuote->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->AskOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->BidOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->AskHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->BidHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOrderRef"), String::NewFromUtf8(isolate, pInputQuote->AskOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOrderRef"), String::NewFromUtf8(isolate, pInputQuote->BidOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteSysID"), String::NewFromUtf8(isolate, pInputQuote->ForQuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputQuote->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputQuote->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputQuote->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputQuote->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspquoteaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputQuoteActionField *pInputQuoteAction = static_cast<CThostFtdcInputQuoteActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputQuoteAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputQuoteAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteActionRef"), Number::New(isolate, pInputQuoteAction->QuoteActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteRef"), String::NewFromUtf8(isolate, pInputQuoteAction->QuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputQuoteAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pInputQuoteAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pInputQuoteAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputQuoteAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteSysID"), String::NewFromUtf8(isolate, pInputQuoteAction->QuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuoteAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputQuoteAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputQuoteAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputQuoteAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputQuoteAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputQuoteAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspbatchorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction = static_cast<CThostFtdcInputBatchOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputBatchOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputBatchOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionRef"), Number::New(isolate, pInputBatchOrderAction->OrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputBatchOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pInputBatchOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pInputBatchOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputBatchOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputBatchOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputBatchOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputBatchOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspoptionselfcloseinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose = static_cast<CThostFtdcInputOptionSelfCloseField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseRef"), String::NewFromUtf8(isolate, pInputOptionSelfClose->OptionSelfCloseRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pInputOptionSelfClose->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputOptionSelfClose->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputOptionSelfClose->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputOptionSelfClose->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputOptionSelfClose->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputOptionSelfClose->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspoptionselfcloseaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction = static_cast<CThostFtdcInputOptionSelfCloseActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseActionRef"), Number::New(isolate, pInputOptionSelfCloseAction->OptionSelfCloseActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseRef"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->OptionSelfCloseRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputOptionSelfCloseAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pInputOptionSelfCloseAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pInputOptionSelfCloseAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseSysID"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->OptionSelfCloseSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pInputOptionSelfCloseAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputOptionSelfCloseAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspcombactioninsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputCombActionField *pInputCombAction = static_cast<CThostFtdcInputCombActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputCombAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputCombAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputCombAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombActionRef"), String::NewFromUtf8(isolate, pInputCombAction->CombActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputCombAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pInputCombAction->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pInputCombAction->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombDirection"), String::NewFromUtf8(isolate, charto_string(pInputCombAction->CombDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputCombAction->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputCombAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputCombAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputCombAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryorder(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOrderField *pOrder = static_cast<CThostFtdcOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pOrder->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderPriceType"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pOrder->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombOffsetFlag"), String::NewFromUtf8(isolate, pOrder->CombOffsetFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombHedgeFlag"), String::NewFromUtf8(isolate, pOrder->CombHedgeFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotalOriginal"), Number::New(isolate, pOrder->VolumeTotalOriginal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TimeCondition"), String::NewFromUtf8(isolate, charto_string(pOrder->TimeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "GTDDate"), String::NewFromUtf8(isolate, pOrder->GTDDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeCondition"), String::NewFromUtf8(isolate, charto_string(pOrder->VolumeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinVolume"), Number::New(isolate, pOrder->MinVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ContingentCondition"), String::NewFromUtf8(isolate, charto_string(pOrder->ContingentCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForceCloseReason"), String::NewFromUtf8(isolate, charto_string(pOrder->ForceCloseReason).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsAutoSuspend"), Number::New(isolate, pOrder->IsAutoSuspend));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderLocalID"), String::NewFromUtf8(isolate, pOrder->OrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pOrder->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pOrder->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pOrder->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pOrder->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pOrder->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pOrder->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pOrder->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pOrder->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSource"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderSource).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderStatus"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderType"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTraded"), Number::New(isolate, pOrder->VolumeTraded));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotal"), Number::New(isolate, pOrder->VolumeTotal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pOrder->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pOrder->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveTime"), String::NewFromUtf8(isolate, pOrder->ActiveTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SuspendTime"), String::NewFromUtf8(isolate, pOrder->SuspendTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UpdateTime"), String::NewFromUtf8(isolate, pOrder->UpdateTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pOrder->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveTraderID"), String::NewFromUtf8(isolate, pOrder->ActiveTraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pOrder->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pOrder->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pOrder->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pOrder->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pOrder->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pOrder->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserForceClose"), Number::New(isolate, pOrder->UserForceClose));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pOrder->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerOrderSeq"), Number::New(isolate, pOrder->BrokerOrderSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RelativeOrderSysID"), String::NewFromUtf8(isolate, pOrder->RelativeOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ZCETotalTradedVolume"), Number::New(isolate, pOrder->ZCETotalTradedVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsSwapOrder"), Number::New(isolate, pOrder->IsSwapOrder));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pOrder->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrytrade(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradeField *pTrade = static_cast<CThostFtdcTradeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTrade->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pTrade->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pTrade->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pTrade->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pTrade->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pTrade->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeID"), String::NewFromUtf8(isolate, pTrade->TradeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pTrade->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pTrade->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pTrade->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pTrade->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingRole"), String::NewFromUtf8(isolate, charto_string(pTrade->TradingRole).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pTrade->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OffsetFlag"), String::NewFromUtf8(isolate, charto_string(pTrade->OffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pTrade->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pTrade->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pTrade->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pTrade->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeType"), String::NewFromUtf8(isolate, charto_string(pTrade->TradeType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PriceSource"), String::NewFromUtf8(isolate, charto_string(pTrade->PriceSource).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pTrade->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderLocalID"), String::NewFromUtf8(isolate, pTrade->OrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pTrade->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pTrade->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pTrade->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pTrade->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pTrade->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerOrderSeq"), Number::New(isolate, pTrade->BrokerOrderSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeSource"), String::NewFromUtf8(isolate, charto_string(pTrade->TradeSource).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinvestorposition(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInvestorPositionField *pInvestorPosition = static_cast<CThostFtdcInvestorPositionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInvestorPosition->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInvestorPosition->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInvestorPosition->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PosiDirection"), String::NewFromUtf8(isolate, charto_string(pInvestorPosition->PosiDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInvestorPosition->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PositionDate"), String::NewFromUtf8(isolate, charto_string(pInvestorPosition->PositionDate).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "YdPosition"), Number::New(isolate, pInvestorPosition->YdPosition));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Position"), Number::New(isolate, pInvestorPosition->Position));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LongFrozen"), Number::New(isolate, pInvestorPosition->LongFrozen));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ShortFrozen"), Number::New(isolate, pInvestorPosition->ShortFrozen));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OpenVolume"), Number::New(isolate, pInvestorPosition->OpenVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CloseVolume"), Number::New(isolate, pInvestorPosition->CloseVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pInvestorPosition->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pInvestorPosition->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombPosition"), Number::New(isolate, pInvestorPosition->CombPosition));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombLongFrozen"), Number::New(isolate, pInvestorPosition->CombLongFrozen));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombShortFrozen"), Number::New(isolate, pInvestorPosition->CombShortFrozen));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TodayPosition"), Number::New(isolate, pInvestorPosition->TodayPosition));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StrikeFrozen"), Number::New(isolate, pInvestorPosition->StrikeFrozen));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AbandonFrozen"), Number::New(isolate, pInvestorPosition->AbandonFrozen));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInvestorPosition->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "YdStrikeFrozen"), Number::New(isolate, pInvestorPosition->YdStrikeFrozen));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrytradingaccount(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradingAccountField *pTradingAccount = static_cast<CThostFtdcTradingAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTradingAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pTradingAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pTradingAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pTradingAccount->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pTradingAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BizType"), String::NewFromUtf8(isolate, charto_string(pTradingAccount->BizType).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinvestor(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInvestorField *pInvestor = static_cast<CThostFtdcInvestorField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInvestor->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInvestor->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorGroupID"), String::NewFromUtf8(isolate, pInvestor->InvestorGroupID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorName"), String::NewFromUtf8(isolate, pInvestor->InvestorName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardType"), String::NewFromUtf8(isolate, charto_string(pInvestor->IdentifiedCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pInvestor->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsActive"), Number::New(isolate, pInvestor->IsActive));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Telephone"), String::NewFromUtf8(isolate, pInvestor->Telephone));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Address"), String::NewFromUtf8(isolate, pInvestor->Address));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OpenDate"), String::NewFromUtf8(isolate, pInvestor->OpenDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Mobile"), String::NewFromUtf8(isolate, pInvestor->Mobile));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CommModelID"), String::NewFromUtf8(isolate, pInvestor->CommModelID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MarginModelID"), String::NewFromUtf8(isolate, pInvestor->MarginModelID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrytradingcode(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradingCodeField *pTradingCode = static_cast<CThostFtdcTradingCodeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pTradingCode->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTradingCode->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pTradingCode->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pTradingCode->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsActive"), Number::New(isolate, pTradingCode->IsActive));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pTradingCode->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BizType"), String::NewFromUtf8(isolate, charto_string(pTradingCode->BizType).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinstrumentmarginrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate = static_cast<CThostFtdcInstrumentMarginRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInstrumentMarginRate->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorRange"), String::NewFromUtf8(isolate, charto_string(pInstrumentMarginRate->InvestorRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInstrumentMarginRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInstrumentMarginRate->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInstrumentMarginRate->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsRelative"), Number::New(isolate, pInstrumentMarginRate->IsRelative));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInstrumentMarginRate->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinstrumentcommissionrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate = static_cast<CThostFtdcInstrumentCommissionRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInstrumentCommissionRate->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorRange"), String::NewFromUtf8(isolate, charto_string(pInstrumentCommissionRate->InvestorRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInstrumentCommissionRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInstrumentCommissionRate->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInstrumentCommissionRate->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BizType"), String::NewFromUtf8(isolate, charto_string(pInstrumentCommissionRate->BizType).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryexchange(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcExchangeField *pExchange = static_cast<CThostFtdcExchangeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pExchange->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeName"), String::NewFromUtf8(isolate, pExchange->ExchangeName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeProperty"), String::NewFromUtf8(isolate, charto_string(pExchange->ExchangeProperty).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryproduct(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcProductField *pProduct = static_cast<CThostFtdcProductField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductID"), String::NewFromUtf8(isolate, pProduct->ProductID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductName"), String::NewFromUtf8(isolate, pProduct->ProductName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pProduct->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductClass"), String::NewFromUtf8(isolate, charto_string(pProduct->ProductClass).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeMultiple"), Number::New(isolate, pProduct->VolumeMultiple));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MaxMarketOrderVolume"), Number::New(isolate, pProduct->MaxMarketOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinMarketOrderVolume"), Number::New(isolate, pProduct->MinMarketOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MaxLimitOrderVolume"), Number::New(isolate, pProduct->MaxLimitOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinLimitOrderVolume"), Number::New(isolate, pProduct->MinLimitOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PositionType"), String::NewFromUtf8(isolate, charto_string(pProduct->PositionType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PositionDateType"), String::NewFromUtf8(isolate, charto_string(pProduct->PositionDateType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CloseDealType"), String::NewFromUtf8(isolate, charto_string(pProduct->CloseDealType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCurrencyID"), String::NewFromUtf8(isolate, pProduct->TradeCurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MortgageFundUseRange"), String::NewFromUtf8(isolate, charto_string(pProduct->MortgageFundUseRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeProductID"), String::NewFromUtf8(isolate, pProduct->ExchangeProductID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinstrument(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInstrumentField *pInstrument = static_cast<CThostFtdcInstrumentField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInstrument->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInstrument->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentName"), String::NewFromUtf8(isolate, pInstrument->InstrumentName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pInstrument->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductID"), String::NewFromUtf8(isolate, pInstrument->ProductID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductClass"), String::NewFromUtf8(isolate, charto_string(pInstrument->ProductClass).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeliveryYear"), Number::New(isolate, pInstrument->DeliveryYear));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeliveryMonth"), Number::New(isolate, pInstrument->DeliveryMonth));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MaxMarketOrderVolume"), Number::New(isolate, pInstrument->MaxMarketOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinMarketOrderVolume"), Number::New(isolate, pInstrument->MinMarketOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MaxLimitOrderVolume"), Number::New(isolate, pInstrument->MaxLimitOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinLimitOrderVolume"), Number::New(isolate, pInstrument->MinLimitOrderVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeMultiple"), Number::New(isolate, pInstrument->VolumeMultiple));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CreateDate"), String::NewFromUtf8(isolate, pInstrument->CreateDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OpenDate"), String::NewFromUtf8(isolate, pInstrument->OpenDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExpireDate"), String::NewFromUtf8(isolate, pInstrument->ExpireDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StartDelivDate"), String::NewFromUtf8(isolate, pInstrument->StartDelivDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "EndDelivDate"), String::NewFromUtf8(isolate, pInstrument->EndDelivDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstLifePhase"), String::NewFromUtf8(isolate, charto_string(pInstrument->InstLifePhase).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsTrading"), Number::New(isolate, pInstrument->IsTrading));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PositionType"), String::NewFromUtf8(isolate, charto_string(pInstrument->PositionType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PositionDateType"), String::NewFromUtf8(isolate, charto_string(pInstrument->PositionDateType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MaxMarginSideAlgorithm"), String::NewFromUtf8(isolate, charto_string(pInstrument->MaxMarginSideAlgorithm).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UnderlyingInstrID"), String::NewFromUtf8(isolate, pInstrument->UnderlyingInstrID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionsType"), String::NewFromUtf8(isolate, charto_string(pInstrument->OptionsType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombinationType"), String::NewFromUtf8(isolate, charto_string(pInstrument->CombinationType).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrydepthmarketdata(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcDepthMarketDataField *pDepthMarketData = static_cast<CThostFtdcDepthMarketDataField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pDepthMarketData->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pDepthMarketData->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pDepthMarketData->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pDepthMarketData->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pDepthMarketData->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UpdateTime"), String::NewFromUtf8(isolate, pDepthMarketData->UpdateTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UpdateMillisec"), Number::New(isolate, pDepthMarketData->UpdateMillisec));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume1"), Number::New(isolate, pDepthMarketData->BidVolume1));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume1"), Number::New(isolate, pDepthMarketData->AskVolume1));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume2"), Number::New(isolate, pDepthMarketData->BidVolume2));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume2"), Number::New(isolate, pDepthMarketData->AskVolume2));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume3"), Number::New(isolate, pDepthMarketData->BidVolume3));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume3"), Number::New(isolate, pDepthMarketData->AskVolume3));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume4"), Number::New(isolate, pDepthMarketData->BidVolume4));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume4"), Number::New(isolate, pDepthMarketData->AskVolume4));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume5"), Number::New(isolate, pDepthMarketData->BidVolume5));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume5"), Number::New(isolate, pDepthMarketData->AskVolume5));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDay"), String::NewFromUtf8(isolate, pDepthMarketData->ActionDay));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrysettlementinfo(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcSettlementInfoField *pSettlementInfo = static_cast<CThostFtdcSettlementInfoField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pSettlementInfo->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pSettlementInfo->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pSettlementInfo->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pSettlementInfo->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pSettlementInfo->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Content"), String::NewFromUtf8(isolate, pSettlementInfo->Content));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pSettlementInfo->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pSettlementInfo->CurrencyID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrytransferbank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTransferBankField *pTransferBank = static_cast<CThostFtdcTransferBankField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pTransferBank->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBrchID"), String::NewFromUtf8(isolate, pTransferBank->BankBrchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankName"), String::NewFromUtf8(isolate, pTransferBank->BankName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsActive"), Number::New(isolate, pTransferBank->IsActive));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinvestorpositiondetail(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail = static_cast<CThostFtdcInvestorPositionDetailField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInvestorPositionDetail->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInvestorPositionDetail->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInvestorPositionDetail->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInvestorPositionDetail->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pInvestorPositionDetail->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OpenDate"), String::NewFromUtf8(isolate, pInvestorPositionDetail->OpenDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeID"), String::NewFromUtf8(isolate, pInvestorPositionDetail->TradeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pInvestorPositionDetail->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pInvestorPositionDetail->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pInvestorPositionDetail->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeType"), String::NewFromUtf8(isolate, charto_string(pInvestorPositionDetail->TradeType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombInstrumentID"), String::NewFromUtf8(isolate, pInvestorPositionDetail->CombInstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInvestorPositionDetail->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CloseVolume"), Number::New(isolate, pInvestorPositionDetail->CloseVolume));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrynotice(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcNoticeField *pNotice = static_cast<CThostFtdcNoticeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pNotice->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Content"), String::NewFromUtf8(isolate, pNotice->Content));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceLabel"), String::NewFromUtf8(isolate, pNotice->SequenceLabel));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrysettlementinfoconfirm(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm = static_cast<CThostFtdcSettlementInfoConfirmField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ConfirmDate"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->ConfirmDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ConfirmTime"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->ConfirmTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pSettlementInfoConfirm->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pSettlementInfoConfirm->CurrencyID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinvestorpositioncombinedetail(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail = static_cast<CThostFtdcInvestorPositionCombineDetailField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OpenDate"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->OpenDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pInvestorPositionCombineDetail->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ComTradeID"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->ComTradeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeID"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->TradeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInvestorPositionCombineDetail->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pInvestorPositionCombineDetail->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TotalAmt"), Number::New(isolate, pInvestorPositionCombineDetail->TotalAmt));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LegID"), Number::New(isolate, pInvestorPositionCombineDetail->LegID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LegMultiple"), Number::New(isolate, pInvestorPositionCombineDetail->LegMultiple));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombInstrumentID"), String::NewFromUtf8(isolate, pInvestorPositionCombineDetail->CombInstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeGroupID"), Number::New(isolate, pInvestorPositionCombineDetail->TradeGroupID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrycfmmctradingaccountkey(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey = static_cast<CThostFtdcCFMMCTradingAccountKeyField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pCFMMCTradingAccountKey->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pCFMMCTradingAccountKey->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pCFMMCTradingAccountKey->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "KeyID"), Number::New(isolate, pCFMMCTradingAccountKey->KeyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrentKey"), String::NewFromUtf8(isolate, pCFMMCTradingAccountKey->CurrentKey));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryewarrantoffset(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcEWarrantOffsetField *pEWarrantOffset = static_cast<CThostFtdcEWarrantOffsetField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pEWarrantOffset->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pEWarrantOffset->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pEWarrantOffset->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pEWarrantOffset->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pEWarrantOffset->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pEWarrantOffset->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pEWarrantOffset->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pEWarrantOffset->Volume));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinvestorproductgroupmargin(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin = static_cast<CThostFtdcInvestorProductGroupMarginField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductGroupID"), String::NewFromUtf8(isolate, pInvestorProductGroupMargin->ProductGroupID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInvestorProductGroupMargin->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInvestorProductGroupMargin->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pInvestorProductGroupMargin->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pInvestorProductGroupMargin->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInvestorProductGroupMargin->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInvestorProductGroupMargin->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryexchangemarginrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcExchangeMarginRateField *pExchangeMarginRate = static_cast<CThostFtdcExchangeMarginRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pExchangeMarginRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pExchangeMarginRate->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pExchangeMarginRate->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pExchangeMarginRate->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryexchangemarginrateadjust(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust = static_cast<CThostFtdcExchangeMarginRateAdjustField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pExchangeMarginRateAdjust->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pExchangeMarginRateAdjust->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pExchangeMarginRateAdjust->HedgeFlag).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryexchangerate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcExchangeRateField *pExchangeRate = static_cast<CThostFtdcExchangeRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pExchangeRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FromCurrencyID"), String::NewFromUtf8(isolate, pExchangeRate->FromCurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ToCurrencyID"), String::NewFromUtf8(isolate, pExchangeRate->ToCurrencyID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrysecagentacidmap(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap = static_cast<CThostFtdcSecAgentACIDMapField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pSecAgentACIDMap->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pSecAgentACIDMap->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pSecAgentACIDMap->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pSecAgentACIDMap->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerSecAgentID"), String::NewFromUtf8(isolate, pSecAgentACIDMap->BrokerSecAgentID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryproductexchrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcProductExchRateField *pProductExchRate = static_cast<CThostFtdcProductExchRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductID"), String::NewFromUtf8(isolate, pProductExchRate->ProductID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteCurrencyID"), String::NewFromUtf8(isolate, pProductExchRate->QuoteCurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pProductExchRate->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryproductgroup(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcProductGroupField *pProductGroup = static_cast<CThostFtdcProductGroupField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductID"), String::NewFromUtf8(isolate, pProductGroup->ProductID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pProductGroup->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ProductGroupID"), String::NewFromUtf8(isolate, pProductGroup->ProductGroupID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrymminstrumentcommissionrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate = static_cast<CThostFtdcMMInstrumentCommissionRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pMMInstrumentCommissionRate->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorRange"), String::NewFromUtf8(isolate, charto_string(pMMInstrumentCommissionRate->InvestorRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pMMInstrumentCommissionRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pMMInstrumentCommissionRate->InvestorID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrymmoptioninstrcommrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate = static_cast<CThostFtdcMMOptionInstrCommRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pMMOptionInstrCommRate->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorRange"), String::NewFromUtf8(isolate, charto_string(pMMOptionInstrCommRate->InvestorRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pMMOptionInstrCommRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pMMOptionInstrCommRate->InvestorID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinstrumentordercommrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate = static_cast<CThostFtdcInstrumentOrderCommRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInstrumentOrderCommRate->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorRange"), String::NewFromUtf8(isolate, charto_string(pInstrumentOrderCommRate->InvestorRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInstrumentOrderCommRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInstrumentOrderCommRate->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInstrumentOrderCommRate->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInstrumentOrderCommRate->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrysecagenttradingaccount(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradingAccountField *pTradingAccount = static_cast<CThostFtdcTradingAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTradingAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pTradingAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pTradingAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pTradingAccount->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pTradingAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BizType"), String::NewFromUtf8(isolate, charto_string(pTradingAccount->BizType).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrysecagentcheckmode(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode = static_cast<CThostFtdcSecAgentCheckModeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pSecAgentCheckMode->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pSecAgentCheckMode->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pSecAgentCheckMode->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerSecAgentID"), String::NewFromUtf8(isolate, pSecAgentCheckMode->BrokerSecAgentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CheckSelfAccount"), Number::New(isolate, pSecAgentCheckMode->CheckSelfAccount));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryoptioninstrtradecost(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost = static_cast<CThostFtdcOptionInstrTradeCostField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOptionInstrTradeCost->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOptionInstrTradeCost->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOptionInstrTradeCost->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pOptionInstrTradeCost->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOptionInstrTradeCost->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryoptioninstrcommrate(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate = static_cast<CThostFtdcOptionInstrCommRateField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOptionInstrCommRate->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorRange"), String::NewFromUtf8(isolate, charto_string(pOptionInstrCommRate->InvestorRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOptionInstrCommRate->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOptionInstrCommRate->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOptionInstrCommRate->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryexecorder(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcExecOrderField *pExecOrder = static_cast<CThostFtdcExecOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pExecOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pExecOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pExecOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderRef"), String::NewFromUtf8(isolate, pExecOrder->ExecOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pExecOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pExecOrder->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pExecOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pExecOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OffsetFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->OffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionType"), String::NewFromUtf8(isolate, charto_string(pExecOrder->ActionType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PosiDirection"), String::NewFromUtf8(isolate, charto_string(pExecOrder->PosiDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ReservePositionFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->ReservePositionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CloseFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->CloseFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderLocalID"), String::NewFromUtf8(isolate, pExecOrder->ExecOrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pExecOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pExecOrder->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pExecOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pExecOrder->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pExecOrder->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pExecOrder->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pExecOrder->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pExecOrder->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pExecOrder->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pExecOrder->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderSysID"), String::NewFromUtf8(isolate, pExecOrder->ExecOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pExecOrder->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pExecOrder->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pExecOrder->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecResult"), String::NewFromUtf8(isolate, charto_string(pExecOrder->ExecResult).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pExecOrder->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pExecOrder->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pExecOrder->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pExecOrder->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pExecOrder->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pExecOrder->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pExecOrder->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerExecOrderSeq"), Number::New(isolate, pExecOrder->BrokerExecOrderSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pExecOrder->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pExecOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pExecOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pExecOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pExecOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryforquote(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcForQuoteField *pForQuote = static_cast<CThostFtdcForQuoteField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pForQuote->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pForQuote->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pForQuote->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteRef"), String::NewFromUtf8(isolate, pForQuote->ForQuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pForQuote->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteLocalID"), String::NewFromUtf8(isolate, pForQuote->ForQuoteLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pForQuote->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pForQuote->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pForQuote->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pForQuote->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pForQuote->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pForQuote->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pForQuote->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pForQuote->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteStatus"), String::NewFromUtf8(isolate, charto_string(pForQuote->ForQuoteStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pForQuote->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pForQuote->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pForQuote->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pForQuote->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerForQutoSeq"), Number::New(isolate, pForQuote->BrokerForQutoSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pForQuote->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pForQuote->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryquote(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcQuoteField *pQuote = static_cast<CThostFtdcQuoteField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pQuote->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pQuote->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pQuote->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteRef"), String::NewFromUtf8(isolate, pQuote->QuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pQuote->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume"), Number::New(isolate, pQuote->AskVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume"), Number::New(isolate, pQuote->BidVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pQuote->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pQuote->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->AskOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->BidOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->AskHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->BidHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteLocalID"), String::NewFromUtf8(isolate, pQuote->QuoteLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pQuote->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pQuote->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pQuote->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pQuote->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pQuote->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pQuote->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pQuote->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pQuote->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pQuote->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pQuote->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteSysID"), String::NewFromUtf8(isolate, pQuote->QuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pQuote->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pQuote->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pQuote->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteStatus"), String::NewFromUtf8(isolate, charto_string(pQuote->QuoteStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pQuote->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pQuote->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOrderSysID"), String::NewFromUtf8(isolate, pQuote->AskOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOrderSysID"), String::NewFromUtf8(isolate, pQuote->BidOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pQuote->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pQuote->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pQuote->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pQuote->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pQuote->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerQuoteSeq"), Number::New(isolate, pQuote->BrokerQuoteSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOrderRef"), String::NewFromUtf8(isolate, pQuote->AskOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOrderRef"), String::NewFromUtf8(isolate, pQuote->BidOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteSysID"), String::NewFromUtf8(isolate, pQuote->ForQuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pQuote->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pQuote->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pQuote->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pQuote->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pQuote->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryoptionselfclose(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOptionSelfCloseField *pOptionSelfClose = static_cast<CThostFtdcOptionSelfCloseField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOptionSelfClose->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOptionSelfClose->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOptionSelfClose->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseRef"), String::NewFromUtf8(isolate, pOptionSelfClose->OptionSelfCloseRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pOptionSelfClose->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pOptionSelfClose->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pOptionSelfClose->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pOptionSelfClose->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pOptionSelfClose->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseLocalID"), String::NewFromUtf8(isolate, pOptionSelfClose->OptionSelfCloseLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOptionSelfClose->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pOptionSelfClose->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pOptionSelfClose->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pOptionSelfClose->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pOptionSelfClose->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pOptionSelfClose->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pOptionSelfClose->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pOptionSelfClose->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pOptionSelfClose->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pOptionSelfClose->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseSysID"), String::NewFromUtf8(isolate, pOptionSelfClose->OptionSelfCloseSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pOptionSelfClose->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pOptionSelfClose->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pOptionSelfClose->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecResult"), String::NewFromUtf8(isolate, charto_string(pOptionSelfClose->ExecResult).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pOptionSelfClose->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pOptionSelfClose->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pOptionSelfClose->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pOptionSelfClose->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pOptionSelfClose->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pOptionSelfClose->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pOptionSelfClose->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerOptionSelfCloseSeq"), Number::New(isolate, pOptionSelfClose->BrokerOptionSelfCloseSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pOptionSelfClose->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pOptionSelfClose->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pOptionSelfClose->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pOptionSelfClose->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pOptionSelfClose->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryinvestunit(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInvestUnitField *pInvestUnit = static_cast<CThostFtdcInvestUnitField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInvestUnit->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInvestUnit->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorUnitName"), String::NewFromUtf8(isolate, pInvestUnit->InvestorUnitName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorGroupID"), String::NewFromUtf8(isolate, pInvestUnit->InvestorGroupID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CommModelID"), String::NewFromUtf8(isolate, pInvestUnit->CommModelID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MarginModelID"), String::NewFromUtf8(isolate, pInvestUnit->MarginModelID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pInvestUnit->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pInvestUnit->CurrencyID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrycombinstrumentguard(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard = static_cast<CThostFtdcCombInstrumentGuardField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pCombInstrumentGuard->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pCombInstrumentGuard->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pCombInstrumentGuard->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrycombaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcCombActionField *pCombAction = static_cast<CThostFtdcCombActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pCombAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pCombAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pCombAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombActionRef"), String::NewFromUtf8(isolate, pCombAction->CombActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pCombAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pCombAction->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pCombAction->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombDirection"), String::NewFromUtf8(isolate, charto_string(pCombAction->CombDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pCombAction->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionLocalID"), String::NewFromUtf8(isolate, pCombAction->ActionLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pCombAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pCombAction->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pCombAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pCombAction->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pCombAction->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pCombAction->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionStatus"), String::NewFromUtf8(isolate, charto_string(pCombAction->ActionStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pCombAction->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pCombAction->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pCombAction->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pCombAction->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pCombAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pCombAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pCombAction->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pCombAction->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pCombAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pCombAction->MacAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ComTradeID"), String::NewFromUtf8(isolate, pCombAction->ComTradeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pCombAction->BranchID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrytransferserial(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTransferSerialField *pTransferSerial = static_cast<CThostFtdcTransferSerialField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pTransferSerial->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pTransferSerial->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pTransferSerial->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pTransferSerial->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pTransferSerial->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pTransferSerial->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pTransferSerial->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pTransferSerial->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pTransferSerial->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pTransferSerial->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pTransferSerial->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTransferSerial->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pTransferSerial->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureAccType"), String::NewFromUtf8(isolate, charto_string(pTransferSerial->FutureAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pTransferSerial->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pTransferSerial->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pTransferSerial->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pTransferSerial->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pTransferSerial->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pTransferSerial->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AvailabilityFlag"), String::NewFromUtf8(isolate, charto_string(pTransferSerial->AvailabilityFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperatorCode"), String::NewFromUtf8(isolate, pTransferSerial->OperatorCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankNewAccount"), String::NewFromUtf8(isolate, pTransferSerial->BankNewAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pTransferSerial->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pTransferSerial->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryaccountregister(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcAccountregisterField *pAccountregister = static_cast<CThostFtdcAccountregisterField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDay"), String::NewFromUtf8(isolate, pAccountregister->TradeDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pAccountregister->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pAccountregister->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pAccountregister->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pAccountregister->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pAccountregister->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pAccountregister->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pAccountregister->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pAccountregister->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pAccountregister->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pAccountregister->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OpenOrDestroy"), String::NewFromUtf8(isolate, charto_string(pAccountregister->OpenOrDestroy).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RegDate"), String::NewFromUtf8(isolate, pAccountregister->RegDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OutDate"), String::NewFromUtf8(isolate, pAccountregister->OutDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pAccountregister->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pAccountregister->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pAccountregister->BankAccType).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrtnorder(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOrderField *pOrder = static_cast<CThostFtdcOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pOrder->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderPriceType"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pOrder->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombOffsetFlag"), String::NewFromUtf8(isolate, pOrder->CombOffsetFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombHedgeFlag"), String::NewFromUtf8(isolate, pOrder->CombHedgeFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotalOriginal"), Number::New(isolate, pOrder->VolumeTotalOriginal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TimeCondition"), String::NewFromUtf8(isolate, charto_string(pOrder->TimeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "GTDDate"), String::NewFromUtf8(isolate, pOrder->GTDDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeCondition"), String::NewFromUtf8(isolate, charto_string(pOrder->VolumeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinVolume"), Number::New(isolate, pOrder->MinVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ContingentCondition"), String::NewFromUtf8(isolate, charto_string(pOrder->ContingentCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForceCloseReason"), String::NewFromUtf8(isolate, charto_string(pOrder->ForceCloseReason).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsAutoSuspend"), Number::New(isolate, pOrder->IsAutoSuspend));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderLocalID"), String::NewFromUtf8(isolate, pOrder->OrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pOrder->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pOrder->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pOrder->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pOrder->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pOrder->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pOrder->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pOrder->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pOrder->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSource"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderSource).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderStatus"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderType"), String::NewFromUtf8(isolate, charto_string(pOrder->OrderType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTraded"), Number::New(isolate, pOrder->VolumeTraded));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotal"), Number::New(isolate, pOrder->VolumeTotal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pOrder->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pOrder->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveTime"), String::NewFromUtf8(isolate, pOrder->ActiveTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SuspendTime"), String::NewFromUtf8(isolate, pOrder->SuspendTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UpdateTime"), String::NewFromUtf8(isolate, pOrder->UpdateTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pOrder->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveTraderID"), String::NewFromUtf8(isolate, pOrder->ActiveTraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pOrder->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pOrder->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pOrder->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pOrder->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pOrder->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pOrder->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserForceClose"), Number::New(isolate, pOrder->UserForceClose));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pOrder->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerOrderSeq"), Number::New(isolate, pOrder->BrokerOrderSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RelativeOrderSysID"), String::NewFromUtf8(isolate, pOrder->RelativeOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ZCETotalTradedVolume"), Number::New(isolate, pOrder->ZCETotalTradedVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsSwapOrder"), Number::New(isolate, pOrder->IsSwapOrder));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pOrder->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtntrade(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradeField *pTrade = static_cast<CThostFtdcTradeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTrade->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pTrade->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pTrade->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pTrade->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pTrade->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pTrade->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeID"), String::NewFromUtf8(isolate, pTrade->TradeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pTrade->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pTrade->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pTrade->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pTrade->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingRole"), String::NewFromUtf8(isolate, charto_string(pTrade->TradingRole).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pTrade->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OffsetFlag"), String::NewFromUtf8(isolate, charto_string(pTrade->OffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pTrade->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pTrade->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pTrade->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pTrade->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeType"), String::NewFromUtf8(isolate, charto_string(pTrade->TradeType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PriceSource"), String::NewFromUtf8(isolate, charto_string(pTrade->PriceSource).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pTrade->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderLocalID"), String::NewFromUtf8(isolate, pTrade->OrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pTrade->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pTrade->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pTrade->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pTrade->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pTrade->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerOrderSeq"), Number::New(isolate, pTrade->BrokerOrderSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeSource"), String::NewFromUtf8(isolate, charto_string(pTrade->TradeSource).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onerrrtnorderinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputOrderField *pInputOrder = static_cast<CThostFtdcInputOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pInputOrder->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderPriceType"), String::NewFromUtf8(isolate, charto_string(pInputOrder->OrderPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pInputOrder->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombOffsetFlag"), String::NewFromUtf8(isolate, pInputOrder->CombOffsetFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombHedgeFlag"), String::NewFromUtf8(isolate, pInputOrder->CombHedgeFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotalOriginal"), Number::New(isolate, pInputOrder->VolumeTotalOriginal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TimeCondition"), String::NewFromUtf8(isolate, charto_string(pInputOrder->TimeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "GTDDate"), String::NewFromUtf8(isolate, pInputOrder->GTDDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeCondition"), String::NewFromUtf8(isolate, charto_string(pInputOrder->VolumeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinVolume"), Number::New(isolate, pInputOrder->MinVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ContingentCondition"), String::NewFromUtf8(isolate, charto_string(pInputOrder->ContingentCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForceCloseReason"), String::NewFromUtf8(isolate, charto_string(pInputOrder->ForceCloseReason).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsAutoSuspend"), Number::New(isolate, pInputOrder->IsAutoSuspend));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserForceClose"), Number::New(isolate, pInputOrder->UserForceClose));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsSwapOrder"), Number::New(isolate, pInputOrder->IsSwapOrder));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pInputOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pInputOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOrderActionField *pOrderAction = static_cast<CThostFtdcOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionRef"), Number::New(isolate, pOrderAction->OrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pOrderAction->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pOrderAction->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pOrderAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeChange"), Number::New(isolate, pOrderAction->VolumeChange));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDate"), String::NewFromUtf8(isolate, pOrderAction->ActionDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionTime"), String::NewFromUtf8(isolate, pOrderAction->ActionTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pOrderAction->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pOrderAction->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderLocalID"), String::NewFromUtf8(isolate, pOrderAction->OrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionLocalID"), String::NewFromUtf8(isolate, pOrderAction->ActionLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pOrderAction->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pOrderAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pOrderAction->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionStatus"), String::NewFromUtf8(isolate, charto_string(pOrderAction->OrderActionStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pOrderAction->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOrderAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pOrderAction->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onrtninstrumentstatus(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInstrumentStatusField *pInstrumentStatus = static_cast<CThostFtdcInstrumentStatusField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInstrumentStatus->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pInstrumentStatus->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementGroupID"), String::NewFromUtf8(isolate, pInstrumentStatus->SettlementGroupID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInstrumentStatus->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentStatus"), String::NewFromUtf8(isolate, charto_string(pInstrumentStatus->InstrumentStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingSegmentSN"), Number::New(isolate, pInstrumentStatus->TradingSegmentSN));
    jsonRtn->Set(String::NewFromUtf8(isolate, "EnterTime"), String::NewFromUtf8(isolate, pInstrumentStatus->EnterTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "EnterReason"), String::NewFromUtf8(isolate, charto_string(pInstrumentStatus->EnterReason).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnbulletin(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcBulletinField *pBulletin = static_cast<CThostFtdcBulletinField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pBulletin->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pBulletin->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pBulletin->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SendTime"), String::NewFromUtf8(isolate, pBulletin->SendTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Content"), String::NewFromUtf8(isolate, pBulletin->Content));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MarketID"), String::NewFromUtf8(isolate, pBulletin->MarketID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtntradingnotice(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo = static_cast<CThostFtdcTradingNoticeInfoField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTradingNoticeInfo->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pTradingNoticeInfo->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SendTime"), String::NewFromUtf8(isolate, pTradingNoticeInfo->SendTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FieldContent"), String::NewFromUtf8(isolate, pTradingNoticeInfo->FieldContent));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceSeries"), Number::New(isolate, pTradingNoticeInfo->SequenceSeries));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pTradingNoticeInfo->SequenceNo));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnerrorconditionalorder(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder = static_cast<CThostFtdcErrorConditionalOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pErrorConditionalOrder->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderPriceType"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->OrderPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombOffsetFlag"), String::NewFromUtf8(isolate, pErrorConditionalOrder->CombOffsetFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombHedgeFlag"), String::NewFromUtf8(isolate, pErrorConditionalOrder->CombHedgeFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotalOriginal"), Number::New(isolate, pErrorConditionalOrder->VolumeTotalOriginal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TimeCondition"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->TimeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "GTDDate"), String::NewFromUtf8(isolate, pErrorConditionalOrder->GTDDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeCondition"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->VolumeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinVolume"), Number::New(isolate, pErrorConditionalOrder->MinVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ContingentCondition"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->ContingentCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForceCloseReason"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->ForceCloseReason).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsAutoSuspend"), Number::New(isolate, pErrorConditionalOrder->IsAutoSuspend));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pErrorConditionalOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pErrorConditionalOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderLocalID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->OrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pErrorConditionalOrder->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pErrorConditionalOrder->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pErrorConditionalOrder->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pErrorConditionalOrder->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSource"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->OrderSource).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderStatus"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->OrderStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderType"), String::NewFromUtf8(isolate, charto_string(pErrorConditionalOrder->OrderType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTraded"), Number::New(isolate, pErrorConditionalOrder->VolumeTraded));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotal"), Number::New(isolate, pErrorConditionalOrder->VolumeTotal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pErrorConditionalOrder->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pErrorConditionalOrder->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveTime"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ActiveTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SuspendTime"), String::NewFromUtf8(isolate, pErrorConditionalOrder->SuspendTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UpdateTime"), String::NewFromUtf8(isolate, pErrorConditionalOrder->UpdateTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pErrorConditionalOrder->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveTraderID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ActiveTraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pErrorConditionalOrder->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pErrorConditionalOrder->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pErrorConditionalOrder->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pErrorConditionalOrder->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pErrorConditionalOrder->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserForceClose"), Number::New(isolate, pErrorConditionalOrder->UserForceClose));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerOrderSeq"), Number::New(isolate, pErrorConditionalOrder->BrokerOrderSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RelativeOrderSysID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->RelativeOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ZCETotalTradedVolume"), Number::New(isolate, pErrorConditionalOrder->ZCETotalTradedVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pErrorConditionalOrder->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pErrorConditionalOrder->ErrorMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsSwapOrder"), Number::New(isolate, pErrorConditionalOrder->IsSwapOrder));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pErrorConditionalOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pErrorConditionalOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pErrorConditionalOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnexecorder(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcExecOrderField *pExecOrder = static_cast<CThostFtdcExecOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pExecOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pExecOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pExecOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderRef"), String::NewFromUtf8(isolate, pExecOrder->ExecOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pExecOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pExecOrder->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pExecOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pExecOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OffsetFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->OffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionType"), String::NewFromUtf8(isolate, charto_string(pExecOrder->ActionType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PosiDirection"), String::NewFromUtf8(isolate, charto_string(pExecOrder->PosiDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ReservePositionFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->ReservePositionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CloseFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrder->CloseFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderLocalID"), String::NewFromUtf8(isolate, pExecOrder->ExecOrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pExecOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pExecOrder->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pExecOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pExecOrder->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pExecOrder->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pExecOrder->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pExecOrder->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pExecOrder->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pExecOrder->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pExecOrder->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderSysID"), String::NewFromUtf8(isolate, pExecOrder->ExecOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pExecOrder->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pExecOrder->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pExecOrder->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecResult"), String::NewFromUtf8(isolate, charto_string(pExecOrder->ExecResult).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pExecOrder->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pExecOrder->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pExecOrder->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pExecOrder->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pExecOrder->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pExecOrder->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pExecOrder->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerExecOrderSeq"), Number::New(isolate, pExecOrder->BrokerExecOrderSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pExecOrder->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pExecOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pExecOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pExecOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pExecOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onerrrtnexecorderinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputExecOrderField *pInputExecOrder = static_cast<CThostFtdcInputExecOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputExecOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputExecOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputExecOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderRef"), String::NewFromUtf8(isolate, pInputExecOrder->ExecOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputExecOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pInputExecOrder->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputExecOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputExecOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OffsetFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->OffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionType"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->ActionType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PosiDirection"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->PosiDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ReservePositionFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->ReservePositionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CloseFlag"), String::NewFromUtf8(isolate, charto_string(pInputExecOrder->CloseFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputExecOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pInputExecOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pInputExecOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputExecOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputExecOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputExecOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnexecorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcExecOrderActionField *pExecOrderAction = static_cast<CThostFtdcExecOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pExecOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pExecOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderActionRef"), Number::New(isolate, pExecOrderAction->ExecOrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderRef"), String::NewFromUtf8(isolate, pExecOrderAction->ExecOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pExecOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pExecOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pExecOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pExecOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderSysID"), String::NewFromUtf8(isolate, pExecOrderAction->ExecOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pExecOrderAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDate"), String::NewFromUtf8(isolate, pExecOrderAction->ActionDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionTime"), String::NewFromUtf8(isolate, pExecOrderAction->ActionTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pExecOrderAction->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pExecOrderAction->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecOrderLocalID"), String::NewFromUtf8(isolate, pExecOrderAction->ExecOrderLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionLocalID"), String::NewFromUtf8(isolate, pExecOrderAction->ActionLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pExecOrderAction->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pExecOrderAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pExecOrderAction->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionStatus"), String::NewFromUtf8(isolate, charto_string(pExecOrderAction->OrderActionStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pExecOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionType"), String::NewFromUtf8(isolate, charto_string(pExecOrderAction->ActionType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pExecOrderAction->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pExecOrderAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pExecOrderAction->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pExecOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pExecOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnforquoteinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputForQuoteField *pInputForQuote = static_cast<CThostFtdcInputForQuoteField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputForQuote->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputForQuote->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputForQuote->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteRef"), String::NewFromUtf8(isolate, pInputForQuote->ForQuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputForQuote->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputForQuote->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputForQuote->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputForQuote->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onrtnquote(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcQuoteField *pQuote = static_cast<CThostFtdcQuoteField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pQuote->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pQuote->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pQuote->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteRef"), String::NewFromUtf8(isolate, pQuote->QuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pQuote->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume"), Number::New(isolate, pQuote->AskVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume"), Number::New(isolate, pQuote->BidVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pQuote->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pQuote->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->AskOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->BidOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->AskHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pQuote->BidHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteLocalID"), String::NewFromUtf8(isolate, pQuote->QuoteLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pQuote->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pQuote->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pQuote->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pQuote->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pQuote->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pQuote->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pQuote->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pQuote->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pQuote->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pQuote->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteSysID"), String::NewFromUtf8(isolate, pQuote->QuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pQuote->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pQuote->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pQuote->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteStatus"), String::NewFromUtf8(isolate, charto_string(pQuote->QuoteStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pQuote->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pQuote->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOrderSysID"), String::NewFromUtf8(isolate, pQuote->AskOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOrderSysID"), String::NewFromUtf8(isolate, pQuote->BidOrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pQuote->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pQuote->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pQuote->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pQuote->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pQuote->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerQuoteSeq"), Number::New(isolate, pQuote->BrokerQuoteSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOrderRef"), String::NewFromUtf8(isolate, pQuote->AskOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOrderRef"), String::NewFromUtf8(isolate, pQuote->BidOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteSysID"), String::NewFromUtf8(isolate, pQuote->ForQuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pQuote->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pQuote->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pQuote->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pQuote->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pQuote->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onerrrtnquoteinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputQuoteField *pInputQuote = static_cast<CThostFtdcInputQuoteField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputQuote->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputQuote->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputQuote->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteRef"), String::NewFromUtf8(isolate, pInputQuote->QuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputQuote->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskVolume"), Number::New(isolate, pInputQuote->AskVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidVolume"), Number::New(isolate, pInputQuote->BidVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputQuote->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputQuote->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->AskOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOffsetFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->BidOffsetFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->AskHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidHedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputQuote->BidHedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AskOrderRef"), String::NewFromUtf8(isolate, pInputQuote->AskOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BidOrderRef"), String::NewFromUtf8(isolate, pInputQuote->BidOrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteSysID"), String::NewFromUtf8(isolate, pInputQuote->ForQuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputQuote->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputQuote->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputQuote->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputQuote->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnquoteaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcQuoteActionField *pQuoteAction = static_cast<CThostFtdcQuoteActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pQuoteAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pQuoteAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteActionRef"), Number::New(isolate, pQuoteAction->QuoteActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteRef"), String::NewFromUtf8(isolate, pQuoteAction->QuoteRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pQuoteAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pQuoteAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pQuoteAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pQuoteAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteSysID"), String::NewFromUtf8(isolate, pQuoteAction->QuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pQuoteAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDate"), String::NewFromUtf8(isolate, pQuoteAction->ActionDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionTime"), String::NewFromUtf8(isolate, pQuoteAction->ActionTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pQuoteAction->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pQuoteAction->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "QuoteLocalID"), String::NewFromUtf8(isolate, pQuoteAction->QuoteLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionLocalID"), String::NewFromUtf8(isolate, pQuoteAction->ActionLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pQuoteAction->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pQuoteAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pQuoteAction->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionStatus"), String::NewFromUtf8(isolate, charto_string(pQuoteAction->OrderActionStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pQuoteAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pQuoteAction->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pQuoteAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pQuoteAction->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pQuoteAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pQuoteAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onrtnforquotersp(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcForQuoteRspField *pForQuoteRsp = static_cast<CThostFtdcForQuoteRspField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pForQuoteRsp->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pForQuoteRsp->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteSysID"), String::NewFromUtf8(isolate, pForQuoteRsp->ForQuoteSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForQuoteTime"), String::NewFromUtf8(isolate, pForQuoteRsp->ForQuoteTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDay"), String::NewFromUtf8(isolate, pForQuoteRsp->ActionDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pForQuoteRsp->ExchangeID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtncfmmctradingaccounttoken(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken = static_cast<CThostFtdcCFMMCTradingAccountTokenField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pCFMMCTradingAccountToken->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pCFMMCTradingAccountToken->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pCFMMCTradingAccountToken->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "KeyID"), Number::New(isolate, pCFMMCTradingAccountToken->KeyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Token"), String::NewFromUtf8(isolate, pCFMMCTradingAccountToken->Token));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onerrrtnbatchorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcBatchOrderActionField *pBatchOrderAction = static_cast<CThostFtdcBatchOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pBatchOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pBatchOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionRef"), Number::New(isolate, pBatchOrderAction->OrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pBatchOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pBatchOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pBatchOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pBatchOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDate"), String::NewFromUtf8(isolate, pBatchOrderAction->ActionDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionTime"), String::NewFromUtf8(isolate, pBatchOrderAction->ActionTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pBatchOrderAction->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pBatchOrderAction->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionLocalID"), String::NewFromUtf8(isolate, pBatchOrderAction->ActionLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pBatchOrderAction->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pBatchOrderAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pBatchOrderAction->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionStatus"), String::NewFromUtf8(isolate, charto_string(pBatchOrderAction->OrderActionStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pBatchOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pBatchOrderAction->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pBatchOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pBatchOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onrtnoptionselfclose(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOptionSelfCloseField *pOptionSelfClose = static_cast<CThostFtdcOptionSelfCloseField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOptionSelfClose->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOptionSelfClose->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOptionSelfClose->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseRef"), String::NewFromUtf8(isolate, pOptionSelfClose->OptionSelfCloseRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pOptionSelfClose->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pOptionSelfClose->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pOptionSelfClose->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pOptionSelfClose->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pOptionSelfClose->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseLocalID"), String::NewFromUtf8(isolate, pOptionSelfClose->OptionSelfCloseLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOptionSelfClose->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pOptionSelfClose->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pOptionSelfClose->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pOptionSelfClose->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pOptionSelfClose->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pOptionSelfClose->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSubmitStatus"), String::NewFromUtf8(isolate, charto_string(pOptionSelfClose->OrderSubmitStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pOptionSelfClose->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pOptionSelfClose->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pOptionSelfClose->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseSysID"), String::NewFromUtf8(isolate, pOptionSelfClose->OptionSelfCloseSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertDate"), String::NewFromUtf8(isolate, pOptionSelfClose->InsertDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InsertTime"), String::NewFromUtf8(isolate, pOptionSelfClose->InsertTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CancelTime"), String::NewFromUtf8(isolate, pOptionSelfClose->CancelTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExecResult"), String::NewFromUtf8(isolate, charto_string(pOptionSelfClose->ExecResult).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClearingPartID"), String::NewFromUtf8(isolate, pOptionSelfClose->ClearingPartID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pOptionSelfClose->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pOptionSelfClose->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pOptionSelfClose->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pOptionSelfClose->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pOptionSelfClose->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActiveUserID"), String::NewFromUtf8(isolate, pOptionSelfClose->ActiveUserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerOptionSelfCloseSeq"), Number::New(isolate, pOptionSelfClose->BrokerOptionSelfCloseSeq));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pOptionSelfClose->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pOptionSelfClose->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pOptionSelfClose->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pOptionSelfClose->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pOptionSelfClose->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onerrrtnoptionselfcloseinsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose = static_cast<CThostFtdcInputOptionSelfCloseField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseRef"), String::NewFromUtf8(isolate, pInputOptionSelfClose->OptionSelfCloseRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pInputOptionSelfClose->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pInputOptionSelfClose->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pInputOptionSelfClose->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputOptionSelfClose->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pInputOptionSelfClose->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputOptionSelfClose->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputOptionSelfClose->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnoptionselfcloseaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction = static_cast<CThostFtdcOptionSelfCloseActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseActionRef"), Number::New(isolate, pOptionSelfCloseAction->OptionSelfCloseActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseRef"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->OptionSelfCloseRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pOptionSelfCloseAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pOptionSelfCloseAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pOptionSelfCloseAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseSysID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->OptionSelfCloseSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pOptionSelfCloseAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionDate"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->ActionDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionTime"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->ActionTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pOptionSelfCloseAction->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionSelfCloseLocalID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->OptionSelfCloseLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionLocalID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->ActionLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionStatus"), String::NewFromUtf8(isolate, charto_string(pOptionSelfCloseAction->OrderActionStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->BranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pOptionSelfCloseAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onrtncombaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcCombActionField *pCombAction = static_cast<CThostFtdcCombActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pCombAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pCombAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pCombAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombActionRef"), String::NewFromUtf8(isolate, pCombAction->CombActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pCombAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pCombAction->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pCombAction->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombDirection"), String::NewFromUtf8(isolate, charto_string(pCombAction->CombDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pCombAction->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionLocalID"), String::NewFromUtf8(isolate, pCombAction->ActionLocalID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pCombAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParticipantID"), String::NewFromUtf8(isolate, pCombAction->ParticipantID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pCombAction->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeInstID"), String::NewFromUtf8(isolate, pCombAction->ExchangeInstID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TraderID"), String::NewFromUtf8(isolate, pCombAction->TraderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pCombAction->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionStatus"), String::NewFromUtf8(isolate, charto_string(pCombAction->ActionStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NotifySequence"), Number::New(isolate, pCombAction->NotifySequence));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pCombAction->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SettlementID"), Number::New(isolate, pCombAction->SettlementID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pCombAction->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pCombAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pCombAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserProductInfo"), String::NewFromUtf8(isolate, pCombAction->UserProductInfo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "StatusMsg"), String::NewFromUtf8(isolate, pCombAction->StatusMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pCombAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pCombAction->MacAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ComTradeID"), String::NewFromUtf8(isolate, pCombAction->ComTradeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BranchID"), String::NewFromUtf8(isolate, pCombAction->BranchID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onerrrtncombactioninsert(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcInputCombActionField *pInputCombAction = static_cast<CThostFtdcInputCombActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pInputCombAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pInputCombAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pInputCombAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombActionRef"), String::NewFromUtf8(isolate, pInputCombAction->CombActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pInputCombAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pInputCombAction->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Volume"), Number::New(isolate, pInputCombAction->Volume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombDirection"), String::NewFromUtf8(isolate, charto_string(pInputCombAction->CombDirection).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HedgeFlag"), String::NewFromUtf8(isolate, charto_string(pInputCombAction->HedgeFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pInputCombAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pInputCombAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pInputCombAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onrspqrycontractbank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcContractBankField *pContractBank = static_cast<CThostFtdcContractBankField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pContractBank->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pContractBank->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBrchID"), String::NewFromUtf8(isolate, pContractBank->BankBrchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankName"), String::NewFromUtf8(isolate, pContractBank->BankName));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryparkedorder(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcParkedOrderField *pParkedOrder = static_cast<CThostFtdcParkedOrderField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pParkedOrder->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pParkedOrder->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pParkedOrder->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pParkedOrder->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pParkedOrder->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderPriceType"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->OrderPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Direction"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->Direction).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombOffsetFlag"), String::NewFromUtf8(isolate, pParkedOrder->CombOffsetFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CombHedgeFlag"), String::NewFromUtf8(isolate, pParkedOrder->CombHedgeFlag));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeTotalOriginal"), Number::New(isolate, pParkedOrder->VolumeTotalOriginal));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TimeCondition"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->TimeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "GTDDate"), String::NewFromUtf8(isolate, pParkedOrder->GTDDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeCondition"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->VolumeCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MinVolume"), Number::New(isolate, pParkedOrder->MinVolume));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ContingentCondition"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->ContingentCondition).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ForceCloseReason"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->ForceCloseReason).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsAutoSuspend"), Number::New(isolate, pParkedOrder->IsAutoSuspend));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BusinessUnit"), String::NewFromUtf8(isolate, pParkedOrder->BusinessUnit));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pParkedOrder->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserForceClose"), Number::New(isolate, pParkedOrder->UserForceClose));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pParkedOrder->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParkedOrderID"), String::NewFromUtf8(isolate, pParkedOrder->ParkedOrderID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserType"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->UserType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Status"), String::NewFromUtf8(isolate, charto_string(pParkedOrder->Status).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pParkedOrder->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pParkedOrder->ErrorMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IsSwapOrder"), Number::New(isolate, pParkedOrder->IsSwapOrder));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pParkedOrder->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pParkedOrder->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ClientID"), String::NewFromUtf8(isolate, pParkedOrder->ClientID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pParkedOrder->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pParkedOrder->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqryparkedorderaction(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcParkedOrderActionField *pParkedOrderAction = static_cast<CThostFtdcParkedOrderActionField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pParkedOrderAction->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pParkedOrderAction->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderActionRef"), Number::New(isolate, pParkedOrderAction->OrderActionRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderRef"), String::NewFromUtf8(isolate, pParkedOrderAction->OrderRef));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pParkedOrderAction->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FrontID"), Number::New(isolate, pParkedOrderAction->FrontID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pParkedOrderAction->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pParkedOrderAction->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OrderSysID"), String::NewFromUtf8(isolate, pParkedOrderAction->OrderSysID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ActionFlag"), String::NewFromUtf8(isolate, charto_string(pParkedOrderAction->ActionFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VolumeChange"), Number::New(isolate, pParkedOrderAction->VolumeChange));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pParkedOrderAction->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pParkedOrderAction->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ParkedOrderActionID"), String::NewFromUtf8(isolate, pParkedOrderAction->ParkedOrderActionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserType"), String::NewFromUtf8(isolate, charto_string(pParkedOrderAction->UserType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Status"), String::NewFromUtf8(isolate, charto_string(pParkedOrderAction->Status).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pParkedOrderAction->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pParkedOrderAction->ErrorMsg));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IPAddress"), String::NewFromUtf8(isolate, pParkedOrderAction->IPAddress));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MacAddress"), String::NewFromUtf8(isolate, pParkedOrderAction->MacAddress));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrytradingnotice(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcTradingNoticeField *pTradingNotice = static_cast<CThostFtdcTradingNoticeField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pTradingNotice->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorRange"), String::NewFromUtf8(isolate, charto_string(pTradingNotice->InvestorRange).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pTradingNotice->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceSeries"), Number::New(isolate, pTradingNotice->SequenceSeries));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pTradingNotice->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SendTime"), String::NewFromUtf8(isolate, pTradingNotice->SendTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SequenceNo"), Number::New(isolate, pTradingNotice->SequenceNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FieldContent"), String::NewFromUtf8(isolate, pTradingNotice->FieldContent));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrybrokertradingparams(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcBrokerTradingParamsField *pBrokerTradingParams = static_cast<CThostFtdcBrokerTradingParamsField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pBrokerTradingParams->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pBrokerTradingParams->InvestorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MarginPriceType"), String::NewFromUtf8(isolate, charto_string(pBrokerTradingParams->MarginPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Algorithm"), String::NewFromUtf8(isolate, charto_string(pBrokerTradingParams->Algorithm).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AvailIncludeCloseProfit"), String::NewFromUtf8(isolate, charto_string(pBrokerTradingParams->AvailIncludeCloseProfit).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pBrokerTradingParams->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OptionRoyaltyPriceType"), String::NewFromUtf8(isolate, charto_string(pBrokerTradingParams->OptionRoyaltyPriceType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pBrokerTradingParams->AccountID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspqrybrokertradingalgos(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos = static_cast<CThostFtdcBrokerTradingAlgosField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pBrokerTradingAlgos->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ExchangeID"), String::NewFromUtf8(isolate, pBrokerTradingAlgos->ExchangeID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstrumentID"), String::NewFromUtf8(isolate, pBrokerTradingAlgos->InstrumentID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HandlePositionAlgoID"), String::NewFromUtf8(isolate, charto_string(pBrokerTradingAlgos->HandlePositionAlgoID).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FindMarginRateAlgoID"), String::NewFromUtf8(isolate, charto_string(pBrokerTradingAlgos->FindMarginRateAlgoID).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "HandleTradingAccountAlgoID"), String::NewFromUtf8(isolate, charto_string(pBrokerTradingAlgos->HandleTradingAccountAlgoID).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspquerycfmmctradingaccounttoken(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken = static_cast<CThostFtdcQueryCFMMCTradingAccountTokenField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pQueryCFMMCTradingAccountToken->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InvestorID"), String::NewFromUtf8(isolate, pQueryCFMMCTradingAccountToken->InvestorID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrtnfrombanktofuturebybank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspTransferField *pRspTransfer = static_cast<CThostFtdcRspTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspTransfer->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspTransfer->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnfromfuturetobankbybank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspTransferField *pRspTransfer = static_cast<CThostFtdcRspTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspTransfer->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspTransfer->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnrepealfrombanktofuturebybank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspRepealField *pRspRepeal = static_cast<CThostFtdcRspRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pRspRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pRspRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pRspRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pRspRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspRepeal->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspRepeal->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnrepealfromfuturetobankbybank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspRepealField *pRspRepeal = static_cast<CThostFtdcRspRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pRspRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pRspRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pRspRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pRspRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspRepeal->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspRepeal->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnfrombanktofuturebyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspTransferField *pRspTransfer = static_cast<CThostFtdcRspTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspTransfer->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspTransfer->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnfromfuturetobankbyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspTransferField *pRspTransfer = static_cast<CThostFtdcRspTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspTransfer->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspTransfer->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspTransfer->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnrepealfrombanktofuturebyfuturemanual(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspRepealField *pRspRepeal = static_cast<CThostFtdcRspRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pRspRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pRspRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pRspRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pRspRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspRepeal->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspRepeal->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnrepealfromfuturetobankbyfuturemanual(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspRepealField *pRspRepeal = static_cast<CThostFtdcRspRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pRspRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pRspRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pRspRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pRspRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspRepeal->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspRepeal->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnquerybankbalancebyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount = static_cast<CThostFtdcNotifyQueryAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pNotifyQueryAccount->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pNotifyQueryAccount->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pNotifyQueryAccount->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pNotifyQueryAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pNotifyQueryAccount->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pNotifyQueryAccount->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pNotifyQueryAccount->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pNotifyQueryAccount->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pNotifyQueryAccount->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pNotifyQueryAccount->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pNotifyQueryAccount->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pNotifyQueryAccount->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pNotifyQueryAccount->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pNotifyQueryAccount->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pNotifyQueryAccount->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pNotifyQueryAccount->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pNotifyQueryAccount->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pNotifyQueryAccount->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pNotifyQueryAccount->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pNotifyQueryAccount->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onerrrtnbanktofuturebyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqTransferField *pReqTransfer = static_cast<CThostFtdcReqTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pReqTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->TransferStatus).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnfuturetobankbyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqTransferField *pReqTransfer = static_cast<CThostFtdcReqTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pReqTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->TransferStatus).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnrepealbanktofuturebyfuturemanual(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqRepealField *pReqRepeal = static_cast<CThostFtdcReqRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pReqRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pReqRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pReqRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pReqRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pReqRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pReqRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->TransferStatus).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnrepealfuturetobankbyfuturemanual(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqRepealField *pReqRepeal = static_cast<CThostFtdcReqRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pReqRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pReqRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pReqRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pReqRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pReqRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pReqRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pReqRepeal->TransferStatus).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onerrrtnquerybankbalancebyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqQueryAccountField *pReqQueryAccount = static_cast<CThostFtdcReqQueryAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqQueryAccount->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqQueryAccount->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqQueryAccount->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqQueryAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqQueryAccount->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqQueryAccount->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqQueryAccount->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqQueryAccount->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqQueryAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqQueryAccount->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqQueryAccount->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqQueryAccount->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqQueryAccount->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqQueryAccount->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqQueryAccount->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqQueryAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqQueryAccount->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqQueryAccount->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqQueryAccount->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqQueryAccount->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqQueryAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqQueryAccount->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqQueryAccount->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqQueryAccount->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqQueryAccount->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqQueryAccount->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqQueryAccount->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqQueryAccount->TID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  return;
}

void CTPTrader::pkg_cb_onrtnrepealfrombanktofuturebyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspRepealField *pRspRepeal = static_cast<CThostFtdcRspRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pRspRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pRspRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pRspRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pRspRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspRepeal->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspRepeal->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnrepealfromfuturetobankbyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcRspRepealField *pRspRepeal = static_cast<CThostFtdcRspRepealField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealTimeInterval"), Number::New(isolate, pRspRepeal->RepealTimeInterval));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RepealedTimes"), Number::New(isolate, pRspRepeal->RepealedTimes));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerRepealFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BrokerRepealFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateRepealSerial"), Number::New(isolate, pRspRepeal->PlateRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankRepealSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureRepealSerial"), Number::New(isolate, pRspRepeal->FutureRepealSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pRspRepeal->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pRspRepeal->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pRspRepeal->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pRspRepeal->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pRspRepeal->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pRspRepeal->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pRspRepeal->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pRspRepeal->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pRspRepeal->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pRspRepeal->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pRspRepeal->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pRspRepeal->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pRspRepeal->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pRspRepeal->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pRspRepeal->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pRspRepeal->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pRspRepeal->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pRspRepeal->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pRspRepeal->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pRspRepeal->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pRspRepeal->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pRspRepeal->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pRspRepeal->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pRspRepeal->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pRspRepeal->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pRspRepeal->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pRspRepeal->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pRspRepeal->TransferStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pRspRepeal->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pRspRepeal->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrspfrombanktofuturebyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqTransferField *pReqTransfer = static_cast<CThostFtdcReqTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pReqTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->TransferStatus).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspfromfuturetobankbyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqTransferField *pReqTransfer = static_cast<CThostFtdcReqTransferField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqTransfer->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqTransfer->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqTransfer->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqTransfer->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqTransfer->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqTransfer->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqTransfer->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqTransfer->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqTransfer->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqTransfer->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqTransfer->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqTransfer->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqTransfer->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqTransfer->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqTransfer->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqTransfer->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqTransfer->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqTransfer->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqTransfer->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FeePayFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->FeePayFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Message"), String::NewFromUtf8(isolate, pReqTransfer->Message));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqTransfer->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqTransfer->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqTransfer->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqTransfer->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqTransfer->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqTransfer->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqTransfer->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TransferStatus"), String::NewFromUtf8(isolate, charto_string(pReqTransfer->TransferStatus).c_str()));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrspquerybankaccountmoneybyfuture(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcReqQueryAccountField *pReqQueryAccount = static_cast<CThostFtdcReqQueryAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pReqQueryAccount->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pReqQueryAccount->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pReqQueryAccount->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pReqQueryAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pReqQueryAccount->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pReqQueryAccount->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pReqQueryAccount->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pReqQueryAccount->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pReqQueryAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pReqQueryAccount->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pReqQueryAccount->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pReqQueryAccount->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pReqQueryAccount->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pReqQueryAccount->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pReqQueryAccount->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pReqQueryAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pReqQueryAccount->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "FutureSerial"), Number::New(isolate, pReqQueryAccount->FutureSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pReqQueryAccount->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pReqQueryAccount->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pReqQueryAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pReqQueryAccount->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pReqQueryAccount->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pReqQueryAccount->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pReqQueryAccount->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pReqQueryAccount->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pReqQueryAccount->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "RequestID"), Number::New(isolate, pReqQueryAccount->RequestID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pReqQueryAccount->TID));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  *(cbArray + 1) = pkg_rspinfo(data->rspInfo);
  *(cbArray + 2) = Number::New(isolate, data->nRequestID);
  *(cbArray + 3) = Boolean::New(isolate, data->bIsLast);
  return;
}

void CTPTrader::pkg_cb_onrtnopenaccountbybank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcOpenAccountField *pOpenAccount = static_cast<CThostFtdcOpenAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pOpenAccount->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pOpenAccount->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pOpenAccount->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pOpenAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pOpenAccount->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pOpenAccount->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pOpenAccount->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pOpenAccount->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pOpenAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pOpenAccount->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pOpenAccount->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pOpenAccount->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pOpenAccount->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Gender"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->Gender).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CountryCode"), String::NewFromUtf8(isolate, pOpenAccount->CountryCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Address"), String::NewFromUtf8(isolate, pOpenAccount->Address));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ZipCode"), String::NewFromUtf8(isolate, pOpenAccount->ZipCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Telephone"), String::NewFromUtf8(isolate, pOpenAccount->Telephone));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MobilePhone"), String::NewFromUtf8(isolate, pOpenAccount->MobilePhone));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Fax"), String::NewFromUtf8(isolate, pOpenAccount->Fax));
    jsonRtn->Set(String::NewFromUtf8(isolate, "EMail"), String::NewFromUtf8(isolate, pOpenAccount->EMail));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MoneyAccountStatus"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->MoneyAccountStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pOpenAccount->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pOpenAccount->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pOpenAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pOpenAccount->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pOpenAccount->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pOpenAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CashExchangeCode"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->CashExchangeCode).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pOpenAccount->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pOpenAccount->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pOpenAccount->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pOpenAccount->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pOpenAccount->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pOpenAccount->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pOpenAccount->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pOpenAccount->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pOpenAccount->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pOpenAccount->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtncancelaccountbybank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcCancelAccountField *pCancelAccount = static_cast<CThostFtdcCancelAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pCancelAccount->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pCancelAccount->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pCancelAccount->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pCancelAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pCancelAccount->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pCancelAccount->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pCancelAccount->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pCancelAccount->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pCancelAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pCancelAccount->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pCancelAccount->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pCancelAccount->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pCancelAccount->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Gender"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->Gender).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CountryCode"), String::NewFromUtf8(isolate, pCancelAccount->CountryCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Address"), String::NewFromUtf8(isolate, pCancelAccount->Address));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ZipCode"), String::NewFromUtf8(isolate, pCancelAccount->ZipCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Telephone"), String::NewFromUtf8(isolate, pCancelAccount->Telephone));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MobilePhone"), String::NewFromUtf8(isolate, pCancelAccount->MobilePhone));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Fax"), String::NewFromUtf8(isolate, pCancelAccount->Fax));
    jsonRtn->Set(String::NewFromUtf8(isolate, "EMail"), String::NewFromUtf8(isolate, pCancelAccount->EMail));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MoneyAccountStatus"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->MoneyAccountStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pCancelAccount->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pCancelAccount->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pCancelAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pCancelAccount->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pCancelAccount->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pCancelAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CashExchangeCode"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->CashExchangeCode).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pCancelAccount->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "DeviceID"), String::NewFromUtf8(isolate, pCancelAccount->DeviceID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAccType"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->BankSecuAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pCancelAccount->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSecuAcc"), String::NewFromUtf8(isolate, pCancelAccount->BankSecuAcc));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pCancelAccount->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "OperNo"), String::NewFromUtf8(isolate, pCancelAccount->OperNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pCancelAccount->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "UserID"), String::NewFromUtf8(isolate, pCancelAccount->UserID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pCancelAccount->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pCancelAccount->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

void CTPTrader::pkg_cb_onrtnchangeaccountbybank(CbRtnField *data, Local <Value> *cbArray) {
  Isolate *isolate = Isolate::GetCurrent();

  if (data->rtnField) {
    CThostFtdcChangeAccountField *pChangeAccount = static_cast<CThostFtdcChangeAccountField *>(data->rtnField);
    Local <Object> jsonRtn = Object::New(isolate);
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeCode"), String::NewFromUtf8(isolate, pChangeAccount->TradeCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankID"), String::NewFromUtf8(isolate, pChangeAccount->BankID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankBranchID"), String::NewFromUtf8(isolate, pChangeAccount->BankBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerID"), String::NewFromUtf8(isolate, pChangeAccount->BrokerID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerBranchID"), String::NewFromUtf8(isolate, pChangeAccount->BrokerBranchID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeDate"), String::NewFromUtf8(isolate, pChangeAccount->TradeDate));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradeTime"), String::NewFromUtf8(isolate, pChangeAccount->TradeTime));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankSerial"), String::NewFromUtf8(isolate, pChangeAccount->BankSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TradingDay"), String::NewFromUtf8(isolate, pChangeAccount->TradingDay));
    jsonRtn->Set(String::NewFromUtf8(isolate, "PlateSerial"), Number::New(isolate, pChangeAccount->PlateSerial));
    jsonRtn->Set(String::NewFromUtf8(isolate, "LastFragment"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->LastFragment).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SessionID"), Number::New(isolate, pChangeAccount->SessionID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustomerName"), String::NewFromUtf8(isolate, pChangeAccount->CustomerName));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdCardType"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->IdCardType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "IdentifiedCardNo"), String::NewFromUtf8(isolate, pChangeAccount->IdentifiedCardNo));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Gender"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->Gender).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CountryCode"), String::NewFromUtf8(isolate, pChangeAccount->CountryCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CustType"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->CustType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Address"), String::NewFromUtf8(isolate, pChangeAccount->Address));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ZipCode"), String::NewFromUtf8(isolate, pChangeAccount->ZipCode));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Telephone"), String::NewFromUtf8(isolate, pChangeAccount->Telephone));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MobilePhone"), String::NewFromUtf8(isolate, pChangeAccount->MobilePhone));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Fax"), String::NewFromUtf8(isolate, pChangeAccount->Fax));
    jsonRtn->Set(String::NewFromUtf8(isolate, "EMail"), String::NewFromUtf8(isolate, pChangeAccount->EMail));
    jsonRtn->Set(String::NewFromUtf8(isolate, "MoneyAccountStatus"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->MoneyAccountStatus).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccount"), String::NewFromUtf8(isolate, pChangeAccount->BankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPassWord"), String::NewFromUtf8(isolate, pChangeAccount->BankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NewBankAccount"), String::NewFromUtf8(isolate, pChangeAccount->NewBankAccount));
    jsonRtn->Set(String::NewFromUtf8(isolate, "NewBankPassWord"), String::NewFromUtf8(isolate, pChangeAccount->NewBankPassWord));
    jsonRtn->Set(String::NewFromUtf8(isolate, "AccountID"), String::NewFromUtf8(isolate, pChangeAccount->AccountID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Password"), String::NewFromUtf8(isolate, pChangeAccount->Password));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankAccType"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->BankAccType).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "InstallID"), Number::New(isolate, pChangeAccount->InstallID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "VerifyCertNoFlag"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->VerifyCertNoFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "CurrencyID"), String::NewFromUtf8(isolate, pChangeAccount->CurrencyID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BrokerIDByBank"), String::NewFromUtf8(isolate, pChangeAccount->BrokerIDByBank));
    jsonRtn->Set(String::NewFromUtf8(isolate, "BankPwdFlag"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->BankPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "SecuPwdFlag"), String::NewFromUtf8(isolate, charto_string(pChangeAccount->SecuPwdFlag).c_str()));
    jsonRtn->Set(String::NewFromUtf8(isolate, "TID"), Number::New(isolate, pChangeAccount->TID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "Digest"), String::NewFromUtf8(isolate, pChangeAccount->Digest));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorID"), Number::New(isolate, pChangeAccount->ErrorID));
    jsonRtn->Set(String::NewFromUtf8(isolate, "ErrorMsg"), String::NewFromUtf8(isolate, pChangeAccount->ErrorMsg));
    *cbArray = jsonRtn;
  } else {
    *cbArray = Local<Value>::New(isolate, Undefined(isolate));
  }
  return;
}

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
