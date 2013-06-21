var path    = require('path');
var mocha   = require('mocha');
var chai    = require('chai');
var should  = chai.should();
var geohash = require('../geohash.js');

var longitude = 112.5584;
var latitude  = 37.8324;
var geostr    = 'ww8p1r4t8';

describe('GeoHash C++', function () {
	it('encodes latitude & longitude as string', function() {
		geohash.encode(latitude, longitude, 9).should.equal(geostr);
	});

	it('decodes string to latitude', function () {
		var latlon = geohash.decode(geostr);
		var diff   = Math.abs(latitude - latlon.latitude) < 0.0001
		var msg    = 'Expected ' + latitude + '-' + latlon.latitude + ' to be very close'
		assert.ok(diff, msg);
	});

	it('decodes string to longitude', function () {
		var latlon = geohash.decode(geostr);
		var diff   = Math.abs(longitude - latlon.longitude) < 0.0001
		var msg    = 'Expected ' + longitude + '-' + latlon.longitude + ' to be very close'
		assert.ok(diff, msg);
	});

	it('finds neighbor to the north', function () {
		geohash.neighbor('dqcjq', [1,0]).should.equal('dqcjw');
	});

	it('finds neighbor to the south-west', function () {
		geohash.neighbor('DQCJQ', [-1,-1]).should.equal('dqcjj');
	});
});
