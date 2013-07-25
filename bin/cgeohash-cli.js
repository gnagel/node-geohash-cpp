#!/usr/bin/env node

var argv = require('optimist')
	.argv;

var sprintf = require('sprintf')
	.sprintf;

var cgeohash = require('../index.js');

if (argv.encode) {
	if (!argv.latitude) throw "latitude field required"
	if (!argv.longitude) throw "longitude field required"
	if (!argv.precision) throw "precision field required"
	
	argv.latitude = +argv.latitude
	argv.longitude =+argv.longitude
	argv.precision = +argv.precision;
	var output = cgeohash.encode(argv.latitude, argv.longitude, argv.precision)
	console.log(sprintf("latitude = %2.10f, longitude = %3.10f, precision = %d, geohash = %12s", argv.latitude, argv.longitude, argv.precision, output));
}

if (argv.decode) {
	if (!argv.geohash) throw "geohash field required"
	
	var output = cgeohash.encode(geohash)
	console.log(sprintf("geohash = %12s, latitude = %2.10f, longitude = %3.10f, latitude.err = %2.10f, longitude.err = %2.10f", argv.geohash, output.latitude, output.longitude, output.error.latitude, output.error.longitude));
}

if (argv.neighbor) {
	if (!argv.geohash) throw "geohash field required"
	if (!argv.directions) throw "directions array required"
	
	argv.directions = argv.directions.split(',')
	argv.directions[0] = +argv.directions[0]
	argv.directions[1] = +argv.directions[1]
	var output = cgeohash.neighbor(geohash, argv.directions)
	console.log(sprintf("%geohash = %12s, directions[0] = %d, directions[1] = %d, neighbor = %12s", argv.geohash, argv.directions[0], argv.directions[1], output));
}



if (argv.encode_the_world) {
	if (!argv.precision) throw "precision field required"
	if (!("decimal_places" in argv)) throw "decimal_places field required"
	
	argv.precision = +argv.precision;
	argv.decimal_places = +argv.decimal_places;

	// Output is dumped to stdout
	cgeohash.encode_the_world(argv.precision, argv.decimal_places)
}
