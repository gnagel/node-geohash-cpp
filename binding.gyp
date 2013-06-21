{
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
            "sources": [
                "bindings.cpp",
                "geohash.cpp",
                "geohash_node_binding.cpp",
                "geohash_node_binding_speed.cpp",
                "geohash_obj.cpp"
            ], 
            "target_name": "cgeohash"
        }
    ]
}
