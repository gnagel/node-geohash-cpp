#include <v8.h>
#include <node.h>
#include <iostream>
#include "cvv8/detail/convert_core.hpp"

#include "geohash.hpp"
#include "geohash_node_binding.hpp"
// #include <v8-profiler.h>

#define _THROW_NODE_ERROR(MSG) ThrowException(v8::Exception::Error(v8::String::New(MSG)));


namespace geohash {

	// Node.JS Hooks to GeoHash encoding
	v8::Handle<v8::Value> test1m_encode_js(const v8::Arguments& args) {
	    v8::HandleScope scope;

			// 	    if (args.Length() < 2) {
			// 	        return _THROW_NODE_ERROR("Takes 3 parameters: latitude, longitude, and numberOfChars");
			// 	    }
			// 
			// const double latitude           = cvv8::CastFromJS< double >(args[0]);
			// const double longitude          = cvv8::CastFromJS< double >(args[1]);
			// const uint32_t numberOfChars    = args.Length() == 3 
			// 	? cvv8::CastFromJS< uint32_t >(args[2])
			// 		: 9; // Default input

			// v8::Handle<v8::String> title(v8::String::New("test1m_encode_js"));
			// v8::CpuProfiler::StartProfiling(title);

			const uint64_t _nanoseconds = nanoseconds();
			for(int i = 0, max = 1000*1000; i < max;  i++) {
		    encode(37.8324, 112.5584, 9);
			}
			const uint64_t _diff = nanoseconds() - _nanoseconds;
			const double   _seconds = ((double) _diff) / ((uint64_t) 1e9);
			
			std::cout << "test1m_encode_js = " << _seconds << std::endl;
			return scope.Close(cvv8::CastToJS<double>(_seconds));
			
			// const v8::CpuProfile* profile = v8::CpuProfiler::StopProfiling(title);
			// double milliseconds = profile->GetTopDownRoot()->GetTotalTime();
			// 
			// std::cout << "test1m_encode_js = " << _seconds << " vs " << milliseconds << std::endl;
			// 
			// return scope.Close(cvv8::CastToJS<double>(milliseconds));
			//   // return scope.Close(Profile::New(profile));
	}

	v8::Handle<v8::Value> test1m_decode_js(const v8::Arguments& args) {
	    v8::HandleScope scope;

	    if (args.Length() < 1) {
	        return _THROW_NODE_ERROR("Takes 1 parameters: hash_string");
	    }

			const std::string hash_string = cvv8::CastFromJS<std::string>(args[0]);
      if (hash_string.empty()) {
          return _THROW_NODE_ERROR("Parameter 0 must be a valid string");
      }

			const uint64_t _nanoseconds = nanoseconds();
			for(int i = 0, max = 1000*1000; i < max;  i++) {
		    decode(hash_string);
			}
			const uint64_t _diff = nanoseconds() - _nanoseconds;
			const double   _seconds = ((double) _diff) / ((uint64_t) 1e9);
			return scope.Close(cvv8::CastToJS<double>(_seconds));
	}
	
	v8::Handle<v8::Value> test1m_decode_bbox_js(const v8::Arguments& args) {
    v8::HandleScope scope;

    if (args.Length() < 1) {
        return _THROW_NODE_ERROR("Takes 1 parameters: hash_string");
    }

		const std::string hash_string = cvv8::CastFromJS<std::string>(args[0]);
    if (hash_string.empty()) {
        return _THROW_NODE_ERROR("Parameter 0 must be a valid string");
    }

		const uint64_t _nanoseconds = nanoseconds();
		for(int i = 0, max = 1000*1000; i < max;  i++) {
	    decode_bbox(hash_string);
		}
		const uint64_t _diff = nanoseconds() - _nanoseconds;
		const double   _seconds = ((double) _diff) / ((uint64_t) 1e9);
		return scope.Close(cvv8::CastToJS<double>(_seconds));
	}

	v8::Handle<v8::Value> test1m_neighbor_js(const v8::Arguments& args) {
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

			const uint64_t _nanoseconds = nanoseconds();
			for(int i = 0, max = 1000*1000; i < max;  i++) {
				neighbor(hash_string, directions_array);
			}
			const uint64_t _diff = nanoseconds() - _nanoseconds;
			const double   _seconds = ((double) _diff) / ((uint64_t) 1e9);
			return scope.Close(cvv8::CastToJS<double>(_seconds));
	}

	void test1m_Init(v8::Handle<v8::Object> target) {
    node::SetMethod(target, "test1m_encode_js",      geohash::test1m_encode_js);
    node::SetMethod(target, "test1m_decode_js",      geohash::test1m_decode_js);
    node::SetMethod(target, "test1m_decode_bbox_js", geohash::test1m_decode_bbox_js);
    node::SetMethod(target, "test1m_neighbor_js",    geohash::test1m_neighbor_js);
	}

}
