#ifndef CTP_MARKET_H_
#define CTP_MARKET_H_

#include <inttypes.h> /* strtoimax */
#include <iostream>
#include <string>
#include <node.h>
#include <node_object_wrap.h>

#include "ctp_utils.h"
#include "uv_market.h"
#include "ThostFtdcUserApiDataType.h"

using namespace v8;

class CTPMarket : public node::ObjectWrap {
public:
  CTPMarket(void);
  ~CTPMarket(void);

  static void Init(Isolate* isolate);
  static void NewInstance(const FunctionCallbackInfo<Value>& args);
  static void Disposed(const FunctionCallbackInfo<Value>& args);
  static void GetTradingDay(const FunctionCallbackInfo<Value>& args);
  static void On(const FunctionCallbackInfo<Value>& args);
  static void Connect(const FunctionCallbackInfo<Value>& args);
  static void ReqUserLogin(const FunctionCallbackInfo<Value>& args);
  static void ReqUserLogout(const FunctionCallbackInfo<Value>& args);

  static void SubscribeMarketData(const FunctionCallbackInfo<Value>& args);
  static void UnSubscribeMarketData(const FunctionCallbackInfo<Value>& args);
  static void SubscribeForQuoteRsp(const FunctionCallbackInfo<Value>& args);
  static void UnSubscribeForQuoteRsp(const FunctionCallbackInfo<Value>& args);

private:
  static Local<Value> pkg_rspinfo(void *vpRspInfo);

  uv_market* uvMarket;
  static int s_uuid;
  static void FunCallback(CbRtnField *data);
  static void FunRtnCallback(int result, void* baton);
  static Persistent<Function> constructor;
  static std::map<std::string, int> event_map;
  static std::map<int, Persistent<Function> > callback_map;
  static std::map<int, Persistent<Function> > fun_rtncb_map;

  static void initEventMap();
  static void New(const FunctionCallbackInfo<Value>& args);
  static void pkg_cb_onrsperror(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onfrontconnected(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onfrontdisconnected(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onheartbeatwarning(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspauthenticate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspuserlogin(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspuserlogout(CbRtnField* data, Local<Value>*cbArray);

  static void pkg_cb_onrspsubmarketdata(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspunsubmarketdata(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspsubforquotersp(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspunsubforquotersp(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtndepthmarketdata(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnforquotersp(CbRtnField* data, Local<Value>*cbArray);
};

#endif
