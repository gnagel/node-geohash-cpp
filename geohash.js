var cgeohash = require('./build/Release/cgeohash');

module.exports = {
    encode:      cgeohash.encode_js,
    decode:      cgeohash.decode_js,
    decode_bbox: cgeohash.decode_bbox_js,
    neighbor:    cgeohash.neighbor_js,
}

