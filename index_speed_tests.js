var cgeohash = require('./build/Release/cgeohash_speed_tests');

module.exports = {
    encode:                cgeohash.encode_fn,
		encode_all_precisions: cgeohash.encode_all_precisions_fn,
    decode:                cgeohash.decode_fn,
    decode_bbox:           cgeohash.decode_bbox_fn,
    neighbor:              cgeohash.neighbor_fn,
};
