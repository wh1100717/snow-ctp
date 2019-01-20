/////////////////////////////////////////////////////////////////////////
///@system ctp行情nodejs addon
///@company 慧网基金
///@file ThostFtdcMdApiSpi.h
///@brief ctp线程及回调
///@history 
///20160326	dreamyzhang		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef __THOSTFTDCMDSPI_H__
#define __THOSTFTDCMDSPI_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <pthread.h>
//#include <semaphore.h>
#include <string.h>
#include <stdint.h>
#include <set>
#include <map>
#include <string>
#include <uv.h>

#include "comm.h"

// CTP
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcMdApi.h"

using namespace std;

namespace md
{

class CThostFtdcMdSpiI;

//以api来划分结构体
struct taskdata
{
    taskdata(CThostFtdcMdSpiI* p){handle.data = this; pmd = p;}
    CThostFtdcMdSpiI* pmd;
    uv_async_t handle;
    string api;             //表示是那个api回调
    
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
        CThostFtdcRspUserLoginField RspUserLogin;
        CThostFtdcUserLogoutField UserLogout;
        CThostFtdcSpecificInstrumentField SpecificInstrument;
        CThostFtdcDepthMarketDataField DepthMarketData;
        CThostFtdcForQuoteRspField ForQuoteRsp;
    }data;
    int nRequestID;
    bool bIsLast;
    CThostFtdcRspInfoField RspInfo; //公用返回
};

class CThostFtdcMdSpiI : public CThostFtdcMdSpi 
{

    public:
        CThostFtdcMdSpiI();
        ~CThostFtdcMdSpiI();

        void uv_async_send_s(uv_async_t* handle)
        {
            //printf("uv_async_send api=%s\n", ((taskdata*)handle->data)->api.c_str());
            //uv_async_init(uv_default_loop(), handle, on_async_cb);
            uv_async_send(handle);
        }

        //主线程回调js处理
        virtual void MainOnFrontConnected() = 0;
        virtual void MainOnFrontDisconnected(int nReason) = 0;
        virtual void MainOnHeartBeatWarning(int nTimeLapse) = 0;
        virtual void MainOnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) = 0;
        virtual void MainOnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) = 0;
        virtual void MainOnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) = 0;
        

        virtual void OnFrontConnected();
        virtual void OnFrontDisconnected(int nReason);
        virtual void OnHeartBeatWarning(int nTimeLapse);
        virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) ;
        virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) ;
        
        CThostFtdcMdApi* GetMdApi(){return m_pApi;}
        void setMdApi(CThostFtdcMdApi*  _m_pApi){ m_pApi = _m_pApi;}
        void RegisterSpi(){ m_pApi->RegisterSpi(this);}
       
    private:
        static void on_uv_close_cb(uv_handle_t* handle); 
        static void on_async_cb(uv_async_t* handle);

        taskdata* get_task()
        {
            if(task_position >= task_size) task_position = 0;
            return ptask[task_position++];
        }

        taskdata** ptask; 
        uint32_t task_size;
        uint32_t task_position;

        CThostFtdcMdApi* 	m_pApi; 		        //交易请求结构体
};
}

#endif






