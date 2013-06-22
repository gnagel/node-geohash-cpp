#include <node.h>
#include <v8.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "cgeohash_nanoseconds.hpp"

// http://stackoverflow.com/a/17112198
#ifdef __MACH__
#include <mach/mach_time.h>

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 0
int clock_gettime(int clk_id, struct timespec *t){
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);
    uint64_t time;
    time = mach_absolute_time();
    double nseconds = ((double)time * (double)timebase.numer)/((double)timebase.denom);
    double seconds = ((double)time * (double)timebase.numer)/((double)timebase.denom * 1e9);
    t->tv_sec = seconds;
    t->tv_nsec = nseconds;
    return 0;
}

#else

#include <time.h>

#endif

namespace cgeohash {
#undef NANOSEC
#define NANOSEC ((uint64_t) 1e9)
	
	uint64_t nanoseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (((uint64_t) ts.tv_sec) * NANOSEC + ts.tv_nsec);
	}

	double seconds_differience_of_nanoseconds(const uint64_t _nanoseconds) {
		const uint64_t _diff = nanoseconds() - _nanoseconds;
		const double   _seconds = ((double) _diff) / ((double) NANOSEC);
		return _seconds;
	}

} // end namespace cgeohash
