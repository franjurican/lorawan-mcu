#ifndef DATA_GATHERING_H
#define DATA_GATHERING_H

#include <Arduino.h>
#include <FreeRTOS.h>
#include <timers.h>
#include "temp_and_humidity_sensor.h"
#include "lorawan_comm.h"

class DataGathering {

    public:
        /*
            pointers to sensors and comm objects
        */
        static TempAndHumididtySensor *RAK1901;
        static LoRaWanCommunication *lora_node;


        /*
            timers handler
        */
        static TimerHandle_t temp_and_humidity_timer;


        /*
            timer callback for temperature and humidity sensor
        */
        static void tempAndHumiditySensorCallback(TimerHandle_t xTimer);
};

#endif // DATA_GATHERING_H