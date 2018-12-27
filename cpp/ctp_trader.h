
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
  static void ReqAuthenticate(const FunctionCallbackInfo<Value>& args);
  static void ReqUserLogin(const FunctionCallbackInfo<Value>& args);
  static void ReqUserLogout(const FunctionCallbackInfo<Value>& args);
  static void ReqUserPasswordUpdate(const FunctionCallbackInfo<Value>& args);
  static void ReqTradingAccountPasswordUpdate(const FunctionCallbackInfo<Value>& args);
  static void ReqOrderInsert(const FunctionCallbackInfo<Value>& args);
  static void ReqParkedOrderInsert(const FunctionCallbackInfo<Value>& args);
  static void ReqParkedOrderAction(const FunctionCallbackInfo<Value>& args);
  static void ReqOrderAction(const FunctionCallbackInfo<Value>& args);
  static void ReqQueryMaxOrderVolume(const FunctionCallbackInfo<Value>& args);
  static void ReqSettlementInfoConfirm(const FunctionCallbackInfo<Value>& args);
  static void ReqRemoveParkedOrder(const FunctionCallbackInfo<Value>& args);
  static void ReqRemoveParkedOrderAction(const FunctionCallbackInfo<Value>& args);
  static void ReqExecOrderInsert(const FunctionCallbackInfo<Value>& args);
  static void ReqExecOrderAction(const FunctionCallbackInfo<Value>& args);
  static void ReqForQuoteInsert(const FunctionCallbackInfo<Value>& args);
  static void ReqQuoteInsert(const FunctionCallbackInfo<Value>& args);
  static void ReqQuoteAction(const FunctionCallbackInfo<Value>& args);
  static void ReqBatchOrderAction(const FunctionCallbackInfo<Value>& args);
  static void ReqOptionSelfCloseInsert(const FunctionCallbackInfo<Value>& args);
  static void ReqOptionSelfCloseAction(const FunctionCallbackInfo<Value>& args);
  static void ReqCombActionInsert(const FunctionCallbackInfo<Value>& args);
  static void ReqQryOrder(const FunctionCallbackInfo<Value>& args);
  static void ReqQryTrade(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInvestorPosition(const FunctionCallbackInfo<Value>& args);
  static void ReqQryTradingAccount(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInvestor(const FunctionCallbackInfo<Value>& args);
  static void ReqQryTradingCode(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInstrumentMarginRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInstrumentCommissionRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQryExchange(const FunctionCallbackInfo<Value>& args);
  static void ReqQryProduct(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInstrument(const FunctionCallbackInfo<Value>& args);
  static void ReqQryDepthMarketData(const FunctionCallbackInfo<Value>& args);
  static void ReqQrySettlementInfo(const FunctionCallbackInfo<Value>& args);
  static void ReqQryTransferBank(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInvestorPositionDetail(const FunctionCallbackInfo<Value>& args);
  static void ReqQryNotice(const FunctionCallbackInfo<Value>& args);
  static void ReqQrySettlementInfoConfirm(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInvestorPositionCombineDetail(const FunctionCallbackInfo<Value>& args);
  static void ReqQryCFMMCTradingAccountKey(const FunctionCallbackInfo<Value>& args);
  static void ReqQryEWarrantOffset(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInvestorProductGroupMargin(const FunctionCallbackInfo<Value>& args);
  static void ReqQryExchangeMarginRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQryExchangeMarginRateAdjust(const FunctionCallbackInfo<Value>& args);
  static void ReqQryExchangeRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQrySecAgentACIDMap(const FunctionCallbackInfo<Value>& args);
  static void ReqQryProductExchRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQryProductGroup(const FunctionCallbackInfo<Value>& args);
  static void ReqQryMMInstrumentCommissionRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQryMMOptionInstrCommRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInstrumentOrderCommRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQrySecAgentTradingAccount(const FunctionCallbackInfo<Value>& args);
  static void ReqQrySecAgentCheckMode(const FunctionCallbackInfo<Value>& args);
  static void ReqQryOptionInstrTradeCost(const FunctionCallbackInfo<Value>& args);
  static void ReqQryOptionInstrCommRate(const FunctionCallbackInfo<Value>& args);
  static void ReqQryExecOrder(const FunctionCallbackInfo<Value>& args);
  static void ReqQryForQuote(const FunctionCallbackInfo<Value>& args);
  static void ReqQryQuote(const FunctionCallbackInfo<Value>& args);
  static void ReqQryOptionSelfClose(const FunctionCallbackInfo<Value>& args);
  static void ReqQryInvestUnit(const FunctionCallbackInfo<Value>& args);
  static void ReqQryCombInstrumentGuard(const FunctionCallbackInfo<Value>& args);
  static void ReqQryCombAction(const FunctionCallbackInfo<Value>& args);
  static void ReqQryTransferSerial(const FunctionCallbackInfo<Value>& args);
  static void ReqQryAccountregister(const FunctionCallbackInfo<Value>& args);
  static void ReqQryContractBank(const FunctionCallbackInfo<Value>& args);
  static void ReqQryParkedOrder(const FunctionCallbackInfo<Value>& args);
  static void ReqQryParkedOrderAction(const FunctionCallbackInfo<Value>& args);
  static void ReqQryTradingNotice(const FunctionCallbackInfo<Value>& args);
  static void ReqQryBrokerTradingParams(const FunctionCallbackInfo<Value>& args);
  static void ReqQryBrokerTradingAlgos(const FunctionCallbackInfo<Value>& args);
  static void ReqQueryCFMMCTradingAccountToken(const FunctionCallbackInfo<Value>& args);
  static void ReqFromBankToFutureByFuture(const FunctionCallbackInfo<Value>& args);
  static void ReqFromFutureToBankByFuture(const FunctionCallbackInfo<Value>& args);
  static void ReqQueryBankAccountMoneyByFuture(const FunctionCallbackInfo<Value>& args);

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
  static void pkg_cb_onfrontconnected(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onfrontdisconnected(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onheartbeatwarning(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspauthenticate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspuserlogin(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspuserlogout(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspuserpasswordupdate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrsptradingaccountpasswordupdate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrsporderinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspparkedorderinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspparkedorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrsporderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspquerymaxordervolume(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspsettlementinfoconfirm(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspremoveparkedorder(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspremoveparkedorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspexecorderinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspexecorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspforquoteinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspquoteinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspquoteaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspbatchorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspoptionselfcloseinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspoptionselfcloseaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspcombactioninsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryorder(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrytrade(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinvestorposition(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrytradingaccount(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinvestor(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrytradingcode(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinstrumentmarginrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinstrumentcommissionrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryexchange(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryproduct(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinstrument(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrydepthmarketdata(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrysettlementinfo(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrytransferbank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinvestorpositiondetail(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrynotice(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrysettlementinfoconfirm(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinvestorpositioncombinedetail(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrycfmmctradingaccountkey(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryewarrantoffset(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinvestorproductgroupmargin(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryexchangemarginrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryexchangemarginrateadjust(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryexchangerate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrysecagentacidmap(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryproductexchrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryproductgroup(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrymminstrumentcommissionrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrymmoptioninstrcommrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinstrumentordercommrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrysecagenttradingaccount(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrysecagentcheckmode(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryoptioninstrtradecost(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryoptioninstrcommrate(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryexecorder(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryforquote(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryquote(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryoptionselfclose(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryinvestunit(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrycombinstrumentguard(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrycombaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrytransferserial(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryaccountregister(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrsperror(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnorder(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtntrade(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnorderinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtninstrumentstatus(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnbulletin(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtntradingnotice(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnerrorconditionalorder(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnexecorder(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnexecorderinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnexecorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnforquoteinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnquote(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnquoteinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnquoteaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnforquotersp(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtncfmmctradingaccounttoken(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnbatchorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnoptionselfclose(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnoptionselfcloseinsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnoptionselfcloseaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtncombaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtncombactioninsert(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrycontractbank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryparkedorder(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqryparkedorderaction(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrytradingnotice(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrybrokertradingparams(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspqrybrokertradingalgos(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspquerycfmmctradingaccounttoken(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnfrombanktofuturebybank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnfromfuturetobankbybank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnrepealfrombanktofuturebybank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnrepealfromfuturetobankbybank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnfrombanktofuturebyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnfromfuturetobankbyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnrepealfrombanktofuturebyfuturemanual(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnrepealfromfuturetobankbyfuturemanual(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnquerybankbalancebyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnbanktofuturebyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnfuturetobankbyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnrepealbanktofuturebyfuturemanual(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnrepealfuturetobankbyfuturemanual(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onerrrtnquerybankbalancebyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnrepealfrombanktofuturebyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnrepealfromfuturetobankbyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspfrombanktofuturebyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspfromfuturetobankbyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrspquerybankaccountmoneybyfuture(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnopenaccountbybank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtncancelaccountbybank(CbRtnField* data, Local<Value>*cbArray);
  static void pkg_cb_onrtnchangeaccountbybank(CbRtnField* data, Local<Value>*cbArray);

};

#endif
