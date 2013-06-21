var geohash_shared_spec    = require('./geohash_shared_spec');
var geohash = new require('../geohash.js').geohash_object;

geohash_shared_spec('GeoHash Object in C++', geohash);
