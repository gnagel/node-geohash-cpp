#include <node.h>
#include <uv.h>
#include <v8.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "geohash.hpp"


namespace geohash {
#define NANOSEC ((uint64_t) 1e9)
	
	uint64_t nanoseconds() {
		uint64_t _nanoseconds = uv_hrtime();
		// std::cout << "nanoseconds=" << _nanoseconds << std::endl;
		return _nanoseconds;
	}

const char base32_codes[] = {
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'b',
	'c',
	'd',
	'e',
	'f',
	'g',
	'h',
	'j',
	'k',
	'm',
	'n',
	'p',
	'q',
	'r',
	's',
	't',
	'u',
	'v',
	'w',
	'x',
	'y',
	'z'};

std::string encode(const double latitude, const double longitude, unsigned long numberOfChars) {
    // DecodedBBox for the lat/lon + errors
    DecodedBBox bbox;
    bbox.maxlat = 90;
    bbox.maxlon = 180;
    bbox.minlat = -90;
    bbox.minlon = -180;
    double mid        = 0;
    bool   islon      = true;
    int    num_bits   = 0;
    int    hash_index = 0;

    std::string hash_string(numberOfChars, ' ');
		// hash_string.reserve(numberOfChars);
		unsigned int hash_string_length = 0;

    while(hash_string_length< numberOfChars) {
        if (islon) {
            mid = (bbox.maxlon + bbox.minlon) / 2;
            if(longitude > mid) {
                hash_index = (hash_index << 1) + 1;
                bbox.minlon=mid;
            } else {
                hash_index = (hash_index << 1) + 0;
                bbox.maxlon=mid;
            }
        } else {
            mid = (bbox.maxlat + bbox.minlat) / 2;
            if(latitude > mid ) {
                hash_index = (hash_index << 1) + 1;
                bbox.minlat = mid;
            } else {
                hash_index = (hash_index << 1) + 0;
                bbox.maxlat = mid;
            }
        }
        islon = !islon;

        ++num_bits;
        if (5 == num_bits) {
					char c = base32_codes[hash_index];
					// hash_string.push_back(c);
					hash_string[hash_string_length] = c;
					hash_string_length++;
					num_bits   = 0;
            hash_index = 0;
        }
    }
		
    return hash_string;
};

DecodedBBox decode_bbox(const std::string & _hash_string) {
    // Copy of the string down-cased
    // Wish this was ruby, then it would be simple: _hash_string.downcase();
    std::string hash_string(_hash_string);
    std::transform(
        _hash_string.begin(),
        _hash_string.end(),
        hash_string.begin(),
        ::tolower);

    DecodedBBox output;
    output.maxlat = 90;
    output.maxlon = 180;
    output.minlat = -90;
    output.minlon = -180;

    int char_index = 0;
    bool islon = true;
    // const std::string base32_codes = "0123456789bcdefghjkmnpqrstuvwxyz";

    for(int i = 0, max = hash_string.length(); i < max; i++) {
			char c = hash_string[i];
			if (c >= '0' && c <= '9') {
				char_index = base32_codes[c - '0'];
			} else {
				char_index = base32_codes[c - 'a'];
			}
        // char_index = base32_codes.find( hash_string[i] );

        for (int bits = 4; bits >= 0; --bits) {
            int bit = (char_index >> bits) & 1;
            if (islon) {
                double mid = (output.maxlon + output.minlon) / 2;
                if(bit == 1) {
                    output.minlon = mid;
                } else {
                    output.maxlon = mid;
                }
            } else {
                double mid = (output.maxlat + output.minlat) / 2;
                if(bit == 1) {
                    output.minlat = mid;
                } else {
                    output.maxlat = mid;
                }
            }
            islon = !islon;
        }
    }
    return output;
}

DecodedHash decode(const std::string & hash_string) {
    DecodedBBox bbox = decode_bbox(hash_string);
    DecodedHash output;
    output.latitude      = (bbox.minlat + bbox.maxlat) / 2;
    output.longitude     = (bbox.minlon + bbox.maxlon) / 2;
    output.latitude_err  = bbox.maxlat - output.latitude;
    output.longitude_err = bbox.maxlon - output.longitude;
    return output;
};

std::string neighbor(const std::string & hash_string, const int direction []) {
    // Adjust the DecodedHash for the direction of the neighbors
    DecodedHash lonlat = decode(hash_string);
    lonlat.latitude   += direction[0] * lonlat.latitude_err * 2;
    lonlat.longitude  += direction[1] * lonlat.longitude_err * 2;

    return encode(
               lonlat.latitude,
               lonlat.longitude,
               hash_string.length());
}

} // end namespace geohash
