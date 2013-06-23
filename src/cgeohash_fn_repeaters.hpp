#ifndef _NODE_CGEOHASH_FN_REPEATERS_HPP
#define _NODE_CGEOHASH_FN_REPEATERS_HPP

#include <node.h>
#include <string>

namespace cgeohash {

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_fn_repeater(const v8::Arguments& args);
v8::Handle<v8::Value> decode_fn_repeater(const v8::Arguments& args);
v8::Handle<v8::Value> decode_bbox_fn_repeater(const v8::Arguments& args);
v8::Handle<v8::Value> neighbor_fn_repeater(const v8::Arguments& args);

// Register the above methods with node
void register_node_fn_repeaters(v8::Handle<v8::Object> target);

}

#endif /* end hpp */
