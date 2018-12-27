const fs = require('fs')
const path = require('path')

const tpl = `
#ifndef _CTP_STRUCT_
#define _CTP_STRUCT_

#include <node.h>

#define MSG_MAX_COUNT 200
{$1}
struct UVConnectField {
  char front_addr[200];
  char szPath[50];
  int public_topic_type;
  int private_topic_type;
};

struct LookupCtpApiBaton {
  uv_work_t work;
  void(*callback)(int, void*);
  void* uv_trader_obj;
  void* uv_market_obj;
  void* args;
  int fun;
  int iRequestID;
  int nResult;
  int uuid;//回调标识
  int nCount;
};

struct CbRtnField {
  uv_work_t work;
  int eFlag;//事件标识
  int nRequestID;
  int nReason;
  int nTimeLapse;
  void* rtnField;
  void* rspInfo;
  bool bIsLast;
};

struct CbWrap {
  void(*callback)(CbRtnField *data);
};

struct ptrCmp
{
  bool operator()( std::string s1, std::string s2 ) const
  {
    // return strcmp( s1, s2 ) < 0;
    return s1 == s2;
  }
};

#endif
`

module.exports = (reqFuncs, resFuncs, base_file_dir) => {
  let enum_count = 1
  let rpl$1 = ''
  rpl$1 += '\n//////////////// Request Function Callback Enum\n'
  rpl$1 += `#define T_CONNECT ${enum_count}\n`
  enum_count++
  for (const reqFunc of reqFuncs) {
    rpl$1 += `#define T_${reqFunc[0].toUpperCase()} ${enum_count}\n`
    enum_count++
  }
  rpl$1 += '\n//////////////// Response Function Callback Enum\n'
  for (const resFunc of resFuncs) {
    rpl$1 += `#define T_${resFunc[0].toUpperCase()} ${enum_count}\n`
    enum_count++
  }
  const market_funcs = [
    'SubscribeMarketData',
    'UnSubscribeMarketData',
    'SubscribeForQuoteRsp',
    'UnSubscribeForQuoteRsp',
    'OnRspSubMarketData',
    'OnRspUnSubMarketData',
    'OnRspSubForQuoteRsp',
    'OnRspUnSubForQuoteRsp',
    'OnRtnDepthMarketData'
  ]
  for (const m_func of market_funcs) {
    rpl$1 += `#define T_${m_func.toUpperCase()} ${enum_count}\n`
    enum_count++
  }
  fs.writeFileSync(path.join(base_file_dir, './cpp/ctp_struct.h'), tpl.replace('{$1}', rpl$1))
}
