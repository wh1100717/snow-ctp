{
  "targets": [
    {
      "target_name": "ctp",
      "sources": [
        "./cpp/shifctp.cpp",
        "./cpp/ThostFtdcMdSpiI.cpp",
        "./cpp/WrapMd.cpp",
        "./cpp/ThostFtdcTraderSpiI.cpp",
        "./cpp/WrapTd.cpp"
      ],
      "include_dirs": ["./lib/"],
      "conditions": [
        ['OS=="linux"', {
          'target_name': 'ctp',
          'libraries': [
            '$(CURDIR)/../lib/thosttraderapi.so',
            '$(CURDIR)/../lib/thostmduserapi.so'
          ]
        }],
        ['OS=="win"', {
          'target_name': 'ctp',
          'libraries': [
            "../lib/thosttraderapi.lib",
            '../lib/thostmduserapi.lib'
          ]
        }]
      ]
    }
  ]
}
