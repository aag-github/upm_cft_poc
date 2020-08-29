#ifndef CFT_FW_CFT_UP_CFT_UP_MESSAGES_H_
#define CFT_FW_CFT_UP_CFT_UP_MESSAGES_H_

enum cft_up_signal_message_type {
    SMT_KILL = 1,
    SMT_HEARTBEAT,
    SMT_PAUSE_PACKET_PROCESS,
    SMT_RESUME_PACKET_PROCESS,
};

enum cft_up_data_message_type {
    DMT_CONFIG = 1,
    DMT_PACKET,
    DMT_RETURN_OK,
    DMT_RETURN_FAIL
};

#endif /* CFT_FW_CFT_UP_CFT_UP_MESSAGES_H_ */
