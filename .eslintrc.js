module.exports = {
  'extends': 'standard',
  'rules': {
    'semi': [2, 'never'],
    'space-before-function-paren': [0],
    'camelcase': [0],
    'no-sequences': [0],
    'no-useless-escape': [0],
    'no-debugger': process.env.NODE_ENV === 'production' ? 2 : 0
  },
  globals: {
    'before': true,
    'it': true,
    'describe': true
  }
}
