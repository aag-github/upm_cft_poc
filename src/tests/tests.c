#include <stdio.h>
#include "et.h"
#include "cft.h"

TEST(TC1_config, 2)
{
    cft_config_manager_send_config_to_all_workers();
}

TEST(TC1_packet_send, 3)
{
    uint8_t raw_packets[4][3] = {
            { 1, 100, 80 },
            { 1, 80, 100 },
            { 1, 99, 22 },
            { 1, 22, 99 },
    };
    cft_packet_t packets[4];
    cft_packet_init(&packets[0], raw_packets[0], PKT_DIR_UPLINK);
    cft_packet_init(&packets[1], raw_packets[1], PKT_DIR_DOWNLINK);
    cft_packet_init(&packets[2], raw_packets[2], PKT_DIR_UPLINK);
    cft_packet_init(&packets[3], raw_packets[3], PKT_DIR_DOWNLINK);

    //Send packet 1 to worker 0 (by default we send any packet to worker 0)
    cft_packet_manager_send_packet(&packets[0]);
    //Send packet 2 to worker 1
    cft_routing_manager_add_flow(&packets[1].five_tuple_, cft_worker_manager_get_worker_id(1));
    cft_packet_manager_send_packet(&packets[1]);

    //Send packet 3 to worker 1
    cft_routing_manager_add_flow(&packets[2].five_tuple_, cft_worker_manager_get_worker_id(1));
    cft_packet_manager_send_packet(&packets[2]);
    //Send packet 4 to worker 0
    cft_flow_t* flow = cft_routing_manager_find_flow(&packets[3].five_tuple_);
    cft_flow_set_next_hop(flow, cft_worker_manager_get_worker_id(0));
    cft_packet_manager_send_packet(&packets[3]);

}
