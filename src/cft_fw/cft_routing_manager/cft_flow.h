#ifndef CFT_FW_CFT_NET_CFT_FLOW_H_
#define CFT_FW_CFT_NET_CFT_FLOW_H_

#include "common_c.h"
#include "cft_packet.h"
#include "cft_worker.h"


struct cft_flow_s {
    cft_five_tuple_t five_tuple_;
    cft_worker_id_t next_hop_;
};

typedef struct cft_flow_s cft_flow_t;

bool cft_flow_init(cft_flow_t* self, cft_five_tuple_t five_tuple);

void cft_flow_fini();

cft_worker_id_t cft_flow_get_next_hop(cft_flow_t* self);

void cft_flow_set_next_hop(cft_flow_t* self, cft_worker_id_t next_hop);

const cft_five_tuple_t* cft_worker_id_get_five_tuple(cft_flow_t* self);

#endif /* CFT_FW_CFT_NET_CFT_PACKET_H_ */
