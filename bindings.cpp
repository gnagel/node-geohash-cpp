#include <v8.h>
#include <node.h>

#include "geohash.hpp"

using namespace v8;
using namespace node;
using namespace geohash;


void RegisterModule(Handle<Object> target) {
    target->Set(v8::String::NewSymbol("encode_js"), v8::FunctionTemplate::New(encode_js)->GetFunction());

    target->Set(v8::String::NewSymbol("decode_js"), v8::FunctionTemplate::New(decode_js)->GetFunction());

    target->Set(v8::String::NewSymbol("decode_bbox_js"), v8::FunctionTemplate::New(decode_bbox_js)->GetFunction());

    target->Set(v8::String::NewSymbol("neighbor_js"), v8::FunctionTemplate::New(neighbor_js)->GetFunction());
}

NODE_MODULE(cgeohash, RegisterModule);
