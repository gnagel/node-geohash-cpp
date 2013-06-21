#ifndef _NODE_GEOHASH_BINDING_SPEED_HPP
#define _NODE_GEOHASH_BINDING_SPEED_HPP

#include <node.h>
#include <string>

// Node.JS Hooks to GeoHash encoding
namespace geohash {
// Used for performance testing!!
v8::Handle<v8::Value> test1m_encode_js(const v8::Arguments& args);
v8::Handle<v8::Value> test1m_decode_js(const v8::Arguments& args);
v8::Handle<v8::Value> test1m_decode_bbox_js(const v8::Arguments& args);
v8::Handle<v8::Value> test1m_neighbor_js(const v8::Arguments& args);

void test1m_Init(v8::Handle<v8::Object> target);

}

#endif /* geohash.hpp */
