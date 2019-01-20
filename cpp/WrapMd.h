/////////////////////////////////////////////////////////////////////////
///@system ctp 行情nodejs addon
///@company 慧网基金
///@file WrapMd.h
///@brief js回调接口
///@history 
///20160326	dreamyzhang		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef __WRAPMD_H__
#define __WRAPMD_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdint.h>
#include <set>
#include <map>
#include <string>
#include <node.h>
#include <node_object_wrap.h>

#include "comm.h"

#include "ThostFtdcMdSpiI.h"
#include "ctp_node.h"

using namespace std;

namespace md
{
class WrapMd : public CThostFtdcMdSpiI, public node::ObjectWrap 
{
    public:
        WrapMd();
        ~WrapMd();

        //wrap主动请求函数
        static void On(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void Init(v8::Isolate* isolate);
    
        static void Init(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void Release(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void CreateFtdcMdApi(const v8::FunctionCallbackInfo<v8::Value>& args);                      
        static void GetApiVersion(const v8::FunctionCallbackInfo<v8::Value>& args);                      
        static void GetTradingDay(const v8::FunctionCallbackInfo<v8::Value>& args);                      
        static void RegisterFront(const v8::FunctionCallbackInfo<v8::Value>& args);                      
        static void RegisterNameServer(const v8::FunctionCallbackInfo<v8::Value>& args);                      
        static void RegisterFensUserInfo(const v8::FunctionCallbackInfo<v8::Value>& args); 
        static void ReqUserLogin(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void ReqUserLogout(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void SubscribeMarketData(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void UnSubscribeMarketData(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void SubscribeForQuoteRsp(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void UnSubscribeForQuoteRsp(const v8::FunctionCallbackInfo<v8::Value>& args);
        
        //回调js部分
        virtual void MainOnFrontConnected();
        virtual void MainOnFrontDisconnected(int nReason);
        virtual void MainOnHeartBeatWarning(int nTimeLapse);
        virtual void MainOnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void MainOnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void MainOnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void MainOnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void MainOnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void MainOnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void MainOnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
        virtual void MainOnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) ;
        virtual void MainOnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) ;

        bool CanCallback(string event)
        {
            if(callback_map.find(event) != callback_map.end()) return true;
            return false;
        }
        void SetCallback(string event, v8::Local<v8::Function>& cb, v8::Isolate* isolate)
        {
            callback_map[event].Reset(isolate, cb);
        }
    private:
        typedef std::map<string, v8::Persistent<v8::Function> > __callback_type;
        typedef std::map<string, v8::Persistent<v8::Function> >::iterator  __callback_iter_type;
        __callback_type callback_map; //回调js name映射回调处理函数
        
        static set<string>         m_event;                //可以注册的回调事件
        static v8::Persistent<v8::Function> constructor;           //主动请求函数映射js name

        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        v8::Local<v8::Value> PkgRspInfo(CThostFtdcRspInfoField *pRspInfo) 
        {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            if (pRspInfo != NULL) 
            { 
                v8::Local<v8::Object> jsonInfo = v8::Object::New(isolate);                                       
                jsonInfo->Set(v8::String::NewFromUtf8(isolate, "ErrorID"), v8::Int32::New(isolate, pRspInfo->ErrorID));   
                jsonInfo->Set(v8::String::NewFromUtf8(isolate, "ErrorMsg"), v8::String::NewFromUtf8(isolate, CSFunction::GBK2UTF8(pRspInfo->ErrorMsg).c_str()));
                return jsonInfo; 
            } 
            else
            {
                return  v8::Local<v8::Value>::New(isolate, v8::Undefined(isolate));                                       
            }     
        }
};
}

#endif






