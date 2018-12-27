
#include "uv_trader.h"

std::map<int, CbWrap*> uv_trader::cb_map;

uv_trader::uv_trader(void) {
  iRequestID = 0;
  uv_async_init(uv_default_loop(),&async_t,NULL);
  logger_cout("uv_trader init");
}

uv_trader::~uv_trader(void) {
  uv_close((uv_handle_t*)&async_t,NULL);
}

const char* uv_trader::GetTradingDay(){
  return this->m_pApi->GetTradingDay();
}

int uv_trader::On(const char* eName,int cb_type, void(*callback)(CbRtnField* cbResult)) {
  std::string log = "uv_trader On------>";
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

void uv_trader::Connect(UVConnectField* pConnectField, int uuid, void(*callback)(int, void*)) {
  UVConnectField* _pConnectField = new UVConnectField();
  memcpy(_pConnectField, pConnectField, sizeof(UVConnectField));
  logger_cout("trader Connect this -> invoke");
  this->invoke(_pConnectField, T_CONNECT, callback, uuid);
}
void uv_trader::Disconnect() {
  m_pApi->RegisterSpi(NULL);
  m_pApi->Release();
  m_pApi = NULL;

  std::map<int, CbWrap*>::iterator callback_it = cb_map.begin();
  while (callback_it != cb_map.end()) {
    delete callback_it->second;
    callback_it++;
  }
  logger_cout("uv_trader Disconnect------>object destroyed");
}
void uv_trader::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  CThostFtdcRspInfoField* _pRspInfo = NULL;
  if (pRspInfo) {
    _pRspInfo = new CThostFtdcRspInfoField();
    memcpy(_pRspInfo, pRspInfo, sizeof(CThostFtdcRspInfoField));
  }
  std::string log = "uv_trader OnRspError------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  on_invoke(T_ONRSPERROR, _pRspInfo, pRspInfo, nRequestID, bIsLast);
}
///uv_queue_work
void uv_trader::_completed(uv_work_t * work, int) {
  LookupCtpApiBaton* baton = static_cast<LookupCtpApiBaton*>(work->data);
  baton->callback(baton->nResult, baton);
  delete baton->args;
  delete baton;
}

void uv_trader::_on_async(uv_work_t * work){
    //do nothing
}

void uv_trader::_on_completed(uv_work_t * work,int){
  std::string head = "uv_trader _on_completed  ==== ";
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

void uv_trader::invoke(void* field, int ret, void(*callback)(int, void*), int uuid) {
  LookupCtpApiBaton* baton = new LookupCtpApiBaton();
  baton->work.data = baton;
  baton->uv_trader_obj = this;
  baton->callback = callback;
  baton->args = field;
  baton->fun = ret;
  baton->uuid = uuid;

  iRequestID = iRequestID+1;
  baton->iRequestID = iRequestID;
  std::string head = "uv_trader invoke------>uuid:";
  logger_cout(head.append(to_string(uuid)).append(",requestid:").append(to_string(baton->iRequestID)).c_str());
  uv_queue_work(uv_default_loop(), &baton->work, _async, _completed);
}

void uv_trader::on_invoke(int event_type, void* _stru, CThostFtdcRspInfoField *pRspInfo_org, int nRequestID, bool bIsLast){
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
void uv_trader::_async(uv_work_t * work) {
  LookupCtpApiBaton* baton = static_cast<LookupCtpApiBaton*>(work->data);
  uv_trader* uv_trader_obj = static_cast<uv_trader*>(baton->uv_trader_obj);
  std::string log = "uv_trader _async------>";
  logger_cout(log.append(to_string(baton->fun)).c_str());
  switch (baton->fun) {
  case T_CONNECT:
  {
    UVConnectField* _pConnectF = static_cast<UVConnectField*>(baton->args);
    uv_trader_obj->m_pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(_pConnectF->szPath);
    uv_trader_obj->m_pApi->RegisterSpi(uv_trader_obj);
    uv_trader_obj->m_pApi->SubscribePublicTopic(static_cast<THOST_TE_RESUME_TYPE>(_pConnectF->public_topic_type));
    uv_trader_obj->m_pApi->SubscribePrivateTopic(static_cast<THOST_TE_RESUME_TYPE>(_pConnectF->private_topic_type));
    uv_trader_obj->m_pApi->RegisterFront(_pConnectF->front_addr);
    uv_trader_obj->m_pApi->Init(); // CThostFtdcMdApi
    logger_cout(log.append("invoke connect,the result is 0 | szPath is ").append(_pConnectF->szPath).append(CThostFtdcTraderApi::GetApiVersion()).c_str());
    break;
  }

  case T_REQAUTHENTICATE:
    {
      CThostFtdcReqAuthenticateField *_pReqAuthenticateField = static_cast<CThostFtdcReqAuthenticateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqAuthenticate(_pReqAuthenticateField, baton->iRequestID);
      logger_cout(log.append("invoke ReqAuthenticate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQUSERLOGIN:
    {
      CThostFtdcReqUserLoginField *_pReqUserLoginField = static_cast<CThostFtdcReqUserLoginField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqUserLogin(_pReqUserLoginField, baton->iRequestID);
      logger_cout(log.append("invoke ReqUserLogin,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQUSERLOGOUT:
    {
      CThostFtdcUserLogoutField *_pUserLogout = static_cast<CThostFtdcUserLogoutField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqUserLogout(_pUserLogout, baton->iRequestID);
      logger_cout(log.append("invoke ReqUserLogout,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQUSERPASSWORDUPDATE:
    {
      CThostFtdcUserPasswordUpdateField *_pUserPasswordUpdate = static_cast<CThostFtdcUserPasswordUpdateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqUserPasswordUpdate(_pUserPasswordUpdate, baton->iRequestID);
      logger_cout(log.append("invoke ReqUserPasswordUpdate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQTRADINGACCOUNTPASSWORDUPDATE:
    {
      CThostFtdcTradingAccountPasswordUpdateField *_pTradingAccountPasswordUpdate = static_cast<CThostFtdcTradingAccountPasswordUpdateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqTradingAccountPasswordUpdate(_pTradingAccountPasswordUpdate, baton->iRequestID);
      logger_cout(log.append("invoke ReqTradingAccountPasswordUpdate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQORDERINSERT:
    {
      CThostFtdcInputOrderField *_pInputOrder = static_cast<CThostFtdcInputOrderField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqOrderInsert(_pInputOrder, baton->iRequestID);
      logger_cout(log.append("invoke ReqOrderInsert,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQPARKEDORDERINSERT:
    {
      CThostFtdcParkedOrderField *_pParkedOrder = static_cast<CThostFtdcParkedOrderField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqParkedOrderInsert(_pParkedOrder, baton->iRequestID);
      logger_cout(log.append("invoke ReqParkedOrderInsert,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQPARKEDORDERACTION:
    {
      CThostFtdcParkedOrderActionField *_pParkedOrderAction = static_cast<CThostFtdcParkedOrderActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqParkedOrderAction(_pParkedOrderAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqParkedOrderAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQORDERACTION:
    {
      CThostFtdcInputOrderActionField *_pInputOrderAction = static_cast<CThostFtdcInputOrderActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqOrderAction(_pInputOrderAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqOrderAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQUERYMAXORDERVOLUME:
    {
      CThostFtdcQueryMaxOrderVolumeField *_pQueryMaxOrderVolume = static_cast<CThostFtdcQueryMaxOrderVolumeField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQueryMaxOrderVolume(_pQueryMaxOrderVolume, baton->iRequestID);
      logger_cout(log.append("invoke ReqQueryMaxOrderVolume,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQSETTLEMENTINFOCONFIRM:
    {
      CThostFtdcSettlementInfoConfirmField *_pSettlementInfoConfirm = static_cast<CThostFtdcSettlementInfoConfirmField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqSettlementInfoConfirm(_pSettlementInfoConfirm, baton->iRequestID);
      logger_cout(log.append("invoke ReqSettlementInfoConfirm,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQREMOVEPARKEDORDER:
    {
      CThostFtdcRemoveParkedOrderField *_pRemoveParkedOrder = static_cast<CThostFtdcRemoveParkedOrderField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqRemoveParkedOrder(_pRemoveParkedOrder, baton->iRequestID);
      logger_cout(log.append("invoke ReqRemoveParkedOrder,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQREMOVEPARKEDORDERACTION:
    {
      CThostFtdcRemoveParkedOrderActionField *_pRemoveParkedOrderAction = static_cast<CThostFtdcRemoveParkedOrderActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqRemoveParkedOrderAction(_pRemoveParkedOrderAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqRemoveParkedOrderAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQEXECORDERINSERT:
    {
      CThostFtdcInputExecOrderField *_pInputExecOrder = static_cast<CThostFtdcInputExecOrderField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqExecOrderInsert(_pInputExecOrder, baton->iRequestID);
      logger_cout(log.append("invoke ReqExecOrderInsert,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQEXECORDERACTION:
    {
      CThostFtdcInputExecOrderActionField *_pInputExecOrderAction = static_cast<CThostFtdcInputExecOrderActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqExecOrderAction(_pInputExecOrderAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqExecOrderAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQFORQUOTEINSERT:
    {
      CThostFtdcInputForQuoteField *_pInputForQuote = static_cast<CThostFtdcInputForQuoteField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqForQuoteInsert(_pInputForQuote, baton->iRequestID);
      logger_cout(log.append("invoke ReqForQuoteInsert,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQUOTEINSERT:
    {
      CThostFtdcInputQuoteField *_pInputQuote = static_cast<CThostFtdcInputQuoteField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQuoteInsert(_pInputQuote, baton->iRequestID);
      logger_cout(log.append("invoke ReqQuoteInsert,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQUOTEACTION:
    {
      CThostFtdcInputQuoteActionField *_pInputQuoteAction = static_cast<CThostFtdcInputQuoteActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQuoteAction(_pInputQuoteAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqQuoteAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQBATCHORDERACTION:
    {
      CThostFtdcInputBatchOrderActionField *_pInputBatchOrderAction = static_cast<CThostFtdcInputBatchOrderActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqBatchOrderAction(_pInputBatchOrderAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqBatchOrderAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQOPTIONSELFCLOSEINSERT:
    {
      CThostFtdcInputOptionSelfCloseField *_pInputOptionSelfClose = static_cast<CThostFtdcInputOptionSelfCloseField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqOptionSelfCloseInsert(_pInputOptionSelfClose, baton->iRequestID);
      logger_cout(log.append("invoke ReqOptionSelfCloseInsert,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQOPTIONSELFCLOSEACTION:
    {
      CThostFtdcInputOptionSelfCloseActionField *_pInputOptionSelfCloseAction = static_cast<CThostFtdcInputOptionSelfCloseActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqOptionSelfCloseAction(_pInputOptionSelfCloseAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqOptionSelfCloseAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQCOMBACTIONINSERT:
    {
      CThostFtdcInputCombActionField *_pInputCombAction = static_cast<CThostFtdcInputCombActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqCombActionInsert(_pInputCombAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqCombActionInsert,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYORDER:
    {
      CThostFtdcQryOrderField *_pQryOrder = static_cast<CThostFtdcQryOrderField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryOrder(_pQryOrder, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryOrder,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYTRADE:
    {
      CThostFtdcQryTradeField *_pQryTrade = static_cast<CThostFtdcQryTradeField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryTrade(_pQryTrade, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryTrade,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINVESTORPOSITION:
    {
      CThostFtdcQryInvestorPositionField *_pQryInvestorPosition = static_cast<CThostFtdcQryInvestorPositionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInvestorPosition(_pQryInvestorPosition, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInvestorPosition,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYTRADINGACCOUNT:
    {
      CThostFtdcQryTradingAccountField *_pQryTradingAccount = static_cast<CThostFtdcQryTradingAccountField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryTradingAccount(_pQryTradingAccount, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryTradingAccount,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINVESTOR:
    {
      CThostFtdcQryInvestorField *_pQryInvestor = static_cast<CThostFtdcQryInvestorField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInvestor(_pQryInvestor, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInvestor,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYTRADINGCODE:
    {
      CThostFtdcQryTradingCodeField *_pQryTradingCode = static_cast<CThostFtdcQryTradingCodeField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryTradingCode(_pQryTradingCode, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryTradingCode,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINSTRUMENTMARGINRATE:
    {
      CThostFtdcQryInstrumentMarginRateField *_pQryInstrumentMarginRate = static_cast<CThostFtdcQryInstrumentMarginRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInstrumentMarginRate(_pQryInstrumentMarginRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInstrumentMarginRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINSTRUMENTCOMMISSIONRATE:
    {
      CThostFtdcQryInstrumentCommissionRateField *_pQryInstrumentCommissionRate = static_cast<CThostFtdcQryInstrumentCommissionRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInstrumentCommissionRate(_pQryInstrumentCommissionRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInstrumentCommissionRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYEXCHANGE:
    {
      CThostFtdcQryExchangeField *_pQryExchange = static_cast<CThostFtdcQryExchangeField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryExchange(_pQryExchange, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryExchange,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYPRODUCT:
    {
      CThostFtdcQryProductField *_pQryProduct = static_cast<CThostFtdcQryProductField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryProduct(_pQryProduct, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryProduct,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINSTRUMENT:
    {
      CThostFtdcQryInstrumentField *_pQryInstrument = static_cast<CThostFtdcQryInstrumentField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInstrument(_pQryInstrument, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInstrument,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYDEPTHMARKETDATA:
    {
      CThostFtdcQryDepthMarketDataField *_pQryDepthMarketData = static_cast<CThostFtdcQryDepthMarketDataField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryDepthMarketData(_pQryDepthMarketData, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryDepthMarketData,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYSETTLEMENTINFO:
    {
      CThostFtdcQrySettlementInfoField *_pQrySettlementInfo = static_cast<CThostFtdcQrySettlementInfoField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQrySettlementInfo(_pQrySettlementInfo, baton->iRequestID);
      logger_cout(log.append("invoke ReqQrySettlementInfo,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYTRANSFERBANK:
    {
      CThostFtdcQryTransferBankField *_pQryTransferBank = static_cast<CThostFtdcQryTransferBankField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryTransferBank(_pQryTransferBank, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryTransferBank,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINVESTORPOSITIONDETAIL:
    {
      CThostFtdcQryInvestorPositionDetailField *_pQryInvestorPositionDetail = static_cast<CThostFtdcQryInvestorPositionDetailField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInvestorPositionDetail(_pQryInvestorPositionDetail, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInvestorPositionDetail,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYNOTICE:
    {
      CThostFtdcQryNoticeField *_pQryNotice = static_cast<CThostFtdcQryNoticeField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryNotice(_pQryNotice, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryNotice,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYSETTLEMENTINFOCONFIRM:
    {
      CThostFtdcQrySettlementInfoConfirmField *_pQrySettlementInfoConfirm = static_cast<CThostFtdcQrySettlementInfoConfirmField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQrySettlementInfoConfirm(_pQrySettlementInfoConfirm, baton->iRequestID);
      logger_cout(log.append("invoke ReqQrySettlementInfoConfirm,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINVESTORPOSITIONCOMBINEDETAIL:
    {
      CThostFtdcQryInvestorPositionCombineDetailField *_pQryInvestorPositionCombineDetail = static_cast<CThostFtdcQryInvestorPositionCombineDetailField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInvestorPositionCombineDetail(_pQryInvestorPositionCombineDetail, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInvestorPositionCombineDetail,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYCFMMCTRADINGACCOUNTKEY:
    {
      CThostFtdcQryCFMMCTradingAccountKeyField *_pQryCFMMCTradingAccountKey = static_cast<CThostFtdcQryCFMMCTradingAccountKeyField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryCFMMCTradingAccountKey(_pQryCFMMCTradingAccountKey, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryCFMMCTradingAccountKey,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYEWARRANTOFFSET:
    {
      CThostFtdcQryEWarrantOffsetField *_pQryEWarrantOffset = static_cast<CThostFtdcQryEWarrantOffsetField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryEWarrantOffset(_pQryEWarrantOffset, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryEWarrantOffset,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINVESTORPRODUCTGROUPMARGIN:
    {
      CThostFtdcQryInvestorProductGroupMarginField *_pQryInvestorProductGroupMargin = static_cast<CThostFtdcQryInvestorProductGroupMarginField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInvestorProductGroupMargin(_pQryInvestorProductGroupMargin, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInvestorProductGroupMargin,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYEXCHANGEMARGINRATE:
    {
      CThostFtdcQryExchangeMarginRateField *_pQryExchangeMarginRate = static_cast<CThostFtdcQryExchangeMarginRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryExchangeMarginRate(_pQryExchangeMarginRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryExchangeMarginRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYEXCHANGEMARGINRATEADJUST:
    {
      CThostFtdcQryExchangeMarginRateAdjustField *_pQryExchangeMarginRateAdjust = static_cast<CThostFtdcQryExchangeMarginRateAdjustField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryExchangeMarginRateAdjust(_pQryExchangeMarginRateAdjust, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryExchangeMarginRateAdjust,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYEXCHANGERATE:
    {
      CThostFtdcQryExchangeRateField *_pQryExchangeRate = static_cast<CThostFtdcQryExchangeRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryExchangeRate(_pQryExchangeRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryExchangeRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYSECAGENTACIDMAP:
    {
      CThostFtdcQrySecAgentACIDMapField *_pQrySecAgentACIDMap = static_cast<CThostFtdcQrySecAgentACIDMapField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQrySecAgentACIDMap(_pQrySecAgentACIDMap, baton->iRequestID);
      logger_cout(log.append("invoke ReqQrySecAgentACIDMap,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYPRODUCTEXCHRATE:
    {
      CThostFtdcQryProductExchRateField *_pQryProductExchRate = static_cast<CThostFtdcQryProductExchRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryProductExchRate(_pQryProductExchRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryProductExchRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYPRODUCTGROUP:
    {
      CThostFtdcQryProductGroupField *_pQryProductGroup = static_cast<CThostFtdcQryProductGroupField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryProductGroup(_pQryProductGroup, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryProductGroup,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYMMINSTRUMENTCOMMISSIONRATE:
    {
      CThostFtdcQryMMInstrumentCommissionRateField *_pQryMMInstrumentCommissionRate = static_cast<CThostFtdcQryMMInstrumentCommissionRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryMMInstrumentCommissionRate(_pQryMMInstrumentCommissionRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryMMInstrumentCommissionRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYMMOPTIONINSTRCOMMRATE:
    {
      CThostFtdcQryMMOptionInstrCommRateField *_pQryMMOptionInstrCommRate = static_cast<CThostFtdcQryMMOptionInstrCommRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryMMOptionInstrCommRate(_pQryMMOptionInstrCommRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryMMOptionInstrCommRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINSTRUMENTORDERCOMMRATE:
    {
      CThostFtdcQryInstrumentOrderCommRateField *_pQryInstrumentOrderCommRate = static_cast<CThostFtdcQryInstrumentOrderCommRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInstrumentOrderCommRate(_pQryInstrumentOrderCommRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInstrumentOrderCommRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYSECAGENTTRADINGACCOUNT:
    {
      CThostFtdcQryTradingAccountField *_pQryTradingAccount = static_cast<CThostFtdcQryTradingAccountField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQrySecAgentTradingAccount(_pQryTradingAccount, baton->iRequestID);
      logger_cout(log.append("invoke ReqQrySecAgentTradingAccount,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYSECAGENTCHECKMODE:
    {
      CThostFtdcQrySecAgentCheckModeField *_pQrySecAgentCheckMode = static_cast<CThostFtdcQrySecAgentCheckModeField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQrySecAgentCheckMode(_pQrySecAgentCheckMode, baton->iRequestID);
      logger_cout(log.append("invoke ReqQrySecAgentCheckMode,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYOPTIONINSTRTRADECOST:
    {
      CThostFtdcQryOptionInstrTradeCostField *_pQryOptionInstrTradeCost = static_cast<CThostFtdcQryOptionInstrTradeCostField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryOptionInstrTradeCost(_pQryOptionInstrTradeCost, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryOptionInstrTradeCost,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYOPTIONINSTRCOMMRATE:
    {
      CThostFtdcQryOptionInstrCommRateField *_pQryOptionInstrCommRate = static_cast<CThostFtdcQryOptionInstrCommRateField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryOptionInstrCommRate(_pQryOptionInstrCommRate, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryOptionInstrCommRate,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYEXECORDER:
    {
      CThostFtdcQryExecOrderField *_pQryExecOrder = static_cast<CThostFtdcQryExecOrderField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryExecOrder(_pQryExecOrder, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryExecOrder,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYFORQUOTE:
    {
      CThostFtdcQryForQuoteField *_pQryForQuote = static_cast<CThostFtdcQryForQuoteField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryForQuote(_pQryForQuote, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryForQuote,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYQUOTE:
    {
      CThostFtdcQryQuoteField *_pQryQuote = static_cast<CThostFtdcQryQuoteField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryQuote(_pQryQuote, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryQuote,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYOPTIONSELFCLOSE:
    {
      CThostFtdcQryOptionSelfCloseField *_pQryOptionSelfClose = static_cast<CThostFtdcQryOptionSelfCloseField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryOptionSelfClose(_pQryOptionSelfClose, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryOptionSelfClose,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYINVESTUNIT:
    {
      CThostFtdcQryInvestUnitField *_pQryInvestUnit = static_cast<CThostFtdcQryInvestUnitField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryInvestUnit(_pQryInvestUnit, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryInvestUnit,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYCOMBINSTRUMENTGUARD:
    {
      CThostFtdcQryCombInstrumentGuardField *_pQryCombInstrumentGuard = static_cast<CThostFtdcQryCombInstrumentGuardField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryCombInstrumentGuard(_pQryCombInstrumentGuard, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryCombInstrumentGuard,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYCOMBACTION:
    {
      CThostFtdcQryCombActionField *_pQryCombAction = static_cast<CThostFtdcQryCombActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryCombAction(_pQryCombAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryCombAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYTRANSFERSERIAL:
    {
      CThostFtdcQryTransferSerialField *_pQryTransferSerial = static_cast<CThostFtdcQryTransferSerialField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryTransferSerial(_pQryTransferSerial, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryTransferSerial,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYACCOUNTREGISTER:
    {
      CThostFtdcQryAccountregisterField *_pQryAccountregister = static_cast<CThostFtdcQryAccountregisterField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryAccountregister(_pQryAccountregister, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryAccountregister,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYCONTRACTBANK:
    {
      CThostFtdcQryContractBankField *_pQryContractBank = static_cast<CThostFtdcQryContractBankField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryContractBank(_pQryContractBank, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryContractBank,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYPARKEDORDER:
    {
      CThostFtdcQryParkedOrderField *_pQryParkedOrder = static_cast<CThostFtdcQryParkedOrderField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryParkedOrder(_pQryParkedOrder, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryParkedOrder,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYPARKEDORDERACTION:
    {
      CThostFtdcQryParkedOrderActionField *_pQryParkedOrderAction = static_cast<CThostFtdcQryParkedOrderActionField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryParkedOrderAction(_pQryParkedOrderAction, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryParkedOrderAction,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYTRADINGNOTICE:
    {
      CThostFtdcQryTradingNoticeField *_pQryTradingNotice = static_cast<CThostFtdcQryTradingNoticeField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryTradingNotice(_pQryTradingNotice, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryTradingNotice,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYBROKERTRADINGPARAMS:
    {
      CThostFtdcQryBrokerTradingParamsField *_pQryBrokerTradingParams = static_cast<CThostFtdcQryBrokerTradingParamsField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryBrokerTradingParams(_pQryBrokerTradingParams, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryBrokerTradingParams,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQRYBROKERTRADINGALGOS:
    {
      CThostFtdcQryBrokerTradingAlgosField *_pQryBrokerTradingAlgos = static_cast<CThostFtdcQryBrokerTradingAlgosField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQryBrokerTradingAlgos(_pQryBrokerTradingAlgos, baton->iRequestID);
      logger_cout(log.append("invoke ReqQryBrokerTradingAlgos,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQUERYCFMMCTRADINGACCOUNTTOKEN:
    {
      CThostFtdcQueryCFMMCTradingAccountTokenField *_pQueryCFMMCTradingAccountToken = static_cast<CThostFtdcQueryCFMMCTradingAccountTokenField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQueryCFMMCTradingAccountToken(_pQueryCFMMCTradingAccountToken, baton->iRequestID);
      logger_cout(log.append("invoke ReqQueryCFMMCTradingAccountToken,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQFROMBANKTOFUTUREBYFUTURE:
    {
      CThostFtdcReqTransferField *_pReqTransfer = static_cast<CThostFtdcReqTransferField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqFromBankToFutureByFuture(_pReqTransfer, baton->iRequestID);
      logger_cout(log.append("invoke ReqFromBankToFutureByFuture,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQFROMFUTURETOBANKBYFUTURE:
    {
      CThostFtdcReqTransferField *_pReqTransfer = static_cast<CThostFtdcReqTransferField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqFromFutureToBankByFuture(_pReqTransfer, baton->iRequestID);
      logger_cout(log.append("invoke ReqFromFutureToBankByFuture,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  case T_REQQUERYBANKACCOUNTMONEYBYFUTURE:
    {
      CThostFtdcReqQueryAccountField *_pReqQueryAccount = static_cast<CThostFtdcReqQueryAccountField*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->ReqQueryBankAccountMoneyByFuture(_pReqQueryAccount, baton->iRequestID);
      logger_cout(log.append("invoke ReqQueryBankAccountMoneyByFuture,the result:").append(to_string(baton->nResult)).c_str());
      break;
    }

  default:
    {
      logger_cout(log.append("No case event:").append(to_string(baton->fun)).c_str());
      break;
    }
  }
}

void uv_trader::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcReqAuthenticateField *_pReqAuthenticateField = new CThostFtdcReqAuthenticateField();
  memcpy(_pReqAuthenticateField, pReqAuthenticateField, sizeof(CThostFtdcReqAuthenticateField));
  this->invoke(_pReqAuthenticateField, T_REQAUTHENTICATE, callback, nRequestID);
}

void uv_trader::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcReqUserLoginField *_pReqUserLoginField = new CThostFtdcReqUserLoginField();
  memcpy(_pReqUserLoginField, pReqUserLoginField, sizeof(CThostFtdcReqUserLoginField));
  this->invoke(_pReqUserLoginField, T_REQUSERLOGIN, callback, nRequestID);
}

void uv_trader::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcUserLogoutField *_pUserLogout = new CThostFtdcUserLogoutField();
  memcpy(_pUserLogout, pUserLogout, sizeof(CThostFtdcUserLogoutField));
  this->invoke(_pUserLogout, T_REQUSERLOGOUT, callback, nRequestID);
}

void uv_trader::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcUserPasswordUpdateField *_pUserPasswordUpdate = new CThostFtdcUserPasswordUpdateField();
  memcpy(_pUserPasswordUpdate, pUserPasswordUpdate, sizeof(CThostFtdcUserPasswordUpdateField));
  this->invoke(_pUserPasswordUpdate, T_REQUSERPASSWORDUPDATE, callback, nRequestID);
}

void uv_trader::ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcTradingAccountPasswordUpdateField *_pTradingAccountPasswordUpdate = new CThostFtdcTradingAccountPasswordUpdateField();
  memcpy(_pTradingAccountPasswordUpdate, pTradingAccountPasswordUpdate, sizeof(CThostFtdcTradingAccountPasswordUpdateField));
  this->invoke(_pTradingAccountPasswordUpdate, T_REQTRADINGACCOUNTPASSWORDUPDATE, callback, nRequestID);
}

void uv_trader::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputOrderField *_pInputOrder = new CThostFtdcInputOrderField();
  memcpy(_pInputOrder, pInputOrder, sizeof(CThostFtdcInputOrderField));
  this->invoke(_pInputOrder, T_REQORDERINSERT, callback, nRequestID);
}

void uv_trader::ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcParkedOrderField *_pParkedOrder = new CThostFtdcParkedOrderField();
  memcpy(_pParkedOrder, pParkedOrder, sizeof(CThostFtdcParkedOrderField));
  this->invoke(_pParkedOrder, T_REQPARKEDORDERINSERT, callback, nRequestID);
}

void uv_trader::ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcParkedOrderActionField *_pParkedOrderAction = new CThostFtdcParkedOrderActionField();
  memcpy(_pParkedOrderAction, pParkedOrderAction, sizeof(CThostFtdcParkedOrderActionField));
  this->invoke(_pParkedOrderAction, T_REQPARKEDORDERACTION, callback, nRequestID);
}

void uv_trader::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputOrderActionField *_pInputOrderAction = new CThostFtdcInputOrderActionField();
  memcpy(_pInputOrderAction, pInputOrderAction, sizeof(CThostFtdcInputOrderActionField));
  this->invoke(_pInputOrderAction, T_REQORDERACTION, callback, nRequestID);
}

void uv_trader::ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQueryMaxOrderVolumeField *_pQueryMaxOrderVolume = new CThostFtdcQueryMaxOrderVolumeField();
  memcpy(_pQueryMaxOrderVolume, pQueryMaxOrderVolume, sizeof(CThostFtdcQueryMaxOrderVolumeField));
  this->invoke(_pQueryMaxOrderVolume, T_REQQUERYMAXORDERVOLUME, callback, nRequestID);
}

void uv_trader::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcSettlementInfoConfirmField *_pSettlementInfoConfirm = new CThostFtdcSettlementInfoConfirmField();
  memcpy(_pSettlementInfoConfirm, pSettlementInfoConfirm, sizeof(CThostFtdcSettlementInfoConfirmField));
  this->invoke(_pSettlementInfoConfirm, T_REQSETTLEMENTINFOCONFIRM, callback, nRequestID);
}

void uv_trader::ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcRemoveParkedOrderField *_pRemoveParkedOrder = new CThostFtdcRemoveParkedOrderField();
  memcpy(_pRemoveParkedOrder, pRemoveParkedOrder, sizeof(CThostFtdcRemoveParkedOrderField));
  this->invoke(_pRemoveParkedOrder, T_REQREMOVEPARKEDORDER, callback, nRequestID);
}

void uv_trader::ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcRemoveParkedOrderActionField *_pRemoveParkedOrderAction = new CThostFtdcRemoveParkedOrderActionField();
  memcpy(_pRemoveParkedOrderAction, pRemoveParkedOrderAction, sizeof(CThostFtdcRemoveParkedOrderActionField));
  this->invoke(_pRemoveParkedOrderAction, T_REQREMOVEPARKEDORDERACTION, callback, nRequestID);
}

void uv_trader::ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputExecOrderField *_pInputExecOrder = new CThostFtdcInputExecOrderField();
  memcpy(_pInputExecOrder, pInputExecOrder, sizeof(CThostFtdcInputExecOrderField));
  this->invoke(_pInputExecOrder, T_REQEXECORDERINSERT, callback, nRequestID);
}

void uv_trader::ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputExecOrderActionField *_pInputExecOrderAction = new CThostFtdcInputExecOrderActionField();
  memcpy(_pInputExecOrderAction, pInputExecOrderAction, sizeof(CThostFtdcInputExecOrderActionField));
  this->invoke(_pInputExecOrderAction, T_REQEXECORDERACTION, callback, nRequestID);
}

void uv_trader::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputForQuoteField *_pInputForQuote = new CThostFtdcInputForQuoteField();
  memcpy(_pInputForQuote, pInputForQuote, sizeof(CThostFtdcInputForQuoteField));
  this->invoke(_pInputForQuote, T_REQFORQUOTEINSERT, callback, nRequestID);
}

void uv_trader::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputQuoteField *_pInputQuote = new CThostFtdcInputQuoteField();
  memcpy(_pInputQuote, pInputQuote, sizeof(CThostFtdcInputQuoteField));
  this->invoke(_pInputQuote, T_REQQUOTEINSERT, callback, nRequestID);
}

void uv_trader::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputQuoteActionField *_pInputQuoteAction = new CThostFtdcInputQuoteActionField();
  memcpy(_pInputQuoteAction, pInputQuoteAction, sizeof(CThostFtdcInputQuoteActionField));
  this->invoke(_pInputQuoteAction, T_REQQUOTEACTION, callback, nRequestID);
}

void uv_trader::ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputBatchOrderActionField *_pInputBatchOrderAction = new CThostFtdcInputBatchOrderActionField();
  memcpy(_pInputBatchOrderAction, pInputBatchOrderAction, sizeof(CThostFtdcInputBatchOrderActionField));
  this->invoke(_pInputBatchOrderAction, T_REQBATCHORDERACTION, callback, nRequestID);
}

void uv_trader::ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputOptionSelfCloseField *_pInputOptionSelfClose = new CThostFtdcInputOptionSelfCloseField();
  memcpy(_pInputOptionSelfClose, pInputOptionSelfClose, sizeof(CThostFtdcInputOptionSelfCloseField));
  this->invoke(_pInputOptionSelfClose, T_REQOPTIONSELFCLOSEINSERT, callback, nRequestID);
}

void uv_trader::ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputOptionSelfCloseActionField *_pInputOptionSelfCloseAction = new CThostFtdcInputOptionSelfCloseActionField();
  memcpy(_pInputOptionSelfCloseAction, pInputOptionSelfCloseAction, sizeof(CThostFtdcInputOptionSelfCloseActionField));
  this->invoke(_pInputOptionSelfCloseAction, T_REQOPTIONSELFCLOSEACTION, callback, nRequestID);
}

void uv_trader::ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcInputCombActionField *_pInputCombAction = new CThostFtdcInputCombActionField();
  memcpy(_pInputCombAction, pInputCombAction, sizeof(CThostFtdcInputCombActionField));
  this->invoke(_pInputCombAction, T_REQCOMBACTIONINSERT, callback, nRequestID);
}

void uv_trader::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryOrderField *_pQryOrder = new CThostFtdcQryOrderField();
  memcpy(_pQryOrder, pQryOrder, sizeof(CThostFtdcQryOrderField));
  this->invoke(_pQryOrder, T_REQQRYORDER, callback, nRequestID);
}

void uv_trader::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryTradeField *_pQryTrade = new CThostFtdcQryTradeField();
  memcpy(_pQryTrade, pQryTrade, sizeof(CThostFtdcQryTradeField));
  this->invoke(_pQryTrade, T_REQQRYTRADE, callback, nRequestID);
}

void uv_trader::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInvestorPositionField *_pQryInvestorPosition = new CThostFtdcQryInvestorPositionField();
  memcpy(_pQryInvestorPosition, pQryInvestorPosition, sizeof(CThostFtdcQryInvestorPositionField));
  this->invoke(_pQryInvestorPosition, T_REQQRYINVESTORPOSITION, callback, nRequestID);
}

void uv_trader::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryTradingAccountField *_pQryTradingAccount = new CThostFtdcQryTradingAccountField();
  memcpy(_pQryTradingAccount, pQryTradingAccount, sizeof(CThostFtdcQryTradingAccountField));
  this->invoke(_pQryTradingAccount, T_REQQRYTRADINGACCOUNT, callback, nRequestID);
}

void uv_trader::ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInvestorField *_pQryInvestor = new CThostFtdcQryInvestorField();
  memcpy(_pQryInvestor, pQryInvestor, sizeof(CThostFtdcQryInvestorField));
  this->invoke(_pQryInvestor, T_REQQRYINVESTOR, callback, nRequestID);
}

void uv_trader::ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryTradingCodeField *_pQryTradingCode = new CThostFtdcQryTradingCodeField();
  memcpy(_pQryTradingCode, pQryTradingCode, sizeof(CThostFtdcQryTradingCodeField));
  this->invoke(_pQryTradingCode, T_REQQRYTRADINGCODE, callback, nRequestID);
}

void uv_trader::ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInstrumentMarginRateField *_pQryInstrumentMarginRate = new CThostFtdcQryInstrumentMarginRateField();
  memcpy(_pQryInstrumentMarginRate, pQryInstrumentMarginRate, sizeof(CThostFtdcQryInstrumentMarginRateField));
  this->invoke(_pQryInstrumentMarginRate, T_REQQRYINSTRUMENTMARGINRATE, callback, nRequestID);
}

void uv_trader::ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInstrumentCommissionRateField *_pQryInstrumentCommissionRate = new CThostFtdcQryInstrumentCommissionRateField();
  memcpy(_pQryInstrumentCommissionRate, pQryInstrumentCommissionRate, sizeof(CThostFtdcQryInstrumentCommissionRateField));
  this->invoke(_pQryInstrumentCommissionRate, T_REQQRYINSTRUMENTCOMMISSIONRATE, callback, nRequestID);
}

void uv_trader::ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryExchangeField *_pQryExchange = new CThostFtdcQryExchangeField();
  memcpy(_pQryExchange, pQryExchange, sizeof(CThostFtdcQryExchangeField));
  this->invoke(_pQryExchange, T_REQQRYEXCHANGE, callback, nRequestID);
}

void uv_trader::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryProductField *_pQryProduct = new CThostFtdcQryProductField();
  memcpy(_pQryProduct, pQryProduct, sizeof(CThostFtdcQryProductField));
  this->invoke(_pQryProduct, T_REQQRYPRODUCT, callback, nRequestID);
}

void uv_trader::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInstrumentField *_pQryInstrument = new CThostFtdcQryInstrumentField();
  memcpy(_pQryInstrument, pQryInstrument, sizeof(CThostFtdcQryInstrumentField));
  this->invoke(_pQryInstrument, T_REQQRYINSTRUMENT, callback, nRequestID);
}

void uv_trader::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryDepthMarketDataField *_pQryDepthMarketData = new CThostFtdcQryDepthMarketDataField();
  memcpy(_pQryDepthMarketData, pQryDepthMarketData, sizeof(CThostFtdcQryDepthMarketDataField));
  this->invoke(_pQryDepthMarketData, T_REQQRYDEPTHMARKETDATA, callback, nRequestID);
}

void uv_trader::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQrySettlementInfoField *_pQrySettlementInfo = new CThostFtdcQrySettlementInfoField();
  memcpy(_pQrySettlementInfo, pQrySettlementInfo, sizeof(CThostFtdcQrySettlementInfoField));
  this->invoke(_pQrySettlementInfo, T_REQQRYSETTLEMENTINFO, callback, nRequestID);
}

void uv_trader::ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryTransferBankField *_pQryTransferBank = new CThostFtdcQryTransferBankField();
  memcpy(_pQryTransferBank, pQryTransferBank, sizeof(CThostFtdcQryTransferBankField));
  this->invoke(_pQryTransferBank, T_REQQRYTRANSFERBANK, callback, nRequestID);
}

void uv_trader::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInvestorPositionDetailField *_pQryInvestorPositionDetail = new CThostFtdcQryInvestorPositionDetailField();
  memcpy(_pQryInvestorPositionDetail, pQryInvestorPositionDetail, sizeof(CThostFtdcQryInvestorPositionDetailField));
  this->invoke(_pQryInvestorPositionDetail, T_REQQRYINVESTORPOSITIONDETAIL, callback, nRequestID);
}

void uv_trader::ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryNoticeField *_pQryNotice = new CThostFtdcQryNoticeField();
  memcpy(_pQryNotice, pQryNotice, sizeof(CThostFtdcQryNoticeField));
  this->invoke(_pQryNotice, T_REQQRYNOTICE, callback, nRequestID);
}

void uv_trader::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQrySettlementInfoConfirmField *_pQrySettlementInfoConfirm = new CThostFtdcQrySettlementInfoConfirmField();
  memcpy(_pQrySettlementInfoConfirm, pQrySettlementInfoConfirm, sizeof(CThostFtdcQrySettlementInfoConfirmField));
  this->invoke(_pQrySettlementInfoConfirm, T_REQQRYSETTLEMENTINFOCONFIRM, callback, nRequestID);
}

void uv_trader::ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInvestorPositionCombineDetailField *_pQryInvestorPositionCombineDetail = new CThostFtdcQryInvestorPositionCombineDetailField();
  memcpy(_pQryInvestorPositionCombineDetail, pQryInvestorPositionCombineDetail, sizeof(CThostFtdcQryInvestorPositionCombineDetailField));
  this->invoke(_pQryInvestorPositionCombineDetail, T_REQQRYINVESTORPOSITIONCOMBINEDETAIL, callback, nRequestID);
}

void uv_trader::ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryCFMMCTradingAccountKeyField *_pQryCFMMCTradingAccountKey = new CThostFtdcQryCFMMCTradingAccountKeyField();
  memcpy(_pQryCFMMCTradingAccountKey, pQryCFMMCTradingAccountKey, sizeof(CThostFtdcQryCFMMCTradingAccountKeyField));
  this->invoke(_pQryCFMMCTradingAccountKey, T_REQQRYCFMMCTRADINGACCOUNTKEY, callback, nRequestID);
}

void uv_trader::ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryEWarrantOffsetField *_pQryEWarrantOffset = new CThostFtdcQryEWarrantOffsetField();
  memcpy(_pQryEWarrantOffset, pQryEWarrantOffset, sizeof(CThostFtdcQryEWarrantOffsetField));
  this->invoke(_pQryEWarrantOffset, T_REQQRYEWARRANTOFFSET, callback, nRequestID);
}

void uv_trader::ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInvestorProductGroupMarginField *_pQryInvestorProductGroupMargin = new CThostFtdcQryInvestorProductGroupMarginField();
  memcpy(_pQryInvestorProductGroupMargin, pQryInvestorProductGroupMargin, sizeof(CThostFtdcQryInvestorProductGroupMarginField));
  this->invoke(_pQryInvestorProductGroupMargin, T_REQQRYINVESTORPRODUCTGROUPMARGIN, callback, nRequestID);
}

void uv_trader::ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryExchangeMarginRateField *_pQryExchangeMarginRate = new CThostFtdcQryExchangeMarginRateField();
  memcpy(_pQryExchangeMarginRate, pQryExchangeMarginRate, sizeof(CThostFtdcQryExchangeMarginRateField));
  this->invoke(_pQryExchangeMarginRate, T_REQQRYEXCHANGEMARGINRATE, callback, nRequestID);
}

void uv_trader::ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryExchangeMarginRateAdjustField *_pQryExchangeMarginRateAdjust = new CThostFtdcQryExchangeMarginRateAdjustField();
  memcpy(_pQryExchangeMarginRateAdjust, pQryExchangeMarginRateAdjust, sizeof(CThostFtdcQryExchangeMarginRateAdjustField));
  this->invoke(_pQryExchangeMarginRateAdjust, T_REQQRYEXCHANGEMARGINRATEADJUST, callback, nRequestID);
}

void uv_trader::ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryExchangeRateField *_pQryExchangeRate = new CThostFtdcQryExchangeRateField();
  memcpy(_pQryExchangeRate, pQryExchangeRate, sizeof(CThostFtdcQryExchangeRateField));
  this->invoke(_pQryExchangeRate, T_REQQRYEXCHANGERATE, callback, nRequestID);
}

void uv_trader::ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQrySecAgentACIDMapField *_pQrySecAgentACIDMap = new CThostFtdcQrySecAgentACIDMapField();
  memcpy(_pQrySecAgentACIDMap, pQrySecAgentACIDMap, sizeof(CThostFtdcQrySecAgentACIDMapField));
  this->invoke(_pQrySecAgentACIDMap, T_REQQRYSECAGENTACIDMAP, callback, nRequestID);
}

void uv_trader::ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryProductExchRateField *_pQryProductExchRate = new CThostFtdcQryProductExchRateField();
  memcpy(_pQryProductExchRate, pQryProductExchRate, sizeof(CThostFtdcQryProductExchRateField));
  this->invoke(_pQryProductExchRate, T_REQQRYPRODUCTEXCHRATE, callback, nRequestID);
}

void uv_trader::ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryProductGroupField *_pQryProductGroup = new CThostFtdcQryProductGroupField();
  memcpy(_pQryProductGroup, pQryProductGroup, sizeof(CThostFtdcQryProductGroupField));
  this->invoke(_pQryProductGroup, T_REQQRYPRODUCTGROUP, callback, nRequestID);
}

void uv_trader::ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryMMInstrumentCommissionRateField *_pQryMMInstrumentCommissionRate = new CThostFtdcQryMMInstrumentCommissionRateField();
  memcpy(_pQryMMInstrumentCommissionRate, pQryMMInstrumentCommissionRate, sizeof(CThostFtdcQryMMInstrumentCommissionRateField));
  this->invoke(_pQryMMInstrumentCommissionRate, T_REQQRYMMINSTRUMENTCOMMISSIONRATE, callback, nRequestID);
}

void uv_trader::ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryMMOptionInstrCommRateField *_pQryMMOptionInstrCommRate = new CThostFtdcQryMMOptionInstrCommRateField();
  memcpy(_pQryMMOptionInstrCommRate, pQryMMOptionInstrCommRate, sizeof(CThostFtdcQryMMOptionInstrCommRateField));
  this->invoke(_pQryMMOptionInstrCommRate, T_REQQRYMMOPTIONINSTRCOMMRATE, callback, nRequestID);
}

void uv_trader::ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInstrumentOrderCommRateField *_pQryInstrumentOrderCommRate = new CThostFtdcQryInstrumentOrderCommRateField();
  memcpy(_pQryInstrumentOrderCommRate, pQryInstrumentOrderCommRate, sizeof(CThostFtdcQryInstrumentOrderCommRateField));
  this->invoke(_pQryInstrumentOrderCommRate, T_REQQRYINSTRUMENTORDERCOMMRATE, callback, nRequestID);
}

void uv_trader::ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryTradingAccountField *_pQryTradingAccount = new CThostFtdcQryTradingAccountField();
  memcpy(_pQryTradingAccount, pQryTradingAccount, sizeof(CThostFtdcQryTradingAccountField));
  this->invoke(_pQryTradingAccount, T_REQQRYSECAGENTTRADINGACCOUNT, callback, nRequestID);
}

void uv_trader::ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQrySecAgentCheckModeField *_pQrySecAgentCheckMode = new CThostFtdcQrySecAgentCheckModeField();
  memcpy(_pQrySecAgentCheckMode, pQrySecAgentCheckMode, sizeof(CThostFtdcQrySecAgentCheckModeField));
  this->invoke(_pQrySecAgentCheckMode, T_REQQRYSECAGENTCHECKMODE, callback, nRequestID);
}

void uv_trader::ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryOptionInstrTradeCostField *_pQryOptionInstrTradeCost = new CThostFtdcQryOptionInstrTradeCostField();
  memcpy(_pQryOptionInstrTradeCost, pQryOptionInstrTradeCost, sizeof(CThostFtdcQryOptionInstrTradeCostField));
  this->invoke(_pQryOptionInstrTradeCost, T_REQQRYOPTIONINSTRTRADECOST, callback, nRequestID);
}

void uv_trader::ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryOptionInstrCommRateField *_pQryOptionInstrCommRate = new CThostFtdcQryOptionInstrCommRateField();
  memcpy(_pQryOptionInstrCommRate, pQryOptionInstrCommRate, sizeof(CThostFtdcQryOptionInstrCommRateField));
  this->invoke(_pQryOptionInstrCommRate, T_REQQRYOPTIONINSTRCOMMRATE, callback, nRequestID);
}

void uv_trader::ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryExecOrderField *_pQryExecOrder = new CThostFtdcQryExecOrderField();
  memcpy(_pQryExecOrder, pQryExecOrder, sizeof(CThostFtdcQryExecOrderField));
  this->invoke(_pQryExecOrder, T_REQQRYEXECORDER, callback, nRequestID);
}

void uv_trader::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryForQuoteField *_pQryForQuote = new CThostFtdcQryForQuoteField();
  memcpy(_pQryForQuote, pQryForQuote, sizeof(CThostFtdcQryForQuoteField));
  this->invoke(_pQryForQuote, T_REQQRYFORQUOTE, callback, nRequestID);
}

void uv_trader::ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryQuoteField *_pQryQuote = new CThostFtdcQryQuoteField();
  memcpy(_pQryQuote, pQryQuote, sizeof(CThostFtdcQryQuoteField));
  this->invoke(_pQryQuote, T_REQQRYQUOTE, callback, nRequestID);
}

void uv_trader::ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryOptionSelfCloseField *_pQryOptionSelfClose = new CThostFtdcQryOptionSelfCloseField();
  memcpy(_pQryOptionSelfClose, pQryOptionSelfClose, sizeof(CThostFtdcQryOptionSelfCloseField));
  this->invoke(_pQryOptionSelfClose, T_REQQRYOPTIONSELFCLOSE, callback, nRequestID);
}

void uv_trader::ReqQryInvestUnit(CThostFtdcQryInvestUnitField *pQryInvestUnit, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryInvestUnitField *_pQryInvestUnit = new CThostFtdcQryInvestUnitField();
  memcpy(_pQryInvestUnit, pQryInvestUnit, sizeof(CThostFtdcQryInvestUnitField));
  this->invoke(_pQryInvestUnit, T_REQQRYINVESTUNIT, callback, nRequestID);
}

void uv_trader::ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryCombInstrumentGuardField *_pQryCombInstrumentGuard = new CThostFtdcQryCombInstrumentGuardField();
  memcpy(_pQryCombInstrumentGuard, pQryCombInstrumentGuard, sizeof(CThostFtdcQryCombInstrumentGuardField));
  this->invoke(_pQryCombInstrumentGuard, T_REQQRYCOMBINSTRUMENTGUARD, callback, nRequestID);
}

void uv_trader::ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryCombActionField *_pQryCombAction = new CThostFtdcQryCombActionField();
  memcpy(_pQryCombAction, pQryCombAction, sizeof(CThostFtdcQryCombActionField));
  this->invoke(_pQryCombAction, T_REQQRYCOMBACTION, callback, nRequestID);
}

void uv_trader::ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryTransferSerialField *_pQryTransferSerial = new CThostFtdcQryTransferSerialField();
  memcpy(_pQryTransferSerial, pQryTransferSerial, sizeof(CThostFtdcQryTransferSerialField));
  this->invoke(_pQryTransferSerial, T_REQQRYTRANSFERSERIAL, callback, nRequestID);
}

void uv_trader::ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryAccountregisterField *_pQryAccountregister = new CThostFtdcQryAccountregisterField();
  memcpy(_pQryAccountregister, pQryAccountregister, sizeof(CThostFtdcQryAccountregisterField));
  this->invoke(_pQryAccountregister, T_REQQRYACCOUNTREGISTER, callback, nRequestID);
}

void uv_trader::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryContractBankField *_pQryContractBank = new CThostFtdcQryContractBankField();
  memcpy(_pQryContractBank, pQryContractBank, sizeof(CThostFtdcQryContractBankField));
  this->invoke(_pQryContractBank, T_REQQRYCONTRACTBANK, callback, nRequestID);
}

void uv_trader::ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryParkedOrderField *_pQryParkedOrder = new CThostFtdcQryParkedOrderField();
  memcpy(_pQryParkedOrder, pQryParkedOrder, sizeof(CThostFtdcQryParkedOrderField));
  this->invoke(_pQryParkedOrder, T_REQQRYPARKEDORDER, callback, nRequestID);
}

void uv_trader::ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryParkedOrderActionField *_pQryParkedOrderAction = new CThostFtdcQryParkedOrderActionField();
  memcpy(_pQryParkedOrderAction, pQryParkedOrderAction, sizeof(CThostFtdcQryParkedOrderActionField));
  this->invoke(_pQryParkedOrderAction, T_REQQRYPARKEDORDERACTION, callback, nRequestID);
}

void uv_trader::ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryTradingNoticeField *_pQryTradingNotice = new CThostFtdcQryTradingNoticeField();
  memcpy(_pQryTradingNotice, pQryTradingNotice, sizeof(CThostFtdcQryTradingNoticeField));
  this->invoke(_pQryTradingNotice, T_REQQRYTRADINGNOTICE, callback, nRequestID);
}

void uv_trader::ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryBrokerTradingParamsField *_pQryBrokerTradingParams = new CThostFtdcQryBrokerTradingParamsField();
  memcpy(_pQryBrokerTradingParams, pQryBrokerTradingParams, sizeof(CThostFtdcQryBrokerTradingParamsField));
  this->invoke(_pQryBrokerTradingParams, T_REQQRYBROKERTRADINGPARAMS, callback, nRequestID);
}

void uv_trader::ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQryBrokerTradingAlgosField *_pQryBrokerTradingAlgos = new CThostFtdcQryBrokerTradingAlgosField();
  memcpy(_pQryBrokerTradingAlgos, pQryBrokerTradingAlgos, sizeof(CThostFtdcQryBrokerTradingAlgosField));
  this->invoke(_pQryBrokerTradingAlgos, T_REQQRYBROKERTRADINGALGOS, callback, nRequestID);
}

void uv_trader::ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcQueryCFMMCTradingAccountTokenField *_pQueryCFMMCTradingAccountToken = new CThostFtdcQueryCFMMCTradingAccountTokenField();
  memcpy(_pQueryCFMMCTradingAccountToken, pQueryCFMMCTradingAccountToken, sizeof(CThostFtdcQueryCFMMCTradingAccountTokenField));
  this->invoke(_pQueryCFMMCTradingAccountToken, T_REQQUERYCFMMCTRADINGACCOUNTTOKEN, callback, nRequestID);
}

void uv_trader::ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcReqTransferField *_pReqTransfer = new CThostFtdcReqTransferField();
  memcpy(_pReqTransfer, pReqTransfer, sizeof(CThostFtdcReqTransferField));
  this->invoke(_pReqTransfer, T_REQFROMBANKTOFUTUREBYFUTURE, callback, nRequestID);
}

void uv_trader::ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcReqTransferField *_pReqTransfer = new CThostFtdcReqTransferField();
  memcpy(_pReqTransfer, pReqTransfer, sizeof(CThostFtdcReqTransferField));
  this->invoke(_pReqTransfer, T_REQFROMFUTURETOBANKBYFUTURE, callback, nRequestID);
}

void uv_trader::ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID, void(*callback)(int, void*)) {
  CThostFtdcReqQueryAccountField *_pReqQueryAccount = new CThostFtdcReqQueryAccountField();
  memcpy(_pReqQueryAccount, pReqQueryAccount, sizeof(CThostFtdcReqQueryAccountField));
  this->invoke(_pReqQueryAccount, T_REQQUERYBANKACCOUNTMONEYBYFUTURE, callback, nRequestID);
}
void uv_trader::OnFrontConnected() {

  logger_cout("uv_trader OnFrontConnected");
  CbRtnField* field = new CbRtnField();
  field->eFlag = T_ONFRONTCONNECTED;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
}

void uv_trader::OnFrontDisconnected(int nReason) {

  std::string log = "uv_trader OnFrontDisconnected------>";
  logger_cout(log.append("nReason:").append(to_string(nReason)).c_str());
  CbRtnField* field = new CbRtnField();
  field->eFlag = T_ONFRONTDISCONNECTED;
  field->nReason = nReason;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
}

void uv_trader::OnHeartBeatWarning(int nTimeLapse) {

  std::string log = "uv_trader OnHeartBeatWarning------>";
  logger_cout(log.append("nTimeLapse:").append(to_string(nTimeLapse)).c_str());
  CbRtnField* field = new CbRtnField();
  field->eFlag = T_ONHEARTBEATWARNING;
  field->nTimeLapse = nTimeLapse;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
}

void uv_trader::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspAuthenticate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcRspAuthenticateField* _pRspAuthenticateField = NULL;
  if (pRspAuthenticateField) {
    _pRspAuthenticateField = new CThostFtdcRspAuthenticateField();
    memcpy(_pRspAuthenticateField, pRspAuthenticateField, sizeof(CThostFtdcRspAuthenticateField));
  }
  on_invoke(T_ONRSPAUTHENTICATE, _pRspAuthenticateField, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspUserLogin------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcRspUserLoginField* _pRspUserLogin = NULL;
  if (pRspUserLogin) {
    _pRspUserLogin = new CThostFtdcRspUserLoginField();
    memcpy(_pRspUserLogin, pRspUserLogin, sizeof(CThostFtdcRspUserLoginField));
  }
  on_invoke(T_ONRSPUSERLOGIN, _pRspUserLogin, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspUserLogout------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcUserLogoutField* _pUserLogout = NULL;
  if (pUserLogout) {
    _pUserLogout = new CThostFtdcUserLogoutField();
    memcpy(_pUserLogout, pUserLogout, sizeof(CThostFtdcUserLogoutField));
  }
  on_invoke(T_ONRSPUSERLOGOUT, _pUserLogout, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspUserPasswordUpdate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcUserPasswordUpdateField* _pUserPasswordUpdate = NULL;
  if (pUserPasswordUpdate) {
    _pUserPasswordUpdate = new CThostFtdcUserPasswordUpdateField();
    memcpy(_pUserPasswordUpdate, pUserPasswordUpdate, sizeof(CThostFtdcUserPasswordUpdateField));
  }
  on_invoke(T_ONRSPUSERPASSWORDUPDATE, _pUserPasswordUpdate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspTradingAccountPasswordUpdate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTradingAccountPasswordUpdateField* _pTradingAccountPasswordUpdate = NULL;
  if (pTradingAccountPasswordUpdate) {
    _pTradingAccountPasswordUpdate = new CThostFtdcTradingAccountPasswordUpdateField();
    memcpy(_pTradingAccountPasswordUpdate, pTradingAccountPasswordUpdate, sizeof(CThostFtdcTradingAccountPasswordUpdateField));
  }
  on_invoke(T_ONRSPTRADINGACCOUNTPASSWORDUPDATE, _pTradingAccountPasswordUpdate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspOrderInsert------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputOrderField* _pInputOrder = NULL;
  if (pInputOrder) {
    _pInputOrder = new CThostFtdcInputOrderField();
    memcpy(_pInputOrder, pInputOrder, sizeof(CThostFtdcInputOrderField));
  }
  on_invoke(T_ONRSPORDERINSERT, _pInputOrder, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspParkedOrderInsert------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcParkedOrderField* _pParkedOrder = NULL;
  if (pParkedOrder) {
    _pParkedOrder = new CThostFtdcParkedOrderField();
    memcpy(_pParkedOrder, pParkedOrder, sizeof(CThostFtdcParkedOrderField));
  }
  on_invoke(T_ONRSPPARKEDORDERINSERT, _pParkedOrder, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspParkedOrderAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcParkedOrderActionField* _pParkedOrderAction = NULL;
  if (pParkedOrderAction) {
    _pParkedOrderAction = new CThostFtdcParkedOrderActionField();
    memcpy(_pParkedOrderAction, pParkedOrderAction, sizeof(CThostFtdcParkedOrderActionField));
  }
  on_invoke(T_ONRSPPARKEDORDERACTION, _pParkedOrderAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspOrderAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputOrderActionField* _pInputOrderAction = NULL;
  if (pInputOrderAction) {
    _pInputOrderAction = new CThostFtdcInputOrderActionField();
    memcpy(_pInputOrderAction, pInputOrderAction, sizeof(CThostFtdcInputOrderActionField));
  }
  on_invoke(T_ONRSPORDERACTION, _pInputOrderAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQueryMaxOrderVolume------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcQueryMaxOrderVolumeField* _pQueryMaxOrderVolume = NULL;
  if (pQueryMaxOrderVolume) {
    _pQueryMaxOrderVolume = new CThostFtdcQueryMaxOrderVolumeField();
    memcpy(_pQueryMaxOrderVolume, pQueryMaxOrderVolume, sizeof(CThostFtdcQueryMaxOrderVolumeField));
  }
  on_invoke(T_ONRSPQUERYMAXORDERVOLUME, _pQueryMaxOrderVolume, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspSettlementInfoConfirm------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcSettlementInfoConfirmField* _pSettlementInfoConfirm = NULL;
  if (pSettlementInfoConfirm) {
    _pSettlementInfoConfirm = new CThostFtdcSettlementInfoConfirmField();
    memcpy(_pSettlementInfoConfirm, pSettlementInfoConfirm, sizeof(CThostFtdcSettlementInfoConfirmField));
  }
  on_invoke(T_ONRSPSETTLEMENTINFOCONFIRM, _pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspRemoveParkedOrder------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcRemoveParkedOrderField* _pRemoveParkedOrder = NULL;
  if (pRemoveParkedOrder) {
    _pRemoveParkedOrder = new CThostFtdcRemoveParkedOrderField();
    memcpy(_pRemoveParkedOrder, pRemoveParkedOrder, sizeof(CThostFtdcRemoveParkedOrderField));
  }
  on_invoke(T_ONRSPREMOVEPARKEDORDER, _pRemoveParkedOrder, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspRemoveParkedOrderAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcRemoveParkedOrderActionField* _pRemoveParkedOrderAction = NULL;
  if (pRemoveParkedOrderAction) {
    _pRemoveParkedOrderAction = new CThostFtdcRemoveParkedOrderActionField();
    memcpy(_pRemoveParkedOrderAction, pRemoveParkedOrderAction, sizeof(CThostFtdcRemoveParkedOrderActionField));
  }
  on_invoke(T_ONRSPREMOVEPARKEDORDERACTION, _pRemoveParkedOrderAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspExecOrderInsert------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputExecOrderField* _pInputExecOrder = NULL;
  if (pInputExecOrder) {
    _pInputExecOrder = new CThostFtdcInputExecOrderField();
    memcpy(_pInputExecOrder, pInputExecOrder, sizeof(CThostFtdcInputExecOrderField));
  }
  on_invoke(T_ONRSPEXECORDERINSERT, _pInputExecOrder, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspExecOrderAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputExecOrderActionField* _pInputExecOrderAction = NULL;
  if (pInputExecOrderAction) {
    _pInputExecOrderAction = new CThostFtdcInputExecOrderActionField();
    memcpy(_pInputExecOrderAction, pInputExecOrderAction, sizeof(CThostFtdcInputExecOrderActionField));
  }
  on_invoke(T_ONRSPEXECORDERACTION, _pInputExecOrderAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspForQuoteInsert------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputForQuoteField* _pInputForQuote = NULL;
  if (pInputForQuote) {
    _pInputForQuote = new CThostFtdcInputForQuoteField();
    memcpy(_pInputForQuote, pInputForQuote, sizeof(CThostFtdcInputForQuoteField));
  }
  on_invoke(T_ONRSPFORQUOTEINSERT, _pInputForQuote, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQuoteInsert------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputQuoteField* _pInputQuote = NULL;
  if (pInputQuote) {
    _pInputQuote = new CThostFtdcInputQuoteField();
    memcpy(_pInputQuote, pInputQuote, sizeof(CThostFtdcInputQuoteField));
  }
  on_invoke(T_ONRSPQUOTEINSERT, _pInputQuote, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQuoteAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputQuoteActionField* _pInputQuoteAction = NULL;
  if (pInputQuoteAction) {
    _pInputQuoteAction = new CThostFtdcInputQuoteActionField();
    memcpy(_pInputQuoteAction, pInputQuoteAction, sizeof(CThostFtdcInputQuoteActionField));
  }
  on_invoke(T_ONRSPQUOTEACTION, _pInputQuoteAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspBatchOrderAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputBatchOrderActionField* _pInputBatchOrderAction = NULL;
  if (pInputBatchOrderAction) {
    _pInputBatchOrderAction = new CThostFtdcInputBatchOrderActionField();
    memcpy(_pInputBatchOrderAction, pInputBatchOrderAction, sizeof(CThostFtdcInputBatchOrderActionField));
  }
  on_invoke(T_ONRSPBATCHORDERACTION, _pInputBatchOrderAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspOptionSelfCloseInsert------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputOptionSelfCloseField* _pInputOptionSelfClose = NULL;
  if (pInputOptionSelfClose) {
    _pInputOptionSelfClose = new CThostFtdcInputOptionSelfCloseField();
    memcpy(_pInputOptionSelfClose, pInputOptionSelfClose, sizeof(CThostFtdcInputOptionSelfCloseField));
  }
  on_invoke(T_ONRSPOPTIONSELFCLOSEINSERT, _pInputOptionSelfClose, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspOptionSelfCloseAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputOptionSelfCloseActionField* _pInputOptionSelfCloseAction = NULL;
  if (pInputOptionSelfCloseAction) {
    _pInputOptionSelfCloseAction = new CThostFtdcInputOptionSelfCloseActionField();
    memcpy(_pInputOptionSelfCloseAction, pInputOptionSelfCloseAction, sizeof(CThostFtdcInputOptionSelfCloseActionField));
  }
  on_invoke(T_ONRSPOPTIONSELFCLOSEACTION, _pInputOptionSelfCloseAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspCombActionInsert------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInputCombActionField* _pInputCombAction = NULL;
  if (pInputCombAction) {
    _pInputCombAction = new CThostFtdcInputCombActionField();
    memcpy(_pInputCombAction, pInputCombAction, sizeof(CThostFtdcInputCombActionField));
  }
  on_invoke(T_ONRSPCOMBACTIONINSERT, _pInputCombAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryOrder------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcOrderField* _pOrder = NULL;
  if (pOrder) {
    _pOrder = new CThostFtdcOrderField();
    memcpy(_pOrder, pOrder, sizeof(CThostFtdcOrderField));
  }
  on_invoke(T_ONRSPQRYORDER, _pOrder, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryTrade------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTradeField* _pTrade = NULL;
  if (pTrade) {
    _pTrade = new CThostFtdcTradeField();
    memcpy(_pTrade, pTrade, sizeof(CThostFtdcTradeField));
  }
  on_invoke(T_ONRSPQRYTRADE, _pTrade, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInvestorPosition------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInvestorPositionField* _pInvestorPosition = NULL;
  if (pInvestorPosition) {
    _pInvestorPosition = new CThostFtdcInvestorPositionField();
    memcpy(_pInvestorPosition, pInvestorPosition, sizeof(CThostFtdcInvestorPositionField));
  }
  on_invoke(T_ONRSPQRYINVESTORPOSITION, _pInvestorPosition, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryTradingAccount------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTradingAccountField* _pTradingAccount = NULL;
  if (pTradingAccount) {
    _pTradingAccount = new CThostFtdcTradingAccountField();
    memcpy(_pTradingAccount, pTradingAccount, sizeof(CThostFtdcTradingAccountField));
  }
  on_invoke(T_ONRSPQRYTRADINGACCOUNT, _pTradingAccount, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInvestor------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInvestorField* _pInvestor = NULL;
  if (pInvestor) {
    _pInvestor = new CThostFtdcInvestorField();
    memcpy(_pInvestor, pInvestor, sizeof(CThostFtdcInvestorField));
  }
  on_invoke(T_ONRSPQRYINVESTOR, _pInvestor, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryTradingCode------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTradingCodeField* _pTradingCode = NULL;
  if (pTradingCode) {
    _pTradingCode = new CThostFtdcTradingCodeField();
    memcpy(_pTradingCode, pTradingCode, sizeof(CThostFtdcTradingCodeField));
  }
  on_invoke(T_ONRSPQRYTRADINGCODE, _pTradingCode, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInstrumentMarginRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInstrumentMarginRateField* _pInstrumentMarginRate = NULL;
  if (pInstrumentMarginRate) {
    _pInstrumentMarginRate = new CThostFtdcInstrumentMarginRateField();
    memcpy(_pInstrumentMarginRate, pInstrumentMarginRate, sizeof(CThostFtdcInstrumentMarginRateField));
  }
  on_invoke(T_ONRSPQRYINSTRUMENTMARGINRATE, _pInstrumentMarginRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInstrumentCommissionRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInstrumentCommissionRateField* _pInstrumentCommissionRate = NULL;
  if (pInstrumentCommissionRate) {
    _pInstrumentCommissionRate = new CThostFtdcInstrumentCommissionRateField();
    memcpy(_pInstrumentCommissionRate, pInstrumentCommissionRate, sizeof(CThostFtdcInstrumentCommissionRateField));
  }
  on_invoke(T_ONRSPQRYINSTRUMENTCOMMISSIONRATE, _pInstrumentCommissionRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryExchange------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcExchangeField* _pExchange = NULL;
  if (pExchange) {
    _pExchange = new CThostFtdcExchangeField();
    memcpy(_pExchange, pExchange, sizeof(CThostFtdcExchangeField));
  }
  on_invoke(T_ONRSPQRYEXCHANGE, _pExchange, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryProduct------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcProductField* _pProduct = NULL;
  if (pProduct) {
    _pProduct = new CThostFtdcProductField();
    memcpy(_pProduct, pProduct, sizeof(CThostFtdcProductField));
  }
  on_invoke(T_ONRSPQRYPRODUCT, _pProduct, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInstrument------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInstrumentField* _pInstrument = NULL;
  if (pInstrument) {
    _pInstrument = new CThostFtdcInstrumentField();
    memcpy(_pInstrument, pInstrument, sizeof(CThostFtdcInstrumentField));
  }
  on_invoke(T_ONRSPQRYINSTRUMENT, _pInstrument, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryDepthMarketData------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcDepthMarketDataField* _pDepthMarketData = NULL;
  if (pDepthMarketData) {
    _pDepthMarketData = new CThostFtdcDepthMarketDataField();
    memcpy(_pDepthMarketData, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
  }
  on_invoke(T_ONRSPQRYDEPTHMARKETDATA, _pDepthMarketData, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQrySettlementInfo------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcSettlementInfoField* _pSettlementInfo = NULL;
  if (pSettlementInfo) {
    _pSettlementInfo = new CThostFtdcSettlementInfoField();
    memcpy(_pSettlementInfo, pSettlementInfo, sizeof(CThostFtdcSettlementInfoField));
  }
  on_invoke(T_ONRSPQRYSETTLEMENTINFO, _pSettlementInfo, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryTransferBank------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTransferBankField* _pTransferBank = NULL;
  if (pTransferBank) {
    _pTransferBank = new CThostFtdcTransferBankField();
    memcpy(_pTransferBank, pTransferBank, sizeof(CThostFtdcTransferBankField));
  }
  on_invoke(T_ONRSPQRYTRANSFERBANK, _pTransferBank, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInvestorPositionDetail------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInvestorPositionDetailField* _pInvestorPositionDetail = NULL;
  if (pInvestorPositionDetail) {
    _pInvestorPositionDetail = new CThostFtdcInvestorPositionDetailField();
    memcpy(_pInvestorPositionDetail, pInvestorPositionDetail, sizeof(CThostFtdcInvestorPositionDetailField));
  }
  on_invoke(T_ONRSPQRYINVESTORPOSITIONDETAIL, _pInvestorPositionDetail, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryNotice------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcNoticeField* _pNotice = NULL;
  if (pNotice) {
    _pNotice = new CThostFtdcNoticeField();
    memcpy(_pNotice, pNotice, sizeof(CThostFtdcNoticeField));
  }
  on_invoke(T_ONRSPQRYNOTICE, _pNotice, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQrySettlementInfoConfirm------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcSettlementInfoConfirmField* _pSettlementInfoConfirm = NULL;
  if (pSettlementInfoConfirm) {
    _pSettlementInfoConfirm = new CThostFtdcSettlementInfoConfirmField();
    memcpy(_pSettlementInfoConfirm, pSettlementInfoConfirm, sizeof(CThostFtdcSettlementInfoConfirmField));
  }
  on_invoke(T_ONRSPQRYSETTLEMENTINFOCONFIRM, _pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInvestorPositionCombineDetail------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInvestorPositionCombineDetailField* _pInvestorPositionCombineDetail = NULL;
  if (pInvestorPositionCombineDetail) {
    _pInvestorPositionCombineDetail = new CThostFtdcInvestorPositionCombineDetailField();
    memcpy(_pInvestorPositionCombineDetail, pInvestorPositionCombineDetail, sizeof(CThostFtdcInvestorPositionCombineDetailField));
  }
  on_invoke(T_ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL, _pInvestorPositionCombineDetail, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryCFMMCTradingAccountKey------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcCFMMCTradingAccountKeyField* _pCFMMCTradingAccountKey = NULL;
  if (pCFMMCTradingAccountKey) {
    _pCFMMCTradingAccountKey = new CThostFtdcCFMMCTradingAccountKeyField();
    memcpy(_pCFMMCTradingAccountKey, pCFMMCTradingAccountKey, sizeof(CThostFtdcCFMMCTradingAccountKeyField));
  }
  on_invoke(T_ONRSPQRYCFMMCTRADINGACCOUNTKEY, _pCFMMCTradingAccountKey, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryEWarrantOffset------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcEWarrantOffsetField* _pEWarrantOffset = NULL;
  if (pEWarrantOffset) {
    _pEWarrantOffset = new CThostFtdcEWarrantOffsetField();
    memcpy(_pEWarrantOffset, pEWarrantOffset, sizeof(CThostFtdcEWarrantOffsetField));
  }
  on_invoke(T_ONRSPQRYEWARRANTOFFSET, _pEWarrantOffset, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInvestorProductGroupMargin------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInvestorProductGroupMarginField* _pInvestorProductGroupMargin = NULL;
  if (pInvestorProductGroupMargin) {
    _pInvestorProductGroupMargin = new CThostFtdcInvestorProductGroupMarginField();
    memcpy(_pInvestorProductGroupMargin, pInvestorProductGroupMargin, sizeof(CThostFtdcInvestorProductGroupMarginField));
  }
  on_invoke(T_ONRSPQRYINVESTORPRODUCTGROUPMARGIN, _pInvestorProductGroupMargin, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryExchangeMarginRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcExchangeMarginRateField* _pExchangeMarginRate = NULL;
  if (pExchangeMarginRate) {
    _pExchangeMarginRate = new CThostFtdcExchangeMarginRateField();
    memcpy(_pExchangeMarginRate, pExchangeMarginRate, sizeof(CThostFtdcExchangeMarginRateField));
  }
  on_invoke(T_ONRSPQRYEXCHANGEMARGINRATE, _pExchangeMarginRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryExchangeMarginRateAdjust------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcExchangeMarginRateAdjustField* _pExchangeMarginRateAdjust = NULL;
  if (pExchangeMarginRateAdjust) {
    _pExchangeMarginRateAdjust = new CThostFtdcExchangeMarginRateAdjustField();
    memcpy(_pExchangeMarginRateAdjust, pExchangeMarginRateAdjust, sizeof(CThostFtdcExchangeMarginRateAdjustField));
  }
  on_invoke(T_ONRSPQRYEXCHANGEMARGINRATEADJUST, _pExchangeMarginRateAdjust, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryExchangeRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcExchangeRateField* _pExchangeRate = NULL;
  if (pExchangeRate) {
    _pExchangeRate = new CThostFtdcExchangeRateField();
    memcpy(_pExchangeRate, pExchangeRate, sizeof(CThostFtdcExchangeRateField));
  }
  on_invoke(T_ONRSPQRYEXCHANGERATE, _pExchangeRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQrySecAgentACIDMap------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcSecAgentACIDMapField* _pSecAgentACIDMap = NULL;
  if (pSecAgentACIDMap) {
    _pSecAgentACIDMap = new CThostFtdcSecAgentACIDMapField();
    memcpy(_pSecAgentACIDMap, pSecAgentACIDMap, sizeof(CThostFtdcSecAgentACIDMapField));
  }
  on_invoke(T_ONRSPQRYSECAGENTACIDMAP, _pSecAgentACIDMap, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryProductExchRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcProductExchRateField* _pProductExchRate = NULL;
  if (pProductExchRate) {
    _pProductExchRate = new CThostFtdcProductExchRateField();
    memcpy(_pProductExchRate, pProductExchRate, sizeof(CThostFtdcProductExchRateField));
  }
  on_invoke(T_ONRSPQRYPRODUCTEXCHRATE, _pProductExchRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryProductGroup------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcProductGroupField* _pProductGroup = NULL;
  if (pProductGroup) {
    _pProductGroup = new CThostFtdcProductGroupField();
    memcpy(_pProductGroup, pProductGroup, sizeof(CThostFtdcProductGroupField));
  }
  on_invoke(T_ONRSPQRYPRODUCTGROUP, _pProductGroup, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryMMInstrumentCommissionRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcMMInstrumentCommissionRateField* _pMMInstrumentCommissionRate = NULL;
  if (pMMInstrumentCommissionRate) {
    _pMMInstrumentCommissionRate = new CThostFtdcMMInstrumentCommissionRateField();
    memcpy(_pMMInstrumentCommissionRate, pMMInstrumentCommissionRate, sizeof(CThostFtdcMMInstrumentCommissionRateField));
  }
  on_invoke(T_ONRSPQRYMMINSTRUMENTCOMMISSIONRATE, _pMMInstrumentCommissionRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryMMOptionInstrCommRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcMMOptionInstrCommRateField* _pMMOptionInstrCommRate = NULL;
  if (pMMOptionInstrCommRate) {
    _pMMOptionInstrCommRate = new CThostFtdcMMOptionInstrCommRateField();
    memcpy(_pMMOptionInstrCommRate, pMMOptionInstrCommRate, sizeof(CThostFtdcMMOptionInstrCommRateField));
  }
  on_invoke(T_ONRSPQRYMMOPTIONINSTRCOMMRATE, _pMMOptionInstrCommRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInstrumentOrderCommRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInstrumentOrderCommRateField* _pInstrumentOrderCommRate = NULL;
  if (pInstrumentOrderCommRate) {
    _pInstrumentOrderCommRate = new CThostFtdcInstrumentOrderCommRateField();
    memcpy(_pInstrumentOrderCommRate, pInstrumentOrderCommRate, sizeof(CThostFtdcInstrumentOrderCommRateField));
  }
  on_invoke(T_ONRSPQRYINSTRUMENTORDERCOMMRATE, _pInstrumentOrderCommRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQrySecAgentTradingAccount------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTradingAccountField* _pTradingAccount = NULL;
  if (pTradingAccount) {
    _pTradingAccount = new CThostFtdcTradingAccountField();
    memcpy(_pTradingAccount, pTradingAccount, sizeof(CThostFtdcTradingAccountField));
  }
  on_invoke(T_ONRSPQRYSECAGENTTRADINGACCOUNT, _pTradingAccount, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQrySecAgentCheckMode------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcSecAgentCheckModeField* _pSecAgentCheckMode = NULL;
  if (pSecAgentCheckMode) {
    _pSecAgentCheckMode = new CThostFtdcSecAgentCheckModeField();
    memcpy(_pSecAgentCheckMode, pSecAgentCheckMode, sizeof(CThostFtdcSecAgentCheckModeField));
  }
  on_invoke(T_ONRSPQRYSECAGENTCHECKMODE, _pSecAgentCheckMode, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryOptionInstrTradeCost------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcOptionInstrTradeCostField* _pOptionInstrTradeCost = NULL;
  if (pOptionInstrTradeCost) {
    _pOptionInstrTradeCost = new CThostFtdcOptionInstrTradeCostField();
    memcpy(_pOptionInstrTradeCost, pOptionInstrTradeCost, sizeof(CThostFtdcOptionInstrTradeCostField));
  }
  on_invoke(T_ONRSPQRYOPTIONINSTRTRADECOST, _pOptionInstrTradeCost, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryOptionInstrCommRate------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcOptionInstrCommRateField* _pOptionInstrCommRate = NULL;
  if (pOptionInstrCommRate) {
    _pOptionInstrCommRate = new CThostFtdcOptionInstrCommRateField();
    memcpy(_pOptionInstrCommRate, pOptionInstrCommRate, sizeof(CThostFtdcOptionInstrCommRateField));
  }
  on_invoke(T_ONRSPQRYOPTIONINSTRCOMMRATE, _pOptionInstrCommRate, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryExecOrder------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcExecOrderField* _pExecOrder = NULL;
  if (pExecOrder) {
    _pExecOrder = new CThostFtdcExecOrderField();
    memcpy(_pExecOrder, pExecOrder, sizeof(CThostFtdcExecOrderField));
  }
  on_invoke(T_ONRSPQRYEXECORDER, _pExecOrder, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryForQuote------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcForQuoteField* _pForQuote = NULL;
  if (pForQuote) {
    _pForQuote = new CThostFtdcForQuoteField();
    memcpy(_pForQuote, pForQuote, sizeof(CThostFtdcForQuoteField));
  }
  on_invoke(T_ONRSPQRYFORQUOTE, _pForQuote, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryQuote------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcQuoteField* _pQuote = NULL;
  if (pQuote) {
    _pQuote = new CThostFtdcQuoteField();
    memcpy(_pQuote, pQuote, sizeof(CThostFtdcQuoteField));
  }
  on_invoke(T_ONRSPQRYQUOTE, _pQuote, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryOptionSelfClose------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcOptionSelfCloseField* _pOptionSelfClose = NULL;
  if (pOptionSelfClose) {
    _pOptionSelfClose = new CThostFtdcOptionSelfCloseField();
    memcpy(_pOptionSelfClose, pOptionSelfClose, sizeof(CThostFtdcOptionSelfCloseField));
  }
  on_invoke(T_ONRSPQRYOPTIONSELFCLOSE, _pOptionSelfClose, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryInvestUnit------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcInvestUnitField* _pInvestUnit = NULL;
  if (pInvestUnit) {
    _pInvestUnit = new CThostFtdcInvestUnitField();
    memcpy(_pInvestUnit, pInvestUnit, sizeof(CThostFtdcInvestUnitField));
  }
  on_invoke(T_ONRSPQRYINVESTUNIT, _pInvestUnit, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryCombInstrumentGuard------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcCombInstrumentGuardField* _pCombInstrumentGuard = NULL;
  if (pCombInstrumentGuard) {
    _pCombInstrumentGuard = new CThostFtdcCombInstrumentGuardField();
    memcpy(_pCombInstrumentGuard, pCombInstrumentGuard, sizeof(CThostFtdcCombInstrumentGuardField));
  }
  on_invoke(T_ONRSPQRYCOMBINSTRUMENTGUARD, _pCombInstrumentGuard, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryCombAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcCombActionField* _pCombAction = NULL;
  if (pCombAction) {
    _pCombAction = new CThostFtdcCombActionField();
    memcpy(_pCombAction, pCombAction, sizeof(CThostFtdcCombActionField));
  }
  on_invoke(T_ONRSPQRYCOMBACTION, _pCombAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryTransferSerial------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTransferSerialField* _pTransferSerial = NULL;
  if (pTransferSerial) {
    _pTransferSerial = new CThostFtdcTransferSerialField();
    memcpy(_pTransferSerial, pTransferSerial, sizeof(CThostFtdcTransferSerialField));
  }
  on_invoke(T_ONRSPQRYTRANSFERSERIAL, _pTransferSerial, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryAccountregister------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcAccountregisterField* _pAccountregister = NULL;
  if (pAccountregister) {
    _pAccountregister = new CThostFtdcAccountregisterField();
    memcpy(_pAccountregister, pAccountregister, sizeof(CThostFtdcAccountregisterField));
  }
  on_invoke(T_ONRSPQRYACCOUNTREGISTER, _pAccountregister, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRtnOrder(CThostFtdcOrderField *pOrder) {
  std::string log = "uv_trader OnRtnOrder------>";
  logger_cout(log.c_str());
  CThostFtdcOrderField* _pOrder = NULL;
  if (pOrder) {
    _pOrder = new CThostFtdcOrderField();
    memcpy(_pOrder, pOrder, sizeof(CThostFtdcOrderField));
  }
  on_invoke(T_ONRTNORDER, _pOrder, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnTrade(CThostFtdcTradeField *pTrade) {
  std::string log = "uv_trader OnRtnTrade------>";
  logger_cout(log.c_str());
  CThostFtdcTradeField* _pTrade = NULL;
  if (pTrade) {
    _pTrade = new CThostFtdcTradeField();
    memcpy(_pTrade, pTrade, sizeof(CThostFtdcTradeField));
  }
  on_invoke(T_ONRTNTRADE, _pTrade, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnOrderInsert------>";
  logger_cout(log.c_str());
  CThostFtdcInputOrderField* _pInputOrder = NULL;
  if (pInputOrder) {
    _pInputOrder = new CThostFtdcInputOrderField();
    memcpy(_pInputOrder, pInputOrder, sizeof(CThostFtdcInputOrderField));
  }
  on_invoke(T_ONERRRTNORDERINSERT, _pInputOrder, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnOrderAction------>";
  logger_cout(log.c_str());
  CThostFtdcOrderActionField* _pOrderAction = NULL;
  if (pOrderAction) {
    _pOrderAction = new CThostFtdcOrderActionField();
    memcpy(_pOrderAction, pOrderAction, sizeof(CThostFtdcOrderActionField));
  }
  on_invoke(T_ONERRRTNORDERACTION, _pOrderAction, pRspInfo, 0, 0);      
}

void uv_trader::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {
  std::string log = "uv_trader OnRtnInstrumentStatus------>";
  logger_cout(log.c_str());
  CThostFtdcInstrumentStatusField* _pInstrumentStatus = NULL;
  if (pInstrumentStatus) {
    _pInstrumentStatus = new CThostFtdcInstrumentStatusField();
    memcpy(_pInstrumentStatus, pInstrumentStatus, sizeof(CThostFtdcInstrumentStatusField));
  }
  on_invoke(T_ONRTNINSTRUMENTSTATUS, _pInstrumentStatus, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {
  std::string log = "uv_trader OnRtnBulletin------>";
  logger_cout(log.c_str());
  CThostFtdcBulletinField* _pBulletin = NULL;
  if (pBulletin) {
    _pBulletin = new CThostFtdcBulletinField();
    memcpy(_pBulletin, pBulletin, sizeof(CThostFtdcBulletinField));
  }
  on_invoke(T_ONRTNBULLETIN, _pBulletin, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {
  std::string log = "uv_trader OnRtnTradingNotice------>";
  logger_cout(log.c_str());
  CThostFtdcTradingNoticeInfoField* _pTradingNoticeInfo = NULL;
  if (pTradingNoticeInfo) {
    _pTradingNoticeInfo = new CThostFtdcTradingNoticeInfoField();
    memcpy(_pTradingNoticeInfo, pTradingNoticeInfo, sizeof(CThostFtdcTradingNoticeInfoField));
  }
  on_invoke(T_ONRTNTRADINGNOTICE, _pTradingNoticeInfo, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {
  std::string log = "uv_trader OnRtnErrorConditionalOrder------>";
  logger_cout(log.c_str());
  CThostFtdcErrorConditionalOrderField* _pErrorConditionalOrder = NULL;
  if (pErrorConditionalOrder) {
    _pErrorConditionalOrder = new CThostFtdcErrorConditionalOrderField();
    memcpy(_pErrorConditionalOrder, pErrorConditionalOrder, sizeof(CThostFtdcErrorConditionalOrderField));
  }
  on_invoke(T_ONRTNERRORCONDITIONALORDER, _pErrorConditionalOrder, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {
  std::string log = "uv_trader OnRtnExecOrder------>";
  logger_cout(log.c_str());
  CThostFtdcExecOrderField* _pExecOrder = NULL;
  if (pExecOrder) {
    _pExecOrder = new CThostFtdcExecOrderField();
    memcpy(_pExecOrder, pExecOrder, sizeof(CThostFtdcExecOrderField));
  }
  on_invoke(T_ONRTNEXECORDER, _pExecOrder, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnExecOrderInsert------>";
  logger_cout(log.c_str());
  CThostFtdcInputExecOrderField* _pInputExecOrder = NULL;
  if (pInputExecOrder) {
    _pInputExecOrder = new CThostFtdcInputExecOrderField();
    memcpy(_pInputExecOrder, pInputExecOrder, sizeof(CThostFtdcInputExecOrderField));
  }
  on_invoke(T_ONERRRTNEXECORDERINSERT, _pInputExecOrder, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnExecOrderAction------>";
  logger_cout(log.c_str());
  CThostFtdcExecOrderActionField* _pExecOrderAction = NULL;
  if (pExecOrderAction) {
    _pExecOrderAction = new CThostFtdcExecOrderActionField();
    memcpy(_pExecOrderAction, pExecOrderAction, sizeof(CThostFtdcExecOrderActionField));
  }
  on_invoke(T_ONERRRTNEXECORDERACTION, _pExecOrderAction, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnForQuoteInsert------>";
  logger_cout(log.c_str());
  CThostFtdcInputForQuoteField* _pInputForQuote = NULL;
  if (pInputForQuote) {
    _pInputForQuote = new CThostFtdcInputForQuoteField();
    memcpy(_pInputForQuote, pInputForQuote, sizeof(CThostFtdcInputForQuoteField));
  }
  on_invoke(T_ONERRRTNFORQUOTEINSERT, _pInputForQuote, pRspInfo, 0, 0);      
}

void uv_trader::OnRtnQuote(CThostFtdcQuoteField *pQuote) {
  std::string log = "uv_trader OnRtnQuote------>";
  logger_cout(log.c_str());
  CThostFtdcQuoteField* _pQuote = NULL;
  if (pQuote) {
    _pQuote = new CThostFtdcQuoteField();
    memcpy(_pQuote, pQuote, sizeof(CThostFtdcQuoteField));
  }
  on_invoke(T_ONRTNQUOTE, _pQuote, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnQuoteInsert------>";
  logger_cout(log.c_str());
  CThostFtdcInputQuoteField* _pInputQuote = NULL;
  if (pInputQuote) {
    _pInputQuote = new CThostFtdcInputQuoteField();
    memcpy(_pInputQuote, pInputQuote, sizeof(CThostFtdcInputQuoteField));
  }
  on_invoke(T_ONERRRTNQUOTEINSERT, _pInputQuote, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnQuoteAction------>";
  logger_cout(log.c_str());
  CThostFtdcQuoteActionField* _pQuoteAction = NULL;
  if (pQuoteAction) {
    _pQuoteAction = new CThostFtdcQuoteActionField();
    memcpy(_pQuoteAction, pQuoteAction, sizeof(CThostFtdcQuoteActionField));
  }
  on_invoke(T_ONERRRTNQUOTEACTION, _pQuoteAction, pRspInfo, 0, 0);      
}

void uv_trader::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  std::string log = "uv_trader OnRtnForQuoteRsp------>";
  logger_cout(log.c_str());
  CThostFtdcForQuoteRspField* _pForQuoteRsp = NULL;
  if (pForQuoteRsp) {
    _pForQuoteRsp = new CThostFtdcForQuoteRspField();
    memcpy(_pForQuoteRsp, pForQuoteRsp, sizeof(CThostFtdcForQuoteRspField));
  }
  on_invoke(T_ONRTNFORQUOTERSP, _pForQuoteRsp, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {
  std::string log = "uv_trader OnRtnCFMMCTradingAccountToken------>";
  logger_cout(log.c_str());
  CThostFtdcCFMMCTradingAccountTokenField* _pCFMMCTradingAccountToken = NULL;
  if (pCFMMCTradingAccountToken) {
    _pCFMMCTradingAccountToken = new CThostFtdcCFMMCTradingAccountTokenField();
    memcpy(_pCFMMCTradingAccountToken, pCFMMCTradingAccountToken, sizeof(CThostFtdcCFMMCTradingAccountTokenField));
  }
  on_invoke(T_ONRTNCFMMCTRADINGACCOUNTTOKEN, _pCFMMCTradingAccountToken, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnBatchOrderAction------>";
  logger_cout(log.c_str());
  CThostFtdcBatchOrderActionField* _pBatchOrderAction = NULL;
  if (pBatchOrderAction) {
    _pBatchOrderAction = new CThostFtdcBatchOrderActionField();
    memcpy(_pBatchOrderAction, pBatchOrderAction, sizeof(CThostFtdcBatchOrderActionField));
  }
  on_invoke(T_ONERRRTNBATCHORDERACTION, _pBatchOrderAction, pRspInfo, 0, 0);      
}

void uv_trader::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) {
  std::string log = "uv_trader OnRtnOptionSelfClose------>";
  logger_cout(log.c_str());
  CThostFtdcOptionSelfCloseField* _pOptionSelfClose = NULL;
  if (pOptionSelfClose) {
    _pOptionSelfClose = new CThostFtdcOptionSelfCloseField();
    memcpy(_pOptionSelfClose, pOptionSelfClose, sizeof(CThostFtdcOptionSelfCloseField));
  }
  on_invoke(T_ONRTNOPTIONSELFCLOSE, _pOptionSelfClose, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnOptionSelfCloseInsert------>";
  logger_cout(log.c_str());
  CThostFtdcInputOptionSelfCloseField* _pInputOptionSelfClose = NULL;
  if (pInputOptionSelfClose) {
    _pInputOptionSelfClose = new CThostFtdcInputOptionSelfCloseField();
    memcpy(_pInputOptionSelfClose, pInputOptionSelfClose, sizeof(CThostFtdcInputOptionSelfCloseField));
  }
  on_invoke(T_ONERRRTNOPTIONSELFCLOSEINSERT, _pInputOptionSelfClose, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnOptionSelfCloseAction------>";
  logger_cout(log.c_str());
  CThostFtdcOptionSelfCloseActionField* _pOptionSelfCloseAction = NULL;
  if (pOptionSelfCloseAction) {
    _pOptionSelfCloseAction = new CThostFtdcOptionSelfCloseActionField();
    memcpy(_pOptionSelfCloseAction, pOptionSelfCloseAction, sizeof(CThostFtdcOptionSelfCloseActionField));
  }
  on_invoke(T_ONERRRTNOPTIONSELFCLOSEACTION, _pOptionSelfCloseAction, pRspInfo, 0, 0);      
}

void uv_trader::OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {
  std::string log = "uv_trader OnRtnCombAction------>";
  logger_cout(log.c_str());
  CThostFtdcCombActionField* _pCombAction = NULL;
  if (pCombAction) {
    _pCombAction = new CThostFtdcCombActionField();
    memcpy(_pCombAction, pCombAction, sizeof(CThostFtdcCombActionField));
  }
  on_invoke(T_ONRTNCOMBACTION, _pCombAction, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnCombActionInsert------>";
  logger_cout(log.c_str());
  CThostFtdcInputCombActionField* _pInputCombAction = NULL;
  if (pInputCombAction) {
    _pInputCombAction = new CThostFtdcInputCombActionField();
    memcpy(_pInputCombAction, pInputCombAction, sizeof(CThostFtdcInputCombActionField));
  }
  on_invoke(T_ONERRRTNCOMBACTIONINSERT, _pInputCombAction, pRspInfo, 0, 0);      
}

void uv_trader::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryContractBank------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcContractBankField* _pContractBank = NULL;
  if (pContractBank) {
    _pContractBank = new CThostFtdcContractBankField();
    memcpy(_pContractBank, pContractBank, sizeof(CThostFtdcContractBankField));
  }
  on_invoke(T_ONRSPQRYCONTRACTBANK, _pContractBank, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryParkedOrder------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcParkedOrderField* _pParkedOrder = NULL;
  if (pParkedOrder) {
    _pParkedOrder = new CThostFtdcParkedOrderField();
    memcpy(_pParkedOrder, pParkedOrder, sizeof(CThostFtdcParkedOrderField));
  }
  on_invoke(T_ONRSPQRYPARKEDORDER, _pParkedOrder, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryParkedOrderAction------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcParkedOrderActionField* _pParkedOrderAction = NULL;
  if (pParkedOrderAction) {
    _pParkedOrderAction = new CThostFtdcParkedOrderActionField();
    memcpy(_pParkedOrderAction, pParkedOrderAction, sizeof(CThostFtdcParkedOrderActionField));
  }
  on_invoke(T_ONRSPQRYPARKEDORDERACTION, _pParkedOrderAction, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryTradingNotice------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcTradingNoticeField* _pTradingNotice = NULL;
  if (pTradingNotice) {
    _pTradingNotice = new CThostFtdcTradingNoticeField();
    memcpy(_pTradingNotice, pTradingNotice, sizeof(CThostFtdcTradingNoticeField));
  }
  on_invoke(T_ONRSPQRYTRADINGNOTICE, _pTradingNotice, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryBrokerTradingParams------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcBrokerTradingParamsField* _pBrokerTradingParams = NULL;
  if (pBrokerTradingParams) {
    _pBrokerTradingParams = new CThostFtdcBrokerTradingParamsField();
    memcpy(_pBrokerTradingParams, pBrokerTradingParams, sizeof(CThostFtdcBrokerTradingParamsField));
  }
  on_invoke(T_ONRSPQRYBROKERTRADINGPARAMS, _pBrokerTradingParams, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQryBrokerTradingAlgos------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcBrokerTradingAlgosField* _pBrokerTradingAlgos = NULL;
  if (pBrokerTradingAlgos) {
    _pBrokerTradingAlgos = new CThostFtdcBrokerTradingAlgosField();
    memcpy(_pBrokerTradingAlgos, pBrokerTradingAlgos, sizeof(CThostFtdcBrokerTradingAlgosField));
  }
  on_invoke(T_ONRSPQRYBROKERTRADINGALGOS, _pBrokerTradingAlgos, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQueryCFMMCTradingAccountToken------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcQueryCFMMCTradingAccountTokenField* _pQueryCFMMCTradingAccountToken = NULL;
  if (pQueryCFMMCTradingAccountToken) {
    _pQueryCFMMCTradingAccountToken = new CThostFtdcQueryCFMMCTradingAccountTokenField();
    memcpy(_pQueryCFMMCTradingAccountToken, pQueryCFMMCTradingAccountToken, sizeof(CThostFtdcQueryCFMMCTradingAccountTokenField));
  }
  on_invoke(T_ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN, _pQueryCFMMCTradingAccountToken, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {
  std::string log = "uv_trader OnRtnFromBankToFutureByBank------>";
  logger_cout(log.c_str());
  CThostFtdcRspTransferField* _pRspTransfer = NULL;
  if (pRspTransfer) {
    _pRspTransfer = new CThostFtdcRspTransferField();
    memcpy(_pRspTransfer, pRspTransfer, sizeof(CThostFtdcRspTransferField));
  }
  on_invoke(T_ONRTNFROMBANKTOFUTUREBYBANK, _pRspTransfer, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {
  std::string log = "uv_trader OnRtnFromFutureToBankByBank------>";
  logger_cout(log.c_str());
  CThostFtdcRspTransferField* _pRspTransfer = NULL;
  if (pRspTransfer) {
    _pRspTransfer = new CThostFtdcRspTransferField();
    memcpy(_pRspTransfer, pRspTransfer, sizeof(CThostFtdcRspTransferField));
  }
  on_invoke(T_ONRTNFROMFUTURETOBANKBYBANK, _pRspTransfer, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {
  std::string log = "uv_trader OnRtnRepealFromBankToFutureByBank------>";
  logger_cout(log.c_str());
  CThostFtdcRspRepealField* _pRspRepeal = NULL;
  if (pRspRepeal) {
    _pRspRepeal = new CThostFtdcRspRepealField();
    memcpy(_pRspRepeal, pRspRepeal, sizeof(CThostFtdcRspRepealField));
  }
  on_invoke(T_ONRTNREPEALFROMBANKTOFUTUREBYBANK, _pRspRepeal, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {
  std::string log = "uv_trader OnRtnRepealFromFutureToBankByBank------>";
  logger_cout(log.c_str());
  CThostFtdcRspRepealField* _pRspRepeal = NULL;
  if (pRspRepeal) {
    _pRspRepeal = new CThostFtdcRspRepealField();
    memcpy(_pRspRepeal, pRspRepeal, sizeof(CThostFtdcRspRepealField));
  }
  on_invoke(T_ONRTNREPEALFROMFUTURETOBANKBYBANK, _pRspRepeal, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  std::string log = "uv_trader OnRtnFromBankToFutureByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcRspTransferField* _pRspTransfer = NULL;
  if (pRspTransfer) {
    _pRspTransfer = new CThostFtdcRspTransferField();
    memcpy(_pRspTransfer, pRspTransfer, sizeof(CThostFtdcRspTransferField));
  }
  on_invoke(T_ONRTNFROMBANKTOFUTUREBYFUTURE, _pRspTransfer, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  std::string log = "uv_trader OnRtnFromFutureToBankByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcRspTransferField* _pRspTransfer = NULL;
  if (pRspTransfer) {
    _pRspTransfer = new CThostFtdcRspTransferField();
    memcpy(_pRspTransfer, pRspTransfer, sizeof(CThostFtdcRspTransferField));
  }
  on_invoke(T_ONRTNFROMFUTURETOBANKBYFUTURE, _pRspTransfer, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  std::string log = "uv_trader OnRtnRepealFromBankToFutureByFutureManual------>";
  logger_cout(log.c_str());
  CThostFtdcRspRepealField* _pRspRepeal = NULL;
  if (pRspRepeal) {
    _pRspRepeal = new CThostFtdcRspRepealField();
    memcpy(_pRspRepeal, pRspRepeal, sizeof(CThostFtdcRspRepealField));
  }
  on_invoke(T_ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL, _pRspRepeal, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  std::string log = "uv_trader OnRtnRepealFromFutureToBankByFutureManual------>";
  logger_cout(log.c_str());
  CThostFtdcRspRepealField* _pRspRepeal = NULL;
  if (pRspRepeal) {
    _pRspRepeal = new CThostFtdcRspRepealField();
    memcpy(_pRspRepeal, pRspRepeal, sizeof(CThostFtdcRspRepealField));
  }
  on_invoke(T_ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL, _pRspRepeal, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {
  std::string log = "uv_trader OnRtnQueryBankBalanceByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcNotifyQueryAccountField* _pNotifyQueryAccount = NULL;
  if (pNotifyQueryAccount) {
    _pNotifyQueryAccount = new CThostFtdcNotifyQueryAccountField();
    memcpy(_pNotifyQueryAccount, pNotifyQueryAccount, sizeof(CThostFtdcNotifyQueryAccountField));
  }
  on_invoke(T_ONRTNQUERYBANKBALANCEBYFUTURE, _pNotifyQueryAccount, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnBankToFutureByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcReqTransferField* _pReqTransfer = NULL;
  if (pReqTransfer) {
    _pReqTransfer = new CThostFtdcReqTransferField();
    memcpy(_pReqTransfer, pReqTransfer, sizeof(CThostFtdcReqTransferField));
  }
  on_invoke(T_ONERRRTNBANKTOFUTUREBYFUTURE, _pReqTransfer, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnFutureToBankByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcReqTransferField* _pReqTransfer = NULL;
  if (pReqTransfer) {
    _pReqTransfer = new CThostFtdcReqTransferField();
    memcpy(_pReqTransfer, pReqTransfer, sizeof(CThostFtdcReqTransferField));
  }
  on_invoke(T_ONERRRTNFUTURETOBANKBYFUTURE, _pReqTransfer, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnRepealBankToFutureByFutureManual------>";
  logger_cout(log.c_str());
  CThostFtdcReqRepealField* _pReqRepeal = NULL;
  if (pReqRepeal) {
    _pReqRepeal = new CThostFtdcReqRepealField();
    memcpy(_pReqRepeal, pReqRepeal, sizeof(CThostFtdcReqRepealField));
  }
  on_invoke(T_ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL, _pReqRepeal, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnRepealFutureToBankByFutureManual------>";
  logger_cout(log.c_str());
  CThostFtdcReqRepealField* _pReqRepeal = NULL;
  if (pReqRepeal) {
    _pReqRepeal = new CThostFtdcReqRepealField();
    memcpy(_pReqRepeal, pReqRepeal, sizeof(CThostFtdcReqRepealField));
  }
  on_invoke(T_ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL, _pReqRepeal, pRspInfo, 0, 0);      
}

void uv_trader::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {
  std::string log = "uv_trader OnErrRtnQueryBankBalanceByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcReqQueryAccountField* _pReqQueryAccount = NULL;
  if (pReqQueryAccount) {
    _pReqQueryAccount = new CThostFtdcReqQueryAccountField();
    memcpy(_pReqQueryAccount, pReqQueryAccount, sizeof(CThostFtdcReqQueryAccountField));
  }
  on_invoke(T_ONERRRTNQUERYBANKBALANCEBYFUTURE, _pReqQueryAccount, pRspInfo, 0, 0);      
}

void uv_trader::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  std::string log = "uv_trader OnRtnRepealFromBankToFutureByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcRspRepealField* _pRspRepeal = NULL;
  if (pRspRepeal) {
    _pRspRepeal = new CThostFtdcRspRepealField();
    memcpy(_pRspRepeal, pRspRepeal, sizeof(CThostFtdcRspRepealField));
  }
  on_invoke(T_ONRTNREPEALFROMBANKTOFUTUREBYFUTURE, _pRspRepeal, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  std::string log = "uv_trader OnRtnRepealFromFutureToBankByFuture------>";
  logger_cout(log.c_str());
  CThostFtdcRspRepealField* _pRspRepeal = NULL;
  if (pRspRepeal) {
    _pRspRepeal = new CThostFtdcRspRepealField();
    memcpy(_pRspRepeal, pRspRepeal, sizeof(CThostFtdcRspRepealField));
  }
  on_invoke(T_ONRTNREPEALFROMFUTURETOBANKBYFUTURE, _pRspRepeal, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspFromBankToFutureByFuture------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcReqTransferField* _pReqTransfer = NULL;
  if (pReqTransfer) {
    _pReqTransfer = new CThostFtdcReqTransferField();
    memcpy(_pReqTransfer, pReqTransfer, sizeof(CThostFtdcReqTransferField));
  }
  on_invoke(T_ONRSPFROMBANKTOFUTUREBYFUTURE, _pReqTransfer, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspFromFutureToBankByFuture------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcReqTransferField* _pReqTransfer = NULL;
  if (pReqTransfer) {
    _pReqTransfer = new CThostFtdcReqTransferField();
    memcpy(_pReqTransfer, pReqTransfer, sizeof(CThostFtdcReqTransferField));
  }
  on_invoke(T_ONRSPFROMFUTURETOBANKBYFUTURE, _pReqTransfer, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  std::string log = "uv_trader OnRspQueryBankAccountMoneyByFuture------>";
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  CThostFtdcReqQueryAccountField* _pReqQueryAccount = NULL;
  if (pReqQueryAccount) {
    _pReqQueryAccount = new CThostFtdcReqQueryAccountField();
    memcpy(_pReqQueryAccount, pReqQueryAccount, sizeof(CThostFtdcReqQueryAccountField));
  }
  on_invoke(T_ONRSPQUERYBANKACCOUNTMONEYBYFUTURE, _pReqQueryAccount, pRspInfo, nRequestID, bIsLast);          
}

void uv_trader::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {
  std::string log = "uv_trader OnRtnOpenAccountByBank------>";
  logger_cout(log.c_str());
  CThostFtdcOpenAccountField* _pOpenAccount = NULL;
  if (pOpenAccount) {
    _pOpenAccount = new CThostFtdcOpenAccountField();
    memcpy(_pOpenAccount, pOpenAccount, sizeof(CThostFtdcOpenAccountField));
  }
  on_invoke(T_ONRTNOPENACCOUNTBYBANK, _pOpenAccount, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {
  std::string log = "uv_trader OnRtnCancelAccountByBank------>";
  logger_cout(log.c_str());
  CThostFtdcCancelAccountField* _pCancelAccount = NULL;
  if (pCancelAccount) {
    _pCancelAccount = new CThostFtdcCancelAccountField();
    memcpy(_pCancelAccount, pCancelAccount, sizeof(CThostFtdcCancelAccountField));
  }
  on_invoke(T_ONRTNCANCELACCOUNTBYBANK, _pCancelAccount, new CThostFtdcRspInfoField(), 0, 0);
}

void uv_trader::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {
  std::string log = "uv_trader OnRtnChangeAccountByBank------>";
  logger_cout(log.c_str());
  CThostFtdcChangeAccountField* _pChangeAccount = NULL;
  if (pChangeAccount) {
    _pChangeAccount = new CThostFtdcChangeAccountField();
    memcpy(_pChangeAccount, pChangeAccount, sizeof(CThostFtdcChangeAccountField));
  }
  on_invoke(T_ONRTNCHANGEACCOUNTBYBANK, _pChangeAccount, new CThostFtdcRspInfoField(), 0, 0);
}


