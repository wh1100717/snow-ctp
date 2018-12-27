#ifndef UV_MARKET_H_
#define UV_MARKET_H_

#include <iostream>
#include <string>
#include <map>
#include <uv.h>
#include <node.h>

#include "ctp_utils.h"
#include "ctp_struct.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiDataType.h"

class uv_market : public CThostFtdcMdSpi {
public:
  uv_market(void);
  virtual ~uv_market(void);

  const char* GetTradingDay();
  int On(const char* eName,int cb_type, void(*callback)(CbRtnField* cbResult));
  void Connect(UVConnectField* pConnectField, int uuid, void(*callback)(int, void*));
  void Disconnect();
  void ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID, void(*callback)(int, void*));
  void ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID, void(*callback)(int, void*));
  void ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID, void(*callback)(int, void*));

	void SubscribeMarketData(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*));
	void UnSubscribeMarketData(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*));
	void SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*));
	void UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*));
private:
  CThostFtdcMdApi* m_pApi;
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
  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
};

#endif
