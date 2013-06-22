#include <v8.h>
#include <node.h>

#include "cgeohash_obj_repeaters.hpp"
#include "cgeohash_fn_repeaters.hpp"

#define _THROW_NODE_ERROR(MSG) ThrowException(v8::Exception::Error(v8::String::New(MSG)));

namespace cgeohash {

v8::Persistent<v8::FunctionTemplate> GeoHashObjectRepeater::constructor;


void GeoHashObjectRepeater::Init(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
    v8::Local<v8::String>           name = v8::String::NewSymbol("GeoHashObjectRepeater");

    constructor = v8::Persistent<v8::FunctionTemplate>::New(tpl);

    // ObjectWrap uses the first internal field to store the wrapped pointer.
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    NODE_SET_PROTOTYPE_METHOD(constructor, "encode_obj_repeater",      Encode);
    NODE_SET_PROTOTYPE_METHOD(constructor, "decode_obj_repeater",      Decode);
    NODE_SET_PROTOTYPE_METHOD(constructor, "decode_bbox_obj_repeater", DecodeBBox);
    NODE_SET_PROTOTYPE_METHOD(constructor, "neighbor_obj_repeater",    Neighbor);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}


GeoHashObjectRepeater::GeoHashObjectRepeater() : node::ObjectWrap() {
}


v8::Handle<v8::Value> GeoHashObjectRepeater::New(const v8::Arguments& args) {
    v8::HandleScope scope;

    if (!args.IsConstructCall()) {
        return _THROW_NODE_ERROR("Use the new operator to create instances of this object.");
    }

    // Creates a new instance object of this type and wraps it.
    GeoHashObjectRepeater* obj = new GeoHashObjectRepeater();
    obj->Wrap(args.This());

    return args.This();
}


v8::Handle<v8::Value> GeoHashObjectRepeater::Encode(const v8::Arguments& args) {
	return geohash::encode_fn_repeater(args);
}


v8::Handle<v8::Value> GeoHashObjectRepeater::Decode(const v8::Arguments& args) {
	return geohash::decode_fn_repeater(args);
}


v8::Handle<v8::Value> GeoHashObjectRepeater::DecodeBBox(const v8::Arguments& args) {
	return geohash::decode_bbox_fn_repeater(args);
}


v8::Handle<v8::Value> GeoHashObjectRepeater::Neighbor(const v8::Arguments& args) {
	return geohash::neighbor_fn_repeater(args);
}
