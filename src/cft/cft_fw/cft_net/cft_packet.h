#ifndef CFT_FW_CFT_NET_CFT_PACKET_H_
#define CFT_FW_CFT_NET_CFT_PACKET_H_

#include "common_c.h"

enum {
    PKT_DIR_DOWNLINK = 0,
    PKT_DIR_UPLINK = 1,
} cft_pkt_direction_t;

//TODO: Esto no es una implementación real de una five tuple, es solo una simplificación para poder probar el
//      cft_router_manager
struct cft_five_tuple_s {
    uint8_t proto;
    //int src_ip_;
    //int dst_ip_;
    uint16_t src_port_;
    uint16_t dst_port_;
};
typedef struct cft_five_tuple_s cft_five_tuple_t;

bool cft_five_tuple_is_equal(const cft_five_tuple_t *first, const cft_five_tuple_t *second);

struct cft_packet_s {
    uint8_t* raw_packet_;
    bool uplink_;
    cft_five_tuple_t five_tuple_;

};

typedef struct cft_packet_s cft_packet_t;

void cft_packet_init(cft_packet_t* self, uint8_t *raw_packet, bool uplink);

#endif /* CFT_FW_CFT_NET_CFT_PACKET_H_ */
