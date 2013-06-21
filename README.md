## Welcome to node-geohash-cpp

node-geohash-cpp is a C++ extension to node based on [node-geohash](https://github.com/sunng87/node-geohash).

Install
-------

    npm install cgeohash

Usage
-----

    var geohash = require('cgeohash');
    sys.puts(geohash.encode(37.8324, 112.5584)); // 'ww8p1r4t8'

    var latlon = geohash.decode('ww8p1r4t8');
    sys.puts(latlon.latitude);
    sys.puts(latlon.longitude);

### encode (latitude, longitude, precision=9)

Encode a pair of latitude and longitude into geohash. The third argument is
optional, you can specify a length of this hash string, which also affect on
the precision of the geohash.

### decode (hashstring)

Decode a hash string into pair of latitude and longitude. A javascript object
is returned with key `latitude` and `longitude`.

### neighbor (hashstring, direction)

Find neighbor of a geohash string in certain direction. Direction is a 
two-element array, i.e. [1,0] means north, [-1,-1] means southwest.

### decode_bbox (hashstring)

Decode hashstring into a bound box matches it. Data returned in a four-element
array: [minlat, minlon, maxlat, maxlon]

About Geohash
-------------

Check [Wikipedia](http://en.wikipedia.org/wiki/Geohash "Wiki page for geohash")
for more information.


## License

Ruby on Rails is released under the [MIT License](http://www.opensource.org/licenses/MIT).