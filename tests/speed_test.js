//
// Required Libraries
//
var path      = require('path');
var mocha     = require('mocha');
var chai      = require('chai');
var should    = chai.should();

//
// Helpers
//

// How many times faster is the new vs old times?
function x_faster(new_time, old_time) {
	return Math.round((old_time / new_time) * 100) / 100;
};

function compare_ratios(tag, timings) {
	describe(tag, function() {
		var seconds = {
			original_in_js: timings.original_in_js(),
			obj_in_js:      timings.obj_in_js(),
			obj_in_cpp:     timings.obj_in_cpp(),
			fn_in_js:       timings.fn_in_js(),
			fn_in_cpp:      timings.fn_in_cpp(),
		};
		console.log("seconds=" + JSON.stringify(seconds, undefined, 2));
		
		// var times_faster = {};
		// var diff = {};
		// 
		// // // Javascript <-> Javascript (original version)
		// // seconds.js_vs_src = src();
		// // times_faster.js_vs_src = 1; // src() / src() ==> 1
		// // diff.js_vs_src = 0;
		// // 
		// // // Javascript <-> C++ Function
		// // seconds.js_vs_cpp_function = js();
		// // diff.js_vs_cpp_function = seconds.js_vs_cpp_function - seconds.js_vs_src;
		// // times_faster.js_vs_cpp_function = x_faster(
		// // 	seconds.js_vs_cpp_function, 
		// // 	seconds.js_vs_src);
		// 
		// // C++ Only
		// seconds.cpp_vs_cpp_object = cpp();
		// diff.cpp_vs_cpp_object = seconds.cpp_vs_cpp_object - seconds.js_vs_src;
		// times_faster.cpp_vs_cpp_object = x_faster(
		// 	seconds.cpp_vs_cpp_object, 
		// 	seconds.js_vs_src);
		// 
		// // Used for logging and errors
		// var seconds_s         = JSON.stringify(seconds, undefined, 2);
		// var diff_s            = JSON.stringify(diff, undefined, 2);
		// var times_faster_to_s = JSON.stringify(times_faster, undefined, 2);
		// // if (process.env.VERBOSE) {
		// 	console.log(tag + ': times_faster=' + times_faster_to_s);
		// 	console.log(tag + ': diff=' + seconds_s);
		// 	console.log(tag + ': seconds=' + seconds_s);
		// // }
		// 
		// describe('[X times Faster]', function() {
		// 	it('JS <-> JS Original Version compared to self should be 1.0', function() {
		// 		chai.assert.ok(times_faster.js_vs_src == 1.0, times_faster_to_s);
		// 	});
		// 
		// 	// it('JS <-> Node Function Wrapping-C++ is slower than Original Version', function() {
		// 	// 	chai.assert.ok(Math.round(times_faster.js_vs_cpp_function) <= 1, times_faster_to_s);
		// 	// });
		// 
		// 	// seconds.cpp_vs_cpp_object is null if it was too fast to measure
		// 	it('Pure-C++ function is 100x+ faster than JS Original Version', function() {
		// 		if (seconds.cpp_vs_cpp_object) {
		// 			chai.assert.ok(Math.round(times_faster.cpp_vs_cpp_object) > 100, times_faster_to_s);
		// 		}
		// 	});
		// });
		
	});
};


//
// Geo Hash Libraries for testing
//
var fn_repeaters   = require('../lib/cgeohash_fn_repeaters.js');
var obj_repeaters  = require('../lib/cgeohash_obj_repeaters.js');
var orig_repeaters = require('../lib/cgeohash_original_repeaters.js');


//
// Test Suite
//
describe('Speed Tests', function() {
	this.timeout(0);
	
	var num_runs = 1000*1000;

	compare_ratios('encodes latitude & longitude as string', {
		original_in_js: function() { 
			return orig_repeaters.repeat_in_js.encode(num_runs, 37.8324, 112.5584, 9);
		},
		obj_in_js: function() { 
			return obj_repeaters.repeat_in_js.encode(num_runs, 37.8324, 112.5584, 9);
		},
		obj_in_cpp: function() { 
			return obj_repeaters.repeat_in_cpp.encode(num_runs, 37.8324, 112.5584, 9);
		},
		fn_in_js: function() { 
			return fn_repeaters.repeat_in_js.encode(num_runs, 37.8324, 112.5584, 9);
		},
		fn_in_cpp: function() { 
			return fn_repeaters.repeat_in_cpp.encode(num_runs, 37.8324, 112.5584, 9);
		},
	});

	// compare_ratios('decodes string to latitude & longitude',
	// 	function() { 
	// 		return orig_repeaters.decode(num_runs, 'ww8p1r4t8');
	// 	},
	// 	function() { 
	// 		return obj_repeaters.decode(num_runs, 'ww8p1r4t8');
	// 	},
	// 	function() { 
	// 		return fn_repeaters.decode(num_runs, 'ww8p1r4t8');
	// 	});
	// 
	// compare_ratios('finds neighbor to the north',
	// 	function() { 
	// 		return orig_repeaters.neighbor(num_runs, 'dqcjq', [1, 0]);
	// 	},
	// 	function() { 
	// 		return obj_repeaters.neighbor(num_runs, 'dqcjq', [1, 0]);
	// 	},
	// 	function() { 
	// 		return fn_repeaters.neighbor(num_runs, 'dqcjq', [1, 0]);
	// 	});
	// 
	// compare_ratios('finds neighbor to the south-west',
	// function() { 
	// 	return orig_repeaters.neighbor(num_runs, 'dqcjq', [-1, - 1]);
	// },
	// function() { 
	// 	return obj_repeaters.neighbor(num_runs, 'dqcjq', [-1, - 1]);
	// },
	// function() { 
	// 	return fn_repeaters.neighbor(num_runs, 'dqcjq', [-1, - 1]);
	// });
});
