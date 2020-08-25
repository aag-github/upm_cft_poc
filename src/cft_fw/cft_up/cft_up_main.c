#include "common_c.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cft_queues.h"

bool break_loop = false;

cft_signaled_pipe_in_t  signal_in;
cft_signaled_pipe_out_t signal_out;


void user_plane_signal_handler(int signo)
{
    if (signo == SIGUSR1) {
        break_loop = true;
        printf("received SIGUSR1!!!!!!!!!!!!!!!!!!!!!!!! %d\n", getpid());

        int signal_type;
        read(signal_in.pipe_.pipe_descriptor_, &signal_type, sizeof(signal_type));

        printf("received type: %d\n", signal_type);

    }
}

void user_plane_runner() {

    signal(SIGUSR1, user_plane_signal_handler);

    cft_signaled_pipe_in_init(&signal_in, "up_signal_in", SIGUSR1);
    cft_signaled_pipe_out_init(&signal_out, "up_signal_out", SIGUSR1);


    while(!break_loop) {
        sleep(3);
        printf("CHILD RUNNING: my id is %d\n", getpid());
    }
    printf("UP done\n");

    cft_signaled_pipe_in_fini(&signal_in);
    cft_signaled_pipe_out_fini(&signal_out);

}
