#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <stdint.h>

#include "cft_config_manager.h"
#include "cft_packet_manager.h"
#include "cft_worker_manager.h"
#include "cft_routing_manager.h"
#include "et.h"

int run_test(void(*test)(), size_t num_workers)
{
    for(int i = 0; i < num_workers; i++) {
        cft_worker_id_t id = cft_worker_manager_start_new_worker() ;
        if( id == 0) {
            return 0;
        }
    }

    test();

    cft_routing_manager_clean();

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

    const size_t size = et_test_case_count();
    test_case_t* test_cases[size];
    memset(test_cases, 0, sizeof(test_case_t*) * size);
    et_get_all_tests(&test_cases, size);

    cft_log("%s: Starting test loop\n", __func__);
    for(int i = 0; i < size; i++) {
        cft_log("%s: ======== running test %s ========\n", __func__, test_cases[i]->name);
        if(1 == run_test(test_cases[i]->func, test_cases[i]->num_workers)) {
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



