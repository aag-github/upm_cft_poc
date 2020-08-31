#include <stdlib.h>
#include <unistd.h>

#include "cft_worker_manager.h"
#include "cft_up_main.h"
#include "cft_logger.h"

#define  MAX_WORKERS 5

size_t curr_worker_id = 0;

typedef struct cft_worker_manager_s {
    cft_worker_t* workers_[MAX_WORKERS];
} cft_worker_manager_t;


cft_worker_manager_t worker_manager_;

bool cft_worker_manager_init()
{
    memset(&worker_manager_, 0, sizeof(worker_manager_));
    return true;
}

void cft_worker_manager_fini()
{
    cft_worker_manager_stop_all_workers();
}

cft_worker_id_t cft_worker_manager_start_new_worker()
{
    cft_log("%s: Starting worker...", __func__);
    size_t i = 0;
    while(i < MAX_WORKERS && worker_manager_.workers_[i] != NULL) {
        ++i;
    }
    if (i >= MAX_WORKERS) {
        abort();
    }

    int fork_id = fork();
    if (fork_id == 0) {
        cft_log("%s: Started worker... %d\n", __func__,  getpid());
        cft_up_runner(i);
    } else {
        worker_manager_.workers_[i] = cft_worker_create(fork_id);
    }

    return fork_id;
}

bool cft_worker_manager_stop_worker (cft_worker_id_t id)
{
    return true;
}

void cft_worker_manager_stop_all_workers()
{
    cft_log("%s: stopping", __func__);
    for (size_t i = 0; i < MAX_WORKERS; i++) {
        if (worker_manager_.workers_[i]) {
            cft_worker_destroy(worker_manager_.workers_[i]);
        }
        worker_manager_.workers_[i] = NULL;
    }
    cft_log("%s: stopping done", __func__);
}

size_t cft_worker_manager_get_num_workers()
{
    size_t count = 0;
    for (size_t i = 0; i < MAX_WORKERS; i++) {
        if (worker_manager_.workers_[i]) {
            count++;
        }
    }
    return count;
}

cft_message_sync_queue_t* cft_worker_manager_get_worker_data_queue_by_id(cft_worker_id_t id)
{
    for (size_t i = 0; i < MAX_WORKERS; i++) {
        if (worker_manager_.workers_[i]) {
            if (cft_worker_get_id(worker_manager_.workers_[i]) == id) {
                return cft_worker_get_data_queue(worker_manager_.workers_[i]);
            }
        }
    }
    return NULL;
}

cft_message_sync_queue_t* cft_worker_manager_get_worker_data_queue_by_index(size_t index)
{
    size_t count = -1;
    for (size_t i = 0; i < MAX_WORKERS; i++) {
        if (worker_manager_.workers_[i]) {
            count++;
            if (count == index) {
                return cft_worker_get_data_queue(worker_manager_.workers_[i]);
            }
        }
    }
    return NULL;
}

cft_worker_id_t cft_worker_manager_get_worker_id(size_t index) {
    size_t count = -1;
    for (size_t i = 0; i < MAX_WORKERS; i++) {
        if (worker_manager_.workers_[i]) {
            count++;
            if (count == index) {
                return cft_worker_get_id(worker_manager_.workers_[i]);
            }
        }
    }
    return BAD_WORKER_ID;
}

cft_worker_t* cft_worker_manager_find_worker(cft_worker_id_t id)
{
    for (size_t i = 0; i < MAX_WORKERS; i++) {
        if (worker_manager_.workers_[i]) {
            if (cft_worker_get_id(worker_manager_.workers_[i]) == id) {
                return worker_manager_.workers_[i];
            }
        }
    }
    return NULL;
}
