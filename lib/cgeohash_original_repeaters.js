//
// Map the originan node-geohash JavaScript functions to callbacks to repeat X-Many times
// 
// Ex:
// var repeat_in_js  = require('geohash_original_repeaters').repeat_in_js
// var avg_seconds_per_decode = {
//   looping_in_js:  repeat_in_js.decode( 1000*1000, 'abcd'),
// }
// 
// console.log('Seconds per call Node <-> JS = ' + looping_in_js);
//

var cgeohash_original        = require('./cgeohash_original');
var repeats_callback_wrapper = require('v8-profiler-table').repeats_callback_wrapper;

// Alias the <...>_obj methods to the expected <...> method names
// Loop in JS and record the seconds / call
var cgeohash_original_repeat_js = {
	encode: function(num_times, latitude, longitude, numberOfChars) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.encode(latitude, longitude, numberOfChars);
		});
		return loop();
	},

	decode: function(num_times, hash_string) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.decode(hash_string);
		});
		return loop();
	},

	decode_bbox: function(num_times, hash_string) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.decode_bbox(hash_string);
		});
		return loop();
	},

	neighbor: function(num_times, hash_string, direction) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.neighbor(hash_string, direction);
		});
		return loop();
	},
};

module.exports = {
	repeat_in_js:  cgeohash_original_repeat_js,
	repeat_in_cpp: undefined, // Not available
};
