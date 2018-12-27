const path = require('path')
const fs = require('fs')
const gen_struct = require('./gen_struct')
const gen_uv_trader = require('./gen_uv_trader')
const gen_ctp_trader = require('./gen_ctp_trader')

const BASE_DIR_PATH = path.join(__dirname, '../')

const CTP_LIB_PATH = path.join(BASE_DIR_PATH, './lib/')

const trader_api_content = fs.readFileSync(path.join(CTP_LIB_PATH, 'ThostFtdcTraderApi.h')).toString()

const reqFuncs = []

const resFuncs = []

const reqFuncs_pattern = new RegExp('virtual +(.*) +([a-zA-Z]*) *\\((.*)\\) *= *0', 'g')
const resFuncs_pattern = new RegExp('virtual +void +(On[a-zA-Z]+) *\\((.*)\\) *{ *}', 'g')

let match = reqFuncs_pattern.exec(trader_api_content)
const filter_funcs = [
  'Release',
  'Init',
  'Join',
  'RegisterFront',
  'RegisterNameServer',
  'RegisterFensUserInfo',
  'RegisterSpi',
  'SubscribePrivateTopic',
  'SubscribePublicTopic'
]

while (match !== null) {
  if (filter_funcs.indexOf(match[2]) < 0) {
    reqFuncs.push([match[2], match[3], match[1]])
  }
  match = reqFuncs_pattern.exec(trader_api_content)
}

match = resFuncs_pattern.exec(trader_api_content)

while (match !== null) {
  // console.log(match[1])
  resFuncs.push([match[1], match[2]])
  match = resFuncs_pattern.exec(trader_api_content)
}

gen_struct(reqFuncs, resFuncs, BASE_DIR_PATH)

gen_uv_trader(reqFuncs, resFuncs, BASE_DIR_PATH)

gen_ctp_trader(reqFuncs, resFuncs, BASE_DIR_PATH)
