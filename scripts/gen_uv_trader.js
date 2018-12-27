const fs = require('fs')
const path = require('path')

const tpl_h = `
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
{$$1}
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
{$$2}
};

#endif
`

const tpl_cpp = `
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
{$$1}
`

const gen_h = (reqFuncs, resFuncs, base_file_dir) => {
  let rpl_1 = ''
  let rpl_2 = ''
  for (const reqFunc of reqFuncs) {
    rpl_1 += `  void ${reqFunc[0]}(${reqFunc[1]}, void(*callback)(int, void*));\n`
  }
  for (const resFunc of resFuncs) {
    rpl_2 += `  virtual void ${resFunc[0]}(${resFunc[1]});\n`
  }
  fs.writeFileSync(path.join(base_file_dir, './cpp/uv_trader.h'), tpl_h.replace('{$$1}', rpl_1).replace('{$$2}', rpl_2))
}

const gen_c = (reqFuncs, resFuncs, base_file_dir) => {
  let rpl_1 = ''
  for (const reqFunc of reqFuncs) {
    const cb_enum = `T_${reqFunc[0].toUpperCase()}`
    const params = reqFunc[1].split(',').map(x => x.trim())
    const CTHostFtdcField = params[0]
    const CTHostFtdcFieldType = CTHostFtdcField.split(' ')[0]
    const CTHostFtdcFieldValue = CTHostFtdcField.split(' ')[1].replace('*', '')
    rpl_1 += `
  case ${cb_enum}:
    {
      ${CTHostFtdcFieldType} *_${CTHostFtdcFieldValue} = static_cast<${CTHostFtdcFieldType}*>(baton->args);
      baton->nResult = uv_trader_obj->m_pApi->${reqFunc[0]}(_${CTHostFtdcFieldValue}, baton->iRequestID);
      logger_cout(log.append("invoke ${reqFunc[0]},the result:").append(to_string(baton->nResult)).c_str());
      break;
    }
`
  }
  rpl_1 += `
  default:
    {
      logger_cout(log.append("No case event:").append(to_string(baton->fun)).c_str());
      break;
    }
  }
}
`
  for (const reqFunc of reqFuncs) {
    const cb_enum = `T_${reqFunc[0].toUpperCase()}`
    const params = reqFunc[1].split(',').map(x => x.trim())
    const CTHostFtdcField = params[0]
    const CTHostFtdcFieldType = CTHostFtdcField.split(' ')[0]
    const CTHostFtdcFieldValue = CTHostFtdcField.split(' ')[1].replace('*', '')
    rpl_1 += `
void uv_trader::${reqFunc[0]}(${reqFunc[1]}, void(*callback)(int, void*)) {
  ${CTHostFtdcFieldType} *_${CTHostFtdcFieldValue} = new ${CTHostFtdcFieldType}();
  memcpy(_${CTHostFtdcFieldValue}, ${CTHostFtdcFieldValue}, sizeof(${CTHostFtdcFieldType}));
  this->invoke(_${CTHostFtdcFieldValue}, ${cb_enum}, callback, nRequestID);
}
`
  }
  for (const resFunc of resFuncs) {
    if (resFunc[0] === 'OnRspError') continue
    const cb_enum = `T_${resFunc[0].toUpperCase()}`
    const params = resFunc[1].split(',').map(x => x.trim())
    rpl_1 += `void uv_trader::${resFunc[0]}(${resFunc[1]}) {\n`
    if (resFunc[0] === 'OnFrontConnected') {
      rpl_1 += `
  logger_cout("uv_trader OnFrontConnected");
  CbRtnField* field = new CbRtnField();
  field->eFlag = ${cb_enum};
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
`
    } else if (resFunc[0] === 'OnFrontDisconnected') {
      rpl_1 += `
  std::string log = "uv_trader OnFrontDisconnected------>";
  logger_cout(log.append("nReason:").append(to_string(nReason)).c_str());
  CbRtnField* field = new CbRtnField();
  field->eFlag = ${cb_enum};
  field->nReason = nReason;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
`
    } else if (resFunc[0] === 'OnHeartBeatWarning') {
      rpl_1 += `
  std::string log = "uv_trader OnHeartBeatWarning------>";
  logger_cout(log.append("nTimeLapse:").append(to_string(nTimeLapse)).c_str());
  CbRtnField* field = new CbRtnField();
  field->eFlag = ${cb_enum};
  field->nTimeLapse = nTimeLapse;
  field->work.data = field;
  uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
`
    } else {
      const CTHostFtdcField = params[0]
      const CTHostFtdcFieldType = CTHostFtdcField.split(' ')[0]
      const CTHostFtdcFieldValue = CTHostFtdcField.split(' ')[1].replace('*', '')
      rpl_1 += `  std::string log = "uv_trader ${resFunc[0]}------>";`
      if (params.length === 1) {
        rpl_1 += `
  logger_cout(log.c_str());
  ${CTHostFtdcFieldType}* _${CTHostFtdcFieldValue} = NULL;
  if (${CTHostFtdcFieldValue}) {
    _${CTHostFtdcFieldValue} = new ${CTHostFtdcFieldType}();
    memcpy(_${CTHostFtdcFieldValue}, ${CTHostFtdcFieldValue}, sizeof(${CTHostFtdcFieldType}));
  }
  on_invoke(${cb_enum}, _${CTHostFtdcFieldValue}, new CThostFtdcRspInfoField(), 0, 0);
`
      } else if (params.length === 2) {
        rpl_1 += `
  logger_cout(log.c_str());
  ${CTHostFtdcFieldType}* _${CTHostFtdcFieldValue} = NULL;
  if (${CTHostFtdcFieldValue}) {
    _${CTHostFtdcFieldValue} = new ${CTHostFtdcFieldType}();
    memcpy(_${CTHostFtdcFieldValue}, ${CTHostFtdcFieldValue}, sizeof(${CTHostFtdcFieldType}));
  }
  on_invoke(${cb_enum}, _${CTHostFtdcFieldValue}, pRspInfo, 0, 0);      
`
      } else {
        rpl_1 += `
  logger_cout(log.append("requestid:").append(to_string(nRequestID)).append(",islast:").append(to_string(bIsLast)).c_str());
  ${CTHostFtdcFieldType}* _${CTHostFtdcFieldValue} = NULL;
  if (${CTHostFtdcFieldValue}) {
    _${CTHostFtdcFieldValue} = new ${CTHostFtdcFieldType}();
    memcpy(_${CTHostFtdcFieldValue}, ${CTHostFtdcFieldValue}, sizeof(${CTHostFtdcFieldType}));
  }
  on_invoke(${cb_enum}, _${CTHostFtdcFieldValue}, pRspInfo, nRequestID, bIsLast);          
`
      }
    }
    rpl_1 += `}\n\n`
  }

  fs.writeFileSync(path.join(base_file_dir, './cpp/uv_trader.cpp'), tpl_cpp.replace('{$$1}', rpl_1))
}

module.exports = (reqFuncs, resFuncs, base_file_dir) => {
  gen_h(reqFuncs, resFuncs, base_file_dir)
  gen_c(reqFuncs, resFuncs, base_file_dir)
}
