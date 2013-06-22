#ifndef _NODE_CGEOHASH_NANOSECONDS_HPP
#define _NODE_CGEOHASH_NANOSECONDS_HPP

#include <node.h>
#include <string>

namespace cgeohash {

// Compute nanoseconds at current time
uint64_t nanoseconds();

double seconds_differience_of_nanoseconds(const uint64_t _nanoseconds);

} // end namespace cgeohash

#endif /* end hpp */
