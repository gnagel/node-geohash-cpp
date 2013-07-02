var cgeohash_fn = require('./lib/cgeohash_fn.js');
var cgeohash_obj = require('./lib/cgeohash_obj.js');
var cgeohash_original = require('./lib/cgeohash_original.js');

module.exports = {
	original_implementation: cgeohash_original,
	cpp_object: cgeohash_obj,
	cpp_functions: cgeohash_fn,

	// Set the default callbacks
  encode:        cgeohash_fn.encode,
  decode:        cgeohash_fn.decode,
  decode_bbox:   cgeohash_fn.decode_bbox,
  neighbor:      cgeohash_fn.neighbor,
};
