#ifndef __NODE_CTP__
#define __NODE_CTP__

#include <v8.h>
#include <string>
#include "ThostFtdcUserApiStruct.h"

using  v8::Local;
using  v8::Isolate;
using  v8::Object;
using  v8::String;
using  v8::Exception;
using  v8::Value;

class CSFunction
{

public:

#ifdef WIN32
#include <windows.h>
static string GBK2UTF8(string strGBK)  
{  
    string strOutUTF8 = "";  
    WCHAR * str1;  
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);  
    str1 = new WCHAR[n];  
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);  
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);  
    char * str2 = new char[n];  
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);  
    strOutUTF8 = str2;  
    delete[]str1;  
    str1 = NULL;  
    delete[]str2;  
    str2 = NULL;  
    return strOutUTF8;  
}  
#else
static string GBK2UTF8(string src)
{
    if(src.length() < 1) return "";
    size_t outlen = 4*src.length()+1;
    char* pout = new char[outlen];
    memset(pout, 0,  outlen);
    char* dest = pout;

    char * pin = (char*)src.c_str();
    size_t inlen = src.length();

    iconv_t conv = iconv_open("UTF-8", "GB2312");
    if(conv == 0) return "";
    iconv(conv, &pin, &inlen, &pout, &outlen);
    iconv_close(conv);
    
    string tmp = dest;
    delete dest;
    return tmp;
}
#endif

static void set_struct(Local<Object>& obj, const char* key, void* dest, int len)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined())
    {
        memset(dest, 0, len);
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    String::Utf8Value t(v);
    strncpy((char*)dest, (char*)*t, len);
    if(len>1) ((char*)dest)[len-1] = '0';
}

static void set_struct(Local<Object>& obj, const char* key, char* dest, int len)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined())
    {
        memset(dest, 0, len);
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    String::Utf8Value t(v);
    strncpy(dest, (char*)*t, len);
    if(len>1) dest[len-1] = '0';
}

static void set_struct(Local<Object>& obj, const char* key, int* dest, int len=0)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined())
    {
        dest = 0;
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    *dest = v->Int32Value();
}

static void set_struct(Local<Object>& obj, const char* key, double* dest, int len=0)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined() || !v->IsNumber())
    {
        dest = 0;
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    *dest = v->NumberValue();
}

static void set_struct(Local<Object>& obj, const char* key, float* dest, int len=0)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined() || !v->IsNumber())
    {
        dest = 0;
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    *dest = (float)v->NumberValue();
}


//处理ctp定义的字符数组指针类型
static void set_obj(v8::Local<v8::Object>& obj, const char* key, void* v)
{
    string u = GBK2UTF8((char*)v);
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), u.c_str()));
}


static void set_obj(v8::Local<v8::Object>& obj, const char* key, char* v)
{
    char s[2]= {0};
    s[0] = *v;
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), s));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, int* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Int32::New(v8::Isolate::GetCurrent(), *v));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, short int* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Int32::New(v8::Isolate::GetCurrent(), (int)*v));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, float* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Number::New(v8::Isolate::GetCurrent(), *v));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, double* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Number::New(v8::Isolate::GetCurrent(), *v));
}
static void set_obj(Local<Object>& obj, CThostFtdcDisseminationField *p)
{
    set_obj(obj, "SequenceSeries", &p->SequenceSeries);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqUserLoginField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "InterfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "ProtocolInfo", &p->ProtocolInfo);
    set_obj(obj, "MacAddress", &p->MacAddress);
    set_obj(obj, "OneTimePassword", &p->OneTimePassword);
    set_obj(obj, "ClientIPAddress", &p->ClientIPAddress);
    set_obj(obj, "LoginRemark", &p->LoginRemark);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspUserLoginField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "LoginTime", &p->LoginTime);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "SystemName", &p->SystemName);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "MaxOrderRef", &p->MaxOrderRef);
    set_obj(obj, "SHFETime", &p->SHFETime);
    set_obj(obj, "DCETime", &p->DCETime);
    set_obj(obj, "CZCETime", &p->CZCETime);
    set_obj(obj, "FFEXTime", &p->FFEXTime);
    set_obj(obj, "INETime", &p->INETime);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserLogoutField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcForceUserLogoutField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqAuthenticateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "AuthCode", &p->AuthCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspAuthenticateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
}
static void set_obj(Local<Object>& obj, CThostFtdcAuthenticationInfoField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "AuthInfo", &p->AuthInfo);
    set_obj(obj, "IsResult", &p->IsResult);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferHeaderField *p)
{
    set_obj(obj, "Version", &p->Version);
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "TradeSerial", &p->TradeSerial);
    set_obj(obj, "FutureID", &p->FutureID);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBrchID", &p->BankBrchID);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "RecordNum", &p->RecordNum);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "RequestID", &p->RequestID);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferBankToFutureReqField *p)
{
    set_obj(obj, "FutureAccount", &p->FutureAccount);
    set_obj(obj, "FuturePwdFlag", &p->FuturePwdFlag);
    set_obj(obj, "FutureAccPwd", &p->FutureAccPwd);
    set_obj(obj, "TradeAmt", &p->TradeAmt);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "CurrencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferBankToFutureRspField *p)
{
    set_obj(obj, "RetCode", &p->RetCode);
    set_obj(obj, "RetInfo", &p->RetInfo);
    set_obj(obj, "FutureAccount", &p->FutureAccount);
    set_obj(obj, "TradeAmt", &p->TradeAmt);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "CurrencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferFutureToBankReqField *p)
{
    set_obj(obj, "FutureAccount", &p->FutureAccount);
    set_obj(obj, "FuturePwdFlag", &p->FuturePwdFlag);
    set_obj(obj, "FutureAccPwd", &p->FutureAccPwd);
    set_obj(obj, "TradeAmt", &p->TradeAmt);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "CurrencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferFutureToBankRspField *p)
{
    set_obj(obj, "RetCode", &p->RetCode);
    set_obj(obj, "RetInfo", &p->RetInfo);
    set_obj(obj, "FutureAccount", &p->FutureAccount);
    set_obj(obj, "TradeAmt", &p->TradeAmt);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "CurrencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryBankReqField *p)
{
    set_obj(obj, "FutureAccount", &p->FutureAccount);
    set_obj(obj, "FuturePwdFlag", &p->FuturePwdFlag);
    set_obj(obj, "FutureAccPwd", &p->FutureAccPwd);
    set_obj(obj, "CurrencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryBankRspField *p)
{
    set_obj(obj, "RetCode", &p->RetCode);
    set_obj(obj, "RetInfo", &p->RetInfo);
    set_obj(obj, "FutureAccount", &p->FutureAccount);
    set_obj(obj, "TradeAmt", &p->TradeAmt);
    set_obj(obj, "UseAmt", &p->UseAmt);
    set_obj(obj, "FetchAmt", &p->FetchAmt);
    set_obj(obj, "CurrencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryDetailReqField *p)
{
    set_obj(obj, "FutureAccount", &p->FutureAccount);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryDetailRspField *p)
{
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "FutureID", &p->FutureID);
    set_obj(obj, "FutureAccount", &p->FutureAccount);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBrchID", &p->BankBrchID);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "CertCode", &p->CertCode);
    set_obj(obj, "CurrencyCode", &p->CurrencyCode);
    set_obj(obj, "TxAmount", &p->TxAmount);
    set_obj(obj, "Flag", &p->Flag);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspInfoField *p)
{
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExchangeName", &p->ExchangeName);
    set_obj(obj, "ExchangeProperty", &p->ExchangeProperty);
}
static void set_obj(Local<Object>& obj, CThostFtdcProductField *p)
{
    set_obj(obj, "ProductID", &p->ProductID);
    set_obj(obj, "ProductName", &p->ProductName);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ProductClass", &p->ProductClass);
    set_obj(obj, "VolumeMultiple", &p->VolumeMultiple);
    set_obj(obj, "PriceTick", &p->PriceTick);
    set_obj(obj, "MaxMarketOrderVolume", &p->MaxMarketOrderVolume);
    set_obj(obj, "MinMarketOrderVolume", &p->MinMarketOrderVolume);
    set_obj(obj, "MaxLimitOrderVolume", &p->MaxLimitOrderVolume);
    set_obj(obj, "MinLimitOrderVolume", &p->MinLimitOrderVolume);
    set_obj(obj, "PositionType", &p->PositionType);
    set_obj(obj, "PositionDateType", &p->PositionDateType);
    set_obj(obj, "CloseDealType", &p->CloseDealType);
    set_obj(obj, "TradeCurrencyID", &p->TradeCurrencyID);
    set_obj(obj, "MortgageFundUseRange", &p->MortgageFundUseRange);
    set_obj(obj, "ExchangeProductID", &p->ExchangeProductID);
    set_obj(obj, "UnderlyingMultiple", &p->UnderlyingMultiple);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InstrumentName", &p->InstrumentName);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "ProductID", &p->ProductID);
    set_obj(obj, "ProductClass", &p->ProductClass);
    set_obj(obj, "DeliveryYear", &p->DeliveryYear);
    set_obj(obj, "DeliveryMonth", &p->DeliveryMonth);
    set_obj(obj, "MaxMarketOrderVolume", &p->MaxMarketOrderVolume);
    set_obj(obj, "MinMarketOrderVolume", &p->MinMarketOrderVolume);
    set_obj(obj, "MaxLimitOrderVolume", &p->MaxLimitOrderVolume);
    set_obj(obj, "MinLimitOrderVolume", &p->MinLimitOrderVolume);
    set_obj(obj, "VolumeMultiple", &p->VolumeMultiple);
    set_obj(obj, "PriceTick", &p->PriceTick);
    set_obj(obj, "CreateDate", &p->CreateDate);
    set_obj(obj, "OpenDate", &p->OpenDate);
    set_obj(obj, "ExpireDate", &p->ExpireDate);
    set_obj(obj, "StartDelivDate", &p->StartDelivDate);
    set_obj(obj, "EndDelivDate", &p->EndDelivDate);
    set_obj(obj, "InstLifePhase", &p->InstLifePhase);
    set_obj(obj, "IsTrading", &p->IsTrading);
    set_obj(obj, "PositionType", &p->PositionType);
    set_obj(obj, "PositionDateType", &p->PositionDateType);
    set_obj(obj, "LongMarginRatio", &p->LongMarginRatio);
    set_obj(obj, "ShortMarginRatio", &p->ShortMarginRatio);
    set_obj(obj, "MaxMarginSideAlgorithm", &p->MaxMarginSideAlgorithm);
    set_obj(obj, "UnderlyingInstrID", &p->UnderlyingInstrID);
    set_obj(obj, "StrikePrice", &p->StrikePrice);
    set_obj(obj, "OptionsType", &p->OptionsType);
    set_obj(obj, "UnderlyingMultiple", &p->UnderlyingMultiple);
    set_obj(obj, "CombinationType", &p->CombinationType);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerAbbr", &p->BrokerAbbr);
    set_obj(obj, "BrokerName", &p->BrokerName);
    set_obj(obj, "IsActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcTraderField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallCount", &p->InstallCount);
    set_obj(obj, "BrokerID", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorField *p)
{
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorGroupID", &p->InvestorGroupID);
    set_obj(obj, "InvestorName", &p->InvestorName);
    set_obj(obj, "IdentifiedCardType", &p->IdentifiedCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "IsActive", &p->IsActive);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "OpenDate", &p->OpenDate);
    set_obj(obj, "Mobile", &p->Mobile);
    set_obj(obj, "CommModelID", &p->CommModelID);
    set_obj(obj, "MarginModelID", &p->MarginModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingCodeField *p)
{
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IsActive", &p->IsActive);
    set_obj(obj, "ClientIDType", &p->ClientIDType);
}
static void set_obj(Local<Object>& obj, CThostFtdcPartBrokerField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "IsActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcSuperUserField *p)
{
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserName", &p->UserName);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "IsActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcSuperUserFunctionField *p)
{
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "FunctionCode", &p->FunctionCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorGroupField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorGroupID", &p->InvestorGroupID);
    set_obj(obj, "InvestorGroupName", &p->InvestorGroupName);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "PreMortgage", &p->PreMortgage);
    set_obj(obj, "PreCredit", &p->PreCredit);
    set_obj(obj, "PreDeposit", &p->PreDeposit);
    set_obj(obj, "PreBalance", &p->PreBalance);
    set_obj(obj, "PreMargin", &p->PreMargin);
    set_obj(obj, "InterestBase", &p->InterestBase);
    set_obj(obj, "Interest", &p->Interest);
    set_obj(obj, "Deposit", &p->Deposit);
    set_obj(obj, "Withdraw", &p->Withdraw);
    set_obj(obj, "FrozenMargin", &p->FrozenMargin);
    set_obj(obj, "FrozenCash", &p->FrozenCash);
    set_obj(obj, "FrozenCommission", &p->FrozenCommission);
    set_obj(obj, "CurrMargin", &p->CurrMargin);
    set_obj(obj, "CashIn", &p->CashIn);
    set_obj(obj, "Commission", &p->Commission);
    set_obj(obj, "CloseProfit", &p->CloseProfit);
    set_obj(obj, "PositionProfit", &p->PositionProfit);
    set_obj(obj, "Balance", &p->Balance);
    set_obj(obj, "Available", &p->Available);
    set_obj(obj, "WithdrawQuota", &p->WithdrawQuota);
    set_obj(obj, "Reserve", &p->Reserve);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "Credit", &p->Credit);
    set_obj(obj, "Mortgage", &p->Mortgage);
    set_obj(obj, "ExchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "DeliveryMargin", &p->DeliveryMargin);
    set_obj(obj, "ExchangeDeliveryMargin", &p->ExchangeDeliveryMargin);
    set_obj(obj, "ReserveBalance", &p->ReserveBalance);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "PreFundMortgageIn", &p->PreFundMortgageIn);
    set_obj(obj, "PreFundMortgageOut", &p->PreFundMortgageOut);
    set_obj(obj, "FundMortgageIn", &p->FundMortgageIn);
    set_obj(obj, "FundMortgageOut", &p->FundMortgageOut);
    set_obj(obj, "FundMortgageAvailable", &p->FundMortgageAvailable);
    set_obj(obj, "MortgageableFund", &p->MortgageableFund);
    set_obj(obj, "SpecProductMargin", &p->SpecProductMargin);
    set_obj(obj, "SpecProductFrozenMargin", &p->SpecProductFrozenMargin);
    set_obj(obj, "SpecProductCommission", &p->SpecProductCommission);
    set_obj(obj, "SpecProductFrozenCommission", &p->SpecProductFrozenCommission);
    set_obj(obj, "SpecProductPositionProfit", &p->SpecProductPositionProfit);
    set_obj(obj, "SpecProductCloseProfit", &p->SpecProductCloseProfit);
    set_obj(obj, "SpecProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg);
    set_obj(obj, "SpecProductExchangeMargin", &p->SpecProductExchangeMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorPositionField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "PosiDirection", &p->PosiDirection);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "PositionDate", &p->PositionDate);
    set_obj(obj, "YdPosition", &p->YdPosition);
    set_obj(obj, "Position", &p->Position);
    set_obj(obj, "LongFrozen", &p->LongFrozen);
    set_obj(obj, "ShortFrozen", &p->ShortFrozen);
    set_obj(obj, "LongFrozenAmount", &p->LongFrozenAmount);
    set_obj(obj, "ShortFrozenAmount", &p->ShortFrozenAmount);
    set_obj(obj, "OpenVolume", &p->OpenVolume);
    set_obj(obj, "CloseVolume", &p->CloseVolume);
    set_obj(obj, "OpenAmount", &p->OpenAmount);
    set_obj(obj, "CloseAmount", &p->CloseAmount);
    set_obj(obj, "PositionCost", &p->PositionCost);
    set_obj(obj, "PreMargin", &p->PreMargin);
    set_obj(obj, "UseMargin", &p->UseMargin);
    set_obj(obj, "FrozenMargin", &p->FrozenMargin);
    set_obj(obj, "FrozenCash", &p->FrozenCash);
    set_obj(obj, "FrozenCommission", &p->FrozenCommission);
    set_obj(obj, "CashIn", &p->CashIn);
    set_obj(obj, "Commission", &p->Commission);
    set_obj(obj, "CloseProfit", &p->CloseProfit);
    set_obj(obj, "PositionProfit", &p->PositionProfit);
    set_obj(obj, "PreSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "SettlementPrice", &p->SettlementPrice);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "OpenCost", &p->OpenCost);
    set_obj(obj, "ExchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "CombPosition", &p->CombPosition);
    set_obj(obj, "CombLongFrozen", &p->CombLongFrozen);
    set_obj(obj, "CombShortFrozen", &p->CombShortFrozen);
    set_obj(obj, "CloseProfitByDate", &p->CloseProfitByDate);
    set_obj(obj, "CloseProfitByTrade", &p->CloseProfitByTrade);
    set_obj(obj, "TodayPosition", &p->TodayPosition);
    set_obj(obj, "MarginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "MarginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "StrikeFrozen", &p->StrikeFrozen);
    set_obj(obj, "StrikeFrozenAmount", &p->StrikeFrozenAmount);
    set_obj(obj, "AbandonFrozen", &p->AbandonFrozen);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentMarginRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "IsRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentCommissionRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OpenRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "OpenRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "CloseRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "CloseRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcDepthMarketDataField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "LastPrice", &p->LastPrice);
    set_obj(obj, "PreSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "PreClosePrice", &p->PreClosePrice);
    set_obj(obj, "PreOpenInterest", &p->PreOpenInterest);
    set_obj(obj, "OpenPrice", &p->OpenPrice);
    set_obj(obj, "HighestPrice", &p->HighestPrice);
    set_obj(obj, "LowestPrice", &p->LowestPrice);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "Turnover", &p->Turnover);
    set_obj(obj, "OpenInterest", &p->OpenInterest);
    set_obj(obj, "ClosePrice", &p->ClosePrice);
    set_obj(obj, "SettlementPrice", &p->SettlementPrice);
    set_obj(obj, "UpperLimitPrice", &p->UpperLimitPrice);
    set_obj(obj, "LowerLimitPrice", &p->LowerLimitPrice);
    set_obj(obj, "PreDelta", &p->PreDelta);
    set_obj(obj, "CurrDelta", &p->CurrDelta);
    set_obj(obj, "UpdateTime", &p->UpdateTime);
    set_obj(obj, "UpdateMillisec", &p->UpdateMillisec);
    set_obj(obj, "BidPrice1", &p->BidPrice1);
    set_obj(obj, "BidVolume1", &p->BidVolume1);
    set_obj(obj, "AskPrice1", &p->AskPrice1);
    set_obj(obj, "AskVolume1", &p->AskVolume1);
    set_obj(obj, "BidPrice2", &p->BidPrice2);
    set_obj(obj, "BidVolume2", &p->BidVolume2);
    set_obj(obj, "AskPrice2", &p->AskPrice2);
    set_obj(obj, "AskVolume2", &p->AskVolume2);
    set_obj(obj, "BidPrice3", &p->BidPrice3);
    set_obj(obj, "BidVolume3", &p->BidVolume3);
    set_obj(obj, "AskPrice3", &p->AskPrice3);
    set_obj(obj, "AskVolume3", &p->AskVolume3);
    set_obj(obj, "BidPrice4", &p->BidPrice4);
    set_obj(obj, "BidVolume4", &p->BidVolume4);
    set_obj(obj, "AskPrice4", &p->AskPrice4);
    set_obj(obj, "AskVolume4", &p->AskVolume4);
    set_obj(obj, "BidPrice5", &p->BidPrice5);
    set_obj(obj, "BidVolume5", &p->BidVolume5);
    set_obj(obj, "AskPrice5", &p->AskPrice5);
    set_obj(obj, "AskVolume5", &p->AskVolume5);
    set_obj(obj, "AveragePrice", &p->AveragePrice);
    set_obj(obj, "ActionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentTradingRightField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "TradingRight", &p->TradingRight);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserName", &p->UserName);
    set_obj(obj, "UserType", &p->UserType);
    set_obj(obj, "IsActive", &p->IsActive);
    set_obj(obj, "IsUsingOTP", &p->IsUsingOTP);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserPasswordField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Password", &p->Password);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserFunctionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "BrokerFunctionCode", &p->BrokerFunctionCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTraderOfferField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "TraderConnectStatus", &p->TraderConnectStatus);
    set_obj(obj, "ConnectRequestDate", &p->ConnectRequestDate);
    set_obj(obj, "ConnectRequestTime", &p->ConnectRequestTime);
    set_obj(obj, "LastReportDate", &p->LastReportDate);
    set_obj(obj, "LastReportTime", &p->LastReportTime);
    set_obj(obj, "ConnectDate", &p->ConnectDate);
    set_obj(obj, "ConnectTime", &p->ConnectTime);
    set_obj(obj, "StartDate", &p->StartDate);
    set_obj(obj, "StartTime", &p->StartTime);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "MaxTradeID", &p->MaxTradeID);
    set_obj(obj, "MaxOrderMessageReference", &p->MaxOrderMessageReference);
}
static void set_obj(Local<Object>& obj, CThostFtdcSettlementInfoField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "Content", &p->Content);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentMarginRateAdjustField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "IsRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeMarginRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeMarginRateAdjustField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "ExchLongMarginRatioByMoney", &p->ExchLongMarginRatioByMoney);
    set_obj(obj, "ExchLongMarginRatioByVolume", &p->ExchLongMarginRatioByVolume);
    set_obj(obj, "ExchShortMarginRatioByMoney", &p->ExchShortMarginRatioByMoney);
    set_obj(obj, "ExchShortMarginRatioByVolume", &p->ExchShortMarginRatioByVolume);
    set_obj(obj, "NoLongMarginRatioByMoney", &p->NoLongMarginRatioByMoney);
    set_obj(obj, "NoLongMarginRatioByVolume", &p->NoLongMarginRatioByVolume);
    set_obj(obj, "NoShortMarginRatioByMoney", &p->NoShortMarginRatioByMoney);
    set_obj(obj, "NoShortMarginRatioByVolume", &p->NoShortMarginRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "FromCurrencyID", &p->FromCurrencyID);
    set_obj(obj, "FromCurrencyUnit", &p->FromCurrencyUnit);
    set_obj(obj, "ToCurrencyID", &p->ToCurrencyID);
    set_obj(obj, "ExchangeRate", &p->ExchangeRate);
}
static void set_obj(Local<Object>& obj, CThostFtdcSettlementRefField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCurrentTimeField *p)
{
    set_obj(obj, "CurrDate", &p->CurrDate);
    set_obj(obj, "CurrTime", &p->CurrTime);
    set_obj(obj, "CurrMillisec", &p->CurrMillisec);
    set_obj(obj, "ActionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcCommPhaseField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "CommPhaseNo", &p->CommPhaseNo);
    set_obj(obj, "SystemID", &p->SystemID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLoginInfoField *p)
{
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "LoginDate", &p->LoginDate);
    set_obj(obj, "LoginTime", &p->LoginTime);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "InterfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "ProtocolInfo", &p->ProtocolInfo);
    set_obj(obj, "SystemName", &p->SystemName);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "MaxOrderRef", &p->MaxOrderRef);
    set_obj(obj, "SHFETime", &p->SHFETime);
    set_obj(obj, "DCETime", &p->DCETime);
    set_obj(obj, "CZCETime", &p->CZCETime);
    set_obj(obj, "FFEXTime", &p->FFEXTime);
    set_obj(obj, "MacAddress", &p->MacAddress);
    set_obj(obj, "OneTimePassword", &p->OneTimePassword);
    set_obj(obj, "INETime", &p->INETime);
    set_obj(obj, "IsQryControl", &p->IsQryControl);
    set_obj(obj, "LoginRemark", &p->LoginRemark);
}
static void set_obj(Local<Object>& obj, CThostFtdcLogoutAllField *p)
{
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "SystemName", &p->SystemName);
}
static void set_obj(Local<Object>& obj, CThostFtdcFrontStatusField *p)
{
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "LastReportDate", &p->LastReportDate);
    set_obj(obj, "LastReportTime", &p->LastReportTime);
    set_obj(obj, "IsActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserPasswordUpdateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OldPassword", &p->OldPassword);
    set_obj(obj, "NewPassword", &p->NewPassword);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OrderPriceType", &p->OrderPriceType);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "CombOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "CombHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "TimeCondition", &p->TimeCondition);
    set_obj(obj, "GTDDate", &p->GTDDate);
    set_obj(obj, "VolumeCondition", &p->VolumeCondition);
    set_obj(obj, "MinVolume", &p->MinVolume);
    set_obj(obj, "ContingentCondition", &p->ContingentCondition);
    set_obj(obj, "StopPrice", &p->StopPrice);
    set_obj(obj, "ForceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "IsAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "UserForceClose", &p->UserForceClose);
    set_obj(obj, "IsSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OrderPriceType", &p->OrderPriceType);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "CombOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "CombHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "TimeCondition", &p->TimeCondition);
    set_obj(obj, "GTDDate", &p->GTDDate);
    set_obj(obj, "VolumeCondition", &p->VolumeCondition);
    set_obj(obj, "MinVolume", &p->MinVolume);
    set_obj(obj, "ContingentCondition", &p->ContingentCondition);
    set_obj(obj, "StopPrice", &p->StopPrice);
    set_obj(obj, "ForceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "IsAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "OrderSource", &p->OrderSource);
    set_obj(obj, "OrderStatus", &p->OrderStatus);
    set_obj(obj, "OrderType", &p->OrderType);
    set_obj(obj, "VolumeTraded", &p->VolumeTraded);
    set_obj(obj, "VolumeTotal", &p->VolumeTotal);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "ActiveTime", &p->ActiveTime);
    set_obj(obj, "SuspendTime", &p->SuspendTime);
    set_obj(obj, "UpdateTime", &p->UpdateTime);
    set_obj(obj, "CancelTime", &p->CancelTime);
    set_obj(obj, "ActiveTraderID", &p->ActiveTraderID);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "UserForceClose", &p->UserForceClose);
    set_obj(obj, "ActiveUserID", &p->ActiveUserID);
    set_obj(obj, "BrokerOrderSeq", &p->BrokerOrderSeq);
    set_obj(obj, "RelativeOrderSysID", &p->RelativeOrderSysID);
    set_obj(obj, "ZCETotalTradedVolume", &p->ZCETotalTradedVolume);
    set_obj(obj, "IsSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderField *p)
{
    set_obj(obj, "OrderPriceType", &p->OrderPriceType);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "CombOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "CombHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "TimeCondition", &p->TimeCondition);
    set_obj(obj, "GTDDate", &p->GTDDate);
    set_obj(obj, "VolumeCondition", &p->VolumeCondition);
    set_obj(obj, "MinVolume", &p->MinVolume);
    set_obj(obj, "ContingentCondition", &p->ContingentCondition);
    set_obj(obj, "StopPrice", &p->StopPrice);
    set_obj(obj, "ForceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "IsAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "OrderSource", &p->OrderSource);
    set_obj(obj, "OrderStatus", &p->OrderStatus);
    set_obj(obj, "OrderType", &p->OrderType);
    set_obj(obj, "VolumeTraded", &p->VolumeTraded);
    set_obj(obj, "VolumeTotal", &p->VolumeTotal);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "ActiveTime", &p->ActiveTime);
    set_obj(obj, "SuspendTime", &p->SuspendTime);
    set_obj(obj, "UpdateTime", &p->UpdateTime);
    set_obj(obj, "CancelTime", &p->CancelTime);
    set_obj(obj, "ActiveTraderID", &p->ActiveTraderID);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderInsertErrorField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OrderActionRef", &p->OrderActionRef);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeChange", &p->VolumeChange);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OrderActionRef", &p->OrderActionRef);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeChange", &p->VolumeChange);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderActionField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeChange", &p->VolumeChange);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderActionErrorField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeTradeField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TradeID", &p->TradeID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "TradingRole", &p->TradingRole);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "Price", &p->Price);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "TradeType", &p->TradeType);
    set_obj(obj, "PriceSource", &p->PriceSource);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "TradeSource", &p->TradeSource);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TradeID", &p->TradeID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "TradingRole", &p->TradingRole);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "Price", &p->Price);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "TradeType", &p->TradeType);
    set_obj(obj, "PriceSource", &p->PriceSource);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "BrokerOrderSeq", &p->BrokerOrderSeq);
    set_obj(obj, "TradeSource", &p->TradeSource);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserSessionField *p)
{
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "LoginDate", &p->LoginDate);
    set_obj(obj, "LoginTime", &p->LoginTime);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "InterfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "ProtocolInfo", &p->ProtocolInfo);
    set_obj(obj, "MacAddress", &p->MacAddress);
    set_obj(obj, "LoginRemark", &p->LoginRemark);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "MaxVolume", &p->MaxVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcSettlementInfoConfirmField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ConfirmDate", &p->ConfirmDate);
    set_obj(obj, "ConfirmTime", &p->ConfirmTime);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncDepositField *p)
{
    set_obj(obj, "DepositSeqNo", &p->DepositSeqNo);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "Deposit", &p->Deposit);
    set_obj(obj, "IsForce", &p->IsForce);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncFundMortgageField *p)
{
    set_obj(obj, "MortgageSeqNo", &p->MortgageSeqNo);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "FromCurrencyID", &p->FromCurrencyID);
    set_obj(obj, "MortgageAmount", &p->MortgageAmount);
    set_obj(obj, "ToCurrencyID", &p->ToCurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerSyncField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInvestorField *p)
{
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorGroupID", &p->InvestorGroupID);
    set_obj(obj, "InvestorName", &p->InvestorName);
    set_obj(obj, "IdentifiedCardType", &p->IdentifiedCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "IsActive", &p->IsActive);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "OpenDate", &p->OpenDate);
    set_obj(obj, "Mobile", &p->Mobile);
    set_obj(obj, "CommModelID", &p->CommModelID);
    set_obj(obj, "MarginModelID", &p->MarginModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingTradingCodeField *p)
{
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IsActive", &p->IsActive);
    set_obj(obj, "ClientIDType", &p->ClientIDType);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInvestorGroupField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorGroupID", &p->InvestorGroupID);
    set_obj(obj, "InvestorGroupName", &p->InvestorGroupName);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingTradingAccountField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "PreMortgage", &p->PreMortgage);
    set_obj(obj, "PreCredit", &p->PreCredit);
    set_obj(obj, "PreDeposit", &p->PreDeposit);
    set_obj(obj, "PreBalance", &p->PreBalance);
    set_obj(obj, "PreMargin", &p->PreMargin);
    set_obj(obj, "InterestBase", &p->InterestBase);
    set_obj(obj, "Interest", &p->Interest);
    set_obj(obj, "Deposit", &p->Deposit);
    set_obj(obj, "Withdraw", &p->Withdraw);
    set_obj(obj, "FrozenMargin", &p->FrozenMargin);
    set_obj(obj, "FrozenCash", &p->FrozenCash);
    set_obj(obj, "FrozenCommission", &p->FrozenCommission);
    set_obj(obj, "CurrMargin", &p->CurrMargin);
    set_obj(obj, "CashIn", &p->CashIn);
    set_obj(obj, "Commission", &p->Commission);
    set_obj(obj, "CloseProfit", &p->CloseProfit);
    set_obj(obj, "PositionProfit", &p->PositionProfit);
    set_obj(obj, "Balance", &p->Balance);
    set_obj(obj, "Available", &p->Available);
    set_obj(obj, "WithdrawQuota", &p->WithdrawQuota);
    set_obj(obj, "Reserve", &p->Reserve);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "Credit", &p->Credit);
    set_obj(obj, "Mortgage", &p->Mortgage);
    set_obj(obj, "ExchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "DeliveryMargin", &p->DeliveryMargin);
    set_obj(obj, "ExchangeDeliveryMargin", &p->ExchangeDeliveryMargin);
    set_obj(obj, "ReserveBalance", &p->ReserveBalance);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "PreFundMortgageIn", &p->PreFundMortgageIn);
    set_obj(obj, "PreFundMortgageOut", &p->PreFundMortgageOut);
    set_obj(obj, "FundMortgageIn", &p->FundMortgageIn);
    set_obj(obj, "FundMortgageOut", &p->FundMortgageOut);
    set_obj(obj, "FundMortgageAvailable", &p->FundMortgageAvailable);
    set_obj(obj, "MortgageableFund", &p->MortgageableFund);
    set_obj(obj, "SpecProductMargin", &p->SpecProductMargin);
    set_obj(obj, "SpecProductFrozenMargin", &p->SpecProductFrozenMargin);
    set_obj(obj, "SpecProductCommission", &p->SpecProductCommission);
    set_obj(obj, "SpecProductFrozenCommission", &p->SpecProductFrozenCommission);
    set_obj(obj, "SpecProductPositionProfit", &p->SpecProductPositionProfit);
    set_obj(obj, "SpecProductCloseProfit", &p->SpecProductCloseProfit);
    set_obj(obj, "SpecProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg);
    set_obj(obj, "SpecProductExchangeMargin", &p->SpecProductExchangeMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInvestorPositionField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "PosiDirection", &p->PosiDirection);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "PositionDate", &p->PositionDate);
    set_obj(obj, "YdPosition", &p->YdPosition);
    set_obj(obj, "Position", &p->Position);
    set_obj(obj, "LongFrozen", &p->LongFrozen);
    set_obj(obj, "ShortFrozen", &p->ShortFrozen);
    set_obj(obj, "LongFrozenAmount", &p->LongFrozenAmount);
    set_obj(obj, "ShortFrozenAmount", &p->ShortFrozenAmount);
    set_obj(obj, "OpenVolume", &p->OpenVolume);
    set_obj(obj, "CloseVolume", &p->CloseVolume);
    set_obj(obj, "OpenAmount", &p->OpenAmount);
    set_obj(obj, "CloseAmount", &p->CloseAmount);
    set_obj(obj, "PositionCost", &p->PositionCost);
    set_obj(obj, "PreMargin", &p->PreMargin);
    set_obj(obj, "UseMargin", &p->UseMargin);
    set_obj(obj, "FrozenMargin", &p->FrozenMargin);
    set_obj(obj, "FrozenCash", &p->FrozenCash);
    set_obj(obj, "FrozenCommission", &p->FrozenCommission);
    set_obj(obj, "CashIn", &p->CashIn);
    set_obj(obj, "Commission", &p->Commission);
    set_obj(obj, "CloseProfit", &p->CloseProfit);
    set_obj(obj, "PositionProfit", &p->PositionProfit);
    set_obj(obj, "PreSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "SettlementPrice", &p->SettlementPrice);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "OpenCost", &p->OpenCost);
    set_obj(obj, "ExchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "CombPosition", &p->CombPosition);
    set_obj(obj, "CombLongFrozen", &p->CombLongFrozen);
    set_obj(obj, "CombShortFrozen", &p->CombShortFrozen);
    set_obj(obj, "CloseProfitByDate", &p->CloseProfitByDate);
    set_obj(obj, "CloseProfitByTrade", &p->CloseProfitByTrade);
    set_obj(obj, "TodayPosition", &p->TodayPosition);
    set_obj(obj, "MarginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "MarginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "StrikeFrozen", &p->StrikeFrozen);
    set_obj(obj, "StrikeFrozenAmount", &p->StrikeFrozenAmount);
    set_obj(obj, "AbandonFrozen", &p->AbandonFrozen);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInstrumentMarginRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "IsRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInstrumentCommissionRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OpenRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "OpenRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "CloseRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "CloseRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInstrumentTradingRightField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "TradingRight", &p->TradingRight);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "InsertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "InsertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TradeID", &p->TradeID);
    set_obj(obj, "TradeTimeStart", &p->TradeTimeStart);
    set_obj(obj, "TradeTimeEnd", &p->TradeTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorPositionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradingAccountField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradingCodeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ClientIDType", &p->ClientIDType);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorGroupField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentMarginRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentCommissionRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentTradingRightField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTraderField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySuperUserFunctionField *p)
{
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryUserSessionField *p)
{
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryPartBrokerField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryFrontStatusField *p)
{
    set_obj(obj, "FrontID", &p->FrontID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeOrderField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeOrderActionField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySuperUserField *p)
{
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryProductField *p)
{
    set_obj(obj, "ProductID", &p->ProductID);
    set_obj(obj, "ProductClass", &p->ProductClass);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "ProductID", &p->ProductID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryDepthMarketDataField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerUserField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerUserFunctionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTraderOfferField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySyncDepositField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "DepositSeqNo", &p->DepositSeqNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySettlementInfoField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "TradingDay", &p->TradingDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeMarginRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeMarginRateAdjustField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "FromCurrencyID", &p->FromCurrencyID);
    set_obj(obj, "ToCurrencyID", &p->ToCurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySyncFundMortgageField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "MortgageSeqNo", &p->MortgageSeqNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryHisOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "InsertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "InsertTimeEnd", &p->InsertTimeEnd);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrMiniMarginField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "MinMargin", &p->MinMargin);
    set_obj(obj, "ValueMethod", &p->ValueMethod);
    set_obj(obj, "IsRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrMarginAdjustField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "SShortMarginRatioByMoney", &p->SShortMarginRatioByMoney);
    set_obj(obj, "SShortMarginRatioByVolume", &p->SShortMarginRatioByVolume);
    set_obj(obj, "HShortMarginRatioByMoney", &p->HShortMarginRatioByMoney);
    set_obj(obj, "HShortMarginRatioByVolume", &p->HShortMarginRatioByVolume);
    set_obj(obj, "AShortMarginRatioByMoney", &p->AShortMarginRatioByMoney);
    set_obj(obj, "AShortMarginRatioByVolume", &p->AShortMarginRatioByVolume);
    set_obj(obj, "IsRelative", &p->IsRelative);
    set_obj(obj, "MShortMarginRatioByMoney", &p->MShortMarginRatioByMoney);
    set_obj(obj, "MShortMarginRatioByVolume", &p->MShortMarginRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrCommRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OpenRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "OpenRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "CloseRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "CloseRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume);
    set_obj(obj, "StrikeRatioByMoney", &p->StrikeRatioByMoney);
    set_obj(obj, "StrikeRatioByVolume", &p->StrikeRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrTradeCostField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "FixedMargin", &p->FixedMargin);
    set_obj(obj, "MiniMargin", &p->MiniMargin);
    set_obj(obj, "Royalty", &p->Royalty);
    set_obj(obj, "ExchFixedMargin", &p->ExchFixedMargin);
    set_obj(obj, "ExchMiniMargin", &p->ExchMiniMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOptionInstrTradeCostField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "InputPrice", &p->InputPrice);
    set_obj(obj, "UnderlyingPrice", &p->UnderlyingPrice);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOptionInstrCommRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcIndexPriceField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ClosePrice", &p->ClosePrice);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputExecOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExecOrderRef", &p->ExecOrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "ActionType", &p->ActionType);
    set_obj(obj, "PosiDirection", &p->PosiDirection);
    set_obj(obj, "ReservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "CloseFlag", &p->CloseFlag);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputExecOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExecOrderActionRef", &p->ExecOrderActionRef);
    set_obj(obj, "ExecOrderRef", &p->ExecOrderRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExecOrderSysID", &p->ExecOrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExecOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExecOrderRef", &p->ExecOrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "ActionType", &p->ActionType);
    set_obj(obj, "PosiDirection", &p->PosiDirection);
    set_obj(obj, "ReservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "CloseFlag", &p->CloseFlag);
    set_obj(obj, "ExecOrderLocalID", &p->ExecOrderLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "ExecOrderSysID", &p->ExecOrderSysID);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "CancelTime", &p->CancelTime);
    set_obj(obj, "ExecResult", &p->ExecResult);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "ActiveUserID", &p->ActiveUserID);
    set_obj(obj, "BrokerExecOrderSeq", &p->BrokerExecOrderSeq);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExecOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExecOrderActionRef", &p->ExecOrderActionRef);
    set_obj(obj, "ExecOrderRef", &p->ExecOrderRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExecOrderSysID", &p->ExecOrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "ExecOrderLocalID", &p->ExecOrderLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "ActionType", &p->ActionType);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExecOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExecOrderSysID", &p->ExecOrderSysID);
    set_obj(obj, "InsertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "InsertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeExecOrderField *p)
{
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "ActionType", &p->ActionType);
    set_obj(obj, "PosiDirection", &p->PosiDirection);
    set_obj(obj, "ReservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "CloseFlag", &p->CloseFlag);
    set_obj(obj, "ExecOrderLocalID", &p->ExecOrderLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "ExecOrderSysID", &p->ExecOrderSysID);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "CancelTime", &p->CancelTime);
    set_obj(obj, "ExecResult", &p->ExecResult);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeExecOrderField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExecOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeExecOrderActionField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExecOrderSysID", &p->ExecOrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "ExecOrderLocalID", &p->ExecOrderLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "ActionType", &p->ActionType);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeExecOrderActionField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrExecOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExecOrderRef", &p->ExecOrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "ActionType", &p->ActionType);
    set_obj(obj, "PosiDirection", &p->PosiDirection);
    set_obj(obj, "ReservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "CloseFlag", &p->CloseFlag);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrExecOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrExecOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExecOrderActionRef", &p->ExecOrderActionRef);
    set_obj(obj, "ExecOrderRef", &p->ExecOrderRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExecOrderSysID", &p->ExecOrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrExecOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrTradingRightField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "TradingRight", &p->TradingRight);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOptionInstrTradingRightField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "Direction", &p->Direction);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputForQuoteField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ForQuoteRef", &p->ForQuoteRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcForQuoteField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ForQuoteRef", &p->ForQuoteRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "ForQuoteLocalID", &p->ForQuoteLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "ForQuoteStatus", &p->ForQuoteStatus);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "ActiveUserID", &p->ActiveUserID);
    set_obj(obj, "BrokerForQutoSeq", &p->BrokerForQutoSeq);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryForQuoteField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InsertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "InsertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeForQuoteField *p)
{
    set_obj(obj, "ForQuoteLocalID", &p->ForQuoteLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "ForQuoteStatus", &p->ForQuoteStatus);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeForQuoteField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputQuoteField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "QuoteRef", &p->QuoteRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "AskPrice", &p->AskPrice);
    set_obj(obj, "BidPrice", &p->BidPrice);
    set_obj(obj, "AskVolume", &p->AskVolume);
    set_obj(obj, "BidVolume", &p->BidVolume);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "AskOffsetFlag", &p->AskOffsetFlag);
    set_obj(obj, "BidOffsetFlag", &p->BidOffsetFlag);
    set_obj(obj, "AskHedgeFlag", &p->AskHedgeFlag);
    set_obj(obj, "BidHedgeFlag", &p->BidHedgeFlag);
    set_obj(obj, "AskOrderRef", &p->AskOrderRef);
    set_obj(obj, "BidOrderRef", &p->BidOrderRef);
    set_obj(obj, "ForQuoteSysID", &p->ForQuoteSysID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputQuoteActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "QuoteActionRef", &p->QuoteActionRef);
    set_obj(obj, "QuoteRef", &p->QuoteRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "QuoteSysID", &p->QuoteSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQuoteField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "QuoteRef", &p->QuoteRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "AskPrice", &p->AskPrice);
    set_obj(obj, "BidPrice", &p->BidPrice);
    set_obj(obj, "AskVolume", &p->AskVolume);
    set_obj(obj, "BidVolume", &p->BidVolume);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "AskOffsetFlag", &p->AskOffsetFlag);
    set_obj(obj, "BidOffsetFlag", &p->BidOffsetFlag);
    set_obj(obj, "AskHedgeFlag", &p->AskHedgeFlag);
    set_obj(obj, "BidHedgeFlag", &p->BidHedgeFlag);
    set_obj(obj, "QuoteLocalID", &p->QuoteLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "OrderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "QuoteSysID", &p->QuoteSysID);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "CancelTime", &p->CancelTime);
    set_obj(obj, "QuoteStatus", &p->QuoteStatus);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "AskOrderSysID", &p->AskOrderSysID);
    set_obj(obj, "BidOrderSysID", &p->BidOrderSysID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "ActiveUserID", &p->ActiveUserID);
    set_obj(obj, "BrokerQuoteSeq", &p->BrokerQuoteSeq);
    set_obj(obj, "AskOrderRef", &p->AskOrderRef);
    set_obj(obj, "BidOrderRef", &p->BidOrderRef);
    set_obj(obj, "ForQuoteSysID", &p->ForQuoteSysID);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQuoteActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "QuoteActionRef", &p->QuoteActionRef);
    set_obj(obj, "QuoteRef", &p->QuoteRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "QuoteSysID", &p->QuoteSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "QuoteLocalID", &p->QuoteLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryQuoteField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "QuoteSysID", &p->QuoteSysID);
    set_obj(obj, "InsertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "InsertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeQuoteField *p)
{
    set_obj(obj, "AskPrice", &p->AskPrice);
    set_obj(obj, "BidPrice", &p->BidPrice);
    set_obj(obj, "AskVolume", &p->AskVolume);
    set_obj(obj, "BidVolume", &p->BidVolume);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "AskOffsetFlag", &p->AskOffsetFlag);
    set_obj(obj, "BidOffsetFlag", &p->BidOffsetFlag);
    set_obj(obj, "AskHedgeFlag", &p->AskHedgeFlag);
    set_obj(obj, "BidHedgeFlag", &p->BidHedgeFlag);
    set_obj(obj, "QuoteLocalID", &p->QuoteLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "OrderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "QuoteSysID", &p->QuoteSysID);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "CancelTime", &p->CancelTime);
    set_obj(obj, "QuoteStatus", &p->QuoteStatus);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "AskOrderSysID", &p->AskOrderSysID);
    set_obj(obj, "BidOrderSysID", &p->BidOrderSysID);
    set_obj(obj, "ForQuoteSysID", &p->ForQuoteSysID);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeQuoteField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryQuoteActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeQuoteActionField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "QuoteSysID", &p->QuoteSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "QuoteLocalID", &p->QuoteLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeQuoteActionField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrDeltaField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "Delta", &p->Delta);
}
static void set_obj(Local<Object>& obj, CThostFtdcForQuoteRspField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ForQuoteSysID", &p->ForQuoteSysID);
    set_obj(obj, "ForQuoteTime", &p->ForQuoteTime);
    set_obj(obj, "ActionDay", &p->ActionDay);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcStrikeOffsetField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "Offset", &p->Offset);
    set_obj(obj, "OffsetType", &p->OffsetType);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryStrikeOffsetField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputBatchOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OrderActionRef", &p->OrderActionRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcBatchOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OrderActionRef", &p->OrderActionRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeBatchOrderActionField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBatchOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCombInstrumentGuardField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "GuarantRatio", &p->GuarantRatio);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCombInstrumentGuardField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputCombActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "CombActionRef", &p->CombActionRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "CombDirection", &p->CombDirection);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcCombActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "CombActionRef", &p->CombActionRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "CombDirection", &p->CombDirection);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "ActionStatus", &p->ActionStatus);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCombActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeCombActionField *p)
{
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "CombDirection", &p->CombDirection);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "ActionStatus", &p->ActionStatus);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeCombActionField *p)
{
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcProductExchRateField *p)
{
    set_obj(obj, "ProductID", &p->ProductID);
    set_obj(obj, "QuoteCurrencyID", &p->QuoteCurrencyID);
    set_obj(obj, "ExchangeRate", &p->ExchangeRate);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryProductExchRateField *p)
{
    set_obj(obj, "ProductID", &p->ProductID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryForQuoteParamField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcForQuoteParamField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "LastPrice", &p->LastPrice);
    set_obj(obj, "PriceInterval", &p->PriceInterval);
}
static void set_obj(Local<Object>& obj, CThostFtdcMMOptionInstrCommRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OpenRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "OpenRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "CloseRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "CloseRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume);
    set_obj(obj, "StrikeRatioByMoney", &p->StrikeRatioByMoney);
    set_obj(obj, "StrikeRatioByVolume", &p->StrikeRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMMOptionInstrCommRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMMInstrumentCommissionRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OpenRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "OpenRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "CloseRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "CloseRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMMInstrumentCommissionRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentOrderCommRateField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "OrderCommByVolume", &p->OrderCommByVolume);
    set_obj(obj, "OrderActionCommByVolume", &p->OrderActionCommByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentOrderCommRateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "LastPrice", &p->LastPrice);
    set_obj(obj, "PreSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "PreClosePrice", &p->PreClosePrice);
    set_obj(obj, "PreOpenInterest", &p->PreOpenInterest);
    set_obj(obj, "OpenPrice", &p->OpenPrice);
    set_obj(obj, "HighestPrice", &p->HighestPrice);
    set_obj(obj, "LowestPrice", &p->LowestPrice);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "Turnover", &p->Turnover);
    set_obj(obj, "OpenInterest", &p->OpenInterest);
    set_obj(obj, "ClosePrice", &p->ClosePrice);
    set_obj(obj, "SettlementPrice", &p->SettlementPrice);
    set_obj(obj, "UpperLimitPrice", &p->UpperLimitPrice);
    set_obj(obj, "LowerLimitPrice", &p->LowerLimitPrice);
    set_obj(obj, "PreDelta", &p->PreDelta);
    set_obj(obj, "CurrDelta", &p->CurrDelta);
    set_obj(obj, "UpdateTime", &p->UpdateTime);
    set_obj(obj, "UpdateMillisec", &p->UpdateMillisec);
    set_obj(obj, "ActionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBaseField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PreSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "PreClosePrice", &p->PreClosePrice);
    set_obj(obj, "PreOpenInterest", &p->PreOpenInterest);
    set_obj(obj, "PreDelta", &p->PreDelta);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataStaticField *p)
{
    set_obj(obj, "OpenPrice", &p->OpenPrice);
    set_obj(obj, "HighestPrice", &p->HighestPrice);
    set_obj(obj, "LowestPrice", &p->LowestPrice);
    set_obj(obj, "ClosePrice", &p->ClosePrice);
    set_obj(obj, "UpperLimitPrice", &p->UpperLimitPrice);
    set_obj(obj, "LowerLimitPrice", &p->LowerLimitPrice);
    set_obj(obj, "SettlementPrice", &p->SettlementPrice);
    set_obj(obj, "CurrDelta", &p->CurrDelta);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataLastMatchField *p)
{
    set_obj(obj, "LastPrice", &p->LastPrice);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "Turnover", &p->Turnover);
    set_obj(obj, "OpenInterest", &p->OpenInterest);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBestPriceField *p)
{
    set_obj(obj, "BidPrice1", &p->BidPrice1);
    set_obj(obj, "BidVolume1", &p->BidVolume1);
    set_obj(obj, "AskPrice1", &p->AskPrice1);
    set_obj(obj, "AskVolume1", &p->AskVolume1);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBid23Field *p)
{
    set_obj(obj, "BidPrice2", &p->BidPrice2);
    set_obj(obj, "BidVolume2", &p->BidVolume2);
    set_obj(obj, "BidPrice3", &p->BidPrice3);
    set_obj(obj, "BidVolume3", &p->BidVolume3);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataAsk23Field *p)
{
    set_obj(obj, "AskPrice2", &p->AskPrice2);
    set_obj(obj, "AskVolume2", &p->AskVolume2);
    set_obj(obj, "AskPrice3", &p->AskPrice3);
    set_obj(obj, "AskVolume3", &p->AskVolume3);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBid45Field *p)
{
    set_obj(obj, "BidPrice4", &p->BidPrice4);
    set_obj(obj, "BidVolume4", &p->BidVolume4);
    set_obj(obj, "BidPrice5", &p->BidPrice5);
    set_obj(obj, "BidVolume5", &p->BidVolume5);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataAsk45Field *p)
{
    set_obj(obj, "AskPrice4", &p->AskPrice4);
    set_obj(obj, "AskVolume4", &p->AskVolume4);
    set_obj(obj, "AskPrice5", &p->AskPrice5);
    set_obj(obj, "AskVolume5", &p->AskVolume5);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataUpdateTimeField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "UpdateTime", &p->UpdateTime);
    set_obj(obj, "UpdateMillisec", &p->UpdateMillisec);
    set_obj(obj, "ActionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataExchangeField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSpecificInstrumentField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentStatusField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "SettlementGroupID", &p->SettlementGroupID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "InstrumentStatus", &p->InstrumentStatus);
    set_obj(obj, "TradingSegmentSN", &p->TradingSegmentSN);
    set_obj(obj, "EnterTime", &p->EnterTime);
    set_obj(obj, "EnterReason", &p->EnterReason);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentStatusField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorAccountField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcPositionProfitAlgorithmField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Algorithm", &p->Algorithm);
    set_obj(obj, "Memo", &p->Memo);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcDiscountField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "Discount", &p->Discount);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTransferBankField *p)
{
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBrchID", &p->BankBrchID);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferBankField *p)
{
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBrchID", &p->BankBrchID);
    set_obj(obj, "BankName", &p->BankName);
    set_obj(obj, "IsActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorPositionDetailField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorPositionDetailField *p)
{
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "OpenDate", &p->OpenDate);
    set_obj(obj, "TradeID", &p->TradeID);
    set_obj(obj, "Volume", &p->Volume);
    set_obj(obj, "OpenPrice", &p->OpenPrice);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "TradeType", &p->TradeType);
    set_obj(obj, "CombInstrumentID", &p->CombInstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "CloseProfitByDate", &p->CloseProfitByDate);
    set_obj(obj, "CloseProfitByTrade", &p->CloseProfitByTrade);
    set_obj(obj, "PositionProfitByDate", &p->PositionProfitByDate);
    set_obj(obj, "PositionProfitByTrade", &p->PositionProfitByTrade);
    set_obj(obj, "Margin", &p->Margin);
    set_obj(obj, "ExchMargin", &p->ExchMargin);
    set_obj(obj, "MarginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "MarginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "LastSettlementPrice", &p->LastSettlementPrice);
    set_obj(obj, "SettlementPrice", &p->SettlementPrice);
    set_obj(obj, "CloseVolume", &p->CloseVolume);
    set_obj(obj, "CloseAmount", &p->CloseAmount);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountPasswordField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMDTraderOfferField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "TraderConnectStatus", &p->TraderConnectStatus);
    set_obj(obj, "ConnectRequestDate", &p->ConnectRequestDate);
    set_obj(obj, "ConnectRequestTime", &p->ConnectRequestTime);
    set_obj(obj, "LastReportDate", &p->LastReportDate);
    set_obj(obj, "LastReportTime", &p->LastReportTime);
    set_obj(obj, "ConnectDate", &p->ConnectDate);
    set_obj(obj, "ConnectTime", &p->ConnectTime);
    set_obj(obj, "StartDate", &p->StartDate);
    set_obj(obj, "StartTime", &p->StartTime);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "MaxTradeID", &p->MaxTradeID);
    set_obj(obj, "MaxOrderMessageReference", &p->MaxOrderMessageReference);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMDTraderOfferField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "TraderID", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryNoticeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcNoticeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "Content", &p->Content);
    set_obj(obj, "SequenceLabel", &p->SequenceLabel);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserRightField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserRightType", &p->UserRightType);
    set_obj(obj, "IsForbidden", &p->IsForbidden);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySettlementInfoConfirmField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLoadSettlementInfoField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerWithdrawAlgorithmField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "WithdrawAlgorithm", &p->WithdrawAlgorithm);
    set_obj(obj, "UsingRatio", &p->UsingRatio);
    set_obj(obj, "IncludeCloseProfit", &p->IncludeCloseProfit);
    set_obj(obj, "AllWithoutTrade", &p->AllWithoutTrade);
    set_obj(obj, "AvailIncludeCloseProfit", &p->AvailIncludeCloseProfit);
    set_obj(obj, "IsBrokerUserEvent", &p->IsBrokerUserEvent);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "FundMortgageRatio", &p->FundMortgageRatio);
    set_obj(obj, "BalanceAlgorithm", &p->BalanceAlgorithm);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateV1Field *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OldPassword", &p->OldPassword);
    set_obj(obj, "NewPassword", &p->NewPassword);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "OldPassword", &p->OldPassword);
    set_obj(obj, "NewPassword", &p->NewPassword);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCombinationLegField *p)
{
    set_obj(obj, "CombInstrumentID", &p->CombInstrumentID);
    set_obj(obj, "LegID", &p->LegID);
    set_obj(obj, "LegInstrumentID", &p->LegInstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySyncStatusField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcCombinationLegField *p)
{
    set_obj(obj, "CombInstrumentID", &p->CombInstrumentID);
    set_obj(obj, "LegID", &p->LegID);
    set_obj(obj, "LegInstrumentID", &p->LegInstrumentID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "LegMultiple", &p->LegMultiple);
    set_obj(obj, "ImplyLevel", &p->ImplyLevel);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncStatusField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "DataSyncStatus", &p->DataSyncStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryLinkManField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLinkManField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "PersonType", &p->PersonType);
    set_obj(obj, "IdentifiedCardType", &p->IdentifiedCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "PersonName", &p->PersonName);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Priority", &p->Priority);
    set_obj(obj, "UOAZipCode", &p->UOAZipCode);
    set_obj(obj, "PersonFullName", &p->PersonFullName);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerUserEventField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserEventType", &p->UserEventType);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserEventField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "UserEventType", &p->UserEventType);
    set_obj(obj, "EventSequenceNo", &p->EventSequenceNo);
    set_obj(obj, "EventDate", &p->EventDate);
    set_obj(obj, "EventTime", &p->EventTime);
    set_obj(obj, "UserEventInfo", &p->UserEventInfo);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryContractBankField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBrchID", &p->BankBrchID);
}
static void set_obj(Local<Object>& obj, CThostFtdcContractBankField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBrchID", &p->BankBrchID);
    set_obj(obj, "BankName", &p->BankName);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorPositionCombineDetailField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "OpenDate", &p->OpenDate);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ComTradeID", &p->ComTradeID);
    set_obj(obj, "TradeID", &p->TradeID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "TotalAmt", &p->TotalAmt);
    set_obj(obj, "Margin", &p->Margin);
    set_obj(obj, "ExchMargin", &p->ExchMargin);
    set_obj(obj, "MarginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "MarginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "LegID", &p->LegID);
    set_obj(obj, "LegMultiple", &p->LegMultiple);
    set_obj(obj, "CombInstrumentID", &p->CombInstrumentID);
    set_obj(obj, "TradeGroupID", &p->TradeGroupID);
}
static void set_obj(Local<Object>& obj, CThostFtdcParkedOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OrderPriceType", &p->OrderPriceType);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "CombOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "CombHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "TimeCondition", &p->TimeCondition);
    set_obj(obj, "GTDDate", &p->GTDDate);
    set_obj(obj, "VolumeCondition", &p->VolumeCondition);
    set_obj(obj, "MinVolume", &p->MinVolume);
    set_obj(obj, "ContingentCondition", &p->ContingentCondition);
    set_obj(obj, "StopPrice", &p->StopPrice);
    set_obj(obj, "ForceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "IsAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "UserForceClose", &p->UserForceClose);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParkedOrderID", &p->ParkedOrderID);
    set_obj(obj, "UserType", &p->UserType);
    set_obj(obj, "Status", &p->Status);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
    set_obj(obj, "IsSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcParkedOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OrderActionRef", &p->OrderActionRef);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeChange", &p->VolumeChange);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ParkedOrderActionID", &p->ParkedOrderActionID);
    set_obj(obj, "UserType", &p->UserType);
    set_obj(obj, "Status", &p->Status);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryParkedOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryParkedOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRemoveParkedOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ParkedOrderID", &p->ParkedOrderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRemoveParkedOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ParkedOrderActionID", &p->ParkedOrderActionID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorWithdrawAlgorithmField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "UsingRatio", &p->UsingRatio);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "FundMortgageRatio", &p->FundMortgageRatio);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorPositionCombineDetailField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "CombInstrumentID", &p->CombInstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataAveragePriceField *p)
{
    set_obj(obj, "AveragePrice", &p->AveragePrice);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyInvestorPasswordField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "Password", &p->Password);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserIPField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "IPMask", &p->IPMask);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingNoticeInfoField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "SendTime", &p->SendTime);
    set_obj(obj, "FieldContent", &p->FieldContent);
    set_obj(obj, "SequenceSeries", &p->SequenceSeries);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingNoticeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorRange", &p->InvestorRange);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "SequenceSeries", &p->SequenceSeries);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "SendTime", &p->SendTime);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "FieldContent", &p->FieldContent);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradingNoticeField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OrderPriceType", &p->OrderPriceType);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "CombOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "CombHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "TimeCondition", &p->TimeCondition);
    set_obj(obj, "GTDDate", &p->GTDDate);
    set_obj(obj, "VolumeCondition", &p->VolumeCondition);
    set_obj(obj, "MinVolume", &p->MinVolume);
    set_obj(obj, "ContingentCondition", &p->ContingentCondition);
    set_obj(obj, "StopPrice", &p->StopPrice);
    set_obj(obj, "ForceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "IsAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "UserForceClose", &p->UserForceClose);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
    set_obj(obj, "IsSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrorConditionalOrderField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OrderPriceType", &p->OrderPriceType);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "CombOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "CombHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "TimeCondition", &p->TimeCondition);
    set_obj(obj, "GTDDate", &p->GTDDate);
    set_obj(obj, "VolumeCondition", &p->VolumeCondition);
    set_obj(obj, "MinVolume", &p->MinVolume);
    set_obj(obj, "ContingentCondition", &p->ContingentCondition);
    set_obj(obj, "StopPrice", &p->StopPrice);
    set_obj(obj, "ForceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "IsAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "ExchangeInstID", &p->ExchangeInstID);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "NotifySequence", &p->NotifySequence);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "OrderSource", &p->OrderSource);
    set_obj(obj, "OrderStatus", &p->OrderStatus);
    set_obj(obj, "OrderType", &p->OrderType);
    set_obj(obj, "VolumeTraded", &p->VolumeTraded);
    set_obj(obj, "VolumeTotal", &p->VolumeTotal);
    set_obj(obj, "InsertDate", &p->InsertDate);
    set_obj(obj, "InsertTime", &p->InsertTime);
    set_obj(obj, "ActiveTime", &p->ActiveTime);
    set_obj(obj, "SuspendTime", &p->SuspendTime);
    set_obj(obj, "UpdateTime", &p->UpdateTime);
    set_obj(obj, "CancelTime", &p->CancelTime);
    set_obj(obj, "ActiveTraderID", &p->ActiveTraderID);
    set_obj(obj, "ClearingPartID", &p->ClearingPartID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "UserProductInfo", &p->UserProductInfo);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "UserForceClose", &p->UserForceClose);
    set_obj(obj, "ActiveUserID", &p->ActiveUserID);
    set_obj(obj, "BrokerOrderSeq", &p->BrokerOrderSeq);
    set_obj(obj, "RelativeOrderSysID", &p->RelativeOrderSysID);
    set_obj(obj, "ZCETotalTradedVolume", &p->ZCETotalTradedVolume);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
    set_obj(obj, "IsSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrOrderActionField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "OrderActionRef", &p->OrderActionRef);
    set_obj(obj, "OrderRef", &p->OrderRef);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "FrontID", &p->FrontID);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "OrderSysID", &p->OrderSysID);
    set_obj(obj, "ActionFlag", &p->ActionFlag);
    set_obj(obj, "LimitPrice", &p->LimitPrice);
    set_obj(obj, "VolumeChange", &p->VolumeChange);
    set_obj(obj, "ActionDate", &p->ActionDate);
    set_obj(obj, "ActionTime", &p->ActionTime);
    set_obj(obj, "TraderID", &p->TraderID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "OrderLocalID", &p->OrderLocalID);
    set_obj(obj, "ActionLocalID", &p->ActionLocalID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ClientID", &p->ClientID);
    set_obj(obj, "BusinessUnit", &p->BusinessUnit);
    set_obj(obj, "OrderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "StatusMsg", &p->StatusMsg);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "BranchID", &p->BranchID);
    set_obj(obj, "InvestUnitID", &p->InvestUnitID);
    set_obj(obj, "IPAddress", &p->IPAddress);
    set_obj(obj, "MacAddress", &p->MacAddress);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeSequenceField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeSequenceField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "MarketStatus", &p->MarketStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeWithPriceField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "OffsetFlag", &p->OffsetFlag);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "MaxVolume", &p->MaxVolume);
    set_obj(obj, "Price", &p->Price);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerTradingParamsField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerTradingParamsField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "MarginPriceType", &p->MarginPriceType);
    set_obj(obj, "Algorithm", &p->Algorithm);
    set_obj(obj, "AvailIncludeCloseProfit", &p->AvailIncludeCloseProfit);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "OptionRoyaltyPriceType", &p->OptionRoyaltyPriceType);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerTradingAlgosField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerTradingAlgosField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "HandlePositionAlgoID", &p->HandlePositionAlgoID);
    set_obj(obj, "FindMarginRateAlgoID", &p->FindMarginRateAlgoID);
    set_obj(obj, "HandleTradingAccountAlgoID", &p->HandleTradingAccountAlgoID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryBrokerDepositField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerDepositField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "PreBalance", &p->PreBalance);
    set_obj(obj, "CurrMargin", &p->CurrMargin);
    set_obj(obj, "CloseProfit", &p->CloseProfit);
    set_obj(obj, "Balance", &p->Balance);
    set_obj(obj, "Deposit", &p->Deposit);
    set_obj(obj, "Withdraw", &p->Withdraw);
    set_obj(obj, "Available", &p->Available);
    set_obj(obj, "Reserve", &p->Reserve);
    set_obj(obj, "FrozenMargin", &p->FrozenMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCFMMCBrokerKeyField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCFMMCBrokerKeyField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "CreateDate", &p->CreateDate);
    set_obj(obj, "CreateTime", &p->CreateTime);
    set_obj(obj, "KeyID", &p->KeyID);
    set_obj(obj, "CurrentKey", &p->CurrentKey);
    set_obj(obj, "KeyKind", &p->KeyKind);
}
static void set_obj(Local<Object>& obj, CThostFtdcCFMMCTradingAccountKeyField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "KeyID", &p->KeyID);
    set_obj(obj, "CurrentKey", &p->CurrentKey);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCFMMCTradingAccountKeyField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserOTPParamField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OTPVendorsID", &p->OTPVendorsID);
    set_obj(obj, "SerialNumber", &p->SerialNumber);
    set_obj(obj, "AuthKey", &p->AuthKey);
    set_obj(obj, "LastDrift", &p->LastDrift);
    set_obj(obj, "LastSuccess", &p->LastSuccess);
    set_obj(obj, "OTPType", &p->OTPType);
}
static void set_obj(Local<Object>& obj, CThostFtdcManualSyncBrokerUserOTPField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "OTPType", &p->OTPType);
    set_obj(obj, "FirstOTP", &p->FirstOTP);
    set_obj(obj, "SecondOTP", &p->SecondOTP);
}
static void set_obj(Local<Object>& obj, CThostFtdcCommRateModelField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "CommModelID", &p->CommModelID);
    set_obj(obj, "CommModelName", &p->CommModelName);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCommRateModelField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "CommModelID", &p->CommModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarginModelField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "MarginModelID", &p->MarginModelID);
    set_obj(obj, "MarginModelName", &p->MarginModelName);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMarginModelField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "MarginModelID", &p->MarginModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcEWarrantOffsetField *p)
{
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
    set_obj(obj, "Direction", &p->Direction);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
    set_obj(obj, "Volume", &p->Volume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryEWarrantOffsetField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "InstrumentID", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorProductGroupMarginField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "ProductGroupID", &p->ProductGroupID);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorProductGroupMarginField *p)
{
    set_obj(obj, "ProductGroupID", &p->ProductGroupID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "SettlementID", &p->SettlementID);
    set_obj(obj, "FrozenMargin", &p->FrozenMargin);
    set_obj(obj, "LongFrozenMargin", &p->LongFrozenMargin);
    set_obj(obj, "ShortFrozenMargin", &p->ShortFrozenMargin);
    set_obj(obj, "UseMargin", &p->UseMargin);
    set_obj(obj, "LongUseMargin", &p->LongUseMargin);
    set_obj(obj, "ShortUseMargin", &p->ShortUseMargin);
    set_obj(obj, "ExchMargin", &p->ExchMargin);
    set_obj(obj, "LongExchMargin", &p->LongExchMargin);
    set_obj(obj, "ShortExchMargin", &p->ShortExchMargin);
    set_obj(obj, "CloseProfit", &p->CloseProfit);
    set_obj(obj, "FrozenCommission", &p->FrozenCommission);
    set_obj(obj, "Commission", &p->Commission);
    set_obj(obj, "FrozenCash", &p->FrozenCash);
    set_obj(obj, "CashIn", &p->CashIn);
    set_obj(obj, "PositionProfit", &p->PositionProfit);
    set_obj(obj, "OffsetAmount", &p->OffsetAmount);
    set_obj(obj, "LongOffsetAmount", &p->LongOffsetAmount);
    set_obj(obj, "ShortOffsetAmount", &p->ShortOffsetAmount);
    set_obj(obj, "ExchOffsetAmount", &p->ExchOffsetAmount);
    set_obj(obj, "LongExchOffsetAmount", &p->LongExchOffsetAmount);
    set_obj(obj, "ShortExchOffsetAmount", &p->ShortExchOffsetAmount);
    set_obj(obj, "HedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryCFMMCTradingAccountTokenField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCFMMCTradingAccountTokenField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "ParticipantID", &p->ParticipantID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "KeyID", &p->KeyID);
    set_obj(obj, "Token", &p->Token);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryProductGroupField *p)
{
    set_obj(obj, "ProductID", &p->ProductID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcProductGroupField *p)
{
    set_obj(obj, "ProductID", &p->ProductID);
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "ProductGroupID", &p->ProductGroupID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBulletinField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "BulletinID", &p->BulletinID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "NewsType", &p->NewsType);
    set_obj(obj, "NewsUrgency", &p->NewsUrgency);
    set_obj(obj, "SendTime", &p->SendTime);
    set_obj(obj, "Abstract", &p->Abstract);
    set_obj(obj, "ComeFrom", &p->ComeFrom);
    set_obj(obj, "Content", &p->Content);
    set_obj(obj, "URLLink", &p->URLLink);
    set_obj(obj, "MarketID", &p->MarketID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBulletinField *p)
{
    set_obj(obj, "ExchangeID", &p->ExchangeID);
    set_obj(obj, "BulletinID", &p->BulletinID);
    set_obj(obj, "SequenceNo", &p->SequenceNo);
    set_obj(obj, "NewsType", &p->NewsType);
    set_obj(obj, "NewsUrgency", &p->NewsUrgency);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqOpenAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "CashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqCancelAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "CashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqChangeAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "NewBankAccount", &p->NewBankAccount);
    set_obj(obj, "NewBankPassWord", &p->NewBankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "Digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqTransferField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "TradeAmount", &p->TradeAmount);
    set_obj(obj, "FutureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "FeePayFlag", &p->FeePayFlag);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "BrokerFee", &p->BrokerFee);
    set_obj(obj, "Message", &p->Message);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "TransferStatus", &p->TransferStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspTransferField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "TradeAmount", &p->TradeAmount);
    set_obj(obj, "FutureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "FeePayFlag", &p->FeePayFlag);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "BrokerFee", &p->BrokerFee);
    set_obj(obj, "Message", &p->Message);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "TransferStatus", &p->TransferStatus);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqRepealField *p)
{
    set_obj(obj, "RepealTimeInterval", &p->RepealTimeInterval);
    set_obj(obj, "RepealedTimes", &p->RepealedTimes);
    set_obj(obj, "BankRepealFlag", &p->BankRepealFlag);
    set_obj(obj, "BrokerRepealFlag", &p->BrokerRepealFlag);
    set_obj(obj, "PlateRepealSerial", &p->PlateRepealSerial);
    set_obj(obj, "BankRepealSerial", &p->BankRepealSerial);
    set_obj(obj, "FutureRepealSerial", &p->FutureRepealSerial);
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "TradeAmount", &p->TradeAmount);
    set_obj(obj, "FutureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "FeePayFlag", &p->FeePayFlag);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "BrokerFee", &p->BrokerFee);
    set_obj(obj, "Message", &p->Message);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "TransferStatus", &p->TransferStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspRepealField *p)
{
    set_obj(obj, "RepealTimeInterval", &p->RepealTimeInterval);
    set_obj(obj, "RepealedTimes", &p->RepealedTimes);
    set_obj(obj, "BankRepealFlag", &p->BankRepealFlag);
    set_obj(obj, "BrokerRepealFlag", &p->BrokerRepealFlag);
    set_obj(obj, "PlateRepealSerial", &p->PlateRepealSerial);
    set_obj(obj, "BankRepealSerial", &p->BankRepealSerial);
    set_obj(obj, "FutureRepealSerial", &p->FutureRepealSerial);
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "TradeAmount", &p->TradeAmount);
    set_obj(obj, "FutureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "FeePayFlag", &p->FeePayFlag);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "BrokerFee", &p->BrokerFee);
    set_obj(obj, "Message", &p->Message);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "TransferStatus", &p->TransferStatus);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqQueryAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspQueryAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "BankUseAmount", &p->BankUseAmount);
    set_obj(obj, "BankFetchAmount", &p->BankFetchAmount);
}
static void set_obj(Local<Object>& obj, CThostFtdcFutureSignIOField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspFutureSignInField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
    set_obj(obj, "PinKey", &p->PinKey);
    set_obj(obj, "MacKey", &p->MacKey);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqFutureSignOutField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspFutureSignOutField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqQueryTradeResultBySerialField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "Reference", &p->Reference);
    set_obj(obj, "RefrenceIssureType", &p->RefrenceIssureType);
    set_obj(obj, "RefrenceIssure", &p->RefrenceIssure);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "TradeAmount", &p->TradeAmount);
    set_obj(obj, "Digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspQueryTradeResultBySerialField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
    set_obj(obj, "Reference", &p->Reference);
    set_obj(obj, "RefrenceIssureType", &p->RefrenceIssureType);
    set_obj(obj, "RefrenceIssure", &p->RefrenceIssure);
    set_obj(obj, "OriginReturnCode", &p->OriginReturnCode);
    set_obj(obj, "OriginDescrInfoForReturnCode", &p->OriginDescrInfoForReturnCode);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "TradeAmount", &p->TradeAmount);
    set_obj(obj, "Digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqDayEndFileReadyField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "FileBusinessCode", &p->FileBusinessCode);
    set_obj(obj, "Digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcReturnResultField *p)
{
    set_obj(obj, "ReturnCode", &p->ReturnCode);
    set_obj(obj, "DescrInfoForReturnCode", &p->DescrInfoForReturnCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyFuturePasswordField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyCustInfoField *p)
{
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyFuturePasswordAndCustInfoField *p)
{
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcDepositResultInformField *p)
{
    set_obj(obj, "DepositSeqNo", &p->DepositSeqNo);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "Deposit", &p->Deposit);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "ReturnCode", &p->ReturnCode);
    set_obj(obj, "DescrInfoForReturnCode", &p->DescrInfoForReturnCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqSyncKeyField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Message", &p->Message);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspSyncKeyField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Message", &p->Message);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifyQueryAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "BankUseAmount", &p->BankUseAmount);
    set_obj(obj, "BankFetchAmount", &p->BankFetchAmount);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferSerialField *p)
{
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "FutureAccType", &p->FutureAccType);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "InvestorID", &p->InvestorID);
    set_obj(obj, "FutureSerial", &p->FutureSerial);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "TradeAmount", &p->TradeAmount);
    set_obj(obj, "CustFee", &p->CustFee);
    set_obj(obj, "BrokerFee", &p->BrokerFee);
    set_obj(obj, "AvailabilityFlag", &p->AvailabilityFlag);
    set_obj(obj, "OperatorCode", &p->OperatorCode);
    set_obj(obj, "BankNewAccount", &p->BankNewAccount);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTransferSerialField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifyFutureSignInField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
    set_obj(obj, "PinKey", &p->PinKey);
    set_obj(obj, "MacKey", &p->MacKey);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifyFutureSignOutField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifySyncKeyField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "Message", &p->Message);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "RequestID", &p->RequestID);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryAccountregisterField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcAccountregisterField *p)
{
    set_obj(obj, "TradeDay", &p->TradeDay);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "OpenOrDestroy", &p->OpenOrDestroy);
    set_obj(obj, "RegDate", &p->RegDate);
    set_obj(obj, "OutDate", &p->OutDate);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "BankAccType", &p->BankAccType);
}
static void set_obj(Local<Object>& obj, CThostFtdcOpenAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "CashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcCancelAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "CashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "DeviceID", &p->DeviceID);
    set_obj(obj, "BankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "OperNo", &p->OperNo);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcChangeAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "NewBankAccount", &p->NewBankAccount);
    set_obj(obj, "NewBankPassWord", &p->NewBankPassWord);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "BankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "SecuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcSecAgentACIDMapField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "BrokerSecAgentID", &p->BrokerSecAgentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySecAgentACIDMapField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserRightsAssignField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "DRIdentityID", &p->DRIdentityID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserRightAssignField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "DRIdentityID", &p->DRIdentityID);
    set_obj(obj, "Tradeable", &p->Tradeable);
}
static void set_obj(Local<Object>& obj, CThostFtdcDRTransferField *p)
{
    set_obj(obj, "OrigDRIdentityID", &p->OrigDRIdentityID);
    set_obj(obj, "DestDRIdentityID", &p->DestDRIdentityID);
    set_obj(obj, "OrigBrokerID", &p->OrigBrokerID);
    set_obj(obj, "DestBrokerID", &p->DestBrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcFensUserInfoField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "LoginMode", &p->LoginMode);
}
static void set_obj(Local<Object>& obj, CThostFtdcCurrTransferIdentityField *p)
{
    set_obj(obj, "IdentityID", &p->IdentityID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLoginForbiddenUserField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
    set_obj(obj, "IPAddress", &p->IPAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryLoginForbiddenUserField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "UserID", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMulticastGroupInfoField *p)
{
    set_obj(obj, "GroupIP", &p->GroupIP);
    set_obj(obj, "GroupPort", &p->GroupPort);
    set_obj(obj, "SourceIP", &p->SourceIP);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountReserveField *p)
{
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Reserve", &p->Reserve);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReserveOpenAccountConfirmField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "AccountID", &p->AccountID);
    set_obj(obj, "Password", &p->Password);
    set_obj(obj, "BankReserveOpenSeq", &p->BankReserveOpenSeq);
    set_obj(obj, "BookDate", &p->BookDate);
    set_obj(obj, "BookPsw", &p->BookPsw);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReserveOpenAccountField *p)
{
    set_obj(obj, "TradeCode", &p->TradeCode);
    set_obj(obj, "BankID", &p->BankID);
    set_obj(obj, "BankBranchID", &p->BankBranchID);
    set_obj(obj, "BrokerID", &p->BrokerID);
    set_obj(obj, "BrokerBranchID", &p->BrokerBranchID);
    set_obj(obj, "TradeDate", &p->TradeDate);
    set_obj(obj, "TradeTime", &p->TradeTime);
    set_obj(obj, "BankSerial", &p->BankSerial);
    set_obj(obj, "TradingDay", &p->TradingDay);
    set_obj(obj, "PlateSerial", &p->PlateSerial);
    set_obj(obj, "LastFragment", &p->LastFragment);
    set_obj(obj, "SessionID", &p->SessionID);
    set_obj(obj, "CustomerName", &p->CustomerName);
    set_obj(obj, "IdCardType", &p->IdCardType);
    set_obj(obj, "IdentifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "Gender", &p->Gender);
    set_obj(obj, "CountryCode", &p->CountryCode);
    set_obj(obj, "CustType", &p->CustType);
    set_obj(obj, "Address", &p->Address);
    set_obj(obj, "ZipCode", &p->ZipCode);
    set_obj(obj, "Telephone", &p->Telephone);
    set_obj(obj, "MobilePhone", &p->MobilePhone);
    set_obj(obj, "Fax", &p->Fax);
    set_obj(obj, "EMail", &p->EMail);
    set_obj(obj, "MoneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "BankAccount", &p->BankAccount);
    set_obj(obj, "BankPassWord", &p->BankPassWord);
    set_obj(obj, "InstallID", &p->InstallID);
    set_obj(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "CurrencyID", &p->CurrencyID);
    set_obj(obj, "Digest", &p->Digest);
    set_obj(obj, "BankAccType", &p->BankAccType);
    set_obj(obj, "BrokerIDByBank", &p->BrokerIDByBank);
    set_obj(obj, "TID", &p->TID);
    set_obj(obj, "ReserveOpenAccStas", &p->ReserveOpenAccStas);
    set_obj(obj, "ErrorID", &p->ErrorID);
    set_obj(obj, "ErrorMsg", &p->ErrorMsg);
}
static void set_struct(Local<Object>& obj, CThostFtdcDisseminationField *p)
{
    set_struct(obj, "SequenceSeries", &p->SequenceSeries, sizeof(p->SequenceSeries));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqUserLoginField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "InterfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "ProtocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "OneTimePassword", &p->OneTimePassword, sizeof(p->OneTimePassword));
    set_struct(obj, "ClientIPAddress", &p->ClientIPAddress, sizeof(p->ClientIPAddress));
    set_struct(obj, "LoginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspUserLoginField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "LoginTime", &p->LoginTime, sizeof(p->LoginTime));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "SystemName", &p->SystemName, sizeof(p->SystemName));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "MaxOrderRef", &p->MaxOrderRef, sizeof(p->MaxOrderRef));
    set_struct(obj, "SHFETime", &p->SHFETime, sizeof(p->SHFETime));
    set_struct(obj, "DCETime", &p->DCETime, sizeof(p->DCETime));
    set_struct(obj, "CZCETime", &p->CZCETime, sizeof(p->CZCETime));
    set_struct(obj, "FFEXTime", &p->FFEXTime, sizeof(p->FFEXTime));
    set_struct(obj, "INETime", &p->INETime, sizeof(p->INETime));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserLogoutField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcForceUserLogoutField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqAuthenticateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "AuthCode", &p->AuthCode, sizeof(p->AuthCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspAuthenticateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
}
static void set_struct(Local<Object>& obj, CThostFtdcAuthenticationInfoField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "AuthInfo", &p->AuthInfo, sizeof(p->AuthInfo));
    set_struct(obj, "IsResult", &p->IsResult, sizeof(p->IsResult));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferHeaderField *p)
{
    set_struct(obj, "Version", &p->Version, sizeof(p->Version));
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "TradeSerial", &p->TradeSerial, sizeof(p->TradeSerial));
    set_struct(obj, "FutureID", &p->FutureID, sizeof(p->FutureID));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBrchID", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "RecordNum", &p->RecordNum, sizeof(p->RecordNum));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferBankToFutureReqField *p)
{
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "FuturePwdFlag", &p->FuturePwdFlag, sizeof(p->FuturePwdFlag));
    set_struct(obj, "FutureAccPwd", &p->FutureAccPwd, sizeof(p->FutureAccPwd));
    set_struct(obj, "TradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "CurrencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferBankToFutureRspField *p)
{
    set_struct(obj, "RetCode", &p->RetCode, sizeof(p->RetCode));
    set_struct(obj, "RetInfo", &p->RetInfo, sizeof(p->RetInfo));
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "TradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "CurrencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferFutureToBankReqField *p)
{
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "FuturePwdFlag", &p->FuturePwdFlag, sizeof(p->FuturePwdFlag));
    set_struct(obj, "FutureAccPwd", &p->FutureAccPwd, sizeof(p->FutureAccPwd));
    set_struct(obj, "TradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "CurrencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferFutureToBankRspField *p)
{
    set_struct(obj, "RetCode", &p->RetCode, sizeof(p->RetCode));
    set_struct(obj, "RetInfo", &p->RetInfo, sizeof(p->RetInfo));
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "TradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "CurrencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryBankReqField *p)
{
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "FuturePwdFlag", &p->FuturePwdFlag, sizeof(p->FuturePwdFlag));
    set_struct(obj, "FutureAccPwd", &p->FutureAccPwd, sizeof(p->FutureAccPwd));
    set_struct(obj, "CurrencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryBankRspField *p)
{
    set_struct(obj, "RetCode", &p->RetCode, sizeof(p->RetCode));
    set_struct(obj, "RetInfo", &p->RetInfo, sizeof(p->RetInfo));
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "TradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "UseAmt", &p->UseAmt, sizeof(p->UseAmt));
    set_struct(obj, "FetchAmt", &p->FetchAmt, sizeof(p->FetchAmt));
    set_struct(obj, "CurrencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryDetailReqField *p)
{
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryDetailRspField *p)
{
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "FutureID", &p->FutureID, sizeof(p->FutureID));
    set_struct(obj, "FutureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBrchID", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "CertCode", &p->CertCode, sizeof(p->CertCode));
    set_struct(obj, "CurrencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
    set_struct(obj, "TxAmount", &p->TxAmount, sizeof(p->TxAmount));
    set_struct(obj, "Flag", &p->Flag, sizeof(p->Flag));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspInfoField *p)
{
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExchangeName", &p->ExchangeName, sizeof(p->ExchangeName));
    set_struct(obj, "ExchangeProperty", &p->ExchangeProperty, sizeof(p->ExchangeProperty));
}
static void set_struct(Local<Object>& obj, CThostFtdcProductField *p)
{
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "ProductName", &p->ProductName, sizeof(p->ProductName));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ProductClass", &p->ProductClass, sizeof(p->ProductClass));
    set_struct(obj, "VolumeMultiple", &p->VolumeMultiple, sizeof(p->VolumeMultiple));
    set_struct(obj, "PriceTick", &p->PriceTick, sizeof(p->PriceTick));
    set_struct(obj, "MaxMarketOrderVolume", &p->MaxMarketOrderVolume, sizeof(p->MaxMarketOrderVolume));
    set_struct(obj, "MinMarketOrderVolume", &p->MinMarketOrderVolume, sizeof(p->MinMarketOrderVolume));
    set_struct(obj, "MaxLimitOrderVolume", &p->MaxLimitOrderVolume, sizeof(p->MaxLimitOrderVolume));
    set_struct(obj, "MinLimitOrderVolume", &p->MinLimitOrderVolume, sizeof(p->MinLimitOrderVolume));
    set_struct(obj, "PositionType", &p->PositionType, sizeof(p->PositionType));
    set_struct(obj, "PositionDateType", &p->PositionDateType, sizeof(p->PositionDateType));
    set_struct(obj, "CloseDealType", &p->CloseDealType, sizeof(p->CloseDealType));
    set_struct(obj, "TradeCurrencyID", &p->TradeCurrencyID, sizeof(p->TradeCurrencyID));
    set_struct(obj, "MortgageFundUseRange", &p->MortgageFundUseRange, sizeof(p->MortgageFundUseRange));
    set_struct(obj, "ExchangeProductID", &p->ExchangeProductID, sizeof(p->ExchangeProductID));
    set_struct(obj, "UnderlyingMultiple", &p->UnderlyingMultiple, sizeof(p->UnderlyingMultiple));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InstrumentName", &p->InstrumentName, sizeof(p->InstrumentName));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "ProductClass", &p->ProductClass, sizeof(p->ProductClass));
    set_struct(obj, "DeliveryYear", &p->DeliveryYear, sizeof(p->DeliveryYear));
    set_struct(obj, "DeliveryMonth", &p->DeliveryMonth, sizeof(p->DeliveryMonth));
    set_struct(obj, "MaxMarketOrderVolume", &p->MaxMarketOrderVolume, sizeof(p->MaxMarketOrderVolume));
    set_struct(obj, "MinMarketOrderVolume", &p->MinMarketOrderVolume, sizeof(p->MinMarketOrderVolume));
    set_struct(obj, "MaxLimitOrderVolume", &p->MaxLimitOrderVolume, sizeof(p->MaxLimitOrderVolume));
    set_struct(obj, "MinLimitOrderVolume", &p->MinLimitOrderVolume, sizeof(p->MinLimitOrderVolume));
    set_struct(obj, "VolumeMultiple", &p->VolumeMultiple, sizeof(p->VolumeMultiple));
    set_struct(obj, "PriceTick", &p->PriceTick, sizeof(p->PriceTick));
    set_struct(obj, "CreateDate", &p->CreateDate, sizeof(p->CreateDate));
    set_struct(obj, "OpenDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "ExpireDate", &p->ExpireDate, sizeof(p->ExpireDate));
    set_struct(obj, "StartDelivDate", &p->StartDelivDate, sizeof(p->StartDelivDate));
    set_struct(obj, "EndDelivDate", &p->EndDelivDate, sizeof(p->EndDelivDate));
    set_struct(obj, "InstLifePhase", &p->InstLifePhase, sizeof(p->InstLifePhase));
    set_struct(obj, "IsTrading", &p->IsTrading, sizeof(p->IsTrading));
    set_struct(obj, "PositionType", &p->PositionType, sizeof(p->PositionType));
    set_struct(obj, "PositionDateType", &p->PositionDateType, sizeof(p->PositionDateType));
    set_struct(obj, "LongMarginRatio", &p->LongMarginRatio, sizeof(p->LongMarginRatio));
    set_struct(obj, "ShortMarginRatio", &p->ShortMarginRatio, sizeof(p->ShortMarginRatio));
    set_struct(obj, "MaxMarginSideAlgorithm", &p->MaxMarginSideAlgorithm, sizeof(p->MaxMarginSideAlgorithm));
    set_struct(obj, "UnderlyingInstrID", &p->UnderlyingInstrID, sizeof(p->UnderlyingInstrID));
    set_struct(obj, "StrikePrice", &p->StrikePrice, sizeof(p->StrikePrice));
    set_struct(obj, "OptionsType", &p->OptionsType, sizeof(p->OptionsType));
    set_struct(obj, "UnderlyingMultiple", &p->UnderlyingMultiple, sizeof(p->UnderlyingMultiple));
    set_struct(obj, "CombinationType", &p->CombinationType, sizeof(p->CombinationType));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerAbbr", &p->BrokerAbbr, sizeof(p->BrokerAbbr));
    set_struct(obj, "BrokerName", &p->BrokerName, sizeof(p->BrokerName));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcTraderField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallCount", &p->InstallCount, sizeof(p->InstallCount));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorField *p)
{
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorGroupID", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "InvestorName", &p->InvestorName, sizeof(p->InvestorName));
    set_struct(obj, "IdentifiedCardType", &p->IdentifiedCardType, sizeof(p->IdentifiedCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "OpenDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "Mobile", &p->Mobile, sizeof(p->Mobile));
    set_struct(obj, "CommModelID", &p->CommModelID, sizeof(p->CommModelID));
    set_struct(obj, "MarginModelID", &p->MarginModelID, sizeof(p->MarginModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingCodeField *p)
{
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "ClientIDType", &p->ClientIDType, sizeof(p->ClientIDType));
}
static void set_struct(Local<Object>& obj, CThostFtdcPartBrokerField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcSuperUserField *p)
{
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserName", &p->UserName, sizeof(p->UserName));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcSuperUserFunctionField *p)
{
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "FunctionCode", &p->FunctionCode, sizeof(p->FunctionCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorGroupField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorGroupID", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "InvestorGroupName", &p->InvestorGroupName, sizeof(p->InvestorGroupName));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "PreMortgage", &p->PreMortgage, sizeof(p->PreMortgage));
    set_struct(obj, "PreCredit", &p->PreCredit, sizeof(p->PreCredit));
    set_struct(obj, "PreDeposit", &p->PreDeposit, sizeof(p->PreDeposit));
    set_struct(obj, "PreBalance", &p->PreBalance, sizeof(p->PreBalance));
    set_struct(obj, "PreMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "InterestBase", &p->InterestBase, sizeof(p->InterestBase));
    set_struct(obj, "Interest", &p->Interest, sizeof(p->Interest));
    set_struct(obj, "Deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "Withdraw", &p->Withdraw, sizeof(p->Withdraw));
    set_struct(obj, "FrozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "FrozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "FrozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "CurrMargin", &p->CurrMargin, sizeof(p->CurrMargin));
    set_struct(obj, "CashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "Commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "CloseProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "PositionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "Balance", &p->Balance, sizeof(p->Balance));
    set_struct(obj, "Available", &p->Available, sizeof(p->Available));
    set_struct(obj, "WithdrawQuota", &p->WithdrawQuota, sizeof(p->WithdrawQuota));
    set_struct(obj, "Reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "Credit", &p->Credit, sizeof(p->Credit));
    set_struct(obj, "Mortgage", &p->Mortgage, sizeof(p->Mortgage));
    set_struct(obj, "ExchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "DeliveryMargin", &p->DeliveryMargin, sizeof(p->DeliveryMargin));
    set_struct(obj, "ExchangeDeliveryMargin", &p->ExchangeDeliveryMargin, sizeof(p->ExchangeDeliveryMargin));
    set_struct(obj, "ReserveBalance", &p->ReserveBalance, sizeof(p->ReserveBalance));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "PreFundMortgageIn", &p->PreFundMortgageIn, sizeof(p->PreFundMortgageIn));
    set_struct(obj, "PreFundMortgageOut", &p->PreFundMortgageOut, sizeof(p->PreFundMortgageOut));
    set_struct(obj, "FundMortgageIn", &p->FundMortgageIn, sizeof(p->FundMortgageIn));
    set_struct(obj, "FundMortgageOut", &p->FundMortgageOut, sizeof(p->FundMortgageOut));
    set_struct(obj, "FundMortgageAvailable", &p->FundMortgageAvailable, sizeof(p->FundMortgageAvailable));
    set_struct(obj, "MortgageableFund", &p->MortgageableFund, sizeof(p->MortgageableFund));
    set_struct(obj, "SpecProductMargin", &p->SpecProductMargin, sizeof(p->SpecProductMargin));
    set_struct(obj, "SpecProductFrozenMargin", &p->SpecProductFrozenMargin, sizeof(p->SpecProductFrozenMargin));
    set_struct(obj, "SpecProductCommission", &p->SpecProductCommission, sizeof(p->SpecProductCommission));
    set_struct(obj, "SpecProductFrozenCommission", &p->SpecProductFrozenCommission, sizeof(p->SpecProductFrozenCommission));
    set_struct(obj, "SpecProductPositionProfit", &p->SpecProductPositionProfit, sizeof(p->SpecProductPositionProfit));
    set_struct(obj, "SpecProductCloseProfit", &p->SpecProductCloseProfit, sizeof(p->SpecProductCloseProfit));
    set_struct(obj, "SpecProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg, sizeof(p->SpecProductPositionProfitByAlg));
    set_struct(obj, "SpecProductExchangeMargin", &p->SpecProductExchangeMargin, sizeof(p->SpecProductExchangeMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorPositionField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "PosiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "PositionDate", &p->PositionDate, sizeof(p->PositionDate));
    set_struct(obj, "YdPosition", &p->YdPosition, sizeof(p->YdPosition));
    set_struct(obj, "Position", &p->Position, sizeof(p->Position));
    set_struct(obj, "LongFrozen", &p->LongFrozen, sizeof(p->LongFrozen));
    set_struct(obj, "ShortFrozen", &p->ShortFrozen, sizeof(p->ShortFrozen));
    set_struct(obj, "LongFrozenAmount", &p->LongFrozenAmount, sizeof(p->LongFrozenAmount));
    set_struct(obj, "ShortFrozenAmount", &p->ShortFrozenAmount, sizeof(p->ShortFrozenAmount));
    set_struct(obj, "OpenVolume", &p->OpenVolume, sizeof(p->OpenVolume));
    set_struct(obj, "CloseVolume", &p->CloseVolume, sizeof(p->CloseVolume));
    set_struct(obj, "OpenAmount", &p->OpenAmount, sizeof(p->OpenAmount));
    set_struct(obj, "CloseAmount", &p->CloseAmount, sizeof(p->CloseAmount));
    set_struct(obj, "PositionCost", &p->PositionCost, sizeof(p->PositionCost));
    set_struct(obj, "PreMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "UseMargin", &p->UseMargin, sizeof(p->UseMargin));
    set_struct(obj, "FrozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "FrozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "FrozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "CashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "Commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "CloseProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "PositionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "PreSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "SettlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "OpenCost", &p->OpenCost, sizeof(p->OpenCost));
    set_struct(obj, "ExchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "CombPosition", &p->CombPosition, sizeof(p->CombPosition));
    set_struct(obj, "CombLongFrozen", &p->CombLongFrozen, sizeof(p->CombLongFrozen));
    set_struct(obj, "CombShortFrozen", &p->CombShortFrozen, sizeof(p->CombShortFrozen));
    set_struct(obj, "CloseProfitByDate", &p->CloseProfitByDate, sizeof(p->CloseProfitByDate));
    set_struct(obj, "CloseProfitByTrade", &p->CloseProfitByTrade, sizeof(p->CloseProfitByTrade));
    set_struct(obj, "TodayPosition", &p->TodayPosition, sizeof(p->TodayPosition));
    set_struct(obj, "MarginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "MarginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "StrikeFrozen", &p->StrikeFrozen, sizeof(p->StrikeFrozen));
    set_struct(obj, "StrikeFrozenAmount", &p->StrikeFrozenAmount, sizeof(p->StrikeFrozenAmount));
    set_struct(obj, "AbandonFrozen", &p->AbandonFrozen, sizeof(p->AbandonFrozen));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentMarginRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "IsRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentCommissionRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OpenRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "OpenRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "CloseRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "CloseRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcDepthMarketDataField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "LastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "PreSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "PreClosePrice", &p->PreClosePrice, sizeof(p->PreClosePrice));
    set_struct(obj, "PreOpenInterest", &p->PreOpenInterest, sizeof(p->PreOpenInterest));
    set_struct(obj, "OpenPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "HighestPrice", &p->HighestPrice, sizeof(p->HighestPrice));
    set_struct(obj, "LowestPrice", &p->LowestPrice, sizeof(p->LowestPrice));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "Turnover", &p->Turnover, sizeof(p->Turnover));
    set_struct(obj, "OpenInterest", &p->OpenInterest, sizeof(p->OpenInterest));
    set_struct(obj, "ClosePrice", &p->ClosePrice, sizeof(p->ClosePrice));
    set_struct(obj, "SettlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "UpperLimitPrice", &p->UpperLimitPrice, sizeof(p->UpperLimitPrice));
    set_struct(obj, "LowerLimitPrice", &p->LowerLimitPrice, sizeof(p->LowerLimitPrice));
    set_struct(obj, "PreDelta", &p->PreDelta, sizeof(p->PreDelta));
    set_struct(obj, "CurrDelta", &p->CurrDelta, sizeof(p->CurrDelta));
    set_struct(obj, "UpdateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "UpdateMillisec", &p->UpdateMillisec, sizeof(p->UpdateMillisec));
    set_struct(obj, "BidPrice1", &p->BidPrice1, sizeof(p->BidPrice1));
    set_struct(obj, "BidVolume1", &p->BidVolume1, sizeof(p->BidVolume1));
    set_struct(obj, "AskPrice1", &p->AskPrice1, sizeof(p->AskPrice1));
    set_struct(obj, "AskVolume1", &p->AskVolume1, sizeof(p->AskVolume1));
    set_struct(obj, "BidPrice2", &p->BidPrice2, sizeof(p->BidPrice2));
    set_struct(obj, "BidVolume2", &p->BidVolume2, sizeof(p->BidVolume2));
    set_struct(obj, "AskPrice2", &p->AskPrice2, sizeof(p->AskPrice2));
    set_struct(obj, "AskVolume2", &p->AskVolume2, sizeof(p->AskVolume2));
    set_struct(obj, "BidPrice3", &p->BidPrice3, sizeof(p->BidPrice3));
    set_struct(obj, "BidVolume3", &p->BidVolume3, sizeof(p->BidVolume3));
    set_struct(obj, "AskPrice3", &p->AskPrice3, sizeof(p->AskPrice3));
    set_struct(obj, "AskVolume3", &p->AskVolume3, sizeof(p->AskVolume3));
    set_struct(obj, "BidPrice4", &p->BidPrice4, sizeof(p->BidPrice4));
    set_struct(obj, "BidVolume4", &p->BidVolume4, sizeof(p->BidVolume4));
    set_struct(obj, "AskPrice4", &p->AskPrice4, sizeof(p->AskPrice4));
    set_struct(obj, "AskVolume4", &p->AskVolume4, sizeof(p->AskVolume4));
    set_struct(obj, "BidPrice5", &p->BidPrice5, sizeof(p->BidPrice5));
    set_struct(obj, "BidVolume5", &p->BidVolume5, sizeof(p->BidVolume5));
    set_struct(obj, "AskPrice5", &p->AskPrice5, sizeof(p->AskPrice5));
    set_struct(obj, "AskVolume5", &p->AskVolume5, sizeof(p->AskVolume5));
    set_struct(obj, "AveragePrice", &p->AveragePrice, sizeof(p->AveragePrice));
    set_struct(obj, "ActionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentTradingRightField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "TradingRight", &p->TradingRight, sizeof(p->TradingRight));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserName", &p->UserName, sizeof(p->UserName));
    set_struct(obj, "UserType", &p->UserType, sizeof(p->UserType));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "IsUsingOTP", &p->IsUsingOTP, sizeof(p->IsUsingOTP));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserPasswordField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserFunctionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "BrokerFunctionCode", &p->BrokerFunctionCode, sizeof(p->BrokerFunctionCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTraderOfferField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "TraderConnectStatus", &p->TraderConnectStatus, sizeof(p->TraderConnectStatus));
    set_struct(obj, "ConnectRequestDate", &p->ConnectRequestDate, sizeof(p->ConnectRequestDate));
    set_struct(obj, "ConnectRequestTime", &p->ConnectRequestTime, sizeof(p->ConnectRequestTime));
    set_struct(obj, "LastReportDate", &p->LastReportDate, sizeof(p->LastReportDate));
    set_struct(obj, "LastReportTime", &p->LastReportTime, sizeof(p->LastReportTime));
    set_struct(obj, "ConnectDate", &p->ConnectDate, sizeof(p->ConnectDate));
    set_struct(obj, "ConnectTime", &p->ConnectTime, sizeof(p->ConnectTime));
    set_struct(obj, "StartDate", &p->StartDate, sizeof(p->StartDate));
    set_struct(obj, "StartTime", &p->StartTime, sizeof(p->StartTime));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "MaxTradeID", &p->MaxTradeID, sizeof(p->MaxTradeID));
    set_struct(obj, "MaxOrderMessageReference", &p->MaxOrderMessageReference, sizeof(p->MaxOrderMessageReference));
}
static void set_struct(Local<Object>& obj, CThostFtdcSettlementInfoField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "Content", &p->Content, sizeof(p->Content));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentMarginRateAdjustField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "IsRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeMarginRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeMarginRateAdjustField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "ExchLongMarginRatioByMoney", &p->ExchLongMarginRatioByMoney, sizeof(p->ExchLongMarginRatioByMoney));
    set_struct(obj, "ExchLongMarginRatioByVolume", &p->ExchLongMarginRatioByVolume, sizeof(p->ExchLongMarginRatioByVolume));
    set_struct(obj, "ExchShortMarginRatioByMoney", &p->ExchShortMarginRatioByMoney, sizeof(p->ExchShortMarginRatioByMoney));
    set_struct(obj, "ExchShortMarginRatioByVolume", &p->ExchShortMarginRatioByVolume, sizeof(p->ExchShortMarginRatioByVolume));
    set_struct(obj, "NoLongMarginRatioByMoney", &p->NoLongMarginRatioByMoney, sizeof(p->NoLongMarginRatioByMoney));
    set_struct(obj, "NoLongMarginRatioByVolume", &p->NoLongMarginRatioByVolume, sizeof(p->NoLongMarginRatioByVolume));
    set_struct(obj, "NoShortMarginRatioByMoney", &p->NoShortMarginRatioByMoney, sizeof(p->NoShortMarginRatioByMoney));
    set_struct(obj, "NoShortMarginRatioByVolume", &p->NoShortMarginRatioByVolume, sizeof(p->NoShortMarginRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "FromCurrencyID", &p->FromCurrencyID, sizeof(p->FromCurrencyID));
    set_struct(obj, "FromCurrencyUnit", &p->FromCurrencyUnit, sizeof(p->FromCurrencyUnit));
    set_struct(obj, "ToCurrencyID", &p->ToCurrencyID, sizeof(p->ToCurrencyID));
    set_struct(obj, "ExchangeRate", &p->ExchangeRate, sizeof(p->ExchangeRate));
}
static void set_struct(Local<Object>& obj, CThostFtdcSettlementRefField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCurrentTimeField *p)
{
    set_struct(obj, "CurrDate", &p->CurrDate, sizeof(p->CurrDate));
    set_struct(obj, "CurrTime", &p->CurrTime, sizeof(p->CurrTime));
    set_struct(obj, "CurrMillisec", &p->CurrMillisec, sizeof(p->CurrMillisec));
    set_struct(obj, "ActionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcCommPhaseField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "CommPhaseNo", &p->CommPhaseNo, sizeof(p->CommPhaseNo));
    set_struct(obj, "SystemID", &p->SystemID, sizeof(p->SystemID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLoginInfoField *p)
{
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "LoginDate", &p->LoginDate, sizeof(p->LoginDate));
    set_struct(obj, "LoginTime", &p->LoginTime, sizeof(p->LoginTime));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "InterfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "ProtocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "SystemName", &p->SystemName, sizeof(p->SystemName));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "MaxOrderRef", &p->MaxOrderRef, sizeof(p->MaxOrderRef));
    set_struct(obj, "SHFETime", &p->SHFETime, sizeof(p->SHFETime));
    set_struct(obj, "DCETime", &p->DCETime, sizeof(p->DCETime));
    set_struct(obj, "CZCETime", &p->CZCETime, sizeof(p->CZCETime));
    set_struct(obj, "FFEXTime", &p->FFEXTime, sizeof(p->FFEXTime));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "OneTimePassword", &p->OneTimePassword, sizeof(p->OneTimePassword));
    set_struct(obj, "INETime", &p->INETime, sizeof(p->INETime));
    set_struct(obj, "IsQryControl", &p->IsQryControl, sizeof(p->IsQryControl));
    set_struct(obj, "LoginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
}
static void set_struct(Local<Object>& obj, CThostFtdcLogoutAllField *p)
{
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "SystemName", &p->SystemName, sizeof(p->SystemName));
}
static void set_struct(Local<Object>& obj, CThostFtdcFrontStatusField *p)
{
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "LastReportDate", &p->LastReportDate, sizeof(p->LastReportDate));
    set_struct(obj, "LastReportTime", &p->LastReportTime, sizeof(p->LastReportTime));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserPasswordUpdateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OldPassword", &p->OldPassword, sizeof(p->OldPassword));
    set_struct(obj, "NewPassword", &p->NewPassword, sizeof(p->NewPassword));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OrderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "CombOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "CombHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "TimeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "GTDDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "VolumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "MinVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "ContingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "StopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "ForceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "IsAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "UserForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "IsSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OrderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "CombOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "CombHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "TimeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "GTDDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "VolumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "MinVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "ContingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "StopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "ForceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "IsAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "OrderSource", &p->OrderSource, sizeof(p->OrderSource));
    set_struct(obj, "OrderStatus", &p->OrderStatus, sizeof(p->OrderStatus));
    set_struct(obj, "OrderType", &p->OrderType, sizeof(p->OrderType));
    set_struct(obj, "VolumeTraded", &p->VolumeTraded, sizeof(p->VolumeTraded));
    set_struct(obj, "VolumeTotal", &p->VolumeTotal, sizeof(p->VolumeTotal));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "ActiveTime", &p->ActiveTime, sizeof(p->ActiveTime));
    set_struct(obj, "SuspendTime", &p->SuspendTime, sizeof(p->SuspendTime));
    set_struct(obj, "UpdateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "CancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "ActiveTraderID", &p->ActiveTraderID, sizeof(p->ActiveTraderID));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "UserForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "ActiveUserID", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "BrokerOrderSeq", &p->BrokerOrderSeq, sizeof(p->BrokerOrderSeq));
    set_struct(obj, "RelativeOrderSysID", &p->RelativeOrderSysID, sizeof(p->RelativeOrderSysID));
    set_struct(obj, "ZCETotalTradedVolume", &p->ZCETotalTradedVolume, sizeof(p->ZCETotalTradedVolume));
    set_struct(obj, "IsSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderField *p)
{
    set_struct(obj, "OrderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "CombOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "CombHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "TimeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "GTDDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "VolumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "MinVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "ContingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "StopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "ForceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "IsAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "OrderSource", &p->OrderSource, sizeof(p->OrderSource));
    set_struct(obj, "OrderStatus", &p->OrderStatus, sizeof(p->OrderStatus));
    set_struct(obj, "OrderType", &p->OrderType, sizeof(p->OrderType));
    set_struct(obj, "VolumeTraded", &p->VolumeTraded, sizeof(p->VolumeTraded));
    set_struct(obj, "VolumeTotal", &p->VolumeTotal, sizeof(p->VolumeTotal));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "ActiveTime", &p->ActiveTime, sizeof(p->ActiveTime));
    set_struct(obj, "SuspendTime", &p->SuspendTime, sizeof(p->SuspendTime));
    set_struct(obj, "UpdateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "CancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "ActiveTraderID", &p->ActiveTraderID, sizeof(p->ActiveTraderID));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderInsertErrorField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OrderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OrderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderActionField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderActionErrorField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeTradeField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TradeID", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "TradingRole", &p->TradingRole, sizeof(p->TradingRole));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "Price", &p->Price, sizeof(p->Price));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "TradeType", &p->TradeType, sizeof(p->TradeType));
    set_struct(obj, "PriceSource", &p->PriceSource, sizeof(p->PriceSource));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "TradeSource", &p->TradeSource, sizeof(p->TradeSource));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TradeID", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "TradingRole", &p->TradingRole, sizeof(p->TradingRole));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "Price", &p->Price, sizeof(p->Price));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "TradeType", &p->TradeType, sizeof(p->TradeType));
    set_struct(obj, "PriceSource", &p->PriceSource, sizeof(p->PriceSource));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "BrokerOrderSeq", &p->BrokerOrderSeq, sizeof(p->BrokerOrderSeq));
    set_struct(obj, "TradeSource", &p->TradeSource, sizeof(p->TradeSource));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserSessionField *p)
{
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "LoginDate", &p->LoginDate, sizeof(p->LoginDate));
    set_struct(obj, "LoginTime", &p->LoginTime, sizeof(p->LoginTime));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "InterfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "ProtocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "LoginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "MaxVolume", &p->MaxVolume, sizeof(p->MaxVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcSettlementInfoConfirmField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ConfirmDate", &p->ConfirmDate, sizeof(p->ConfirmDate));
    set_struct(obj, "ConfirmTime", &p->ConfirmTime, sizeof(p->ConfirmTime));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncDepositField *p)
{
    set_struct(obj, "DepositSeqNo", &p->DepositSeqNo, sizeof(p->DepositSeqNo));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "Deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "IsForce", &p->IsForce, sizeof(p->IsForce));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncFundMortgageField *p)
{
    set_struct(obj, "MortgageSeqNo", &p->MortgageSeqNo, sizeof(p->MortgageSeqNo));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "FromCurrencyID", &p->FromCurrencyID, sizeof(p->FromCurrencyID));
    set_struct(obj, "MortgageAmount", &p->MortgageAmount, sizeof(p->MortgageAmount));
    set_struct(obj, "ToCurrencyID", &p->ToCurrencyID, sizeof(p->ToCurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerSyncField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInvestorField *p)
{
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorGroupID", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "InvestorName", &p->InvestorName, sizeof(p->InvestorName));
    set_struct(obj, "IdentifiedCardType", &p->IdentifiedCardType, sizeof(p->IdentifiedCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "OpenDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "Mobile", &p->Mobile, sizeof(p->Mobile));
    set_struct(obj, "CommModelID", &p->CommModelID, sizeof(p->CommModelID));
    set_struct(obj, "MarginModelID", &p->MarginModelID, sizeof(p->MarginModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingTradingCodeField *p)
{
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "ClientIDType", &p->ClientIDType, sizeof(p->ClientIDType));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInvestorGroupField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorGroupID", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "InvestorGroupName", &p->InvestorGroupName, sizeof(p->InvestorGroupName));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingTradingAccountField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "PreMortgage", &p->PreMortgage, sizeof(p->PreMortgage));
    set_struct(obj, "PreCredit", &p->PreCredit, sizeof(p->PreCredit));
    set_struct(obj, "PreDeposit", &p->PreDeposit, sizeof(p->PreDeposit));
    set_struct(obj, "PreBalance", &p->PreBalance, sizeof(p->PreBalance));
    set_struct(obj, "PreMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "InterestBase", &p->InterestBase, sizeof(p->InterestBase));
    set_struct(obj, "Interest", &p->Interest, sizeof(p->Interest));
    set_struct(obj, "Deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "Withdraw", &p->Withdraw, sizeof(p->Withdraw));
    set_struct(obj, "FrozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "FrozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "FrozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "CurrMargin", &p->CurrMargin, sizeof(p->CurrMargin));
    set_struct(obj, "CashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "Commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "CloseProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "PositionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "Balance", &p->Balance, sizeof(p->Balance));
    set_struct(obj, "Available", &p->Available, sizeof(p->Available));
    set_struct(obj, "WithdrawQuota", &p->WithdrawQuota, sizeof(p->WithdrawQuota));
    set_struct(obj, "Reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "Credit", &p->Credit, sizeof(p->Credit));
    set_struct(obj, "Mortgage", &p->Mortgage, sizeof(p->Mortgage));
    set_struct(obj, "ExchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "DeliveryMargin", &p->DeliveryMargin, sizeof(p->DeliveryMargin));
    set_struct(obj, "ExchangeDeliveryMargin", &p->ExchangeDeliveryMargin, sizeof(p->ExchangeDeliveryMargin));
    set_struct(obj, "ReserveBalance", &p->ReserveBalance, sizeof(p->ReserveBalance));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "PreFundMortgageIn", &p->PreFundMortgageIn, sizeof(p->PreFundMortgageIn));
    set_struct(obj, "PreFundMortgageOut", &p->PreFundMortgageOut, sizeof(p->PreFundMortgageOut));
    set_struct(obj, "FundMortgageIn", &p->FundMortgageIn, sizeof(p->FundMortgageIn));
    set_struct(obj, "FundMortgageOut", &p->FundMortgageOut, sizeof(p->FundMortgageOut));
    set_struct(obj, "FundMortgageAvailable", &p->FundMortgageAvailable, sizeof(p->FundMortgageAvailable));
    set_struct(obj, "MortgageableFund", &p->MortgageableFund, sizeof(p->MortgageableFund));
    set_struct(obj, "SpecProductMargin", &p->SpecProductMargin, sizeof(p->SpecProductMargin));
    set_struct(obj, "SpecProductFrozenMargin", &p->SpecProductFrozenMargin, sizeof(p->SpecProductFrozenMargin));
    set_struct(obj, "SpecProductCommission", &p->SpecProductCommission, sizeof(p->SpecProductCommission));
    set_struct(obj, "SpecProductFrozenCommission", &p->SpecProductFrozenCommission, sizeof(p->SpecProductFrozenCommission));
    set_struct(obj, "SpecProductPositionProfit", &p->SpecProductPositionProfit, sizeof(p->SpecProductPositionProfit));
    set_struct(obj, "SpecProductCloseProfit", &p->SpecProductCloseProfit, sizeof(p->SpecProductCloseProfit));
    set_struct(obj, "SpecProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg, sizeof(p->SpecProductPositionProfitByAlg));
    set_struct(obj, "SpecProductExchangeMargin", &p->SpecProductExchangeMargin, sizeof(p->SpecProductExchangeMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInvestorPositionField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "PosiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "PositionDate", &p->PositionDate, sizeof(p->PositionDate));
    set_struct(obj, "YdPosition", &p->YdPosition, sizeof(p->YdPosition));
    set_struct(obj, "Position", &p->Position, sizeof(p->Position));
    set_struct(obj, "LongFrozen", &p->LongFrozen, sizeof(p->LongFrozen));
    set_struct(obj, "ShortFrozen", &p->ShortFrozen, sizeof(p->ShortFrozen));
    set_struct(obj, "LongFrozenAmount", &p->LongFrozenAmount, sizeof(p->LongFrozenAmount));
    set_struct(obj, "ShortFrozenAmount", &p->ShortFrozenAmount, sizeof(p->ShortFrozenAmount));
    set_struct(obj, "OpenVolume", &p->OpenVolume, sizeof(p->OpenVolume));
    set_struct(obj, "CloseVolume", &p->CloseVolume, sizeof(p->CloseVolume));
    set_struct(obj, "OpenAmount", &p->OpenAmount, sizeof(p->OpenAmount));
    set_struct(obj, "CloseAmount", &p->CloseAmount, sizeof(p->CloseAmount));
    set_struct(obj, "PositionCost", &p->PositionCost, sizeof(p->PositionCost));
    set_struct(obj, "PreMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "UseMargin", &p->UseMargin, sizeof(p->UseMargin));
    set_struct(obj, "FrozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "FrozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "FrozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "CashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "Commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "CloseProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "PositionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "PreSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "SettlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "OpenCost", &p->OpenCost, sizeof(p->OpenCost));
    set_struct(obj, "ExchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "CombPosition", &p->CombPosition, sizeof(p->CombPosition));
    set_struct(obj, "CombLongFrozen", &p->CombLongFrozen, sizeof(p->CombLongFrozen));
    set_struct(obj, "CombShortFrozen", &p->CombShortFrozen, sizeof(p->CombShortFrozen));
    set_struct(obj, "CloseProfitByDate", &p->CloseProfitByDate, sizeof(p->CloseProfitByDate));
    set_struct(obj, "CloseProfitByTrade", &p->CloseProfitByTrade, sizeof(p->CloseProfitByTrade));
    set_struct(obj, "TodayPosition", &p->TodayPosition, sizeof(p->TodayPosition));
    set_struct(obj, "MarginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "MarginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "StrikeFrozen", &p->StrikeFrozen, sizeof(p->StrikeFrozen));
    set_struct(obj, "StrikeFrozenAmount", &p->StrikeFrozenAmount, sizeof(p->StrikeFrozenAmount));
    set_struct(obj, "AbandonFrozen", &p->AbandonFrozen, sizeof(p->AbandonFrozen));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInstrumentMarginRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "LongMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "LongMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "ShortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "ShortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "IsRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInstrumentCommissionRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OpenRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "OpenRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "CloseRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "CloseRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInstrumentTradingRightField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "TradingRight", &p->TradingRight, sizeof(p->TradingRight));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "InsertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "InsertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TradeID", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "TradeTimeStart", &p->TradeTimeStart, sizeof(p->TradeTimeStart));
    set_struct(obj, "TradeTimeEnd", &p->TradeTimeEnd, sizeof(p->TradeTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorPositionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradingAccountField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradingCodeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ClientIDType", &p->ClientIDType, sizeof(p->ClientIDType));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorGroupField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentMarginRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentCommissionRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentTradingRightField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTraderField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySuperUserFunctionField *p)
{
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryUserSessionField *p)
{
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryPartBrokerField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryFrontStatusField *p)
{
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeOrderField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeOrderActionField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySuperUserField *p)
{
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryProductField *p)
{
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "ProductClass", &p->ProductClass, sizeof(p->ProductClass));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryDepthMarketDataField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerUserField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerUserFunctionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTraderOfferField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySyncDepositField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "DepositSeqNo", &p->DepositSeqNo, sizeof(p->DepositSeqNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySettlementInfoField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeMarginRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeMarginRateAdjustField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "FromCurrencyID", &p->FromCurrencyID, sizeof(p->FromCurrencyID));
    set_struct(obj, "ToCurrencyID", &p->ToCurrencyID, sizeof(p->ToCurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySyncFundMortgageField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "MortgageSeqNo", &p->MortgageSeqNo, sizeof(p->MortgageSeqNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryHisOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "InsertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "InsertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrMiniMarginField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "MinMargin", &p->MinMargin, sizeof(p->MinMargin));
    set_struct(obj, "ValueMethod", &p->ValueMethod, sizeof(p->ValueMethod));
    set_struct(obj, "IsRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrMarginAdjustField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "SShortMarginRatioByMoney", &p->SShortMarginRatioByMoney, sizeof(p->SShortMarginRatioByMoney));
    set_struct(obj, "SShortMarginRatioByVolume", &p->SShortMarginRatioByVolume, sizeof(p->SShortMarginRatioByVolume));
    set_struct(obj, "HShortMarginRatioByMoney", &p->HShortMarginRatioByMoney, sizeof(p->HShortMarginRatioByMoney));
    set_struct(obj, "HShortMarginRatioByVolume", &p->HShortMarginRatioByVolume, sizeof(p->HShortMarginRatioByVolume));
    set_struct(obj, "AShortMarginRatioByMoney", &p->AShortMarginRatioByMoney, sizeof(p->AShortMarginRatioByMoney));
    set_struct(obj, "AShortMarginRatioByVolume", &p->AShortMarginRatioByVolume, sizeof(p->AShortMarginRatioByVolume));
    set_struct(obj, "IsRelative", &p->IsRelative, sizeof(p->IsRelative));
    set_struct(obj, "MShortMarginRatioByMoney", &p->MShortMarginRatioByMoney, sizeof(p->MShortMarginRatioByMoney));
    set_struct(obj, "MShortMarginRatioByVolume", &p->MShortMarginRatioByVolume, sizeof(p->MShortMarginRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrCommRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OpenRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "OpenRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "CloseRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "CloseRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
    set_struct(obj, "StrikeRatioByMoney", &p->StrikeRatioByMoney, sizeof(p->StrikeRatioByMoney));
    set_struct(obj, "StrikeRatioByVolume", &p->StrikeRatioByVolume, sizeof(p->StrikeRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrTradeCostField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "FixedMargin", &p->FixedMargin, sizeof(p->FixedMargin));
    set_struct(obj, "MiniMargin", &p->MiniMargin, sizeof(p->MiniMargin));
    set_struct(obj, "Royalty", &p->Royalty, sizeof(p->Royalty));
    set_struct(obj, "ExchFixedMargin", &p->ExchFixedMargin, sizeof(p->ExchFixedMargin));
    set_struct(obj, "ExchMiniMargin", &p->ExchMiniMargin, sizeof(p->ExchMiniMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOptionInstrTradeCostField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "InputPrice", &p->InputPrice, sizeof(p->InputPrice));
    set_struct(obj, "UnderlyingPrice", &p->UnderlyingPrice, sizeof(p->UnderlyingPrice));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOptionInstrCommRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcIndexPriceField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ClosePrice", &p->ClosePrice, sizeof(p->ClosePrice));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputExecOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExecOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "ActionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "PosiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "ReservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "CloseFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputExecOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExecOrderActionRef", &p->ExecOrderActionRef, sizeof(p->ExecOrderActionRef));
    set_struct(obj, "ExecOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExecOrderSysID", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExecOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExecOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "ActionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "PosiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "ReservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "CloseFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "ExecOrderLocalID", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "ExecOrderSysID", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "CancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "ExecResult", &p->ExecResult, sizeof(p->ExecResult));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "ActiveUserID", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "BrokerExecOrderSeq", &p->BrokerExecOrderSeq, sizeof(p->BrokerExecOrderSeq));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExecOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExecOrderActionRef", &p->ExecOrderActionRef, sizeof(p->ExecOrderActionRef));
    set_struct(obj, "ExecOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExecOrderSysID", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "ExecOrderLocalID", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "ActionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExecOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExecOrderSysID", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "InsertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "InsertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeExecOrderField *p)
{
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "ActionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "PosiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "ReservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "CloseFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "ExecOrderLocalID", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "ExecOrderSysID", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "CancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "ExecResult", &p->ExecResult, sizeof(p->ExecResult));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeExecOrderField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExecOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeExecOrderActionField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExecOrderSysID", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "ExecOrderLocalID", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "ActionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeExecOrderActionField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrExecOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExecOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "ActionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "PosiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "ReservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "CloseFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrExecOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrExecOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExecOrderActionRef", &p->ExecOrderActionRef, sizeof(p->ExecOrderActionRef));
    set_struct(obj, "ExecOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExecOrderSysID", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrExecOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrTradingRightField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "TradingRight", &p->TradingRight, sizeof(p->TradingRight));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOptionInstrTradingRightField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputForQuoteField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ForQuoteRef", &p->ForQuoteRef, sizeof(p->ForQuoteRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcForQuoteField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ForQuoteRef", &p->ForQuoteRef, sizeof(p->ForQuoteRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "ForQuoteLocalID", &p->ForQuoteLocalID, sizeof(p->ForQuoteLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "ForQuoteStatus", &p->ForQuoteStatus, sizeof(p->ForQuoteStatus));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "ActiveUserID", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "BrokerForQutoSeq", &p->BrokerForQutoSeq, sizeof(p->BrokerForQutoSeq));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryForQuoteField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InsertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "InsertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeForQuoteField *p)
{
    set_struct(obj, "ForQuoteLocalID", &p->ForQuoteLocalID, sizeof(p->ForQuoteLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "ForQuoteStatus", &p->ForQuoteStatus, sizeof(p->ForQuoteStatus));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeForQuoteField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputQuoteField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "QuoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "AskPrice", &p->AskPrice, sizeof(p->AskPrice));
    set_struct(obj, "BidPrice", &p->BidPrice, sizeof(p->BidPrice));
    set_struct(obj, "AskVolume", &p->AskVolume, sizeof(p->AskVolume));
    set_struct(obj, "BidVolume", &p->BidVolume, sizeof(p->BidVolume));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "AskOffsetFlag", &p->AskOffsetFlag, sizeof(p->AskOffsetFlag));
    set_struct(obj, "BidOffsetFlag", &p->BidOffsetFlag, sizeof(p->BidOffsetFlag));
    set_struct(obj, "AskHedgeFlag", &p->AskHedgeFlag, sizeof(p->AskHedgeFlag));
    set_struct(obj, "BidHedgeFlag", &p->BidHedgeFlag, sizeof(p->BidHedgeFlag));
    set_struct(obj, "AskOrderRef", &p->AskOrderRef, sizeof(p->AskOrderRef));
    set_struct(obj, "BidOrderRef", &p->BidOrderRef, sizeof(p->BidOrderRef));
    set_struct(obj, "ForQuoteSysID", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputQuoteActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "QuoteActionRef", &p->QuoteActionRef, sizeof(p->QuoteActionRef));
    set_struct(obj, "QuoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "QuoteSysID", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQuoteField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "QuoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "AskPrice", &p->AskPrice, sizeof(p->AskPrice));
    set_struct(obj, "BidPrice", &p->BidPrice, sizeof(p->BidPrice));
    set_struct(obj, "AskVolume", &p->AskVolume, sizeof(p->AskVolume));
    set_struct(obj, "BidVolume", &p->BidVolume, sizeof(p->BidVolume));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "AskOffsetFlag", &p->AskOffsetFlag, sizeof(p->AskOffsetFlag));
    set_struct(obj, "BidOffsetFlag", &p->BidOffsetFlag, sizeof(p->BidOffsetFlag));
    set_struct(obj, "AskHedgeFlag", &p->AskHedgeFlag, sizeof(p->AskHedgeFlag));
    set_struct(obj, "BidHedgeFlag", &p->BidHedgeFlag, sizeof(p->BidHedgeFlag));
    set_struct(obj, "QuoteLocalID", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "OrderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "QuoteSysID", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "CancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "QuoteStatus", &p->QuoteStatus, sizeof(p->QuoteStatus));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "AskOrderSysID", &p->AskOrderSysID, sizeof(p->AskOrderSysID));
    set_struct(obj, "BidOrderSysID", &p->BidOrderSysID, sizeof(p->BidOrderSysID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "ActiveUserID", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "BrokerQuoteSeq", &p->BrokerQuoteSeq, sizeof(p->BrokerQuoteSeq));
    set_struct(obj, "AskOrderRef", &p->AskOrderRef, sizeof(p->AskOrderRef));
    set_struct(obj, "BidOrderRef", &p->BidOrderRef, sizeof(p->BidOrderRef));
    set_struct(obj, "ForQuoteSysID", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQuoteActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "QuoteActionRef", &p->QuoteActionRef, sizeof(p->QuoteActionRef));
    set_struct(obj, "QuoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "QuoteSysID", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "QuoteLocalID", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryQuoteField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "QuoteSysID", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "InsertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "InsertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeQuoteField *p)
{
    set_struct(obj, "AskPrice", &p->AskPrice, sizeof(p->AskPrice));
    set_struct(obj, "BidPrice", &p->BidPrice, sizeof(p->BidPrice));
    set_struct(obj, "AskVolume", &p->AskVolume, sizeof(p->AskVolume));
    set_struct(obj, "BidVolume", &p->BidVolume, sizeof(p->BidVolume));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "AskOffsetFlag", &p->AskOffsetFlag, sizeof(p->AskOffsetFlag));
    set_struct(obj, "BidOffsetFlag", &p->BidOffsetFlag, sizeof(p->BidOffsetFlag));
    set_struct(obj, "AskHedgeFlag", &p->AskHedgeFlag, sizeof(p->AskHedgeFlag));
    set_struct(obj, "BidHedgeFlag", &p->BidHedgeFlag, sizeof(p->BidHedgeFlag));
    set_struct(obj, "QuoteLocalID", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "OrderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "QuoteSysID", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "CancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "QuoteStatus", &p->QuoteStatus, sizeof(p->QuoteStatus));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "AskOrderSysID", &p->AskOrderSysID, sizeof(p->AskOrderSysID));
    set_struct(obj, "BidOrderSysID", &p->BidOrderSysID, sizeof(p->BidOrderSysID));
    set_struct(obj, "ForQuoteSysID", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeQuoteField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryQuoteActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeQuoteActionField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "QuoteSysID", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "QuoteLocalID", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeQuoteActionField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrDeltaField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "Delta", &p->Delta, sizeof(p->Delta));
}
static void set_struct(Local<Object>& obj, CThostFtdcForQuoteRspField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ForQuoteSysID", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "ForQuoteTime", &p->ForQuoteTime, sizeof(p->ForQuoteTime));
    set_struct(obj, "ActionDay", &p->ActionDay, sizeof(p->ActionDay));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcStrikeOffsetField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "Offset", &p->Offset, sizeof(p->Offset));
    set_struct(obj, "OffsetType", &p->OffsetType, sizeof(p->OffsetType));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryStrikeOffsetField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputBatchOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OrderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcBatchOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OrderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeBatchOrderActionField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBatchOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCombInstrumentGuardField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "GuarantRatio", &p->GuarantRatio, sizeof(p->GuarantRatio));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCombInstrumentGuardField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputCombActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "CombActionRef", &p->CombActionRef, sizeof(p->CombActionRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "CombDirection", &p->CombDirection, sizeof(p->CombDirection));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcCombActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "CombActionRef", &p->CombActionRef, sizeof(p->CombActionRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "CombDirection", &p->CombDirection, sizeof(p->CombDirection));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "ActionStatus", &p->ActionStatus, sizeof(p->ActionStatus));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCombActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeCombActionField *p)
{
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "CombDirection", &p->CombDirection, sizeof(p->CombDirection));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "ActionStatus", &p->ActionStatus, sizeof(p->ActionStatus));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeCombActionField *p)
{
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcProductExchRateField *p)
{
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "QuoteCurrencyID", &p->QuoteCurrencyID, sizeof(p->QuoteCurrencyID));
    set_struct(obj, "ExchangeRate", &p->ExchangeRate, sizeof(p->ExchangeRate));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryProductExchRateField *p)
{
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryForQuoteParamField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcForQuoteParamField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "LastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "PriceInterval", &p->PriceInterval, sizeof(p->PriceInterval));
}
static void set_struct(Local<Object>& obj, CThostFtdcMMOptionInstrCommRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OpenRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "OpenRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "CloseRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "CloseRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
    set_struct(obj, "StrikeRatioByMoney", &p->StrikeRatioByMoney, sizeof(p->StrikeRatioByMoney));
    set_struct(obj, "StrikeRatioByVolume", &p->StrikeRatioByVolume, sizeof(p->StrikeRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMMOptionInstrCommRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMMInstrumentCommissionRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OpenRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "OpenRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "CloseRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "CloseRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "CloseTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "CloseTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMMInstrumentCommissionRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentOrderCommRateField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "OrderCommByVolume", &p->OrderCommByVolume, sizeof(p->OrderCommByVolume));
    set_struct(obj, "OrderActionCommByVolume", &p->OrderActionCommByVolume, sizeof(p->OrderActionCommByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentOrderCommRateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "LastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "PreSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "PreClosePrice", &p->PreClosePrice, sizeof(p->PreClosePrice));
    set_struct(obj, "PreOpenInterest", &p->PreOpenInterest, sizeof(p->PreOpenInterest));
    set_struct(obj, "OpenPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "HighestPrice", &p->HighestPrice, sizeof(p->HighestPrice));
    set_struct(obj, "LowestPrice", &p->LowestPrice, sizeof(p->LowestPrice));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "Turnover", &p->Turnover, sizeof(p->Turnover));
    set_struct(obj, "OpenInterest", &p->OpenInterest, sizeof(p->OpenInterest));
    set_struct(obj, "ClosePrice", &p->ClosePrice, sizeof(p->ClosePrice));
    set_struct(obj, "SettlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "UpperLimitPrice", &p->UpperLimitPrice, sizeof(p->UpperLimitPrice));
    set_struct(obj, "LowerLimitPrice", &p->LowerLimitPrice, sizeof(p->LowerLimitPrice));
    set_struct(obj, "PreDelta", &p->PreDelta, sizeof(p->PreDelta));
    set_struct(obj, "CurrDelta", &p->CurrDelta, sizeof(p->CurrDelta));
    set_struct(obj, "UpdateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "UpdateMillisec", &p->UpdateMillisec, sizeof(p->UpdateMillisec));
    set_struct(obj, "ActionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBaseField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PreSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "PreClosePrice", &p->PreClosePrice, sizeof(p->PreClosePrice));
    set_struct(obj, "PreOpenInterest", &p->PreOpenInterest, sizeof(p->PreOpenInterest));
    set_struct(obj, "PreDelta", &p->PreDelta, sizeof(p->PreDelta));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataStaticField *p)
{
    set_struct(obj, "OpenPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "HighestPrice", &p->HighestPrice, sizeof(p->HighestPrice));
    set_struct(obj, "LowestPrice", &p->LowestPrice, sizeof(p->LowestPrice));
    set_struct(obj, "ClosePrice", &p->ClosePrice, sizeof(p->ClosePrice));
    set_struct(obj, "UpperLimitPrice", &p->UpperLimitPrice, sizeof(p->UpperLimitPrice));
    set_struct(obj, "LowerLimitPrice", &p->LowerLimitPrice, sizeof(p->LowerLimitPrice));
    set_struct(obj, "SettlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "CurrDelta", &p->CurrDelta, sizeof(p->CurrDelta));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataLastMatchField *p)
{
    set_struct(obj, "LastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "Turnover", &p->Turnover, sizeof(p->Turnover));
    set_struct(obj, "OpenInterest", &p->OpenInterest, sizeof(p->OpenInterest));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBestPriceField *p)
{
    set_struct(obj, "BidPrice1", &p->BidPrice1, sizeof(p->BidPrice1));
    set_struct(obj, "BidVolume1", &p->BidVolume1, sizeof(p->BidVolume1));
    set_struct(obj, "AskPrice1", &p->AskPrice1, sizeof(p->AskPrice1));
    set_struct(obj, "AskVolume1", &p->AskVolume1, sizeof(p->AskVolume1));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBid23Field *p)
{
    set_struct(obj, "BidPrice2", &p->BidPrice2, sizeof(p->BidPrice2));
    set_struct(obj, "BidVolume2", &p->BidVolume2, sizeof(p->BidVolume2));
    set_struct(obj, "BidPrice3", &p->BidPrice3, sizeof(p->BidPrice3));
    set_struct(obj, "BidVolume3", &p->BidVolume3, sizeof(p->BidVolume3));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataAsk23Field *p)
{
    set_struct(obj, "AskPrice2", &p->AskPrice2, sizeof(p->AskPrice2));
    set_struct(obj, "AskVolume2", &p->AskVolume2, sizeof(p->AskVolume2));
    set_struct(obj, "AskPrice3", &p->AskPrice3, sizeof(p->AskPrice3));
    set_struct(obj, "AskVolume3", &p->AskVolume3, sizeof(p->AskVolume3));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBid45Field *p)
{
    set_struct(obj, "BidPrice4", &p->BidPrice4, sizeof(p->BidPrice4));
    set_struct(obj, "BidVolume4", &p->BidVolume4, sizeof(p->BidVolume4));
    set_struct(obj, "BidPrice5", &p->BidPrice5, sizeof(p->BidPrice5));
    set_struct(obj, "BidVolume5", &p->BidVolume5, sizeof(p->BidVolume5));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataAsk45Field *p)
{
    set_struct(obj, "AskPrice4", &p->AskPrice4, sizeof(p->AskPrice4));
    set_struct(obj, "AskVolume4", &p->AskVolume4, sizeof(p->AskVolume4));
    set_struct(obj, "AskPrice5", &p->AskPrice5, sizeof(p->AskPrice5));
    set_struct(obj, "AskVolume5", &p->AskVolume5, sizeof(p->AskVolume5));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataUpdateTimeField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "UpdateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "UpdateMillisec", &p->UpdateMillisec, sizeof(p->UpdateMillisec));
    set_struct(obj, "ActionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataExchangeField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSpecificInstrumentField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentStatusField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "SettlementGroupID", &p->SettlementGroupID, sizeof(p->SettlementGroupID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "InstrumentStatus", &p->InstrumentStatus, sizeof(p->InstrumentStatus));
    set_struct(obj, "TradingSegmentSN", &p->TradingSegmentSN, sizeof(p->TradingSegmentSN));
    set_struct(obj, "EnterTime", &p->EnterTime, sizeof(p->EnterTime));
    set_struct(obj, "EnterReason", &p->EnterReason, sizeof(p->EnterReason));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentStatusField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorAccountField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcPositionProfitAlgorithmField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Algorithm", &p->Algorithm, sizeof(p->Algorithm));
    set_struct(obj, "Memo", &p->Memo, sizeof(p->Memo));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcDiscountField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "Discount", &p->Discount, sizeof(p->Discount));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTransferBankField *p)
{
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBrchID", &p->BankBrchID, sizeof(p->BankBrchID));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferBankField *p)
{
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBrchID", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "BankName", &p->BankName, sizeof(p->BankName));
    set_struct(obj, "IsActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorPositionDetailField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorPositionDetailField *p)
{
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "OpenDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "TradeID", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "OpenPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "TradeType", &p->TradeType, sizeof(p->TradeType));
    set_struct(obj, "CombInstrumentID", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "CloseProfitByDate", &p->CloseProfitByDate, sizeof(p->CloseProfitByDate));
    set_struct(obj, "CloseProfitByTrade", &p->CloseProfitByTrade, sizeof(p->CloseProfitByTrade));
    set_struct(obj, "PositionProfitByDate", &p->PositionProfitByDate, sizeof(p->PositionProfitByDate));
    set_struct(obj, "PositionProfitByTrade", &p->PositionProfitByTrade, sizeof(p->PositionProfitByTrade));
    set_struct(obj, "Margin", &p->Margin, sizeof(p->Margin));
    set_struct(obj, "ExchMargin", &p->ExchMargin, sizeof(p->ExchMargin));
    set_struct(obj, "MarginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "MarginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "LastSettlementPrice", &p->LastSettlementPrice, sizeof(p->LastSettlementPrice));
    set_struct(obj, "SettlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "CloseVolume", &p->CloseVolume, sizeof(p->CloseVolume));
    set_struct(obj, "CloseAmount", &p->CloseAmount, sizeof(p->CloseAmount));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountPasswordField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMDTraderOfferField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "TraderConnectStatus", &p->TraderConnectStatus, sizeof(p->TraderConnectStatus));
    set_struct(obj, "ConnectRequestDate", &p->ConnectRequestDate, sizeof(p->ConnectRequestDate));
    set_struct(obj, "ConnectRequestTime", &p->ConnectRequestTime, sizeof(p->ConnectRequestTime));
    set_struct(obj, "LastReportDate", &p->LastReportDate, sizeof(p->LastReportDate));
    set_struct(obj, "LastReportTime", &p->LastReportTime, sizeof(p->LastReportTime));
    set_struct(obj, "ConnectDate", &p->ConnectDate, sizeof(p->ConnectDate));
    set_struct(obj, "ConnectTime", &p->ConnectTime, sizeof(p->ConnectTime));
    set_struct(obj, "StartDate", &p->StartDate, sizeof(p->StartDate));
    set_struct(obj, "StartTime", &p->StartTime, sizeof(p->StartTime));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "MaxTradeID", &p->MaxTradeID, sizeof(p->MaxTradeID));
    set_struct(obj, "MaxOrderMessageReference", &p->MaxOrderMessageReference, sizeof(p->MaxOrderMessageReference));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMDTraderOfferField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryNoticeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcNoticeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "Content", &p->Content, sizeof(p->Content));
    set_struct(obj, "SequenceLabel", &p->SequenceLabel, sizeof(p->SequenceLabel));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserRightField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserRightType", &p->UserRightType, sizeof(p->UserRightType));
    set_struct(obj, "IsForbidden", &p->IsForbidden, sizeof(p->IsForbidden));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySettlementInfoConfirmField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLoadSettlementInfoField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerWithdrawAlgorithmField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "WithdrawAlgorithm", &p->WithdrawAlgorithm, sizeof(p->WithdrawAlgorithm));
    set_struct(obj, "UsingRatio", &p->UsingRatio, sizeof(p->UsingRatio));
    set_struct(obj, "IncludeCloseProfit", &p->IncludeCloseProfit, sizeof(p->IncludeCloseProfit));
    set_struct(obj, "AllWithoutTrade", &p->AllWithoutTrade, sizeof(p->AllWithoutTrade));
    set_struct(obj, "AvailIncludeCloseProfit", &p->AvailIncludeCloseProfit, sizeof(p->AvailIncludeCloseProfit));
    set_struct(obj, "IsBrokerUserEvent", &p->IsBrokerUserEvent, sizeof(p->IsBrokerUserEvent));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "FundMortgageRatio", &p->FundMortgageRatio, sizeof(p->FundMortgageRatio));
    set_struct(obj, "BalanceAlgorithm", &p->BalanceAlgorithm, sizeof(p->BalanceAlgorithm));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateV1Field *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OldPassword", &p->OldPassword, sizeof(p->OldPassword));
    set_struct(obj, "NewPassword", &p->NewPassword, sizeof(p->NewPassword));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "OldPassword", &p->OldPassword, sizeof(p->OldPassword));
    set_struct(obj, "NewPassword", &p->NewPassword, sizeof(p->NewPassword));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCombinationLegField *p)
{
    set_struct(obj, "CombInstrumentID", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "LegID", &p->LegID, sizeof(p->LegID));
    set_struct(obj, "LegInstrumentID", &p->LegInstrumentID, sizeof(p->LegInstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySyncStatusField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcCombinationLegField *p)
{
    set_struct(obj, "CombInstrumentID", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "LegID", &p->LegID, sizeof(p->LegID));
    set_struct(obj, "LegInstrumentID", &p->LegInstrumentID, sizeof(p->LegInstrumentID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "LegMultiple", &p->LegMultiple, sizeof(p->LegMultiple));
    set_struct(obj, "ImplyLevel", &p->ImplyLevel, sizeof(p->ImplyLevel));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncStatusField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "DataSyncStatus", &p->DataSyncStatus, sizeof(p->DataSyncStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryLinkManField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLinkManField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "PersonType", &p->PersonType, sizeof(p->PersonType));
    set_struct(obj, "IdentifiedCardType", &p->IdentifiedCardType, sizeof(p->IdentifiedCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "PersonName", &p->PersonName, sizeof(p->PersonName));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Priority", &p->Priority, sizeof(p->Priority));
    set_struct(obj, "UOAZipCode", &p->UOAZipCode, sizeof(p->UOAZipCode));
    set_struct(obj, "PersonFullName", &p->PersonFullName, sizeof(p->PersonFullName));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerUserEventField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserEventType", &p->UserEventType, sizeof(p->UserEventType));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserEventField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "UserEventType", &p->UserEventType, sizeof(p->UserEventType));
    set_struct(obj, "EventSequenceNo", &p->EventSequenceNo, sizeof(p->EventSequenceNo));
    set_struct(obj, "EventDate", &p->EventDate, sizeof(p->EventDate));
    set_struct(obj, "EventTime", &p->EventTime, sizeof(p->EventTime));
    set_struct(obj, "UserEventInfo", &p->UserEventInfo, sizeof(p->UserEventInfo));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryContractBankField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBrchID", &p->BankBrchID, sizeof(p->BankBrchID));
}
static void set_struct(Local<Object>& obj, CThostFtdcContractBankField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBrchID", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "BankName", &p->BankName, sizeof(p->BankName));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorPositionCombineDetailField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "OpenDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ComTradeID", &p->ComTradeID, sizeof(p->ComTradeID));
    set_struct(obj, "TradeID", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "TotalAmt", &p->TotalAmt, sizeof(p->TotalAmt));
    set_struct(obj, "Margin", &p->Margin, sizeof(p->Margin));
    set_struct(obj, "ExchMargin", &p->ExchMargin, sizeof(p->ExchMargin));
    set_struct(obj, "MarginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "MarginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "LegID", &p->LegID, sizeof(p->LegID));
    set_struct(obj, "LegMultiple", &p->LegMultiple, sizeof(p->LegMultiple));
    set_struct(obj, "CombInstrumentID", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "TradeGroupID", &p->TradeGroupID, sizeof(p->TradeGroupID));
}
static void set_struct(Local<Object>& obj, CThostFtdcParkedOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OrderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "CombOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "CombHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "TimeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "GTDDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "VolumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "MinVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "ContingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "StopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "ForceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "IsAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "UserForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParkedOrderID", &p->ParkedOrderID, sizeof(p->ParkedOrderID));
    set_struct(obj, "UserType", &p->UserType, sizeof(p->UserType));
    set_struct(obj, "Status", &p->Status, sizeof(p->Status));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "IsSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcParkedOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OrderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ParkedOrderActionID", &p->ParkedOrderActionID, sizeof(p->ParkedOrderActionID));
    set_struct(obj, "UserType", &p->UserType, sizeof(p->UserType));
    set_struct(obj, "Status", &p->Status, sizeof(p->Status));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryParkedOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryParkedOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRemoveParkedOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ParkedOrderID", &p->ParkedOrderID, sizeof(p->ParkedOrderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRemoveParkedOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ParkedOrderActionID", &p->ParkedOrderActionID, sizeof(p->ParkedOrderActionID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorWithdrawAlgorithmField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "UsingRatio", &p->UsingRatio, sizeof(p->UsingRatio));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "FundMortgageRatio", &p->FundMortgageRatio, sizeof(p->FundMortgageRatio));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorPositionCombineDetailField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "CombInstrumentID", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataAveragePriceField *p)
{
    set_struct(obj, "AveragePrice", &p->AveragePrice, sizeof(p->AveragePrice));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyInvestorPasswordField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserIPField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "IPMask", &p->IPMask, sizeof(p->IPMask));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingNoticeInfoField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "SendTime", &p->SendTime, sizeof(p->SendTime));
    set_struct(obj, "FieldContent", &p->FieldContent, sizeof(p->FieldContent));
    set_struct(obj, "SequenceSeries", &p->SequenceSeries, sizeof(p->SequenceSeries));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingNoticeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "SequenceSeries", &p->SequenceSeries, sizeof(p->SequenceSeries));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "SendTime", &p->SendTime, sizeof(p->SendTime));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "FieldContent", &p->FieldContent, sizeof(p->FieldContent));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradingNoticeField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OrderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "CombOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "CombHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "TimeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "GTDDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "VolumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "MinVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "ContingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "StopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "ForceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "IsAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "UserForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "IsSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrorConditionalOrderField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OrderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "CombOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "CombHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "TimeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "GTDDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "VolumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "MinVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "ContingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "StopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "ForceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "IsAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "ExchangeInstID", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "NotifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "OrderSource", &p->OrderSource, sizeof(p->OrderSource));
    set_struct(obj, "OrderStatus", &p->OrderStatus, sizeof(p->OrderStatus));
    set_struct(obj, "OrderType", &p->OrderType, sizeof(p->OrderType));
    set_struct(obj, "VolumeTraded", &p->VolumeTraded, sizeof(p->VolumeTraded));
    set_struct(obj, "VolumeTotal", &p->VolumeTotal, sizeof(p->VolumeTotal));
    set_struct(obj, "InsertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "InsertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "ActiveTime", &p->ActiveTime, sizeof(p->ActiveTime));
    set_struct(obj, "SuspendTime", &p->SuspendTime, sizeof(p->SuspendTime));
    set_struct(obj, "UpdateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "CancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "ActiveTraderID", &p->ActiveTraderID, sizeof(p->ActiveTraderID));
    set_struct(obj, "ClearingPartID", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "UserProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "UserForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "ActiveUserID", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "BrokerOrderSeq", &p->BrokerOrderSeq, sizeof(p->BrokerOrderSeq));
    set_struct(obj, "RelativeOrderSysID", &p->RelativeOrderSysID, sizeof(p->RelativeOrderSysID));
    set_struct(obj, "ZCETotalTradedVolume", &p->ZCETotalTradedVolume, sizeof(p->ZCETotalTradedVolume));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "IsSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrOrderActionField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "OrderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "OrderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "FrontID", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "OrderSysID", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "ActionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "LimitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "VolumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "ActionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "ActionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "TraderID", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "OrderLocalID", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "ActionLocalID", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ClientID", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "BusinessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "OrderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "StatusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "BranchID", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "InvestUnitID", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "MacAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeSequenceField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeSequenceField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "MarketStatus", &p->MarketStatus, sizeof(p->MarketStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeWithPriceField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "OffsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "MaxVolume", &p->MaxVolume, sizeof(p->MaxVolume));
    set_struct(obj, "Price", &p->Price, sizeof(p->Price));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerTradingParamsField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerTradingParamsField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "MarginPriceType", &p->MarginPriceType, sizeof(p->MarginPriceType));
    set_struct(obj, "Algorithm", &p->Algorithm, sizeof(p->Algorithm));
    set_struct(obj, "AvailIncludeCloseProfit", &p->AvailIncludeCloseProfit, sizeof(p->AvailIncludeCloseProfit));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "OptionRoyaltyPriceType", &p->OptionRoyaltyPriceType, sizeof(p->OptionRoyaltyPriceType));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerTradingAlgosField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerTradingAlgosField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "HandlePositionAlgoID", &p->HandlePositionAlgoID, sizeof(p->HandlePositionAlgoID));
    set_struct(obj, "FindMarginRateAlgoID", &p->FindMarginRateAlgoID, sizeof(p->FindMarginRateAlgoID));
    set_struct(obj, "HandleTradingAccountAlgoID", &p->HandleTradingAccountAlgoID, sizeof(p->HandleTradingAccountAlgoID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryBrokerDepositField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerDepositField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "PreBalance", &p->PreBalance, sizeof(p->PreBalance));
    set_struct(obj, "CurrMargin", &p->CurrMargin, sizeof(p->CurrMargin));
    set_struct(obj, "CloseProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "Balance", &p->Balance, sizeof(p->Balance));
    set_struct(obj, "Deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "Withdraw", &p->Withdraw, sizeof(p->Withdraw));
    set_struct(obj, "Available", &p->Available, sizeof(p->Available));
    set_struct(obj, "Reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "FrozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCFMMCBrokerKeyField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCFMMCBrokerKeyField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "CreateDate", &p->CreateDate, sizeof(p->CreateDate));
    set_struct(obj, "CreateTime", &p->CreateTime, sizeof(p->CreateTime));
    set_struct(obj, "KeyID", &p->KeyID, sizeof(p->KeyID));
    set_struct(obj, "CurrentKey", &p->CurrentKey, sizeof(p->CurrentKey));
    set_struct(obj, "KeyKind", &p->KeyKind, sizeof(p->KeyKind));
}
static void set_struct(Local<Object>& obj, CThostFtdcCFMMCTradingAccountKeyField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "KeyID", &p->KeyID, sizeof(p->KeyID));
    set_struct(obj, "CurrentKey", &p->CurrentKey, sizeof(p->CurrentKey));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCFMMCTradingAccountKeyField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserOTPParamField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OTPVendorsID", &p->OTPVendorsID, sizeof(p->OTPVendorsID));
    set_struct(obj, "SerialNumber", &p->SerialNumber, sizeof(p->SerialNumber));
    set_struct(obj, "AuthKey", &p->AuthKey, sizeof(p->AuthKey));
    set_struct(obj, "LastDrift", &p->LastDrift, sizeof(p->LastDrift));
    set_struct(obj, "LastSuccess", &p->LastSuccess, sizeof(p->LastSuccess));
    set_struct(obj, "OTPType", &p->OTPType, sizeof(p->OTPType));
}
static void set_struct(Local<Object>& obj, CThostFtdcManualSyncBrokerUserOTPField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "OTPType", &p->OTPType, sizeof(p->OTPType));
    set_struct(obj, "FirstOTP", &p->FirstOTP, sizeof(p->FirstOTP));
    set_struct(obj, "SecondOTP", &p->SecondOTP, sizeof(p->SecondOTP));
}
static void set_struct(Local<Object>& obj, CThostFtdcCommRateModelField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "CommModelID", &p->CommModelID, sizeof(p->CommModelID));
    set_struct(obj, "CommModelName", &p->CommModelName, sizeof(p->CommModelName));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCommRateModelField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "CommModelID", &p->CommModelID, sizeof(p->CommModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarginModelField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "MarginModelID", &p->MarginModelID, sizeof(p->MarginModelID));
    set_struct(obj, "MarginModelName", &p->MarginModelName, sizeof(p->MarginModelName));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMarginModelField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "MarginModelID", &p->MarginModelID, sizeof(p->MarginModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcEWarrantOffsetField *p)
{
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "Direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "Volume", &p->Volume, sizeof(p->Volume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryEWarrantOffsetField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "InstrumentID", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorProductGroupMarginField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "ProductGroupID", &p->ProductGroupID, sizeof(p->ProductGroupID));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorProductGroupMarginField *p)
{
    set_struct(obj, "ProductGroupID", &p->ProductGroupID, sizeof(p->ProductGroupID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "SettlementID", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "FrozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "LongFrozenMargin", &p->LongFrozenMargin, sizeof(p->LongFrozenMargin));
    set_struct(obj, "ShortFrozenMargin", &p->ShortFrozenMargin, sizeof(p->ShortFrozenMargin));
    set_struct(obj, "UseMargin", &p->UseMargin, sizeof(p->UseMargin));
    set_struct(obj, "LongUseMargin", &p->LongUseMargin, sizeof(p->LongUseMargin));
    set_struct(obj, "ShortUseMargin", &p->ShortUseMargin, sizeof(p->ShortUseMargin));
    set_struct(obj, "ExchMargin", &p->ExchMargin, sizeof(p->ExchMargin));
    set_struct(obj, "LongExchMargin", &p->LongExchMargin, sizeof(p->LongExchMargin));
    set_struct(obj, "ShortExchMargin", &p->ShortExchMargin, sizeof(p->ShortExchMargin));
    set_struct(obj, "CloseProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "FrozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "Commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "FrozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "CashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "PositionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "OffsetAmount", &p->OffsetAmount, sizeof(p->OffsetAmount));
    set_struct(obj, "LongOffsetAmount", &p->LongOffsetAmount, sizeof(p->LongOffsetAmount));
    set_struct(obj, "ShortOffsetAmount", &p->ShortOffsetAmount, sizeof(p->ShortOffsetAmount));
    set_struct(obj, "ExchOffsetAmount", &p->ExchOffsetAmount, sizeof(p->ExchOffsetAmount));
    set_struct(obj, "LongExchOffsetAmount", &p->LongExchOffsetAmount, sizeof(p->LongExchOffsetAmount));
    set_struct(obj, "ShortExchOffsetAmount", &p->ShortExchOffsetAmount, sizeof(p->ShortExchOffsetAmount));
    set_struct(obj, "HedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryCFMMCTradingAccountTokenField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCFMMCTradingAccountTokenField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "ParticipantID", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "KeyID", &p->KeyID, sizeof(p->KeyID));
    set_struct(obj, "Token", &p->Token, sizeof(p->Token));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryProductGroupField *p)
{
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcProductGroupField *p)
{
    set_struct(obj, "ProductID", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "ProductGroupID", &p->ProductGroupID, sizeof(p->ProductGroupID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBulletinField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "BulletinID", &p->BulletinID, sizeof(p->BulletinID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "NewsType", &p->NewsType, sizeof(p->NewsType));
    set_struct(obj, "NewsUrgency", &p->NewsUrgency, sizeof(p->NewsUrgency));
    set_struct(obj, "SendTime", &p->SendTime, sizeof(p->SendTime));
    set_struct(obj, "Abstract", &p->Abstract, sizeof(p->Abstract));
    set_struct(obj, "ComeFrom", &p->ComeFrom, sizeof(p->ComeFrom));
    set_struct(obj, "Content", &p->Content, sizeof(p->Content));
    set_struct(obj, "URLLink", &p->URLLink, sizeof(p->URLLink));
    set_struct(obj, "MarketID", &p->MarketID, sizeof(p->MarketID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBulletinField *p)
{
    set_struct(obj, "ExchangeID", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "BulletinID", &p->BulletinID, sizeof(p->BulletinID));
    set_struct(obj, "SequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "NewsType", &p->NewsType, sizeof(p->NewsType));
    set_struct(obj, "NewsUrgency", &p->NewsUrgency, sizeof(p->NewsUrgency));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqOpenAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "CashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqCancelAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "CashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqChangeAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "NewBankAccount", &p->NewBankAccount, sizeof(p->NewBankAccount));
    set_struct(obj, "NewBankPassWord", &p->NewBankPassWord, sizeof(p->NewBankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqTransferField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "TradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "FutureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "FeePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "BrokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "Message", &p->Message, sizeof(p->Message));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "TransferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspTransferField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "TradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "FutureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "FeePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "BrokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "Message", &p->Message, sizeof(p->Message));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "TransferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqRepealField *p)
{
    set_struct(obj, "RepealTimeInterval", &p->RepealTimeInterval, sizeof(p->RepealTimeInterval));
    set_struct(obj, "RepealedTimes", &p->RepealedTimes, sizeof(p->RepealedTimes));
    set_struct(obj, "BankRepealFlag", &p->BankRepealFlag, sizeof(p->BankRepealFlag));
    set_struct(obj, "BrokerRepealFlag", &p->BrokerRepealFlag, sizeof(p->BrokerRepealFlag));
    set_struct(obj, "PlateRepealSerial", &p->PlateRepealSerial, sizeof(p->PlateRepealSerial));
    set_struct(obj, "BankRepealSerial", &p->BankRepealSerial, sizeof(p->BankRepealSerial));
    set_struct(obj, "FutureRepealSerial", &p->FutureRepealSerial, sizeof(p->FutureRepealSerial));
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "TradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "FutureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "FeePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "BrokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "Message", &p->Message, sizeof(p->Message));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "TransferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspRepealField *p)
{
    set_struct(obj, "RepealTimeInterval", &p->RepealTimeInterval, sizeof(p->RepealTimeInterval));
    set_struct(obj, "RepealedTimes", &p->RepealedTimes, sizeof(p->RepealedTimes));
    set_struct(obj, "BankRepealFlag", &p->BankRepealFlag, sizeof(p->BankRepealFlag));
    set_struct(obj, "BrokerRepealFlag", &p->BrokerRepealFlag, sizeof(p->BrokerRepealFlag));
    set_struct(obj, "PlateRepealSerial", &p->PlateRepealSerial, sizeof(p->PlateRepealSerial));
    set_struct(obj, "BankRepealSerial", &p->BankRepealSerial, sizeof(p->BankRepealSerial));
    set_struct(obj, "FutureRepealSerial", &p->FutureRepealSerial, sizeof(p->FutureRepealSerial));
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "TradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "FutureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "FeePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "BrokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "Message", &p->Message, sizeof(p->Message));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "TransferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqQueryAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspQueryAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "BankUseAmount", &p->BankUseAmount, sizeof(p->BankUseAmount));
    set_struct(obj, "BankFetchAmount", &p->BankFetchAmount, sizeof(p->BankFetchAmount));
}
static void set_struct(Local<Object>& obj, CThostFtdcFutureSignIOField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspFutureSignInField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "PinKey", &p->PinKey, sizeof(p->PinKey));
    set_struct(obj, "MacKey", &p->MacKey, sizeof(p->MacKey));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqFutureSignOutField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspFutureSignOutField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqQueryTradeResultBySerialField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "Reference", &p->Reference, sizeof(p->Reference));
    set_struct(obj, "RefrenceIssureType", &p->RefrenceIssureType, sizeof(p->RefrenceIssureType));
    set_struct(obj, "RefrenceIssure", &p->RefrenceIssure, sizeof(p->RefrenceIssure));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "TradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspQueryTradeResultBySerialField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "Reference", &p->Reference, sizeof(p->Reference));
    set_struct(obj, "RefrenceIssureType", &p->RefrenceIssureType, sizeof(p->RefrenceIssureType));
    set_struct(obj, "RefrenceIssure", &p->RefrenceIssure, sizeof(p->RefrenceIssure));
    set_struct(obj, "OriginReturnCode", &p->OriginReturnCode, sizeof(p->OriginReturnCode));
    set_struct(obj, "OriginDescrInfoForReturnCode", &p->OriginDescrInfoForReturnCode, sizeof(p->OriginDescrInfoForReturnCode));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "TradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqDayEndFileReadyField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "FileBusinessCode", &p->FileBusinessCode, sizeof(p->FileBusinessCode));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcReturnResultField *p)
{
    set_struct(obj, "ReturnCode", &p->ReturnCode, sizeof(p->ReturnCode));
    set_struct(obj, "DescrInfoForReturnCode", &p->DescrInfoForReturnCode, sizeof(p->DescrInfoForReturnCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyFuturePasswordField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyCustInfoField *p)
{
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyFuturePasswordAndCustInfoField *p)
{
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcDepositResultInformField *p)
{
    set_struct(obj, "DepositSeqNo", &p->DepositSeqNo, sizeof(p->DepositSeqNo));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "Deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "ReturnCode", &p->ReturnCode, sizeof(p->ReturnCode));
    set_struct(obj, "DescrInfoForReturnCode", &p->DescrInfoForReturnCode, sizeof(p->DescrInfoForReturnCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqSyncKeyField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Message", &p->Message, sizeof(p->Message));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspSyncKeyField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Message", &p->Message, sizeof(p->Message));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifyQueryAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "BankUseAmount", &p->BankUseAmount, sizeof(p->BankUseAmount));
    set_struct(obj, "BankFetchAmount", &p->BankFetchAmount, sizeof(p->BankFetchAmount));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferSerialField *p)
{
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "FutureAccType", &p->FutureAccType, sizeof(p->FutureAccType));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "InvestorID", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "FutureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "TradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "CustFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "BrokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "AvailabilityFlag", &p->AvailabilityFlag, sizeof(p->AvailabilityFlag));
    set_struct(obj, "OperatorCode", &p->OperatorCode, sizeof(p->OperatorCode));
    set_struct(obj, "BankNewAccount", &p->BankNewAccount, sizeof(p->BankNewAccount));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTransferSerialField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifyFutureSignInField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "PinKey", &p->PinKey, sizeof(p->PinKey));
    set_struct(obj, "MacKey", &p->MacKey, sizeof(p->MacKey));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifyFutureSignOutField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifySyncKeyField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "Message", &p->Message, sizeof(p->Message));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "RequestID", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryAccountregisterField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcAccountregisterField *p)
{
    set_struct(obj, "TradeDay", &p->TradeDay, sizeof(p->TradeDay));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "OpenOrDestroy", &p->OpenOrDestroy, sizeof(p->OpenOrDestroy));
    set_struct(obj, "RegDate", &p->RegDate, sizeof(p->RegDate));
    set_struct(obj, "OutDate", &p->OutDate, sizeof(p->OutDate));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
}
static void set_struct(Local<Object>& obj, CThostFtdcOpenAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "CashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcCancelAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "CashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "DeviceID", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "BankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "OperNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcChangeAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "NewBankAccount", &p->NewBankAccount, sizeof(p->NewBankAccount));
    set_struct(obj, "NewBankPassWord", &p->NewBankPassWord, sizeof(p->NewBankPassWord));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "BankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "SecuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcSecAgentACIDMapField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "BrokerSecAgentID", &p->BrokerSecAgentID, sizeof(p->BrokerSecAgentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySecAgentACIDMapField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserRightsAssignField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "DRIdentityID", &p->DRIdentityID, sizeof(p->DRIdentityID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserRightAssignField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "DRIdentityID", &p->DRIdentityID, sizeof(p->DRIdentityID));
    set_struct(obj, "Tradeable", &p->Tradeable, sizeof(p->Tradeable));
}
static void set_struct(Local<Object>& obj, CThostFtdcDRTransferField *p)
{
    set_struct(obj, "OrigDRIdentityID", &p->OrigDRIdentityID, sizeof(p->OrigDRIdentityID));
    set_struct(obj, "DestDRIdentityID", &p->DestDRIdentityID, sizeof(p->DestDRIdentityID));
    set_struct(obj, "OrigBrokerID", &p->OrigBrokerID, sizeof(p->OrigBrokerID));
    set_struct(obj, "DestBrokerID", &p->DestBrokerID, sizeof(p->DestBrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcFensUserInfoField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "LoginMode", &p->LoginMode, sizeof(p->LoginMode));
}
static void set_struct(Local<Object>& obj, CThostFtdcCurrTransferIdentityField *p)
{
    set_struct(obj, "IdentityID", &p->IdentityID, sizeof(p->IdentityID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLoginForbiddenUserField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "IPAddress", &p->IPAddress, sizeof(p->IPAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryLoginForbiddenUserField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "UserID", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMulticastGroupInfoField *p)
{
    set_struct(obj, "GroupIP", &p->GroupIP, sizeof(p->GroupIP));
    set_struct(obj, "GroupPort", &p->GroupPort, sizeof(p->GroupPort));
    set_struct(obj, "SourceIP", &p->SourceIP, sizeof(p->SourceIP));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountReserveField *p)
{
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReserveOpenAccountConfirmField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "AccountID", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "Password", &p->Password, sizeof(p->Password));
    set_struct(obj, "BankReserveOpenSeq", &p->BankReserveOpenSeq, sizeof(p->BankReserveOpenSeq));
    set_struct(obj, "BookDate", &p->BookDate, sizeof(p->BookDate));
    set_struct(obj, "BookPsw", &p->BookPsw, sizeof(p->BookPsw));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReserveOpenAccountField *p)
{
    set_struct(obj, "TradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "BankID", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "BankBranchID", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "BrokerID", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "BrokerBranchID", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "TradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "TradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "BankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "TradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "PlateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "LastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "SessionID", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "CustomerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "IdCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "IdentifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "Gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "CountryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "CustType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "Address", &p->Address, sizeof(p->Address));
    set_struct(obj, "ZipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "Telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "MobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "Fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "EMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "MoneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "BankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "BankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "InstallID", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "VerifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "CurrencyID", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "Digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "BankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "BrokerIDByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "TID", &p->TID, sizeof(p->TID));
    set_struct(obj, "ReserveOpenAccStas", &p->ReserveOpenAccStas, sizeof(p->ReserveOpenAccStas));
    set_struct(obj, "ErrorID", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "ErrorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}

};
#endif



