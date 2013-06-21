var cgeohash = require('./build/Release/cgeohash');

module.exports = {
    encode:      cgeohash.encode,
    decode:      cgeohash.decode,
    decode_bbox: cgeohash.decode_bbox,
    neighbor:    cgeohash.neighbor,
}

