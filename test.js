const { ctp, defineDict } = require('./index')

ctp.settings({ log: true })

class CTP {
  constructor (config) {
    this.user_id = String(config.user_id)
    this.password = String(config.password)
    this.broker_id = String(config.broker_id)
    this.investor_id = String(config.investor_id || '')
    this.trade_front_addr = String(config.trade_front_addr)
    this.market_front_addr = String(config.market_front_addr)

    this.trade_api = ctp.createTrader()
    this.is_login = false
    this.balance = null
    this.instruments = null
  }
  login () {
    this.trade_api.On('OnFrontConnected', () => {
      this.trade_api.ReqUserLogin({
        BrokerID: this.broker_id,
        UserID: this.user_id,
        Password: this.password
      }, result => {
        console.log('ReqUserlogin', result)
      })
    })
    this.trade_api.On('OnRspUserLogin', (field, info, requestId, isLast) => {
      this.is_login = true
      this.OnRspUserLogin(field, info, requestId, isLast)
    })
    this.trade_api.On('OnRtnInstrumentStatus', (field, info, requestId, isLast) => {
      console.log(field)
    })
    this.trade_api.Connect(this.trade_front_addr, undefined, defineDict.THOST_TERT_QUICK, defineDict.THOST_TERT_QUICK, result => {
      console.log('connect', result)
    })
  }
  logout () {
    this.trade_api.on('OnRspUserLogout', (field, info, requestId, isLast) => {
      this.is_login = false
      this.OnRspUserLogout(field, info, requestId, isLast)
    })
    this.trade_api.ReqUserLogout({
      BrokerID: this.broker_id,
      UserID: this.user_id
    })
  }
  // 获取当前交易日
  getTradingDay () {
    return this.trade_api.GetTradingDay()
  }
  // 获取 Instrument 信息
  ReqQryInstrument (instrument_id, exchange_id) {
    try {
      this.trade_api.on('OnRspQryInstrument', (field, info, requestId, isLast) => {
        console.log(111111)
        this.OnRspQryInstrument(field, info, requestId, isLast)
      })
    } catch (error) {
      console.error(error)
    }
    this.trade_api.ReqQryInstrument(instrument_id, exchange_id)
  }
  // 查询账户信息
  reqQryTradingAccount () {
    this.trade_api.on('OnRspQryTradingAccount', (field, info, requestId, isLast) => {
      this.OnRspQryTradingAccount(field, info, requestId, isLast)
    })
    this.trade_api.ReqQryTradingAccount({
      BrokerID: this.broker_id,
      InvestorID: this.investor_id
    })
    // this.trade_api.reqQryTradingAccount(this.broker_id, this.investor_id)
  }
  // 查询持仓
  // 下单
  // 撤单
  OnRspUserLogin (field, info, requestId, isLast) {
    console.log('***********OnRspUserLogin*************')
  }
  OnRspUserLogout (field, info, requestId, isLast) {
    console.log('***********OnRspUserLogin*************')
  }
  OnRspQryTradingAccount (field, info, requestId, isLast) {
    console.log('***********OnRspQryTradingAccount*************')
    console.log(field, info, requestId, isLast)
  }
  OnRspQryInstrument (field, info, requestId, isLast) {
    console.log('***********OnRspQryInstrument*************')
    console.log(field, info, requestId, isLast)
  }
}

module.exports = CTP

if (require.main === module) {
  const ctp_client = new CTP({
    user_id: '092531',
    password: 'sq3sj5dt2ryR',
    broker_id: '9999',
    trade_front_addr: 'tcp://180.168.146.187:10001',
    market_front_addr: 'tcp://180.168.146.187:10011'
  })
  ctp_client.login()
  ctp_client.OnRspUserLogin = () => {
    // console.log(ctp_client.getTradingDay())
    // ctp_client.reqQryTradingAccount()
    // ctp_client.ReqQryInstrument('rb1901', 'SHFE')
  }
}
