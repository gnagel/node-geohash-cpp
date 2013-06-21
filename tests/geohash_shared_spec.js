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

	// Validate the expected speed of the function calls
	describe(tag + ' - Speed Tests', function() {
		this.timeout(0);

		describe('encodes latitude & longitude as string', function() {
			it('[JS]', function() {
				var seconds = seconds_per_call_loop_1M(function() {
					return encode_latitude_and_longitude_as_string(geohash);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			})

			it('[CPP]', function() {
				var seconds = seconds_per_call(function() {
					return geohash.test1m_encode(latitude, longitude, 9);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			})
		});


		describe('decodes string to latitude', function() {
			it('[JS]', function() {
				var seconds = seconds_per_call_loop_1M(function() {
					return decodes_string_to_latitude(geohash);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});
			it('[CPP]', function() {
				var seconds = seconds_per_call(function() {
					return geohash.test1m_decode(geostr)
						.latitude;
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});
		});


		describe('decodes string to longitude', function() {
			it('[JS]', function() {
				var seconds = seconds_per_call_loop_1M(function() {
					return decodes_string_to_longitude(geohash);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});

			it('[CPP]', function() {
				var seconds = seconds_per_call(function() {
					return geohash.test1m_decode(geostr)
						.longitude;
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});
		});


		describe('finds neighbor to the north', function() {
			it('[JS]', function() {
				var seconds = seconds_per_call_loop_1M(function() {
					return finds_neighbor_to_the_north(geohash);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});

			it('[CPP]', function() {
				var seconds = seconds_per_call(function() {
					return geohash.test1m_neighbor('dqcjq', [1, 0]);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});
		});


		describe('finds neighbor to the south-west', function() {
			it('[JS]', function() {
				var seconds = seconds_per_call_loop_1M(function() {
					return finds_neighbor_to_the_south_west(geohash);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});

			it('[CPP]', function() {
				var seconds = seconds_per_call(function() {
					return geohash.test1m_neighbor('dqcjq', [-1, - 1]);
				});
				// 0.1 micro-seconds
				chai.assert.ok(seconds <= 0.0000001, seconds * 1000 * 1000 + ' micro-seconds');
			});
		});
	});
};
