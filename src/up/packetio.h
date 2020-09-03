#ifndef UP_PACKETIO_H_
#define UP_PACKETIO_H_

#include <inttypes.h>

struct packet_s {
    uint8_t* pkt;
};

typedef struct packet_s packet_t;

void packetio_handle_packet(packet_t *pkt);

#endif /* UP_PACKETIO_H_ */
