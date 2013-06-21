#include <v8.h>
#include <node.h>

#include "geohash.hpp"
#include "geohash_node_binding.hpp"
#include "geohash_node_binding_speed.hpp"
#include "geohash_obj.hpp"

void RegisterModule(v8::Handle<v8::Object> target) {
    GeoHashObject::Init(target);
    geohash_Init(target);
    geohash::test1m_Init(target);
}

NODE_MODULE(cgeohash, RegisterModule);
