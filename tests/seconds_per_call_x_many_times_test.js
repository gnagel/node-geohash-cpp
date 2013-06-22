var path = require('path');
var mocha = require('mocha');
var chai = require('chai');
var should = chai.should();
var repeater = require('../lib/seconds_per_call_x_many_times');

describe('Record Avg Seconds per call', function() {
	var counter = 0;
	var num_times = 1000 * 1000 * 1000;
	var callback = function() {
		Math.sqrt(++counter);
	};
	var sec_per_call = repeater(num_times, callback);

	/* Make sure the callback was called */
	it('Counter should equal num_times', function() {
		counter.should.equal(num_times);
	});
});
