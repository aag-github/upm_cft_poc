#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <stdint.h>

#include "cft_config_manager.h"
#include "cft_packet_manager.h"
#include "cft_worker_manager.h"


void dummy_test() {
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

    printf("Press enter to send config %d\n", getpid());
    getchar();
    cft_config_manager_send_config_to_all_workers();
    printf("Press enter to exit %d\n", getpid());

    //Send packet 1 to worker 0
    cft_packet_manager_send_packet(&packets[0]);
    //Send packet 2 to worker 1
    cft_packet_manager_send_packet(&packets[1]);
    //Send packet 3 to worker 0
    cft_packet_manager_send_packet(&packets[2]);
    //Send packet 4 to worker 0
    cft_packet_manager_send_packet(&packets[3]);
    getchar();
}

int run_test(void(*test)(), size_t num_workers)
{
    for(int i = 0; i < num_workers; i++) {
        cft_worker_id_t id = cft_worker_manager_start_new_worker() ;
        if( id == 0) {
            return 0;
        }
    }

    test();
    return 1;
}

void cft_fw_init()
{
    cft_worker_manager_init();
    cft_config_manager_init();
}

void cft_fw_fini()
{
    cft_worker_manager_fini();
    cft_config_manager_fini();
}

int test_runner()
{
    cft_fw_init();

    pid_t me = getpid();

    cft_log("%s: Starting test loop\n", __func__);
    // For each test.... {
    for(int i = 2; i <= 2; i++) {
        cft_log("%s", "running first test\n");
        if(1 == run_test(dummy_test, i)) {
            cft_worker_manager_stop_all_workers();
        } else {
            break;
        }
    }

    if(me == getpid()) {
        cft_log("%s: Test loop finished\n", __func__);
        cft_fw_fini();
    } else {
        cft_log("%s: Test runner worker loop %d\n", __func__, getpid());
    }

    return 0;
}



