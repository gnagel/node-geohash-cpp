#include <v8.h>
#include <node.h>
#include "../includes/cvv8/detail/convert_core.hpp"

#include "cgeohash.hpp"
#include "cgeohash_fn_repeaters.hpp"
#include "cgeohash_nanoseconds.hpp"

#include <iostream>

#define _THROW_NODE_ERROR(MSG) ThrowException(v8::Exception::Error(v8::String::New(MSG)));


namespace cgeohash {

	// Node.JS Hooks to GeoHash encoding
	v8::Handle<v8::Value> encode_fn_repeater(const v8::Arguments& args) {
	    v8::HandleScope scope;

			for(int i = 0; i < 1e6;  i++) {
				encode(37.8324, 112.5584, 9);
			}
			
			return scope.Close(v8::Undefined());
	}

	v8::Handle<v8::Value> decode_fn_repeater(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 2) {
	        return _THROW_NODE_ERROR("Takes 1 parameters: num_times, hash_string");
	    }

		int i = 0;
		const int num_times = cvv8::CastFromJS< int >(args[i++]);
			const std::string hash_string = cvv8::CastFromJS<std::string>(args[i++]);
      if (hash_string.empty()) {
          return _THROW_NODE_ERROR("Parameter 0 must be a valid string");
      }

			const uint64_t _nanoseconds = nanoseconds();
			for(int i = 0; i < num_times;  i++) {
				// std::cout << __FILE__ << ':' << __LINE__ << '=' << i << std::endl;
		    decode(hash_string);
			}
			return scope.Close(cvv8::CastToJS<uint64_t>((nanoseconds() - _nanoseconds) / num_times));
			// const double   _seconds = seconds_differience_of_nanoseconds(_nanoseconds) / num_times;
			// return scope.Close(cvv8::CastToJS<double>(_seconds));
	}
	
	v8::Handle<v8::Value> decode_bbox_fn_repeater(const v8::Arguments& args) {
    v8::HandleScope scope;

    if (args.Length() < 2) {
        return _THROW_NODE_ERROR("Takes 1 parameters: num_times, hash_string");
    }

	int i = 0;
	const int num_times = cvv8::CastFromJS< int >(args[i++]);
		const std::string hash_string = cvv8::CastFromJS<std::string>(args[i++]);
    if (hash_string.empty()) {
        return _THROW_NODE_ERROR("Parameter 1 must be a valid string");
    }

		const uint64_t _nanoseconds = nanoseconds();
		for(int i = 0; i < num_times;  i++) {
			// std::cout << __FILE__ << ':' << __LINE__ << '=' << i << std::endl;
	    decode_bbox(hash_string);
		}
		return scope.Close(cvv8::CastToJS<uint64_t>((nanoseconds() - _nanoseconds) / num_times));
		// const double   _seconds = seconds_differience_of_nanoseconds(_nanoseconds) / num_times;
		// return scope.Close(cvv8::CastToJS<double>(_seconds));
	}

	v8::Handle<v8::Value> neighbor_fn_repeater(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 3) {
	        return _THROW_NODE_ERROR("Takes 3 parameters: num_times, hash_string, and direction []");
	    }

		int i = 0;
		const int num_times = cvv8::CastFromJS< int >(args[i++]);
			const std::string hash_string = cvv8::CastFromJS<std::string>(args[i++]);
      if (hash_string.empty()) {
          return _THROW_NODE_ERROR("Parameter 1 must be a valid string");
      }

			const std::list<uint32_t> directions = cvv8::CastFromJS< std::list<uint32_t> >(args[i++]);
			if (directions.size() != 2) {
          return _THROW_NODE_ERROR("Parameter 2 must be an array with 2 numbers");
      }
			
			const int directions_array [] = {
				directions.front(), // Only 2 elements
				directions.back()   // Only 2 elements
			};

			const uint64_t _nanoseconds = nanoseconds();
			for(int i = 0; i < num_times;  i++) {
				// std::cout << __FILE__ << ':' << __LINE__ << '=' << i << std::endl;
				neighbor(hash_string, directions_array);
			}
			return scope.Close(cvv8::CastToJS<uint64_t>((nanoseconds() - _nanoseconds) / num_times));
			// const double   _seconds = seconds_differience_of_nanoseconds(_nanoseconds) / num_times;
			// return scope.Close(cvv8::CastToJS<double>(_seconds));
	}

	void register_node_fn_repeaters(v8::Handle<v8::Object> target) {
    node::SetMethod(target, "encode_fn_repeater",      encode_fn_repeater);
    node::SetMethod(target, "decode_fn_repeater",      decode_fn_repeater);
    node::SetMethod(target, "decode_bbox_fn_repeater", decode_bbox_fn_repeater);
    node::SetMethod(target, "neighbor_fn_repeater",    neighbor_fn_repeater);
	}

}
