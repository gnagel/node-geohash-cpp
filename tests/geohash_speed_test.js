//
// Required Libraries
//
var path      = require('path');
var mocha     = require('mocha');
var chai      = require('chai');
var should    = chai.should();

//
// Constants
//
var longitude = 112.5584;
var latitude  = 37.8324;
var geostr    = 'ww8p1r4t8';

//
// Helpers
//
function seconds_per_call(callback) {
	var time = process.hrtime(); // Start
	callback(); // Execute 
	var diff = process.hrtime(time); // Stop
	var seconds = diff[0].valueOf() + diff[1].valueOf() / (1000 * 1000 * 1000);

	return seconds / (1000 * 1000);
};

function wrap_loop_1M_in_js(callback, validates) {
	return function() {
		var last = null;
		for (var i = 0, max = 1000 * 1000; i < max; i++) {
			last = callback();
		}
		return validates(last);
	};
}

function seconds_per_call_loop_1M(callback, validates) {
	return seconds_per_call(wrap_loop_1M_in_js(callback, validates));
}

function encode_latitude_and_longitude_as_string(geohash) {
	return geohash.encode(latitude, longitude, 9);
}

function decodes_string_to_latitude(geohash) {
	return geohash.decode(geostr)
		.latitude;
}

function decodes_string_to_longitude(geohash) {
	return geohash.decode(geostr)
		.longitude;
}

function finds_neighbor_to_the_north(geohash) {
	return geohash.neighbor('dqcjq', [1, 0]);
}

function finds_neighbor_to_the_south_west(geohash) {
	return geohash.neighbor('dqcjq', [-1, - 1]);
}

// How many times faster is the new vs old times?
function x_faster(new_time, old_time) {
	return Math.round((old_time / new_time) * 100) / 100;
};


//
// Geo Hash Libraries for testing
//
var geohash_c_object = new require('../geohash.js')
	.geohash_object;
var geohash_c_functions = require('../geohash.js');
var geohash_original = require('./geohash_original.js');

geohash_original.test1m_encode = function(a, b, c) {
	var last = undefined;
	for (var i = 0, max = 1000 * 1000; i < max; i++) {
		last = geohash_original.encode(a, b, c);
	}
	return last;
}

geohash_original.test1m_decode = function(a) {
	var last = undefined;
	for (var i = 0, max = 1000 * 1000; i < max; i++) {
		last = geohash_original.decode(a);
	}
	return last;
}

geohash_original.test1m_neighbor = function(a, b) {
	var last = undefined;
	for (var i = 0, max = 1000 * 1000; i < max; i++) {
		last = geohash_original.neighbor(a, b);
	}
	return last;
}

//
// Test Suite
//
describe('Speed Tests', function() {
	this.timeout(0);

	function compare_ratios(tag, src, js, cpp, validates) {
		describe(tag, function() {
			var seconds = {
				// Javascript <-> Javascript (original version)
				js_vs_src: seconds_per_call_loop_1M(src, validates),
				// Javascript <-> C++ Function
				js_vs_c_function: seconds_per_call_loop_1M(js, validates),
				// Javascript <-> C++ Object
				js_vs_c_object: seconds_per_call(cpp),
				// C++ Only
				cpp_vs_c_object: cpp(),
			};
			var times_faster = {
				js_vs_src:        1.0, // Ratio to self is always 1
				js_vs_c_function: x_faster(seconds.js_vs_c_function , seconds.js_vs_src),
				js_vs_c_object:   x_faster(seconds.js_vs_c_object   , seconds.js_vs_src),
				cpp_vs_c_object:  x_faster(seconds.cpp_vs_c_object  , seconds.js_vs_src),
			}

			var seconds_s      = JSON.stringify(seconds);
			var times_faster_to_s = JSON.stringify(times_faster);
			if (process.env.VERBOSE) {
				console.log(tag + ': times_faster=' + times_faster_to_s);
				console.log(tag + ': seconds=' + seconds_s);
			}

			describe('[X times Faster]', function() {
				it('JS <-> JS Original Version compared to self should be 1.0', function() {
					chai.assert.ok(times_faster.js_vs_src == 1.0, times_faster_to_s);
				});

				it('JS <-> Node Function Wrapping-C++ is slower than Original Version', function() {
					chai.assert.ok(Math.round(times_faster.js_vs_c_function) <= 1, times_faster_to_s);
				});

				it('JS <-> Node Object Wrapping-C++ is slower than Original Version', function() {
					chai.assert.ok(Math.round(times_faster.js_vs_c_object) <= 1, times_faster_to_s);
				});

				// seconds.cpp_vs_c_object is null if it was too fast to measure
				it('Pure-C++ function is 100x+ faster than JS Original Version', function() {
					if (seconds.cpp_vs_c_object) {
						chai.assert.ok(Math.round(times_faster.cpp_vs_c_object) > 100, times_faster_to_s);
					}
				});
			});
			
		});
	};

	compare_ratios('encodes latitude & longitude as string',
		function() { return encode_latitude_and_longitude_as_string(geohash_original); },
		function() { return encode_latitude_and_longitude_as_string(geohash_c_functions); },
		function() { return geohash_c_object.test1m_encode(latitude, longitude, 9) / 1000000000; },
		function(data) { data.should.equal(geostr); });

	compare_ratios('decodes string to latitude',
		function() { return decodes_string_to_latitude(geohash_original); },
		function() { return decodes_string_to_latitude(geohash_c_functions); },
		function() { return geohash_c_object.test1m_decode(geostr) / 1000000000; },
		function(data) {
			var diff = Math.abs(latitude - data) < 0.0001
			var msg = 'Expected ' + latitude + '-' + data + ' to be very close'
			chai.assert.ok(diff, msg);
		});

	compare_ratios('decodes string to longitude',
		function() { return decodes_string_to_longitude(geohash_original); },
		function() { return decodes_string_to_longitude(geohash_c_functions); },
		function() { return geohash_original.test1m_decode(geostr) / 1000000000; },
		function(data) {
			var diff = Math.abs(longitude - data) < 0.0001
			var msg = 'Expected ' + longitude + '-' + data + ' to be very close'
			chai.assert.ok(diff, msg);
		});

	compare_ratios('finds neighbor to the north',
		function() { return finds_neighbor_to_the_north(geohash_original); },
		function() { return finds_neighbor_to_the_north(geohash_c_functions); },
		function() { return geohash_c_object.test1m_neighbor('dqcjq', [1, 0]) / 1000000000; },
		function(data) { data.should.equal('dqcjw'); });

	compare_ratios('finds neighbor to the south-west',
		function() { return finds_neighbor_to_the_south_west(geohash_original); },
		function() { return finds_neighbor_to_the_south_west(geohash_c_functions); },
		function() { return geohash_c_object.test1m_neighbor('dqcjq', [-1, - 1]) / 1000000000; },
		function(data) { data.should.equal('dqcjj'); });
});
