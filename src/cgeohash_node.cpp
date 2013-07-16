#include "cgeohash_requires_params.hpp"
#include "cgeohash.hpp"
#include "cgeohash_node.hpp"

namespace cgeohash
{

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(3);
    REQUIRES_PARAM_IS_NUMBER(0);
    REQUIRES_PARAM_IS_NUMBER(1);
    REQUIRES_PARAM_IS_NUMBER(2);

    int i = 0;
    const double   latitude  = cvv8::CastFromJS< double >(args[i++]);
    const double   longitude = cvv8::CastFromJS< double >(args[i++]);
    const uint32_t precision = cvv8::CastFromJS< uint32_t >(args[i++]);

    string_type output;
        output = encode(latitude, longitude, precision);

    return scope.Close(cvv8::CastToJS<string_type>(output));
}

// Node.JS Hooks to GeoHash encoding
v8::Handle<v8::Value> encode_all_precisions_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(2);
    REQUIRES_PARAM_IS_NUMBER(0);
    REQUIRES_PARAM_IS_NUMBER(1);

    int i = 0;
    const double latitude  = cvv8::CastFromJS< double >(args[i++]);
    const double longitude = cvv8::CastFromJS< double >(args[i++]);

    string_vector output;
    encode_all_precisions(latitude, longitude, output);

    return scope.Close(cvv8::CastToJS<string_vector>(output));
}

v8::Handle<v8::Value> decode_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(1);
    REQUIRES_PARAM_IS_STRING(0);

    int i = 0;
    const string_type hash_string = cvv8::CastFromJS<string_type>(args[i++]);
		REQUIRES_STRING_IS_NOT_EMPTY(0, hash_string);

    const DecodedHash decoded_hash = decode(hash_string);

    // Return:
    // {
    //   latitude:lat,
    //   longitude:lon,
    //   error:{latitude:laterr, longitude:lonerr}
    // }
    v8::Handle<v8::Object> error(v8::Object::New());
    error->Set(
        v8::String::New("latitude"),
        v8::Number::New(decoded_hash.latitude_err) );
    error->Set(
        v8::String::New("longitude"),
        v8::Number::New(decoded_hash.longitude_err) );

    v8::Handle<v8::Object> output(v8::Object::New());
    output->Set(
        v8::String::New("latitude"), v8::Number::New(decoded_hash.latitude) );
    output->Set( v8::String::New("longitude"), v8::Number::New(decoded_hash.longitude) );
    output->Set( v8::String::New("error"), error );

    return scope.Close(output);
}

v8::Handle<v8::Value> decode_bbox_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(1);
    REQUIRES_PARAM_IS_STRING(0);

    int i = 0;
    const string_type hash_string = cvv8::CastFromJS<string_type>(args[i++]);
		REQUIRES_STRING_IS_NOT_EMPTY(0, hash_string);

    DecodedBBox decoded_bbox = decode_bbox(hash_string);
    std::list<double> list;
    list.push_back(decoded_bbox.minlat);
    list.push_back(decoded_bbox.minlon);
    list.push_back(decoded_bbox.maxlat);
    list.push_back(decoded_bbox.maxlon);

    return scope.Close(cvv8::CastToJS< std::list<double> >(list));
}

v8::Handle<v8::Value> neighbor_fn(const v8::Arguments& args)
{
    v8::HandleScope scope;
    REQUIRES_PARAM_LENGTH(2);
    REQUIRES_PARAM_IS_STRING(0);
    REQUIRES_PARAM_IS_ARRAY(1);

    int i = 0;
    const string_type hash_string = cvv8::CastFromJS<string_type>(args[i++]);
    const int_vector  directions  = cvv8::CastFromJS< int_vector >(args[i++]);
		REQUIRES_STRING_IS_NOT_EMPTY(0, hash_string);
    if (directions.size() != 2) {
        return THROW_EXCEPTION("Parameter 1 must be an array with 2 numbers");
    }

    const int directions_array []        = {
        directions.front(), // Only 2 elements
        directions.back()   // Only 2 elements
    };
    const string_type neighbor_string = neighbor(hash_string, directions_array);

    return scope.Close(cvv8::CastToJS<string_type>(neighbor_string));
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

NODE_MODULE(cgeohash, cgeohash::RegisterModule);


