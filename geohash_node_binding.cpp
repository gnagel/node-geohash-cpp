#include <v8.h>
#include <node.h>
#include "cvv8/detail/convert_core.hpp"

#include "geohash.hpp"
#include "geohash_node_binding.hpp"

#define _THROW_NODE_ERROR(MSG) ThrowException(v8::Exception::Error(v8::String::New(MSG)));


namespace geohash {

	// Node.JS Hooks to GeoHash encoding
	v8::Handle<v8::Value> encode_js(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 2) {
	        return _THROW_NODE_ERROR("Takes 3 parameters: latitude, longitude, and numberOfChars");
	    }

			const double latitude           = cvv8::CastFromJS< double >(args[0]);
			const double longitude          = cvv8::CastFromJS< double >(args[1]);
			const uint32_t numberOfChars    = args.Length() == 3 
				? cvv8::CastFromJS< uint32_t >(args[2])
					: 9; // Default input
	    const std::string hash_string = encode(latitude, longitude, numberOfChars);

	    return scope.Close(cvv8::CastToJS<std::string>(hash_string));
	}

	v8::Handle<v8::Value> decode_js(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 1) {
	        return _THROW_NODE_ERROR("Takes 1 parameters: hash_string");
	    }

			const std::string hash_string = cvv8::CastFromJS<std::string>(args[0]);
      if (hash_string.empty()) {
          return _THROW_NODE_ERROR("Parameter 0 must be a valid string");
      }

	    const DecodedHash decoded_hash = decode(hash_string);

	    // Return:
	    // {
	    //   latitude:lat,
	    //   longitude:lon,
	    //   error:{latitude:laterr, longitude:lonerr}
	    // }
	    v8::Handle<v8::Object> error(v8::Object::New());
	    error->Set( v8::String::New("latitude"), v8::Number::New(decoded_hash.latitude_err) );
	    error->Set( v8::String::New("longitude"), v8::Number::New(decoded_hash.longitude_err) );

	    v8::Handle<v8::Object> output(v8::Object::New());
	    output->Set( v8::String::New("latitude"), v8::Number::New(decoded_hash.latitude) );
	    output->Set( v8::String::New("longitude"), v8::Number::New(decoded_hash.longitude) );
	    output->Set( v8::String::New("error"), error );

	    return scope.Close(output);
	}
	
	v8::Handle<v8::Value> decode_bbox_js(const v8::Arguments& args) {
    v8::HandleScope scope;

    if (args.Length() < 1) {
        return _THROW_NODE_ERROR("Takes 1 parameters: hash_string");
    }

		const std::string hash_string = cvv8::CastFromJS<std::string>(args[0]);
    if (hash_string.empty()) {
        return _THROW_NODE_ERROR("Parameter 0 must be a valid string");
    }

    DecodedBBox decoded_bbox = decode_bbox(hash_string);
		std::list<double> list(4);
		list.push_back(decoded_bbox.minlat);
		list.push_back(decoded_bbox.minlon);
		list.push_back(decoded_bbox.maxlat);
		list.push_back(decoded_bbox.maxlon);
		
		return scope.Close(cvv8::CastToJS< std::list<double> >(list));
	}

	v8::Handle<v8::Value> neighbor_js(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 2) {
	        return _THROW_NODE_ERROR("Takes 2 parameters: hash_string, and direction []");
	    }

			const std::string hash_string = cvv8::CastFromJS<std::string>(args[0]);
      if (hash_string.empty()) {
          return _THROW_NODE_ERROR("Parameter 0 must be a valid string");
      }

			const std::list<uint32_t> directions = cvv8::CastFromJS< std::list<uint32_t> >(args[1]);
			if (directions.size() != 2) {
          return _THROW_NODE_ERROR("Parameter 1 must be an array with 2 numbers");
      }
			
			const int directions_array [] = {
				directions.front(), // Only 2 elements
				directions.back()   // Only 2 elements
			};
			const std::string neighbor_string = neighbor(hash_string, directions_array);

	    return scope.Close(cvv8::CastToJS<std::string>(neighbor_string));
	}
}


void geohash_Init(v8::Handle<v8::Object> target) {
  node::SetMethod(target, "encode_js",      geohash::encode_js);
  node::SetMethod(target, "decode_js",      geohash::decode_js);
  node::SetMethod(target, "decode_bbox_js", geohash::decode_bbox_js);
  node::SetMethod(target, "neighbor_js",    geohash::neighbor_js);
}
