#ifndef CFT_FW_CFT_QUEUES_CFT_LOCAL_SOCKET_H_
#define CFT_FW_CFT_QUEUES_CFT_LOCAL_SOCKET_H_

#include "common_c.h"
#include "cft_queues.h"

typedef int cft_local_socket_descriptor_t;

struct cft_local_socket_client_s {
    cft_local_socket_descriptor_t descriptor_;
};

struct cft_local_socket_server_s {
    char name_[QUEUE_NAME_MAX_SIZE];
    cft_local_socket_descriptor_t descriptor_;
    int connection_;
};


typedef struct cft_local_socket_client_s cft_local_socket_client_t;
typedef struct cft_local_socket_server_s cft_local_socket_server_t;

typedef cft_local_socket_client_t cft_message_sync_queue_t;

bool cft_local_socket_server_init(cft_local_socket_server_t* socket, const char *name);
void cft_local_socket_server_fini(cft_local_socket_server_t* socket);
int cft_local_socket_server_read(cft_local_socket_server_t* socket, void* buffer, size_t size);
int cft_local_socket_server_write(cft_local_socket_server_t* socket, void* buffer, size_t size);

bool cft_local_socket_client_init(cft_local_socket_client_t* socket, const char *name);
void cft_local_socket_client_fini(cft_local_socket_client_t* socket);
int cft_local_socket_client_read(cft_local_socket_client_t* socket, void* buffer, size_t size);
int cft_local_socket_client_write(cft_local_socket_client_t* socket, void* buffer, size_t size);

#endif /* CFT_FW_CFT_QUEUES_CFT_LOCAL_SOCKET_H_ */
