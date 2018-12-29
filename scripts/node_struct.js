const structDict = {}

// 信息分发
structDict['CThostFtdcDisseminationField'] = {
  // 序列系列号
  SequenceSeries: 'TThostFtdcSequenceSeriesType',
  // 序列号
  SequenceNo: 'TThostFtdcSequenceNoType'
}

// 用户登录请求
structDict['CThostFtdcReqUserLoginField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 密码
  Password: 'TThostFtdcPasswordType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 接口端产品信息
  InterfaceProductInfo: 'TThostFtdcProductInfoType',
  // 协议信息
  ProtocolInfo: 'TThostFtdcProtocolInfoType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 动态密码
  OneTimePassword: 'TThostFtdcPasswordType',
  // 终端IP地址
  ClientIPAddress: 'TThostFtdcIPAddressType',
  // 登录备注
  LoginRemark: 'TThostFtdcLoginRemarkType'
}

// 用户登录应答
structDict['CThostFtdcRspUserLoginField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 登录成功时间
  LoginTime: 'TThostFtdcTimeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 交易系统名称
  SystemName: 'TThostFtdcSystemNameType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 最大报单引用
  MaxOrderRef: 'TThostFtdcOrderRefType',
  // 上期所时间
  SHFETime: 'TThostFtdcTimeType',
  // 大商所时间
  DCETime: 'TThostFtdcTimeType',
  // 郑商所时间
  CZCETime: 'TThostFtdcTimeType',
  // 中金所时间
  FFEXTime: 'TThostFtdcTimeType',
  // 能源中心时间
  INETime: 'TThostFtdcTimeType'
}

// 用户登出请求
structDict['CThostFtdcUserLogoutField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 强制交易员退出
structDict['CThostFtdcForceUserLogoutField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 客户端认证请求
structDict['CThostFtdcReqAuthenticateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 认证码
  AuthCode: 'TThostFtdcAuthCodeType'
}

// 客户端认证响应
structDict['CThostFtdcRspAuthenticateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType'
}

// 客户端认证信息
structDict['CThostFtdcAuthenticationInfoField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 认证信息
  AuthInfo: 'TThostFtdcAuthInfoType',
  // 是否为认证结果
  IsResult: 'TThostFtdcBoolType'
}

// 用户登录应答2
structDict['CThostFtdcRspUserLogin2Field'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 登录成功时间
  LoginTime: 'TThostFtdcTimeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 交易系统名称
  SystemName: 'TThostFtdcSystemNameType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 最大报单引用
  MaxOrderRef: 'TThostFtdcOrderRefType',
  // 上期所时间
  SHFETime: 'TThostFtdcTimeType',
  // 大商所时间
  DCETime: 'TThostFtdcTimeType',
  // 郑商所时间
  CZCETime: 'TThostFtdcTimeType',
  // 中金所时间
  FFEXTime: 'TThostFtdcTimeType',
  // 能源中心时间
  INETime: 'TThostFtdcTimeType',
  // 随机串
  RandomString: 'TThostFtdcRandomStringType'
}

// 银期转帐报文头
structDict['CThostFtdcTransferHeaderField'] = {
  // 版本号，常量，1.0
  Version: 'TThostFtdcVersionType',
  // 交易代码，必填
  TradeCode: 'TThostFtdcTradeCodeType',
  // 交易日期，必填，格式：yyyymmdd
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间，必填，格式：hhmmss
  TradeTime: 'TThostFtdcTradeTimeType',
  // 发起方流水号，N/A
  TradeSerial: 'TThostFtdcTradeSerialType',
  // 期货公司代码，必填
  FutureID: 'TThostFtdcFutureIDType',
  // 银行代码，根据查询银行得到，必填
  BankID: 'TThostFtdcBankIDType',
  // 银行分中心代码，根据查询银行得到，必填
  BankBrchID: 'TThostFtdcBankBrchIDType',
  // 操作员，N/A
  OperNo: 'TThostFtdcOperNoType',
  // 交易设备类型，N/A
  DeviceID: 'TThostFtdcDeviceIDType',
  // 记录数，N/A
  RecordNum: 'TThostFtdcRecordNumType',
  // 会话编号，N/A
  SessionID: 'TThostFtdcSessionIDType',
  // 请求编号，N/A
  RequestID: 'TThostFtdcRequestIDType'
}

// 银行资金转期货请求，TradeCode=202001
structDict['CThostFtdcTransferBankToFutureReqField'] = {
  // 期货资金账户
  FutureAccount: 'TThostFtdcAccountIDType',
  // 密码标志
  FuturePwdFlag: 'TThostFtdcFuturePwdFlagType',
  // 密码
  FutureAccPwd: 'TThostFtdcFutureAccPwdType',
  // 转账金额
  TradeAmt: 'TThostFtdcMoneyType',
  // 客户手续费
  CustFee: 'TThostFtdcMoneyType',
  // 币种：RMB-人民币 USD-美圆 HKD-港元
  CurrencyCode: 'TThostFtdcCurrencyCodeType'
}

// 银行资金转期货请求响应
structDict['CThostFtdcTransferBankToFutureRspField'] = {
  // 响应代码
  RetCode: 'TThostFtdcRetCodeType',
  // 响应信息
  RetInfo: 'TThostFtdcRetInfoType',
  // 资金账户
  FutureAccount: 'TThostFtdcAccountIDType',
  // 转帐金额
  TradeAmt: 'TThostFtdcMoneyType',
  // 应收客户手续费
  CustFee: 'TThostFtdcMoneyType',
  // 币种
  CurrencyCode: 'TThostFtdcCurrencyCodeType'
}

// 期货资金转银行请求，TradeCode=202002
structDict['CThostFtdcTransferFutureToBankReqField'] = {
  // 期货资金账户
  FutureAccount: 'TThostFtdcAccountIDType',
  // 密码标志
  FuturePwdFlag: 'TThostFtdcFuturePwdFlagType',
  // 密码
  FutureAccPwd: 'TThostFtdcFutureAccPwdType',
  // 转账金额
  TradeAmt: 'TThostFtdcMoneyType',
  // 客户手续费
  CustFee: 'TThostFtdcMoneyType',
  // 币种：RMB-人民币 USD-美圆 HKD-港元
  CurrencyCode: 'TThostFtdcCurrencyCodeType'
}

// 期货资金转银行请求响应
structDict['CThostFtdcTransferFutureToBankRspField'] = {
  // 响应代码
  RetCode: 'TThostFtdcRetCodeType',
  // 响应信息
  RetInfo: 'TThostFtdcRetInfoType',
  // 资金账户
  FutureAccount: 'TThostFtdcAccountIDType',
  // 转帐金额
  TradeAmt: 'TThostFtdcMoneyType',
  // 应收客户手续费
  CustFee: 'TThostFtdcMoneyType',
  // 币种
  CurrencyCode: 'TThostFtdcCurrencyCodeType'
}

// 查询银行资金请求，TradeCode=204002
structDict['CThostFtdcTransferQryBankReqField'] = {
  // 期货资金账户
  FutureAccount: 'TThostFtdcAccountIDType',
  // 密码标志
  FuturePwdFlag: 'TThostFtdcFuturePwdFlagType',
  // 密码
  FutureAccPwd: 'TThostFtdcFutureAccPwdType',
  // 币种：RMB-人民币 USD-美圆 HKD-港元
  CurrencyCode: 'TThostFtdcCurrencyCodeType'
}

// 查询银行资金请求响应
structDict['CThostFtdcTransferQryBankRspField'] = {
  // 响应代码
  RetCode: 'TThostFtdcRetCodeType',
  // 响应信息
  RetInfo: 'TThostFtdcRetInfoType',
  // 资金账户
  FutureAccount: 'TThostFtdcAccountIDType',
  // 银行余额
  TradeAmt: 'TThostFtdcMoneyType',
  // 银行可用余额
  UseAmt: 'TThostFtdcMoneyType',
  // 银行可取余额
  FetchAmt: 'TThostFtdcMoneyType',
  // 币种
  CurrencyCode: 'TThostFtdcCurrencyCodeType'
}

// 查询银行交易明细请求，TradeCode=204999
structDict['CThostFtdcTransferQryDetailReqField'] = {
  // 期货资金账户
  FutureAccount: 'TThostFtdcAccountIDType'
}

// 查询银行交易明细请求响应
structDict['CThostFtdcTransferQryDetailRspField'] = {
  // 交易日期
  TradeDate: 'TThostFtdcDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 交易代码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 期货流水号
  FutureSerial: 'TThostFtdcTradeSerialNoType',
  // 期货公司代码
  FutureID: 'TThostFtdcFutureIDType',
  // 资金帐号
  FutureAccount: 'TThostFtdcFutureAccountType',
  // 银行流水号
  BankSerial: 'TThostFtdcTradeSerialNoType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分中心代码
  BankBrchID: 'TThostFtdcBankBrchIDType',
  // 银行账号
  BankAccount: 'TThostFtdcBankAccountType',
  // 证件号码
  CertCode: 'TThostFtdcCertCodeType',
  // 货币代码
  CurrencyCode: 'TThostFtdcCurrencyCodeType',
  // 发生金额
  TxAmount: 'TThostFtdcMoneyType',
  // 有效标志
  Flag: 'TThostFtdcTransferValidFlagType'
}

// 响应信息
structDict['CThostFtdcRspInfoField'] = {
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 交易所
structDict['CThostFtdcExchangeField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所名称
  ExchangeName: 'TThostFtdcExchangeNameType',
  // 交易所属性
  ExchangeProperty: 'TThostFtdcExchangePropertyType'
}

// 产品
structDict['CThostFtdcProductField'] = {
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 产品名称
  ProductName: 'TThostFtdcProductNameType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 产品类型
  ProductClass: 'TThostFtdcProductClassType',
  // 合约数量乘数
  VolumeMultiple: 'TThostFtdcVolumeMultipleType',
  // 最小变动价位
  PriceTick: 'TThostFtdcPriceType',
  // 市价单最大下单量
  MaxMarketOrderVolume: 'TThostFtdcVolumeType',
  // 市价单最小下单量
  MinMarketOrderVolume: 'TThostFtdcVolumeType',
  // 限价单最大下单量
  MaxLimitOrderVolume: 'TThostFtdcVolumeType',
  // 限价单最小下单量
  MinLimitOrderVolume: 'TThostFtdcVolumeType',
  // 持仓类型
  PositionType: 'TThostFtdcPositionTypeType',
  // 持仓日期类型
  PositionDateType: 'TThostFtdcPositionDateTypeType',
  // 平仓处理类型
  CloseDealType: 'TThostFtdcCloseDealTypeType',
  // 交易币种类型
  TradeCurrencyID: 'TThostFtdcCurrencyIDType',
  // 质押资金可用范围
  MortgageFundUseRange: 'TThostFtdcMortgageFundUseRangeType',
  // 交易所产品代码
  ExchangeProductID: 'TThostFtdcInstrumentIDType',
  // 合约基础商品乘数
  UnderlyingMultiple: 'TThostFtdcUnderlyingMultipleType'
}

// 合约
structDict['CThostFtdcInstrumentField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约名称
  InstrumentName: 'TThostFtdcInstrumentNameType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 产品类型
  ProductClass: 'TThostFtdcProductClassType',
  // 交割年份
  DeliveryYear: 'TThostFtdcYearType',
  // 交割月
  DeliveryMonth: 'TThostFtdcMonthType',
  // 市价单最大下单量
  MaxMarketOrderVolume: 'TThostFtdcVolumeType',
  // 市价单最小下单量
  MinMarketOrderVolume: 'TThostFtdcVolumeType',
  // 限价单最大下单量
  MaxLimitOrderVolume: 'TThostFtdcVolumeType',
  // 限价单最小下单量
  MinLimitOrderVolume: 'TThostFtdcVolumeType',
  // 合约数量乘数
  VolumeMultiple: 'TThostFtdcVolumeMultipleType',
  // 最小变动价位
  PriceTick: 'TThostFtdcPriceType',
  // 创建日
  CreateDate: 'TThostFtdcDateType',
  // 上市日
  OpenDate: 'TThostFtdcDateType',
  // 到期日
  ExpireDate: 'TThostFtdcDateType',
  // 开始交割日
  StartDelivDate: 'TThostFtdcDateType',
  // 结束交割日
  EndDelivDate: 'TThostFtdcDateType',
  // 合约生命周期状态
  InstLifePhase: 'TThostFtdcInstLifePhaseType',
  // 当前是否交易
  IsTrading: 'TThostFtdcBoolType',
  // 持仓类型
  PositionType: 'TThostFtdcPositionTypeType',
  // 持仓日期类型
  PositionDateType: 'TThostFtdcPositionDateTypeType',
  // 多头保证金率
  LongMarginRatio: 'TThostFtdcRatioType',
  // 空头保证金率
  ShortMarginRatio: 'TThostFtdcRatioType',
  // 是否使用大额单边保证金算法
  MaxMarginSideAlgorithm: 'TThostFtdcMaxMarginSideAlgorithmType',
  // 基础商品代码
  UnderlyingInstrID: 'TThostFtdcInstrumentIDType',
  // 执行价
  StrikePrice: 'TThostFtdcPriceType',
  // 期权类型
  OptionsType: 'TThostFtdcOptionsTypeType',
  // 合约基础商品乘数
  UnderlyingMultiple: 'TThostFtdcUnderlyingMultipleType',
  // 组合类型
  CombinationType: 'TThostFtdcCombinationTypeType'
}

// 经纪公司
structDict['CThostFtdcBrokerField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 经纪公司简称
  BrokerAbbr: 'TThostFtdcBrokerAbbrType',
  // 经纪公司名称
  BrokerName: 'TThostFtdcBrokerNameType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType'
}

// 交易所交易员
structDict['CThostFtdcTraderField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 密码
  Password: 'TThostFtdcPasswordType',
  // 安装数量
  InstallCount: 'TThostFtdcInstallCountType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType'
}

// 投资者
structDict['CThostFtdcInvestorField'] = {
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者分组代码
  InvestorGroupID: 'TThostFtdcInvestorIDType',
  // 投资者名称
  InvestorName: 'TThostFtdcPartyNameType',
  // 证件类型
  IdentifiedCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType',
  // 联系电话
  Telephone: 'TThostFtdcTelephoneType',
  // 通讯地址
  Address: 'TThostFtdcAddressType',
  // 开户日期
  OpenDate: 'TThostFtdcDateType',
  // 手机
  Mobile: 'TThostFtdcMobileType',
  // 手续费率模板代码
  CommModelID: 'TThostFtdcInvestorIDType',
  // 保证金率模板代码
  MarginModelID: 'TThostFtdcInvestorIDType'
}

// 交易编码
structDict['CThostFtdcTradingCodeField'] = {
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType',
  // 交易编码类型
  ClientIDType: 'TThostFtdcClientIDTypeType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 业务类型
  BizType: 'TThostFtdcBizTypeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 会员编码和经纪公司编码对照表
structDict['CThostFtdcPartBrokerField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType'
}

// 管理用户
structDict['CThostFtdcSuperUserField'] = {
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 用户名称
  UserName: 'TThostFtdcUserNameType',
  // 密码
  Password: 'TThostFtdcPasswordType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType'
}

// 管理用户功能权限
structDict['CThostFtdcSuperUserFunctionField'] = {
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 功能代码
  FunctionCode: 'TThostFtdcFunctionCodeType'
}

// 投资者组
structDict['CThostFtdcInvestorGroupField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者分组代码
  InvestorGroupID: 'TThostFtdcInvestorIDType',
  // 投资者分组名称
  InvestorGroupName: 'TThostFtdcInvestorGroupNameType'
}

// 资金账户
structDict['CThostFtdcTradingAccountField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 上次质押金额
  PreMortgage: 'TThostFtdcMoneyType',
  // 上次信用额度
  PreCredit: 'TThostFtdcMoneyType',
  // 上次存款额
  PreDeposit: 'TThostFtdcMoneyType',
  // 上次结算准备金
  PreBalance: 'TThostFtdcMoneyType',
  // 上次占用的保证金
  PreMargin: 'TThostFtdcMoneyType',
  // 利息基数
  InterestBase: 'TThostFtdcMoneyType',
  // 利息收入
  Interest: 'TThostFtdcMoneyType',
  // 入金金额
  Deposit: 'TThostFtdcMoneyType',
  // 出金金额
  Withdraw: 'TThostFtdcMoneyType',
  // 冻结的保证金
  FrozenMargin: 'TThostFtdcMoneyType',
  // 冻结的资金
  FrozenCash: 'TThostFtdcMoneyType',
  // 冻结的手续费
  FrozenCommission: 'TThostFtdcMoneyType',
  // 当前保证金总额
  CurrMargin: 'TThostFtdcMoneyType',
  // 资金差额
  CashIn: 'TThostFtdcMoneyType',
  // 手续费
  Commission: 'TThostFtdcMoneyType',
  // 平仓盈亏
  CloseProfit: 'TThostFtdcMoneyType',
  // 持仓盈亏
  PositionProfit: 'TThostFtdcMoneyType',
  // 期货结算准备金
  Balance: 'TThostFtdcMoneyType',
  // 可用资金
  Available: 'TThostFtdcMoneyType',
  // 可取资金
  WithdrawQuota: 'TThostFtdcMoneyType',
  // 基本准备金
  Reserve: 'TThostFtdcMoneyType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 信用额度
  Credit: 'TThostFtdcMoneyType',
  // 质押金额
  Mortgage: 'TThostFtdcMoneyType',
  // 交易所保证金
  ExchangeMargin: 'TThostFtdcMoneyType',
  // 投资者交割保证金
  DeliveryMargin: 'TThostFtdcMoneyType',
  // 交易所交割保证金
  ExchangeDeliveryMargin: 'TThostFtdcMoneyType',
  // 保底期货结算准备金
  ReserveBalance: 'TThostFtdcMoneyType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 上次货币质入金额
  PreFundMortgageIn: 'TThostFtdcMoneyType',
  // 上次货币质出金额
  PreFundMortgageOut: 'TThostFtdcMoneyType',
  // 货币质入金额
  FundMortgageIn: 'TThostFtdcMoneyType',
  // 货币质出金额
  FundMortgageOut: 'TThostFtdcMoneyType',
  // 货币质押余额
  FundMortgageAvailable: 'TThostFtdcMoneyType',
  // 可质押货币金额
  MortgageableFund: 'TThostFtdcMoneyType',
  // 特殊产品占用保证金
  SpecProductMargin: 'TThostFtdcMoneyType',
  // 特殊产品冻结保证金
  SpecProductFrozenMargin: 'TThostFtdcMoneyType',
  // 特殊产品手续费
  SpecProductCommission: 'TThostFtdcMoneyType',
  // 特殊产品冻结手续费
  SpecProductFrozenCommission: 'TThostFtdcMoneyType',
  // 特殊产品持仓盈亏
  SpecProductPositionProfit: 'TThostFtdcMoneyType',
  // 特殊产品平仓盈亏
  SpecProductCloseProfit: 'TThostFtdcMoneyType',
  // 根据持仓盈亏算法计算的特殊产品持仓盈亏
  SpecProductPositionProfitByAlg: 'TThostFtdcMoneyType',
  // 特殊产品交易所保证金
  SpecProductExchangeMargin: 'TThostFtdcMoneyType',
  // 业务类型
  BizType: 'TThostFtdcBizTypeType',
  // 延时换汇冻结金额
  FrozenSwap: 'TThostFtdcMoneyType',
  // 剩余换汇额度
  RemainSwap: 'TThostFtdcMoneyType'
}

// 投资者持仓
structDict['CThostFtdcInvestorPositionField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 持仓多空方向
  PosiDirection: 'TThostFtdcPosiDirectionType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 持仓日期
  PositionDate: 'TThostFtdcPositionDateType',
  // 上日持仓
  YdPosition: 'TThostFtdcVolumeType',
  // 今日持仓
  Position: 'TThostFtdcVolumeType',
  // 多头冻结
  LongFrozen: 'TThostFtdcVolumeType',
  // 空头冻结
  ShortFrozen: 'TThostFtdcVolumeType',
  // 开仓冻结金额
  LongFrozenAmount: 'TThostFtdcMoneyType',
  // 开仓冻结金额
  ShortFrozenAmount: 'TThostFtdcMoneyType',
  // 开仓量
  OpenVolume: 'TThostFtdcVolumeType',
  // 平仓量
  CloseVolume: 'TThostFtdcVolumeType',
  // 开仓金额
  OpenAmount: 'TThostFtdcMoneyType',
  // 平仓金额
  CloseAmount: 'TThostFtdcMoneyType',
  // 持仓成本
  PositionCost: 'TThostFtdcMoneyType',
  // 上次占用的保证金
  PreMargin: 'TThostFtdcMoneyType',
  // 占用的保证金
  UseMargin: 'TThostFtdcMoneyType',
  // 冻结的保证金
  FrozenMargin: 'TThostFtdcMoneyType',
  // 冻结的资金
  FrozenCash: 'TThostFtdcMoneyType',
  // 冻结的手续费
  FrozenCommission: 'TThostFtdcMoneyType',
  // 资金差额
  CashIn: 'TThostFtdcMoneyType',
  // 手续费
  Commission: 'TThostFtdcMoneyType',
  // 平仓盈亏
  CloseProfit: 'TThostFtdcMoneyType',
  // 持仓盈亏
  PositionProfit: 'TThostFtdcMoneyType',
  // 上次结算价
  PreSettlementPrice: 'TThostFtdcPriceType',
  // 本次结算价
  SettlementPrice: 'TThostFtdcPriceType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 开仓成本
  OpenCost: 'TThostFtdcMoneyType',
  // 交易所保证金
  ExchangeMargin: 'TThostFtdcMoneyType',
  // 组合成交形成的持仓
  CombPosition: 'TThostFtdcVolumeType',
  // 组合多头冻结
  CombLongFrozen: 'TThostFtdcVolumeType',
  // 组合空头冻结
  CombShortFrozen: 'TThostFtdcVolumeType',
  // 逐日盯市平仓盈亏
  CloseProfitByDate: 'TThostFtdcMoneyType',
  // 逐笔对冲平仓盈亏
  CloseProfitByTrade: 'TThostFtdcMoneyType',
  // 今日持仓
  TodayPosition: 'TThostFtdcVolumeType',
  // 保证金率
  MarginRateByMoney: 'TThostFtdcRatioType',
  // 保证金率(按手数)
  MarginRateByVolume: 'TThostFtdcRatioType',
  // 执行冻结
  StrikeFrozen: 'TThostFtdcVolumeType',
  // 执行冻结金额
  StrikeFrozenAmount: 'TThostFtdcMoneyType',
  // 放弃执行冻结
  AbandonFrozen: 'TThostFtdcVolumeType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 执行冻结的昨仓
  YdStrikeFrozen: 'TThostFtdcVolumeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 合约保证金率
structDict['CThostFtdcInstrumentMarginRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 多头保证金率
  LongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 多头保证金费
  LongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 空头保证金率
  ShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 空头保证金费
  ShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 是否相对交易所收取
  IsRelative: 'TThostFtdcBoolType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 合约手续费率
structDict['CThostFtdcInstrumentCommissionRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 开仓手续费率
  OpenRatioByMoney: 'TThostFtdcRatioType',
  // 开仓手续费
  OpenRatioByVolume: 'TThostFtdcRatioType',
  // 平仓手续费率
  CloseRatioByMoney: 'TThostFtdcRatioType',
  // 平仓手续费
  CloseRatioByVolume: 'TThostFtdcRatioType',
  // 平今手续费率
  CloseTodayRatioByMoney: 'TThostFtdcRatioType',
  // 平今手续费
  CloseTodayRatioByVolume: 'TThostFtdcRatioType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 业务类型
  BizType: 'TThostFtdcBizTypeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 深度行情
structDict['CThostFtdcDepthMarketDataField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 最新价
  LastPrice: 'TThostFtdcPriceType',
  // 上次结算价
  PreSettlementPrice: 'TThostFtdcPriceType',
  // 昨收盘
  PreClosePrice: 'TThostFtdcPriceType',
  // 昨持仓量
  PreOpenInterest: 'TThostFtdcLargeVolumeType',
  // 今开盘
  OpenPrice: 'TThostFtdcPriceType',
  // 最高价
  HighestPrice: 'TThostFtdcPriceType',
  // 最低价
  LowestPrice: 'TThostFtdcPriceType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 成交金额
  Turnover: 'TThostFtdcMoneyType',
  // 持仓量
  OpenInterest: 'TThostFtdcLargeVolumeType',
  // 今收盘
  ClosePrice: 'TThostFtdcPriceType',
  // 本次结算价
  SettlementPrice: 'TThostFtdcPriceType',
  // 涨停板价
  UpperLimitPrice: 'TThostFtdcPriceType',
  // 跌停板价
  LowerLimitPrice: 'TThostFtdcPriceType',
  // 昨虚实度
  PreDelta: 'TThostFtdcRatioType',
  // 今虚实度
  CurrDelta: 'TThostFtdcRatioType',
  // 最后修改时间
  UpdateTime: 'TThostFtdcTimeType',
  // 最后修改毫秒
  UpdateMillisec: 'TThostFtdcMillisecType',
  // 申买价一
  BidPrice1: 'TThostFtdcPriceType',
  // 申买量一
  BidVolume1: 'TThostFtdcVolumeType',
  // 申卖价一
  AskPrice1: 'TThostFtdcPriceType',
  // 申卖量一
  AskVolume1: 'TThostFtdcVolumeType',
  // 申买价二
  BidPrice2: 'TThostFtdcPriceType',
  // 申买量二
  BidVolume2: 'TThostFtdcVolumeType',
  // 申卖价二
  AskPrice2: 'TThostFtdcPriceType',
  // 申卖量二
  AskVolume2: 'TThostFtdcVolumeType',
  // 申买价三
  BidPrice3: 'TThostFtdcPriceType',
  // 申买量三
  BidVolume3: 'TThostFtdcVolumeType',
  // 申卖价三
  AskPrice3: 'TThostFtdcPriceType',
  // 申卖量三
  AskVolume3: 'TThostFtdcVolumeType',
  // 申买价四
  BidPrice4: 'TThostFtdcPriceType',
  // 申买量四
  BidVolume4: 'TThostFtdcVolumeType',
  // 申卖价四
  AskPrice4: 'TThostFtdcPriceType',
  // 申卖量四
  AskVolume4: 'TThostFtdcVolumeType',
  // 申买价五
  BidPrice5: 'TThostFtdcPriceType',
  // 申买量五
  BidVolume5: 'TThostFtdcVolumeType',
  // 申卖价五
  AskPrice5: 'TThostFtdcPriceType',
  // 申卖量五
  AskVolume5: 'TThostFtdcVolumeType',
  // 当日均价
  AveragePrice: 'TThostFtdcPriceType',
  // 业务日期
  ActionDay: 'TThostFtdcDateType'
}

// 投资者合约交易权限
structDict['CThostFtdcInstrumentTradingRightField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易权限
  TradingRight: 'TThostFtdcTradingRightType'
}

// 经纪公司用户
structDict['CThostFtdcBrokerUserField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 用户名称
  UserName: 'TThostFtdcUserNameType',
  // 用户类型
  UserType: 'TThostFtdcUserTypeType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType',
  // 是否使用令牌
  IsUsingOTP: 'TThostFtdcBoolType',
  // 是否强制终端认证
  IsAuthForce: 'TThostFtdcBoolType'
}

// 经纪公司用户口令
structDict['CThostFtdcBrokerUserPasswordField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 密码
  Password: 'TThostFtdcPasswordType',
  // 上次修改时间
  LastUpdateTime: 'TThostFtdcDateTimeType',
  // 上次登陆时间
  LastLoginTime: 'TThostFtdcDateTimeType',
  // 密码过期时间
  ExpireDate: 'TThostFtdcDateType',
  // 弱密码过期时间
  WeakExpireDate: 'TThostFtdcDateType'
}

// 经纪公司用户功能权限
structDict['CThostFtdcBrokerUserFunctionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 经纪公司功能代码
  BrokerFunctionCode: 'TThostFtdcBrokerFunctionCodeType'
}

// 交易所交易员报盘机
structDict['CThostFtdcTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所交易员连接状态
  TraderConnectStatus: 'TThostFtdcTraderConnectStatusType',
  // 发出连接请求的日期
  ConnectRequestDate: 'TThostFtdcDateType',
  // 发出连接请求的时间
  ConnectRequestTime: 'TThostFtdcTimeType',
  // 上次报告日期
  LastReportDate: 'TThostFtdcDateType',
  // 上次报告时间
  LastReportTime: 'TThostFtdcTimeType',
  // 完成连接日期
  ConnectDate: 'TThostFtdcDateType',
  // 完成连接时间
  ConnectTime: 'TThostFtdcTimeType',
  // 启动日期
  StartDate: 'TThostFtdcDateType',
  // 启动时间
  StartTime: 'TThostFtdcTimeType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 本席位最大成交编号
  MaxTradeID: 'TThostFtdcTradeIDType',
  // 本席位最大报单备拷
  MaxOrderMessageReference: 'TThostFtdcReturnCodeType'
}

// 投资者结算结果
structDict['CThostFtdcSettlementInfoField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 消息正文
  Content: 'TThostFtdcContentType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 合约保证金率调整
structDict['CThostFtdcInstrumentMarginRateAdjustField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 多头保证金率
  LongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 多头保证金费
  LongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 空头保证金率
  ShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 空头保证金费
  ShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 是否相对交易所收取
  IsRelative: 'TThostFtdcBoolType'
}

// 交易所保证金率
structDict['CThostFtdcExchangeMarginRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 多头保证金率
  LongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 多头保证金费
  LongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 空头保证金率
  ShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 空头保证金费
  ShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 交易所保证金率调整
structDict['CThostFtdcExchangeMarginRateAdjustField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 跟随交易所投资者多头保证金率
  LongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 跟随交易所投资者多头保证金费
  LongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 跟随交易所投资者空头保证金率
  ShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 跟随交易所投资者空头保证金费
  ShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 交易所多头保证金率
  ExchLongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 交易所多头保证金费
  ExchLongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 交易所空头保证金率
  ExchShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 交易所空头保证金费
  ExchShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 不跟随交易所投资者多头保证金率
  NoLongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 不跟随交易所投资者多头保证金费
  NoLongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 不跟随交易所投资者空头保证金率
  NoShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 不跟随交易所投资者空头保证金费
  NoShortMarginRatioByVolume: 'TThostFtdcMoneyType'
}

// 汇率
structDict['CThostFtdcExchangeRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 源币种
  FromCurrencyID: 'TThostFtdcCurrencyIDType',
  // 源币种单位数量
  FromCurrencyUnit: 'TThostFtdcCurrencyUnitType',
  // 目标币种
  ToCurrencyID: 'TThostFtdcCurrencyIDType',
  // 汇率
  ExchangeRate: 'TThostFtdcExchangeRateType'
}

// 结算引用
structDict['CThostFtdcSettlementRefField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType'
}

// 当前时间
structDict['CThostFtdcCurrentTimeField'] = {
  // 当前日期
  CurrDate: 'TThostFtdcDateType',
  // 当前时间
  CurrTime: 'TThostFtdcTimeType',
  // 当前时间（毫秒）
  CurrMillisec: 'TThostFtdcMillisecType',
  // 业务日期
  ActionDay: 'TThostFtdcDateType'
}

// 通讯阶段
structDict['CThostFtdcCommPhaseField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 通讯时段编号
  CommPhaseNo: 'TThostFtdcCommPhaseNoType',
  // 系统编号
  SystemID: 'TThostFtdcSystemIDType'
}

// 登录信息
structDict['CThostFtdcLoginInfoField'] = {
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 登录日期
  LoginDate: 'TThostFtdcDateType',
  // 登录时间
  LoginTime: 'TThostFtdcTimeType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 接口端产品信息
  InterfaceProductInfo: 'TThostFtdcProductInfoType',
  // 协议信息
  ProtocolInfo: 'TThostFtdcProtocolInfoType',
  // 系统名称
  SystemName: 'TThostFtdcSystemNameType',
  // 密码,已弃用
  PasswordDeprecated: 'TThostFtdcPasswordType',
  // 最大报单引用
  MaxOrderRef: 'TThostFtdcOrderRefType',
  // 上期所时间
  SHFETime: 'TThostFtdcTimeType',
  // 大商所时间
  DCETime: 'TThostFtdcTimeType',
  // 郑商所时间
  CZCETime: 'TThostFtdcTimeType',
  // 中金所时间
  FFEXTime: 'TThostFtdcTimeType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 动态密码
  OneTimePassword: 'TThostFtdcPasswordType',
  // 能源中心时间
  INETime: 'TThostFtdcTimeType',
  // 查询时是否需要流控
  IsQryControl: 'TThostFtdcBoolType',
  // 登录备注
  LoginRemark: 'TThostFtdcLoginRemarkType',
  // 密码
  Password: 'TThostFtdcPasswordType'
}

// 登录信息
structDict['CThostFtdcLogoutAllField'] = {
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 系统名称
  SystemName: 'TThostFtdcSystemNameType'
}

// 前置状态
structDict['CThostFtdcFrontStatusField'] = {
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 上次报告日期
  LastReportDate: 'TThostFtdcDateType',
  // 上次报告时间
  LastReportTime: 'TThostFtdcTimeType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType'
}

// 用户口令变更
structDict['CThostFtdcUserPasswordUpdateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 原来的口令
  OldPassword: 'TThostFtdcPasswordType',
  // 新的口令
  NewPassword: 'TThostFtdcPasswordType'
}

// 输入报单
structDict['CThostFtdcInputOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 报单价格条件
  OrderPriceType: 'TThostFtdcOrderPriceTypeType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 组合开平标志
  CombOffsetFlag: 'TThostFtdcCombOffsetFlagType',
  // 组合投机套保标志
  CombHedgeFlag: 'TThostFtdcCombHedgeFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量
  VolumeTotalOriginal: 'TThostFtdcVolumeType',
  // 有效期类型
  TimeCondition: 'TThostFtdcTimeConditionType',
  // GTD日期
  GTDDate: 'TThostFtdcDateType',
  // 成交量类型
  VolumeCondition: 'TThostFtdcVolumeConditionType',
  // 最小成交量
  MinVolume: 'TThostFtdcVolumeType',
  // 触发条件
  ContingentCondition: 'TThostFtdcContingentConditionType',
  // 止损价
  StopPrice: 'TThostFtdcPriceType',
  // 强平原因
  ForceCloseReason: 'TThostFtdcForceCloseReasonType',
  // 自动挂起标志
  IsAutoSuspend: 'TThostFtdcBoolType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 用户强评标志
  UserForceClose: 'TThostFtdcBoolType',
  // 互换单标志
  IsSwapOrder: 'TThostFtdcBoolType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 报单
structDict['CThostFtdcOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 报单价格条件
  OrderPriceType: 'TThostFtdcOrderPriceTypeType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 组合开平标志
  CombOffsetFlag: 'TThostFtdcCombOffsetFlagType',
  // 组合投机套保标志
  CombHedgeFlag: 'TThostFtdcCombHedgeFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量
  VolumeTotalOriginal: 'TThostFtdcVolumeType',
  // 有效期类型
  TimeCondition: 'TThostFtdcTimeConditionType',
  // GTD日期
  GTDDate: 'TThostFtdcDateType',
  // 成交量类型
  VolumeCondition: 'TThostFtdcVolumeConditionType',
  // 最小成交量
  MinVolume: 'TThostFtdcVolumeType',
  // 触发条件
  ContingentCondition: 'TThostFtdcContingentConditionType',
  // 止损价
  StopPrice: 'TThostFtdcPriceType',
  // 强平原因
  ForceCloseReason: 'TThostFtdcForceCloseReasonType',
  // 自动挂起标志
  IsAutoSuspend: 'TThostFtdcBoolType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 报单提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 报单来源
  OrderSource: 'TThostFtdcOrderSourceType',
  // 报单状态
  OrderStatus: 'TThostFtdcOrderStatusType',
  // 报单类型
  OrderType: 'TThostFtdcOrderTypeType',
  // 今成交数量
  VolumeTraded: 'TThostFtdcVolumeType',
  // 剩余数量
  VolumeTotal: 'TThostFtdcVolumeType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 委托时间
  InsertTime: 'TThostFtdcTimeType',
  // 激活时间
  ActiveTime: 'TThostFtdcTimeType',
  // 挂起时间
  SuspendTime: 'TThostFtdcTimeType',
  // 最后修改时间
  UpdateTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 最后修改交易所交易员代码
  ActiveTraderID: 'TThostFtdcTraderIDType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 用户强评标志
  UserForceClose: 'TThostFtdcBoolType',
  // 操作用户代码
  ActiveUserID: 'TThostFtdcUserIDType',
  // 经纪公司报单编号
  BrokerOrderSeq: 'TThostFtdcSequenceNoType',
  // 相关报单
  RelativeOrderSysID: 'TThostFtdcOrderSysIDType',
  // 郑商所成交数量
  ZCETotalTradedVolume: 'TThostFtdcVolumeType',
  // 互换单标志
  IsSwapOrder: 'TThostFtdcBoolType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所报单
structDict['CThostFtdcExchangeOrderField'] = {
  // 报单价格条件
  OrderPriceType: 'TThostFtdcOrderPriceTypeType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 组合开平标志
  CombOffsetFlag: 'TThostFtdcCombOffsetFlagType',
  // 组合投机套保标志
  CombHedgeFlag: 'TThostFtdcCombHedgeFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量
  VolumeTotalOriginal: 'TThostFtdcVolumeType',
  // 有效期类型
  TimeCondition: 'TThostFtdcTimeConditionType',
  // GTD日期
  GTDDate: 'TThostFtdcDateType',
  // 成交量类型
  VolumeCondition: 'TThostFtdcVolumeConditionType',
  // 最小成交量
  MinVolume: 'TThostFtdcVolumeType',
  // 触发条件
  ContingentCondition: 'TThostFtdcContingentConditionType',
  // 止损价
  StopPrice: 'TThostFtdcPriceType',
  // 强平原因
  ForceCloseReason: 'TThostFtdcForceCloseReasonType',
  // 自动挂起标志
  IsAutoSuspend: 'TThostFtdcBoolType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 报单提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 报单来源
  OrderSource: 'TThostFtdcOrderSourceType',
  // 报单状态
  OrderStatus: 'TThostFtdcOrderStatusType',
  // 报单类型
  OrderType: 'TThostFtdcOrderTypeType',
  // 今成交数量
  VolumeTraded: 'TThostFtdcVolumeType',
  // 剩余数量
  VolumeTotal: 'TThostFtdcVolumeType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 委托时间
  InsertTime: 'TThostFtdcTimeType',
  // 激活时间
  ActiveTime: 'TThostFtdcTimeType',
  // 挂起时间
  SuspendTime: 'TThostFtdcTimeType',
  // 最后修改时间
  UpdateTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 最后修改交易所交易员代码
  ActiveTraderID: 'TThostFtdcTraderIDType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所报单插入失败
structDict['CThostFtdcExchangeOrderInsertErrorField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 输入报单操作
structDict['CThostFtdcInputOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报单操作引用
  OrderActionRef: 'TThostFtdcOrderActionRefType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量变化
  VolumeChange: 'TThostFtdcVolumeType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 报单操作
structDict['CThostFtdcOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报单操作引用
  OrderActionRef: 'TThostFtdcOrderActionRefType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量变化
  VolumeChange: 'TThostFtdcVolumeType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所报单操作
structDict['CThostFtdcExchangeOrderActionField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量变化
  VolumeChange: 'TThostFtdcVolumeType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所报单操作失败
structDict['CThostFtdcExchangeOrderActionErrorField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 交易所成交
structDict['CThostFtdcExchangeTradeField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 成交编号
  TradeID: 'TThostFtdcTradeIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 交易角色
  TradingRole: 'TThostFtdcTradingRoleType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 价格
  Price: 'TThostFtdcPriceType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 成交时期
  TradeDate: 'TThostFtdcDateType',
  // 成交时间
  TradeTime: 'TThostFtdcTimeType',
  // 成交类型
  TradeType: 'TThostFtdcTradeTypeType',
  // 成交价来源
  PriceSource: 'TThostFtdcPriceSourceType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 成交来源
  TradeSource: 'TThostFtdcTradeSourceType'
}

// 成交
structDict['CThostFtdcTradeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 成交编号
  TradeID: 'TThostFtdcTradeIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 交易角色
  TradingRole: 'TThostFtdcTradingRoleType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 价格
  Price: 'TThostFtdcPriceType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 成交时期
  TradeDate: 'TThostFtdcDateType',
  // 成交时间
  TradeTime: 'TThostFtdcTimeType',
  // 成交类型
  TradeType: 'TThostFtdcTradeTypeType',
  // 成交价来源
  PriceSource: 'TThostFtdcPriceSourceType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 经纪公司报单编号
  BrokerOrderSeq: 'TThostFtdcSequenceNoType',
  // 成交来源
  TradeSource: 'TThostFtdcTradeSourceType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 用户会话
structDict['CThostFtdcUserSessionField'] = {
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 登录日期
  LoginDate: 'TThostFtdcDateType',
  // 登录时间
  LoginTime: 'TThostFtdcTimeType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 接口端产品信息
  InterfaceProductInfo: 'TThostFtdcProductInfoType',
  // 协议信息
  ProtocolInfo: 'TThostFtdcProtocolInfoType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 登录备注
  LoginRemark: 'TThostFtdcLoginRemarkType'
}

// 查询最大报单数量
structDict['CThostFtdcQueryMaxOrderVolumeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 最大允许报单数量
  MaxVolume: 'TThostFtdcVolumeType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 投资者结算结果确认信息
structDict['CThostFtdcSettlementInfoConfirmField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 确认日期
  ConfirmDate: 'TThostFtdcDateType',
  // 确认时间
  ConfirmTime: 'TThostFtdcTimeType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 出入金同步
structDict['CThostFtdcSyncDepositField'] = {
  // 出入金流水号
  DepositSeqNo: 'TThostFtdcDepositSeqNoType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 入金金额
  Deposit: 'TThostFtdcMoneyType',
  // 是否强制进行
  IsForce: 'TThostFtdcBoolType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 货币质押同步
structDict['CThostFtdcSyncFundMortgageField'] = {
  // 货币质押流水号
  MortgageSeqNo: 'TThostFtdcDepositSeqNoType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 源币种
  FromCurrencyID: 'TThostFtdcCurrencyIDType',
  // 质押金额
  MortgageAmount: 'TThostFtdcMoneyType',
  // 目标币种
  ToCurrencyID: 'TThostFtdcCurrencyIDType'
}

// 经纪公司同步
structDict['CThostFtdcBrokerSyncField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType'
}

// 正在同步中的投资者
structDict['CThostFtdcSyncingInvestorField'] = {
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者分组代码
  InvestorGroupID: 'TThostFtdcInvestorIDType',
  // 投资者名称
  InvestorName: 'TThostFtdcPartyNameType',
  // 证件类型
  IdentifiedCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType',
  // 联系电话
  Telephone: 'TThostFtdcTelephoneType',
  // 通讯地址
  Address: 'TThostFtdcAddressType',
  // 开户日期
  OpenDate: 'TThostFtdcDateType',
  // 手机
  Mobile: 'TThostFtdcMobileType',
  // 手续费率模板代码
  CommModelID: 'TThostFtdcInvestorIDType',
  // 保证金率模板代码
  MarginModelID: 'TThostFtdcInvestorIDType'
}

// 正在同步中的交易代码
structDict['CThostFtdcSyncingTradingCodeField'] = {
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType',
  // 交易编码类型
  ClientIDType: 'TThostFtdcClientIDTypeType'
}

// 正在同步中的投资者分组
structDict['CThostFtdcSyncingInvestorGroupField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者分组代码
  InvestorGroupID: 'TThostFtdcInvestorIDType',
  // 投资者分组名称
  InvestorGroupName: 'TThostFtdcInvestorGroupNameType'
}

// 正在同步中的交易账号
structDict['CThostFtdcSyncingTradingAccountField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 上次质押金额
  PreMortgage: 'TThostFtdcMoneyType',
  // 上次信用额度
  PreCredit: 'TThostFtdcMoneyType',
  // 上次存款额
  PreDeposit: 'TThostFtdcMoneyType',
  // 上次结算准备金
  PreBalance: 'TThostFtdcMoneyType',
  // 上次占用的保证金
  PreMargin: 'TThostFtdcMoneyType',
  // 利息基数
  InterestBase: 'TThostFtdcMoneyType',
  // 利息收入
  Interest: 'TThostFtdcMoneyType',
  // 入金金额
  Deposit: 'TThostFtdcMoneyType',
  // 出金金额
  Withdraw: 'TThostFtdcMoneyType',
  // 冻结的保证金
  FrozenMargin: 'TThostFtdcMoneyType',
  // 冻结的资金
  FrozenCash: 'TThostFtdcMoneyType',
  // 冻结的手续费
  FrozenCommission: 'TThostFtdcMoneyType',
  // 当前保证金总额
  CurrMargin: 'TThostFtdcMoneyType',
  // 资金差额
  CashIn: 'TThostFtdcMoneyType',
  // 手续费
  Commission: 'TThostFtdcMoneyType',
  // 平仓盈亏
  CloseProfit: 'TThostFtdcMoneyType',
  // 持仓盈亏
  PositionProfit: 'TThostFtdcMoneyType',
  // 期货结算准备金
  Balance: 'TThostFtdcMoneyType',
  // 可用资金
  Available: 'TThostFtdcMoneyType',
  // 可取资金
  WithdrawQuota: 'TThostFtdcMoneyType',
  // 基本准备金
  Reserve: 'TThostFtdcMoneyType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 信用额度
  Credit: 'TThostFtdcMoneyType',
  // 质押金额
  Mortgage: 'TThostFtdcMoneyType',
  // 交易所保证金
  ExchangeMargin: 'TThostFtdcMoneyType',
  // 投资者交割保证金
  DeliveryMargin: 'TThostFtdcMoneyType',
  // 交易所交割保证金
  ExchangeDeliveryMargin: 'TThostFtdcMoneyType',
  // 保底期货结算准备金
  ReserveBalance: 'TThostFtdcMoneyType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 上次货币质入金额
  PreFundMortgageIn: 'TThostFtdcMoneyType',
  // 上次货币质出金额
  PreFundMortgageOut: 'TThostFtdcMoneyType',
  // 货币质入金额
  FundMortgageIn: 'TThostFtdcMoneyType',
  // 货币质出金额
  FundMortgageOut: 'TThostFtdcMoneyType',
  // 货币质押余额
  FundMortgageAvailable: 'TThostFtdcMoneyType',
  // 可质押货币金额
  MortgageableFund: 'TThostFtdcMoneyType',
  // 特殊产品占用保证金
  SpecProductMargin: 'TThostFtdcMoneyType',
  // 特殊产品冻结保证金
  SpecProductFrozenMargin: 'TThostFtdcMoneyType',
  // 特殊产品手续费
  SpecProductCommission: 'TThostFtdcMoneyType',
  // 特殊产品冻结手续费
  SpecProductFrozenCommission: 'TThostFtdcMoneyType',
  // 特殊产品持仓盈亏
  SpecProductPositionProfit: 'TThostFtdcMoneyType',
  // 特殊产品平仓盈亏
  SpecProductCloseProfit: 'TThostFtdcMoneyType',
  // 根据持仓盈亏算法计算的特殊产品持仓盈亏
  SpecProductPositionProfitByAlg: 'TThostFtdcMoneyType',
  // 特殊产品交易所保证金
  SpecProductExchangeMargin: 'TThostFtdcMoneyType',
  // 延时换汇冻结金额
  FrozenSwap: 'TThostFtdcMoneyType',
  // 剩余换汇额度
  RemainSwap: 'TThostFtdcMoneyType'
}

// 正在同步中的投资者持仓
structDict['CThostFtdcSyncingInvestorPositionField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 持仓多空方向
  PosiDirection: 'TThostFtdcPosiDirectionType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 持仓日期
  PositionDate: 'TThostFtdcPositionDateType',
  // 上日持仓
  YdPosition: 'TThostFtdcVolumeType',
  // 今日持仓
  Position: 'TThostFtdcVolumeType',
  // 多头冻结
  LongFrozen: 'TThostFtdcVolumeType',
  // 空头冻结
  ShortFrozen: 'TThostFtdcVolumeType',
  // 开仓冻结金额
  LongFrozenAmount: 'TThostFtdcMoneyType',
  // 开仓冻结金额
  ShortFrozenAmount: 'TThostFtdcMoneyType',
  // 开仓量
  OpenVolume: 'TThostFtdcVolumeType',
  // 平仓量
  CloseVolume: 'TThostFtdcVolumeType',
  // 开仓金额
  OpenAmount: 'TThostFtdcMoneyType',
  // 平仓金额
  CloseAmount: 'TThostFtdcMoneyType',
  // 持仓成本
  PositionCost: 'TThostFtdcMoneyType',
  // 上次占用的保证金
  PreMargin: 'TThostFtdcMoneyType',
  // 占用的保证金
  UseMargin: 'TThostFtdcMoneyType',
  // 冻结的保证金
  FrozenMargin: 'TThostFtdcMoneyType',
  // 冻结的资金
  FrozenCash: 'TThostFtdcMoneyType',
  // 冻结的手续费
  FrozenCommission: 'TThostFtdcMoneyType',
  // 资金差额
  CashIn: 'TThostFtdcMoneyType',
  // 手续费
  Commission: 'TThostFtdcMoneyType',
  // 平仓盈亏
  CloseProfit: 'TThostFtdcMoneyType',
  // 持仓盈亏
  PositionProfit: 'TThostFtdcMoneyType',
  // 上次结算价
  PreSettlementPrice: 'TThostFtdcPriceType',
  // 本次结算价
  SettlementPrice: 'TThostFtdcPriceType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 开仓成本
  OpenCost: 'TThostFtdcMoneyType',
  // 交易所保证金
  ExchangeMargin: 'TThostFtdcMoneyType',
  // 组合成交形成的持仓
  CombPosition: 'TThostFtdcVolumeType',
  // 组合多头冻结
  CombLongFrozen: 'TThostFtdcVolumeType',
  // 组合空头冻结
  CombShortFrozen: 'TThostFtdcVolumeType',
  // 逐日盯市平仓盈亏
  CloseProfitByDate: 'TThostFtdcMoneyType',
  // 逐笔对冲平仓盈亏
  CloseProfitByTrade: 'TThostFtdcMoneyType',
  // 今日持仓
  TodayPosition: 'TThostFtdcVolumeType',
  // 保证金率
  MarginRateByMoney: 'TThostFtdcRatioType',
  // 保证金率(按手数)
  MarginRateByVolume: 'TThostFtdcRatioType',
  // 执行冻结
  StrikeFrozen: 'TThostFtdcVolumeType',
  // 执行冻结金额
  StrikeFrozenAmount: 'TThostFtdcMoneyType',
  // 放弃执行冻结
  AbandonFrozen: 'TThostFtdcVolumeType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 执行冻结的昨仓
  YdStrikeFrozen: 'TThostFtdcVolumeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 正在同步中的合约保证金率
structDict['CThostFtdcSyncingInstrumentMarginRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 多头保证金率
  LongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 多头保证金费
  LongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 空头保证金率
  ShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 空头保证金费
  ShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 是否相对交易所收取
  IsRelative: 'TThostFtdcBoolType'
}

// 正在同步中的合约手续费率
structDict['CThostFtdcSyncingInstrumentCommissionRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 开仓手续费率
  OpenRatioByMoney: 'TThostFtdcRatioType',
  // 开仓手续费
  OpenRatioByVolume: 'TThostFtdcRatioType',
  // 平仓手续费率
  CloseRatioByMoney: 'TThostFtdcRatioType',
  // 平仓手续费
  CloseRatioByVolume: 'TThostFtdcRatioType',
  // 平今手续费率
  CloseTodayRatioByMoney: 'TThostFtdcRatioType',
  // 平今手续费
  CloseTodayRatioByVolume: 'TThostFtdcRatioType'
}

// 正在同步中的合约交易权限
structDict['CThostFtdcSyncingInstrumentTradingRightField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易权限
  TradingRight: 'TThostFtdcTradingRightType'
}

// 查询报单
structDict['CThostFtdcQryOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 开始时间
  InsertTimeStart: 'TThostFtdcTimeType',
  // 结束时间
  InsertTimeEnd: 'TThostFtdcTimeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询成交
structDict['CThostFtdcQryTradeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 成交编号
  TradeID: 'TThostFtdcTradeIDType',
  // 开始时间
  TradeTimeStart: 'TThostFtdcTimeType',
  // 结束时间
  TradeTimeEnd: 'TThostFtdcTimeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询投资者持仓
structDict['CThostFtdcQryInvestorPositionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询资金账户
structDict['CThostFtdcQryTradingAccountField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 业务类型
  BizType: 'TThostFtdcBizTypeType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType'
}

// 查询投资者
structDict['CThostFtdcQryInvestorField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

// 查询交易编码
structDict['CThostFtdcQryTradingCodeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 交易编码类型
  ClientIDType: 'TThostFtdcClientIDTypeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询投资者组
structDict['CThostFtdcQryInvestorGroupField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType'
}

// 查询合约保证金率
structDict['CThostFtdcQryInstrumentMarginRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询手续费率
structDict['CThostFtdcQryInstrumentCommissionRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询合约交易权限
structDict['CThostFtdcQryInstrumentTradingRightField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 查询经纪公司
structDict['CThostFtdcQryBrokerField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType'
}

// 查询交易员
structDict['CThostFtdcQryTraderField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 查询管理用户功能权限
structDict['CThostFtdcQrySuperUserFunctionField'] = {
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 查询用户会话
structDict['CThostFtdcQryUserSessionField'] = {
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 查询经纪公司会员代码
structDict['CThostFtdcQryPartBrokerField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType'
}

// 查询前置状态
structDict['CThostFtdcQryFrontStatusField'] = {
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType'
}

// 查询交易所报单
structDict['CThostFtdcQryExchangeOrderField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 查询报单操作
structDict['CThostFtdcQryOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 查询交易所报单操作
structDict['CThostFtdcQryExchangeOrderActionField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 查询管理用户
structDict['CThostFtdcQrySuperUserField'] = {
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 查询交易所
structDict['CThostFtdcQryExchangeField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 查询产品
structDict['CThostFtdcQryProductField'] = {
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 产品类型
  ProductClass: 'TThostFtdcProductClassType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 查询合约
structDict['CThostFtdcQryInstrumentField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType'
}

// 查询行情
structDict['CThostFtdcQryDepthMarketDataField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 查询经纪公司用户
structDict['CThostFtdcQryBrokerUserField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 查询经纪公司用户权限
structDict['CThostFtdcQryBrokerUserFunctionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 查询交易员报盘机
structDict['CThostFtdcQryTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 查询出入金流水
structDict['CThostFtdcQrySyncDepositField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 出入金流水号
  DepositSeqNo: 'TThostFtdcDepositSeqNoType'
}

// 查询投资者结算结果
structDict['CThostFtdcQrySettlementInfoField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 查询交易所保证金率
structDict['CThostFtdcQryExchangeMarginRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 查询交易所调整保证金率
structDict['CThostFtdcQryExchangeMarginRateAdjustField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType'
}

// 查询汇率
structDict['CThostFtdcQryExchangeRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 源币种
  FromCurrencyID: 'TThostFtdcCurrencyIDType',
  // 目标币种
  ToCurrencyID: 'TThostFtdcCurrencyIDType'
}

// 查询货币质押流水
structDict['CThostFtdcQrySyncFundMortgageField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 货币质押流水号
  MortgageSeqNo: 'TThostFtdcDepositSeqNoType'
}

// 查询报单
structDict['CThostFtdcQryHisOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 开始时间
  InsertTimeStart: 'TThostFtdcTimeType',
  // 结束时间
  InsertTimeEnd: 'TThostFtdcTimeType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType'
}

// 当前期权合约最小保证金
structDict['CThostFtdcOptionInstrMiniMarginField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 单位（手）期权合约最小保证金
  MinMargin: 'TThostFtdcMoneyType',
  // 取值方式
  ValueMethod: 'TThostFtdcValueMethodType',
  // 是否跟随交易所收取
  IsRelative: 'TThostFtdcBoolType'
}

// 当前期权合约保证金调整系数
structDict['CThostFtdcOptionInstrMarginAdjustField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投机空头保证金调整系数
  SShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 投机空头保证金调整系数
  SShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 保值空头保证金调整系数
  HShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 保值空头保证金调整系数
  HShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 套利空头保证金调整系数
  AShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 套利空头保证金调整系数
  AShortMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 是否跟随交易所收取
  IsRelative: 'TThostFtdcBoolType',
  // 做市商空头保证金调整系数
  MShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 做市商空头保证金调整系数
  MShortMarginRatioByVolume: 'TThostFtdcMoneyType'
}

// 当前期权合约手续费的详细内容
structDict['CThostFtdcOptionInstrCommRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 开仓手续费率
  OpenRatioByMoney: 'TThostFtdcRatioType',
  // 开仓手续费
  OpenRatioByVolume: 'TThostFtdcRatioType',
  // 平仓手续费率
  CloseRatioByMoney: 'TThostFtdcRatioType',
  // 平仓手续费
  CloseRatioByVolume: 'TThostFtdcRatioType',
  // 平今手续费率
  CloseTodayRatioByMoney: 'TThostFtdcRatioType',
  // 平今手续费
  CloseTodayRatioByVolume: 'TThostFtdcRatioType',
  // 执行手续费率
  StrikeRatioByMoney: 'TThostFtdcRatioType',
  // 执行手续费
  StrikeRatioByVolume: 'TThostFtdcRatioType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 期权交易成本
structDict['CThostFtdcOptionInstrTradeCostField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 期权合约保证金不变部分
  FixedMargin: 'TThostFtdcMoneyType',
  // 期权合约最小保证金
  MiniMargin: 'TThostFtdcMoneyType',
  // 期权合约权利金
  Royalty: 'TThostFtdcMoneyType',
  // 交易所期权合约保证金不变部分
  ExchFixedMargin: 'TThostFtdcMoneyType',
  // 交易所期权合约最小保证金
  ExchMiniMargin: 'TThostFtdcMoneyType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 期权交易成本查询
structDict['CThostFtdcQryOptionInstrTradeCostField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 期权合约报价
  InputPrice: 'TThostFtdcPriceType',
  // 标的价格,填0则用昨结算价
  UnderlyingPrice: 'TThostFtdcPriceType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 期权手续费率查询
structDict['CThostFtdcQryOptionInstrCommRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 股指现货指数
structDict['CThostFtdcIndexPriceField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 指数现货收盘价
  ClosePrice: 'TThostFtdcPriceType'
}

// 输入的执行宣告
structDict['CThostFtdcInputExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 执行宣告引用
  ExecOrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 执行类型
  ActionType: 'TThostFtdcActionTypeType',
  // 保留头寸申请的持仓方向
  PosiDirection: 'TThostFtdcPosiDirectionType',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'TThostFtdcExecOrderPositionFlagType',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'TThostFtdcExecOrderCloseFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 输入执行宣告操作
structDict['CThostFtdcInputExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 执行宣告操作引用
  ExecOrderActionRef: 'TThostFtdcOrderActionRefType',
  // 执行宣告引用
  ExecOrderRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 执行宣告操作编号
  ExecOrderSysID: 'TThostFtdcExecOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 执行宣告
structDict['CThostFtdcExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 执行宣告引用
  ExecOrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 执行类型
  ActionType: 'TThostFtdcActionTypeType',
  // 保留头寸申请的持仓方向
  PosiDirection: 'TThostFtdcPosiDirectionType',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'TThostFtdcExecOrderPositionFlagType',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'TThostFtdcExecOrderCloseFlagType',
  // 本地执行宣告编号
  ExecOrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 执行宣告提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 执行宣告编号
  ExecOrderSysID: 'TThostFtdcExecOrderSysIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 执行结果
  ExecResult: 'TThostFtdcExecResultType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 操作用户代码
  ActiveUserID: 'TThostFtdcUserIDType',
  // 经纪公司报单编号
  BrokerExecOrderSeq: 'TThostFtdcSequenceNoType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 执行宣告操作
structDict['CThostFtdcExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 执行宣告操作引用
  ExecOrderActionRef: 'TThostFtdcOrderActionRefType',
  // 执行宣告引用
  ExecOrderRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 执行宣告操作编号
  ExecOrderSysID: 'TThostFtdcExecOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地执行宣告编号
  ExecOrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 执行类型
  ActionType: 'TThostFtdcActionTypeType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 执行宣告查询
structDict['CThostFtdcQryExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 执行宣告编号
  ExecOrderSysID: 'TThostFtdcExecOrderSysIDType',
  // 开始时间
  InsertTimeStart: 'TThostFtdcTimeType',
  // 结束时间
  InsertTimeEnd: 'TThostFtdcTimeType'
}

// 交易所执行宣告信息
structDict['CThostFtdcExchangeExecOrderField'] = {
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 执行类型
  ActionType: 'TThostFtdcActionTypeType',
  // 保留头寸申请的持仓方向
  PosiDirection: 'TThostFtdcPosiDirectionType',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'TThostFtdcExecOrderPositionFlagType',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'TThostFtdcExecOrderCloseFlagType',
  // 本地执行宣告编号
  ExecOrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 执行宣告提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 执行宣告编号
  ExecOrderSysID: 'TThostFtdcExecOrderSysIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 执行结果
  ExecResult: 'TThostFtdcExecResultType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所执行宣告查询
structDict['CThostFtdcQryExchangeExecOrderField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 执行宣告操作查询
structDict['CThostFtdcQryExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 交易所执行宣告操作
structDict['CThostFtdcExchangeExecOrderActionField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 执行宣告操作编号
  ExecOrderSysID: 'TThostFtdcExecOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地执行宣告编号
  ExecOrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 执行类型
  ActionType: 'TThostFtdcActionTypeType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所执行宣告操作查询
structDict['CThostFtdcQryExchangeExecOrderActionField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 错误执行宣告
structDict['CThostFtdcErrExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 执行宣告引用
  ExecOrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 执行类型
  ActionType: 'TThostFtdcActionTypeType',
  // 保留头寸申请的持仓方向
  PosiDirection: 'TThostFtdcPosiDirectionType',
  // 期权行权后是否保留期货头寸的标记,该字段已废弃
  ReservePositionFlag: 'TThostFtdcExecOrderPositionFlagType',
  // 期权行权后生成的头寸是否自动平仓
  CloseFlag: 'TThostFtdcExecOrderCloseFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 查询错误执行宣告
structDict['CThostFtdcQryErrExecOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

// 错误执行宣告操作
structDict['CThostFtdcErrExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 执行宣告操作引用
  ExecOrderActionRef: 'TThostFtdcOrderActionRefType',
  // 执行宣告引用
  ExecOrderRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 执行宣告操作编号
  ExecOrderSysID: 'TThostFtdcExecOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 查询错误执行宣告操作
structDict['CThostFtdcQryErrExecOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

// 投资者期权合约交易权限
structDict['CThostFtdcOptionInstrTradingRightField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 交易权限
  TradingRight: 'TThostFtdcTradingRightType'
}

// 查询期权合约交易权限
structDict['CThostFtdcQryOptionInstrTradingRightField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType'
}

// 输入的询价
structDict['CThostFtdcInputForQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 询价引用
  ForQuoteRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 询价
structDict['CThostFtdcForQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 询价引用
  ForQuoteRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 本地询价编号
  ForQuoteLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 询价状态
  ForQuoteStatus: 'TThostFtdcForQuoteStatusType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 操作用户代码
  ActiveUserID: 'TThostFtdcUserIDType',
  // 经纪公司询价编号
  BrokerForQutoSeq: 'TThostFtdcSequenceNoType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 询价查询
structDict['CThostFtdcQryForQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 开始时间
  InsertTimeStart: 'TThostFtdcTimeType',
  // 结束时间
  InsertTimeEnd: 'TThostFtdcTimeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 交易所询价信息
structDict['CThostFtdcExchangeForQuoteField'] = {
  // 本地询价编号
  ForQuoteLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 询价状态
  ForQuoteStatus: 'TThostFtdcForQuoteStatusType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所询价查询
structDict['CThostFtdcQryExchangeForQuoteField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 输入的报价
structDict['CThostFtdcInputQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报价引用
  QuoteRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 卖价格
  AskPrice: 'TThostFtdcPriceType',
  // 买价格
  BidPrice: 'TThostFtdcPriceType',
  // 卖数量
  AskVolume: 'TThostFtdcVolumeType',
  // 买数量
  BidVolume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 卖开平标志
  AskOffsetFlag: 'TThostFtdcOffsetFlagType',
  // 买开平标志
  BidOffsetFlag: 'TThostFtdcOffsetFlagType',
  // 卖投机套保标志
  AskHedgeFlag: 'TThostFtdcHedgeFlagType',
  // 买投机套保标志
  BidHedgeFlag: 'TThostFtdcHedgeFlagType',
  // 衍生卖报单引用
  AskOrderRef: 'TThostFtdcOrderRefType',
  // 衍生买报单引用
  BidOrderRef: 'TThostFtdcOrderRefType',
  // 应价编号
  ForQuoteSysID: 'TThostFtdcOrderSysIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 输入报价操作
structDict['CThostFtdcInputQuoteActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报价操作引用
  QuoteActionRef: 'TThostFtdcOrderActionRefType',
  // 报价引用
  QuoteRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报价操作编号
  QuoteSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 报价
structDict['CThostFtdcQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报价引用
  QuoteRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 卖价格
  AskPrice: 'TThostFtdcPriceType',
  // 买价格
  BidPrice: 'TThostFtdcPriceType',
  // 卖数量
  AskVolume: 'TThostFtdcVolumeType',
  // 买数量
  BidVolume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 卖开平标志
  AskOffsetFlag: 'TThostFtdcOffsetFlagType',
  // 买开平标志
  BidOffsetFlag: 'TThostFtdcOffsetFlagType',
  // 卖投机套保标志
  AskHedgeFlag: 'TThostFtdcHedgeFlagType',
  // 买投机套保标志
  BidHedgeFlag: 'TThostFtdcHedgeFlagType',
  // 本地报价编号
  QuoteLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 报价提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 报价提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 报价编号
  QuoteSysID: 'TThostFtdcOrderSysIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 报价状态
  QuoteStatus: 'TThostFtdcOrderStatusType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 卖方报单编号
  AskOrderSysID: 'TThostFtdcOrderSysIDType',
  // 买方报单编号
  BidOrderSysID: 'TThostFtdcOrderSysIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 操作用户代码
  ActiveUserID: 'TThostFtdcUserIDType',
  // 经纪公司报价编号
  BrokerQuoteSeq: 'TThostFtdcSequenceNoType',
  // 衍生卖报单引用
  AskOrderRef: 'TThostFtdcOrderRefType',
  // 衍生买报单引用
  BidOrderRef: 'TThostFtdcOrderRefType',
  // 应价编号
  ForQuoteSysID: 'TThostFtdcOrderSysIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 报价操作
structDict['CThostFtdcQuoteActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报价操作引用
  QuoteActionRef: 'TThostFtdcOrderActionRefType',
  // 报价引用
  QuoteRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报价操作编号
  QuoteSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报价编号
  QuoteLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 报价查询
structDict['CThostFtdcQryQuoteField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报价编号
  QuoteSysID: 'TThostFtdcOrderSysIDType',
  // 开始时间
  InsertTimeStart: 'TThostFtdcTimeType',
  // 结束时间
  InsertTimeEnd: 'TThostFtdcTimeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 交易所报价信息
structDict['CThostFtdcExchangeQuoteField'] = {
  // 卖价格
  AskPrice: 'TThostFtdcPriceType',
  // 买价格
  BidPrice: 'TThostFtdcPriceType',
  // 卖数量
  AskVolume: 'TThostFtdcVolumeType',
  // 买数量
  BidVolume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 卖开平标志
  AskOffsetFlag: 'TThostFtdcOffsetFlagType',
  // 买开平标志
  BidOffsetFlag: 'TThostFtdcOffsetFlagType',
  // 卖投机套保标志
  AskHedgeFlag: 'TThostFtdcHedgeFlagType',
  // 买投机套保标志
  BidHedgeFlag: 'TThostFtdcHedgeFlagType',
  // 本地报价编号
  QuoteLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 报价提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 报价提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 报价编号
  QuoteSysID: 'TThostFtdcOrderSysIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 报价状态
  QuoteStatus: 'TThostFtdcOrderStatusType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 卖方报单编号
  AskOrderSysID: 'TThostFtdcOrderSysIDType',
  // 买方报单编号
  BidOrderSysID: 'TThostFtdcOrderSysIDType',
  // 应价编号
  ForQuoteSysID: 'TThostFtdcOrderSysIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所报价查询
structDict['CThostFtdcQryExchangeQuoteField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 报价操作查询
structDict['CThostFtdcQryQuoteActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 交易所报价操作
structDict['CThostFtdcExchangeQuoteActionField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报价操作编号
  QuoteSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报价编号
  QuoteLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所报价操作查询
structDict['CThostFtdcQryExchangeQuoteActionField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 期权合约delta值
structDict['CThostFtdcOptionInstrDeltaField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // Delta值
  Delta: 'TThostFtdcRatioType'
}

// 发给做市商的询价请求
structDict['CThostFtdcForQuoteRspField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 询价编号
  ForQuoteSysID: 'TThostFtdcOrderSysIDType',
  // 询价时间
  ForQuoteTime: 'TThostFtdcTimeType',
  // 业务日期
  ActionDay: 'TThostFtdcDateType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 当前期权合约执行偏移值的详细内容
structDict['CThostFtdcStrikeOffsetField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 执行偏移值
  Offset: 'TThostFtdcMoneyType',
  // 执行偏移类型
  OffsetType: 'TThostFtdcStrikeOffsetTypeType'
}

// 期权执行偏移值查询
structDict['CThostFtdcQryStrikeOffsetField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 输入批量报单操作
structDict['CThostFtdcInputBatchOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报单操作引用
  OrderActionRef: 'TThostFtdcOrderActionRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 批量报单操作
structDict['CThostFtdcBatchOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报单操作引用
  OrderActionRef: 'TThostFtdcOrderActionRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 交易所批量报单操作
structDict['CThostFtdcExchangeBatchOrderActionField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 查询批量报单操作
structDict['CThostFtdcQryBatchOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 组合合约安全系数
structDict['CThostFtdcCombInstrumentGuardField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // No Description
  GuarantRatio: 'TThostFtdcRatioType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 组合合约安全系数查询
structDict['CThostFtdcQryCombInstrumentGuardField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 输入的申请组合
structDict['CThostFtdcInputCombActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 组合引用
  CombActionRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 组合指令方向
  CombDirection: 'TThostFtdcCombDirectionType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 申请组合
structDict['CThostFtdcCombActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 组合引用
  CombActionRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 组合指令方向
  CombDirection: 'TThostFtdcCombDirectionType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 本地申请组合编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 组合状态
  ActionStatus: 'TThostFtdcOrderActionStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 组合编号
  ComTradeID: 'TThostFtdcTradeIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 申请组合查询
structDict['CThostFtdcQryCombActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 交易所申请组合信息
structDict['CThostFtdcExchangeCombActionField'] = {
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 组合指令方向
  CombDirection: 'TThostFtdcCombDirectionType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 本地申请组合编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 组合状态
  ActionStatus: 'TThostFtdcOrderActionStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 组合编号
  ComTradeID: 'TThostFtdcTradeIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType'
}

// 交易所申请组合查询
structDict['CThostFtdcQryExchangeCombActionField'] = {
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 产品报价汇率
structDict['CThostFtdcProductExchRateField'] = {
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 报价币种类型
  QuoteCurrencyID: 'TThostFtdcCurrencyIDType',
  // 汇率
  ExchangeRate: 'TThostFtdcExchangeRateType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 产品报价汇率查询
structDict['CThostFtdcQryProductExchRateField'] = {
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 查询询价价差参数
structDict['CThostFtdcQryForQuoteParamField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 询价价差参数
structDict['CThostFtdcForQuoteParamField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 最新价
  LastPrice: 'TThostFtdcPriceType',
  // 价差
  PriceInterval: 'TThostFtdcPriceType'
}

// 当前做市商期权合约手续费的详细内容
structDict['CThostFtdcMMOptionInstrCommRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 开仓手续费率
  OpenRatioByMoney: 'TThostFtdcRatioType',
  // 开仓手续费
  OpenRatioByVolume: 'TThostFtdcRatioType',
  // 平仓手续费率
  CloseRatioByMoney: 'TThostFtdcRatioType',
  // 平仓手续费
  CloseRatioByVolume: 'TThostFtdcRatioType',
  // 平今手续费率
  CloseTodayRatioByMoney: 'TThostFtdcRatioType',
  // 平今手续费
  CloseTodayRatioByVolume: 'TThostFtdcRatioType',
  // 执行手续费率
  StrikeRatioByMoney: 'TThostFtdcRatioType',
  // 执行手续费
  StrikeRatioByVolume: 'TThostFtdcRatioType'
}

// 做市商期权手续费率查询
structDict['CThostFtdcQryMMOptionInstrCommRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 做市商合约手续费率
structDict['CThostFtdcMMInstrumentCommissionRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 开仓手续费率
  OpenRatioByMoney: 'TThostFtdcRatioType',
  // 开仓手续费
  OpenRatioByVolume: 'TThostFtdcRatioType',
  // 平仓手续费率
  CloseRatioByMoney: 'TThostFtdcRatioType',
  // 平仓手续费
  CloseRatioByVolume: 'TThostFtdcRatioType',
  // 平今手续费率
  CloseTodayRatioByMoney: 'TThostFtdcRatioType',
  // 平今手续费
  CloseTodayRatioByVolume: 'TThostFtdcRatioType'
}

// 查询做市商合约手续费率
structDict['CThostFtdcQryMMInstrumentCommissionRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 当前报单手续费的详细内容
structDict['CThostFtdcInstrumentOrderCommRateField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 报单手续费
  OrderCommByVolume: 'TThostFtdcRatioType',
  // 撤单手续费
  OrderActionCommByVolume: 'TThostFtdcRatioType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 报单手续费率查询
structDict['CThostFtdcQryInstrumentOrderCommRateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 交易参数
structDict['CThostFtdcTradeParamField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 参数代码
  TradeParamID: 'TThostFtdcTradeParamIDType',
  // 参数代码值
  TradeParamValue: 'TThostFtdcSettlementParamValueType',
  // 备注
  Memo: 'TThostFtdcMemoType'
}

// 合约保证金率调整
structDict['CThostFtdcInstrumentMarginRateULField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 多头保证金率
  LongMarginRatioByMoney: 'TThostFtdcRatioType',
  // 多头保证金费
  LongMarginRatioByVolume: 'TThostFtdcMoneyType',
  // 空头保证金率
  ShortMarginRatioByMoney: 'TThostFtdcRatioType',
  // 空头保证金费
  ShortMarginRatioByVolume: 'TThostFtdcMoneyType'
}

// 期货持仓限制参数
structDict['CThostFtdcFutureLimitPosiParamField'] = {
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 当日投机开仓数量限制
  SpecOpenVolume: 'TThostFtdcVolumeType',
  // 当日套利开仓数量限制
  ArbiOpenVolume: 'TThostFtdcVolumeType',
  // 当日投机+套利开仓数量限制
  OpenVolume: 'TThostFtdcVolumeType'
}

// 禁止登录IP
structDict['CThostFtdcLoginForbiddenIPField'] = {
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType'
}

// IP列表
structDict['CThostFtdcIPListField'] = {
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // 是否白名单
  IsWhite: 'TThostFtdcBoolType'
}

// 输入的期权自对冲
structDict['CThostFtdcInputOptionSelfCloseField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 期权自对冲引用
  OptionSelfCloseRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 期权行权的头寸是否自对冲
  OptSelfCloseFlag: 'TThostFtdcOptSelfCloseFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 输入期权自对冲操作
structDict['CThostFtdcInputOptionSelfCloseActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 期权自对冲操作引用
  OptionSelfCloseActionRef: 'TThostFtdcOrderActionRefType',
  // 期权自对冲引用
  OptionSelfCloseRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 期权自对冲操作编号
  OptionSelfCloseSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 期权自对冲
structDict['CThostFtdcOptionSelfCloseField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 期权自对冲引用
  OptionSelfCloseRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 期权行权的头寸是否自对冲
  OptSelfCloseFlag: 'TThostFtdcOptSelfCloseFlagType',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 期权自对冲提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 期权自对冲编号
  OptionSelfCloseSysID: 'TThostFtdcOrderSysIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 自对冲结果
  ExecResult: 'TThostFtdcExecResultType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 操作用户代码
  ActiveUserID: 'TThostFtdcUserIDType',
  // 经纪公司报单编号
  BrokerOptionSelfCloseSeq: 'TThostFtdcSequenceNoType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 期权自对冲操作
structDict['CThostFtdcOptionSelfCloseActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 期权自对冲操作引用
  OptionSelfCloseActionRef: 'TThostFtdcOrderActionRefType',
  // 期权自对冲引用
  OptionSelfCloseRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 期权自对冲操作编号
  OptionSelfCloseSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 期权自对冲查询
structDict['CThostFtdcQryOptionSelfCloseField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 期权自对冲编号
  OptionSelfCloseSysID: 'TThostFtdcOrderSysIDType',
  // 开始时间
  InsertTimeStart: 'TThostFtdcTimeType',
  // 结束时间
  InsertTimeEnd: 'TThostFtdcTimeType'
}

// 交易所期权自对冲信息
structDict['CThostFtdcExchangeOptionSelfCloseField'] = {
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 期权行权的头寸是否自对冲
  OptSelfCloseFlag: 'TThostFtdcOptSelfCloseFlagType',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 期权自对冲提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 期权自对冲编号
  OptionSelfCloseSysID: 'TThostFtdcOrderSysIDType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 插入时间
  InsertTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 自对冲结果
  ExecResult: 'TThostFtdcExecResultType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 期权自对冲操作查询
structDict['CThostFtdcQryOptionSelfCloseActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 交易所期权自对冲操作
structDict['CThostFtdcExchangeOptionSelfCloseActionField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 期权自对冲操作编号
  OptionSelfCloseSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地期权自对冲编号
  OptionSelfCloseLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 延时换汇同步
structDict['CThostFtdcSyncDelaySwapField'] = {
  // 换汇流水号
  DelaySwapSeqNo: 'TThostFtdcDepositSeqNoType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 源币种
  FromCurrencyID: 'TThostFtdcCurrencyIDType',
  // 源金额
  FromAmount: 'TThostFtdcMoneyType',
  // 源换汇冻结金额(可用冻结)
  FromFrozenSwap: 'TThostFtdcMoneyType',
  // 源剩余换汇额度(可提冻结)
  FromRemainSwap: 'TThostFtdcMoneyType',
  // 目标币种
  ToCurrencyID: 'TThostFtdcCurrencyIDType',
  // 目标金额
  ToAmount: 'TThostFtdcMoneyType'
}

// 查询延时换汇同步
structDict['CThostFtdcQrySyncDelaySwapField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 延时换汇流水号
  DelaySwapSeqNo: 'TThostFtdcDepositSeqNoType'
}

// 投资单元
structDict['CThostFtdcInvestUnitField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 投资者单元名称
  InvestorUnitName: 'TThostFtdcPartyNameType',
  // 投资者分组代码
  InvestorGroupID: 'TThostFtdcInvestorIDType',
  // 手续费率模板代码
  CommModelID: 'TThostFtdcInvestorIDType',
  // 保证金率模板代码
  MarginModelID: 'TThostFtdcInvestorIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 查询投资单元
structDict['CThostFtdcQryInvestUnitField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 二级代理商资金校验模式
structDict['CThostFtdcSecAgentCheckModeField'] = {
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 币种
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 境外中介机构资金帐号
  BrokerSecAgentID: 'TThostFtdcAccountIDType',
  // 是否需要校验自己的资金账户
  CheckSelfAccount: 'TThostFtdcBoolType'
}

// 市场行情
structDict['CThostFtdcMarketDataField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 最新价
  LastPrice: 'TThostFtdcPriceType',
  // 上次结算价
  PreSettlementPrice: 'TThostFtdcPriceType',
  // 昨收盘
  PreClosePrice: 'TThostFtdcPriceType',
  // 昨持仓量
  PreOpenInterest: 'TThostFtdcLargeVolumeType',
  // 今开盘
  OpenPrice: 'TThostFtdcPriceType',
  // 最高价
  HighestPrice: 'TThostFtdcPriceType',
  // 最低价
  LowestPrice: 'TThostFtdcPriceType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 成交金额
  Turnover: 'TThostFtdcMoneyType',
  // 持仓量
  OpenInterest: 'TThostFtdcLargeVolumeType',
  // 今收盘
  ClosePrice: 'TThostFtdcPriceType',
  // 本次结算价
  SettlementPrice: 'TThostFtdcPriceType',
  // 涨停板价
  UpperLimitPrice: 'TThostFtdcPriceType',
  // 跌停板价
  LowerLimitPrice: 'TThostFtdcPriceType',
  // 昨虚实度
  PreDelta: 'TThostFtdcRatioType',
  // 今虚实度
  CurrDelta: 'TThostFtdcRatioType',
  // 最后修改时间
  UpdateTime: 'TThostFtdcTimeType',
  // 最后修改毫秒
  UpdateMillisec: 'TThostFtdcMillisecType',
  // 业务日期
  ActionDay: 'TThostFtdcDateType'
}

// 行情基础属性
structDict['CThostFtdcMarketDataBaseField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 上次结算价
  PreSettlementPrice: 'TThostFtdcPriceType',
  // 昨收盘
  PreClosePrice: 'TThostFtdcPriceType',
  // 昨持仓量
  PreOpenInterest: 'TThostFtdcLargeVolumeType',
  // 昨虚实度
  PreDelta: 'TThostFtdcRatioType'
}

// 行情静态属性
structDict['CThostFtdcMarketDataStaticField'] = {
  // 今开盘
  OpenPrice: 'TThostFtdcPriceType',
  // 最高价
  HighestPrice: 'TThostFtdcPriceType',
  // 最低价
  LowestPrice: 'TThostFtdcPriceType',
  // 今收盘
  ClosePrice: 'TThostFtdcPriceType',
  // 涨停板价
  UpperLimitPrice: 'TThostFtdcPriceType',
  // 跌停板价
  LowerLimitPrice: 'TThostFtdcPriceType',
  // 本次结算价
  SettlementPrice: 'TThostFtdcPriceType',
  // 今虚实度
  CurrDelta: 'TThostFtdcRatioType'
}

// 行情最新成交属性
structDict['CThostFtdcMarketDataLastMatchField'] = {
  // 最新价
  LastPrice: 'TThostFtdcPriceType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 成交金额
  Turnover: 'TThostFtdcMoneyType',
  // 持仓量
  OpenInterest: 'TThostFtdcLargeVolumeType'
}

// 行情最优价属性
structDict['CThostFtdcMarketDataBestPriceField'] = {
  // 申买价一
  BidPrice1: 'TThostFtdcPriceType',
  // 申买量一
  BidVolume1: 'TThostFtdcVolumeType',
  // 申卖价一
  AskPrice1: 'TThostFtdcPriceType',
  // 申卖量一
  AskVolume1: 'TThostFtdcVolumeType'
}

// 行情申买二、三属性
structDict['CThostFtdcMarketDataBid23Field'] = {
  // 申买价二
  BidPrice2: 'TThostFtdcPriceType',
  // 申买量二
  BidVolume2: 'TThostFtdcVolumeType',
  // 申买价三
  BidPrice3: 'TThostFtdcPriceType',
  // 申买量三
  BidVolume3: 'TThostFtdcVolumeType'
}

// 行情申卖二、三属性
structDict['CThostFtdcMarketDataAsk23Field'] = {
  // 申卖价二
  AskPrice2: 'TThostFtdcPriceType',
  // 申卖量二
  AskVolume2: 'TThostFtdcVolumeType',
  // 申卖价三
  AskPrice3: 'TThostFtdcPriceType',
  // 申卖量三
  AskVolume3: 'TThostFtdcVolumeType'
}

// 行情申买四、五属性
structDict['CThostFtdcMarketDataBid45Field'] = {
  // 申买价四
  BidPrice4: 'TThostFtdcPriceType',
  // 申买量四
  BidVolume4: 'TThostFtdcVolumeType',
  // 申买价五
  BidPrice5: 'TThostFtdcPriceType',
  // 申买量五
  BidVolume5: 'TThostFtdcVolumeType'
}

// 行情申卖四、五属性
structDict['CThostFtdcMarketDataAsk45Field'] = {
  // 申卖价四
  AskPrice4: 'TThostFtdcPriceType',
  // 申卖量四
  AskVolume4: 'TThostFtdcVolumeType',
  // 申卖价五
  AskPrice5: 'TThostFtdcPriceType',
  // 申卖量五
  AskVolume5: 'TThostFtdcVolumeType'
}

// 行情更新时间属性
structDict['CThostFtdcMarketDataUpdateTimeField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 最后修改时间
  UpdateTime: 'TThostFtdcTimeType',
  // 最后修改毫秒
  UpdateMillisec: 'TThostFtdcMillisecType',
  // 业务日期
  ActionDay: 'TThostFtdcDateType'
}

// 行情交易所代码属性
structDict['CThostFtdcMarketDataExchangeField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 指定的合约
structDict['CThostFtdcSpecificInstrumentField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 合约状态
structDict['CThostFtdcInstrumentStatusField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 结算组代码
  SettlementGroupID: 'TThostFtdcSettlementGroupIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 合约交易状态
  InstrumentStatus: 'TThostFtdcInstrumentStatusType',
  // 交易阶段编号
  TradingSegmentSN: 'TThostFtdcTradingSegmentSNType',
  // 进入本状态时间
  EnterTime: 'TThostFtdcTimeType',
  // 进入本状态原因
  EnterReason: 'TThostFtdcInstStatusEnterReasonType'
}

// 查询合约状态
structDict['CThostFtdcQryInstrumentStatusField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType'
}

// 投资者账户
structDict['CThostFtdcInvestorAccountField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 浮动盈亏算法
structDict['CThostFtdcPositionProfitAlgorithmField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 盈亏算法
  Algorithm: 'TThostFtdcAlgorithmType',
  // 备注
  Memo: 'TThostFtdcMemoType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 会员资金折扣
structDict['CThostFtdcDiscountField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 资金折扣比例
  Discount: 'TThostFtdcRatioType'
}

// 查询转帐银行
structDict['CThostFtdcQryTransferBankField'] = {
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分中心代码
  BankBrchID: 'TThostFtdcBankBrchIDType'
}

// 转帐银行
structDict['CThostFtdcTransferBankField'] = {
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分中心代码
  BankBrchID: 'TThostFtdcBankBrchIDType',
  // 银行名称
  BankName: 'TThostFtdcBankNameType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType'
}

// 查询投资者持仓明细
structDict['CThostFtdcQryInvestorPositionDetailField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 投资者持仓明细
structDict['CThostFtdcInvestorPositionDetailField'] = {
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 买卖
  Direction: 'TThostFtdcDirectionType',
  // 开仓日期
  OpenDate: 'TThostFtdcDateType',
  // 成交编号
  TradeID: 'TThostFtdcTradeIDType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 开仓价
  OpenPrice: 'TThostFtdcPriceType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 成交类型
  TradeType: 'TThostFtdcTradeTypeType',
  // 组合合约代码
  CombInstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 逐日盯市平仓盈亏
  CloseProfitByDate: 'TThostFtdcMoneyType',
  // 逐笔对冲平仓盈亏
  CloseProfitByTrade: 'TThostFtdcMoneyType',
  // 逐日盯市持仓盈亏
  PositionProfitByDate: 'TThostFtdcMoneyType',
  // 逐笔对冲持仓盈亏
  PositionProfitByTrade: 'TThostFtdcMoneyType',
  // 投资者保证金
  Margin: 'TThostFtdcMoneyType',
  // 交易所保证金
  ExchMargin: 'TThostFtdcMoneyType',
  // 保证金率
  MarginRateByMoney: 'TThostFtdcRatioType',
  // 保证金率(按手数)
  MarginRateByVolume: 'TThostFtdcRatioType',
  // 昨结算价
  LastSettlementPrice: 'TThostFtdcPriceType',
  // 结算价
  SettlementPrice: 'TThostFtdcPriceType',
  // 平仓量
  CloseVolume: 'TThostFtdcVolumeType',
  // 平仓金额
  CloseAmount: 'TThostFtdcMoneyType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 资金账户口令域
structDict['CThostFtdcTradingAccountPasswordField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 密码
  Password: 'TThostFtdcPasswordType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 交易所行情报盘机
structDict['CThostFtdcMDTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所交易员连接状态
  TraderConnectStatus: 'TThostFtdcTraderConnectStatusType',
  // 发出连接请求的日期
  ConnectRequestDate: 'TThostFtdcDateType',
  // 发出连接请求的时间
  ConnectRequestTime: 'TThostFtdcTimeType',
  // 上次报告日期
  LastReportDate: 'TThostFtdcDateType',
  // 上次报告时间
  LastReportTime: 'TThostFtdcTimeType',
  // 完成连接日期
  ConnectDate: 'TThostFtdcDateType',
  // 完成连接时间
  ConnectTime: 'TThostFtdcTimeType',
  // 启动日期
  StartDate: 'TThostFtdcDateType',
  // 启动时间
  StartTime: 'TThostFtdcTimeType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 本席位最大成交编号
  MaxTradeID: 'TThostFtdcTradeIDType',
  // 本席位最大报单备拷
  MaxOrderMessageReference: 'TThostFtdcReturnCodeType'
}

// 查询行情报盘机
structDict['CThostFtdcQryMDTraderOfferField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType'
}

// 查询客户通知
structDict['CThostFtdcQryNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType'
}

// 客户通知
structDict['CThostFtdcNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 消息正文
  Content: 'TThostFtdcContentType',
  // 经纪公司通知内容序列号
  SequenceLabel: 'TThostFtdcSequenceLabelType'
}

// 用户权限
structDict['CThostFtdcUserRightField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 客户权限类型
  UserRightType: 'TThostFtdcUserRightTypeType',
  // 是否禁止
  IsForbidden: 'TThostFtdcBoolType'
}

// 查询结算信息确认域
structDict['CThostFtdcQrySettlementInfoConfirmField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 装载结算信息
structDict['CThostFtdcLoadSettlementInfoField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType'
}

// 经纪公司可提资金算法表
structDict['CThostFtdcBrokerWithdrawAlgorithmField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 可提资金算法
  WithdrawAlgorithm: 'TThostFtdcAlgorithmType',
  // 资金使用率
  UsingRatio: 'TThostFtdcRatioType',
  // 可提是否包含平仓盈利
  IncludeCloseProfit: 'TThostFtdcIncludeCloseProfitType',
  // 本日无仓且无成交客户是否受可提比例限制
  AllWithoutTrade: 'TThostFtdcAllWithoutTradeType',
  // 可用是否包含平仓盈利
  AvailIncludeCloseProfit: 'TThostFtdcIncludeCloseProfitType',
  // 是否启用用户事件
  IsBrokerUserEvent: 'TThostFtdcBoolType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 货币质押比率
  FundMortgageRatio: 'TThostFtdcRatioType',
  // 权益算法
  BalanceAlgorithm: 'TThostFtdcBalanceAlgorithmType'
}

// 资金账户口令变更域
structDict['CThostFtdcTradingAccountPasswordUpdateV1Field'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 原来的口令
  OldPassword: 'TThostFtdcPasswordType',
  // 新的口令
  NewPassword: 'TThostFtdcPasswordType'
}

// 资金账户口令变更域
structDict['CThostFtdcTradingAccountPasswordUpdateField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 原来的口令
  OldPassword: 'TThostFtdcPasswordType',
  // 新的口令
  NewPassword: 'TThostFtdcPasswordType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 查询组合合约分腿
structDict['CThostFtdcQryCombinationLegField'] = {
  // 组合合约代码
  CombInstrumentID: 'TThostFtdcInstrumentIDType',
  // 单腿编号
  LegID: 'TThostFtdcLegIDType',
  // 单腿合约代码
  LegInstrumentID: 'TThostFtdcInstrumentIDType'
}

// 查询组合合约分腿
structDict['CThostFtdcQrySyncStatusField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType'
}

// 组合交易合约的单腿
structDict['CThostFtdcCombinationLegField'] = {
  // 组合合约代码
  CombInstrumentID: 'TThostFtdcInstrumentIDType',
  // 单腿编号
  LegID: 'TThostFtdcLegIDType',
  // 单腿合约代码
  LegInstrumentID: 'TThostFtdcInstrumentIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 单腿乘数
  LegMultiple: 'TThostFtdcLegMultipleType',
  // 派生层数
  ImplyLevel: 'TThostFtdcImplyLevelType'
}

// 数据同步状态
structDict['CThostFtdcSyncStatusField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 数据同步状态
  DataSyncStatus: 'TThostFtdcDataSyncStatusType'
}

// 查询联系人
structDict['CThostFtdcQryLinkManField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

// 联系人
structDict['CThostFtdcLinkManField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 联系人类型
  PersonType: 'TThostFtdcPersonTypeType',
  // 证件类型
  IdentifiedCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 名称
  PersonName: 'TThostFtdcPartyNameType',
  // 联系电话
  Telephone: 'TThostFtdcTelephoneType',
  // 通讯地址
  Address: 'TThostFtdcAddressType',
  // 邮政编码
  ZipCode: 'TThostFtdcZipCodeType',
  // 优先级
  Priority: 'TThostFtdcPriorityType',
  // 开户邮政编码
  UOAZipCode: 'TThostFtdcUOAZipCodeType',
  // 全称
  PersonFullName: 'TThostFtdcInvestorFullNameType'
}

// 查询经纪公司用户事件
structDict['CThostFtdcQryBrokerUserEventField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 用户事件类型
  UserEventType: 'TThostFtdcUserEventTypeType'
}

// 查询经纪公司用户事件
structDict['CThostFtdcBrokerUserEventField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 用户事件类型
  UserEventType: 'TThostFtdcUserEventTypeType',
  // 用户事件序号
  EventSequenceNo: 'TThostFtdcSequenceNoType',
  // 事件发生日期
  EventDate: 'TThostFtdcDateType',
  // 事件发生时间
  EventTime: 'TThostFtdcTimeType',
  // 用户事件信息
  UserEventInfo: 'TThostFtdcUserEventInfoType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 查询签约银行请求
structDict['CThostFtdcQryContractBankField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分中心代码
  BankBrchID: 'TThostFtdcBankBrchIDType'
}

// 查询签约银行响应
structDict['CThostFtdcContractBankField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分中心代码
  BankBrchID: 'TThostFtdcBankBrchIDType',
  // 银行名称
  BankName: 'TThostFtdcBankNameType'
}

// 投资者组合持仓明细
structDict['CThostFtdcInvestorPositionCombineDetailField'] = {
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 开仓日期
  OpenDate: 'TThostFtdcDateType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 组合编号
  ComTradeID: 'TThostFtdcTradeIDType',
  // 撮合编号
  TradeID: 'TThostFtdcTradeIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 买卖
  Direction: 'TThostFtdcDirectionType',
  // 持仓量
  TotalAmt: 'TThostFtdcVolumeType',
  // 投资者保证金
  Margin: 'TThostFtdcMoneyType',
  // 交易所保证金
  ExchMargin: 'TThostFtdcMoneyType',
  // 保证金率
  MarginRateByMoney: 'TThostFtdcRatioType',
  // 保证金率(按手数)
  MarginRateByVolume: 'TThostFtdcRatioType',
  // 单腿编号
  LegID: 'TThostFtdcLegIDType',
  // 单腿乘数
  LegMultiple: 'TThostFtdcLegMultipleType',
  // 组合持仓合约编码
  CombInstrumentID: 'TThostFtdcInstrumentIDType',
  // 成交组号
  TradeGroupID: 'TThostFtdcTradeGroupIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 预埋单
structDict['CThostFtdcParkedOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 报单价格条件
  OrderPriceType: 'TThostFtdcOrderPriceTypeType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 组合开平标志
  CombOffsetFlag: 'TThostFtdcCombOffsetFlagType',
  // 组合投机套保标志
  CombHedgeFlag: 'TThostFtdcCombHedgeFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量
  VolumeTotalOriginal: 'TThostFtdcVolumeType',
  // 有效期类型
  TimeCondition: 'TThostFtdcTimeConditionType',
  // GTD日期
  GTDDate: 'TThostFtdcDateType',
  // 成交量类型
  VolumeCondition: 'TThostFtdcVolumeConditionType',
  // 最小成交量
  MinVolume: 'TThostFtdcVolumeType',
  // 触发条件
  ContingentCondition: 'TThostFtdcContingentConditionType',
  // 止损价
  StopPrice: 'TThostFtdcPriceType',
  // 强平原因
  ForceCloseReason: 'TThostFtdcForceCloseReasonType',
  // 自动挂起标志
  IsAutoSuspend: 'TThostFtdcBoolType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 用户强评标志
  UserForceClose: 'TThostFtdcBoolType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 预埋报单编号
  ParkedOrderID: 'TThostFtdcParkedOrderIDType',
  // 用户类型
  UserType: 'TThostFtdcUserTypeType',
  // 预埋单状态
  Status: 'TThostFtdcParkedOrderStatusType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 互换单标志
  IsSwapOrder: 'TThostFtdcBoolType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 输入预埋单操作
structDict['CThostFtdcParkedOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报单操作引用
  OrderActionRef: 'TThostFtdcOrderActionRefType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量变化
  VolumeChange: 'TThostFtdcVolumeType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 预埋撤单单编号
  ParkedOrderActionID: 'TThostFtdcParkedOrderActionIDType',
  // 用户类型
  UserType: 'TThostFtdcUserTypeType',
  // 预埋撤单状态
  Status: 'TThostFtdcParkedOrderStatusType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 查询预埋单
structDict['CThostFtdcQryParkedOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询预埋撤单
structDict['CThostFtdcQryParkedOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 删除预埋单
structDict['CThostFtdcRemoveParkedOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 预埋报单编号
  ParkedOrderID: 'TThostFtdcParkedOrderIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 删除预埋撤单
structDict['CThostFtdcRemoveParkedOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 预埋撤单编号
  ParkedOrderActionID: 'TThostFtdcParkedOrderActionIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 经纪公司可提资金算法表
structDict['CThostFtdcInvestorWithdrawAlgorithmField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 可提资金比例
  UsingRatio: 'TThostFtdcRatioType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 货币质押比率
  FundMortgageRatio: 'TThostFtdcRatioType'
}

// 查询组合持仓明细
structDict['CThostFtdcQryInvestorPositionCombineDetailField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 组合持仓合约编码
  CombInstrumentID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 成交均价
structDict['CThostFtdcMarketDataAveragePriceField'] = {
  // 当日均价
  AveragePrice: 'TThostFtdcPriceType'
}

// 校验投资者密码
structDict['CThostFtdcVerifyInvestorPasswordField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 密码
  Password: 'TThostFtdcPasswordType'
}

// 用户IP
structDict['CThostFtdcUserIPField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // IP地址掩码
  IPMask: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 用户事件通知信息
structDict['CThostFtdcTradingNoticeInfoField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 发送时间
  SendTime: 'TThostFtdcTimeType',
  // 消息正文
  FieldContent: 'TThostFtdcContentType',
  // 序列系列号
  SequenceSeries: 'TThostFtdcSequenceSeriesType',
  // 序列号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 用户事件通知
structDict['CThostFtdcTradingNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者范围
  InvestorRange: 'TThostFtdcInvestorRangeType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 序列系列号
  SequenceSeries: 'TThostFtdcSequenceSeriesType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 发送时间
  SendTime: 'TThostFtdcTimeType',
  // 序列号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 消息正文
  FieldContent: 'TThostFtdcContentType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询交易事件通知
structDict['CThostFtdcQryTradingNoticeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询错误报单
structDict['CThostFtdcQryErrOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

// 错误报单
structDict['CThostFtdcErrOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 报单价格条件
  OrderPriceType: 'TThostFtdcOrderPriceTypeType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 组合开平标志
  CombOffsetFlag: 'TThostFtdcCombOffsetFlagType',
  // 组合投机套保标志
  CombHedgeFlag: 'TThostFtdcCombHedgeFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量
  VolumeTotalOriginal: 'TThostFtdcVolumeType',
  // 有效期类型
  TimeCondition: 'TThostFtdcTimeConditionType',
  // GTD日期
  GTDDate: 'TThostFtdcDateType',
  // 成交量类型
  VolumeCondition: 'TThostFtdcVolumeConditionType',
  // 最小成交量
  MinVolume: 'TThostFtdcVolumeType',
  // 触发条件
  ContingentCondition: 'TThostFtdcContingentConditionType',
  // 止损价
  StopPrice: 'TThostFtdcPriceType',
  // 强平原因
  ForceCloseReason: 'TThostFtdcForceCloseReasonType',
  // 自动挂起标志
  IsAutoSuspend: 'TThostFtdcBoolType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 用户强评标志
  UserForceClose: 'TThostFtdcBoolType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 互换单标志
  IsSwapOrder: 'TThostFtdcBoolType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 交易编码
  ClientID: 'TThostFtdcClientIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 查询错误报单操作
structDict['CThostFtdcErrorConditionalOrderField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 报单价格条件
  OrderPriceType: 'TThostFtdcOrderPriceTypeType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 组合开平标志
  CombOffsetFlag: 'TThostFtdcCombOffsetFlagType',
  // 组合投机套保标志
  CombHedgeFlag: 'TThostFtdcCombHedgeFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量
  VolumeTotalOriginal: 'TThostFtdcVolumeType',
  // 有效期类型
  TimeCondition: 'TThostFtdcTimeConditionType',
  // GTD日期
  GTDDate: 'TThostFtdcDateType',
  // 成交量类型
  VolumeCondition: 'TThostFtdcVolumeConditionType',
  // 最小成交量
  MinVolume: 'TThostFtdcVolumeType',
  // 触发条件
  ContingentCondition: 'TThostFtdcContingentConditionType',
  // 止损价
  StopPrice: 'TThostFtdcPriceType',
  // 强平原因
  ForceCloseReason: 'TThostFtdcForceCloseReasonType',
  // 自动挂起标志
  IsAutoSuspend: 'TThostFtdcBoolType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 合约在交易所的代码
  ExchangeInstID: 'TThostFtdcExchangeInstIDType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 报单提交状态
  OrderSubmitStatus: 'TThostFtdcOrderSubmitStatusType',
  // 报单提示序号
  NotifySequence: 'TThostFtdcSequenceNoType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 报单来源
  OrderSource: 'TThostFtdcOrderSourceType',
  // 报单状态
  OrderStatus: 'TThostFtdcOrderStatusType',
  // 报单类型
  OrderType: 'TThostFtdcOrderTypeType',
  // 今成交数量
  VolumeTraded: 'TThostFtdcVolumeType',
  // 剩余数量
  VolumeTotal: 'TThostFtdcVolumeType',
  // 报单日期
  InsertDate: 'TThostFtdcDateType',
  // 委托时间
  InsertTime: 'TThostFtdcTimeType',
  // 激活时间
  ActiveTime: 'TThostFtdcTimeType',
  // 挂起时间
  SuspendTime: 'TThostFtdcTimeType',
  // 最后修改时间
  UpdateTime: 'TThostFtdcTimeType',
  // 撤销时间
  CancelTime: 'TThostFtdcTimeType',
  // 最后修改交易所交易员代码
  ActiveTraderID: 'TThostFtdcTraderIDType',
  // 结算会员编号
  ClearingPartID: 'TThostFtdcParticipantIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 用户端产品信息
  UserProductInfo: 'TThostFtdcProductInfoType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 用户强评标志
  UserForceClose: 'TThostFtdcBoolType',
  // 操作用户代码
  ActiveUserID: 'TThostFtdcUserIDType',
  // 经纪公司报单编号
  BrokerOrderSeq: 'TThostFtdcSequenceNoType',
  // 相关报单
  RelativeOrderSysID: 'TThostFtdcOrderSysIDType',
  // 郑商所成交数量
  ZCETotalTradedVolume: 'TThostFtdcVolumeType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 互换单标志
  IsSwapOrder: 'TThostFtdcBoolType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // 资金账号
  AccountID: 'TThostFtdcAccountIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType'
}

// 查询错误报单操作
structDict['CThostFtdcQryErrOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

// 错误报单操作
structDict['CThostFtdcErrOrderActionField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 报单操作引用
  OrderActionRef: 'TThostFtdcOrderActionRefType',
  // 报单引用
  OrderRef: 'TThostFtdcOrderRefType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 前置编号
  FrontID: 'TThostFtdcFrontIDType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 报单编号
  OrderSysID: 'TThostFtdcOrderSysIDType',
  // 操作标志
  ActionFlag: 'TThostFtdcActionFlagType',
  // 价格
  LimitPrice: 'TThostFtdcPriceType',
  // 数量变化
  VolumeChange: 'TThostFtdcVolumeType',
  // 操作日期
  ActionDate: 'TThostFtdcDateType',
  // 操作时间
  ActionTime: 'TThostFtdcTimeType',
  // 交易所交易员代码
  TraderID: 'TThostFtdcTraderIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 本地报单编号
  OrderLocalID: 'TThostFtdcOrderLocalIDType',
  // 操作本地编号
  ActionLocalID: 'TThostFtdcOrderLocalIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 客户代码
  ClientID: 'TThostFtdcClientIDType',
  // 业务单元
  BusinessUnit: 'TThostFtdcBusinessUnitType',
  // 报单操作状态
  OrderActionStatus: 'TThostFtdcOrderActionStatusType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 状态信息
  StatusMsg: 'TThostFtdcErrorMsgType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 营业部编号
  BranchID: 'TThostFtdcBranchIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType',
  // Mac地址
  MacAddress: 'TThostFtdcMacAddressType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 查询交易所状态
structDict['CThostFtdcQryExchangeSequenceField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 交易所状态
structDict['CThostFtdcExchangeSequenceField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 序号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 合约交易状态
  MarketStatus: 'TThostFtdcInstrumentStatusType'
}

// 根据价格查询最大报单数量
structDict['CThostFtdcQueryMaxOrderVolumeWithPriceField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 开平标志
  OffsetFlag: 'TThostFtdcOffsetFlagType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 最大允许报单数量
  MaxVolume: 'TThostFtdcVolumeType',
  // 报单价格
  Price: 'TThostFtdcPriceType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询经纪公司交易参数
structDict['CThostFtdcQryBrokerTradingParamsField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType'
}

// 经纪公司交易参数
structDict['CThostFtdcBrokerTradingParamsField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 保证金价格类型
  MarginPriceType: 'TThostFtdcMarginPriceTypeType',
  // 盈亏算法
  Algorithm: 'TThostFtdcAlgorithmType',
  // 可用是否包含平仓盈利
  AvailIncludeCloseProfit: 'TThostFtdcIncludeCloseProfitType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 期权权利金价格类型
  OptionRoyaltyPriceType: 'TThostFtdcOptionRoyaltyPriceTypeType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType'
}

// 查询经纪公司交易算法
structDict['CThostFtdcQryBrokerTradingAlgosField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType'
}

// 经纪公司交易算法
structDict['CThostFtdcBrokerTradingAlgosField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 持仓处理算法编号
  HandlePositionAlgoID: 'TThostFtdcHandlePositionAlgoIDType',
  // 寻找保证金率算法编号
  FindMarginRateAlgoID: 'TThostFtdcFindMarginRateAlgoIDType',
  // 资金处理算法编号
  HandleTradingAccountAlgoID: 'TThostFtdcHandleTradingAccountAlgoIDType'
}

// 查询经纪公司资金
structDict['CThostFtdcQueryBrokerDepositField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 经纪公司资金
structDict['CThostFtdcBrokerDepositField'] = {
  // 交易日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 会员代码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 上次结算准备金
  PreBalance: 'TThostFtdcMoneyType',
  // 当前保证金总额
  CurrMargin: 'TThostFtdcMoneyType',
  // 平仓盈亏
  CloseProfit: 'TThostFtdcMoneyType',
  // 期货结算准备金
  Balance: 'TThostFtdcMoneyType',
  // 入金金额
  Deposit: 'TThostFtdcMoneyType',
  // 出金金额
  Withdraw: 'TThostFtdcMoneyType',
  // 可提资金
  Available: 'TThostFtdcMoneyType',
  // 基本准备金
  Reserve: 'TThostFtdcMoneyType',
  // 冻结的保证金
  FrozenMargin: 'TThostFtdcMoneyType'
}

// 查询保证金监管系统经纪公司密钥
structDict['CThostFtdcQryCFMMCBrokerKeyField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType'
}

// 保证金监管系统经纪公司密钥
structDict['CThostFtdcCFMMCBrokerKeyField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 经纪公司统一编码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 密钥生成日期
  CreateDate: 'TThostFtdcDateType',
  // 密钥生成时间
  CreateTime: 'TThostFtdcTimeType',
  // 密钥编号
  KeyID: 'TThostFtdcSequenceNoType',
  // 动态密钥
  CurrentKey: 'TThostFtdcCFMMCKeyType',
  // 动态密钥类型
  KeyKind: 'TThostFtdcCFMMCKeyKindType'
}

// 保证金监管系统经纪公司资金账户密钥
structDict['CThostFtdcCFMMCTradingAccountKeyField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 经纪公司统一编码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 密钥编号
  KeyID: 'TThostFtdcSequenceNoType',
  // 动态密钥
  CurrentKey: 'TThostFtdcCFMMCKeyType'
}

// 请求查询保证金监管系统经纪公司资金账户密钥
structDict['CThostFtdcQryCFMMCTradingAccountKeyField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

// 用户动态令牌参数
structDict['CThostFtdcBrokerUserOTPParamField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 动态令牌提供商
  OTPVendorsID: 'TThostFtdcOTPVendorsIDType',
  // 动态令牌序列号
  SerialNumber: 'TThostFtdcSerialNumberType',
  // 令牌密钥
  AuthKey: 'TThostFtdcAuthKeyType',
  // 漂移值
  LastDrift: 'TThostFtdcLastDriftType',
  // 成功值
  LastSuccess: 'TThostFtdcLastSuccessType',
  // 动态令牌类型
  OTPType: 'TThostFtdcOTPTypeType'
}

// 手工同步用户动态令牌
structDict['CThostFtdcManualSyncBrokerUserOTPField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 动态令牌类型
  OTPType: 'TThostFtdcOTPTypeType',
  // 第一个动态密码
  FirstOTP: 'TThostFtdcPasswordType',
  // 第二个动态密码
  SecondOTP: 'TThostFtdcPasswordType'
}

// 投资者手续费率模板
structDict['CThostFtdcCommRateModelField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 手续费率模板代码
  CommModelID: 'TThostFtdcInvestorIDType',
  // 模板名称
  CommModelName: 'TThostFtdcCommModelNameType'
}

// 请求查询投资者手续费率模板
structDict['CThostFtdcQryCommRateModelField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 手续费率模板代码
  CommModelID: 'TThostFtdcInvestorIDType'
}

// 投资者保证金率模板
structDict['CThostFtdcMarginModelField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 保证金率模板代码
  MarginModelID: 'TThostFtdcInvestorIDType',
  // 模板名称
  MarginModelName: 'TThostFtdcCommModelNameType'
}

// 请求查询投资者保证金率模板
structDict['CThostFtdcQryMarginModelField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 保证金率模板代码
  MarginModelID: 'TThostFtdcInvestorIDType'
}

// 仓单折抵信息
structDict['CThostFtdcEWarrantOffsetField'] = {
  // 交易日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 买卖方向
  Direction: 'TThostFtdcDirectionType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 数量
  Volume: 'TThostFtdcVolumeType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询仓单折抵信息
structDict['CThostFtdcQryEWarrantOffsetField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 合约代码
  InstrumentID: 'TThostFtdcInstrumentIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询投资者品种/跨品种保证金
structDict['CThostFtdcQryInvestorProductGroupMarginField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 品种/跨品种标示
  ProductGroupID: 'TThostFtdcInstrumentIDType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 投资者品种/跨品种保证金
structDict['CThostFtdcInvestorProductGroupMarginField'] = {
  // 品种/跨品种标示
  ProductGroupID: 'TThostFtdcInstrumentIDType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 结算编号
  SettlementID: 'TThostFtdcSettlementIDType',
  // 冻结的保证金
  FrozenMargin: 'TThostFtdcMoneyType',
  // 多头冻结的保证金
  LongFrozenMargin: 'TThostFtdcMoneyType',
  // 空头冻结的保证金
  ShortFrozenMargin: 'TThostFtdcMoneyType',
  // 占用的保证金
  UseMargin: 'TThostFtdcMoneyType',
  // 多头保证金
  LongUseMargin: 'TThostFtdcMoneyType',
  // 空头保证金
  ShortUseMargin: 'TThostFtdcMoneyType',
  // 交易所保证金
  ExchMargin: 'TThostFtdcMoneyType',
  // 交易所多头保证金
  LongExchMargin: 'TThostFtdcMoneyType',
  // 交易所空头保证金
  ShortExchMargin: 'TThostFtdcMoneyType',
  // 平仓盈亏
  CloseProfit: 'TThostFtdcMoneyType',
  // 冻结的手续费
  FrozenCommission: 'TThostFtdcMoneyType',
  // 手续费
  Commission: 'TThostFtdcMoneyType',
  // 冻结的资金
  FrozenCash: 'TThostFtdcMoneyType',
  // 资金差额
  CashIn: 'TThostFtdcMoneyType',
  // 持仓盈亏
  PositionProfit: 'TThostFtdcMoneyType',
  // 折抵总金额
  OffsetAmount: 'TThostFtdcMoneyType',
  // 多头折抵总金额
  LongOffsetAmount: 'TThostFtdcMoneyType',
  // 空头折抵总金额
  ShortOffsetAmount: 'TThostFtdcMoneyType',
  // 交易所折抵总金额
  ExchOffsetAmount: 'TThostFtdcMoneyType',
  // 交易所多头折抵总金额
  LongExchOffsetAmount: 'TThostFtdcMoneyType',
  // 交易所空头折抵总金额
  ShortExchOffsetAmount: 'TThostFtdcMoneyType',
  // 投机套保标志
  HedgeFlag: 'TThostFtdcHedgeFlagType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 查询监控中心用户令牌
structDict['CThostFtdcQueryCFMMCTradingAccountTokenField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 投资单元代码
  InvestUnitID: 'TThostFtdcInvestUnitIDType'
}

// 监控中心用户令牌
structDict['CThostFtdcCFMMCTradingAccountTokenField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 经纪公司统一编码
  ParticipantID: 'TThostFtdcParticipantIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 密钥编号
  KeyID: 'TThostFtdcSequenceNoType',
  // 动态令牌
  Token: 'TThostFtdcCFMMCTokenType'
}

// 查询产品组
structDict['CThostFtdcQryProductGroupField'] = {
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType'
}

// 投资者品种/跨品种保证金产品组
structDict['CThostFtdcProductGroupField'] = {
  // 产品代码
  ProductID: 'TThostFtdcInstrumentIDType',
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 产品组代码
  ProductGroupID: 'TThostFtdcInstrumentIDType'
}

// 交易所公告
structDict['CThostFtdcBulletinField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 交易日
  TradingDay: 'TThostFtdcDateType',
  // 公告编号
  BulletinID: 'TThostFtdcBulletinIDType',
  // 序列号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 公告类型
  NewsType: 'TThostFtdcNewsTypeType',
  // 紧急程度
  NewsUrgency: 'TThostFtdcNewsUrgencyType',
  // 发送时间
  SendTime: 'TThostFtdcTimeType',
  // 消息摘要
  Abstract: 'TThostFtdcAbstractType',
  // 消息来源
  ComeFrom: 'TThostFtdcComeFromType',
  // 消息正文
  Content: 'TThostFtdcContentType',
  // WEB地址
  URLLink: 'TThostFtdcURLLinkType',
  // 市场代码
  MarketID: 'TThostFtdcMarketIDType'
}

// 查询交易所公告
structDict['CThostFtdcQryBulletinField'] = {
  // 交易所代码
  ExchangeID: 'TThostFtdcExchangeIDType',
  // 公告编号
  BulletinID: 'TThostFtdcBulletinIDType',
  // 序列号
  SequenceNo: 'TThostFtdcSequenceNoType',
  // 公告类型
  NewsType: 'TThostFtdcNewsTypeType',
  // 紧急程度
  NewsUrgency: 'TThostFtdcNewsUrgencyType'
}

// 转帐开户请求
structDict['CThostFtdcReqOpenAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 汇钞标志
  CashExchangeCode: 'TThostFtdcCashExchangeCodeType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 转帐销户请求
structDict['CThostFtdcReqCancelAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 汇钞标志
  CashExchangeCode: 'TThostFtdcCashExchangeCodeType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 变更银行账户请求
structDict['CThostFtdcReqChangeAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 新银行帐号
  NewBankAccount: 'TThostFtdcBankAccountType',
  // 新银行密码
  NewBankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 转账请求
structDict['CThostFtdcReqTransferField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 转帐金额
  TradeAmount: 'TThostFtdcTradeAmountType',
  // 期货可取金额
  FutureFetchAmount: 'TThostFtdcTradeAmountType',
  // 费用支付标志
  FeePayFlag: 'TThostFtdcFeePayFlagType',
  // 应收客户费用
  CustFee: 'TThostFtdcCustFeeType',
  // 应收期货公司费用
  BrokerFee: 'TThostFtdcFutureFeeType',
  // 发送方给接收方的消息
  Message: 'TThostFtdcAddInfoType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 转账交易状态
  TransferStatus: 'TThostFtdcTransferStatusType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 银行发起银行资金转期货响应
structDict['CThostFtdcRspTransferField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 转帐金额
  TradeAmount: 'TThostFtdcTradeAmountType',
  // 期货可取金额
  FutureFetchAmount: 'TThostFtdcTradeAmountType',
  // 费用支付标志
  FeePayFlag: 'TThostFtdcFeePayFlagType',
  // 应收客户费用
  CustFee: 'TThostFtdcCustFeeType',
  // 应收期货公司费用
  BrokerFee: 'TThostFtdcFutureFeeType',
  // 发送方给接收方的消息
  Message: 'TThostFtdcAddInfoType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 转账交易状态
  TransferStatus: 'TThostFtdcTransferStatusType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 冲正请求
structDict['CThostFtdcReqRepealField'] = {
  // 冲正时间间隔
  RepealTimeInterval: 'TThostFtdcRepealTimeIntervalType',
  // 已经冲正次数
  RepealedTimes: 'TThostFtdcRepealedTimesType',
  // 银行冲正标志
  BankRepealFlag: 'TThostFtdcBankRepealFlagType',
  // 期商冲正标志
  BrokerRepealFlag: 'TThostFtdcBrokerRepealFlagType',
  // 被冲正平台流水号
  PlateRepealSerial: 'TThostFtdcPlateSerialType',
  // 被冲正银行流水号
  BankRepealSerial: 'TThostFtdcBankSerialType',
  // 被冲正期货流水号
  FutureRepealSerial: 'TThostFtdcFutureSerialType',
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 转帐金额
  TradeAmount: 'TThostFtdcTradeAmountType',
  // 期货可取金额
  FutureFetchAmount: 'TThostFtdcTradeAmountType',
  // 费用支付标志
  FeePayFlag: 'TThostFtdcFeePayFlagType',
  // 应收客户费用
  CustFee: 'TThostFtdcCustFeeType',
  // 应收期货公司费用
  BrokerFee: 'TThostFtdcFutureFeeType',
  // 发送方给接收方的消息
  Message: 'TThostFtdcAddInfoType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 转账交易状态
  TransferStatus: 'TThostFtdcTransferStatusType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 冲正响应
structDict['CThostFtdcRspRepealField'] = {
  // 冲正时间间隔
  RepealTimeInterval: 'TThostFtdcRepealTimeIntervalType',
  // 已经冲正次数
  RepealedTimes: 'TThostFtdcRepealedTimesType',
  // 银行冲正标志
  BankRepealFlag: 'TThostFtdcBankRepealFlagType',
  // 期商冲正标志
  BrokerRepealFlag: 'TThostFtdcBrokerRepealFlagType',
  // 被冲正平台流水号
  PlateRepealSerial: 'TThostFtdcPlateSerialType',
  // 被冲正银行流水号
  BankRepealSerial: 'TThostFtdcBankSerialType',
  // 被冲正期货流水号
  FutureRepealSerial: 'TThostFtdcFutureSerialType',
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 转帐金额
  TradeAmount: 'TThostFtdcTradeAmountType',
  // 期货可取金额
  FutureFetchAmount: 'TThostFtdcTradeAmountType',
  // 费用支付标志
  FeePayFlag: 'TThostFtdcFeePayFlagType',
  // 应收客户费用
  CustFee: 'TThostFtdcCustFeeType',
  // 应收期货公司费用
  BrokerFee: 'TThostFtdcFutureFeeType',
  // 发送方给接收方的消息
  Message: 'TThostFtdcAddInfoType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 转账交易状态
  TransferStatus: 'TThostFtdcTransferStatusType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 查询账户信息请求
structDict['CThostFtdcReqQueryAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 查询账户信息响应
structDict['CThostFtdcRspQueryAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 银行可用金额
  BankUseAmount: 'TThostFtdcTradeAmountType',
  // 银行可取金额
  BankFetchAmount: 'TThostFtdcTradeAmountType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 期商签到签退
structDict['CThostFtdcFutureSignIOField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType'
}

// 期商签到响应
structDict['CThostFtdcRspFutureSignInField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // PIN密钥
  PinKey: 'TThostFtdcPasswordKeyType',
  // MAC密钥
  MacKey: 'TThostFtdcPasswordKeyType'
}

// 期商签退请求
structDict['CThostFtdcReqFutureSignOutField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType'
}

// 期商签退响应
structDict['CThostFtdcRspFutureSignOutField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 查询指定流水号的交易结果请求
structDict['CThostFtdcReqQueryTradeResultBySerialField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 流水号
  Reference: 'TThostFtdcSerialType',
  // 本流水号发布者的机构类型
  RefrenceIssureType: 'TThostFtdcInstitutionTypeType',
  // 本流水号发布者机构编码
  RefrenceIssure: 'TThostFtdcOrganCodeType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 转帐金额
  TradeAmount: 'TThostFtdcTradeAmountType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 查询指定流水号的交易结果响应
structDict['CThostFtdcRspQueryTradeResultBySerialField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 流水号
  Reference: 'TThostFtdcSerialType',
  // 本流水号发布者的机构类型
  RefrenceIssureType: 'TThostFtdcInstitutionTypeType',
  // 本流水号发布者机构编码
  RefrenceIssure: 'TThostFtdcOrganCodeType',
  // 原始返回代码
  OriginReturnCode: 'TThostFtdcReturnCodeType',
  // 原始返回码描述
  OriginDescrInfoForReturnCode: 'TThostFtdcDescrInfoForReturnCodeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 转帐金额
  TradeAmount: 'TThostFtdcTradeAmountType',
  // 摘要
  Digest: 'TThostFtdcDigestType'
}

// 日终文件就绪请求
structDict['CThostFtdcReqDayEndFileReadyField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 文件业务功能
  FileBusinessCode: 'TThostFtdcFileBusinessCodeType',
  // 摘要
  Digest: 'TThostFtdcDigestType'
}

// 返回结果
structDict['CThostFtdcReturnResultField'] = {
  // 返回代码
  ReturnCode: 'TThostFtdcReturnCodeType',
  // 返回码描述
  DescrInfoForReturnCode: 'TThostFtdcDescrInfoForReturnCodeType'
}

// 验证期货资金密码
structDict['CThostFtdcVerifyFuturePasswordField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 验证客户信息
structDict['CThostFtdcVerifyCustInfoField'] = {
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 验证期货资金密码和客户信息
structDict['CThostFtdcVerifyFuturePasswordAndCustInfoField'] = {
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 验证期货资金密码和客户信息
structDict['CThostFtdcDepositResultInformField'] = {
  // 出入金流水号，该流水号为银期报盘返回的流水号
  DepositSeqNo: 'TThostFtdcDepositSeqNoType',
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 入金金额
  Deposit: 'TThostFtdcMoneyType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 返回代码
  ReturnCode: 'TThostFtdcReturnCodeType',
  // 返回码描述
  DescrInfoForReturnCode: 'TThostFtdcDescrInfoForReturnCodeType'
}

// 交易核心向银期报盘发出密钥同步请求
structDict['CThostFtdcReqSyncKeyField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 交易核心给银期报盘的消息
  Message: 'TThostFtdcAddInfoType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType'
}

// 交易核心向银期报盘发出密钥同步响应
structDict['CThostFtdcRspSyncKeyField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 交易核心给银期报盘的消息
  Message: 'TThostFtdcAddInfoType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 查询账户信息通知
structDict['CThostFtdcNotifyQueryAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 银行可用金额
  BankUseAmount: 'TThostFtdcTradeAmountType',
  // 银行可取金额
  BankFetchAmount: 'TThostFtdcTradeAmountType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 银期转账交易流水表
structDict['CThostFtdcTransferSerialField'] = {
  // 平台流水号
  PlateSerial: 'TThostFtdcPlateSerialType',
  // 交易发起方日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易日期
  TradingDay: 'TThostFtdcDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 交易代码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 会话编号
  SessionID: 'TThostFtdcSessionIDType',
  // 银行编码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构编码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 期货公司编码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 期货公司帐号类型
  FutureAccType: 'TThostFtdcFutureAccTypeType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType',
  // 期货公司流水号
  FutureSerial: 'TThostFtdcFutureSerialType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 交易金额
  TradeAmount: 'TThostFtdcTradeAmountType',
  // 应收客户费用
  CustFee: 'TThostFtdcCustFeeType',
  // 应收期货公司费用
  BrokerFee: 'TThostFtdcFutureFeeType',
  // 有效标志
  AvailabilityFlag: 'TThostFtdcAvailabilityFlagType',
  // 操作员
  OperatorCode: 'TThostFtdcOperatorCodeType',
  // 新银行帐号
  BankNewAccount: 'TThostFtdcBankAccountType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 请求查询转帐流水
structDict['CThostFtdcQryTransferSerialField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 银行编码
  BankID: 'TThostFtdcBankIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 期商签到通知
structDict['CThostFtdcNotifyFutureSignInField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // PIN密钥
  PinKey: 'TThostFtdcPasswordKeyType',
  // MAC密钥
  MacKey: 'TThostFtdcPasswordKeyType'
}

// 期商签退通知
structDict['CThostFtdcNotifyFutureSignOutField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 交易核心向银期报盘发出密钥同步处理结果的通知
structDict['CThostFtdcNotifySyncKeyField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 交易核心给银期报盘的消息
  Message: 'TThostFtdcAddInfoType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 请求编号
  RequestID: 'TThostFtdcRequestIDType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 请求查询银期签约关系
structDict['CThostFtdcQryAccountregisterField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 银行编码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构编码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 客户开销户信息表
structDict['CThostFtdcAccountregisterField'] = {
  // 交易日期
  TradeDay: 'TThostFtdcTradeDateType',
  // 银行编码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构编码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 期货公司编码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期货公司分支机构编码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 开销户类别
  OpenOrDestroy: 'TThostFtdcOpenOrDestroyType',
  // 签约日期
  RegDate: 'TThostFtdcTradeDateType',
  // 解约日期
  OutDate: 'TThostFtdcTradeDateType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 银期开户信息
structDict['CThostFtdcOpenAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 汇钞标志
  CashExchangeCode: 'TThostFtdcCashExchangeCodeType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 银期销户信息
structDict['CThostFtdcCancelAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 汇钞标志
  CashExchangeCode: 'TThostFtdcCashExchangeCodeType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 渠道标志
  DeviceID: 'TThostFtdcDeviceIDType',
  // 期货单位帐号类型
  BankSecuAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 期货单位帐号
  BankSecuAcc: 'TThostFtdcBankAccountType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易柜员
  OperNo: 'TThostFtdcOperNoType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 用户标识
  UserID: 'TThostFtdcUserIDType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 银期变更银行账号信息
structDict['CThostFtdcChangeAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 新银行帐号
  NewBankAccount: 'TThostFtdcBankAccountType',
  // 新银行密码
  NewBankPassWord: 'TThostFtdcPasswordType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 银行密码标志
  BankPwdFlag: 'TThostFtdcPwdFlagType',
  // 期货资金密码核对标志
  SecuPwdFlag: 'TThostFtdcPwdFlagType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType',
  // 长客户姓名
  LongCustomerName: 'TThostFtdcLongIndividualNameType'
}

// 二级代理操作员银期权限
structDict['CThostFtdcSecAgentACIDMapField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 资金账户
  AccountID: 'TThostFtdcAccountIDType',
  // 币种
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 境外中介机构资金帐号
  BrokerSecAgentID: 'TThostFtdcAccountIDType'
}

// 二级代理操作员银期权限查询
structDict['CThostFtdcQrySecAgentACIDMapField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 资金账户
  AccountID: 'TThostFtdcAccountIDType',
  // 币种
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 灾备中心交易权限
structDict['CThostFtdcUserRightsAssignField'] = {
  // 应用单元代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 交易中心代码
  DRIdentityID: 'TThostFtdcDRIdentityIDType'
}

// 经济公司是否有在本标示的交易权限
structDict['CThostFtdcBrokerUserRightAssignField'] = {
  // 应用单元代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 交易中心代码
  DRIdentityID: 'TThostFtdcDRIdentityIDType',
  // 能否交易
  Tradeable: 'TThostFtdcBoolType'
}

// 灾备交易转换报文
structDict['CThostFtdcDRTransferField'] = {
  // 原交易中心代码
  OrigDRIdentityID: 'TThostFtdcDRIdentityIDType',
  // 目标交易中心代码
  DestDRIdentityID: 'TThostFtdcDRIdentityIDType',
  // 原应用单元代码
  OrigBrokerID: 'TThostFtdcBrokerIDType',
  // 目标易用单元代码
  DestBrokerID: 'TThostFtdcBrokerIDType'
}

// Fens用户信息
structDict['CThostFtdcFensUserInfoField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // 登录模式
  LoginMode: 'TThostFtdcLoginModeType'
}

// 当前银期所属交易中心
structDict['CThostFtdcCurrTransferIdentityField'] = {
  // 交易中心代码
  IdentityID: 'TThostFtdcDRIdentityIDType'
}

// 禁止登录用户
structDict['CThostFtdcLoginForbiddenUserField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType',
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType'
}

// 查询禁止登录用户
structDict['CThostFtdcQryLoginForbiddenUserField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// UDP组播组信息
structDict['CThostFtdcMulticastGroupInfoField'] = {
  // 组播组IP地址
  GroupIP: 'TThostFtdcIPAddressType',
  // 组播组IP端口
  GroupPort: 'TThostFtdcIPPortType',
  // 源地址
  SourceIP: 'TThostFtdcIPAddressType'
}

// 资金账户基本准备金
structDict['CThostFtdcTradingAccountReserveField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 基本准备金
  Reserve: 'TThostFtdcMoneyType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 查询禁止登录IP
structDict['CThostFtdcQryLoginForbiddenIPField'] = {
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType'
}

// 查询IP列表
structDict['CThostFtdcQryIPListField'] = {
  // IP地址
  IPAddress: 'TThostFtdcIPAddressType'
}

// 查询用户下单权限分配表
structDict['CThostFtdcQryUserRightsAssignField'] = {
  // 应用单元代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 用户代码
  UserID: 'TThostFtdcUserIDType'
}

// 银期预约开户确认请求
structDict['CThostFtdcReserveOpenAccountConfirmField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcLongIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 期货密码
  Password: 'TThostFtdcPasswordType',
  // 预约开户银行流水号
  BankReserveOpenSeq: 'TThostFtdcBankSerialType',
  // 预约开户日期
  BookDate: 'TThostFtdcTradeDateType',
  // 预约开户验证密码
  BookPsw: 'TThostFtdcPasswordType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 银期预约开户
structDict['CThostFtdcReserveOpenAccountField'] = {
  // 业务功能码
  TradeCode: 'TThostFtdcTradeCodeType',
  // 银行代码
  BankID: 'TThostFtdcBankIDType',
  // 银行分支机构代码
  BankBranchID: 'TThostFtdcBankBrchIDType',
  // 期商代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 期商分支机构代码
  BrokerBranchID: 'TThostFtdcFutureBranchIDType',
  // 交易日期
  TradeDate: 'TThostFtdcTradeDateType',
  // 交易时间
  TradeTime: 'TThostFtdcTradeTimeType',
  // 银行流水号
  BankSerial: 'TThostFtdcBankSerialType',
  // 交易系统日期
  TradingDay: 'TThostFtdcTradeDateType',
  // 银期平台消息流水号
  PlateSerial: 'TThostFtdcSerialType',
  // 最后分片标志
  LastFragment: 'TThostFtdcLastFragmentType',
  // 会话号
  SessionID: 'TThostFtdcSessionIDType',
  // 客户姓名
  CustomerName: 'TThostFtdcLongIndividualNameType',
  // 证件类型
  IdCardType: 'TThostFtdcIdCardTypeType',
  // 证件号码
  IdentifiedCardNo: 'TThostFtdcIdentifiedCardNoType',
  // 性别
  Gender: 'TThostFtdcGenderType',
  // 国家代码
  CountryCode: 'TThostFtdcCountryCodeType',
  // 客户类型
  CustType: 'TThostFtdcCustTypeType',
  // 地址
  Address: 'TThostFtdcAddressType',
  // 邮编
  ZipCode: 'TThostFtdcZipCodeType',
  // 电话号码
  Telephone: 'TThostFtdcTelephoneType',
  // 手机
  MobilePhone: 'TThostFtdcMobilePhoneType',
  // 传真
  Fax: 'TThostFtdcFaxType',
  // 电子邮件
  EMail: 'TThostFtdcEMailType',
  // 资金账户状态
  MoneyAccountStatus: 'TThostFtdcMoneyAccountStatusType',
  // 银行帐号
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行密码
  BankPassWord: 'TThostFtdcPasswordType',
  // 安装编号
  InstallID: 'TThostFtdcInstallIDType',
  // 验证客户证件号码标志
  VerifyCertNoFlag: 'TThostFtdcYesNoIndicatorType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType',
  // 摘要
  Digest: 'TThostFtdcDigestType',
  // 银行帐号类型
  BankAccType: 'TThostFtdcBankAccTypeType',
  // 期货公司银行编码
  BrokerIDByBank: 'TThostFtdcBankCodingForFutureType',
  // 交易ID
  TID: 'TThostFtdcTIDType',
  // 预约开户状态
  ReserveOpenAccStas: 'TThostFtdcReserveOpenAccStasType',
  // 错误代码
  ErrorID: 'TThostFtdcErrorIDType',
  // 错误信息
  ErrorMsg: 'TThostFtdcErrorMsgType'
}

// 银行账户属性
structDict['CThostFtdcAccountPropertyField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者帐号
  AccountID: 'TThostFtdcAccountIDType',
  // 银行统一标识类型
  BankID: 'TThostFtdcBankIDType',
  // 银行账户
  BankAccount: 'TThostFtdcBankAccountType',
  // 银行账户的开户人名称
  OpenName: 'TThostFtdcInvestorFullNameType',
  // 银行账户的开户行
  OpenBank: 'TThostFtdcOpenBankType',
  // 是否活跃
  IsActive: 'TThostFtdcBoolType',
  // 账户来源
  AccountSourceType: 'TThostFtdcAccountSourceTypeType',
  // 开户日期
  OpenDate: 'TThostFtdcDateType',
  // 注销日期
  CancelDate: 'TThostFtdcDateType',
  // 录入员代码
  OperatorID: 'TThostFtdcOperatorIDType',
  // 录入日期
  OperateDate: 'TThostFtdcDateType',
  // 录入时间
  OperateTime: 'TThostFtdcTimeType',
  // 币种代码
  CurrencyID: 'TThostFtdcCurrencyIDType'
}

// 查询当前交易中心
structDict['CThostFtdcQryCurrDRIdentityField'] = {
  // 交易中心代码
  DRIdentityID: 'TThostFtdcDRIdentityIDType'
}

// 当前交易中心
structDict['CThostFtdcCurrDRIdentityField'] = {
  // 交易中心代码
  DRIdentityID: 'TThostFtdcDRIdentityIDType'
}

// 查询二级代理商资金校验模式
structDict['CThostFtdcQrySecAgentCheckModeField'] = {
  // 经纪公司代码
  BrokerID: 'TThostFtdcBrokerIDType',
  // 投资者代码
  InvestorID: 'TThostFtdcInvestorIDType'
}

module.exports = structDict
