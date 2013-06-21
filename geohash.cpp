#include <node.h>
#include <cstdlib>
#include <iostream>

#include "geohash.hpp"

using namespace std;


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

	
	std::string encode(const double latitude, const double longitude, int numberOfChars) {
		DecodedBBox bbox;
	    bbox.maxlat = 90;
	    bbox.maxlon = 180;
		bbox.minlat = -90;
		bbox.minlon = -180;

		// Default to 9 characters
		numberOfChars = numberOfChars >= 1 ? numberOfChars : 9;

	    var chars = [], bits = 0;
	    var hash_value = 0;

	    var mid;
	    var islon = true;
	    while(chars.length < numberOfChars) {
	        if (islon){
	            mid = (bbox.maxlon+bbox.minlon)/2;
	            if(longitude > mid){
	                hash_value = (hash_value << 1) + 1;
	                bbox.minlon=mid;
	            } else {
	                hash_value = (hash_value << 1) + 0;
	                bbox.maxlon=mid;
	            }
	        } else {
	            mid = (bbox.maxlat+bbox.minlat)/2;
	            if(latitude > mid ){
	                hash_value = (hash_value << 1) + 1;
	                bbox.minlat = mid;
	            } else {
	                hash_value = (hash_value << 1) + 0;
	                bbox.maxlat = mid;
	            }
	        }
	        islon = !islon;

	        bits++;
	        if (bits == 5) {
	            var code = BASE32_CODES[hash_value];
	            chars.push(code);
	            bits = 0;
	            hash_value = 0;
	        } 
	    }
	    return chars.join('')
	};


	DecodedBBox decode_bbox(const std::string & hash_string) {
		DecodedBBox output;
	    output.maxlat = 90;
	    output.maxlon = 180;
		output.minlat = -90;
		output.minlon = -180;

	    double hash_value = 0;
		bool islon = true;
	    for(int i = 0, max = hash_string.size(); i < max; i++) {
	        var code = hash_string[i].toLowerCase();
	        hash_value = BASE32_CODES_DICT[code];

	        for (int bits = 4; bits >= 0; --bits) {
	            int bit = (hash_value >> bits) & 1;
	            if (islon) {
	                double mid = (maxlon + minlon)/2;
	                if(bit == 1){
						output.minlon = mid;
	                } else {
	                    output.maxlon = mid;
	                }
	            } else {
	                double mid = (maxlat+minlat)/2;
	                if(bit == 1){
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



   /**
    * direction [lat, lon], i.e.
    * [1,0] - north
    * [1,1] - northeast
    * ...
    */
   std::string neighbor(const std::string & hash_string, const direction []) {
	   // Adjust the DecodedHash for the direction of the neighbors
       DecodedHash lonlat = decode(hash_string);
	   lonlat.latitude   += direction[0] * lonlat.latitude_err * 2;
       lonlat.longitude  += direction[1] * lonlat.longitude_err * 2;

       return encode(latitude, longitude, hash_string.length);
   }

	// Node.JS Hooks to GeoHash encoding
	v8::Handle<v8::Value> encode_js(const v8::Arguments& args);
	v8::Handle<v8::Value> decode_js(const v8::Arguments& args);
	v8::Handle<v8::Value> decode_bbox_js(const v8::Arguments& args);
	v8::Handle<v8::Value> neighbor_js(const v8::Arguments& args);
}
