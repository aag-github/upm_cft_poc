#include "common_c.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cft_queues.h"

bool break_loop = false;

cft_pipe_t signal_in = 0;
cft_pipe_t signal_out = 0;


void user_plane_signal_handler(int signo)
{
    if (signo == SIGUSR1) {
        break_loop = true;
        printf("received SIGUSR1!!!!!!!!!!!!!!!!!!!!!!!! %d\n", getpid());

        int signal_type;
        read(signal_in, &signal_type, sizeof(signal_type));

        printf("received type: %d\n", signal_type);

    }
}

void user_plane_runner() {

    signal(SIGUSR1, user_plane_signal_handler);

    char pipe_name[100];
    sprintf(pipe_name, "/tmp/up_signal_in_%d", getpid());
    signal_in = open(pipe_name, O_RDONLY);

    sprintf(pipe_name, "/tmp/up_signal_out_%d", getpid());
    mkfifo(pipe_name, S_IRUSR | S_IWUSR);
    signal_out = open(pipe_name, O_RDWR);



    while(!break_loop) {
        sleep(3);
        printf("CHILD RUNNING: my id is %d\n", getpid());
    }
    printf("UP done\n");

    close(signal_in);
    close(signal_out);

}
