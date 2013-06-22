var cgeohash = require('../build/Release/cgeohash');

module.exports = {
    encode:        cgeohash.encode_fn,
    decode:        cgeohash.decode_fn,
    decode_bbox:   cgeohash.decode_bbox_fn,
    neighbor:      cgeohash.neighbor_fn,
};
