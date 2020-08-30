#ifndef CFT_FW_CFT_QUEUES_CFT_QUEUES_H_
#define CFT_FW_CFT_QUEUES_CFT_QUEUES_H_

#include "cft_local_socket.h"
#include "cft_signaled_pipe.h"

typedef cft_local_socket_client_t cft_message_sync_queue_t;

typedef cft_signaled_pipe_in_t cft_message_async_queue_in_t;
typedef cft_signaled_pipe_out_t cft_message_async_queue_out_t;

#endif /* CFT_FW_CFT_QUEUES_CFT_QUEUES_H_ */
