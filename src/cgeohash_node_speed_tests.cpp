#include "cgeohash_requires_params.hpp"
#include "cgeohash.hpp"
#include "cgeohash_node.hpp"

namespace cgeohash
{

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(4);
    REQUIRES_PARAM_IS_NUMBER(0);
    REQUIRES_PARAM_IS_NUMBER(1);
    REQUIRES_PARAM_IS_NUMBER(2);
    REQUIRES_PARAM_IS_NUMBER(3);

    int i = 0;
    const double   latitude  = cvv8::CastFromJS< double >(args[i++]);
    const double   longitude = cvv8::CastFromJS< double >(args[i++]);
    const uint32_t precision = cvv8::CastFromJS< uint32_t >(args[i++]);
    const size_t   num_times = cvv8::CastFromJS< size_t >(args[i++]);

    string_type output;
    for(size_t i = 0; i < num_times; ++i) {
        output = encode(latitude, longitude, precision);
    }

    return scope.Close(cvv8::CastToJS<string_type>(output));
}

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_all_precisions_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(3);
    REQUIRES_PARAM_IS_NUMBER(0);
    REQUIRES_PARAM_IS_NUMBER(1);
    REQUIRES_PARAM_IS_NUMBER(2);

    int i = 0;
    const double latitude  = cvv8::CastFromJS< double >(args[i++]);
    const double longitude = cvv8::CastFromJS< double >(args[i++]);
    const size_t num_times = cvv8::CastFromJS< size_t >(args[i++]);

    string_vector output;
    for(size_t i = 0; i < num_times; ++i) {
        encode_all_precisions(latitude, longitude, output);
    }

    return scope.Close(cvv8::CastToJS<string_vector>(output));
}

v8::Handle<v8::Value> decode_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(2);
    REQUIRES_PARAM_IS_STRING(0);
    REQUIRES_PARAM_IS_NUMBER(1);

    int i = 0;
    const string_type hash_string = cvv8::CastFromJS<string_type>(args[i++]);
    const size_t      num_times = cvv8::CastFromJS< size_t >(args[i++]);
    REQUIRES_STRING_IS_NOT_EMPTY(0, hash_string);

    DecodedHash output;
    for(size_t i = 0; i < num_times; ++i) {
        output = decode(hash_string);
    }

    // Return:
    // {
    //   latitude:lat,
    //   longitude:lon,
    //   error:{latitude:laterr, longitude:lonerr}
    // }
    v8::Handle<v8::Object> error(v8::Object::New());
    error->Set(
        v8::String::New("latitude"),
        v8::Number::New(output.latitude_err) );
    error->Set(
        v8::String::New("longitude"),
        v8::Number::New(output.longitude_err) );

    v8::Handle<v8::Object> buffer(v8::Object::New());
    buffer->Set(
        v8::String::New("latitude"), v8::Number::New(output.latitude) );
    buffer->Set( v8::String::New("longitude"), v8::Number::New(output.longitude) );
    buffer->Set( v8::String::New("error"), error );

    return scope.Close(buffer);
}

v8::Handle<v8::Value> decode_bbox_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(2);
    REQUIRES_PARAM_IS_STRING(0);
    REQUIRES_PARAM_IS_NUMBER(1);

    int i = 0;
    const string_type hash_string = cvv8::CastFromJS<string_type>(args[i++]);
    const size_t      num_times   = cvv8::CastFromJS< size_t >(args[i++]);

    REQUIRES_STRING_IS_NOT_EMPTY(0, hash_string);

    DecodedBBox output;
    for(size_t i = 0; i < num_times; ++i) {
        output = decode_bbox(hash_string);
    }

    double_vector buffer(4);
    buffer.push_back(output.minlat);
    buffer.push_back(output.minlon);
    buffer.push_back(output.maxlat);
    buffer.push_back(output.maxlon);

    return scope.Close(cvv8::CastToJS<double_vector>(buffer));
}

v8::Handle<v8::Value> neighbor_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(3);
    REQUIRES_PARAM_IS_STRING(0);
    REQUIRES_PARAM_IS_ARRAY(1);
    REQUIRES_PARAM_IS_NUMBER(2);

    int i = 0;
    const string_type hash_string = cvv8::CastFromJS<string_type>(args[i++]);
    const int_vector  directions  = cvv8::CastFromJS< int_vector >(args[i++]);
    const size_t      num_times   = cvv8::CastFromJS< size_t >(args[i++]);

    REQUIRES_STRING_IS_NOT_EMPTY(0, hash_string);

    if (directions.size() != 2) {
        return THROW_EXCEPTION("Parameter 1 must be an array with 2 numbers");
    }

    const int directions_array [] = {
        directions.front(), // Only 2 elements
        directions.back()   // Only 2 elements
    };
    string_type output;
    for(size_t i = 0; i < num_times; ++i) {
        output = neighbor(hash_string, directions_array);
    }

    return scope.Close(cvv8::CastToJS<string_type>(output));
}

void RegisterModule(v8::Handle<v8::Object> target)
{
    node::SetMethod(target, "encode_fn",      encode_fn);
    node::SetMethod(target, "encode_all_precisions_fn",      encode_all_precisions_fn);
    node::SetMethod(target, "decode_fn",      decode_fn);
    node::SetMethod(target, "decode_bbox_fn", decode_bbox_fn);
    node::SetMethod(target, "neighbor_fn",    neighbor_fn);
}

}

NODE_MODULE(cgeohash_speed_tests, cgeohash::RegisterModule);


