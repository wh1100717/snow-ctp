const structDict = require('./src/ctp_struct')
const { defineDict, typedefDict } = require('./src/ctp_data_type')

exports.ctp = require(`./src/ctp_${process.platform}.node`)
exports.structDict = structDict
exports.defineDict = defineDict
exports.typedefDict = typedefDict
