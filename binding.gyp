{
"variables": { "library_files": ["lib/cgeohash_obj.js", "lib/cgeohash_fn.js", "lib/cgeohash_obj_speed_tests.js", "lib/cgeohash_fn_speed_tests.js"] },
    "conditions": [
        [
            "OS=='win'", 
            {
                "variables": {
                    "ONI_Root%": "../"
                }
            }, 
            {
                "variables": {
                    "ONI_Root%": ""
                }
            }
        ]
    ], 
    "targets": [
        {
            "cflags": [
                "-O3"
            ], 
            "cflags!": [
                "-fno-exceptions"
            ], 
            "cflags_cc!": [
                "-fno-exceptions"
            ], 
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
                "src/cgeohash_bindings.cpp",
                "src/cgeohash.cpp",
                "src/cgeohash_fn.cpp",
                "src/cgeohash_fn_repeaters.cpp",
                "src/cgeohash_obj.cpp",
                "src/cgeohash_obj_repeaters.cpp",
                "src/cgeohash_nanoseconds.cpp"
            ], 
            "target_name": "cgeohash"
        }
    ]
}
