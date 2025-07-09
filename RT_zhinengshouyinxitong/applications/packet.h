#ifndef PACKET
#define PACKET

#include "stm32f4xx_hal.h"


#define HEADER_SOF 0xA5
#define END1_SOF 0x0D
#define END2_SOF 0x0A
#define REF_PROTOCOL_HEADER_SIZE            sizeof(frame_header_struct_t)
#define REF_PROTOCOL_CRC16_SIZE             2
#define REF_HEADER_CRC_CMDID_LEN            (REF_PROTOCOL_HEADER_SIZE + REF_PROTOCOL_CRC16_SIZE + sizeof(uint16_t))

typedef  struct
{
    uint8_t SOF;
    uint8_t data_length;
    uint8_t seq;
    uint8_t CRC8;
}frame_header_struct_t;

typedef struct
{
    uint8_t end1;
} msg_end_info ;

typedef struct
{
    uint16_t id;
} vision_t;

typedef struct
{
    uint8_t nam_len;
    char name[10];
    uint16_t price;
}  charge_inf;

typedef struct
{
    uint8_t lens;
    char id[10];
} information;

void encode_send_data(uint16_t cmd_id, void* buf, uint16_t len);
void uart_queue_data(uint16_t cmd_id, void* buf, uint16_t len);
#endif /* APPLICATIONS_OPENMV_UART_H_ */
