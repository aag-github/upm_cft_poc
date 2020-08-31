#include "cft_logger.h"
#include "cft_queues.h"
#include "cft_packet_manager.h"
#include "cft_up_messages.h"
#include "cft_worker_manager.h"

void cft_packet_manager_send_packet(cft_packet_t *packet)
{
    cft_log("%s: sending packet", __func__);
    size_t worker = 0;//cft_routing_manager_get_worker_index(packet);

    cft_message_sync_queue_t *data_queue = cft_worker_manager_get_worker_data_queue(worker);

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
