#ifndef _NODE_CGEOHASH_FN_HPP
#define _NODE_CGEOHASH_FN_HPP

#include <node.h>
#include <string>

namespace cgeohash {

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_fn(const v8::Arguments& args);
v8::Handle<v8::Value> decode_fn(const v8::Arguments& args);
v8::Handle<v8::Value> decode_bbox_fn(const v8::Arguments& args);
v8::Handle<v8::Value> neighbor_fn(const v8::Arguments& args);

// Register the above methods with node
v8::Handle<v8::Value> register_node_fns(v8::Handle<v8::Object> target);

}

#endif /* end hpp */
