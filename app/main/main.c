#include <stdint.h>
#include <string.h>
#include "app_error.h"
#include "app_scheduler.h"
#include "softdevice_handler.h"
#include "app_timer.h"
#include "nrf_delay.h"
#include "boards.h"
#include "nrf_drv_gpiote.h"
#include "bles.h"
#include "communicate.h"
#include "packet_parser.h"
#include "clock.h"
#include "alarm.h"
#include "wdt.h"
#include "app_uart.h"

#define APP_TIMER_PRESCALER             0                               /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE         4                               /**< Size of timer operation queues. */
#define SCHED_MAX_EVENT_DATA_SIZE       8       /**< Maximum size of scheduler events. Note that scheduler BLE stack events do not contain any data, as the events are being pulled from the stack in the event handler. */
#define SCHED_QUEUE_SIZE                10                               /**< Maximum number of events in the scheduler queue. */

static clock_callbacks_t clock_callbacks;

uint8_t mock_val_1[10] = {0x00,0x14,0x01,0x00,0x20,0x33,0x00,0x00,0x00,0x01};
uint8_t mock_val_2[17] = {  0x00,0x87,0x00,0x56,0x00,0x33,0x00,0x08,0x00,0x15, \
                                0x01,0x00,0x12,0x00,0x00,0x15,0x16};
uint8_t mock_val_3[7] = {0x00,0x00,0x00,0x01,0x08,0x04,0x78};
uint8_t mock_val_4[4] = {0x6D,0x75,0x6C,0x00};
uint8_t mock_val_5[20] = {  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t mock_val_6[10] = {0x00,0x01,0x00,0x18,0x01,0x02,0x03,0x04,0x07,0x01};
uint8_t mock_val_7[20] = {  0x01,0x10,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,\
                                0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x00,0x00};  
uint8_t mock_val_8[3] = {0xff,0xff,0xff};
void mock(uint32_t sec)
{
    mock_val_1[0] = sec;
    mock_val_2[0] = sec;
    mock_val_3[0] = sec;
    mock_val_4[0] = sec;
    mock_val_5[0] = sec;
    mock_val_6[0] = sec;
    mock_val_7[0] = sec;
    mock_val_8[0] = sec;
    if(sec%10==0)
    ble_ebike_battery_update(&m_ebike, mock_val_1, 10);
    if(sec%10==1)
    ble_ebike_sensor_data_update(&m_ebike, mock_val_2, 17);
    if(sec%10==2)
    ble_ebike_special_update(&m_ebike, mock_val_3, 7);
    if(sec%10==3)
    ble_ebike_settings_update(&m_ebike, mock_val_4, 4);
    if(sec%10==4)
    ble_ebike_error_update(&m_ebike, mock_val_5, 20);
    if(sec%10==5)
    ble_ebike_identifiers_update(&m_ebike, mock_val_6, 10);
    if(sec%10==6)
    ble_ebike_serial_number_update(&m_ebike, mock_val_7, 20);
    if(sec%10==7)
    ble_ebike_feedback_update(&m_ebike, mock_val_8, 3);
}
/*
#define APP_TIMER_PRESCALER 0
#define TEST_TIMER_INTERVAL         APP_TIMER_TICKS(100, APP_TIMER_PRESCALER)
static app_timer_id_t test_timer_id;
static void test_timer_handle(void *p_context)
{
    static uint32_t timer = 0;
    timer++;
//    mock(timer);
    ble_ebike_battery_update(&m_ebike, mock_val_1, 10);
}
void test_timer_init(void)
{
	uint32_t err_code;
	err_code = app_timer_create(&test_timer_id, APP_TIMER_MODE_REPEATED,test_timer_handle);
	APP_ERROR_CHECK(err_code);
	err_code = app_timer_start(test_timer_id, TEST_TIMER_INTERVAL, NULL);
	APP_ERROR_CHECK(err_code);

}
*/
void second_handler(uint32_t second)
{
    wdt_feed();
    if(second%5==0)
    {
        //ble_connection(NULL,0);
    }
    //mock(second);
}
void minute_handle(uint32_t minute)
{
    check_alarm();
    //
}
void hour_handle(uint32_t hour)
{

}

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module. This creates and starts application timers.
 */
static void timers_init(void)
{
    // Initialize timer module.
    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
}


/**@brief Function for starting timers.
*/
static void register_clock_event(void)
{
    clock_callbacks.on_second_update =  (clock_callback_t)second_handler;
    clock_callbacks.on_minute_update = (clock_callback_t)minute_handle;
    clock_callbacks.on_hour_update = (clock_callback_t)hour_handle;
    register_clock_callbacks(&clock_callbacks);
}

static void scheduler_init(void)
{
    APP_SCHED_INIT(SCHED_MAX_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
}

/**@brief Function for the Power manager.
 */
static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for application main entry.
 */
int main(void)
{
//    uint32_t err_code;
    nrf_delay_ms(500);
                                        
    nrf_drv_gpiote_uninit();
    timers_init();
    scheduler_init();
    ble_init();
    system_clock_init();
    wdt_init(); 
    wdt_start();
    register_clock_event();
    communicateInit();

    for (;;)
    {
        app_sched_execute();
        power_manage();
    }
}
