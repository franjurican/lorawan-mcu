#ifndef LORAWAN_COMM_H
#define LORAWAN_COMM_H

#include <Arduino.h>
#include <LoRaWan-RAK4630.h>
#include "lorawan_def.h"

class LoRaWanCommunication 
{
    private:
        /*
            some internal definitions
        */
        lmh_param_t lora_params;
        DeviceClass_t device_class;
        LoRaMacRegion_t lora_region;
        lmh_callback_t lora_callbacks;


        /*
            OTAA credentials
        */
        uint8_t device_EUI[8] = DEVICE_EUI;
        uint8_t join_EUI[8]   = JOIN_EUI;
        uint8_t app_key[16]   = APP_KEY;


        /*
            default callbacks
        */
        static void lorawanHasJoined();
        static void lorawanJoinFailed();
        static void lorawanRx(lmh_app_data_t *app_data);
        static void lorawanConfirmClass(DeviceClass_t Class);


    public:
        /*
            Enumeration describing possible erros.
            LORA_OK - everything is OK
            LORA_CHIP_INIT - error initializing Lora communication chip
            LORA_PROTOCOL_INIT - error initializing Lora communication protocol
            LORA_DATA_SIZE - data size is too big
            LORA_NOT_JOINED - device is NOT joined to LoRaWAN Network Server
            LORA_SEND_ERROR - failed to send data
        */
        enum LoraErrors {LORA_OK, LORA_CHIP_INIT, LORA_PROTOCOL_INIT, LORA_DATA_SIZE, LORA_NOT_JOINED, LORA_SEND_ERROR};


        /*
            creates LoRaWan communication object
        */
        LoRaWanCommunication(DeviceClass_t device_class = CLASS_A, LoRaMacRegion_t lora_region = LORAMAC_REGION_EU868);


        /*
            initialization of LoRaWAN end device(node)
            @return error_code
        */
        LoraErrors init();


        /*
            set lora parameters
        */
        void setLoRaWanParameters(lmh_param_t params);


        /*
            set recive callback
        */
        void setRxCallback(void (*callback)(lmh_app_data_t *));


        /*
            send data using LoRaWAN network
        */
        LoraErrors send(uint8_t *data, uint8_t data_size);
};

#endif // LORAWAN_COMM_H