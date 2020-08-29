#include <fcntl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <unistd.h>

#include "cft_local_socket.h"
#include "cft_queues.h"

int setnonblock(int sock) {
   int flags;
   flags = fcntl(sock, F_GETFL, 0);
   if (-1 == flags)
      return -1;
   return fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

bool cft_local_socket_server_init(cft_local_socket_server_t* server_socket, const char *name)
{
    memset(server_socket, 0, sizeof(*server_socket));
    strcpy(server_socket->name_, "/tmp/");
    strcat(server_socket->name_, name);
    unlink(server_socket->name_);

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, server_socket->name_);

    if((server_socket->descriptor_ = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return false;
    }

    if ((bind(server_socket->descriptor_, (struct sockaddr *)&address, sizeof(address))) != 0) {
        return false;
    }

    if ((listen(server_socket->descriptor_, 100)) != 0) {
        return false;
    }

        struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(server_socket->descriptor_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    // Accept incoming connections.
    if((server_socket->connection_ = accept(server_socket->descriptor_, (struct sockaddr*)NULL, NULL)) < 0) {
        return false;
    }

    setnonblock(server_socket->connection_ );

    return true;

}

bool cft_local_socket_client_init(cft_local_socket_client_t* client_socket, const char *name)
{
    memset(client_socket, 0, sizeof(*client_socket));

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "/tmp/");
    strcat(address.sun_path, name);

    if((client_socket->descriptor_ = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return false;
    }

    while(connect(client_socket->descriptor_ , (struct sockaddr *)&address, sizeof(address)) != 0) {
        sleep(1);
    }

    return true;
}

void cft_local_socket_server_fini(cft_local_socket_server_t* server_socket)
{
    close(server_socket->connection_);
    close(server_socket->descriptor_);
    unlink(server_socket->name_);
}

void cft_local_socket_client_fini(cft_local_socket_client_t* client_socket)
{
    shutdown(client_socket->descriptor_, SHUT_RDWR);
    close(client_socket->descriptor_);
}

int cft_local_socket_server_read(cft_local_socket_server_t* socket, void* buffer, size_t size)
{
    return read(socket->connection_, buffer, size);
}

int cft_local_socket_server_write(cft_local_socket_server_t* socket, void* buffer, size_t size)
{
    return write(socket->connection_, buffer, size);
}

int cft_local_socket_client_read(cft_local_socket_client_t* socket, void* buffer, size_t size)
{
    return read(socket->descriptor_, buffer, size);
}

int cft_local_socket_client_write(cft_local_socket_client_t* socket, void* buffer, size_t size)
{
    return write(socket->descriptor_, buffer, size);
}

