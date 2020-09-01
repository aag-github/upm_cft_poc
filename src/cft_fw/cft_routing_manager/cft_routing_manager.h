#ifndef CFT_FW_CFT_ROUTING_MANAGER_CFT_ROUTING_MANAGER_H_
#define CFT_FW_CFT_ROUTING_MANAGER_CFT_ROUTING_MANAGER_H_

#include "cft_flow.h"
#include "cft_packet.h"
#include "common_c.h"

bool cft_routing_manager_init();

void cft_routing_manager_fini();

void cft_routing_manager_clean();

cft_flow_t* cft_routing_manager_add_flow(const cft_five_tuple_t* five_tuple, cft_worker_id_t next_hop);

cft_flow_t* cft_routing_manager_find_flow(const cft_five_tuple_t* five_tuple);

#endif /* CFT_FW_CFT_ROUTING_MANAGER_CFT_ROUTING_MANAGER_H_ */
