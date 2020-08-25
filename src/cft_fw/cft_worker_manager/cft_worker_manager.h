#ifndef CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_MANAGER_H_
#define CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_MANAGER_H_

#include "common_c.h"
#include "cft_worker.h"

bool cft_worker_manager_init();

void cft_worker_manager_fini();

cft_worker_id_t cft_worker_manager_start_new_worker();

bool cft_worker_manager_stop_worker (cft_worker_id_t id);

void cft_worker_manager_stop_all_workers();

//void send_heartbeat_to_all_workers : void();
//void pause_all_workers : void();
//void resume_all_workers : void();
//void get_worker_data_queue : cft_msg_sync_queue_t(cft_worker_id_t worker_id);

#endif /* CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_MANAGER_H_ */
