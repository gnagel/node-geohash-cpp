#!/usr/bin/env node

var argv = require('optimist')
	.argv;

// Convert our shorthand
if (argv.lat) argv.latitude = argv.lat;
if (argv.lon) argv.longitude = argv.lon;
if (argv.h) argv.help = argv.h;



// Load the implementation type
// Default is C++ Object
var impl = undefined;
if (argv.impl && argv.impl === 'cpp') {
	impl = require('../index.js')
		.cpp_object;
} else if (argv.impl && argv.impl === 'js') {
	impl = require('../index.js')
		.original_implementation;
} else {
	impl = require('../index.js')
		.cpp_object;
}

var latitude = argv.latitude ? argv.latitude.valueOf() : null;
var longitude = argv.longitude ? argv.longitude.valueOf() : null;
var geohash = argv.geohash ? argv.geohash.toString() : null;
var directions = [0, 0];
if (argv.north) directions[0] = 1;
if (argv.south) directions[0] = -1;
if (argv.east) directions[1] = 1;
if (argv.west) directions[1] = -1;


if (argv.encode) {
	geohash = impl.encode(latitude, longitude);
	console.log(geohash);
	process.exit(0);
}

if (argv.decode) {
	var tmp = impl.decode(geohash);
	latitude = tmp.latitude;
	longitude = tmp.longitude;
	console.log(latitude + ',' + longitude);
	process.exit(0);
}

if (argv.neighbor) {
	geohash = impl.neighbor(geohash, directions);
	console.log(geohash);
	process.exit(0);
}


console.log("");
console.log("cgeohash-cli.js [implementation type] [task] [arguments]");
console.log("");
console.log("\t--impl [cpp|js] (use C++ or JS implementation)");
console.log("");
console.log("\t--encode --lat[itude] '<coordinates>' --lon[gitude] '<coordinates>' (ex: lat=37.8324, lon=112.5584)");
console.log("");
console.log("\t--decode --geohash '<hash string>' (ex 'ww8p1r4t8')");
console.log("");
console.log("\t--neighbor --geohash '<hash string>' --[north|south] --[east|west]");
console.log("");
console.log("");
console.log("Example usage:");
console.log("");
console.log("$ cgeohash-cli.js --encode --lat=37.8324 --lon=112.5584");
console.log("> ww8p1r4t8");
console.log("");
console.log("$ cgeohash-cli.js --decode 'ww8p1r4t8'");
console.log("> 37.8324,112.5584");
console.log("");
console.log("$ cgeohash-cli.js --neighbor 'dqcjq' --north");
console.log("> dqcjw");
console.log("");
console.log("$ cgeohash-cli.js --neighbor 'dqcjq' --south --west");
console.log("> dqcjj");
console.log("");
console.log("");

process.exit(0);
