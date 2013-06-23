#include <v8.h>
#include <node.h>

#include "cgeohash_fn.hpp"
#include "cgeohash_obj.hpp"

#define _THROW_NODE_ERROR(MSG) ThrowException(v8::Exception::Error(v8::String::New(MSG)));

namespace cgeohash {

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
    NODE_SET_PROTOTYPE_METHOD(constructor, "encode_obj",      Encode);
    NODE_SET_PROTOTYPE_METHOD(constructor, "decode_obj",      Decode);
    NODE_SET_PROTOTYPE_METHOD(constructor, "decode_bbox_obj", DecodeBBox);
    NODE_SET_PROTOTYPE_METHOD(constructor, "neighbor_obj",    Neighbor);


    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}


GeoHashObject::GeoHashObject() : node::ObjectWrap() {
}


v8::Handle<v8::Value> GeoHashObject::New(const v8::Arguments& args) {
    v8::HandleScope scope;

    if (!args.IsConstructCall()) {
        return _THROW_NODE_ERROR("Use the new operator to create instances of this object.");
    }

    // Creates a new instance object of this type and wraps it.
    GeoHashObject* obj = new GeoHashObject();
    obj->Wrap(args.This());

    return args.This();
}


v8::Handle<v8::Value> GeoHashObject::Encode(const v8::Arguments& args) {
	return encode_fn(args);
}


v8::Handle<v8::Value> GeoHashObject::Decode(const v8::Arguments& args) {
	return decode_fn(args);
}


v8::Handle<v8::Value> GeoHashObject::DecodeBBox(const v8::Arguments& args) {
	return decode_bbox_fn(args);
}


v8::Handle<v8::Value> GeoHashObject::Neighbor(const v8::Arguments& args) {
	return neighbor_fn(args);
}

}