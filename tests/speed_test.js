//
// Required Libraries
//
var path              = require('path');
var mocha             = require('mocha');
var chai              = require('chai');
var should            = chai.should();
var v8_profiler_table = require('v8-profiler-table');

//
// Helpers
//

function compare_ratios(tag, timings) {
	describe(tag, function() {
		// Clear the profiles
		v8_profiler_table.reset_profiles();

			// Log the run-times of the Original and C++ versions
		v8_profiler_table.record_profile('Original JS Version', timings.original_in_js);
		v8_profiler_table.record_profile('All C++ Version',     timings.fn_in_cpp);
		
		console.log(v8_profiler_table.stringify());
		
		it ('Original JS Version', function() {
			var profile = v8_profiler_table.profiles()['Original JS Version'];
			
			// Sanity checks
			profile.title.should.equal('Original JS Version');
			profile.ratio_to_base.should.equal(1);
		});
		
		it ('All C++ Version', function() {
			var profile = v8_profiler_table.profiles()['All C++ Version'];
			
			// Sanity checks
			profile.title.should.equal('All C++ Version');
			chai.assert.ok(profile.ratio_to_base >= 1.0, JSON.stringify(profile, undefined, 2));
			chai.assert.ok(profile.total_seconds <= 0.5, JSON.stringify(profile, undefined, 2));
		});
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

	compare_ratios('decodes string to latitude & longitude', {
		original_in_js: function() { 
			return orig_repeaters.repeat_in_js.decode(num_runs, 'ww8p1r4t8');
		},
		obj_in_js: function() { 
			return obj_repeaters.repeat_in_js.decode(num_runs, 'ww8p1r4t8');
		},
		obj_in_cpp: function() { 
			return obj_repeaters.repeat_in_cpp.decode(num_runs, 'ww8p1r4t8');
		},
		fn_in_js: function() { 
			return fn_repeaters.repeat_in_js.decode(num_runs, 'ww8p1r4t8');
		},
		fn_in_cpp: function() { 
			return fn_repeaters.repeat_in_cpp.decode(num_runs, 'ww8p1r4t8');
		},
	});
	
	compare_ratios('finds neighbor to the north', {
		original_in_js: function() { 
			return orig_repeaters.repeat_in_js.neighbor(num_runs, 'dqcjq', [1, 0]);
		},
		obj_in_js: function() { 
			return obj_repeaters.repeat_in_js.neighbor(num_runs, 'dqcjq', [1, 0]);
		},
		obj_in_cpp: function() { 
			return obj_repeaters.repeat_in_cpp.neighbor(num_runs, 'dqcjq', [1, 0]);
		},
		fn_in_js: function() { 
			return fn_repeaters.repeat_in_js.neighbor(num_runs, 'dqcjq', [1, 0]);
		},
		fn_in_cpp: function() { 
			return fn_repeaters.repeat_in_cpp.neighbor(num_runs, 'dqcjq', [1, 0]);
		},
	});
	
	compare_ratios('finds neighbor to the south-west', {
		original_in_js: function() { 
			return orig_repeaters.repeat_in_js.neighbor(num_runs, 'dqcjq', [-1, - 1]);
		},
		obj_in_js: function() { 
			return obj_repeaters.repeat_in_js.neighbor(num_runs, 'dqcjq', [-1, - 1]);
		},
		obj_in_cpp: function() { 
			return obj_repeaters.repeat_in_cpp.neighbor(num_runs, 'dqcjq', [-1, - 1]);
		},
		fn_in_js: function() { 
			return fn_repeaters.repeat_in_js.neighbor(num_runs, 'dqcjq', [-1, - 1]);
		},
		fn_in_cpp: function() { 
			return fn_repeaters.repeat_in_cpp.neighbor(num_runs, 'dqcjq', [-1, - 1]);
		},
	});

});
