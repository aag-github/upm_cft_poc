#ifndef CFT_UP_STATS_H_
#define CFT_UP_STATS_H_

#include <inttypes.h>

void stats_init();

void stats_increment_packet_counter();

uint64_t stats_get_packet_counter();

void stats_fini();

#endif /* CFT_UP_STATS_H_ */
