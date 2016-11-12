#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "app_scheduler.h"
#include "communicate.h"
#include "packet.h"
#include "packet_parser.h"
#include "ble_ebike.h"
#include "bles.h"

#define VERSION_MAJOR   1
#define VERSION_MINOR   0

void resolve(Packet_t * packet)
{
    PROTOCOL_COMMAND command_id;
    uint8_t *p_data;
    uint16_t length;
    packet = getReceivePacket();
    p_data = packet->data+HEADERS_LENGTH;
    length = packet->length-HEADERS_LENGTH-1;
    if(length>20)
    {
        packetClear(packet);
        return;
    }
    command_id = (PROTOCOL_COMMAND)(packet->data[L2_HEADER_OFFSET]);
    
    switch(command_id)
    {
        case COMMAND_01:
            ble_connection(NULL,0);
            break;
        case COMMAND_A:
            ble_ebike_battery_update(&m_ebike, p_data, length); 
            break;
        case COMMAND_B:
            ble_ebike_sensor_data_update(&m_ebike, p_data, length); 
            break;
        case COMMAND_C:
            ble_ebike_special_update(&m_ebike, p_data, length);  
            break;
        case COMMAND_D:
            ble_ebike_settings_update(&m_ebike, p_data, length); 
            break;
        case COMMAND_E:
            ble_ebike_error_update(&m_ebike, p_data, length);
            break;
        case COMMAND_F:
            ble_ebike_identifiers_update(&m_ebike, p_data, length); 
            break;
        case COMMAND_G:
            ble_ebike_serial_number_update(&m_ebike,p_data, length);
            break;
        case COMMAND_H:
            ble_ebike_feedback_update(&m_ebike, p_data, length);
            break;
        default:
            return_test(command_id,p_data, length);
            break;
    }

    packetClear(packet);
}

void return_test(PROTOCOL_COMMAND cmd_id,uint8_t *testValue,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = cmd_id;
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = testValue;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    send(); 

//    ble_ebike_battery_update(&m_ebike, testValue,length);    
}

void ble_connection(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    uint8_t connection = get_connect_state();
    l2.command = 0x01;
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = &connection;
    val.length = 1;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
//    app_sched_event_put(NULL,0,(app_sched_event_handler_t)send);
    send();
}
void navigation(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'I';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
//    app_sched_event_put(NULL,0,(app_sched_event_handler_t)send);
    send();
}
void navigation_b(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'J';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    
    send();
}
void message_info(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'K';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    send();
}
void message_data(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'L';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    send();
}
void computers_a(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'M';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    send();
}
void computers_b(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'N';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    send();
}
void feedback(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'O';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    send();
}
void time_sync(uint8_t *value,uint16_t length)
{
    Packet_L2_Header_t l2;
    Packet_Value_t val;
    l2.command = 'T';
    packetClear(getSendPacket());
    setL2Header(getSendPacket(),&l2);
    val.data = value;
    val.length = length;
    appendValue(getSendPacket(),&val);
    genL1Header(getSendPacket());
    send();
}
