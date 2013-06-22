//
// Execute the callback X-Many times and return the "Seconds / Call"
// 
// Ex:
//   var repeater     = require('./seconds_per_call_x_many_times');
//   var counter      = 0;
//   var num_times    = 1000*1000*1000;
//   var callback     = function() { Math.sqrt(++counter); };
//   var sec_per_call = repeater(num_times, callback);
// 
//   /* Make sure the callback was called */
//   counter.should.equal(num_times);
// 
//   /* Log the avg time per call */
//   console.log("Calculating Math.sqrt " + counter + " times took " + sec_per_call + " (s) / call");
//

var NANOSECONDS_TO_SECONDS = 1000 * 1000 * 1000;

module.exports = function(num_times, callback) {
	// Start
	var time = process.hrtime();

	// Execute 
	for (var i = 0; i < num_times; ++i) {
		last = callback();
	}

	// Stop
	var diff    = process.hrtime(time);
	var seconds = diff[0].valueOf() * NANOSECONDS_TO_SECONDS + diff[1].valueOf();

	console.log(seconds);

	return seconds / num_times;
};
