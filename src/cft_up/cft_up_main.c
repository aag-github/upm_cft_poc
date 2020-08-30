#include "common_c.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cft_queues.h"
#include "cft_local_socket.h"
#include "cft_up_messages.h"

bool break_loop = false;

cft_message_async_queue_in_t  signal_in;

int ppid = 0;

cft_local_socket_server_t data_queue;

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

    sprintf(pipe_name, "up_data_in_%d", getpid());
    cft_local_socket_server_init(&data_queue, pipe_name);

    while(!break_loop) {
        printf("CHILD SLEEPING: my id is %d\n\n", getpid());
        sleep(5);
        printf("CHILD RUNNING: my id is %d\n", getpid());

        if (ppid != getppid()) {
            break;
        }

        int msg = 0;
        int read_result = cft_local_socket_server_read(&data_queue, &msg, sizeof(msg));
        printf("CHILD %d GOT READ RESULT: %d\n", getpid(), read_result);
        if (read_result > 0) {
            char config[1000];
            cft_local_socket_server_read(&data_queue, config, sizeof(config));
            printf("CHILD %d GOT CONFIG: %s\n", getpid(), config);
            int return_value = DMT_RETURN_OK;
            cft_local_socket_server_write(&data_queue, &return_value, sizeof(return_value));
        }

    }
    printf("UP done\n");

    cft_signaled_pipe_in_fini(&signal_in);
    cft_local_socket_server_fini(&data_queue);
}
