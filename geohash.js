var cgeohash = require('./build/Release/cgeohash');

var GeoHashObject = new cgeohash.GeoHashObject();

module.exports = {
    encode:        cgeohash.encode_js,
    decode:        cgeohash.decode_js,
    decode_bbox:   cgeohash.decode_bbox_js,
    neighbor:      cgeohash.neighbor_js,

    test1m_encode:        cgeohash.test1m_encode_js,
    test1m_decode:        cgeohash.test1m_decode_js,
    test1m_decode_bbox:   cgeohash.test1m_decode_bbox_js,
    test1m_neighbor:      cgeohash.test1m_neighbor_js,
		
		geohash_object: GeoHashObject,
}

