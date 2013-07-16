{
  "target_defaults": {
    "include_dirs": ["./includes"]
  },
    "conditions": [
        [
            "OS=='win'", 
            { "variables": { "ONI_Root%": "../" } }, 
            { "variables": { "ONI_Root%": "" } }
        ]
    ], 
    "targets": [
        {
          "cflags!": [
              "-fno-exceptions",
              "-O3",
              "-I./includes/cvv8",
              "-Wno-missing-field-initializers",
              "-Wno-unused" ],
          "cflags_cc!": [ 
              "-fno-exceptions",
              "-Wno-missing-field-initializers",
              "-Wno-unused" ],
          "cflags": [ "-O3" ],
            "conditions": [
                [
                    "OS=='mac'", 
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                        }
                    }
                ]
            ], 
            "include_dirs": ["src"],
            "sources": [
                "src/cgeohash.cpp",
                "src/cgeohash_node.cpp"
            ], 
            "target_name": "cgeohash"
        },
        {
          "cflags!": [
              "-fno-exceptions",
              "-O3",
              "-I./includes/cvv8",
              "-Wno-missing-field-initializers",
              "-Wno-unused" ],
          "cflags_cc!": [ 
              "-fno-exceptions",
              "-Wno-missing-field-initializers",
              "-Wno-unused" ],
          "cflags": [ "-O3" ],
            "conditions": [
                [
                    "OS=='mac'", 
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                        }
                    }
                ]
            ], 
            "defines": [ "GEOHASH_ENABLE_SPEED_TESTS=1" ],
            "include_dirs": ["src"],
            "sources": [
                "src/cgeohash_node_speed_tests.cpp",
                "src/cgeohash.cpp"
            ], 
            "target_name": "cgeohash_speed_tests"
        },
        {
          "cflags!": [
              "-fno-exceptions",
              "-O3",
              "-I./includes/cvv8",
              "-Wno-missing-field-initializers",
              "-Wno-unused" ],
          "cflags_cc!": [ 
              "-fno-exceptions",
              "-Wno-missing-field-initializers",
              "-Wno-unused" ],
          "cflags": [ "-O3" ],
            "conditions": [
                [
                    "OS=='mac'", 
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                        }
                    }
                ]
            ], 
            "include_dirs": ["src"],
            "sources": [
                "src/cgeohash.cpp",
                "src/cgeohash_node.cpp"
            ], 
            "type": "static_library",
            "include_dirs": [
                "src",
            ],
            "all_dependent_settings": {
                "include_dirs": [
                    "src",
                ],
            },
            "target_name": "cgeohash_lib"
        }
    ]
}
