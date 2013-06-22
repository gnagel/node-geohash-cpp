//
// Map the cgeohash C++ Object to callbacks to repeat X-Many times
// 
// Ex:
// var repeat_in_js  = require('cgeohash_obj_repeaters').repeat_in_js
// var repeat_in_cpp = require('cgeohash_obj_repeaters').repeat_in_cpp
// var avg_seconds_per_decode = {
//   looping_in_js:  repeat_in_js.decode( 1000*1000, 'abcd'),
//   looping_in_cpp: repeat_in_cpp.decode(1000*1000, 'abcd'),
// }
// 
// console.log('Seconds per call Node <-> C++ = ' + looping_in_js);
// console.log('Seconds per call C++  <-> C++ = ' + looping_in_cpp);
//

var cgeohash                      = require('../build/Release/cgeohash');
var cgeohash_obj                  = require('./cgeohash_obj');
var cgeohash_obj_repeater         = new cgeohash.GeoHashObjectRepeater();
var seconds_per_call_x_many_times = require('./seconds_per_call_x_many_times');

// Alias the <...>_obj methods to the expected <...> method names
// Loop in JS and record the seconds / call
var cgeohash_fn_repeat_js = {
	encode: function(num_times, latitude, longitude, numberOfChars) {
		return seconds_per_call_x_many_times(num_times, function() {
			return cgeohash_obj.encode(latitude, longitude, numberOfChars);
		});
	},

	decode: function(num_times, hash_string) {
		return seconds_per_call_x_many_times(num_times, function() {
			return cgeohash_obj.decode(hash_string);
		});
	},

	decode_bbox: function(num_times, hash_string) {
		return seconds_per_call_x_many_times(num_times, function() {
			return cgeohash_obj.decode_bbox(hash_string);
		});
	},

	neighbor: function(num_times, hash_string, direction) {
		return seconds_per_call_x_many_times(num_times, function() {
			return cgeohash_obj.neighbor(hash_string, direction);
		});
	},
};

// Alias the <...>_obj methods to the expected <...> method names
// Loop in CPP and record the seconds / call
var cgeohash_fn_repeat_cpp = {
    encode:        cgeohash_obj_repeater.encode_obj_repeater,
    decode:        cgeohash_obj_repeater.decode_obj_repeater,
    decode_bbox:   cgeohash_obj_repeater.decode_bbox_obj_repeater,
    neighbor:      cgeohash_obj_repeater.neighbor_obj_repeater,
};


module.exports = {
	repeat_in_js:  cgeohash_fn_repeat_js,
	repeat_in_cpp: cgeohash_fn_repeat_cpp,
};
