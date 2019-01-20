/////////////////////////////////////////////////////////////////////////
///@system node ctp addon
///@company 慧网基金
///@file ThostFtdcTraderSpiI.h
///@brief ctp 接口
///@history 
///20160326	dreamyzhang		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef __THOSTFTDCTRADERSPI_H__
#define __THOSTFTDCTRADERSPI_H__

//#include <sys/socket.h>
//#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <math.h>
//#include <pthread.h>
#include <map>
#include <uv.h>

#include "comm.h"

#include "ThostFtdcUserApiDataType.h"                       
#include "ThostFtdcUserApiStruct.h"                         
#include "ThostFtdcTraderApi.h"                                 

using namespace std;
		
namespace td
{
class CThostFtdcTraderSpiI;

//以api来划分结构体
struct taskdata
{
    taskdata(CThostFtdcTraderSpiI* p){handle.data = this; ptd = p;}
    CThostFtdcTraderSpiI* ptd;
    string api;             //表示是那个api回调
    uv_async_t handle;
    void reinit()
    {
        api = "";
        memset(&data, 0, sizeof(data));
        nRequestID = 0;
        bIsLast = 0;
        memset(&RspInfo, 0, sizeof(RspInfo));
    }


    union _data 
    {
       int nReason;
       int nTimeLapse;
       CThostFtdcAccountregisterField Accountregister;
       CThostFtdcBatchOrderActionField BatchOrderAction;
       CThostFtdcBrokerTradingAlgosField BrokerTradingAlgos;
       CThostFtdcBrokerTradingParamsField BrokerTradingParams;
       CThostFtdcBulletinField Bulletin;
       CThostFtdcCancelAccountField CancelAccount;
       CThostFtdcCFMMCTradingAccountKeyField CFMMCTradingAccountKey;
       CThostFtdcCFMMCTradingAccountTokenField CFMMCTradingAccountToken;
       CThostFtdcChangeAccountField ChangeAccount;
       CThostFtdcCombActionField CombAction;
       CThostFtdcCombInstrumentGuardField CombInstrumentGuard;
       CThostFtdcContractBankField ContractBank;
       CThostFtdcDepthMarketDataField DepthMarketData;
       CThostFtdcErrorConditionalOrderField ErrorConditionalOrder;
       CThostFtdcEWarrantOffsetField EWarrantOffset;
       CThostFtdcExchangeField Exchange;
       CThostFtdcExchangeMarginRateAdjustField ExchangeMarginRateAdjust;
       CThostFtdcExchangeMarginRateField ExchangeMarginRate;
       CThostFtdcExchangeRateField ExchangeRate;
       CThostFtdcExecOrderActionField ExecOrderAction;
       CThostFtdcExecOrderField ExecOrder;
       CThostFtdcForQuoteField ForQuote;
       CThostFtdcForQuoteRspField ForQuoteRsp;
       CThostFtdcInputBatchOrderActionField InputBatchOrderAction;
       CThostFtdcInputCombActionField InputCombAction;
       CThostFtdcInputExecOrderActionField InputExecOrderAction;
       CThostFtdcInputExecOrderField InputExecOrder;
       CThostFtdcInputForQuoteField InputForQuote;
       CThostFtdcInputOrderActionField InputOrderAction;
       CThostFtdcInputOrderField InputOrder;
       CThostFtdcInputQuoteActionField InputQuoteAction;
       CThostFtdcInputQuoteField InputQuote;
       CThostFtdcInstrumentCommissionRateField InstrumentCommissionRate;
       CThostFtdcInstrumentField Instrument;
       CThostFtdcInstrumentMarginRateField InstrumentMarginRate;
       CThostFtdcInstrumentOrderCommRateField InstrumentOrderCommRate;
       CThostFtdcInstrumentStatusField InstrumentStatus;
       CThostFtdcInvestorField Investor;
       CThostFtdcInvestorPositionCombineDetailField InvestorPositionCombineDetail;
       CThostFtdcInvestorPositionDetailField InvestorPositionDetail;
       CThostFtdcInvestorPositionField InvestorPosition;
       CThostFtdcInvestorProductGroupMarginField InvestorProductGroupMargin;
       CThostFtdcMMInstrumentCommissionRateField MMInstrumentCommissionRate;
       CThostFtdcMMOptionInstrCommRateField MMOptionInstrCommRate;
       CThostFtdcNoticeField Notice;
       CThostFtdcNotifyQueryAccountField NotifyQueryAccount;
       CThostFtdcOpenAccountField OpenAccount;
       CThostFtdcOptionInstrCommRateField OptionInstrCommRate;
       CThostFtdcOptionInstrTradeCostField OptionInstrTradeCost;
       CThostFtdcOrderActionField OrderAction;
       CThostFtdcOrderField Order;
       CThostFtdcParkedOrderActionField ParkedOrderAction;
       CThostFtdcParkedOrderField ParkedOrder;
       CThostFtdcProductExchRateField ProductExchRate;
       CThostFtdcProductField Product;
       CThostFtdcProductGroupField ProductGroup;
       CThostFtdcQueryCFMMCTradingAccountTokenField QueryCFMMCTradingAccountToken;
       CThostFtdcQueryMaxOrderVolumeField QueryMaxOrderVolume;
       CThostFtdcQuoteActionField QuoteAction;
       CThostFtdcQuoteField Quote;
       CThostFtdcRemoveParkedOrderActionField RemoveParkedOrderAction;
       CThostFtdcRemoveParkedOrderField RemoveParkedOrder;
       CThostFtdcReqQueryAccountField ReqQueryAccount;
       CThostFtdcReqRepealField ReqRepeal;
       CThostFtdcReqTransferField ReqTransfer;
       CThostFtdcRspAuthenticateField RspAuthenticateField;
       CThostFtdcRspRepealField RspRepeal;
       CThostFtdcRspTransferField RspTransfer;
       CThostFtdcRspUserLoginField RspUserLogin;
       CThostFtdcSecAgentACIDMapField SecAgentACIDMap;
       CThostFtdcSettlementInfoConfirmField SettlementInfoConfirm;
       CThostFtdcSettlementInfoField SettlementInfo;
       CThostFtdcTradeField Trade;
       CThostFtdcTradingAccountField TradingAccount;
       CThostFtdcTradingAccountPasswordUpdateField TradingAccountPasswordUpdate;
       CThostFtdcTradingCodeField TradingCode;
       CThostFtdcTradingNoticeField TradingNotice;
       CThostFtdcTradingNoticeInfoField TradingNoticeInfo;
       CThostFtdcTransferBankField TransferBank;
       CThostFtdcTransferSerialField TransferSerial;
       CThostFtdcUserLogoutField UserLogout;
       CThostFtdcUserPasswordUpdateField UserPasswordUpdate;
    }data;
    int nRequestID;
    bool bIsLast;
    CThostFtdcRspInfoField RspInfo; //公用返回
};

//一个实例对用一个用户
class CThostFtdcTraderSpiI : public CThostFtdcTraderSpi
{
	public:
		CThostFtdcTraderSpiI();
		virtual ~CThostFtdcTraderSpiI();
		CThostFtdcTraderApi* GetTdApi(){ return m_pApi;}
    void setTdApi(CThostFtdcTraderApi* _m_pApi){ m_pApi = _m_pApi;}
    void RegisterSpi(){ m_pApi->RegisterSpi(this);}
    
        void uv_async_send_s(uv_async_t* handle)
        {
            //uv_async_init(uv_default_loop(), handle, on_async_cb);
            uv_async_send(handle);
        }

        inline void  QUEUEPUSH(const char* api, void* p=NULL, int len=0, CThostFtdcRspInfoField* pRspInfo=NULL, int nRequestID=0, int bIsLast=0)
        {
            taskdata* t = get_task();
            if(t->api != "") {printf("%s process fail. task queue is full.\n", api);return;}
            t->api = api;

            //taskdata* t = new taskdata(this);
            if(len > 0 && p!=NULL) 
            {
                memcpy((char*)&t->data, p, len); 
            }
            else
            {
                memset((char*)&t->data, 0, len);
            }
            memset(&t->RspInfo, 0, sizeof(t->RspInfo));
            if(pRspInfo != NULL)t->RspInfo = *pRspInfo;    
            t->nRequestID = nRequestID;
            t->bIsLast = bIsLast;
            //uv_queue_work(uv_default_loop(), &t->work, _on_async_queue, _on_completed);
            uv_async_send_s(&t->handle);
        }

	    virtual void MainOnFrontConnected() = 0;
        virtual void MainOnFrontDisconnected(int nReason) = 0;
        virtual void MainOnHeartBeatWarning(int nTimeLapse) = 0;
        virtual void MainOnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRtnBulletin(CThostFtdcBulletinField *pBulletin) = 0;
        virtual void MainOnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRtnOrder(CThostFtdcOrderField *pOrder) = 0;
        virtual void MainOnRtnTrade(CThostFtdcTradeField *pTrade) = 0;
        virtual void MainOnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) = 0;
        virtual void MainOnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) = 0;
        virtual void MainOnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) = 0;
        virtual void MainOnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) = 0;
        virtual void MainOnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnRtnQuote(CThostFtdcQuoteField *pQuote) = 0;
        virtual void MainOnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) = 0;
        virtual void MainOnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) = 0;
        virtual void MainOnRtnCombAction(CThostFtdcCombActionField *pCombAction) = 0;
        virtual void MainOnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) = 0;
        virtual void MainOnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) = 0;
        virtual void MainOnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) = 0;
        virtual void MainOnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) = 0;
        virtual void MainOnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) = 0;
        virtual void MainOnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) = 0;
        virtual void MainOnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) = 0;
        virtual void MainOnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) = 0;
        virtual void MainOnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) = 0;
        virtual void MainOnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) = 0;
        virtual void MainOnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) = 0;
        virtual void MainOnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) = 0;
        virtual void MainOnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) = 0;
        virtual void MainOnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) = 0;
        virtual void MainOnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) = 0;
		
        ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected();
		
        ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		///@param nReason 错误原因
		///        0x1001 网络读失败
		///        0x1002 网络写失败
		///        0x2001 接收心跳超时
		///        0x2002 发送心跳失败
		///        0x2003 收到错误报文
		virtual void OnFrontDisconnected(int nReason);
			
		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		///@param nTimeLapse 距离上次接收报文的时间
		virtual void OnHeartBeatWarning(int nTimeLapse);
		
		///客户端认证响应
		virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		

		///登录请求响应
		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///登出请求响应
		virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///用户口令更新请求响应
		virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///资金账户口令更新请求响应
		virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报单录入请求响应
		virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///预埋单录入请求响应
		virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///预埋撤单录入请求响应
		virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报单操作请求响应
		virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///查询最大报单数量响应
		virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///投资者结算结果确认响应
		virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///删除预埋单响应
		virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///删除预埋撤单响应
		virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///执行宣告录入请求响应
		virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///执行宣告操作请求响应
		virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///询价录入请求响应
		virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报价录入请求响应
		virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报价操作请求响应
		virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///批量报单操作请求响应
		virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询产品组
		virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询做市商合约手续费率响应
		virtual void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询做市商期权合约手续费响应
		virtual void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询报单手续费响应
		virtual void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///交易所公告通知
		virtual void OnRtnBulletin(CThostFtdcBulletinField *pBulletin);
		///批量报单操作错误回报
		virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);
		///申请组合录入请求响应
		virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询报单响应
		virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询成交响应
		virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓响应
		virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询资金账户响应
		virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者响应
		virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易编码响应
		virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约保证金率响应
		virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约手续费率响应
		virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易所响应
		virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询产品响应
		virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约响应
		virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询行情响应
		virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者结算结果响应
		virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询转帐银行响应
		virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓明细响应
		virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询客户通知响应
		virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询结算信息确认响应
		virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓明细响应
		virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///查询保证金监管系统经纪公司资金账户密钥响应
		virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询仓单折抵信息响应
		virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者品种/跨品种保证金响应
		virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易所保证金率响应
		virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易所调整保证金率响应
		virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询汇率响应
		virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询二级代理操作员银期权限响应
		virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询产品报价汇率
		virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询期权交易成本响应
		virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询期权合约手续费响应
		virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询执行宣告响应
		virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询询价响应
		virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询报价响应
		virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询组合合约安全系数响应
		virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询申请组合响应
		virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询转帐流水响应
		virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询银期签约关系响应
		virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///错误应答
		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报单通知
		virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

		///成交通知
		virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

		///报单录入错误回报
		virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

		///报单操作错误回报
		virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

		///合约交易状态通知
		virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

		///交易通知
		virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

		///提示条件单校验错误
		virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

		///执行宣告通知
		virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

		///执行宣告录入错误回报
		virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);

		///执行宣告操作错误回报
		virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);

		///询价录入错误回报
		virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);

		///报价通知
		virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);

		///报价录入错误回报
		virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);

		///报价操作错误回报
		virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);

		///询价通知
		virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

		///保证金监控中心用户令牌
		virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);

		///申请组合通知
		virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction);

		///申请组合录入错误回报
		virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);

		///请求查询签约银行响应
		virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询预埋单响应
		virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询预埋撤单响应
		virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易通知响应
		virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询经纪公司交易参数响应
		virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询经纪公司交易算法响应
		virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询监控中心用户令牌
		virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///银行发起银行资金转期货通知
		virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer);

		///银行发起期货资金转银行通知
		virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer);

		///银行发起冲正银行转期货通知
		virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal);

		///银行发起冲正期货转银行通知
		virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal);

		///期货发起银行资金转期货通知
		virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);

		///期货发起期货资金转银行通知
		virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);

		///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

		///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

		///期货发起查询银行余额通知
		virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);

		///期货发起银行资金转期货错误回报
		virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

		///期货发起期货资金转银行错误回报
		virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

		///系统运行时期货端手工发起冲正银行转期货错误回报
		virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

		///系统运行时期货端手工发起冲正期货转银行错误回报
		virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

		///期货发起查询银行余额错误回报
		virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);

		///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal);

		///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal);

		///期货发起银行资金转期货应答
		virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///期货发起期货资金转银行应答
		virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///期货发起查询银行余额应答
		virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///银行发起银期开户通知
		virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount);

		///银行发起银期销户通知
		virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount);

		///银行发起变更银行账号通知
		virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount);
		
    private:
 
        taskdata* get_task()
        {
            if(task_position >= task_size) task_position = 0;
            return ptask[task_position++];
        }

        taskdata** ptask; 
        uint32_t task_size;
        uint32_t task_position;

        static void on_uv_close_cb(uv_handle_t* handle); 
        static void on_async_cb(uv_async_t* handle);

        CThostFtdcTraderApi*    		m_pApi;        //交易请求结构体
};

}


#endif



