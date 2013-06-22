#ifndef _NODE_CGEOHASH_OBJ_REPEATERS_HPP
#define _NODE_CGEOHASH_OBJ_REPEATERS_HPP

#include <node.h>
#include <string>

namespace cgeohash {

class GeoHashObjectRepeater : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);

protected:
    GeoHashObjectRepeater();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static v8::Handle<v8::Value> Encode(const v8::Arguments& args);
		static v8::Handle<v8::Value> Decode(const v8::Arguments& args);
		static v8::Handle<v8::Value> DecodeBBox(const v8::Arguments& args);
		static v8::Handle<v8::Value> Neighbor(const v8::Arguments& args);

	};

}

#endif /* geohash.hpp */
