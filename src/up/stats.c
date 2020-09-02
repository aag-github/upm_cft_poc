#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "stats.h"

#define PKT_COUNT_SHMEM

char shmem_name[] = "packet_counter";
uint64_t* packet_counter = NULL;

void stats_init()
{
#if 0
    packet_counter = calloc(1, sizeof(*packet_counter));
#else
    int shm_fd = shm_open(shmem_name, O_CREAT | O_RDWR, 0666);
    void ftruncate(int, size_t);
    ftruncate(shm_fd, sizeof(uint64_t));
    packet_counter = (uint64_t*)mmap(0, sizeof(uint64_t), PROT_WRITE, MAP_SHARED, shm_fd, 0);
#endif
}

void stats_increment_packet_counter()
{
    ++(*packet_counter);
}

uint64_t stats_get_packet_counter()
{
    return (*packet_counter);
}

void stats_fini()
{
    shm_unlink(shmem_name);
}
