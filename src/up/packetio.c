#include "packetio.h"
#include "stats.h"

void packetio_handle_packet(packet_t *pkt)
{
    stats_increment_packet_counter();
}
