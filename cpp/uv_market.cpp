#include "uv_market.h"

std::map<int, CbWrap*> uv_market::cb_map;

uv_market::uv_market(void) {
  iRequestID = 0;
  uv_async_init(uv_default_loop(),&async_t,NULL);
  logger_cout("uv_market init");
}

uv_market::~uv_market(void) {
  uv_close((uv_handle_t*)&async_t,NULL);
}

const char* uv_market::GetTradingDay(){
  return this->m_pApi->GetTradingDay();
}

int uv_market::On(const char* eName,int cb_type, void(*callback)(CbRtnField* cbResult)) {
  std::string log = "uv_market On------>";
  std::map<int, CbWrap*>::iterator it = cb_map.find(cb_type);
  if (it != cb_map.end()) {
    logger_cout(log.append(" event id").append(to_string(cb_type)).append(" register repeat").c_str());
    return 1;
  }

  CbWrap* cb_wrap = new CbWrap();
  cb_wrap->callback = callback;
  cb_map[cb_type] = cb_wrap;
  logger_cout(log.append(" Event:").append(eName).append(" ID:").append(to_string(cb_type)).append(" register").c_str());
  return 0;
}

void uv_market::Connect(UVConnectField* pConnectField, int uuid, void(*callback)(int, void*)) {
  UVConnectField* _pConnectField = new UVConnectField();
  memcpy(_pConnectField, pConnectField, sizeof(UVConnectField));
  logger_cout("market Connect this -> invoke");
  this->invoke(_pConnectField, T_CONNECT, callback, uuid);
}
void uv_market::Disconnect() {
  m_pApi->RegisterSpi(NULL);
  m_pApi->Release();
  m_pApi = NULL;

  std::map<int, CbWrap*>::iterator callback_it = cb_map.begin();
  while (callback_it != cb_map.end()) {
    delete callback_it->second;
    callback_it++;
  }
  logger_cout("uv_market Disconnect------>object destroyed");
}
void uv_market::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  CThostFtdcRspInfoField* _pRspInfo = NULL;
  if (pRspInfo) {
    _pRspInfo = new CThostFtdcRspInfoField();
    memcpy(_pRspInfo, pRspInfo, sizeof(CThostFtdcRspInfoField));
  }
  std::string log = "uv_market OnRspError------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  on_invoke(T_ONRSPERROR, _pRspInfo, pRspInfo, nRequestID, bIsLast);
}
///uv_queue_work
void uv_market::_completed(uv_work_t * work, int) {
  LookupCtpApiBaton* baton = static_cast<LookupCtpApiBaton*>(work->data);
  baton->callback(baton->nResult, baton);
  delete baton->args;
  delete baton;
}

void uv_market::_on_async(uv_work_t * work){
    //do nothing
}

void uv_market::_on_completed(uv_work_t * work,int){
  std::string head = "uv_market _on_completed  ==== ";
  logger_cout(head.c_str());

  CbRtnField* cbTrnField = static_cast<CbRtnField*>(work->data);
  std::map<int, CbWrap*>::iterator it = cb_map.find(cbTrnField->eFlag);
  if (it != cb_map.end()) {
    cb_map[cbTrnField->eFlag]->callback(cbTrnField);
  }
  if (cbTrnField->rtnField)
    delete cbTrnField->rtnField;
  if (cbTrnField->rspInfo)
    delete cbTrnField->rspInfo;
  delete cbTrnField;
}

void uv_market::invoke(void* field, int ret, void(*callback)(int, void*), int uuid) {
  LookupCtpApiBaton* baton = new LookupCtpApiBaton();
  baton->work.data = baton;
  baton->uv_market_obj = this;
  baton->callback = callback;
  baton->args = field;
  baton->fun = ret;
  baton->uuid = uuid;

  iRequestID = iRequestID+1;
  baton->iRequestID = iRequestID;
  std::string head = "uv_market invoke------>uuid:";
  logger_cout(head.append(to_string(uuid)).append(",requestid:").append(to_string(baton->iRequestID)).c_str());
  uv_queue_work(uv_default_loop(), &baton->work, _async, _completed);
}

void uv_market::on_invoke(int event_type, void* _stru, CThostFtdcRspInfoField *pRspInfo_org, int nRequestID, bool bIsLast){
  CThostFtdcRspInfoField* _pRspInfo = NULL;
  if (pRspInfo_org) {
    _pRspInfo = new CThostFtdcRspInfoField();
    memcpy(_pRspInfo, pRspInfo_org, sizeof(CThostFtdcRspInfoField));
  }
  CbRtnField* field = new CbRtnField();
  field->work.data = field;
  field->eFlag = event_type;
  field->rtnField = _stru;
  field->rspInfo = (void*)_pRspInfo;
  field->nRequestID = nRequestID;
  field->bIsLast = bIsLast;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
}

void uv_market::_async(uv_work_t * work) {
  LookupCtpApiBaton* baton = static_cast<LookupCtpApiBaton*>(work->data);
  uv_market* uv_market_obj = static_cast<uv_market*>(baton->uv_market_obj);
  std::string log = "uv_market _async------>";
  logger_cout(log.append(to_string(baton->fun)).c_str());
  switch (baton->fun) {
  case T_CONNECT:
  {
    UVConnectField* _pConnectF = static_cast<UVConnectField*>(baton->args);
    uv_market_obj->m_pApi = CThostFtdcMdApi::CreateFtdcMdApi(_pConnectF->szPath);
    uv_market_obj->m_pApi->RegisterSpi(uv_market_obj);
    uv_market_obj->m_pApi->RegisterFront(_pConnectF->front_addr);
    uv_market_obj->m_pApi->Init(); // CThostFtdcMdApi
    logger_cout(log.append("invoke connect,the result is 0 | szPath is ").append(_pConnectF->szPath).append(CThostFtdcMdApi::GetApiVersion()).c_str());
    break;
  }
  case T_REQUSERLOGIN:
    {
      CThostFtdcReqUserLoginField *_pReqUserLoginField = static_cast<CThostFtdcReqUserLoginField*>(baton->args);
      baton->nResult = uv_market_obj->m_pApi->ReqUserLogin(_pReqUserLoginField, baton->iRequestID);
      logger_cout(log.append("invoke ReqUserLogin,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }
  case T_REQUSERLOGOUT:
    {
      CThostFtdcUserLogoutField *_pUserLogout = static_cast<CThostFtdcUserLogoutField*>(baton->args);
      baton->nResult = uv_market_obj->m_pApi->ReqUserLogout(_pUserLogout, baton->iRequestID);
      logger_cout(log.append("invoke ReqUserLogout,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }
  case T_SUBSCRIBEMARKETDATA:
    {
      char ** _ppInstrumentID = static_cast<char **>(baton->args);	 
      baton->nResult = uv_market_obj->m_pApi->SubscribeMarketData(_ppInstrumentID, baton->nCount);
      logger_cout(log.append("invoke SubscribeMarketData,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }
  case T_UNSUBSCRIBEMARKETDATA:
    {
      char ** _ppInstrumentID = static_cast<char **>(baton->args);
      baton->nResult = uv_market_obj->m_pApi->UnSubscribeMarketData(_ppInstrumentID, baton->nCount);
      logger_cout(log.append("invoke UnSubscribeMarketData,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }
  case T_SUBSCRIBEFORQUOTERSP:
    {
      char ** _ppInstrumentID = static_cast<char **>(baton->args);
      baton->nResult = uv_market_obj->m_pApi->SubscribeForQuoteRsp(_ppInstrumentID, baton->nCount);
      logger_cout(log.append("invoke SubscribeForQuoteRsp,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }
  case T_UNSUBSCRIBEFORQUOTERSP:
    {
      char ** _ppInstrumentID = static_cast<char **>(baton->args);
      baton->nResult = uv_market_obj->m_pApi->UnSubscribeForQuoteRsp(_ppInstrumentID, baton->nCount);
      logger_cout(log.append("invoke UnSubscribeForQuoteRsp,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }
  default:
    {
      logger_cout(log.append("No case event:").append(to_string(baton->fun)).c_str());
      break;
    }
  }
}

void uv_market::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcReqUserLoginField *_pReqUserLoginField = new CThostFtdcReqUserLoginField();
  memcpy(_pReqUserLoginField, pReqUserLoginField, sizeof(CThostFtdcReqUserLoginField));
  this->invoke(_pReqUserLoginField, T_REQUSERLOGIN, callback, nRequestID);
}

void uv_market::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcUserLogoutField *_pUserLogout = new CThostFtdcUserLogoutField();
  memcpy(_pUserLogout, pUserLogout, sizeof(CThostFtdcUserLogoutField));
  this->invoke(_pUserLogout, T_REQUSERLOGOUT, callback, nRequestID);
}

void uv_market::SubscribeMarketData(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*)) {
	char **_ppInstrumentID = new char*[nCount];
	for (int i = 0; i < nCount; i++) {
		memcpy(_ppInstrumentID + i, ppInstrumentID + i, sizeof(*(ppInstrumentID + i)));
	}
	this->invoke(_ppInstrumentID, T_SUBSCRIBEMARKETDATA, callback, nRequestID);
}

void uv_market::UnSubscribeMarketData(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*)) {
	char **_ppInstrumentID = new char*[nCount];
	for (int i = 0; i < nCount; i++) {
		memcpy(_ppInstrumentID + i, ppInstrumentID + i, sizeof(*(ppInstrumentID + i)));
	}
	this->invoke(_ppInstrumentID, T_UNSUBSCRIBEMARKETDATA, callback, nRequestID);
}

void uv_market::SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*)) {
	char **_ppInstrumentID = new char*[nCount];
	for (int i = 0; i < nCount; i++) {
		memcpy(_ppInstrumentID + i, ppInstrumentID + i, sizeof(*(ppInstrumentID + i)));
	}
	this->invoke(_ppInstrumentID, T_SUBSCRIBEFORQUOTERSP, callback, nRequestID);
}

void uv_market::UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount, int nRequestID, void(*callback)(int, void*)) {
	char **_ppInstrumentID = new char*[nCount];
	for (int i = 0; i < nCount; i++) {
		memcpy(_ppInstrumentID + i, ppInstrumentID + i, sizeof(*(ppInstrumentID + i)));
	}
	this->invoke(_ppInstrumentID, T_UNSUBSCRIBEFORQUOTERSP, callback, nRequestID);
}

void uv_market::OnFrontConnected() {

  logger_cout("uv_market OnFrontConnected");
  CbRtnField* field = new CbRtnField();
  field->eFlag = T_ONFRONTCONNECTED;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
}

void uv_market::OnFrontDisconnected(int nReason) {

  std::string log = "uv_market OnFrontDisconnected------>";
  logger_cout(log.append("nReason:").append(to_string(nReason)).c_str());
  CbRtnField* field = new CbRtnField();
  field->eFlag = T_ONFRONTDISCONNECTED;
  field->nReason = nReason;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
}

void uv_market::OnHeartBeatWarning(int nTimeLapse) {

  std::string log = "uv_market OnHeartBeatWarning------>";
  logger_cout(log.append("nTimeLapse:").append(to_string(nTimeLapse)).c_str());
  CbRtnField* field = new CbRtnField();
  field->eFlag = T_ONHEARTBEATWARNING;
  field->nTimeLapse = nTimeLapse;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
}

void uv_market::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_market OnRspUserLogin------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcRspUserLoginField* _pRspUserLogin = NULL;
  if (pRspUserLogin) {
    _pRspUserLogin = new CThostFtdcRspUserLoginField();
    memcpy(_pRspUserLogin, pRspUserLogin, sizeof(CThostFtdcRspUserLoginField));
  }
  on_invoke(T_ONRSPUSERLOGIN, _pRspUserLogin, pRspInfo, nRequestID, bIsLast);          
}

void uv_market::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_market OnRspUserLogout------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcUserLogoutField* _pUserLogout = NULL;
  if (pUserLogout) {
    _pUserLogout = new CThostFtdcUserLogoutField();
    memcpy(_pUserLogout, pUserLogout, sizeof(CThostFtdcUserLogoutField));
  }
  on_invoke(T_ONRSPUSERLOGOUT, _pUserLogout, pRspInfo, nRequestID, bIsLast);          
}

void uv_market::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	CThostFtdcSpecificInstrumentField* _pSpecificInstrument = NULL;
	if (pSpecificInstrument) {
		_pSpecificInstrument = new CThostFtdcSpecificInstrumentField();
		memcpy(_pSpecificInstrument, pSpecificInstrument, sizeof(CThostFtdcSpecificInstrumentField));
	}
	std::string log = "uv_market OnRspSubMarketData------>";
	logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
	on_invoke(T_ONRSPSUBMARKETDATA, _pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void uv_market::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	CThostFtdcSpecificInstrumentField* _pSpecificInstrument = NULL;
	if (pSpecificInstrument) {
		_pSpecificInstrument = new CThostFtdcSpecificInstrumentField();
		memcpy(_pSpecificInstrument, pSpecificInstrument, sizeof(CThostFtdcSpecificInstrumentField));
	}
	std::string log = "uv_market OnRspUnSubMarketData------>";
	logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
	on_invoke(T_ONRSPUNSUBMARKETDATA, _pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void uv_market::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	CThostFtdcSpecificInstrumentField* _pSpecificInstrument = NULL;
	if (pSpecificInstrument) {
		_pSpecificInstrument = new CThostFtdcSpecificInstrumentField();
		memcpy(_pSpecificInstrument, pSpecificInstrument, sizeof(CThostFtdcSpecificInstrumentField));
	}
	std::string log = "uv_market OnRspSubForQuoteRsp------>";
	logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
	on_invoke(T_ONRSPSUBFORQUOTERSP, _pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void uv_market::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	CThostFtdcSpecificInstrumentField* _pSpecificInstrument = NULL;
	if (pSpecificInstrument) {
		_pSpecificInstrument = new CThostFtdcSpecificInstrumentField();
		memcpy(_pSpecificInstrument, pSpecificInstrument, sizeof(CThostFtdcSpecificInstrumentField));
	}
	std::string log = "uv_market OnRspUnSubForQuoteRsp------>";
	logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
	on_invoke(T_ONRSPUNSUBFORQUOTERSP, _pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void uv_market::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	CThostFtdcDepthMarketDataField* _pDepthMarketData = NULL;
	if (pDepthMarketData) {
		_pDepthMarketData = new CThostFtdcDepthMarketDataField();
		memcpy(_pDepthMarketData, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
	}
	std::string log = "uv_market OnRtnDepthMarketData";
	logger_cout(log.c_str());
	on_invoke(T_ONRTNDEPTHMARKETDATA, _pDepthMarketData, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_market::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
	CThostFtdcForQuoteRspField* _pForQuoteRsp = NULL;
	if (pForQuoteRsp) {
		_pForQuoteRsp = new CThostFtdcForQuoteRspField();
		memcpy(_pForQuoteRsp, pForQuoteRsp, sizeof(CThostFtdcForQuoteRspField));
	}
	std::string log = "uv_market OnRtnForQuoteRsp";
	logger_cout(log.c_str());
	on_invoke(T_ONRTNFORQUOTERSP, pForQuoteRsp, new CThostFtdcRspInfoField(), 0, 0);
}
