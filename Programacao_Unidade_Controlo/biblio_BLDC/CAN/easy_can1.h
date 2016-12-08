#ifndef __MODULE_EASY_CAN1_H__
#define __MODULE_EASY_CAN1_H__

#define EASY_CAN1_MSG_EXTENDED_ID (1LL << 31)
#define EASY_CAN1_MSG_RTR         (1LL << 30)

typedef struct
{
        unsigned long id;
        unsigned long data_length;
        unsigned long reserved;
        unsigned char data[8];
        unsigned Request;
} EASY_CAN1_MSG;

void easy_can1_init_remap(unsigned int speed_ratio, unsigned char tx_pin, unsigned char rx_pin,unsigned char enable_pin, unsigned char en);
void easy_can1_init(unsigned int speed_ratio, unsigned char enable_pin, unsigned char en);
void easy_can1_fundamental(unsigned int speed_ratio);
void conf_transceiver(unsigned char enable_pin, unsigned char en);

int easy_can1_send_msg(EASY_CAN1_MSG *msg);
int easy_can1_recv_msg(EASY_CAN1_MSG *msg);

#endif
