#ifndef _BLES_H_
#define _BLES_H_
#include "ble_ebike.h"
#include "ble_devinfo.h"
extern ble_ebike_t   m_ebike;
extern ble_devinfo_t   m_devinfo;;

uint8_t get_connect_state(void);
void ble_init(void);

#endif
