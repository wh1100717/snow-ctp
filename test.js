const { ctp, defineDict } = require('./index')

if (require.main === module) {
  const user_id = '092531'
  const password = 'sq3sj5dt2ryR'
  const broker_id = '9999'
  const td_uri = 'tcp://180.168.146.187:10001'
  const md_uri = 'tcp://180.168.146.187:10011'
  const ctp_td = ctp.createTrader()
  console.log(1)
  ctp_td.CreateFtdcTraderApi('./')
  console.log(2)
  ctp_td.RegisterFront(td_uri)
  console.log(3)
  ctp_td.SubscribePrivateTopic(2)
  console.log(4)
  ctp_td.SubscribePublicTopic(2)
  console.log(5)
  ctp_td.Init(6)
  console.log(7)
  ctp_td.ReqUserLogin({
    BrokerID: broker_id,
    UserID: user_id,
    Password: password
  }, 111)
  console.log(8)
  ctp_td.once('OnRspUserLogin', res => {
    const { data, info } = res
    console.log(data, info)
  })
}
