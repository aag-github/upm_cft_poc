#include <stdlib.h>
#include "cft_routing_manager.h"

struct cft_flow_hash_map_s {
    cft_flow_t* flows;
    size_t size;
};

typedef struct cft_flow_hash_map_s cft_flow_hash_map_t;

cft_flow_hash_map_t routing_table;

bool cft_routing_manager_init()
{
    routing_table.flows = NULL;
    routing_table.size = 0;
    return true;
}

void cft_routing_manager_fini()
{
    free(routing_table.flows);
}

cft_flow_t* cft_routing_manager_add_flow(const cft_five_tuple_t* five_tuple, cft_worker_id_t next_hop)
{
    if (cft_routing_manager_find_flow(five_tuple)) {
        return NULL;
    }

    ++routing_table.size;
    routing_table.flows = realloc(routing_table.flows, sizeof(cft_flow_t) * routing_table.size);

    cft_flow_t* new_flow = &routing_table.flows[routing_table.size - 1];
    cft_flow_init(new_flow, *five_tuple);
    cft_flow_set_next_hop(new_flow, next_hop);

    return new_flow;
}

cft_flow_t* cft_routing_manager_find_flow(const cft_five_tuple_t* five_tuple)
{
    int i = 0;
    cft_flow_t* ret = NULL;

    while(i < routing_table.size) {
        if (cft_five_tuple_is_equal(five_tuple, &routing_table.flows[i].five_tuple_)) {
            return &routing_table.flows[i];
        }
        ++i;
    }

    return ret;
}
