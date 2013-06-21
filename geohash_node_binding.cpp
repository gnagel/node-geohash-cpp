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

	    if (args.Length() < 3) {
	        return _THROW_NODE_ERROR("Takes 3 parameters: latitude, longitude, and numberOfChars");
	    }

	    for(int i = 0, max = args.Length(); i < max; i++) {
	        if (args[i].IsEmpty() || !args[i]->IsNumber()) {
	            return _THROW_NODE_ERROR("All parameters must be numbers");
	        }
	    }

	    double latitude             = args[0]->NumberValue();
	    double longitude            = args[1]->NumberValue();
	    unsigned long numberOfChars = args[2]->NumberValue();

	    const std::string hash_string = encode(latitude, longitude, numberOfChars);

		  // Use .data() instead of .c_str() here
	    char const * const cstr  = hash_string.data();
	    v8::Handle<v8::String> output(
	        cstr
	        ? v8::String::New( cstr, static_cast<int>( hash_string.size() ) )
	        : v8::String::New("",0)
	    );

	    return scope.Close(output);
	}

	v8::Handle<v8::Value> decode_js(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 1) {
	        return _THROW_NODE_ERROR("Takes 1 parameters: hash_string");
	    }

	    for(int i = 0, max = args.Length(); i < max; i++) {
	        if (args[i].IsEmpty() || !args[i]->IsString()) {
	            return _THROW_NODE_ERROR("All parameters must be strings");
	        }
	    }

	    v8::String::Utf8Value utf8_string(args[0]);
			const char*           utf8_char = *utf8_string;
			const std::string hash_string = utf8_char
				? std::string(*utf8_string, utf8_string.length())
					: "";

	    DecodedHash decoded_hash = decode(hash_string);

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
	
	}

	v8::Handle<v8::Value> neighbor_js(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 3) {
	        return _THROW_NODE_ERROR("Takes 2 parameters: hash_string, and direction []");
	    }

			const std::string hash_string = cvv8::CastFromJS<std::string>(args[0]);
      if (hash_string.empty()) {
          return _THROW_NODE_ERROR("Parameter 0 must be a string");
      }

			const std::list<uint32_t> directions = cvv8::CastFromJS<uint32_t>(directions_array);
			if (directions.size() != 2) {
          return _THROW_NODE_ERROR("Parameter 1 must be an array with 2 numbers");
      }

			const std::string hash_string        = cvv8::CastFromJS<std::string>(args[0]);
			const std::string neighbor_string    = neighbor(hash_string, [directions[0], directions[1]]);

	    return scope.Close(CastToJS<std::string>(neighbor_string));
	}
}
