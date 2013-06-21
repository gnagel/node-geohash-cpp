#include <v8.h>
#include <node.h>

#include "geohash.hpp"
#include "geohash_node_binding.hpp"

void RegisterModule(v8::Handle<v8::Object> target) {
    node::SetMethod(target, "encode_js",      geohash::encode_js);
    node::SetMethod(target, "decode_js",      geohash::encode_js);
    node::SetMethod(target, "decode_bbox_js", geohash::encode_js);
    node::SetMethod(target, "neighbor_js",    geohash::encode_js);
}

NODE_MODULE(cgeohash, RegisterModule);
