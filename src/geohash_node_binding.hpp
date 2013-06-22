#ifndef _NODE_GEOHASH_NODE_BINDINGS_HPP
#define _NODE_GEOHASH_NODE_BINDINGS_HPP

#include <node.h>
#include <string>

// Node.JS Hooks to GeoHash encoding
namespace geohash {
v8::Handle<v8::Value> encode_js(const v8::Arguments& args);
v8::Handle<v8::Value> decode_js(const v8::Arguments& args);
v8::Handle<v8::Value> decode_bbox_js(const v8::Arguments& args);
v8::Handle<v8::Value> neighbor_js(const v8::Arguments& args);

}

void geohash_Init(v8::Handle<v8::Object> target);

#endif /* geohash.hpp */
