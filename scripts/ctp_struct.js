const structDict = {}

// 信息分发
structDict['CThostFtdcDisseminationField'] = {
  // 序列系列号
  SequenceSeries: 'int',
  // 序列号
  SequenceNo: 'int'
}

// 用户登录请求
structDict['CThostFtdcReqUserLoginField'] = {
  // 交易日
  TradingDay: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 密码
  Password: 'string',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 接口端产品信息
  InterfaceProductInfo: 'string',
  // 协议信息
  ProtocolInfo: 'string',
  // Mac地址
  MacAddress: 'string',
  // 动态密码
  OneTimePassword: 'string',
  // 终端IP地址
  ClientIPAddress: 'string',
  // 登录备注
  LoginRemark: 'undefined'
}

// 用户登录应答
structDict['CThostFtdcRspUserLoginField'] = {
  // 交易日
  TradingDay: 'string',
  // 登录成功时间
  LoginTime: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 交易系统名称
  SystemName: 'string',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 最大报单引用
  MaxOrderRef: 'string',
  // 上期所时间
  SHFETime: 'string',
  // 大商所时间
  DCETime: 'string',
  // 郑商所时间
  CZCETime: 'string',
  // 中金所时间
  FFEXTime: 'string',
  // 能源中心时间
  INETime: 'string'
}

// 用户登出请求
structDict['CThostFtdcUserLogoutField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string'
}

// 强制交易员退出
structDict['CThostFtdcForceUserLogoutField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string'
}

// 客户端认证请求
structDict['CThostFtdcReqAuthenticateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 认证码
  AuthCode: 'string'
}

// 客户端认证响应
structDict['CThostFtdcRspAuthenticateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 用户端产品信息
  UserProductInfo: 'string'
}

// 客户端认证信息
structDict['CThostFtdcAuthenticationInfoField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 认证信息
  AuthInfo: 'string',
  // 是否为认证结果
  IsResult: 'int'
}

// 用户登录应答2
structDict['CThostFtdcRspUserLogin2Field'] = {
  // 交易日
  TradingDay: 'string',
  // 登录成功时间
  LoginTime: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 交易系统名称
  SystemName: 'string',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 最大报单引用
  MaxOrderRef: 'string',
  // 上期所时间
  SHFETime: 'string',
  // 大商所时间
  DCETime: 'string',
  // 郑商所时间
  CZCETime: 'string',
  // 中金所时间
  FFEXTime: 'string',
  // 能源中心时间
  INETime: 'string',
  // 随机串
  RandomString: 'undefined'
}

// 银期转帐报文头
structDict['CThostFtdcTransferHeaderField'] = {
  // 版本号，常量，1.0
  Version: 'string',
  // 交易代码，必填
  TradeCode: 'string',
  // 交易日期，必填，格式：yyyymmdd
  TradeDate: 'string',
  // 交易时间，必填，格式：hhmmss
  TradeTime: 'string',
  // 发起方流水号，N/A
  TradeSerial: 'string',
  // 期货公司代码，必填
  FutureID: 'string',
  // 银行代码，根据查询银行得到，必填
  BankID: 'string',
  // 银行分中心代码，根据查询银行得到，必填
  BankBrchID: 'string',
  // 操作员，N/A
  OperNo: 'string',
  // 交易设备类型，N/A
  DeviceID: 'string',
  // 记录数，N/A
  RecordNum: 'string',
  // 会话编号，N/A
  SessionID: 'int',
  // 请求编号，N/A
  RequestID: 'int'
}

// 银行资金转期货请求，TradeCode=202001
structDict['CThostFtdcTransferBankToFutureReqField'] = {
  // 期货资金账户
  FutureAccount: 'string',
  // 密码标志
  FuturePwdFlag: 'char',
  // 密码
  FutureAccPwd: 'string',
  // 转账金额
  TradeAmt: 'float',
  // 客户手续费
  CustFee: 'float',
  // 币种：RMB-人民币 USD-美圆 HKD-港元
  CurrencyCode: 'string'
}

// 银行资金转期货请求响应
structDict['CThostFtdcTransferBankToFutureRspField'] = {
  // 响应代码
  RetCode: 'string',
  // 响应信息
  RetInfo: 'string',
  // 资金账户
  FutureAccount: 'string',
  // 转帐金额
  TradeAmt: 'float',
  // 应收客户手续费
  CustFee: 'float',
  // 币种
  CurrencyCode: 'string'
}

// 期货资金转银行请求，TradeCode=202002
structDict['CThostFtdcTransferFutureToBankReqField'] = {
  // 期货资金账户
  FutureAccount: 'string',
  // 密码标志
  FuturePwdFlag: 'char',
  // 密码
  FutureAccPwd: 'string',
  // 转账金额
  TradeAmt: 'float',
  // 客户手续费
  CustFee: 'float',
  // 币种：RMB-人民币 USD-美圆 HKD-港元
  CurrencyCode: 'string'
}

// 期货资金转银行请求响应
structDict['CThostFtdcTransferFutureToBankRspField'] = {
  // 响应代码
  RetCode: 'string',
  // 响应信息
  RetInfo: 'string',
  // 资金账户
  FutureAccount: 'string',
  // 转帐金额
  TradeAmt: 'float',
  // 应收客户手续费
  CustFee: 'float',
  // 币种
  CurrencyCode: 'string'
}

// 查询银行资金请求，TradeCode=204002
structDict['CThostFtdcTransferQryBankReqField'] = {
  // 期货资金账户
  FutureAccount: 'string',
  // 密码标志
  FuturePwdFlag: 'char',
  // 密码
  FutureAccPwd: 'string',
  // 币种：RMB-人民币 USD-美圆 HKD-港元
  CurrencyCode: 'string'
}

// 查询银行资金请求响应
structDict['CThostFtdcTransferQryBankRspField'] = {
  // 响应代码
  RetCode: 'string',
  // 响应信息
  RetInfo: 'string',
  // 资金账户
  FutureAccount: 'string',
  // 银行余额
  TradeAmt: 'float',
  // 银行可用余额
  UseAmt: 'float',
  // 银行可取余额
  FetchAmt: 'float',
  // 币种
  CurrencyCode: 'string'
}

// 查询银行交易明细请求，TradeCode=204999
structDict['CThostFtdcTransferQryDetailReqField'] = {
  // 期货资金账户
  FutureAccount: 'string'
}

// 查询银行交易明细请求响应
structDict['CThostFtdcTransferQryDetailRspField'] = {
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 交易代码
  TradeCode: 'string',
  // 期货流水号
  FutureSerial: 'int',
  // 期货公司代码
  FutureID: 'string',
  // 资金帐号
  FutureAccount: 'string',
  // 银行流水号
  BankSerial: 'int',
  // 银行代码
  BankID: 'string',
  // 银行分中心代码
  BankBrchID: 'string',
  // 银行账号
  BankAccount: 'string',
  // 证件号码
  CertCode: 'string',
  // 货币代码
  CurrencyCode: 'string',
  // 发生金额
  TxAmount: 'float',
  // 有效标志
  Flag: 'char'
}

// 响应信息
structDict['CThostFtdcRspInfoField'] = {
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 交易所
structDict['CThostFtdcExchangeField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 交易所名称
  ExchangeName: 'string',
  // 交易所属性
  ExchangeProperty: 'char'
}

// 产品
structDict['CThostFtdcProductField'] = {
  // 产品代码
  ProductID: 'string',
  // 产品名称
  ProductName: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 产品类型
  ProductClass: 'char',
  // 合约数量乘数
  VolumeMultiple: 'int',
  // 最小变动价位
  PriceTick: 'float',
  // 市价单最大下单量
  MaxMarketOrderVolume: 'int',
  // 市价单最小下单量
  MinMarketOrderVolume: 'int',
  // 限价单最大下单量
  MaxLimitOrderVolume: 'int',
  // 限价单最小下单量
  MinLimitOrderVolume: 'int',
  // 持仓类型
  PositionType: 'char',
  // 持仓日期类型
  PositionDateType: 'char',
  // 平仓处理类型
  CloseDealType: 'char',
  // 交易币种类型
  TradeCurrencyID: 'string',
  // 质押资金可用范围
  MortgageFundUseRange: 'char',
  // 交易所产品代码
  ExchangeProductID: 'string',
  // 合约基础商品乘数
  UnderlyingMultiple: 'float'
}

// 合约
structDict['CThostFtdcInstrumentField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约名称
  InstrumentName: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 产品代码
  ProductID: 'string',
  // 产品类型
  ProductClass: 'char',
  // 交割年份
  DeliveryYear: 'int',
  // 交割月
  DeliveryMonth: 'int',
  // 市价单最大下单量
  MaxMarketOrderVolume: 'int',
  // 市价单最小下单量
  MinMarketOrderVolume: 'int',
  // 限价单最大下单量
  MaxLimitOrderVolume: 'int',
  // 限价单最小下单量
  MinLimitOrderVolume: 'int',
  // 合约数量乘数
  VolumeMultiple: 'int',
  // 最小变动价位
  PriceTick: 'float',
  // 创建日
  CreateDate: 'string',
  // 上市日
  OpenDate: 'string',
  // 到期日
  ExpireDate: 'string',
  // 开始交割日
  StartDelivDate: 'string',
  // 结束交割日
  EndDelivDate: 'string',
  // 合约生命周期状态
  InstLifePhase: 'char',
  // 当前是否交易
  IsTrading: 'int',
  // 持仓类型
  PositionType: 'char',
  // 持仓日期类型
  PositionDateType: 'char',
  // 多头保证金率
  LongMarginRatio: 'float',
  // 空头保证金率
  ShortMarginRatio: 'float',
  // 是否使用大额单边保证金算法
  MaxMarginSideAlgorithm: 'char',
  // 基础商品代码
  UnderlyingInstrID: 'string',
  // 执行价
  StrikePrice: 'float',
  // 期权类型
  OptionsType: 'char',
  // 合约基础商品乘数
  UnderlyingMultiple: 'float',
  // 组合类型
  CombinationType: 'char'
}

// 经纪公司
structDict['CThostFtdcBrokerField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 经纪公司简称
  BrokerAbbr: 'string',
  // 经纪公司名称
  BrokerName: 'string',
  // 是否活跃
  IsActive: 'int'
}

// 交易所交易员
structDict['CThostFtdcTraderField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 密码
  Password: 'string',
  // 安装数量
  InstallCount: 'int',
  // 经纪公司代码
  BrokerID: 'string'
}

// 投资者
structDict['CThostFtdcInvestorField'] = {
  // 投资者代码
  InvestorID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者分组代码
  InvestorGroupID: 'string',
  // 投资者名称
  InvestorName: 'string',
  // 证件类型
  IdentifiedCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 是否活跃
  IsActive: 'int',
  // 联系电话
  Telephone: 'string',
  // 通讯地址
  Address: 'string',
  // 开户日期
  OpenDate: 'string',
  // 手机
  Mobile: 'string',
  // 手续费率模板代码
  CommModelID: 'string',
  // 保证金率模板代码
  MarginModelID: 'string'
}

// 交易编码
structDict['CThostFtdcTradingCodeField'] = {
  // 投资者代码
  InvestorID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 客户代码
  ClientID: 'string',
  // 是否活跃
  IsActive: 'int',
  // 交易编码类型
  ClientIDType: 'stringType',
  // 营业部编号
  BranchID: 'string',
  // 业务类型
  BizType: 'char',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 会员编码和经纪公司编码对照表
structDict['CThostFtdcPartBrokerField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 是否活跃
  IsActive: 'int'
}

// 管理用户
structDict['CThostFtdcSuperUserField'] = {
  // 用户代码
  UserID: 'string',
  // 用户名称
  UserName: 'string',
  // 密码
  Password: 'string',
  // 是否活跃
  IsActive: 'int'
}

// 管理用户功能权限
structDict['CThostFtdcSuperUserFunctionField'] = {
  // 用户代码
  UserID: 'string',
  // 功能代码
  FunctionCode: 'char'
}

// 投资者组
structDict['CThostFtdcInvestorGroupField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者分组代码
  InvestorGroupID: 'string',
  // 投资者分组名称
  InvestorGroupName: 'string'
}

// 资金账户
structDict['CThostFtdcTradingAccountField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 上次质押金额
  PreMortgage: 'float',
  // 上次信用额度
  PreCredit: 'float',
  // 上次存款额
  PreDeposit: 'float',
  // 上次结算准备金
  PreBalance: 'float',
  // 上次占用的保证金
  PreMargin: 'float',
  // 利息基数
  InterestBase: 'float',
  // 利息收入
  Interest: 'float',
  // 入金金额
  Deposit: 'float',
  // 出金金额
  Withdraw: 'float',
  // 冻结的保证金
  FrozenMargin: 'float',
  // 冻结的资金
  FrozenCash: 'float',
  // 冻结的手续费
  FrozenCommission: 'float',
  // 当前保证金总额
  CurrMargin: 'float',
  // 资金差额
  CashIn: 'float',
  // 手续费
  Commission: 'float',
  // 平仓盈亏
  CloseProfit: 'float',
  // 持仓盈亏
  PositionProfit: 'float',
  // 期货结算准备金
  Balance: 'float',
  // 可用资金
  Available: 'float',
  // 可取资金
  WithdrawQuota: 'float',
  // 基本准备金
  Reserve: 'float',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 信用额度
  Credit: 'float',
  // 质押金额
  Mortgage: 'float',
  // 交易所保证金
  ExchangeMargin: 'float',
  // 投资者交割保证金
  DeliveryMargin: 'float',
  // 交易所交割保证金
  ExchangeDeliveryMargin: 'float',
  // 保底期货结算准备金
  ReserveBalance: 'float',
  // 币种代码
  CurrencyID: 'string',
  // 上次货币质入金额
  PreFundMortgageIn: 'float',
  // 上次货币质出金额
  PreFundMortgageOut: 'float',
  // 货币质入金额
  FundMortgageIn: 'float',
  // 货币质出金额
  FundMortgageOut: 'float',
  // 货币质押余额
  FundMortgageAvailable: 'float',
  // 可质押货币金额
  MortgageableFund: 'float',
  // 特殊产品占用保证金
  SpecProductMargin: 'float',
  // 特殊产品冻结保证金
  SpecProductFrozenMargin: 'float',
  // 特殊产品手续费
  SpecProductCommission: 'float',
  // 特殊产品冻结手续费
  SpecProductFrozenCommission: 'float',
  // 特殊产品持仓盈亏
  SpecProductPositionProfit: 'float',
  // 特殊产品平仓盈亏
  SpecProductCloseProfit: 'float',
  // 根据持仓盈亏算法计算的特殊产品持仓盈亏
  SpecProductPositionProfitByAlg: 'float',
  // 特殊产品交易所保证金
  SpecProductExchangeMargin: 'float',
  // 业务类型
  BizType: 'char',
  // 延时换汇冻结金额
  FrozenSwap: 'float',
  // 剩余换汇额度
  RemainSwap: 'float'
}

// 投资者持仓
structDict['CThostFtdcInvestorPositionField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 持仓多空方向
  PosiDirection: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 持仓日期
  PositionDate: 'char',
  // 上日持仓
  YdPosition: 'int',
  // 今日持仓
  Position: 'int',
  // 多头冻结
  LongFrozen: 'int',
  // 空头冻结
  ShortFrozen: 'int',
  // 开仓冻结金额
  LongFrozenAmount: 'float',
  // 开仓冻结金额
  ShortFrozenAmount: 'float',
  // 开仓量
  OpenVolume: 'int',
  // 平仓量
  CloseVolume: 'int',
  // 开仓金额
  OpenAmount: 'float',
  // 平仓金额
  CloseAmount: 'float',
  // 持仓成本
  PositionCost: 'float',
  // 上次占用的保证金
  PreMargin: 'float',
  // 占用的保证金
  UseMargin: 'float',
  // 冻结的保证金
  FrozenMargin: 'float',
  // 冻结的资金
  FrozenCash: 'float',
  // 冻结的手续费
  FrozenCommission: 'float',
  // 资金差额
  CashIn: 'float',
  // 手续费
  Commission: 'float',
  // 平仓盈亏
  CloseProfit: 'float',
  // 持仓盈亏
  PositionProfit: 'float',
  // 上次结算价
  PreSettlementPrice: 'float',
  // 本次结算价
  SettlementPrice: 'float',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 开仓成本
  OpenCost: 'float',
  // 交易所保证金
  ExchangeMargin: 'float',
  // 组合成交形成的持仓
  CombPosition: 'int',
  // 组合多头冻结
  CombLongFrozen: 'int',
  // 组合空头冻结
  CombShortFrozen: 'int',
  // 逐日盯市平仓盈亏
  CloseProfitByDate: 'float',
  // 逐笔对冲平仓盈亏
  CloseProfitByTrade: 'float',
  // 今日持仓
  TodayPosition: 'int',
  // 保证金率
  MarginRateByMoney: 'float',
  // 保证金率(按手数)
  MarginRateByVolume: 'float',
  // 执行冻结
  StrikeFrozen: 'int',
  // 执行冻结金额
  StrikeFrozenAmount: 'float',
  // 放弃执行冻结
  AbandonFrozen: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 执行冻结的昨仓
  YdStrikeFrozen: 'int',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 合约保证金率
structDict['CThostFtdcInstrumentMarginRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 多头保证金率
  LongMarginRatioByMoney: 'float',
  // 多头保证金费
  LongMarginRatioByVolume: 'float',
  // 空头保证金率
  ShortMarginRatioByMoney: 'float',
  // 空头保证金费
  ShortMarginRatioByVolume: 'float',
  // 是否相对交易所收取
  IsRelative: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 合约手续费率
structDict['CThostFtdcInstrumentCommissionRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 开仓手续费率
  OpenRatioByMoney: 'float',
  // 开仓手续费
  OpenRatioByVolume: 'float',
  // 平仓手续费率
  CloseRatioByMoney: 'float',
  // 平仓手续费
  CloseRatioByVolume: 'float',
  // 平今手续费率
  CloseTodayRatioByMoney: 'float',
  // 平今手续费
  CloseTodayRatioByVolume: 'float',
  // 交易所代码
  ExchangeID: 'string',
  // 业务类型
  BizType: 'char',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 深度行情
structDict['CThostFtdcDepthMarketDataField'] = {
  // 交易日
  TradingDay: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 最新价
  LastPrice: 'float',
  // 上次结算价
  PreSettlementPrice: 'float',
  // 昨收盘
  PreClosePrice: 'float',
  // 昨持仓量
  PreOpenInterest: 'float',
  // 今开盘
  OpenPrice: 'float',
  // 最高价
  HighestPrice: 'float',
  // 最低价
  LowestPrice: 'float',
  // 数量
  Volume: 'int',
  // 成交金额
  Turnover: 'float',
  // 持仓量
  OpenInterest: 'float',
  // 今收盘
  ClosePrice: 'float',
  // 本次结算价
  SettlementPrice: 'float',
  // 涨停板价
  UpperLimitPrice: 'float',
  // 跌停板价
  LowerLimitPrice: 'float',
  // 昨虚实度
  PreDelta: 'float',
  // 今虚实度
  CurrDelta: 'float',
  // 最后修改时间
  UpdateTime: 'string',
  // 最后修改毫秒
  UpdateMillisec: 'int',
  // 申买价一
  BidPrice1: 'float',
  // 申买量一
  BidVolume1: 'int',
  // 申卖价一
  AskPrice1: 'float',
  // 申卖量一
  AskVolume1: 'int',
  // 申买价二
  BidPrice2: 'float',
  // 申买量二
  BidVolume2: 'int',
  // 申卖价二
  AskPrice2: 'float',
  // 申卖量二
  AskVolume2: 'int',
  // 申买价三
  BidPrice3: 'float',
  // 申买量三
  BidVolume3: 'int',
  // 申卖价三
  AskPrice3: 'float',
  // 申卖量三
  AskVolume3: 'int',
  // 申买价四
  BidPrice4: 'float',
  // 申买量四
  BidVolume4: 'int',
  // 申卖价四
  AskPrice4: 'float',
  // 申卖量四
  AskVolume4: 'int',
  // 申买价五
  BidPrice5: 'float',
  // 申买量五
  BidVolume5: 'int',
  // 申卖价五
  AskPrice5: 'float',
  // 申卖量五
  AskVolume5: 'int',
  // 当日均价
  AveragePrice: 'float',
  // 业务日期
  ActionDay: 'string'
}

// 投资者合约交易权限
structDict['CThostFtdcInstrumentTradingRightField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易权限
  TradingRight: 'char'
}

// 经纪公司用户
structDict['CThostFtdcBrokerUserField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 用户名称
  UserName: 'string',
  // 用户类型
  UserType: 'char',
  // 是否活跃
  IsActive: 'int',
  // 是否使用令牌
  IsUsingOTP: 'int',
  // 是否强制终端认证
  IsAuthForce: 'int'
}

// 经纪公司用户口令
structDict['CThostFtdcBrokerUserPasswordField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 密码
  Password: 'string',
  // 上次修改时间
  LastUpdateTime: 'undefined',
  // 上次登陆时间
  LastLoginTime: 'undefined',
  // 密码过期时间
  ExpireDate: 'string',
  // 弱密码过期时间
  WeakExpireDate: 'string'
}

// 经纪公司用户功能权限
structDict['CThostFtdcBrokerUserFunctionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 经纪公司功能代码
  BrokerFunctionCode: 'char'
}

// 交易所交易员报盘机
structDict['CThostFtdcTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 交易所交易员连接状态
  TraderConnectStatus: 'char',
  // 发出连接请求的日期
  ConnectRequestDate: 'string',
  // 发出连接请求的时间
  ConnectRequestTime: 'string',
  // 上次报告日期
  LastReportDate: 'string',
  // 上次报告时间
  LastReportTime: 'string',
  // 完成连接日期
  ConnectDate: 'string',
  // 完成连接时间
  ConnectTime: 'string',
  // 启动日期
  StartDate: 'string',
  // 启动时间
  StartTime: 'string',
  // 交易日
  TradingDay: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 本席位最大成交编号
  MaxTradeID: 'string',
  // 本席位最大报单备拷
  MaxOrderMessageReference: 'string'
}

// 投资者结算结果
structDict['CThostFtdcSettlementInfoField'] = {
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 序号
  SequenceNo: 'int',
  // 消息正文
  Content: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 合约保证金率调整
structDict['CThostFtdcInstrumentMarginRateAdjustField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 多头保证金率
  LongMarginRatioByMoney: 'float',
  // 多头保证金费
  LongMarginRatioByVolume: 'float',
  // 空头保证金率
  ShortMarginRatioByMoney: 'float',
  // 空头保证金费
  ShortMarginRatioByVolume: 'float',
  // 是否相对交易所收取
  IsRelative: 'int'
}

// 交易所保证金率
structDict['CThostFtdcExchangeMarginRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 多头保证金率
  LongMarginRatioByMoney: 'float',
  // 多头保证金费
  LongMarginRatioByVolume: 'float',
  // 空头保证金率
  ShortMarginRatioByMoney: 'float',
  // 空头保证金费
  ShortMarginRatioByVolume: 'float',
  // 交易所代码
  ExchangeID: 'string'
}

// 交易所保证金率调整
structDict['CThostFtdcExchangeMarginRateAdjustField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 跟随交易所投资者多头保证金率
  LongMarginRatioByMoney: 'float',
  // 跟随交易所投资者多头保证金费
  LongMarginRatioByVolume: 'float',
  // 跟随交易所投资者空头保证金率
  ShortMarginRatioByMoney: 'float',
  // 跟随交易所投资者空头保证金费
  ShortMarginRatioByVolume: 'float',
  // 交易所多头保证金率
  ExchLongMarginRatioByMoney: 'float',
  // 交易所多头保证金费
  ExchLongMarginRatioByVolume: 'float',
  // 交易所空头保证金率
  ExchShortMarginRatioByMoney: 'float',
  // 交易所空头保证金费
  ExchShortMarginRatioByVolume: 'float',
  // 不跟随交易所投资者多头保证金率
  NoLongMarginRatioByMoney: 'float',
  // 不跟随交易所投资者多头保证金费
  NoLongMarginRatioByVolume: 'float',
  // 不跟随交易所投资者空头保证金率
  NoShortMarginRatioByMoney: 'float',
  // 不跟随交易所投资者空头保证金费
  NoShortMarginRatioByVolume: 'float'
}

// 汇率
structDict['CThostFtdcExchangeRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 源币种
  FromCurrencyID: 'string',
  // 源币种单位数量
  FromCurrencyUnit: 'float',
  // 目标币种
  ToCurrencyID: 'string',
  // 汇率
  ExchangeRate: 'float'
}

// 结算引用
structDict['CThostFtdcSettlementRefField'] = {
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int'
}

// 当前时间
structDict['CThostFtdcCurrentTimeField'] = {
  // 当前日期
  CurrDate: 'string',
  // 当前时间
  CurrTime: 'string',
  // 当前时间（毫秒）
  CurrMillisec: 'int',
  // 业务日期
  ActionDay: 'string'
}

// 通讯阶段
structDict['CThostFtdcCommPhaseField'] = {
  // 交易日
  TradingDay: 'string',
  // 通讯时段编号
  CommPhaseNo: 'int',
  // 系统编号
  SystemID: 'string'
}

// 登录信息
structDict['CThostFtdcLoginInfoField'] = {
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 登录日期
  LoginDate: 'string',
  // 登录时间
  LoginTime: 'string',
  // IP地址
  IPAddress: 'string',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 接口端产品信息
  InterfaceProductInfo: 'string',
  // 协议信息
  ProtocolInfo: 'string',
  // 系统名称
  SystemName: 'string',
  // 密码,已弃用
  PasswordDeprecated: 'string',
  // 最大报单引用
  MaxOrderRef: 'string',
  // 上期所时间
  SHFETime: 'string',
  // 大商所时间
  DCETime: 'string',
  // 郑商所时间
  CZCETime: 'string',
  // 中金所时间
  FFEXTime: 'string',
  // Mac地址
  MacAddress: 'string',
  // 动态密码
  OneTimePassword: 'string',
  // 能源中心时间
  INETime: 'string',
  // 查询时是否需要流控
  IsQryControl: 'int',
  // 登录备注
  LoginRemark: 'undefined',
  // 密码
  Password: 'string'
}

// 登录信息
structDict['CThostFtdcLogoutAllField'] = {
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 系统名称
  SystemName: 'string'
}

// 前置状态
structDict['CThostFtdcFrontStatusField'] = {
  // 前置编号
  FrontID: 'int',
  // 上次报告日期
  LastReportDate: 'string',
  // 上次报告时间
  LastReportTime: 'string',
  // 是否活跃
  IsActive: 'int'
}

// 用户口令变更
structDict['CThostFtdcUserPasswordUpdateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 原来的口令
  OldPassword: 'string',
  // 新的口令
  NewPassword: 'string'
}

// 输入报单
structDict['CThostFtdcInputOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报单引用
  OrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 报单价格条件
  OrderPriceType: 'char',
  // 买卖方向
  Direction: 'char',
  // 组合开平标志
  CombOffsetFlag: 'string',
  // 组合投机套保标志
  CombHedgeFlag: 'string',
  // 价格
  LimitPrice: 'float',
  // 数量
  VolumeTotalOriginal: 'int',
  // 有效期类型
  TimeCondition: 'char',
  // GTD日期
  GTDDate: 'string',
  // 成交量类型
  VolumeCondition: 'char',
  // 最小成交量
  MinVolume: 'int',
  // 触发条件
  ContingentCondition: 'char',
  // 止损价
  StopPrice: 'float',
  // 强平原因
  ForceCloseReason: 'char',
  // 自动挂起标志
  IsAutoSuspend: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 请求编号
  RequestID: 'int',
  // 用户强评标志
  UserForceClose: 'int',
  // 互换单标志
  IsSwapOrder: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 交易编码
  ClientID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 报单
structDict['CThostFtdcOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报单引用
  OrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 报单价格条件
  OrderPriceType: 'char',
  // 买卖方向
  Direction: 'char',
  // 组合开平标志
  CombOffsetFlag: 'string',
  // 组合投机套保标志
  CombHedgeFlag: 'string',
  // 价格
  LimitPrice: 'float',
  // 数量
  VolumeTotalOriginal: 'int',
  // 有效期类型
  TimeCondition: 'char',
  // GTD日期
  GTDDate: 'string',
  // 成交量类型
  VolumeCondition: 'char',
  // 最小成交量
  MinVolume: 'int',
  // 触发条件
  ContingentCondition: 'char',
  // 止损价
  StopPrice: 'float',
  // 强平原因
  ForceCloseReason: 'char',
  // 自动挂起标志
  IsAutoSuspend: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 请求编号
  RequestID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 报单提交状态
  OrderSubmitStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 报单编号
  OrderSysID: 'string',
  // 报单来源
  OrderSource: 'char',
  // 报单状态
  OrderStatus: 'char',
  // 报单类型
  OrderType: 'char',
  // 今成交数量
  VolumeTraded: 'int',
  // 剩余数量
  VolumeTotal: 'int',
  // 报单日期
  InsertDate: 'string',
  // 委托时间
  InsertTime: 'string',
  // 激活时间
  ActiveTime: 'string',
  // 挂起时间
  SuspendTime: 'string',
  // 最后修改时间
  UpdateTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 最后修改交易所交易员代码
  ActiveTraderID: 'string',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 用户强评标志
  UserForceClose: 'int',
  // 操作用户代码
  ActiveUserID: 'string',
  // 经纪公司报单编号
  BrokerOrderSeq: 'int',
  // 相关报单
  RelativeOrderSysID: 'string',
  // 郑商所成交数量
  ZCETotalTradedVolume: 'int',
  // 互换单标志
  IsSwapOrder: 'int',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所报单
structDict['CThostFtdcExchangeOrderField'] = {
  // 报单价格条件
  OrderPriceType: 'char',
  // 买卖方向
  Direction: 'char',
  // 组合开平标志
  CombOffsetFlag: 'string',
  // 组合投机套保标志
  CombHedgeFlag: 'string',
  // 价格
  LimitPrice: 'float',
  // 数量
  VolumeTotalOriginal: 'int',
  // 有效期类型
  TimeCondition: 'char',
  // GTD日期
  GTDDate: 'string',
  // 成交量类型
  VolumeCondition: 'char',
  // 最小成交量
  MinVolume: 'int',
  // 触发条件
  ContingentCondition: 'char',
  // 止损价
  StopPrice: 'float',
  // 强平原因
  ForceCloseReason: 'char',
  // 自动挂起标志
  IsAutoSuspend: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 请求编号
  RequestID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 报单提交状态
  OrderSubmitStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 报单编号
  OrderSysID: 'string',
  // 报单来源
  OrderSource: 'char',
  // 报单状态
  OrderStatus: 'char',
  // 报单类型
  OrderType: 'char',
  // 今成交数量
  VolumeTraded: 'int',
  // 剩余数量
  VolumeTotal: 'int',
  // 报单日期
  InsertDate: 'string',
  // 委托时间
  InsertTime: 'string',
  // 激活时间
  ActiveTime: 'string',
  // 挂起时间
  SuspendTime: 'string',
  // 最后修改时间
  UpdateTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 最后修改交易所交易员代码
  ActiveTraderID: 'string',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 营业部编号
  BranchID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所报单插入失败
structDict['CThostFtdcExchangeOrderInsertErrorField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 输入报单操作
structDict['CThostFtdcInputOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报单操作引用
  OrderActionRef: 'int',
  // 报单引用
  OrderRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 价格
  LimitPrice: 'float',
  // 数量变化
  VolumeChange: 'int',
  // 用户代码
  UserID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 报单操作
structDict['CThostFtdcOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报单操作引用
  OrderActionRef: 'int',
  // 报单引用
  OrderRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 价格
  LimitPrice: 'float',
  // 数量变化
  VolumeChange: 'int',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所报单操作
structDict['CThostFtdcExchangeOrderActionField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 价格
  LimitPrice: 'float',
  // 数量变化
  VolumeChange: 'int',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 营业部编号
  BranchID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所报单操作失败
structDict['CThostFtdcExchangeOrderActionErrorField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 交易所成交
structDict['CThostFtdcExchangeTradeField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 成交编号
  TradeID: 'string',
  // 买卖方向
  Direction: 'char',
  // 报单编号
  OrderSysID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 交易角色
  TradingRole: 'char',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 价格
  Price: 'float',
  // 数量
  Volume: 'int',
  // 成交时期
  TradeDate: 'string',
  // 成交时间
  TradeTime: 'string',
  // 成交类型
  TradeType: 'char',
  // 成交价来源
  PriceSource: 'char',
  // 交易所交易员代码
  TraderID: 'string',
  // 本地报单编号
  OrderLocalID: 'string',
  // 结算会员编号
  ClearingPartID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 序号
  SequenceNo: 'int',
  // 成交来源
  TradeSource: 'char'
}

// 成交
structDict['CThostFtdcTradeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报单引用
  OrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 成交编号
  TradeID: 'string',
  // 买卖方向
  Direction: 'char',
  // 报单编号
  OrderSysID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 交易角色
  TradingRole: 'char',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 价格
  Price: 'float',
  // 数量
  Volume: 'int',
  // 成交时期
  TradeDate: 'string',
  // 成交时间
  TradeTime: 'string',
  // 成交类型
  TradeType: 'char',
  // 成交价来源
  PriceSource: 'char',
  // 交易所交易员代码
  TraderID: 'string',
  // 本地报单编号
  OrderLocalID: 'string',
  // 结算会员编号
  ClearingPartID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 序号
  SequenceNo: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 经纪公司报单编号
  BrokerOrderSeq: 'int',
  // 成交来源
  TradeSource: 'char',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 用户会话
structDict['CThostFtdcUserSessionField'] = {
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 登录日期
  LoginDate: 'string',
  // 登录时间
  LoginTime: 'string',
  // IP地址
  IPAddress: 'string',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 接口端产品信息
  InterfaceProductInfo: 'string',
  // 协议信息
  ProtocolInfo: 'string',
  // Mac地址
  MacAddress: 'string',
  // 登录备注
  LoginRemark: 'undefined'
}

// 查询最大报单数量
structDict['CThostFtdcQueryMaxOrderVolumeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 买卖方向
  Direction: 'char',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 最大允许报单数量
  MaxVolume: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 投资者结算结果确认信息
structDict['CThostFtdcSettlementInfoConfirmField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 确认日期
  ConfirmDate: 'string',
  // 确认时间
  ConfirmTime: 'string',
  // 结算编号
  SettlementID: 'int',
  // 投资者帐号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 出入金同步
structDict['CThostFtdcSyncDepositField'] = {
  // 出入金流水号
  DepositSeqNo: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 入金金额
  Deposit: 'float',
  // 是否强制进行
  IsForce: 'int',
  // 币种代码
  CurrencyID: 'string'
}

// 货币质押同步
structDict['CThostFtdcSyncFundMortgageField'] = {
  // 货币质押流水号
  MortgageSeqNo: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 源币种
  FromCurrencyID: 'string',
  // 质押金额
  MortgageAmount: 'float',
  // 目标币种
  ToCurrencyID: 'string'
}

// 经纪公司同步
structDict['CThostFtdcBrokerSyncField'] = {
  // 经纪公司代码
  BrokerID: 'string'
}

// 正在同步中的投资者
structDict['CThostFtdcSyncingInvestorField'] = {
  // 投资者代码
  InvestorID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者分组代码
  InvestorGroupID: 'string',
  // 投资者名称
  InvestorName: 'string',
  // 证件类型
  IdentifiedCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 是否活跃
  IsActive: 'int',
  // 联系电话
  Telephone: 'string',
  // 通讯地址
  Address: 'string',
  // 开户日期
  OpenDate: 'string',
  // 手机
  Mobile: 'string',
  // 手续费率模板代码
  CommModelID: 'string',
  // 保证金率模板代码
  MarginModelID: 'string'
}

// 正在同步中的交易代码
structDict['CThostFtdcSyncingTradingCodeField'] = {
  // 投资者代码
  InvestorID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 客户代码
  ClientID: 'string',
  // 是否活跃
  IsActive: 'int',
  // 交易编码类型
  ClientIDType: 'stringType'
}

// 正在同步中的投资者分组
structDict['CThostFtdcSyncingInvestorGroupField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者分组代码
  InvestorGroupID: 'string',
  // 投资者分组名称
  InvestorGroupName: 'string'
}

// 正在同步中的交易账号
structDict['CThostFtdcSyncingTradingAccountField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 上次质押金额
  PreMortgage: 'float',
  // 上次信用额度
  PreCredit: 'float',
  // 上次存款额
  PreDeposit: 'float',
  // 上次结算准备金
  PreBalance: 'float',
  // 上次占用的保证金
  PreMargin: 'float',
  // 利息基数
  InterestBase: 'float',
  // 利息收入
  Interest: 'float',
  // 入金金额
  Deposit: 'float',
  // 出金金额
  Withdraw: 'float',
  // 冻结的保证金
  FrozenMargin: 'float',
  // 冻结的资金
  FrozenCash: 'float',
  // 冻结的手续费
  FrozenCommission: 'float',
  // 当前保证金总额
  CurrMargin: 'float',
  // 资金差额
  CashIn: 'float',
  // 手续费
  Commission: 'float',
  // 平仓盈亏
  CloseProfit: 'float',
  // 持仓盈亏
  PositionProfit: 'float',
  // 期货结算准备金
  Balance: 'float',
  // 可用资金
  Available: 'float',
  // 可取资金
  WithdrawQuota: 'float',
  // 基本准备金
  Reserve: 'float',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 信用额度
  Credit: 'float',
  // 质押金额
  Mortgage: 'float',
  // 交易所保证金
  ExchangeMargin: 'float',
  // 投资者交割保证金
  DeliveryMargin: 'float',
  // 交易所交割保证金
  ExchangeDeliveryMargin: 'float',
  // 保底期货结算准备金
  ReserveBalance: 'float',
  // 币种代码
  CurrencyID: 'string',
  // 上次货币质入金额
  PreFundMortgageIn: 'float',
  // 上次货币质出金额
  PreFundMortgageOut: 'float',
  // 货币质入金额
  FundMortgageIn: 'float',
  // 货币质出金额
  FundMortgageOut: 'float',
  // 货币质押余额
  FundMortgageAvailable: 'float',
  // 可质押货币金额
  MortgageableFund: 'float',
  // 特殊产品占用保证金
  SpecProductMargin: 'float',
  // 特殊产品冻结保证金
  SpecProductFrozenMargin: 'float',
  // 特殊产品手续费
  SpecProductCommission: 'float',
  // 特殊产品冻结手续费
  SpecProductFrozenCommission: 'float',
  // 特殊产品持仓盈亏
  SpecProductPositionProfit: 'float',
  // 特殊产品平仓盈亏
  SpecProductCloseProfit: 'float',
  // 根据持仓盈亏算法计算的特殊产品持仓盈亏
  SpecProductPositionProfitByAlg: 'float',
  // 特殊产品交易所保证金
  SpecProductExchangeMargin: 'float',
  // 延时换汇冻结金额
  FrozenSwap: 'float',
  // 剩余换汇额度
  RemainSwap: 'float'
}

// 正在同步中的投资者持仓
structDict['CThostFtdcSyncingInvestorPositionField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 持仓多空方向
  PosiDirection: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 持仓日期
  PositionDate: 'char',
  // 上日持仓
  YdPosition: 'int',
  // 今日持仓
  Position: 'int',
  // 多头冻结
  LongFrozen: 'int',
  // 空头冻结
  ShortFrozen: 'int',
  // 开仓冻结金额
  LongFrozenAmount: 'float',
  // 开仓冻结金额
  ShortFrozenAmount: 'float',
  // 开仓量
  OpenVolume: 'int',
  // 平仓量
  CloseVolume: 'int',
  // 开仓金额
  OpenAmount: 'float',
  // 平仓金额
  CloseAmount: 'float',
  // 持仓成本
  PositionCost: 'float',
  // 上次占用的保证金
  PreMargin: 'float',
  // 占用的保证金
  UseMargin: 'float',
  // 冻结的保证金
  FrozenMargin: 'float',
  // 冻结的资金
  FrozenCash: 'float',
  // 冻结的手续费
  FrozenCommission: 'float',
  // 资金差额
  CashIn: 'float',
  // 手续费
  Commission: 'float',
  // 平仓盈亏
  CloseProfit: 'float',
  // 持仓盈亏
  PositionProfit: 'float',
  // 上次结算价
  PreSettlementPrice: 'float',
  // 本次结算价
  SettlementPrice: 'float',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 开仓成本
  OpenCost: 'float',
  // 交易所保证金
  ExchangeMargin: 'float',
  // 组合成交形成的持仓
  CombPosition: 'int',
  // 组合多头冻结
  CombLongFrozen: 'int',
  // 组合空头冻结
  CombShortFrozen: 'int',
  // 逐日盯市平仓盈亏
  CloseProfitByDate: 'float',
  // 逐笔对冲平仓盈亏
  CloseProfitByTrade: 'float',
  // 今日持仓
  TodayPosition: 'int',
  // 保证金率
  MarginRateByMoney: 'float',
  // 保证金率(按手数)
  MarginRateByVolume: 'float',
  // 执行冻结
  StrikeFrozen: 'int',
  // 执行冻结金额
  StrikeFrozenAmount: 'float',
  // 放弃执行冻结
  AbandonFrozen: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 执行冻结的昨仓
  YdStrikeFrozen: 'int',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 正在同步中的合约保证金率
structDict['CThostFtdcSyncingInstrumentMarginRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 多头保证金率
  LongMarginRatioByMoney: 'float',
  // 多头保证金费
  LongMarginRatioByVolume: 'float',
  // 空头保证金率
  ShortMarginRatioByMoney: 'float',
  // 空头保证金费
  ShortMarginRatioByVolume: 'float',
  // 是否相对交易所收取
  IsRelative: 'int'
}

// 正在同步中的合约手续费率
structDict['CThostFtdcSyncingInstrumentCommissionRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 开仓手续费率
  OpenRatioByMoney: 'float',
  // 开仓手续费
  OpenRatioByVolume: 'float',
  // 平仓手续费率
  CloseRatioByMoney: 'float',
  // 平仓手续费
  CloseRatioByVolume: 'float',
  // 平今手续费率
  CloseTodayRatioByMoney: 'float',
  // 平今手续费
  CloseTodayRatioByVolume: 'float'
}

// 正在同步中的合约交易权限
structDict['CThostFtdcSyncingInstrumentTradingRightField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易权限
  TradingRight: 'char'
}

// 查询报单
structDict['CThostFtdcQryOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 开始时间
  InsertTimeStart: 'string',
  // 结束时间
  InsertTimeEnd: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询成交
structDict['CThostFtdcQryTradeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 成交编号
  TradeID: 'string',
  // 开始时间
  TradeTimeStart: 'string',
  // 结束时间
  TradeTimeEnd: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询投资者持仓
structDict['CThostFtdcQryInvestorPositionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询资金账户
structDict['CThostFtdcQryTradingAccountField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 业务类型
  BizType: 'char',
  // 投资者帐号
  AccountID: 'string'
}

// 查询投资者
structDict['CThostFtdcQryInvestorField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

// 查询交易编码
structDict['CThostFtdcQryTradingCodeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 客户代码
  ClientID: 'string',
  // 交易编码类型
  ClientIDType: 'stringType',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询投资者组
structDict['CThostFtdcQryInvestorGroupField'] = {
  // 经纪公司代码
  BrokerID: 'string'
}

// 查询合约保证金率
structDict['CThostFtdcQryInstrumentMarginRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询手续费率
structDict['CThostFtdcQryInstrumentCommissionRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询合约交易权限
structDict['CThostFtdcQryInstrumentTradingRightField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string'
}

// 查询经纪公司
structDict['CThostFtdcQryBrokerField'] = {
  // 经纪公司代码
  BrokerID: 'string'
}

// 查询交易员
structDict['CThostFtdcQryTraderField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 查询管理用户功能权限
structDict['CThostFtdcQrySuperUserFunctionField'] = {
  // 用户代码
  UserID: 'string'
}

// 查询用户会话
structDict['CThostFtdcQryUserSessionField'] = {
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string'
}

// 查询经纪公司会员代码
structDict['CThostFtdcQryPartBrokerField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 会员代码
  ParticipantID: 'string'
}

// 查询前置状态
structDict['CThostFtdcQryFrontStatusField'] = {
  // 前置编号
  FrontID: 'int'
}

// 查询交易所报单
structDict['CThostFtdcQryExchangeOrderField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 查询报单操作
structDict['CThostFtdcQryOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 查询交易所报单操作
structDict['CThostFtdcQryExchangeOrderActionField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 查询管理用户
structDict['CThostFtdcQrySuperUserField'] = {
  // 用户代码
  UserID: 'string'
}

// 查询交易所
structDict['CThostFtdcQryExchangeField'] = {
  // 交易所代码
  ExchangeID: 'string'
}

// 查询产品
structDict['CThostFtdcQryProductField'] = {
  // 产品代码
  ProductID: 'string',
  // 产品类型
  ProductClass: 'char',
  // 交易所代码
  ExchangeID: 'string'
}

// 查询合约
structDict['CThostFtdcQryInstrumentField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 产品代码
  ProductID: 'string'
}

// 查询行情
structDict['CThostFtdcQryDepthMarketDataField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 查询经纪公司用户
structDict['CThostFtdcQryBrokerUserField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string'
}

// 查询经纪公司用户权限
structDict['CThostFtdcQryBrokerUserFunctionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string'
}

// 查询交易员报盘机
structDict['CThostFtdcQryTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 查询出入金流水
structDict['CThostFtdcQrySyncDepositField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 出入金流水号
  DepositSeqNo: 'string'
}

// 查询投资者结算结果
structDict['CThostFtdcQrySettlementInfoField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易日
  TradingDay: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 查询交易所保证金率
structDict['CThostFtdcQryExchangeMarginRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 交易所代码
  ExchangeID: 'string'
}

// 查询交易所调整保证金率
structDict['CThostFtdcQryExchangeMarginRateAdjustField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char'
}

// 查询汇率
structDict['CThostFtdcQryExchangeRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 源币种
  FromCurrencyID: 'string',
  // 目标币种
  ToCurrencyID: 'string'
}

// 查询货币质押流水
structDict['CThostFtdcQrySyncFundMortgageField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 货币质押流水号
  MortgageSeqNo: 'string'
}

// 查询报单
structDict['CThostFtdcQryHisOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 开始时间
  InsertTimeStart: 'string',
  // 结束时间
  InsertTimeEnd: 'string',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int'
}

// 当前期权合约最小保证金
structDict['CThostFtdcOptionInstrMiniMarginField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 单位（手）期权合约最小保证金
  MinMargin: 'float',
  // 取值方式
  ValueMethod: 'char',
  // 是否跟随交易所收取
  IsRelative: 'int'
}

// 当前期权合约保证金调整系数
structDict['CThostFtdcOptionInstrMarginAdjustField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投机空头保证金调整系数
  SShortMarginRatioByMoney: 'float',
  // 投机空头保证金调整系数
  SShortMarginRatioByVolume: 'float',
  // 保值空头保证金调整系数
  HShortMarginRatioByMoney: 'float',
  // 保值空头保证金调整系数
  HShortMarginRatioByVolume: 'float',
  // 套利空头保证金调整系数
  AShortMarginRatioByMoney: 'float',
  // 套利空头保证金调整系数
  AShortMarginRatioByVolume: 'float',
  // 是否跟随交易所收取
  IsRelative: 'int',
  // 做市商空头保证金调整系数
  MShortMarginRatioByMoney: 'float',
  // 做市商空头保证金调整系数
  MShortMarginRatioByVolume: 'float'
}

// 当前期权合约手续费的详细内容
structDict['CThostFtdcOptionInstrCommRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 开仓手续费率
  OpenRatioByMoney: 'float',
  // 开仓手续费
  OpenRatioByVolume: 'float',
  // 平仓手续费率
  CloseRatioByMoney: 'float',
  // 平仓手续费
  CloseRatioByVolume: 'float',
  // 平今手续费率
  CloseTodayRatioByMoney: 'float',
  // 平今手续费
  CloseTodayRatioByVolume: 'float',
  // 执行手续费率
  StrikeRatioByMoney: 'float',
  // 执行手续费
  StrikeRatioByVolume: 'float',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 期权交易成本
structDict['CThostFtdcOptionInstrTradeCostField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 期权合约保证金不变部分
  FixedMargin: 'float',
  // 期权合约最小保证金
  MiniMargin: 'float',
  // 期权合约权利金
  Royalty: 'float',
  // 交易所期权合约保证金不变部分
  ExchFixedMargin: 'float',
  // 交易所期权合约最小保证金
  ExchMiniMargin: 'float',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 期权交易成本查询
structDict['CThostFtdcQryOptionInstrTradeCostField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 期权合约报价
  InputPrice: 'float',
  // 标的价格,填0则用昨结算价
  UnderlyingPrice: 'float',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 期权手续费率查询
structDict['CThostFtdcQryOptionInstrCommRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 股指现货指数
structDict['CThostFtdcIndexPriceField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 指数现货收盘价
  ClosePrice: 'float'
}

// 输入的执行宣告
structDict['CThostFtdcInputExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 执行宣告引用
  ExecOrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 数量
  Volume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 执行类型
  ActionType: 'char',
  // 保留头寸申请的持仓方向
  PosiDirection: 'char',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'char',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'char',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 交易编码
  ClientID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 输入执行宣告操作
structDict['CThostFtdcInputExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 执行宣告操作引用
  ExecOrderActionRef: 'int',
  // 执行宣告引用
  ExecOrderRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 执行宣告操作编号
  ExecOrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 用户代码
  UserID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 执行宣告
structDict['CThostFtdcExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 执行宣告引用
  ExecOrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 数量
  Volume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 执行类型
  ActionType: 'char',
  // 保留头寸申请的持仓方向
  PosiDirection: 'char',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'char',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'char',
  // 本地执行宣告编号
  ExecOrderLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 执行宣告提交状态
  OrderSubmitStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 执行宣告编号
  ExecOrderSysID: 'string',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 执行结果
  ExecResult: 'char',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 操作用户代码
  ActiveUserID: 'string',
  // 经纪公司报单编号
  BrokerExecOrderSeq: 'int',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 执行宣告操作
structDict['CThostFtdcExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 执行宣告操作引用
  ExecOrderActionRef: 'int',
  // 执行宣告引用
  ExecOrderRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 执行宣告操作编号
  ExecOrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地执行宣告编号
  ExecOrderLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 执行类型
  ActionType: 'char',
  // 状态信息
  StatusMsg: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 执行宣告查询
structDict['CThostFtdcQryExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 执行宣告编号
  ExecOrderSysID: 'string',
  // 开始时间
  InsertTimeStart: 'string',
  // 结束时间
  InsertTimeEnd: 'string'
}

// 交易所执行宣告信息
structDict['CThostFtdcExchangeExecOrderField'] = {
  // 数量
  Volume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 执行类型
  ActionType: 'char',
  // 保留头寸申请的持仓方向
  PosiDirection: 'char',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'char',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'char',
  // 本地执行宣告编号
  ExecOrderLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 执行宣告提交状态
  OrderSubmitStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 执行宣告编号
  ExecOrderSysID: 'string',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 执行结果
  ExecResult: 'char',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 营业部编号
  BranchID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所执行宣告查询
structDict['CThostFtdcQryExchangeExecOrderField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 执行宣告操作查询
structDict['CThostFtdcQryExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 交易所执行宣告操作
structDict['CThostFtdcExchangeExecOrderActionField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 执行宣告操作编号
  ExecOrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地执行宣告编号
  ExecOrderLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 执行类型
  ActionType: 'char',
  // 营业部编号
  BranchID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所执行宣告操作查询
structDict['CThostFtdcQryExchangeExecOrderActionField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 错误执行宣告
structDict['CThostFtdcErrExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 执行宣告引用
  ExecOrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 数量
  Volume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 执行类型
  ActionType: 'char',
  // 保留头寸申请的持仓方向
  PosiDirection: 'char',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'char',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'char',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 交易编码
  ClientID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 查询错误执行宣告
structDict['CThostFtdcQryErrExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

// 错误执行宣告操作
structDict['CThostFtdcErrExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 执行宣告操作引用
  ExecOrderActionRef: 'int',
  // 执行宣告引用
  ExecOrderRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 执行宣告操作编号
  ExecOrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 用户代码
  UserID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 查询错误执行宣告操作
structDict['CThostFtdcQryErrExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

// 投资者期权合约交易权限
structDict['CThostFtdcOptionInstrTradingRightField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 买卖方向
  Direction: 'char',
  // 交易权限
  TradingRight: 'char'
}

// 查询期权合约交易权限
structDict['CThostFtdcQryOptionInstrTradingRightField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 买卖方向
  Direction: 'char'
}

// 输入的询价
structDict['CThostFtdcInputForQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 询价引用
  ForQuoteRef: 'string',
  // 用户代码
  UserID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 询价
structDict['CThostFtdcForQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 询价引用
  ForQuoteRef: 'string',
  // 用户代码
  UserID: 'string',
  // 本地询价编号
  ForQuoteLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 询价状态
  ForQuoteStatus: 'char',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 状态信息
  StatusMsg: 'string',
  // 操作用户代码
  ActiveUserID: 'string',
  // 经纪公司询价编号
  BrokerForQutoSeq: 'int',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 询价查询
structDict['CThostFtdcQryForQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 开始时间
  InsertTimeStart: 'string',
  // 结束时间
  InsertTimeEnd: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 交易所询价信息
structDict['CThostFtdcExchangeForQuoteField'] = {
  // 本地询价编号
  ForQuoteLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 询价状态
  ForQuoteStatus: 'char',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所询价查询
structDict['CThostFtdcQryExchangeForQuoteField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 输入的报价
structDict['CThostFtdcInputQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报价引用
  QuoteRef: 'string',
  // 用户代码
  UserID: 'string',
  // 卖价格
  AskPrice: 'float',
  // 买价格
  BidPrice: 'float',
  // 卖数量
  AskVolume: 'int',
  // 买数量
  BidVolume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 卖开平标志
  AskOffsetFlag: 'char',
  // 买开平标志
  BidOffsetFlag: 'char',
  // 卖投机套保标志
  AskHedgeFlag: 'char',
  // 买投机套保标志
  BidHedgeFlag: 'char',
  // 衍生卖报单引用
  AskOrderRef: 'string',
  // 衍生买报单引用
  BidOrderRef: 'string',
  // 应价编号
  ForQuoteSysID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 交易编码
  ClientID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 输入报价操作
structDict['CThostFtdcInputQuoteActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报价操作引用
  QuoteActionRef: 'int',
  // 报价引用
  QuoteRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 报价操作编号
  QuoteSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 用户代码
  UserID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 交易编码
  ClientID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 报价
structDict['CThostFtdcQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报价引用
  QuoteRef: 'string',
  // 用户代码
  UserID: 'string',
  // 卖价格
  AskPrice: 'float',
  // 买价格
  BidPrice: 'float',
  // 卖数量
  AskVolume: 'int',
  // 买数量
  BidVolume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 卖开平标志
  AskOffsetFlag: 'char',
  // 买开平标志
  BidOffsetFlag: 'char',
  // 卖投机套保标志
  AskHedgeFlag: 'char',
  // 买投机套保标志
  BidHedgeFlag: 'char',
  // 本地报价编号
  QuoteLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 报价提示序号
  NotifySequence: 'int',
  // 报价提交状态
  OrderSubmitStatus: 'char',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 报价编号
  QuoteSysID: 'string',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 报价状态
  QuoteStatus: 'char',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 卖方报单编号
  AskOrderSysID: 'string',
  // 买方报单编号
  BidOrderSysID: 'string',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 操作用户代码
  ActiveUserID: 'string',
  // 经纪公司报价编号
  BrokerQuoteSeq: 'int',
  // 衍生卖报单引用
  AskOrderRef: 'string',
  // 衍生买报单引用
  BidOrderRef: 'string',
  // 应价编号
  ForQuoteSysID: 'string',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 报价操作
structDict['CThostFtdcQuoteActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报价操作引用
  QuoteActionRef: 'int',
  // 报价引用
  QuoteRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 报价操作编号
  QuoteSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报价编号
  QuoteLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 报价查询
structDict['CThostFtdcQryQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 报价编号
  QuoteSysID: 'string',
  // 开始时间
  InsertTimeStart: 'string',
  // 结束时间
  InsertTimeEnd: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 交易所报价信息
structDict['CThostFtdcExchangeQuoteField'] = {
  // 卖价格
  AskPrice: 'float',
  // 买价格
  BidPrice: 'float',
  // 卖数量
  AskVolume: 'int',
  // 买数量
  BidVolume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 卖开平标志
  AskOffsetFlag: 'char',
  // 买开平标志
  BidOffsetFlag: 'char',
  // 卖投机套保标志
  AskHedgeFlag: 'char',
  // 买投机套保标志
  BidHedgeFlag: 'char',
  // 本地报价编号
  QuoteLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 报价提示序号
  NotifySequence: 'int',
  // 报价提交状态
  OrderSubmitStatus: 'char',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 报价编号
  QuoteSysID: 'string',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 报价状态
  QuoteStatus: 'char',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 卖方报单编号
  AskOrderSysID: 'string',
  // 买方报单编号
  BidOrderSysID: 'string',
  // 应价编号
  ForQuoteSysID: 'string',
  // 营业部编号
  BranchID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所报价查询
structDict['CThostFtdcQryExchangeQuoteField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 报价操作查询
structDict['CThostFtdcQryQuoteActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 交易所报价操作
structDict['CThostFtdcExchangeQuoteActionField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 报价操作编号
  QuoteSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报价编号
  QuoteLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所报价操作查询
structDict['CThostFtdcQryExchangeQuoteActionField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 期权合约delta值
structDict['CThostFtdcOptionInstrDeltaField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // Delta值
  Delta: 'float'
}

// 发给做市商的询价请求
structDict['CThostFtdcForQuoteRspField'] = {
  // 交易日
  TradingDay: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 询价编号
  ForQuoteSysID: 'string',
  // 询价时间
  ForQuoteTime: 'string',
  // 业务日期
  ActionDay: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 当前期权合约执行偏移值的详细内容
structDict['CThostFtdcStrikeOffsetField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 执行偏移值
  Offset: 'float',
  // 执行偏移类型
  OffsetType: 'undefined'
}

// 期权执行偏移值查询
structDict['CThostFtdcQryStrikeOffsetField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string'
}

// 输入批量报单操作
structDict['CThostFtdcInputBatchOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报单操作引用
  OrderActionRef: 'int',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 用户代码
  UserID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 批量报单操作
structDict['CThostFtdcBatchOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报单操作引用
  OrderActionRef: 'int',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 交易所批量报单操作
structDict['CThostFtdcExchangeBatchOrderActionField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 查询批量报单操作
structDict['CThostFtdcQryBatchOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 组合合约安全系数
structDict['CThostFtdcCombInstrumentGuardField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // No Description
  GuarantRatio: 'float',
  // 交易所代码
  ExchangeID: 'string'
}

// 组合合约安全系数查询
structDict['CThostFtdcQryCombInstrumentGuardField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 输入的申请组合
structDict['CThostFtdcInputCombActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 组合引用
  CombActionRef: 'string',
  // 用户代码
  UserID: 'string',
  // 买卖方向
  Direction: 'char',
  // 数量
  Volume: 'int',
  // 组合指令方向
  CombDirection: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 交易所代码
  ExchangeID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 申请组合
structDict['CThostFtdcCombActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 组合引用
  CombActionRef: 'string',
  // 用户代码
  UserID: 'string',
  // 买卖方向
  Direction: 'char',
  // 数量
  Volume: 'int',
  // 组合指令方向
  CombDirection: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 本地申请组合编号
  ActionLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 组合状态
  ActionStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 序号
  SequenceNo: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 状态信息
  StatusMsg: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string',
  // 组合编号
  ComTradeID: 'string',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 申请组合查询
structDict['CThostFtdcQryCombActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 交易所申请组合信息
structDict['CThostFtdcExchangeCombActionField'] = {
  // 买卖方向
  Direction: 'char',
  // 数量
  Volume: 'int',
  // 组合指令方向
  CombDirection: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 本地申请组合编号
  ActionLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 组合状态
  ActionStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 序号
  SequenceNo: 'int',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string',
  // 组合编号
  ComTradeID: 'string',
  // 营业部编号
  BranchID: 'string'
}

// 交易所申请组合查询
structDict['CThostFtdcQryExchangeCombActionField'] = {
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 产品报价汇率
structDict['CThostFtdcProductExchRateField'] = {
  // 产品代码
  ProductID: 'string',
  // 报价币种类型
  QuoteCurrencyID: 'string',
  // 汇率
  ExchangeRate: 'float',
  // 交易所代码
  ExchangeID: 'string'
}

// 产品报价汇率查询
structDict['CThostFtdcQryProductExchRateField'] = {
  // 产品代码
  ProductID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 查询询价价差参数
structDict['CThostFtdcQryForQuoteParamField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 询价价差参数
structDict['CThostFtdcForQuoteParamField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 最新价
  LastPrice: 'float',
  // 价差
  PriceInterval: 'float'
}

// 当前做市商期权合约手续费的详细内容
structDict['CThostFtdcMMOptionInstrCommRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 开仓手续费率
  OpenRatioByMoney: 'float',
  // 开仓手续费
  OpenRatioByVolume: 'float',
  // 平仓手续费率
  CloseRatioByMoney: 'float',
  // 平仓手续费
  CloseRatioByVolume: 'float',
  // 平今手续费率
  CloseTodayRatioByMoney: 'float',
  // 平今手续费
  CloseTodayRatioByVolume: 'float',
  // 执行手续费率
  StrikeRatioByMoney: 'float',
  // 执行手续费
  StrikeRatioByVolume: 'float'
}

// 做市商期权手续费率查询
structDict['CThostFtdcQryMMOptionInstrCommRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string'
}

// 做市商合约手续费率
structDict['CThostFtdcMMInstrumentCommissionRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 开仓手续费率
  OpenRatioByMoney: 'float',
  // 开仓手续费
  OpenRatioByVolume: 'float',
  // 平仓手续费率
  CloseRatioByMoney: 'float',
  // 平仓手续费
  CloseRatioByVolume: 'float',
  // 平今手续费率
  CloseTodayRatioByMoney: 'float',
  // 平今手续费
  CloseTodayRatioByVolume: 'float'
}

// 查询做市商合约手续费率
structDict['CThostFtdcQryMMInstrumentCommissionRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string'
}

// 当前报单手续费的详细内容
structDict['CThostFtdcInstrumentOrderCommRateField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 报单手续费
  OrderCommByVolume: 'float',
  // 撤单手续费
  OrderActionCommByVolume: 'float',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 报单手续费率查询
structDict['CThostFtdcQryInstrumentOrderCommRateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string'
}

// 交易参数
structDict['CThostFtdcTradeParamField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 参数代码
  TradeParamID: 'char',
  // 参数代码值
  TradeParamValue: 'string',
  // 备注
  Memo: 'string'
}

// 合约保证金率调整
structDict['CThostFtdcInstrumentMarginRateULField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 多头保证金率
  LongMarginRatioByMoney: 'float',
  // 多头保证金费
  LongMarginRatioByVolume: 'float',
  // 空头保证金率
  ShortMarginRatioByMoney: 'float',
  // 空头保证金费
  ShortMarginRatioByVolume: 'float'
}

// 期货持仓限制参数
structDict['CThostFtdcFutureLimitPosiParamField'] = {
  // 投资者范围
  InvestorRange: 'char',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 产品代码
  ProductID: 'string',
  // 当日投机开仓数量限制
  SpecOpenVolume: 'int',
  // 当日套利开仓数量限制
  ArbiOpenVolume: 'int',
  // 当日投机+套利开仓数量限制
  OpenVolume: 'int'
}

// 禁止登录IP
structDict['CThostFtdcLoginForbiddenIPField'] = {
  // IP地址
  IPAddress: 'string'
}

// IP列表
structDict['CThostFtdcIPListField'] = {
  // IP地址
  IPAddress: 'string',
  // 是否白名单
  IsWhite: 'int'
}

// 输入的期权自对冲
structDict['CThostFtdcInputOptionSelfCloseField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 期权自对冲引用
  OptionSelfCloseRef: 'string',
  // 用户代码
  UserID: 'string',
  // 数量
  Volume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 期权行权的头寸是否自对冲
  OptSelfCloseFlag: 'undefined',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 交易编码
  ClientID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 输入期权自对冲操作
structDict['CThostFtdcInputOptionSelfCloseActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 期权自对冲操作引用
  OptionSelfCloseActionRef: 'int',
  // 期权自对冲引用
  OptionSelfCloseRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 期权自对冲操作编号
  OptionSelfCloseSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 用户代码
  UserID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 期权自对冲
structDict['CThostFtdcOptionSelfCloseField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 期权自对冲引用
  OptionSelfCloseRef: 'string',
  // 用户代码
  UserID: 'string',
  // 数量
  Volume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 期权行权的头寸是否自对冲
  OptSelfCloseFlag: 'undefined',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 期权自对冲提交状态
  OrderSubmitStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 期权自对冲编号
  OptionSelfCloseSysID: 'string',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 自对冲结果
  ExecResult: 'char',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 操作用户代码
  ActiveUserID: 'string',
  // 经纪公司报单编号
  BrokerOptionSelfCloseSeq: 'int',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 期权自对冲操作
structDict['CThostFtdcOptionSelfCloseActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 期权自对冲操作引用
  OptionSelfCloseActionRef: 'int',
  // 期权自对冲引用
  OptionSelfCloseRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 期权自对冲操作编号
  OptionSelfCloseSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 期权自对冲查询
structDict['CThostFtdcQryOptionSelfCloseField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 期权自对冲编号
  OptionSelfCloseSysID: 'string',
  // 开始时间
  InsertTimeStart: 'string',
  // 结束时间
  InsertTimeEnd: 'string'
}

// 交易所期权自对冲信息
structDict['CThostFtdcExchangeOptionSelfCloseField'] = {
  // 数量
  Volume: 'int',
  // 请求编号
  RequestID: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 期权行权的头寸是否自对冲
  OptSelfCloseFlag: 'undefined',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 期权自对冲提交状态
  OrderSubmitStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 期权自对冲编号
  OptionSelfCloseSysID: 'string',
  // 报单日期
  InsertDate: 'string',
  // 插入时间
  InsertTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 自对冲结果
  ExecResult: 'char',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 营业部编号
  BranchID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 期权自对冲操作查询
structDict['CThostFtdcQryOptionSelfCloseActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 交易所期权自对冲操作
structDict['CThostFtdcExchangeOptionSelfCloseActionField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 期权自对冲操作编号
  OptionSelfCloseSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 营业部编号
  BranchID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 延时换汇同步
structDict['CThostFtdcSyncDelaySwapField'] = {
  // 换汇流水号
  DelaySwapSeqNo: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 源币种
  FromCurrencyID: 'string',
  // 源金额
  FromAmount: 'float',
  // 源换汇冻结金额(可用冻结)
  FromFrozenSwap: 'float',
  // 源剩余换汇额度(可提冻结)
  FromRemainSwap: 'float',
  // 目标币种
  ToCurrencyID: 'string',
  // 目标金额
  ToAmount: 'float'
}

// 查询延时换汇同步
structDict['CThostFtdcQrySyncDelaySwapField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 延时换汇流水号
  DelaySwapSeqNo: 'string'
}

// 投资单元
structDict['CThostFtdcInvestUnitField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 投资者单元名称
  InvestorUnitName: 'string',
  // 投资者分组代码
  InvestorGroupID: 'string',
  // 手续费率模板代码
  CommModelID: 'string',
  // 保证金率模板代码
  MarginModelID: 'string',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 查询投资单元
structDict['CThostFtdcQryInvestUnitField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 二级代理商资金校验模式
structDict['CThostFtdcSecAgentCheckModeField'] = {
  // 投资者代码
  InvestorID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 币种
  CurrencyID: 'string',
  // 境外中介机构资金帐号
  BrokerSecAgentID: 'string',
  // 是否需要校验自己的资金账户
  CheckSelfAccount: 'int'
}

// 市场行情
structDict['CThostFtdcMarketDataField'] = {
  // 交易日
  TradingDay: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 最新价
  LastPrice: 'float',
  // 上次结算价
  PreSettlementPrice: 'float',
  // 昨收盘
  PreClosePrice: 'float',
  // 昨持仓量
  PreOpenInterest: 'float',
  // 今开盘
  OpenPrice: 'float',
  // 最高价
  HighestPrice: 'float',
  // 最低价
  LowestPrice: 'float',
  // 数量
  Volume: 'int',
  // 成交金额
  Turnover: 'float',
  // 持仓量
  OpenInterest: 'float',
  // 今收盘
  ClosePrice: 'float',
  // 本次结算价
  SettlementPrice: 'float',
  // 涨停板价
  UpperLimitPrice: 'float',
  // 跌停板价
  LowerLimitPrice: 'float',
  // 昨虚实度
  PreDelta: 'float',
  // 今虚实度
  CurrDelta: 'float',
  // 最后修改时间
  UpdateTime: 'string',
  // 最后修改毫秒
  UpdateMillisec: 'int',
  // 业务日期
  ActionDay: 'string'
}

// 行情基础属性
structDict['CThostFtdcMarketDataBaseField'] = {
  // 交易日
  TradingDay: 'string',
  // 上次结算价
  PreSettlementPrice: 'float',
  // 昨收盘
  PreClosePrice: 'float',
  // 昨持仓量
  PreOpenInterest: 'float',
  // 昨虚实度
  PreDelta: 'float'
}

// 行情静态属性
structDict['CThostFtdcMarketDataStaticField'] = {
  // 今开盘
  OpenPrice: 'float',
  // 最高价
  HighestPrice: 'float',
  // 最低价
  LowestPrice: 'float',
  // 今收盘
  ClosePrice: 'float',
  // 涨停板价
  UpperLimitPrice: 'float',
  // 跌停板价
  LowerLimitPrice: 'float',
  // 本次结算价
  SettlementPrice: 'float',
  // 今虚实度
  CurrDelta: 'float'
}

// 行情最新成交属性
structDict['CThostFtdcMarketDataLastMatchField'] = {
  // 最新价
  LastPrice: 'float',
  // 数量
  Volume: 'int',
  // 成交金额
  Turnover: 'float',
  // 持仓量
  OpenInterest: 'float'
}

// 行情最优价属性
structDict['CThostFtdcMarketDataBestPriceField'] = {
  // 申买价一
  BidPrice1: 'float',
  // 申买量一
  BidVolume1: 'int',
  // 申卖价一
  AskPrice1: 'float',
  // 申卖量一
  AskVolume1: 'int'
}

// 行情申买二、三属性
structDict['CThostFtdcMarketDataBid23Field'] = {
  // 申买价二
  BidPrice2: 'float',
  // 申买量二
  BidVolume2: 'int',
  // 申买价三
  BidPrice3: 'float',
  // 申买量三
  BidVolume3: 'int'
}

// 行情申卖二、三属性
structDict['CThostFtdcMarketDataAsk23Field'] = {
  // 申卖价二
  AskPrice2: 'float',
  // 申卖量二
  AskVolume2: 'int',
  // 申卖价三
  AskPrice3: 'float',
  // 申卖量三
  AskVolume3: 'int'
}

// 行情申买四、五属性
structDict['CThostFtdcMarketDataBid45Field'] = {
  // 申买价四
  BidPrice4: 'float',
  // 申买量四
  BidVolume4: 'int',
  // 申买价五
  BidPrice5: 'float',
  // 申买量五
  BidVolume5: 'int'
}

// 行情申卖四、五属性
structDict['CThostFtdcMarketDataAsk45Field'] = {
  // 申卖价四
  AskPrice4: 'float',
  // 申卖量四
  AskVolume4: 'int',
  // 申卖价五
  AskPrice5: 'float',
  // 申卖量五
  AskVolume5: 'int'
}

// 行情更新时间属性
structDict['CThostFtdcMarketDataUpdateTimeField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 最后修改时间
  UpdateTime: 'string',
  // 最后修改毫秒
  UpdateMillisec: 'int',
  // 业务日期
  ActionDay: 'string'
}

// 行情交易所代码属性
structDict['CThostFtdcMarketDataExchangeField'] = {
  // 交易所代码
  ExchangeID: 'string'
}

// 指定的合约
structDict['CThostFtdcSpecificInstrumentField'] = {
  // 合约代码
  InstrumentID: 'string'
}

// 合约状态
structDict['CThostFtdcInstrumentStatusField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 结算组代码
  SettlementGroupID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 合约交易状态
  InstrumentStatus: 'char',
  // 交易阶段编号
  TradingSegmentSN: 'int',
  // 进入本状态时间
  EnterTime: 'string',
  // 进入本状态原因
  EnterReason: 'char'
}

// 查询合约状态
structDict['CThostFtdcQryInstrumentStatusField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string'
}

// 投资者账户
structDict['CThostFtdcInvestorAccountField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 浮动盈亏算法
structDict['CThostFtdcPositionProfitAlgorithmField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 盈亏算法
  Algorithm: 'char',
  // 备注
  Memo: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 会员资金折扣
structDict['CThostFtdcDiscountField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 投资者代码
  InvestorID: 'string',
  // 资金折扣比例
  Discount: 'float'
}

// 查询转帐银行
structDict['CThostFtdcQryTransferBankField'] = {
  // 银行代码
  BankID: 'string',
  // 银行分中心代码
  BankBrchID: 'string'
}

// 转帐银行
structDict['CThostFtdcTransferBankField'] = {
  // 银行代码
  BankID: 'string',
  // 银行分中心代码
  BankBrchID: 'string',
  // 银行名称
  BankName: 'string',
  // 是否活跃
  IsActive: 'int'
}

// 查询投资者持仓明细
structDict['CThostFtdcQryInvestorPositionDetailField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 投资者持仓明细
structDict['CThostFtdcInvestorPositionDetailField'] = {
  // 合约代码
  InstrumentID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 买卖
  Direction: 'char',
  // 开仓日期
  OpenDate: 'string',
  // 成交编号
  TradeID: 'string',
  // 数量
  Volume: 'int',
  // 开仓价
  OpenPrice: 'float',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 成交类型
  TradeType: 'char',
  // 组合合约代码
  CombInstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 逐日盯市平仓盈亏
  CloseProfitByDate: 'float',
  // 逐笔对冲平仓盈亏
  CloseProfitByTrade: 'float',
  // 逐日盯市持仓盈亏
  PositionProfitByDate: 'float',
  // 逐笔对冲持仓盈亏
  PositionProfitByTrade: 'float',
  // 投资者保证金
  Margin: 'float',
  // 交易所保证金
  ExchMargin: 'float',
  // 保证金率
  MarginRateByMoney: 'float',
  // 保证金率(按手数)
  MarginRateByVolume: 'float',
  // 昨结算价
  LastSettlementPrice: 'float',
  // 结算价
  SettlementPrice: 'float',
  // 平仓量
  CloseVolume: 'int',
  // 平仓金额
  CloseAmount: 'float',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 资金账户口令域
structDict['CThostFtdcTradingAccountPasswordField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 密码
  Password: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 交易所行情报盘机
structDict['CThostFtdcMDTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 交易所交易员连接状态
  TraderConnectStatus: 'char',
  // 发出连接请求的日期
  ConnectRequestDate: 'string',
  // 发出连接请求的时间
  ConnectRequestTime: 'string',
  // 上次报告日期
  LastReportDate: 'string',
  // 上次报告时间
  LastReportTime: 'string',
  // 完成连接日期
  ConnectDate: 'string',
  // 完成连接时间
  ConnectTime: 'string',
  // 启动日期
  StartDate: 'string',
  // 启动时间
  StartTime: 'string',
  // 交易日
  TradingDay: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 本席位最大成交编号
  MaxTradeID: 'string',
  // 本席位最大报单备拷
  MaxOrderMessageReference: 'string'
}

// 查询行情报盘机
structDict['CThostFtdcQryMDTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 交易所交易员代码
  TraderID: 'string'
}

// 查询客户通知
structDict['CThostFtdcQryNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'string'
}

// 客户通知
structDict['CThostFtdcNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 消息正文
  Content: 'string',
  // 经纪公司通知内容序列号
  SequenceLabel: 'string'
}

// 用户权限
structDict['CThostFtdcUserRightField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 客户权限类型
  UserRightType: 'char',
  // 是否禁止
  IsForbidden: 'int'
}

// 查询结算信息确认域
structDict['CThostFtdcQrySettlementInfoConfirmField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 装载结算信息
structDict['CThostFtdcLoadSettlementInfoField'] = {
  // 经纪公司代码
  BrokerID: 'string'
}

// 经纪公司可提资金算法表
structDict['CThostFtdcBrokerWithdrawAlgorithmField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 可提资金算法
  WithdrawAlgorithm: 'char',
  // 资金使用率
  UsingRatio: 'float',
  // 可提是否包含平仓盈利
  IncludeCloseProfit: 'char',
  // 本日无仓且无成交客户是否受可提比例限制
  AllWithoutTrade: 'char',
  // 可用是否包含平仓盈利
  AvailIncludeCloseProfit: 'char',
  // 是否启用用户事件
  IsBrokerUserEvent: 'int',
  // 币种代码
  CurrencyID: 'string',
  // 货币质押比率
  FundMortgageRatio: 'float',
  // 权益算法
  BalanceAlgorithm: 'char'
}

// 资金账户口令变更域
structDict['CThostFtdcTradingAccountPasswordUpdateV1Field'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 原来的口令
  OldPassword: 'string',
  // 新的口令
  NewPassword: 'string'
}

// 资金账户口令变更域
structDict['CThostFtdcTradingAccountPasswordUpdateField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 原来的口令
  OldPassword: 'string',
  // 新的口令
  NewPassword: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 查询组合合约分腿
structDict['CThostFtdcQryCombinationLegField'] = {
  // 组合合约代码
  CombInstrumentID: 'string',
  // 单腿编号
  LegID: 'int',
  // 单腿合约代码
  LegInstrumentID: 'string'
}

// 查询组合合约分腿
structDict['CThostFtdcQrySyncStatusField'] = {
  // 交易日
  TradingDay: 'string'
}

// 组合交易合约的单腿
structDict['CThostFtdcCombinationLegField'] = {
  // 组合合约代码
  CombInstrumentID: 'string',
  // 单腿编号
  LegID: 'int',
  // 单腿合约代码
  LegInstrumentID: 'string',
  // 买卖方向
  Direction: 'char',
  // 单腿乘数
  LegMultiple: 'int',
  // 派生层数
  ImplyLevel: 'int'
}

// 数据同步状态
structDict['CThostFtdcSyncStatusField'] = {
  // 交易日
  TradingDay: 'string',
  // 数据同步状态
  DataSyncStatus: 'char'
}

// 查询联系人
structDict['CThostFtdcQryLinkManField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

// 联系人
structDict['CThostFtdcLinkManField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 联系人类型
  PersonType: 'char',
  // 证件类型
  IdentifiedCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 名称
  PersonName: 'string',
  // 联系电话
  Telephone: 'string',
  // 通讯地址
  Address: 'string',
  // 邮政编码
  ZipCode: 'string',
  // 优先级
  Priority: 'int',
  // 开户邮政编码
  UOAZipCode: 'string',
  // 全称
  PersonFullName: 'string'
}

// 查询经纪公司用户事件
structDict['CThostFtdcQryBrokerUserEventField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 用户事件类型
  UserEventType: 'char'
}

// 查询经纪公司用户事件
structDict['CThostFtdcBrokerUserEventField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 用户事件类型
  UserEventType: 'char',
  // 用户事件序号
  EventSequenceNo: 'int',
  // 事件发生日期
  EventDate: 'string',
  // 事件发生时间
  EventTime: 'string',
  // 用户事件信息
  UserEventInfo: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string'
}

// 查询签约银行请求
structDict['CThostFtdcQryContractBankField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分中心代码
  BankBrchID: 'string'
}

// 查询签约银行响应
structDict['CThostFtdcContractBankField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分中心代码
  BankBrchID: 'string',
  // 银行名称
  BankName: 'string'
}

// 投资者组合持仓明细
structDict['CThostFtdcInvestorPositionCombineDetailField'] = {
  // 交易日
  TradingDay: 'string',
  // 开仓日期
  OpenDate: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 结算编号
  SettlementID: 'int',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 组合编号
  ComTradeID: 'string',
  // 撮合编号
  TradeID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 买卖
  Direction: 'char',
  // 持仓量
  TotalAmt: 'int',
  // 投资者保证金
  Margin: 'float',
  // 交易所保证金
  ExchMargin: 'float',
  // 保证金率
  MarginRateByMoney: 'float',
  // 保证金率(按手数)
  MarginRateByVolume: 'float',
  // 单腿编号
  LegID: 'int',
  // 单腿乘数
  LegMultiple: 'int',
  // 组合持仓合约编码
  CombInstrumentID: 'string',
  // 成交组号
  TradeGroupID: 'int',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 预埋单
structDict['CThostFtdcParkedOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报单引用
  OrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 报单价格条件
  OrderPriceType: 'char',
  // 买卖方向
  Direction: 'char',
  // 组合开平标志
  CombOffsetFlag: 'string',
  // 组合投机套保标志
  CombHedgeFlag: 'string',
  // 价格
  LimitPrice: 'float',
  // 数量
  VolumeTotalOriginal: 'int',
  // 有效期类型
  TimeCondition: 'char',
  // GTD日期
  GTDDate: 'string',
  // 成交量类型
  VolumeCondition: 'char',
  // 最小成交量
  MinVolume: 'int',
  // 触发条件
  ContingentCondition: 'char',
  // 止损价
  StopPrice: 'float',
  // 强平原因
  ForceCloseReason: 'char',
  // 自动挂起标志
  IsAutoSuspend: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 请求编号
  RequestID: 'int',
  // 用户强评标志
  UserForceClose: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 预埋报单编号
  ParkedOrderID: 'string',
  // 用户类型
  UserType: 'char',
  // 预埋单状态
  Status: 'char',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 互换单标志
  IsSwapOrder: 'int',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 交易编码
  ClientID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 输入预埋单操作
structDict['CThostFtdcParkedOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报单操作引用
  OrderActionRef: 'int',
  // 报单引用
  OrderRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 价格
  LimitPrice: 'float',
  // 数量变化
  VolumeChange: 'int',
  // 用户代码
  UserID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 预埋撤单单编号
  ParkedOrderActionID: 'string',
  // 用户类型
  UserType: 'char',
  // 预埋撤单状态
  Status: 'char',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 查询预埋单
structDict['CThostFtdcQryParkedOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询预埋撤单
structDict['CThostFtdcQryParkedOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 删除预埋单
structDict['CThostFtdcRemoveParkedOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 预埋报单编号
  ParkedOrderID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 删除预埋撤单
structDict['CThostFtdcRemoveParkedOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 预埋撤单编号
  ParkedOrderActionID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 经纪公司可提资金算法表
structDict['CThostFtdcInvestorWithdrawAlgorithmField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 投资者代码
  InvestorID: 'string',
  // 可提资金比例
  UsingRatio: 'float',
  // 币种代码
  CurrencyID: 'string',
  // 货币质押比率
  FundMortgageRatio: 'float'
}

// 查询组合持仓明细
structDict['CThostFtdcQryInvestorPositionCombineDetailField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 组合持仓合约编码
  CombInstrumentID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 成交均价
structDict['CThostFtdcMarketDataAveragePriceField'] = {
  // 当日均价
  AveragePrice: 'float'
}

// 校验投资者密码
structDict['CThostFtdcVerifyInvestorPasswordField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 密码
  Password: 'string'
}

// 用户IP
structDict['CThostFtdcUserIPField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // IP地址
  IPAddress: 'string',
  // IP地址掩码
  IPMask: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 用户事件通知信息
structDict['CThostFtdcTradingNoticeInfoField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 发送时间
  SendTime: 'string',
  // 消息正文
  FieldContent: 'string',
  // 序列系列号
  SequenceSeries: 'int',
  // 序列号
  SequenceNo: 'int',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 用户事件通知
structDict['CThostFtdcTradingNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者范围
  InvestorRange: 'char',
  // 投资者代码
  InvestorID: 'string',
  // 序列系列号
  SequenceSeries: 'int',
  // 用户代码
  UserID: 'string',
  // 发送时间
  SendTime: 'string',
  // 序列号
  SequenceNo: 'int',
  // 消息正文
  FieldContent: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询交易事件通知
structDict['CThostFtdcQryTradingNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询错误报单
structDict['CThostFtdcQryErrOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

// 错误报单
structDict['CThostFtdcErrOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报单引用
  OrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 报单价格条件
  OrderPriceType: 'char',
  // 买卖方向
  Direction: 'char',
  // 组合开平标志
  CombOffsetFlag: 'string',
  // 组合投机套保标志
  CombHedgeFlag: 'string',
  // 价格
  LimitPrice: 'float',
  // 数量
  VolumeTotalOriginal: 'int',
  // 有效期类型
  TimeCondition: 'char',
  // GTD日期
  GTDDate: 'string',
  // 成交量类型
  VolumeCondition: 'char',
  // 最小成交量
  MinVolume: 'int',
  // 触发条件
  ContingentCondition: 'char',
  // 止损价
  StopPrice: 'float',
  // 强平原因
  ForceCloseReason: 'char',
  // 自动挂起标志
  IsAutoSuspend: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 请求编号
  RequestID: 'int',
  // 用户强评标志
  UserForceClose: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 互换单标志
  IsSwapOrder: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 交易编码
  ClientID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 查询错误报单操作
structDict['CThostFtdcErrorConditionalOrderField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 报单引用
  OrderRef: 'string',
  // 用户代码
  UserID: 'string',
  // 报单价格条件
  OrderPriceType: 'char',
  // 买卖方向
  Direction: 'char',
  // 组合开平标志
  CombOffsetFlag: 'string',
  // 组合投机套保标志
  CombHedgeFlag: 'string',
  // 价格
  LimitPrice: 'float',
  // 数量
  VolumeTotalOriginal: 'int',
  // 有效期类型
  TimeCondition: 'char',
  // GTD日期
  GTDDate: 'string',
  // 成交量类型
  VolumeCondition: 'char',
  // 最小成交量
  MinVolume: 'int',
  // 触发条件
  ContingentCondition: 'char',
  // 止损价
  StopPrice: 'float',
  // 强平原因
  ForceCloseReason: 'char',
  // 自动挂起标志
  IsAutoSuspend: 'int',
  // 业务单元
  BusinessUnit: 'string',
  // 请求编号
  RequestID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 合约在交易所的代码
  ExchangeInstID: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 报单提交状态
  OrderSubmitStatus: 'char',
  // 报单提示序号
  NotifySequence: 'int',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 报单编号
  OrderSysID: 'string',
  // 报单来源
  OrderSource: 'char',
  // 报单状态
  OrderStatus: 'char',
  // 报单类型
  OrderType: 'char',
  // 今成交数量
  VolumeTraded: 'int',
  // 剩余数量
  VolumeTotal: 'int',
  // 报单日期
  InsertDate: 'string',
  // 委托时间
  InsertTime: 'string',
  // 激活时间
  ActiveTime: 'string',
  // 挂起时间
  SuspendTime: 'string',
  // 最后修改时间
  UpdateTime: 'string',
  // 撤销时间
  CancelTime: 'string',
  // 最后修改交易所交易员代码
  ActiveTraderID: 'string',
  // 结算会员编号
  ClearingPartID: 'string',
  // 序号
  SequenceNo: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 用户端产品信息
  UserProductInfo: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 用户强评标志
  UserForceClose: 'int',
  // 操作用户代码
  ActiveUserID: 'string',
  // 经纪公司报单编号
  BrokerOrderSeq: 'int',
  // 相关报单
  RelativeOrderSysID: 'string',
  // 郑商所成交数量
  ZCETotalTradedVolume: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 互换单标志
  IsSwapOrder: 'int',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // 资金账号
  AccountID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string'
}

// 查询错误报单操作
structDict['CThostFtdcQryErrOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

// 错误报单操作
structDict['CThostFtdcErrOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 报单操作引用
  OrderActionRef: 'int',
  // 报单引用
  OrderRef: 'string',
  // 请求编号
  RequestID: 'int',
  // 前置编号
  FrontID: 'int',
  // 会话编号
  SessionID: 'int',
  // 交易所代码
  ExchangeID: 'string',
  // 报单编号
  OrderSysID: 'string',
  // 操作标志
  ActionFlag: 'char',
  // 价格
  LimitPrice: 'float',
  // 数量变化
  VolumeChange: 'int',
  // 操作日期
  ActionDate: 'string',
  // 操作时间
  ActionTime: 'string',
  // 交易所交易员代码
  TraderID: 'string',
  // 安装编号
  InstallID: 'int',
  // 本地报单编号
  OrderLocalID: 'string',
  // 操作本地编号
  ActionLocalID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 客户代码
  ClientID: 'string',
  // 业务单元
  BusinessUnit: 'string',
  // 报单操作状态
  OrderActionStatus: 'char',
  // 用户代码
  UserID: 'string',
  // 状态信息
  StatusMsg: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 营业部编号
  BranchID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined',
  // IP地址
  IPAddress: 'string',
  // Mac地址
  MacAddress: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 查询交易所状态
structDict['CThostFtdcQryExchangeSequenceField'] = {
  // 交易所代码
  ExchangeID: 'string'
}

// 交易所状态
structDict['CThostFtdcExchangeSequenceField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 序号
  SequenceNo: 'int',
  // 合约交易状态
  MarketStatus: 'char'
}

// 根据价格查询最大报单数量
structDict['CThostFtdcQueryMaxOrderVolumeWithPriceField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 买卖方向
  Direction: 'char',
  // 开平标志
  OffsetFlag: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 最大允许报单数量
  MaxVolume: 'int',
  // 报单价格
  Price: 'float',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询经纪公司交易参数
structDict['CThostFtdcQryBrokerTradingParamsField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 投资者帐号
  AccountID: 'string'
}

// 经纪公司交易参数
structDict['CThostFtdcBrokerTradingParamsField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 保证金价格类型
  MarginPriceType: 'char',
  // 盈亏算法
  Algorithm: 'char',
  // 可用是否包含平仓盈利
  AvailIncludeCloseProfit: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 期权权利金价格类型
  OptionRoyaltyPriceType: 'char',
  // 投资者帐号
  AccountID: 'string'
}

// 查询经纪公司交易算法
structDict['CThostFtdcQryBrokerTradingAlgosField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约代码
  InstrumentID: 'string'
}

// 经纪公司交易算法
structDict['CThostFtdcBrokerTradingAlgosField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 持仓处理算法编号
  HandlePositionAlgoID: 'char',
  // 寻找保证金率算法编号
  FindMarginRateAlgoID: 'char',
  // 资金处理算法编号
  HandleTradingAccountAlgoID: 'char'
}

// 查询经纪公司资金
structDict['CThostFtdcQueryBrokerDepositField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 经纪公司资金
structDict['CThostFtdcBrokerDepositField'] = {
  // 交易日期
  TradingDay: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 会员代码
  ParticipantID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 上次结算准备金
  PreBalance: 'float',
  // 当前保证金总额
  CurrMargin: 'float',
  // 平仓盈亏
  CloseProfit: 'float',
  // 期货结算准备金
  Balance: 'float',
  // 入金金额
  Deposit: 'float',
  // 出金金额
  Withdraw: 'float',
  // 可提资金
  Available: 'float',
  // 基本准备金
  Reserve: 'float',
  // 冻结的保证金
  FrozenMargin: 'float'
}

// 查询保证金监管系统经纪公司密钥
structDict['CThostFtdcQryCFMMCBrokerKeyField'] = {
  // 经纪公司代码
  BrokerID: 'string'
}

// 保证金监管系统经纪公司密钥
structDict['CThostFtdcCFMMCBrokerKeyField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 经纪公司统一编码
  ParticipantID: 'string',
  // 密钥生成日期
  CreateDate: 'string',
  // 密钥生成时间
  CreateTime: 'string',
  // 密钥编号
  KeyID: 'int',
  // 动态密钥
  CurrentKey: 'string',
  // 动态密钥类型
  KeyKind: 'char'
}

// 保证金监管系统经纪公司资金账户密钥
structDict['CThostFtdcCFMMCTradingAccountKeyField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 经纪公司统一编码
  ParticipantID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 密钥编号
  KeyID: 'int',
  // 动态密钥
  CurrentKey: 'string'
}

// 请求查询保证金监管系统经纪公司资金账户密钥
structDict['CThostFtdcQryCFMMCTradingAccountKeyField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

// 用户动态令牌参数
structDict['CThostFtdcBrokerUserOTPParamField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 动态令牌提供商
  OTPVendorsID: 'string',
  // 动态令牌序列号
  SerialNumber: 'string',
  // 令牌密钥
  AuthKey: 'string',
  // 漂移值
  LastDrift: 'int',
  // 成功值
  LastSuccess: 'int',
  // 动态令牌类型
  OTPType: 'char'
}

// 手工同步用户动态令牌
structDict['CThostFtdcManualSyncBrokerUserOTPField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 动态令牌类型
  OTPType: 'char',
  // 第一个动态密码
  FirstOTP: 'string',
  // 第二个动态密码
  SecondOTP: 'string'
}

// 投资者手续费率模板
structDict['CThostFtdcCommRateModelField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 手续费率模板代码
  CommModelID: 'string',
  // 模板名称
  CommModelName: 'string'
}

// 请求查询投资者手续费率模板
structDict['CThostFtdcQryCommRateModelField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 手续费率模板代码
  CommModelID: 'string'
}

// 投资者保证金率模板
structDict['CThostFtdcMarginModelField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 保证金率模板代码
  MarginModelID: 'string',
  // 模板名称
  MarginModelName: 'string'
}

// 请求查询投资者保证金率模板
structDict['CThostFtdcQryMarginModelField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 保证金率模板代码
  MarginModelID: 'string'
}

// 仓单折抵信息
structDict['CThostFtdcEWarrantOffsetField'] = {
  // 交易日期
  TradingDay: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 买卖方向
  Direction: 'char',
  // 投机套保标志
  HedgeFlag: 'char',
  // 数量
  Volume: 'int',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询仓单折抵信息
structDict['CThostFtdcQryEWarrantOffsetField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 合约代码
  InstrumentID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询投资者品种/跨品种保证金
structDict['CThostFtdcQryInvestorProductGroupMarginField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 品种/跨品种标示
  ProductGroupID: 'string',
  // 投机套保标志
  HedgeFlag: 'char',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 投资者品种/跨品种保证金
structDict['CThostFtdcInvestorProductGroupMarginField'] = {
  // 品种/跨品种标示
  ProductGroupID: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 交易日
  TradingDay: 'string',
  // 结算编号
  SettlementID: 'int',
  // 冻结的保证金
  FrozenMargin: 'float',
  // 多头冻结的保证金
  LongFrozenMargin: 'float',
  // 空头冻结的保证金
  ShortFrozenMargin: 'float',
  // 占用的保证金
  UseMargin: 'float',
  // 多头保证金
  LongUseMargin: 'float',
  // 空头保证金
  ShortUseMargin: 'float',
  // 交易所保证金
  ExchMargin: 'float',
  // 交易所多头保证金
  LongExchMargin: 'float',
  // 交易所空头保证金
  ShortExchMargin: 'float',
  // 平仓盈亏
  CloseProfit: 'float',
  // 冻结的手续费
  FrozenCommission: 'float',
  // 手续费
  Commission: 'float',
  // 冻结的资金
  FrozenCash: 'float',
  // 资金差额
  CashIn: 'float',
  // 持仓盈亏
  PositionProfit: 'float',
  // 折抵总金额
  OffsetAmount: 'float',
  // 多头折抵总金额
  LongOffsetAmount: 'float',
  // 空头折抵总金额
  ShortOffsetAmount: 'float',
  // 交易所折抵总金额
  ExchOffsetAmount: 'float',
  // 交易所多头折抵总金额
  LongExchOffsetAmount: 'float',
  // 交易所空头折抵总金额
  ShortExchOffsetAmount: 'float',
  // 投机套保标志
  HedgeFlag: 'char',
  // 交易所代码
  ExchangeID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 查询监控中心用户令牌
structDict['CThostFtdcQueryCFMMCTradingAccountTokenField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 投资单元代码
  InvestUnitID: 'undefined'
}

// 监控中心用户令牌
structDict['CThostFtdcCFMMCTradingAccountTokenField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 经纪公司统一编码
  ParticipantID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 密钥编号
  KeyID: 'int',
  // 动态令牌
  Token: 'string'
}

// 查询产品组
structDict['CThostFtdcQryProductGroupField'] = {
  // 产品代码
  ProductID: 'string',
  // 交易所代码
  ExchangeID: 'string'
}

// 投资者品种/跨品种保证金产品组
structDict['CThostFtdcProductGroupField'] = {
  // 产品代码
  ProductID: 'string',
  // 交易所代码
  ExchangeID: 'string',
  // 产品组代码
  ProductGroupID: 'string'
}

// 交易所公告
structDict['CThostFtdcBulletinField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 交易日
  TradingDay: 'string',
  // 公告编号
  BulletinID: 'undefined',
  // 序列号
  SequenceNo: 'int',
  // 公告类型
  NewsType: 'undefined',
  // 紧急程度
  NewsUrgency: 'undefined',
  // 发送时间
  SendTime: 'string',
  // 消息摘要
  Abstract: 'undefined',
  // 消息来源
  ComeFrom: 'undefined',
  // 消息正文
  Content: 'string',
  // WEB地址
  URLLink: 'undefined',
  // 市场代码
  MarketID: 'string'
}

// 查询交易所公告
structDict['CThostFtdcQryBulletinField'] = {
  // 交易所代码
  ExchangeID: 'string',
  // 公告编号
  BulletinID: 'undefined',
  // 序列号
  SequenceNo: 'int',
  // 公告类型
  NewsType: 'undefined',
  // 紧急程度
  NewsUrgency: 'undefined'
}

// 转帐开户请求
structDict['CThostFtdcReqOpenAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 汇钞标志
  CashExchangeCode: 'char',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 交易ID
  TID: 'int',
  // 用户标识
  UserID: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 转帐销户请求
structDict['CThostFtdcReqCancelAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 汇钞标志
  CashExchangeCode: 'char',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 交易ID
  TID: 'int',
  // 用户标识
  UserID: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 变更银行账户请求
structDict['CThostFtdcReqChangeAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 新银行帐号
  NewBankAccount: 'string',
  // 新银行密码
  NewBankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易ID
  TID: 'int',
  // 摘要
  Digest: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 转账请求
structDict['CThostFtdcReqTransferField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 期货公司流水号
  FutureSerial: 'int',
  // 用户标识
  UserID: 'string',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 转帐金额
  TradeAmount: 'float',
  // 期货可取金额
  FutureFetchAmount: 'float',
  // 费用支付标志
  FeePayFlag: 'char',
  // 应收客户费用
  CustFee: 'float',
  // 应收期货公司费用
  BrokerFee: 'float',
  // 发送方给接收方的消息
  Message: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 转账交易状态
  TransferStatus: 'char',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 银行发起银行资金转期货响应
structDict['CThostFtdcRspTransferField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 期货公司流水号
  FutureSerial: 'int',
  // 用户标识
  UserID: 'string',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 转帐金额
  TradeAmount: 'float',
  // 期货可取金额
  FutureFetchAmount: 'float',
  // 费用支付标志
  FeePayFlag: 'char',
  // 应收客户费用
  CustFee: 'float',
  // 应收期货公司费用
  BrokerFee: 'float',
  // 发送方给接收方的消息
  Message: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 转账交易状态
  TransferStatus: 'char',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 冲正请求
structDict['CThostFtdcReqRepealField'] = {
  // 冲正时间间隔
  RepealTimeInterval: 'int',
  // 已经冲正次数
  RepealedTimes: 'int',
  // 银行冲正标志
  BankRepealFlag: 'char',
  // 期商冲正标志
  BrokerRepealFlag: 'char',
  // 被冲正平台流水号
  PlateRepealSerial: 'int',
  // 被冲正银行流水号
  BankRepealSerial: 'string',
  // 被冲正期货流水号
  FutureRepealSerial: 'int',
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 期货公司流水号
  FutureSerial: 'int',
  // 用户标识
  UserID: 'string',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 转帐金额
  TradeAmount: 'float',
  // 期货可取金额
  FutureFetchAmount: 'float',
  // 费用支付标志
  FeePayFlag: 'char',
  // 应收客户费用
  CustFee: 'float',
  // 应收期货公司费用
  BrokerFee: 'float',
  // 发送方给接收方的消息
  Message: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 转账交易状态
  TransferStatus: 'char',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 冲正响应
structDict['CThostFtdcRspRepealField'] = {
  // 冲正时间间隔
  RepealTimeInterval: 'int',
  // 已经冲正次数
  RepealedTimes: 'int',
  // 银行冲正标志
  BankRepealFlag: 'char',
  // 期商冲正标志
  BrokerRepealFlag: 'char',
  // 被冲正平台流水号
  PlateRepealSerial: 'int',
  // 被冲正银行流水号
  BankRepealSerial: 'string',
  // 被冲正期货流水号
  FutureRepealSerial: 'int',
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 期货公司流水号
  FutureSerial: 'int',
  // 用户标识
  UserID: 'string',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 转帐金额
  TradeAmount: 'float',
  // 期货可取金额
  FutureFetchAmount: 'float',
  // 费用支付标志
  FeePayFlag: 'char',
  // 应收客户费用
  CustFee: 'float',
  // 应收期货公司费用
  BrokerFee: 'float',
  // 发送方给接收方的消息
  Message: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 转账交易状态
  TransferStatus: 'char',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 查询账户信息请求
structDict['CThostFtdcReqQueryAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 期货公司流水号
  FutureSerial: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 查询账户信息响应
structDict['CThostFtdcRspQueryAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 期货公司流水号
  FutureSerial: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 银行可用金额
  BankUseAmount: 'float',
  // 银行可取金额
  BankFetchAmount: 'float',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 期商签到签退
structDict['CThostFtdcFutureSignIOField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 摘要
  Digest: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int'
}

// 期商签到响应
structDict['CThostFtdcRspFutureSignInField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 摘要
  Digest: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // PIN密钥
  PinKey: 'string',
  // MAC密钥
  MacKey: 'string'
}

// 期商签退请求
structDict['CThostFtdcReqFutureSignOutField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 摘要
  Digest: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int'
}

// 期商签退响应
structDict['CThostFtdcRspFutureSignOutField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 摘要
  Digest: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 查询指定流水号的交易结果请求
structDict['CThostFtdcReqQueryTradeResultBySerialField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 流水号
  Reference: 'int',
  // 本流水号发布者的机构类型
  RefrenceIssureType: 'char',
  // 本流水号发布者机构编码
  RefrenceIssure: 'string',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 转帐金额
  TradeAmount: 'float',
  // 摘要
  Digest: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 查询指定流水号的交易结果响应
structDict['CThostFtdcRspQueryTradeResultBySerialField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 流水号
  Reference: 'int',
  // 本流水号发布者的机构类型
  RefrenceIssureType: 'char',
  // 本流水号发布者机构编码
  RefrenceIssure: 'string',
  // 原始返回代码
  OriginReturnCode: 'string',
  // 原始返回码描述
  OriginDescrInfoForReturnCode: 'string',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 转帐金额
  TradeAmount: 'float',
  // 摘要
  Digest: 'string'
}

// 日终文件就绪请求
structDict['CThostFtdcReqDayEndFileReadyField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 文件业务功能
  FileBusinessCode: 'char',
  // 摘要
  Digest: 'string'
}

// 返回结果
structDict['CThostFtdcReturnResultField'] = {
  // 返回代码
  ReturnCode: 'string',
  // 返回码描述
  DescrInfoForReturnCode: 'string'
}

// 验证期货资金密码
structDict['CThostFtdcVerifyFuturePasswordField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 安装编号
  InstallID: 'int',
  // 交易ID
  TID: 'int',
  // 币种代码
  CurrencyID: 'string'
}

// 验证客户信息
structDict['CThostFtdcVerifyCustInfoField'] = {
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 验证期货资金密码和客户信息
structDict['CThostFtdcVerifyFuturePasswordAndCustInfoField'] = {
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 验证期货资金密码和客户信息
structDict['CThostFtdcDepositResultInformField'] = {
  // 出入金流水号，该流水号为银期报盘返回的流水号
  DepositSeqNo: 'string',
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 入金金额
  Deposit: 'float',
  // 请求编号
  RequestID: 'int',
  // 返回代码
  ReturnCode: 'string',
  // 返回码描述
  DescrInfoForReturnCode: 'string'
}

// 交易核心向银期报盘发出密钥同步请求
structDict['CThostFtdcReqSyncKeyField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 交易核心给银期报盘的消息
  Message: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int'
}

// 交易核心向银期报盘发出密钥同步响应
structDict['CThostFtdcRspSyncKeyField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 交易核心给银期报盘的消息
  Message: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 查询账户信息通知
structDict['CThostFtdcNotifyQueryAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户类型
  CustType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 期货公司流水号
  FutureSerial: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 银行可用金额
  BankUseAmount: 'float',
  // 银行可取金额
  BankFetchAmount: 'float',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 银期转账交易流水表
structDict['CThostFtdcTransferSerialField'] = {
  // 平台流水号
  PlateSerial: 'int',
  // 交易发起方日期
  TradeDate: 'string',
  // 交易日期
  TradingDay: 'string',
  // 交易时间
  TradeTime: 'string',
  // 交易代码
  TradeCode: 'string',
  // 会话编号
  SessionID: 'int',
  // 银行编码
  BankID: 'string',
  // 银行分支机构编码
  BankBranchID: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 期货公司编码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 期货公司帐号类型
  FutureAccType: 'char',
  // 投资者帐号
  AccountID: 'string',
  // 投资者代码
  InvestorID: 'string',
  // 期货公司流水号
  FutureSerial: 'int',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 交易金额
  TradeAmount: 'float',
  // 应收客户费用
  CustFee: 'float',
  // 应收期货公司费用
  BrokerFee: 'float',
  // 有效标志
  AvailabilityFlag: 'char',
  // 操作员
  OperatorCode: 'string',
  // 新银行帐号
  BankNewAccount: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 请求查询转帐流水
structDict['CThostFtdcQryTransferSerialField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 银行编码
  BankID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 期商签到通知
structDict['CThostFtdcNotifyFutureSignInField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 摘要
  Digest: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // PIN密钥
  PinKey: 'string',
  // MAC密钥
  MacKey: 'string'
}

// 期商签退通知
structDict['CThostFtdcNotifyFutureSignOutField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 摘要
  Digest: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 交易核心向银期报盘发出密钥同步处理结果的通知
structDict['CThostFtdcNotifySyncKeyField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 安装编号
  InstallID: 'int',
  // 用户标识
  UserID: 'string',
  // 交易核心给银期报盘的消息
  Message: 'string',
  // 渠道标志
  DeviceID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易柜员
  OperNo: 'string',
  // 请求编号
  RequestID: 'int',
  // 交易ID
  TID: 'int',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 请求查询银期签约关系
structDict['CThostFtdcQryAccountregisterField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 银行编码
  BankID: 'string',
  // 银行分支机构编码
  BankBranchID: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 客户开销户信息表
structDict['CThostFtdcAccountregisterField'] = {
  // 交易日期
  TradeDay: 'string',
  // 银行编码
  BankID: 'string',
  // 银行分支机构编码
  BankBranchID: 'string',
  // 银行帐号
  BankAccount: 'string',
  // 期货公司编码
  BrokerID: 'string',
  // 期货公司分支机构编码
  BrokerBranchID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 客户姓名
  CustomerName: 'string',
  // 币种代码
  CurrencyID: 'string',
  // 开销户类别
  OpenOrDestroy: 'char',
  // 签约日期
  RegDate: 'string',
  // 解约日期
  OutDate: 'string',
  // 交易ID
  TID: 'int',
  // 客户类型
  CustType: 'char',
  // 银行帐号类型
  BankAccType: 'char',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 银期开户信息
structDict['CThostFtdcOpenAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 汇钞标志
  CashExchangeCode: 'char',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 交易ID
  TID: 'int',
  // 用户标识
  UserID: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 银期销户信息
structDict['CThostFtdcCancelAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 汇钞标志
  CashExchangeCode: 'char',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 渠道标志
  DeviceID: 'string',
  // 期货单位帐号类型
  BankSecuAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 期货单位帐号
  BankSecuAcc: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易柜员
  OperNo: 'string',
  // 交易ID
  TID: 'int',
  // 用户标识
  UserID: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 银期变更银行账号信息
structDict['CThostFtdcChangeAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'string',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 新银行帐号
  NewBankAccount: 'string',
  // 新银行密码
  NewBankPassWord: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 银行密码标志
  BankPwdFlag: 'char',
  // 期货资金密码核对标志
  SecuPwdFlag: 'char',
  // 交易ID
  TID: 'int',
  // 摘要
  Digest: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string',
  // 长客户姓名
  LongCustomerName: 'undefined'
}

// 二级代理操作员银期权限
structDict['CThostFtdcSecAgentACIDMapField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 资金账户
  AccountID: 'string',
  // 币种
  CurrencyID: 'string',
  // 境外中介机构资金帐号
  BrokerSecAgentID: 'string'
}

// 二级代理操作员银期权限查询
structDict['CThostFtdcQrySecAgentACIDMapField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 资金账户
  AccountID: 'string',
  // 币种
  CurrencyID: 'string'
}

// 灾备中心交易权限
structDict['CThostFtdcUserRightsAssignField'] = {
  // 应用单元代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 交易中心代码
  DRIdentityID: 'int'
}

// 经济公司是否有在本标示的交易权限
structDict['CThostFtdcBrokerUserRightAssignField'] = {
  // 应用单元代码
  BrokerID: 'string',
  // 交易中心代码
  DRIdentityID: 'int',
  // 能否交易
  Tradeable: 'int'
}

// 灾备交易转换报文
structDict['CThostFtdcDRTransferField'] = {
  // 原交易中心代码
  OrigDRIdentityID: 'int',
  // 目标交易中心代码
  DestDRIdentityID: 'int',
  // 原应用单元代码
  OrigBrokerID: 'string',
  // 目标易用单元代码
  DestBrokerID: 'string'
}

// Fens用户信息
structDict['CThostFtdcFensUserInfoField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // 登录模式
  LoginMode: 'char'
}

// 当前银期所属交易中心
structDict['CThostFtdcCurrTransferIdentityField'] = {
  // 交易中心代码
  IdentityID: 'int'
}

// 禁止登录用户
structDict['CThostFtdcLoginForbiddenUserField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string',
  // IP地址
  IPAddress: 'string'
}

// 查询禁止登录用户
structDict['CThostFtdcQryLoginForbiddenUserField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string'
}

// UDP组播组信息
structDict['CThostFtdcMulticastGroupInfoField'] = {
  // 组播组IP地址
  GroupIP: 'string',
  // 组播组IP端口
  GroupPort: 'int',
  // 源地址
  SourceIP: 'string'
}

// 资金账户基本准备金
structDict['CThostFtdcTradingAccountReserveField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 基本准备金
  Reserve: 'float',
  // 币种代码
  CurrencyID: 'string'
}

// 查询禁止登录IP
structDict['CThostFtdcQryLoginForbiddenIPField'] = {
  // IP地址
  IPAddress: 'string'
}

// 查询IP列表
structDict['CThostFtdcQryIPListField'] = {
  // IP地址
  IPAddress: 'string'
}

// 查询用户下单权限分配表
structDict['CThostFtdcQryUserRightsAssignField'] = {
  // 应用单元代码
  BrokerID: 'string',
  // 用户代码
  UserID: 'string'
}

// 银期预约开户确认请求
structDict['CThostFtdcReserveOpenAccountConfirmField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'undefined',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易ID
  TID: 'int',
  // 投资者帐号
  AccountID: 'string',
  // 期货密码
  Password: 'string',
  // 预约开户银行流水号
  BankReserveOpenSeq: 'string',
  // 预约开户日期
  BookDate: 'string',
  // 预约开户验证密码
  BookPsw: 'string',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 银期预约开户
structDict['CThostFtdcReserveOpenAccountField'] = {
  // 业务功能码
  TradeCode: 'string',
  // 银行代码
  BankID: 'string',
  // 银行分支机构代码
  BankBranchID: 'string',
  // 期商代码
  BrokerID: 'string',
  // 期商分支机构代码
  BrokerBranchID: 'string',
  // 交易日期
  TradeDate: 'string',
  // 交易时间
  TradeTime: 'string',
  // 银行流水号
  BankSerial: 'string',
  // 交易系统日期
  TradingDay: 'string',
  // 银期平台消息流水号
  PlateSerial: 'int',
  // 最后分片标志
  LastFragment: 'char',
  // 会话号
  SessionID: 'int',
  // 客户姓名
  CustomerName: 'undefined',
  // 证件类型
  IdCardType: 'char',
  // 证件号码
  IdentifiedCardNo: 'string',
  // 性别
  Gender: 'char',
  // 国家代码
  CountryCode: 'string',
  // 客户类型
  CustType: 'char',
  // 地址
  Address: 'string',
  // 邮编
  ZipCode: 'string',
  // 电话号码
  Telephone: 'string',
  // 手机
  MobilePhone: 'string',
  // 传真
  Fax: 'string',
  // 电子邮件
  EMail: 'string',
  // 资金账户状态
  MoneyAccountStatus: 'char',
  // 银行帐号
  BankAccount: 'string',
  // 银行密码
  BankPassWord: 'string',
  // 安装编号
  InstallID: 'int',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'char',
  // 币种代码
  CurrencyID: 'string',
  // 摘要
  Digest: 'string',
  // 银行帐号类型
  BankAccType: 'char',
  // 期货公司银行编码
  BrokerIDByBank: 'string',
  // 交易ID
  TID: 'int',
  // 预约开户状态
  ReserveOpenAccStas: 'undefined',
  // 错误代码
  ErrorID: 'int',
  // 错误信息
  ErrorMsg: 'string'
}

// 银行账户属性
structDict['CThostFtdcAccountPropertyField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者帐号
  AccountID: 'string',
  // 银行统一标识类型
  BankID: 'string',
  // 银行账户
  BankAccount: 'string',
  // 银行账户的开户人名称
  OpenName: 'string',
  // 银行账户的开户行
  OpenBank: 'string',
  // 是否活跃
  IsActive: 'int',
  // 账户来源
  AccountSourceType: 'char',
  // 开户日期
  OpenDate: 'string',
  // 注销日期
  CancelDate: 'string',
  // 录入员代码
  OperatorID: 'string',
  // 录入日期
  OperateDate: 'string',
  // 录入时间
  OperateTime: 'string',
  // 币种代码
  CurrencyID: 'string'
}

// 查询当前交易中心
structDict['CThostFtdcQryCurrDRIdentityField'] = {
  // 交易中心代码
  DRIdentityID: 'int'
}

// 当前交易中心
structDict['CThostFtdcCurrDRIdentityField'] = {
  // 交易中心代码
  DRIdentityID: 'int'
}

// 查询二级代理商资金校验模式
structDict['CThostFtdcQrySecAgentCheckModeField'] = {
  // 经纪公司代码
  BrokerID: 'string',
  // 投资者代码
  InvestorID: 'string'
}

module.exports = structDict
