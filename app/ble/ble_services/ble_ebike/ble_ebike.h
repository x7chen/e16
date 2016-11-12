
#ifndef BLE_EBIKE_H__
#define BLE_EBIKE_H__

#include "ble.h"
#include "ble_srv_common.h"
#include <stdint.h>
#include <stdbool.h>

#define BLE_UUID_EBIKE_SERVICE 0x1501                      /**< The UUID of the Nordic UART Service. */
#define BLE_EBIKE_MAX_DATA_LEN (GATT_MTU_SIZE_DEFAULT - 3) /**< Maximum length of data (in bytes) that can be transmitted to the peer by the Nordic UART service module. */

typedef struct ble_ebike_s ble_ebike_t;

typedef void (*ble_ebike_data_handler_t) (ble_ebike_t * p_ebike, uint8_t * p_data, uint16_t length);

typedef struct
{
    bool                          is_notification_enabled;
} ble_ebike_init_t;


struct ble_ebike_s
{
    uint8_t                  uuid_type;               /**< UUID type for Nordic UART Service Base UUID. */
    uint16_t                 service_handle;          /**< Handle of Nordic UART Service (as provided by the S110 SoftDevice). */
    ble_gatts_char_handles_t battery_handles;
	ble_gatts_char_handles_t sensor_data_handles;
	ble_gatts_char_handles_t special_handles;
	ble_gatts_char_handles_t settings_handles;
	ble_gatts_char_handles_t error_handles;
	ble_gatts_char_handles_t identifiers_handles;
	ble_gatts_char_handles_t serial_number_handles;
	ble_gatts_char_handles_t feedback_handles;
    uint16_t                 conn_handle;             /**< Handle of the current connection (as provided by the S110 SoftDevice). BLE_CONN_HANDLE_INVALID if not in a connection. */
    bool                     is_notification_enabled; /**< Variable to indicate if the peer has enabled notification of the RX characteristic.*/
};


uint32_t ble_ebike_init(ble_ebike_t * p_ebike, const ble_ebike_init_t * p_ebike_init);


void ble_ebike_on_ble_evt(ble_ebike_t * p_ebike, ble_evt_t * p_ble_evt);


uint32_t ble_ebike_battery_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);
uint32_t ble_ebike_sensor_data_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);
uint32_t ble_ebike_special_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);
uint32_t ble_ebike_settings_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);
uint32_t ble_ebike_error_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);
uint32_t ble_ebike_identifiers_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);
uint32_t ble_ebike_serial_number_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);
uint32_t ble_ebike_feedback_update(ble_ebike_t * p_ebike, uint8_t * p_dat, uint16_t length);

#endif 

/** @} */
