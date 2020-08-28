#include "common_c.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cft_queues.h"
#include "cft_up_messages.h"

bool break_loop = false;

cft_signaled_pipe_in_t  signal_in;

int ppid = 0;

void cft_up_signal_handler(int signo)
{
    printf("received SIGUSR1!!!!!!!!!!!!!!!!!!!!!!!! %d\n", getpid());

    int msg_type;
    read(signal_in.pipe_.pipe_descriptor_, &msg_type, sizeof(msg_type));

    switch (msg_type) {
    case SMT_KILL:
        printf("request to kill %d\n", getpid());
        break_loop = true;
        break;
    case SMT_HEARTBEAT:
        printf("%d received heartbeat\n", getpid());
        break;
    default:
        printf("********** %d msgt %d\n", getpid(), signal_in.pipe_.pipe_descriptor_);
        assert(false);
    }
}

void cft_up_runner()
{
    ppid = getppid();

    char pipe_name[QUEUE_NAME_MAX_SIZE];
    sprintf(pipe_name, "up_signal_in_%d", getpid());
    cft_signaled_pipe_in_init(&signal_in, pipe_name, SIGUSR1, cft_up_signal_handler);

    while(!break_loop) {
        sleep(3);
        printf("CHILD RUNNING: my id is %d\n", getpid());

        if (ppid != getppid()) {
            break;
        }
    }
    printf("UP done\n");

    cft_signaled_pipe_in_fini(&signal_in);
}
