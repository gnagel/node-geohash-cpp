#ifndef _NODE_GEOHASH_HPP
#define _NODE_GEOHASH_HPP

#include <node.h>
#include <string>

namespace geohash {
struct DecodedBBox {
    double minlat, minlon, maxlat, maxlon;
};

struct DecodedHash {
    double latitude;
    double longitude;

    double latitude_err;
    double longitude_err;
};

uint64_t nanoseconds();

std::string encode(const double latitude, const double longitude, const unsigned long numberOfChars);

DecodedHash decode(const std::string & hash_string);

DecodedBBox decode_bbox(const std::string & hash_string);


/**
 * direction [lat, lon], i.e.
 * [1,0] - north
 * [1,1] - northeast
 * ...
 */
std::string neighbor(const std::string & hash_string, const int direction []);

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_js(const v8::Arguments& args);
v8::Handle<v8::Value> decode_js(const v8::Arguments& args);
v8::Handle<v8::Value> decode_bbox_js(const v8::Arguments& args);
v8::Handle<v8::Value> neighbor_js(const v8::Arguments& args);
}

#endif /* geohash.hpp */
