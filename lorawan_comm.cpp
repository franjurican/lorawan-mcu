#include "lorawan_comm.h"


/*
    class methods defintion
*/
LoRaWanCommunication::LoRaWanCommunication(DeviceClass_t device_class, LoRaMacRegion_t lora_region): device_class(device_class), lora_region(lora_region)
{
    // initial params
    this->lora_params = {LORAWAN_ADR_ON, LORAWAN_START_DR, LORAWAN_PUBLIC_NETWORK, JOIN_REQUEST_TRIALS, LORAWAN_START_POWER, LORAWAN_DUTYCYCLE_OFF};

    // set default callbacks
    this->lora_callbacks.BoardGetBatteryLevel = BoardGetBatteryLevel; // placeholder
    this->lora_callbacks.BoardGetRandomSeed = BoardGetRandomSeed; // placeholder
    this->lora_callbacks.BoardGetUniqueId = BoardGetUniqueId; // placeholder
    this->lora_callbacks.lmh_RxData = lorawanRx;
    this->lora_callbacks.lmh_has_joined = lorawanHasJoined;
    this->lora_callbacks.lmh_ConfirmClass = lorawanConfirmClass;
    this->lora_callbacks.lmh_has_joined_failed = lorawanJoinFailed;
}


LoRaWanCommunication::LoraErrors LoRaWanCommunication::init()
{
    // initialize LoRa chip.
    if(lora_rak4630_init())
    {
        return LORA_CHIP_INIT;
    }

    // set EUIs and security key
    lmh_setDevEui(device_EUI);
    lmh_setAppEui(join_EUI);
    lmh_setAppKey(app_key);

    // initialize LoRaWan
    lmh_error_status err_code = lmh_init(&lora_callbacks, lora_params, ENABLE_OTAA, device_class, lora_region);
    if(err_code != 0)
    {
        return LORA_PROTOCOL_INIT;
    }

    // start join procedure
    lmh_join();
    return LORA_OK;
}


void LoRaWanCommunication::setLoRaWanParameters(lmh_param_t params)
{
    this->lora_params = params;
}


void LoRaWanCommunication::setRxCallback(void (*callback)(lmh_app_data_t *))
{
    this->lora_callbacks.lmh_RxData = callback;
}


LoRaWanCommunication::LoraErrors LoRaWanCommunication::send(uint8_t *data, uint8_t data_size)
{
    if(data_size > LORAWAN_APP_DATA_BUFF_SIZE)
    {
        return LORA_DATA_SIZE;
    } 
    else if(lmh_join_status_get() != LMH_SET)
    {
        return LORA_NOT_JOINED;
    }

    // lora frame
    lmh_app_data_t lora_data = {0};
    lora_data.port = LORAWAN_APP_PORT;
    lora_data.buffer = data;
    lora_data.buffsize = data_size;

    // send data
    lmh_error_status error = lmh_send(&lora_data, LMH_CONFIRMED_MSG);
    if (error != LMH_SUCCESS)
        return LORA_SEND_ERROR;
    
    return LORA_OK;
}


///////////////
// callbacks //
///////////////
void LoRaWanCommunication::lorawanHasJoined()
{
    Serial.println("Device joined network as CLASS A device!");
}


void LoRaWanCommunication::lorawanJoinFailed()
{
    Serial.println("OTAA join failed!");
    Serial.println("===========================");
    Serial.println("Starting join request again");
    Serial.println("===========================");
    lmh_join();
}


void LoRaWanCommunication::lorawanRx(lmh_app_data_t *app_data)
{
    Serial.printf("LoRa packet received on port %d, size:%d, rssi:%d, snr:%d, data:%s\n", 
            app_data->port, app_data->buffsize, app_data->rssi, app_data->snr, app_data->buffer);
}


void LoRaWanCommunication::lorawanConfirmClass(DeviceClass_t Class)
{
    Serial.printf("Switch to class %c done\n", "ABC"[Class]);

    // informs the server that switch has occurred ASAP
    lmh_app_data_t lora_data = {0};
    lora_data.port = LORAWAN_APP_PORT;
    lmh_send(&lora_data, LMH_CONFIRMED_MSG);
}
