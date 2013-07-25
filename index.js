var cgeohash = require('./build/Release/cgeohash');

module.exports = {
    encode:                  cgeohash.encode_fn,
    encode_the_world:        cgeohash.encode_the_world_fn,
		encode_all_precisions:   cgeohash.encode_all_precisions_fn,
		encode_range_precisions: cgeohash.encode_range_precisions_fn,
    decode:                  cgeohash.decode_fn,
    decode_bbox:             cgeohash.decode_bbox_fn,
    neighbor:                cgeohash.neighbor_fn,
};
