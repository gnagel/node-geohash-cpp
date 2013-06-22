var shared_spec = require('./shared_spec');
var geohash_js  = require('./geohash_original.js');

// 
// geohash.test1m_encode = function(a, b, c) {
// 	var last = undefined;
// 	for(var i = 0, max = 1000*1000; i < max; i++) {
// 		last = geohash.encode(a, b, c);
// 	}
// 	return last;
// }
// 
// geohash.test1m_decode = function(a) {
// 	var last = undefined;
// 	for(var i = 0, max = 1000*1000; i < max; i++) {
// 		last = geohash.decode(a);
// 	}
// 	return last;
// }
// 
// geohash.test1m_neighbor = function(a, b) {
// 	var last = undefined;
// 	for(var i = 0, max = 1000*1000; i < max; i++) {
// 		last = geohash.neighbor(a, b);
// 	}
// 	return last;
// }


shared_spec('GeoHash Functions in C++', geohash_js);
