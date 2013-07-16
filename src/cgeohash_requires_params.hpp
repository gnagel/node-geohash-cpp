#ifndef _NODE_CGEOHASH_REQUIRES_PARAMS_HPP
#define _NODE_CGEOHASH_REQUIRES_PARAMS_HPP

#include <node.h>
#include <v8.h>
#include <cvv8/convert.hpp>

#include <string>
#include <set>
#include <map>
#include <list>
#include <vector>


namespace cgeohash
{
typedef std::string string_type;
typedef std::vector<string_type> string_vector;

typedef std::list<double> double_list;
typedef std::vector<double> double_vector;

#define UNWRAP_THIS(TYPE) node::ObjectWrap::Unwrap<TYPE>(args.This());
#define UNWRAP_PARAM_OBJECT(TYPE, INDEX) node::ObjectWrap::Unwrap<TYPE>(args[INDEX]->ToObject());

#define REQUIRES_CONSTRUCTOR_CALL() \
	if (!args.IsConstructCall()) { \
    return ThrowException(v8::Exception::Error(v8::String::New("Use the new operator to create instances of this object."))); \
}

#define REQUIRES_PARAM_LENGTH(LENGTH) \
  if (run_utils::ArgsLengthIsNot(args, LENGTH)) { \
			std::ostringstream msg; \
			msg << __FILE__ << ":" << __LINE__ << " @ "; \
			msg << "Requires " << LENGTH << " parameters, not " << args.Length(); string_type msg_value = msg.str(); \
      return ThrowException(v8::Exception::Error(v8::String::New(msg_value.c_str()))); \
  }

#define REQUIRES_PARAM_IS_STRING(INDEX) \
  if (run_utils::ArgsIsNotString(args, INDEX)) { \
		std::ostringstream msg; \
		msg << __FILE__ << ":" << __LINE__ << " @ "; \
		msg << run_utils::BuildArgsTypeError(args, INDEX, "string");\
		string_type msg_value = msg.str(); \
    return ThrowException(v8::Exception::Error(v8::String::New(msg_value.c_str()))); \
  }

#define REQUIRES_PARAM_IS_ARRAY(INDEX) \
  if (run_utils::ArgsIsNotArray(args, INDEX)) { \
		std::ostringstream msg; \
		msg << __FILE__ << ":" << __LINE__ << " @ "; \
		msg << run_utils::BuildArgsTypeError(args, INDEX, "array");\
			string_type msg_value = msg.str(); \
    return ThrowException(v8::Exception::Error(v8::String::New(msg_value.c_str()))); \
  }

#define REQUIRES_PARAM_IS_NUMBER(INDEX) \
  if (run_utils::ArgsIsNotNumber(args, INDEX)) { \
		std::ostringstream msg; \
		msg << __FILE__ << ":" << __LINE__ << " @ "; \
		msg << run_utils::BuildArgsTypeError(args, INDEX, "number");\
			string_type msg_value = msg.str(); \
    return ThrowException(v8::Exception::Error(v8::String::New(msg_value.c_str()))); \
  }

#define REQUIRES_PARAM_IS_OBJECT(INDEX) \
  if (run_utils::ArgsIsNotObject(args, INDEX)) { \
		std::ostringstream msg; \
		msg << __FILE__ << ":" << __LINE__ << " @ "; \
		msg << run_utils::BuildArgsTypeError(args, INDEX, "object"); \
			string_type msg_value = msg.str(); \
    return ThrowException(v8::Exception::Error(v8::String::New(msg_value.c_str()))); \
  }

#define RETHROW_EXCEPTION(e)  ThrowException(v8::Exception::Error(v8::String::New(e.what())));

}

#endif