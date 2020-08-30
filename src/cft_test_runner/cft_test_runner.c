#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <stdint.h>

#include "cft_config_manager.h"
#include "cft_worker_manager.h"


void dummy_test() {
    printf("Press enter to send config %d\n", getpid());
    getchar();
    cft_config_manager_send_config_to_all_workers();
    printf("Press enter to exit %d\n", getpid());
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
        cft_log("%s: Worker loop\n", __func__);
    }

    return 0;
}



