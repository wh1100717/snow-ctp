const EventEmitter = require('events').EventEmitter

const structDict = require('./src/ctp_struct')
const { defineDict, typedefDict } = require('./src/ctp_data_type')

exports.structDict = structDict
exports.defineDict = defineDict
exports.typedefDict = typedefDict

const ctp = require(`./src/ctp_${process.platform}.node`)

ctp.createTrader = () => {
  const emitter = new EventEmitter()
  const td = ctp.crtd()
  td.on = (event, func) => {
    emitter.on(event, func)
  }
  td.On('OnFrontConnected', (data, info, req_id, is_last) => {
    emitter.emit('OnFrontConnected', { data, info, req_id, is_last })
  })
  td.On('OnFrontDisconnected', (data, info, req_id, is_last) => {
    emitter.emit('OnFrontDisconnected', { data, info, req_id, is_last })
  })
  td.On('OnHeartBeatWarning', (data, info, req_id, is_last) => {
    emitter.emit('OnHeartBeatWarning', { data, info, req_id, is_last })
  })
  td.On('OnRspAuthenticate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspAuthenticate', { data, info, req_id, is_last })
  })
  td.On('OnRspUserLogin', (data, info, req_id, is_last) => {
    emitter.emit('OnRspUserLogin', { data, info, req_id, is_last })
  })
  td.On('OnRspUserLogout', (data, info, req_id, is_last) => {
    emitter.emit('OnRspUserLogout', { data, info, req_id, is_last })
  })
  td.On('OnRspUserPasswordUpdate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspUserPasswordUpdate', { data, info, req_id, is_last })
  })
  td.On('OnRspTradingAccountPasswordUpdate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspTradingAccountPasswordUpdate', { data, info, req_id, is_last })
  })
  td.On('OnRspOrderInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnRspOrderInsert', { data, info, req_id, is_last })
  })
  td.On('OnRspParkedOrderInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnRspParkedOrderInsert', { data, info, req_id, is_last })
  })
  td.On('OnRspParkedOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspParkedOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRspOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRspQueryMaxOrderVolume', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQueryMaxOrderVolume', { data, info, req_id, is_last })
  })
  td.On('OnRspSettlementInfoConfirm', (data, info, req_id, is_last) => {
    emitter.emit('OnRspSettlementInfoConfirm', { data, info, req_id, is_last })
  })
  td.On('OnRspRemoveParkedOrder', (data, info, req_id, is_last) => {
    emitter.emit('OnRspRemoveParkedOrder', { data, info, req_id, is_last })
  })
  td.On('OnRspRemoveParkedOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspRemoveParkedOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRspExecOrderInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnRspExecOrderInsert', { data, info, req_id, is_last })
  })
  td.On('OnRspExecOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspExecOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRspForQuoteInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnRspForQuoteInsert', { data, info, req_id, is_last })
  })
  td.On('OnRspQuoteInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQuoteInsert', { data, info, req_id, is_last })
  })
  td.On('OnRspQuoteAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQuoteAction', { data, info, req_id, is_last })
  })
  td.On('OnRspBatchOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspBatchOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRspQryProductGroup', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryProductGroup', { data, info, req_id, is_last })
  })
  td.On('OnRspQryMMInstrumentCommissionRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryMMInstrumentCommissionRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQryMMOptionInstrCommRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryMMOptionInstrCommRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrumentOrderCommRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInstrumentOrderCommRate', { data, info, req_id, is_last })
  })
  td.On('OnRtnBulletin', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnBulletin', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnBatchOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnBatchOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRspCombActionInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnRspCombActionInsert', { data, info, req_id, is_last })
  })
  td.On('OnRspQryOrder', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryOrder', { data, info, req_id, is_last })
  })
  td.On('OnRspQryTrade', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryTrade', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorPosition', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInvestorPosition', { data, info, req_id, is_last })
  })
  td.On('OnRspQryTradingAccount', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryTradingAccount', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestor', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInvestor', { data, info, req_id, is_last })
  })
  td.On('OnRspQryTradingCode', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryTradingCode', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrumentMarginRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInstrumentMarginRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrumentCommissionRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInstrumentCommissionRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQryExchange', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryExchange', { data, info, req_id, is_last })
  })
  td.On('OnRspQryProduct', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryProduct', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInstrument', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInstrument', { data, info, req_id, is_last })
  })
  td.On('OnRspQryDepthMarketData', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryDepthMarketData', { data, info, req_id, is_last })
  })
  td.On('OnRspQrySettlementInfo', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQrySettlementInfo', { data, info, req_id, is_last })
  })
  td.On('OnRspQryTransferBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryTransferBank', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorPositionDetail', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInvestorPositionDetail', { data, info, req_id, is_last })
  })
  td.On('OnRspQryNotice', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryNotice', { data, info, req_id, is_last })
  })
  td.On('OnRspQrySettlementInfoConfirm', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQrySettlementInfoConfirm', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorPositionCombineDetail', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInvestorPositionCombineDetail', { data, info, req_id, is_last })
  })
  td.On('OnRspQryCFMMCTradingAccountKey', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryCFMMCTradingAccountKey', { data, info, req_id, is_last })
  })
  td.On('OnRspQryEWarrantOffset', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryEWarrantOffset', { data, info, req_id, is_last })
  })
  td.On('OnRspQryInvestorProductGroupMargin', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryInvestorProductGroupMargin', { data, info, req_id, is_last })
  })
  td.On('OnRspQryExchangeMarginRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryExchangeMarginRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQryExchangeMarginRateAdjust', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryExchangeMarginRateAdjust', { data, info, req_id, is_last })
  })
  td.On('OnRspQryExchangeRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryExchangeRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQrySecAgentACIDMap', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQrySecAgentACIDMap', { data, info, req_id, is_last })
  })
  td.On('OnRspQryProductExchRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryProductExchRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQryOptionInstrTradeCost', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryOptionInstrTradeCost', { data, info, req_id, is_last })
  })
  td.On('OnRspQryOptionInstrCommRate', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryOptionInstrCommRate', { data, info, req_id, is_last })
  })
  td.On('OnRspQryExecOrder', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryExecOrder', { data, info, req_id, is_last })
  })
  td.On('OnRspQryForQuote', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryForQuote', { data, info, req_id, is_last })
  })
  td.On('OnRspQryQuote', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryQuote', { data, info, req_id, is_last })
  })
  td.On('OnRspQryCombInstrumentGuard', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryCombInstrumentGuard', { data, info, req_id, is_last })
  })
  td.On('OnRspQryCombAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryCombAction', { data, info, req_id, is_last })
  })
  td.On('OnRspQryTransferSerial', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryTransferSerial', { data, info, req_id, is_last })
  })
  td.On('OnRspQryAccountregister', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryAccountregister', { data, info, req_id, is_last })
  })
  td.On('OnRspError', (data, info, req_id, is_last) => {
    emitter.emit('OnRspError', { data, info, req_id, is_last })
  })
  td.On('OnRtnOrder', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnOrder', { data, info, req_id, is_last })
  })
  td.On('OnRtnTrade', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnTrade', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnOrderInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnOrderInsert', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRtnInstrumentStatus', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnInstrumentStatus', { data, info, req_id, is_last })
  })
  td.On('OnRtnTradingNotice', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnTradingNotice', { data, info, req_id, is_last })
  })
  td.On('OnRtnErrorConditionalOrder', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnErrorConditionalOrder', { data, info, req_id, is_last })
  })
  td.On('OnRtnExecOrder', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnExecOrder', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnExecOrderInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnExecOrderInsert', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnExecOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnExecOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnForQuoteInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnForQuoteInsert', { data, info, req_id, is_last })
  })
  td.On('OnRtnQuote', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnQuote', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnQuoteInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnQuoteInsert', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnQuoteAction', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnQuoteAction', { data, info, req_id, is_last })
  })
  td.On('OnRtnForQuoteRsp', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnForQuoteRsp', { data, info, req_id, is_last })
  })
  td.On('OnRtnCFMMCTradingAccountToken', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnCFMMCTradingAccountToken', { data, info, req_id, is_last })
  })
  td.On('OnRtnCombAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnCombAction', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnCombActionInsert', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnCombActionInsert', { data, info, req_id, is_last })
  })
  td.On('OnRspQryContractBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryContractBank', { data, info, req_id, is_last })
  })
  td.On('OnRspQryParkedOrder', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryParkedOrder', { data, info, req_id, is_last })
  })
  td.On('OnRspQryParkedOrderAction', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryParkedOrderAction', { data, info, req_id, is_last })
  })
  td.On('OnRspQryTradingNotice', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryTradingNotice', { data, info, req_id, is_last })
  })
  td.On('OnRspQryBrokerTradingParams', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryBrokerTradingParams', { data, info, req_id, is_last })
  })
  td.On('OnRspQryBrokerTradingAlgos', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQryBrokerTradingAlgos', { data, info, req_id, is_last })
  })
  td.On('OnRspQueryCFMMCTradingAccountToken', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQueryCFMMCTradingAccountToken', { data, info, req_id, is_last })
  })
  td.On('OnRtnFromBankToFutureByBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnFromBankToFutureByBank', { data, info, req_id, is_last })
  })
  td.On('OnRtnFromFutureToBankByBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnFromFutureToBankByBank', { data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromBankToFutureByBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnRepealFromBankToFutureByBank', { data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromFutureToBankByBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnRepealFromFutureToBankByBank', { data, info, req_id, is_last })
  })
  td.On('OnRtnFromBankToFutureByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnFromBankToFutureByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRtnFromFutureToBankByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnFromFutureToBankByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromBankToFutureByFutureManual', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnRepealFromBankToFutureByFutureManual', { data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromFutureToBankByFutureManual', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnRepealFromFutureToBankByFutureManual', { data, info, req_id, is_last })
  })
  td.On('OnRtnQueryBankBalanceByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnQueryBankBalanceByFuture', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnBankToFutureByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnBankToFutureByFuture', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnFutureToBankByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnFutureToBankByFuture', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnRepealBankToFutureByFutureManual', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnRepealBankToFutureByFutureManual', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnRepealFutureToBankByFutureManual', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnRepealFutureToBankByFutureManual', { data, info, req_id, is_last })
  })
  td.On('OnErrRtnQueryBankBalanceByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnErrRtnQueryBankBalanceByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromBankToFutureByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnRepealFromBankToFutureByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRtnRepealFromFutureToBankByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnRepealFromFutureToBankByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRspFromBankToFutureByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRspFromBankToFutureByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRspFromFutureToBankByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRspFromFutureToBankByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRspQueryBankAccountMoneyByFuture', (data, info, req_id, is_last) => {
    emitter.emit('OnRspQueryBankAccountMoneyByFuture', { data, info, req_id, is_last })
  })
  td.On('OnRtnOpenAccountByBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnOpenAccountByBank', { data, info, req_id, is_last })
  })
  td.On('OnRtnCancelAccountByBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnCancelAccountByBank', { data, info, req_id, is_last })
  })
  td.On('OnRtnChangeAccountByBank', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnChangeAccountByBank', { data, info, req_id, is_last })
  })
  return td
}

ctp.createMarket = () => {
  const emitter = new EventEmitter()
  const md = ctp.crmd()
  md.on = (event, func) => {
    emitter.on(event, func)
  }
  md.On('OnFrontConnected', (data, info, req_id, is_last) => {
    emitter.emit('OnFrontConnected', { data, info, req_id, is_last })
  })
  md.On('OnFrontDisconnected', (data, info, req_id, is_last) => {
    emitter.emit('OnFrontDisconnected', { data, info, req_id, is_last })
  })
  md.On('OnHeartBeatWarning', (data, info, req_id, is_last) => {
    emitter.emit('OnHeartBeatWarning', { data, info, req_id, is_last })
  })
  md.On('OnRspUserLogin', (data, info, req_id, is_last) => {
    emitter.emit('OnRspUserLogin', { data, info, req_id, is_last })
  })
  md.On('OnRspUserLogout', (data, info, req_id, is_last) => {
    emitter.emit('OnRspUserLogout', { data, info, req_id, is_last })
  })
  md.On('OnRspError', (data, info, req_id, is_last) => {
    emitter.emit('OnRspError', { data, info, req_id, is_last })
  })
  md.On('OnRspSubMarketData', (data, info, req_id, is_last) => {
    emitter.emit('OnRspSubMarketData', { data, info, req_id, is_last })
  })
  md.On('OnRspUnSubMarketData', (data, info, req_id, is_last) => {
    emitter.emit('OnRspUnSubMarketData', { data, info, req_id, is_last })
  })
  md.On('OnRspSubForQuoteRsp', (data, info, req_id, is_last) => {
    emitter.emit('OnRspSubForQuoteRsp', { data, info, req_id, is_last })
  })
  md.On('OnRspUnSubForQuoteRsp', (data, info, req_id, is_last) => {
    emitter.emit('OnRspUnSubForQuoteRsp', { data, info, req_id, is_last })
  })
  md.On('OnRtnDepthMarketData', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnDepthMarketData', { data, info, req_id, is_last })
  })
  md.On('OnRtnForQuoteRsp', (data, info, req_id, is_last) => {
    emitter.emit('OnRtnForQuoteRsp', { data, info, req_id, is_last })
  })
  return md
}

exports.ctp = ctp
