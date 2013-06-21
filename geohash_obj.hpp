#ifndef _NODE_GEOHASH_OBJ_HPP
#define _NODE_GEOHASH_OBJ_HPP

#include <node.h>

class GeoHashObject : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);

protected:
    GeoHashObject();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static v8::Handle<v8::Value> Encode(const v8::Arguments& args);
		static v8::Handle<v8::Value> Decode(const v8::Arguments& args);
		static v8::Handle<v8::Value> DecodeBBox(const v8::Arguments& args);
		static v8::Handle<v8::Value> Neighbor(const v8::Arguments& args);

		// Used for performance testing!!
		static v8::Handle<v8::Value> Test1M_Encode(const v8::Arguments& args);
		static v8::Handle<v8::Value> Test1M_Decode(const v8::Arguments& args);
		static v8::Handle<v8::Value> Test1M_DecodeBBox(const v8::Arguments& args);
		static v8::Handle<v8::Value> Test1M_Neighbor(const v8::Arguments& args);
	};

#endif
