#include <v8.h>
#include <node.h>

#include "cgeohash.hpp"
#include "cgeohash_fn.hpp"
#include "cgeohash_obj.hpp"

#include "cgeohash_fn_repeaters.hpp"
#include "cgeohash_obj_repeaters.hpp"

void RegisterModule(v8::Handle<v8::Object> target) {
    cgeohash::GeoHashObject::Init(target);
    cgeohash::register_node_fns(target);

    cgeohash::GeoHashObjectRepeater::Init(target);
    cgeohash::register_node_fn_repeaters(target);
}

NODE_MODULE(cgeohash_speed_tests, RegisterModule);
