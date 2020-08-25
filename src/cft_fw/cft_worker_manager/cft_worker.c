#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cft_worker.h"
#include "cft_logger.h"
#include "cft_queues.h"
#include "cft_up_messages.h"


struct cft_worker_s {
    pid_t pid_;
    cft_signaled_pipe_out_t signal_to_up;
};

bool cft_worker_init(cft_worker_t* self, pid_t pid)
{
    self->pid_ = pid;

    char pipe_name[QUEUE_NAME_MAX_SIZE];
    sprintf(pipe_name, "up_signal_in_%d", self->pid_);
    cft_signaled_pipe_out_init(&self->signal_to_up, pipe_name, SIGUSR1);

    return true;
}

void cft_worker_fini(cft_worker_t* self)
{
}

cft_worker_id_t cft_worker_get_id(cft_worker_t* self)
{
    return self->pid_;
}

cft_worker_t* cft_worker_create(pid_t pid)
{
    cft_worker_t* worker = calloc(1, sizeof(cft_worker_t));

    if (!cft_worker_init(worker, pid)) {
        free(worker);
        worker = NULL;
    }

    return worker;
}

void cft_worker_stop_worker(cft_worker_t* self)
{
    cft_log("%s: Process %d stopping worker... %d\n", __func__, getpid(), self->pid_);

    int kill_signal = SMT_KILL;
    write(self->signal_to_up.pipe_.pipe_descriptor_, &kill_signal, sizeof(kill_signal));
    kill(self->pid_, SIGUSR1);

    int status = 0;
    waitpid(self->pid_, &status, 0);
}

void cft_worker_destroy(cft_worker_t* self)
{
    cft_worker_stop_worker(self);

    cft_signaled_pipe_out_fini(&self->signal_to_up);
}
