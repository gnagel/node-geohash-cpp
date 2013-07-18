#ifndef _NODE_CGEOHASH_HPP
#define _NODE_CGEOHASH_HPP

#include <node.h>
#include <string>
#include <vector>

namespace cgeohash
{
typedef std::string string_type;
typedef std::vector<string_type> string_vector;

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
void encode(const double latitude, const double longitude, const unsigned long precision, string_type & output);

// Encode a pair of latitude and longitude into geohash
// All Precisions from [1 to 9] (inclusive)
void encode_all_precisions(
    const double latitude,
    const double longitude,
    std::vector<std::string> & output);

// Encode a pair of latitude and longitude into geohash
// All Precisions from [min to max] (inclusive)
void encode_range_precisions(
    const double latitude,
    const double longitude,
    const size_t min,
    const size_t max,
    std::vector<string_type> & output);


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
