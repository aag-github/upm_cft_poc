#ifndef CFT_FW_CFT_CONFIG_MANAGER_CFT_CONFIG_MANAGER_H_
#define CFT_FW_CFT_CONFIG_MANAGER_CFT_CONFIG_MANAGER_H_

#include "common_c.h"

bool cft_config_manager_init();

void cft_config_manager_fini();

void cft_config_manager_send_config_to_all_workers();

#endif /* CFT_FW_CFT_CONFIG_MANAGER_CFT_CONFIG_MANAGER_H_ */
