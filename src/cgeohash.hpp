#ifndef _NODE_CGEOHASH_HPP
#define _NODE_CGEOHASH_HPP

#include <node.h>
#include <string>

namespace cgeohash {

struct DecodedBBox {
    double minlat, minlon, maxlat, maxlon;
};

struct DecodedHash {
    double latitude;
    double longitude;

    double latitude_err;
    double longitude_err;
};

// Encode a pair of latitude and longitude into geohash
std::string encode(const double latitude, const double longitude, const unsigned long precision);

// Decode a hash string into pair of latitude and longitude
DecodedHash decode(const std::string & hash_string);

// Decode hashstring into a bound box matches it 
DecodedBBox decode_bbox(const std::string & hash_string);

// Find neighbor of a geohash string in certain direction.
// Direction is a two-element array:
// Ex: [ 1, 0] == north
// Ex: [-1,-1] == southwest
std::string neighbor(const std::string & hash_string, const int direction []);

} // end namespace cgeohash

#endif /* end hpp */
