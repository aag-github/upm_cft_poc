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
cft_signaled_pipe_out_t signal_out;


void user_plane_signal_handler(int signo)
{
    if (signo == SIGUSR1) {
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
}

void user_plane_runner() {

    signal(SIGUSR1, user_plane_signal_handler);

    char pipe_name[QUEUE_NAME_MAX_SIZE];
    sprintf(pipe_name, "up_signal_out_%d", getpid());
    cft_signaled_pipe_out_init(&signal_out, pipe_name, SIGUSR1);
    sprintf(pipe_name, "up_signal_in_%d", getpid());
    cft_signaled_pipe_in_init(&signal_in, pipe_name, SIGUSR1);


    while(!break_loop) {
        sleep(3);
        printf("CHILD RUNNING: my id is %d\n", getpid());
    }
    printf("UP done\n");

    cft_signaled_pipe_in_fini(&signal_in);
    cft_signaled_pipe_out_fini(&signal_out);

}
