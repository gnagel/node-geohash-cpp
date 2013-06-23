var path = require('path');
var mocha = require('mocha');
var chai = require('chai');
var should = chai.should();

var longitude = 112.5584;
var latitude = 37.8324;
var geostr = 'ww8p1r4t8';

// Helpers

function seconds_per_call(callback) {
	var time = process.hrtime(); // Start
	callback(); // Execute 
	var diff = process.hrtime(time); // Stop
	var seconds = diff[0].valueOf() + diff[1].valueOf() / (1000 * 1000 * 1000);

	return seconds / (1000 * 1000);
};

// Helpers

function wrap_loop_1M_in_js(callback) {
	return function() {
		var last = null;
		for (var i = 0, max = 1000 * 1000; i < max; i++) {
			last = callback();
		}
		return last;
	};
}

function seconds_per_call_loop_1M(callback) {
	return seconds_per_call(wrap_loop_1M_in_js(callback));
}


function encode_latitude_and_longitude_as_string(geohash) {
	return geohash.encode(latitude, longitude, 9);
}

function decodes_string_to_bounded_box(geohash) {
	return geohash.decode_bbox('ww8p1r4t8');
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

module.exports = function(tag, geohash) {
	// Validate the Input matches the Output
	describe(tag + ' - Input Checks', function() {
		it('encodes latitude & longitude as string', function() {
			encode_latitude_and_longitude_as_string(geohash)
				.should.equal(geostr);
		});

		it('decodes string to bounded box', function() {
			var expected = [
			37.83236503601074,
			112.55836486816406,
			37.83240795135498,
			112.5584077835083];

			var bbox = decodes_string_to_bounded_box(geohash);

			// Round the numbers to integers and compare them
			var rounding_match = function(a, b) {
				Math.round(a)
					.should.equal(
				Math.round(b), "expected=" + JSON.stringify(expected, undefined, 2) + ", bbox=" + JSON.stringify(bbox, undefined, 2));
			}
			rounding_match(bbox[0], expected[0]);
			rounding_match(bbox[1], expected[1]);
			rounding_match(bbox[2], expected[2]);
			rounding_match(bbox[3], expected[3]);
		});

		it('decodes string to latitude', function() {
			var latlon_latitude = decodes_string_to_latitude(geohash);
			var diff = Math.abs(latitude - latlon_latitude) < 0.0001
			var msg = 'Expected ' + latitude + '-' + latlon_latitude + ' to be very close'
			chai.assert.ok(diff, msg);
		});

		it('decodes string to longitude', function() {
			var latlon_longitude = decodes_string_to_longitude(geohash);
			var diff = Math.abs(longitude - latlon_longitude) < 0.0001
			var msg = 'Expected ' + longitude + '-' + latlon_longitude + ' to be very close'
			chai.assert.ok(diff, msg);
		});

		it('finds neighbor to the north', function() {
			finds_neighbor_to_the_north(geohash)
				.should.equal('dqcjw');
		});

		it('finds neighbor to the south-west', function() {
			finds_neighbor_to_the_south_west(geohash)
				.should.equal('dqcjj');
		});
	});
};
