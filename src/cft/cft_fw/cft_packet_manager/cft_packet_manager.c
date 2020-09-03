#include "cft_logger.h"
#include "cft_queues.h"
#include "cft_packet_manager.h"
#include "cft_up_messages.h"
#include "cft_worker_manager.h"
#include "cft_routing_manager.h"

void cft_packet_manager_send_packet(cft_packet_t *packet)
{
    cft_log("%s: sending packet", __func__);

    cft_message_sync_queue_t *data_queue;
    cft_flow_t *flow = cft_routing_manager_find_flow(&packet->five_tuple_);
    if(flow) {
        data_queue = cft_worker_manager_get_worker_data_queue_by_id(flow->next_hop_);
    } else {
        data_queue = cft_worker_manager_get_worker_data_queue_by_index(0);
    }

    // Send packet to UP
    int msg = DMT_PACKET;
    int bytes_sent = cft_local_socket_client_write(data_queue, &msg, sizeof(msg));
    assert(bytes_sent > 0);
    bytes_sent = cft_local_socket_client_write(data_queue, (void*)packet, sizeof(*packet));
    assert(bytes_sent > 0);

    // Wait for response from UP
    int return_value = 0;
    bytes_sent = cft_local_socket_client_read(data_queue, (void*)&return_value, sizeof(return_value));
    assert(bytes_sent > 0);
    assert(return_value == DMT_RETURN_OK);

    cft_log("%s: sending packet done", __func__);
}
