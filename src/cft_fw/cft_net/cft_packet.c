#include "cft_packet.h"

bool cft_five_tuple_is_equal(cft_five_tuple_t *first, cft_five_tuple_t *second)
{
    return first->proto == second->proto
           && first->src_port_== second->src_port_
           && first->dst_port_== second->dst_port_;
}

void cft_five_tuple_from_packet(cft_five_tuple_t *self, uint8_t *raw_packet, bool uplink)
{
    self->proto = raw_packet[0];
    if (uplink) {
        self->src_port_ = raw_packet[1];
        self->dst_port_ = raw_packet[2];
    } else {
        self->src_port_ = raw_packet[2];
        self->dst_port_ = raw_packet[1];
    }
}

void cft_packet_init(cft_packet_t* self, uint8_t *raw_packet, bool uplink)
{
    assert(raw_packet);
    self->raw_packet_ = raw_packet;
    self->uplink_ = uplink;
    cft_five_tuple_from_packet(&self->five_tuple_, raw_packet, uplink);
}
