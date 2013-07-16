#ifndef _NODE_CGEOHASH_NODE_HPP
#define _NODE_CGEOHASH_NODE_HPP

#include <node.h>
#include <string>

namespace cgeohash {

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_fn(const v8::Arguments& args);
v8::Handle<v8::Value> decode_fn(const v8::Arguments& args);
v8::Handle<v8::Value> encode_all_precisions_fn(const v8::Arguments& args);
v8::Handle<v8::Value> decode_bbox_fn(const v8::Arguments& args);
v8::Handle<v8::Value> neighbor_fn(const v8::Arguments& args);

}

#endif /* end hpp */
