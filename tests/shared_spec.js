var path = require('path');
var mocha = require('mocha');
var chai = require('chai');
var should = chai.should();

var longitude = 112.5584;
var latitude = 37.8324;
var geostr = 'ww8p1r4t8';

// Helpers
var shared_spec = function(tag, geohash) {
	// Validate the Input matches the Output
	describe(tag + ' - Input Checks', function() {
		it('encodes latitude & longitude as string', function() {
			var actual = geohash.encode(latitude, longitude, 9);
			var expected = geostr;
			chai.assert.deepEqual(actual, expected);
		});

		it('encodes latitude & longitude as string for all precisions', function() {
			var actual = geohash.encode_all_precisions(latitude, longitude);
			var expected = [
			geohash.encode(latitude, longitude, 1),
			geohash.encode(latitude, longitude, 2),
			geohash.encode(latitude, longitude, 3),
			geohash.encode(latitude, longitude, 4),
			geohash.encode(latitude, longitude, 5),
			geohash.encode(latitude, longitude, 6),
			geohash.encode(latitude, longitude, 7),
			geohash.encode(latitude, longitude, 8),
			geohash.encode(latitude, longitude, 9)];

			chai.assert.deepEqual(actual, expected);
		});

		it('decodes string to bounded box', function() {
			// Round the numbers to integers and compare them
			var rounding_match = function(actual, expected, index) {
				Math.round(actual[index])
					.should.equal(
				Math.round(expected[index]), "expected=" + JSON.stringify(expected, undefined, 2) + ", bbox=" + JSON.stringify(actual, undefined, 2));
			}

			var actual = geohash.decode_bbox(geostr);
			var expected = [
			37.83236503601074,
			112.55836486816406,
			37.83240795135498,
			112.5584077835083];
			for (var i = 0; i < 4; ++i) {
				rounding_match(actual, expected, i);
			}
		});

		it('decodes string to latitude', function() {
			var actual = geohash.decode(geostr)
				.latitude;
			var diff = Math.abs(latitude - actual) < 0.0001
			var msg = 'Expected ' + latitude + '-' + actual + ' to be very close'
			chai.assert.ok(diff, msg);
		});

		it('decodes string to longitude', function() {
			var actual = geohash.decode(geostr)
				.longitude;
			var diff = Math.abs(longitude - actual) < 0.0001
			var msg = 'Expected ' + longitude + '-' + actual + ' to be very close'
			chai.assert.ok(diff, msg);
		});

		it('finds neighbor to the north', function() {
			var actual = geohash.neighbor('dqcjq', [1, 0]);
			var expected = 'dqcjw';
			chai.assert.deepEqual(actual, expected);
		});

		it('finds neighbor to the south-west', function() {
			var actual = geohash.neighbor('dqcjq', [-1, - 1])
			var expected = 'dqcjj';
			chai.assert.deepEqual(actual, expected);
		});
	});
};

describe('Geo Hash', function() {
	shared_spec('C++ Functions', require('../index.js'));
	shared_spec('JS Functions', require('./cgeohash_original.js'));
});
