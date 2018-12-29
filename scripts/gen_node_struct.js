const fs = require('fs')
const path = require('path')
const { typedefDict } = require('./ctp_data_type')

let abc_content = fs.readFileSync('node_struct.js').toString()

const tthost_pattern = new RegExp('(TThost.*)\'', 'g')

let match = tthost_pattern.exec(abc_content)

while (match !== null) {
  abc_content = abc_content.replace(new RegExp(match[1], 'g'), typedefDict[match[1]])
  match = tthost_pattern.exec(abc_content)
}

fs.writeFileSync('./ctp_struct.js', abc_content)
