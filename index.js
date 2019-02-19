const Rx = require('rxjs')
const { filter, first } = require('rxjs/operators')

const structDict = require('./src/ctp_struct')
const { defineDict, typedefDict } = require('./src/ctp_data_type')

exports.structDict = structDict
exports.defineDict = defineDict
exports.typedefDict = typedefDict

const ctp = require('./build/Release/ctp.node')

ctp.createTrader = () => {
  const subject = new Rx.Subject()
  const td = ctp.crtd()
  td.on = (event, func) => {
    return subject.pipe(filter(n => n.event === event)).subscribe(func)
  }
  td.once = (event, func) => {
    return subject.pipe(filter(n => n.event === event), first()).subscribe(func)
  }
  td.On('OnFrontConnected', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnFrontConnected', data, info, req_id, is_last })
  })
  td.On('OnFrontDisconnected', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnFrontDisconnected', data, info, req_id, is_last })
  })
  td.On('OnHeartBeatWarning', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnHeartBeatWarning', data, info, req_id, is_last })
  })
  td.On('OnRspAuthenticate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspAuthenticate', data, info, req_id, is_last })
  })
  td.On('OnRspUserLogin', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspUserLogin', data, info, req_id, is_last })
  })
  td.On('OnRspUserLogout', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspUserLogout', data, info, req_id, is_last })
  })
  td.On('OnRspUserPasswordUpdate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspUserPasswordUpdate', data, info, req_id, is_last })
  })
  td.On('OnRspTradingAccountPasswordUpdate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspTradingAccountPasswordUpdate', data, info, req_id, is_last })
  })
  td.On('OnRspOrderInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspOrderInsert', data, info, req_id, is_last })
  })
  td.On('OnRspParkedOrderInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspParkedOrderInsert', data, info, req_id, is_last })
  })
  td.On('OnRspParkedOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspParkedOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRspOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRspQueryMaxOrderVolume', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQueryMaxOrderVolume', data, info, req_id, is_last })
  })
  td.On('OnRspSettlementInfoConfirm', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspSettlementInfoConfirm', data, info, req_id, is_last })
  })
  td.On('OnRspRemoveParkedOrder', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspRemoveParkedOrder', data, info, req_id, is_last })
  })
  td.On('OnRspRemoveParkedOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspRemoveParkedOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRspExecOrderInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspExecOrderInsert', data, info, req_id, is_last })
  })
  td.On('OnRspExecOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspExecOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRspForQuoteInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspForQuoteInsert', data, info, req_id, is_last })
  })
  td.On('OnRspQuoteInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQuoteInsert', data, info, req_id, is_last })
  })
  td.On('OnRspQuoteAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQuoteAction', data, info, req_id, is_last })
  })
  td.On('OnRspBatchOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspBatchOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRspQryProductGroup', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryProductGroup', data, info, req_id, is_last })
  })
  td.On('OnRspQryMMInstrumentCommissionRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryMMInstrumentCommissionRate', data, info, req_id, is_last })
  })
  td.On('OnRspQryMMOptionInstrCommRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryMMOptionInstrCommRate', data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrumentOrderCommRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInstrumentOrderCommRate', data, info, req_id, is_last })
  })
  td.On('OnRtnBulletin', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnBulletin', data, info, req_id, is_last })
  })
  td.On('OnErrRtnBatchOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnBatchOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRspCombActionInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspCombActionInsert', data, info, req_id, is_last })
  })
  td.On('OnRspQryOrder', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryOrder', data, info, req_id, is_last })
  })
  td.On('OnRspQryTrade', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryTrade', data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorPosition', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInvestorPosition', data, info, req_id, is_last })
  })
  td.On('OnRspQryTradingAccount', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryTradingAccount', data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestor', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInvestor', data, info, req_id, is_last })
  })
  td.On('OnRspQryTradingCode', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryTradingCode', data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrumentMarginRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInstrumentMarginRate', data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrumentCommissionRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInstrumentCommissionRate', data, info, req_id, is_last })
  })
  td.On('OnRspQryExchange', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryExchange', data, info, req_id, is_last })
  })
  td.On('OnRspQryProduct', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryProduct', data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrument', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInstrument', data, info, req_id, is_last })
  })
  td.On('OnRspQryDepthMarketData', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryDepthMarketData', data, info, req_id, is_last })
  })
  td.On('OnRspQrySettlementInfo', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQrySettlementInfo', data, info, req_id, is_last })
  })
  td.On('OnRspQryTransferBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryTransferBank', data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorPositionDetail', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInvestorPositionDetail', data, info, req_id, is_last })
  })
  td.On('OnRspQryNotice', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryNotice', data, info, req_id, is_last })
  })
  td.On('OnRspQrySettlementInfoConfirm', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQrySettlementInfoConfirm', data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorPositionCombineDetail', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInvestorPositionCombineDetail', data, info, req_id, is_last })
  })
  td.On('OnRspQryCFMMCTradingAccountKey', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryCFMMCTradingAccountKey', data, info, req_id, is_last })
  })
  td.On('OnRspQryEWarrantOffset', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryEWarrantOffset', data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorProductGroupMargin', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryInvestorProductGroupMargin', data, info, req_id, is_last })
  })
  td.On('OnRspQryExchangeMarginRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryExchangeMarginRate', data, info, req_id, is_last })
  })
  td.On('OnRspQryExchangeMarginRateAdjust', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryExchangeMarginRateAdjust', data, info, req_id, is_last })
  })
  td.On('OnRspQryExchangeRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryExchangeRate', data, info, req_id, is_last })
  })
  td.On('OnRspQrySecAgentACIDMap', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQrySecAgentACIDMap', data, info, req_id, is_last })
  })
  td.On('OnRspQryProductExchRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryProductExchRate', data, info, req_id, is_last })
  })
  td.On('OnRspQryOptionInstrTradeCost', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryOptionInstrTradeCost', data, info, req_id, is_last })
  })
  td.On('OnRspQryOptionInstrCommRate', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryOptionInstrCommRate', data, info, req_id, is_last })
  })
  td.On('OnRspQryExecOrder', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryExecOrder', data, info, req_id, is_last })
  })
  td.On('OnRspQryForQuote', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryForQuote', data, info, req_id, is_last })
  })
  td.On('OnRspQryQuote', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryQuote', data, info, req_id, is_last })
  })
  td.On('OnRspQryCombInstrumentGuard', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryCombInstrumentGuard', data, info, req_id, is_last })
  })
  td.On('OnRspQryCombAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryCombAction', data, info, req_id, is_last })
  })
  td.On('OnRspQryTransferSerial', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryTransferSerial', data, info, req_id, is_last })
  })
  td.On('OnRspQryAccountregister', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryAccountregister', data, info, req_id, is_last })
  })
  td.On('OnRspError', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspError', data, info, req_id, is_last })
  })
  td.On('OnRtnOrder', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnOrder', data, info, req_id, is_last })
  })
  td.On('OnRtnTrade', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnTrade', data, info, req_id, is_last })
  })
  td.On('OnErrRtnOrderInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnOrderInsert', data, info, req_id, is_last })
  })
  td.On('OnErrRtnOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRtnInstrumentStatus', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnInstrumentStatus', data, info, req_id, is_last })
  })
  td.On('OnRtnTradingNotice', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnTradingNotice', data, info, req_id, is_last })
  })
  td.On('OnRtnErrorConditionalOrder', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnErrorConditionalOrder', data, info, req_id, is_last })
  })
  td.On('OnRtnExecOrder', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnExecOrder', data, info, req_id, is_last })
  })
  td.On('OnErrRtnExecOrderInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnExecOrderInsert', data, info, req_id, is_last })
  })
  td.On('OnErrRtnExecOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnExecOrderAction', data, info, req_id, is_last })
  })
  td.On('OnErrRtnForQuoteInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnForQuoteInsert', data, info, req_id, is_last })
  })
  td.On('OnRtnQuote', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnQuote', data, info, req_id, is_last })
  })
  td.On('OnErrRtnQuoteInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnQuoteInsert', data, info, req_id, is_last })
  })
  td.On('OnErrRtnQuoteAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnQuoteAction', data, info, req_id, is_last })
  })
  td.On('OnRtnForQuoteRsp', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnForQuoteRsp', data, info, req_id, is_last })
  })
  td.On('OnRtnCFMMCTradingAccountToken', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnCFMMCTradingAccountToken', data, info, req_id, is_last })
  })
  td.On('OnRtnCombAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnCombAction', data, info, req_id, is_last })
  })
  td.On('OnErrRtnCombActionInsert', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnCombActionInsert', data, info, req_id, is_last })
  })
  td.On('OnRspQryContractBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryContractBank', data, info, req_id, is_last })
  })
  td.On('OnRspQryParkedOrder', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryParkedOrder', data, info, req_id, is_last })
  })
  td.On('OnRspQryParkedOrderAction', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryParkedOrderAction', data, info, req_id, is_last })
  })
  td.On('OnRspQryTradingNotice', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryTradingNotice', data, info, req_id, is_last })
  })
  td.On('OnRspQryBrokerTradingParams', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryBrokerTradingParams', data, info, req_id, is_last })
  })
  td.On('OnRspQryBrokerTradingAlgos', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQryBrokerTradingAlgos', data, info, req_id, is_last })
  })
  td.On('OnRspQueryCFMMCTradingAccountToken', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQueryCFMMCTradingAccountToken', data, info, req_id, is_last })
  })
  td.On('OnRtnFromBankToFutureByBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnFromBankToFutureByBank', data, info, req_id, is_last })
  })
  td.On('OnRtnFromFutureToBankByBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnFromFutureToBankByBank', data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromBankToFutureByBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnRepealFromBankToFutureByBank', data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromFutureToBankByBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnRepealFromFutureToBankByBank', data, info, req_id, is_last })
  })
  td.On('OnRtnFromBankToFutureByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnFromBankToFutureByFuture', data, info, req_id, is_last })
  })
  td.On('OnRtnFromFutureToBankByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnFromFutureToBankByFuture', data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromBankToFutureByFutureManual', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnRepealFromBankToFutureByFutureManual', data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromFutureToBankByFutureManual', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnRepealFromFutureToBankByFutureManual', data, info, req_id, is_last })
  })
  td.On('OnRtnQueryBankBalanceByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnQueryBankBalanceByFuture', data, info, req_id, is_last })
  })
  td.On('OnErrRtnBankToFutureByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnBankToFutureByFuture', data, info, req_id, is_last })
  })
  td.On('OnErrRtnFutureToBankByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnFutureToBankByFuture', data, info, req_id, is_last })
  })
  td.On('OnErrRtnRepealBankToFutureByFutureManual', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnRepealBankToFutureByFutureManual', data, info, req_id, is_last })
  })
  td.On('OnErrRtnRepealFutureToBankByFutureManual', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnRepealFutureToBankByFutureManual', data, info, req_id, is_last })
  })
  td.On('OnErrRtnQueryBankBalanceByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnErrRtnQueryBankBalanceByFuture', data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromBankToFutureByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnRepealFromBankToFutureByFuture', data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromFutureToBankByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnRepealFromFutureToBankByFuture', data, info, req_id, is_last })
  })
  td.On('OnRspFromBankToFutureByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspFromBankToFutureByFuture', data, info, req_id, is_last })
  })
  td.On('OnRspFromFutureToBankByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspFromFutureToBankByFuture', data, info, req_id, is_last })
  })
  td.On('OnRspQueryBankAccountMoneyByFuture', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspQueryBankAccountMoneyByFuture', data, info, req_id, is_last })
  })
  td.On('OnRtnOpenAccountByBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnOpenAccountByBank', data, info, req_id, is_last })
  })
  td.On('OnRtnCancelAccountByBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnCancelAccountByBank', data, info, req_id, is_last })
  })
  td.On('OnRtnChangeAccountByBank', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnChangeAccountByBank', data, info, req_id, is_last })
  })
  return td
}

ctp.createMarket = () => {
  const subject = new Rx.Subject()
  const md = ctp.crmd()
  md.on = (event, func) => {
    return subject.pipe(filter(n => n.event === event)).subscribe(func)
  }
  md.once = (event, func) => {
    return subject.pipe(filter(n => n.event === event), first()).subscribe(func)
  }
  md.On('OnFrontConnected', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnFrontConnected', data, info, req_id, is_last })
  })
  md.On('OnFrontDisconnected', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnFrontDisconnected', data, info, req_id, is_last })
  })
  md.On('OnHeartBeatWarning', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnHeartBeatWarning', data, info, req_id, is_last })
  })
  md.On('OnRspUserLogin', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspUserLogin', data, info, req_id, is_last })
  })
  md.On('OnRspUserLogout', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspUserLogout', data, info, req_id, is_last })
  })
  md.On('OnRspError', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspError', data, info, req_id, is_last })
  })
  md.On('OnRspSubMarketData', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspSubMarketData', data, info, req_id, is_last })
  })
  md.On('OnRspUnSubMarketData', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspUnSubMarketData', data, info, req_id, is_last })
  })
  md.On('OnRspSubForQuoteRsp', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspSubForQuoteRsp', data, info, req_id, is_last })
  })
  md.On('OnRspUnSubForQuoteRsp', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRspUnSubForQuoteRsp', data, info, req_id, is_last })
  })
  md.On('OnRtnDepthMarketData', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnDepthMarketData', data, info, req_id, is_last })
  })
  md.On('OnRtnForQuoteRsp', (data, info, req_id, is_last) => {
    subject.next({ event: 'OnRtnForQuoteRsp', data, info, req_id, is_last })
  })
  return md
}

exports.ctp = ctp
