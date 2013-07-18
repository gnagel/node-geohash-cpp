var sprintf = require('sprintf')
	.sprintf;

var BASE32_CODES = "0123456789bcdefghjkmnpqrstuvwxyz";
var BASE32_CODES_DICT = {};
for (var i = 0; i < BASE32_CODES.length; i++) {
	BASE32_CODES_DICT[BASE32_CODES.charAt(i)] = i;
}

var encode = function(latitude, longitude, numberOfChars) {
	numberOfChars = numberOfChars || 9;
	var chars = [],
		bits = 0;
	var hash_value = 0;

	var maxlat = 90,
		minlat = -90;
	var maxlon = 180,
		minlon = -180;

	var mid;
	var islon = true;
	while (chars.length < numberOfChars) {
		if (islon) {
			mid = (maxlon + minlon) / 2;
			if (longitude > mid) {
				hash_value = (hash_value << 1) + 1;
				minlon = mid;
			} else {
				hash_value = (hash_value << 1) + 0;
				maxlon = mid;
			}
		} else {
			mid = (maxlat + minlat) / 2;
			if (latitude > mid) {
				hash_value = (hash_value << 1) + 1;
				minlat = mid;
			} else {
				hash_value = (hash_value << 1) + 0;
				maxlat = mid;
			}
		}

		islon = !islon;
		bits++;

		if (bits == 5) {
			var code = BASE32_CODES[hash_value];
			chars.push(code);
			bits = 0;
			hash_value = 0;
		}
	}
	return chars.join('')
};

var encode_all_precisions_slow = function(latitude, longitude) {
	var output = [
	encode(latitude, longitude, 1),
	encode(latitude, longitude, 2),
	encode(latitude, longitude, 3),
	encode(latitude, longitude, 4),
	encode(latitude, longitude, 5),
	encode(latitude, longitude, 6),
	encode(latitude, longitude, 7),
	encode(latitude, longitude, 8),
	encode(latitude, longitude, 9), ];
	return output;
};

var encode_all_precisions_fast = function(latitude, longitude) {
	return encode_range_precisions(latitude, longitude, 1, 9);
};

var encode_range_precisions = function(latitude, longitude, min, max) {
	var num_precisions = max - (min-1); // Inclusive
	var output = new Array(num_precisions);

	// Set the "end" value
	output[num_precisions - 1] = encode(latitude, longitude, max);

	for (var i = num_precisions - 2; i >= 0; --i) {
		var last = output[i + 1];
		output[i] = last.substring(0, last.length - 1);

	}

	return output;
};

var decode_bbox = function(hash_string) {
	var islon = true;
	var maxlat = 90,
		minlat = -90;
	var maxlon = 180,
		minlon = -180;

	var hash_value = 0;
	for (var i = 0, l = hash_string.length; i < l; i++) {
		var code = hash_string[i].toLowerCase();
		hash_value = BASE32_CODES_DICT[code];

		for (var bits = 4; bits >= 0; bits--) {
			var bit = (hash_value >> bits) & 1;
			if (islon) {
				var mid = (maxlon + minlon) / 2;
				if (bit == 1) {
					minlon = mid;
				} else {
					maxlon = mid;
				}
			} else {
				var mid = (maxlat + minlat) / 2;
				if (bit == 1) {
					minlat = mid;
				} else {
					maxlat = mid;
				}
			}
			islon = !islon;
		}
	}
	return [minlat, minlon, maxlat, maxlon];
}

var decode = function(hash_string) {
	var bbox = decode_bbox(hash_string);
	var lat = (bbox[0] + bbox[2]) / 2;
	var lon = (bbox[1] + bbox[3]) / 2;
	var laterr = bbox[2] - lat;
	var lonerr = bbox[3] - lon;
	return {
		latitude: lat,
		longitude: lon,
		error: {
			latitude: laterr,
			longitude: lonerr
		}
	};
};

/**
 * direction [lat, lon], i.e.
 * [1,0] - north
 * [1,1] - northeast
 * ...
 */
var neighbor = function(hashstring, direction) {
	var lonlat = decode(hashstring);
	var neighbor_lat = lonlat.latitude + direction[0] * lonlat.error.latitude * 2;
	var neighbor_lon = lonlat.longitude + direction[1] * lonlat.error.longitude * 2;
	return encode(neighbor_lat, neighbor_lon, hashstring.length);
}

var geohash = {
	'encode': encode,
	'encode_range_precisions': encode_range_precisions,
	'encode_all_precisions': encode_all_precisions_fast,
	'encode_all_precisions_fast': encode_all_precisions_fast,
	'encode_all_precisions_slow': encode_all_precisions_slow,
	'decode': decode,
	'decode_bbox': decode_bbox,
	'neighbor': neighbor,
}
module.exports = geohash;
