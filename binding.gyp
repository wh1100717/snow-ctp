{
  "targets": [
    {
      "target_name": "ctp",
      "sources": [
        "./cpp/ctp.cc",
        "./cpp/ctp_trader.cpp",
        "./cpp/uv_trader.cpp",
        "./cpp/ctp_market.cpp",
        "./cpp/uv_market.cpp",
        "./cpp/ctp_utils.cpp"
      ],
      "libraries": [
        "../lib/thosttraderapi.lib",
        '../lib/thostmduserapi.lib'
      ],
      "include_dirs": ["./lib/"],
      "conditions": [
        ['OS=="linux"', {
          'target_name': 'ctp_linux'
        }],
        ['OS=="win"', {
          'target_name': 'ctp_win32'
        }]
      ]
    }
  ]
}
