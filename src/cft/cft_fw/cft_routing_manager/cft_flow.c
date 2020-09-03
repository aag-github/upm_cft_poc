#include "cft_flow.h"

bool cft_flow_init(cft_flow_t* self, cft_five_tuple_t five_tuple)
{
    self->five_tuple_ = five_tuple;
    self->next_hop_ = BAD_WORKER_ID;
    return true;
}

void cft_flow_fini()
{

}

cft_worker_id_t cft_flow_get_next_hop(cft_flow_t* self)
{
    return self->next_hop_;
}

void cft_flow_set_next_hop(cft_flow_t* self, cft_worker_id_t next_hop)
{
    self->next_hop_ = next_hop;
}

const cft_five_tuple_t* cft_worker_id_get_five_tuple(cft_flow_t* self)
{
    return &self->five_tuple_;
}
