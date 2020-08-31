#ifndef CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_MANAGER_H_
#define CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_MANAGER_H_

#include "common_c.h"
#include "cft_worker.h"
#include "cft_queues.h"

bool cft_worker_manager_init();

void cft_worker_manager_fini();

cft_worker_id_t cft_worker_manager_start_new_worker();

bool cft_worker_manager_stop_worker (cft_worker_id_t id);

void cft_worker_manager_stop_all_workers();

//void send_heartbeat_to_all_workers : void();
//void pause_all_workers : void();
//void resume_all_workers : void();

size_t cft_worker_manager_get_num_workers();
cft_message_sync_queue_t* cft_worker_manager_get_worker_data_queue_by_index(size_t index);
cft_worker_id_t cft_worker_manager_get_worker_id(size_t index);

cft_message_sync_queue_t* cft_worker_manager_get_worker_data_queue_by_id(cft_worker_id_t id);

void cft_worker_manager_send_config_to_all_workers(const char *config);

cft_worker_t* cft_worker_manager_find_worker (cft_worker_id_t id);

#endif /* CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_MANAGER_H_ */
