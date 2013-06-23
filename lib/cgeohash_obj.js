var cgeohash = require('../build/Release/cgeohash');
var cgeohash_obj = new cgeohash.GeoHashObject();

// Alias the <...>_obj methods to the expected <...> method names
module.exports = {
    encode:        cgeohash_obj.encode_obj,
    decode:        cgeohash_obj.decode_obj,
    decode_bbox:   cgeohash_obj.decode_bbox_obj,
    neighbor:      cgeohash_obj.neighbor_obj,
};
