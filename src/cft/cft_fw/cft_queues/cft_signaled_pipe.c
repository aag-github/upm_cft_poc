#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cft_queues.h"

bool cft_signaled_pipe_init(cft_signaled_pipe_t *self, const char *name, int signal)
{
    memset(self, 0, sizeof(*self));
    sprintf(self->name_, "/tmp/%s", name);
    return true;
}

void cft_signaled_pipe_fini(cft_signaled_pipe_t *self)
{
    if (self->pipe_descriptor_ > 0) {
        close(self->pipe_descriptor_);
    }
    unlink(self->name_);
}

bool cft_signaled_pipe_in_init(cft_signaled_pipe_in_t *self, const char *name, int signal_value, void (*handler)(int))
{
    if (!cft_signaled_pipe_init(&self->pipe_, name, signal_value)) {
        return false;
    }

    signal(signal_value, handler);

    self->pipe_.pipe_descriptor_ = open(self->pipe_.name_, O_RDONLY);

    return true;
}

void cft_signaled_pipe_in_fini(cft_signaled_pipe_in_t *self) {
    cft_signaled_pipe_fini(&self->pipe_);
}

cft_signaled_pipe_in_t* cft_signal_in_pipe_create()
{
    //TODO
    return NULL;
}
void cft_signalin_pipe_destroy(cft_signaled_pipe_in_t *self)
{
    //TODO
}

bool cft_signaled_pipe_out_init(cft_signaled_pipe_out_t *self, const char *name, int signal)
{
    if (!cft_signaled_pipe_init(&self->pipe_, name, signal)) {
        return false;
    }

    unlink(self->pipe_.name_);
    mkfifo(self->pipe_.name_, S_IRUSR | S_IWUSR);
    self->pipe_.pipe_descriptor_ = open(self->pipe_.name_, O_RDWR);

    return true;
}

void cft_signaled_pipe_out_fini(cft_signaled_pipe_out_t *self) {
    cft_signaled_pipe_fini(&self->pipe_);
}

cft_signaled_pipe_out_t* cft_signal_out_pipe_create()
{
    //TODO
    return NULL;
}
void cft_signal_pipe_out_destroy(cft_signaled_pipe_out_t *self)
{
    //TODO
}
