#ifndef LORAWAN_DEF_H
#define LORAWAN_DEF_H

#include <LoRaWan-RAK4630.h>

// macros
#define ENABLE_OTAA                 true
#define EVENT_QUEUE_MAX_DATA_SIZE   APP_TIMER_SCHED_EVENT_DATA_SIZE 
#define EVENT_QUEUE_SIZE            60
#define LORAWAN_START_DR            LORAWAN_DEFAULT_DATARATE									  
#define LORAWAN_START_POWER         LORAWAN_DEFAULT_TX_POWER							
#define JOIN_REQUEST_TRIALS         3
#define LORAWAN_APP_DATA_BUFF_SIZE  64              


/////////////////////
// device specific //
/////////////////////
#define DEVICE_EUI     {0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x33, 0x33};
#define JOIN_EUI       {0xB8, 0x27, 0xEB, 0xFF, 0xFE, 0x39, 0x00, 0x00};
#define APP_KEY        {0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88}; // AES key

#endif // LORAWAN_DEF_H