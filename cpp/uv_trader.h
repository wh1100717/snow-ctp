
#ifndef UV_TRADER_H_
#define UV_TRADER_H_

#include <iostream>
#include <string>
#include <map>
#include <uv.h>
#include <node.h>

#include "ctp_utils.h"
#include "ctp_struct.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"

class uv_trader : public CThostFtdcTraderSpi {
public:
  uv_trader(void);
  virtual ~uv_trader(void);

  const char* GetTradingDay();
  int On(const char* eName,int cb_type, void(*callback)(CbRtnField* cbResult));
  void Connect(UVConnectField* pConnectField, int uuid, void(*callback)(int, void*));
  void Disconnect();
  void ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID, void(*callback)(int, void*));
  void ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID, void(*callback)(int, void*));
  void ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID, void(*callback)(int, void*));
  void ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID, void(*callback)(int, void*));
  void ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID, void(*callback)(int, void*));
  void ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID, void(*callback)(int, void*));
  void ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID, void(*callback)(int, void*));
  void ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID, void(*callback)(int, void*));
  void ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID, void(*callback)(int, void*));
  void ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID, void(*callback)(int, void*));
  void ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID, void(*callback)(int, void*));
  void ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID, void(*callback)(int, void*));
  void ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID, void(*callback)(int, void*));
  void ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID, void(*callback)(int, void*));
  void ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID, void(*callback)(int, void*));
  void ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID, void(*callback)(int, void*));
  void ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID, void(*callback)(int, void*));
  void ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID, void(*callback)(int, void*));
  void ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID, void(*callback)(int, void*));
  void ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID, void(*callback)(int, void*));
  void ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, int nRequestID, void(*callback)(int, void*));
  void ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID, void(*callback)(int, void*));
  void ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID, void(*callback)(int, void*));
  void ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID, void(*callback)(int, void*));
  void ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID, void(*callback)(int, void*));
  void ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID, void(*callback)(int, void*));
  void ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID, void(*callback)(int, void*));
  void ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID, void(*callback)(int, void*));
  void ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID, void(*callback)(int, void*));
  void ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID, void(*callback)(int, void*));
  void ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID, void(*callback)(int, void*));
  void ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID, void(*callback)(int, void*));
  void ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID, void(*callback)(int, void*));
  void ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID, void(*callback)(int, void*));
  void ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID, void(*callback)(int, void*));
  void ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID, void(*callback)(int, void*));
  void ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID, void(*callback)(int, void*));
  void ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID, void(*callback)(int, void*));
  void ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID, void(*callback)(int, void*));
  void ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID, void(*callback)(int, void*));
  void ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID, void(*callback)(int, void*));
  void ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID, void(*callback)(int, void*));
  void ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID, void(*callback)(int, void*));
  void ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID, void(*callback)(int, void*));
  void ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID, void(*callback)(int, void*));
  void ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID, void(*callback)(int, void*));
  void ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID, void(*callback)(int, void*));
  void ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID, void(*callback)(int, void*));
  void ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID, void(*callback)(int, void*));
  void ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate, int nRequestID, void(*callback)(int, void*));
  void ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate, int nRequestID, void(*callback)(int, void*));
  void ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate, int nRequestID, void(*callback)(int, void*));
  void ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID, void(*callback)(int, void*));
  void ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode, int nRequestID, void(*callback)(int, void*));
  void ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID, void(*callback)(int, void*));
  void ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID, void(*callback)(int, void*));
  void ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID, void(*callback)(int, void*));
  void ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID, void(*callback)(int, void*));
  void ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID, void(*callback)(int, void*));
  void ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose, int nRequestID, void(*callback)(int, void*));
  void ReqQryInvestUnit(CThostFtdcQryInvestUnitField *pQryInvestUnit, int nRequestID, void(*callback)(int, void*));
  void ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID, void(*callback)(int, void*));
  void ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID, void(*callback)(int, void*));
  void ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID, void(*callback)(int, void*));
  void ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID, void(*callback)(int, void*));
  void ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID, void(*callback)(int, void*));
  void ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID, void(*callback)(int, void*));
  void ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID, void(*callback)(int, void*));
  void ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID, void(*callback)(int, void*));
  void ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID, void(*callback)(int, void*));
  void ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID, void(*callback)(int, void*));
  void ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID, void(*callback)(int, void*));
  void ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID, void(*callback)(int, void*));
  void ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID, void(*callback)(int, void*));
  void ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID, void(*callback)(int, void*));

private:
  CThostFtdcTraderApi* m_pApi;
  int iRequestID;
  uv_async_t async_t;
  static std::map<int, CbWrap*> cb_map;

  static void _async(uv_work_t * work);
  static void _completed(uv_work_t * work, int);
  static void _on_async(uv_work_t * work);
  static void _on_completed(uv_work_t * work,int);

  void invoke(void* field, int ret, void(*callback)(int, void*), int uuid);
  void on_invoke(int event_type, void* _stru, CThostFtdcRspInfoField *pRspInfo_org, int nRequestID, bool bIsLast);
  virtual void OnFrontConnected();
  virtual void OnFrontDisconnected(int nReason);
  virtual void OnHeartBeatWarning(int nTimeLapse);
  virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
  virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);
  virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);
  virtual void OnRtnBulletin(CThostFtdcBulletinField *pBulletin);
  virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);
  virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);
  virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);
  virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);
  virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
  virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);
  virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose);
  virtual void OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction);
  virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer);
  virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer);
  virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);
  virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);
  virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);
  virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount);
  virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount);
  virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount);

};

#endif
