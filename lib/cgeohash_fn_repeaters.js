//
// Map the cgeohash C++ functions to callbacks to repeat X-Many times
// 
// Ex:
// var repeat_in_js  = require('cgeohash_fn_repeaters').repeat_in_js
// var repeat_in_cpp = require('cgeohash_fn_repeaters').repeat_in_cpp
// var avg_seconds_per_decode = {
//   looping_in_js:  repeat_in_js.decode( 1000*1000, 'abcd'),
//   looping_in_cpp: repeat_in_cpp.decode(1000*1000, 'abcd'),
// }
// 
// console.log('Seconds per call Node <-> C++ = ' + looping_in_js);
// console.log('Seconds per call C++  <-> C++ = ' + looping_in_cpp);
//

var cgeohash                      = require('../build/Release/cgeohash');
var cgeohash_fn                   = require('./cgeohash_fn');
var repeats_callback = require('v8-profiler-table').repeats_callback;

// Alias the <...>_obj methods to the expected <...> method names
// Loop in JS and record the seconds / call
var cgeohash_fn_repeat_js = {
	encode: function(num_times, latitude, longitude, numberOfChars) {
		var callback = function() {
			return cgeohash_fn.encode(latitude, longitude, numberOfChars);
		};

		return function() {
			var last = undefined;
			for(var i = 0; i < num_loops; i++) { last = callback(); }
			return last;
		};
	},

	decode: function(num_times, hash_string) {
		return repeats_callback(num_times, function() {
			return cgeohash_fn.decode(hash_string);
		});
	},

	decode_bbox: function(num_times, hash_string) {
		return repeats_callback(num_times, function() {
			return cgeohash_fn.decode_bbox(hash_string);
		});
	},

	neighbor: function(num_times, hash_string, direction) {
		return repeats_callback(num_times, function() {
			return cgeohash_fn.neighbor(hash_string, direction);
		});
	},
};

// Alias the <...>_obj methods to the expected <...> method names
// Loop in CPP and record the seconds / call
var cgeohash_fn_repeat_cpp = {
    encode:        cgeohash.encode_fn_repeater,
    decode:        cgeohash.decode_fn_repeater,
    decode_bbox:   cgeohash.decode_bbox_fn_repeater,
    neighbor:      cgeohash.neighbor_fn_repeater,
};


module.exports = {
	repeat_in_js:  cgeohash_fn_repeat_js,
	repeat_in_cpp: cgeohash_fn_repeat_cpp,
};
