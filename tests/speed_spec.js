var path = require('path');
var mocha = require('mocha');
var chai = require('chai');
var should = chai.should();

var precision = 12;
var longitude = 112.5584;
var latitude = 37.8324;
var geo_str = 'ww8p1r4t8';
var geo_neighbor = 'dqcjq';

var sprintf = require('sprintf')
	.sprintf;

var format_tag = "\n[%-30s][%-12s]\t MS Per/Call %.4f (ms)\t Total for %d Calls = %5f (ms)";

var log_times = function(num_loops, class_name, operation_name, start, end) {
	var total = (end - start) * 1.0;

	var per_loop = total / num_loops;

	console.log(sprintf(format_tag, operation_name, class_name, per_loop, num_loops, total));
};

// Helpers
var speed_spec = function(tag, geohash) {
	var num_loops = 1000*1000;
	
	// Validate the Input matches the Output
	describe(tag + ' - Input Checks', function() {
		it('encodes latitude & longitude as string', function() {
			var start = new Date();
			geohash.encode(latitude, longitude, precision, num_loops);
			log_times(num_loops, tag, 'encode', start, new Date());
		});

		it('encodes latitude & longitude as string for all precisions', function() {
			var start = new Date();
			geohash.encode_all_precisions(latitude, longitude, num_loops);
			log_times(num_loops, tag, 'encode_all_precisions', start, new Date());
		});

		it('decodes string to bounded box', function() {
			var start = new Date();
			geohash.decode_bbox(geo_str, num_loops);
			log_times(num_loops, tag, 'decode_bbox', start, new Date());
		});

		it('decodes string to latitude & longitude', function() {
			var start = new Date();
			geohash.decode(geo_str, num_loops);
			log_times(num_loops, tag, 'decode', start, new Date());
		});

		it('finds neighbor to the north', function() {
			var start = new Date();
			var actual = geohash.neighbor(geo_neighbor, [1, 0], num_loops);
			log_times(num_loops, tag, 'neighbor NW', start, new Date());
		});

		it('finds neighbor to the south-west', function() {
			var start = new Date();
			var actual = geohash.neighbor(geo_neighbor, [-1, - 1], num_loops);
			log_times(num_loops, tag, 'neighbor SW', start, new Date());
		});
	});
};

describe('Geo Hash Speed Tests', function() {
	speed_spec('cgeohash', require('../index_speed_tests.js'));
	speed_spec('ngeohash', require('./cgeohash_original_repeaters.js'));
});
