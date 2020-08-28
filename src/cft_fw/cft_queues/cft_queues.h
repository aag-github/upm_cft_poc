#ifndef CFT_FW_CFT_QUEUES_CFT_QUEUES_H_
#define CFT_FW_CFT_QUEUES_CFT_QUEUES_H_

#include <limits.h>
#include <signal.h>
#include "common_c.h"

#define QUEUE_NAME_MAX_SIZE 150

typedef int cft_pipe_descriptor_t;

struct cft_signaled_pipe_s {
    char name_[QUEUE_NAME_MAX_SIZE];
    cft_pipe_descriptor_t pipe_descriptor_;
};
typedef struct cft_signaled_pipe_s cft_signaled_pipe_t;

struct cft_signaled_pipe_in_s {
    cft_signaled_pipe_t pipe_;
};

struct cft_signaled_pipe_out_s {
    cft_signaled_pipe_t pipe_;
};


typedef struct cft_signaled_pipe_in_s cft_signaled_pipe_in_t;
typedef struct cft_signaled_pipe_out_s cft_signaled_pipe_out_t;

bool cft_signaled_pipe_in_init(cft_signaled_pipe_in_t *self, const char *name, int signal, void (*handler)(int));
void cft_signaled_pipe_in_fini(cft_signaled_pipe_in_t *self);
cft_signaled_pipe_in_t* cft_signal_in_pipe_create();
void cft_signal_pipe_in_destroy(cft_signaled_pipe_in_t *self);


bool cft_signaled_pipe_out_init(cft_signaled_pipe_out_t *self, const char *name, int signal);
void cft_signaled_pipe_out_fini(cft_signaled_pipe_out_t *self);
cft_signaled_pipe_out_t* cft_signal_out_pipe_create();
void cft_signal_pipe_out_destroy(cft_signaled_pipe_out_t *self);

#endif /* CFT_FW_CFT_QUEUES_CFT_QUEUES_H_ */
