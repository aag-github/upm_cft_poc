#ifndef CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_H_
#define CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_H_

#include "common_c.h"
#include <sys/types.h>

#include "cft_logger.h"
#include "cft_queues.h"

typedef struct cft_worker_s cft_worker_t;

typedef size_t cft_worker_id_t;
#define BAD_WORKER_ID 0;

cft_worker_t* cft_worker_create(pid_t pid);

bool cft_worker_init(cft_worker_t* self, pid_t pid);

void cft_worker_destroy(cft_worker_t* self);

cft_worker_id_t cft_worker_get_id(cft_worker_t* self);

void cft_worker_stop_worker(cft_worker_t* self);

//bool cft_worker_is_alive(cft_worker_t* self);

//void cft_worker_send_heartbeat(cft_worker_t* self);

//void cft_worker_send_pause(cft_worker_t* self);

//void cft_worker_send_resume(cft_worker_t* self);

cft_message_sync_queue_t* cft_worker_get_data_queue(cft_worker_t* self);

void cft_worker_send_config(cft_worker_t* self, const char* config);

#endif /* CFT_FW_CFT_WORKER_MANAGER_CFT_WORKER_H_ */
