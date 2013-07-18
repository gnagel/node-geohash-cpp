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
module.exports = {
	encode: function(latitude, longitude, numberOfChars, num_times) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.encode(latitude, longitude, numberOfChars);
		});
		return loop();
	},

	encode_all_precisions: function(latitude, longitude, num_times) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.encode_all_precisions(latitude, longitude);
		});
		return loop();
	},

	encode_range_precisions: function(latitude, longitude, min, max, num_times) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.encode_range_precisions(latitude, longitude, min, max);
		});
		return loop();
	},

	decode: function(hash_string, num_times) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.decode(hash_string);
		});
		return loop();
	},

	decode_bbox: function(hash_string, num_times) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.decode_bbox(hash_string);
		});
		return loop();
	},

	neighbor: function(hash_string, direction, num_times) {
		var loop = repeats_callback_wrapper(num_times, function() {
			return cgeohash_original.neighbor(hash_string, direction);
		});
		return loop();
	},
};
