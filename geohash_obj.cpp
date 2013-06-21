#include <v8.h>
#include <node.h>
#include "geohash_obj.hpp"

#include "geohash.hpp"
#include "geohash_node_binding.hpp"


v8::Persistent<v8::FunctionTemplate> GeoHashObject::constructor;


void GeoHashObject::Init(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
    v8::Local<v8::String>           name = v8::String::NewSymbol("GeoHashObject");

    constructor = v8::Persistent<v8::FunctionTemplate>::New(tpl);

    // ObjectWrap uses the first internal field to store the wrapped pointer.
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    NODE_SET_PROTOTYPE_METHOD(constructor, "encode",      Encode);
    NODE_SET_PROTOTYPE_METHOD(constructor, "decode",      Decode);
    NODE_SET_PROTOTYPE_METHOD(constructor, "decode_bbox", DecodeBBox);
    NODE_SET_PROTOTYPE_METHOD(constructor, "neighbor",    Neighbor);

		// Used for performance testing!!
		NODE_SET_PROTOTYPE_METHOD(constructor, "test1m_encode", Test1M_Encode);
		NODE_SET_PROTOTYPE_METHOD(constructor, "test1m_decode", Test1M_Decode);
		NODE_SET_PROTOTYPE_METHOD(constructor, "test1m_decode_bbox", Test1M_DecodeBBox);
		NODE_SET_PROTOTYPE_METHOD(constructor, "test1m_neighbor", Test1M_Neighbor);


    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}


GeoHashObject::GeoHashObject() : node::ObjectWrap() {
}


v8::Handle<v8::Value> GeoHashObject::New(const v8::Arguments& args) {
    v8::HandleScope scope;

    if (!args.IsConstructCall()) {
        return ThrowException(
                   v8::Exception::TypeError(
                       v8::String::New("Use the new operator to create instances of this object."))
               );
    }

    // Creates a new instance object of this type and wraps it.
    GeoHashObject* obj = new GeoHashObject();
    obj->Wrap(args.This());

    return args.This();
}


v8::Handle<v8::Value> GeoHashObject::Encode(const v8::Arguments& args) {
	return geohash::encode_js(args);
}


v8::Handle<v8::Value> GeoHashObject::Decode(const v8::Arguments& args) {
	return geohash::decode_js(args);
}


v8::Handle<v8::Value> GeoHashObject::DecodeBBox(const v8::Arguments& args) {
	return geohash::decode_bbox_js(args);
}


v8::Handle<v8::Value> GeoHashObject::Neighbor(const v8::Arguments& args) {
	return geohash::neighbor_js(args);
}



// Used for performance testing!!
v8::Handle<v8::Value> GeoHashObject::Test1M_Encode(const v8::Arguments& args) {
  v8::HandleScope scope;

	for(int i = 0, max = 1000*1000; i < max; i++) {
		v8::Handle<v8::Value> output = Encode(args);
		if (i + 1 == max)
			return output;
	}
	
	return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> GeoHashObject::Test1M_Decode(const v8::Arguments& args) {
  v8::HandleScope scope;

	for(int i = 0, max = 1000*1000; i < max; i++) {
		v8::Handle<v8::Value> output = Decode(args);
		if (i + 1 == max)
			return output;
	}
	
	return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> GeoHashObject::Test1M_DecodeBBox(const v8::Arguments& args) {
  v8::HandleScope scope;

	for(int i = 0, max = 1000*1000; i < max; i++) {
		v8::Handle<v8::Value> output = DecodeBBox(args);
		if (i + 1 == max)
			return output;
	}
	
	return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> GeoHashObject::Test1M_Neighbor(const v8::Arguments& args) {
  v8::HandleScope scope;

	for(int i = 0, max = 1000*1000; i < max; i++) {
		v8::Handle<v8::Value> output = Neighbor(args);
		if (i + 1 == max)
			return output;
	}
	
	return scope.Close(v8::Undefined());
}

