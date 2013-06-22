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
                "src/bindings.cpp",
                "src/cgeohash_cpp.cpp",
                "src/cgeohash_node_fns.cpp",
                "src/cgeohash_node_obj.cpp",
                "src/speed_tests/cgeohash_cpp_st.cpp",
                "src/speed_tests/cgeohash_node_fns_st.cpp",
                "src/speed_tests/cgeohash_node_obj_st.cpp",
            ], 
            "target_name": "cgeohash"
        }
    ]
}
