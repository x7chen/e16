#ifndef _PACKET_PARSER_H_
#define _PACKET_PARSER_H_
#include "stdint.h"
#include "packet.h"

#define L1VERSION       (0)
#define L2VERSION       (0)
/* Command ID */
typedef enum {
    COMMAND_01= 0x01,
    COMMAND_A= 'A',
    COMMAND_B= 'B',
    COMMAND_C= 'C',
    COMMAND_D= 'D',
    COMMAND_E= 'E',
    COMMAND_F= 'F',
    COMMAND_G= 'G',
    COMMAND_H= 'H',
    COMMAND_I= 'I',
    COMMAND_J= 'J',
    COMMAND_K= 'K',
    COMMAND_L= 'L',
    COMMAND_M= 'M',
    COMMAND_N= 'N',
    COMMAND_O= 'O',  
}PROTOCOL_COMMAND;

void resolve(Packet_t * packet);

void return_test(PROTOCOL_COMMAND cmd_id,uint8_t *testValue,uint16_t length);
void ble_connection(uint8_t *value,uint16_t length);
void navigation(uint8_t *value,uint16_t length);
void navigation_b(uint8_t *value,uint16_t length);
void message_info(uint8_t *value,uint16_t length);
void message_data(uint8_t *value,uint16_t length);
void computers_a(uint8_t *value,uint16_t length);
void computers_b(uint8_t *value,uint16_t length);
void feedback(uint8_t *value,uint16_t length);
void time_sync(uint8_t *value,uint16_t length);

#endif
