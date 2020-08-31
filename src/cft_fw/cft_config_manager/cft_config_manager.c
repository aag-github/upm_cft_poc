#include <stdlib.h>
#include <stdio.h>

#include "cft_config_manager.h"
#include "cft_up_messages.h"
#include "cft_worker_manager.h"

char *xml_config = NULL;

bool cft_config_manager_init()
{
    xml_config = malloc(1024);
    sprintf(xml_config, "First config from test runner");
    return true;
}

void cft_config_manager_fini()
{
    free(xml_config);
}

void cft_config_manager_send_config_to_all_workers()
{
    cft_log("%s: sending config", __func__);
    for (size_t i = 0; i < cft_worker_manager_get_num_workers(); i++) {
        cft_message_sync_queue_t *data_queue = cft_worker_manager_get_worker_data_queue_by_index(i);

        // Send packet to UP
        int msg = DMT_CONFIG;
        int bytes_sent = cft_local_socket_client_write(data_queue, &msg, sizeof(msg));
        assert(bytes_sent > 0);
        bytes_sent = cft_local_socket_client_write(data_queue, (void*)xml_config, strlen(xml_config) + 1);
        assert(bytes_sent > 0);

        // Wait for response from UP
        int return_value = 0;
        bytes_sent = cft_local_socket_client_read(data_queue, (void*)&return_value, sizeof(return_value));
        assert(bytes_sent > 0);
        assert(return_value == DMT_RETURN_OK);
    }
    cft_log("%s: sending config done", __func__);
}
