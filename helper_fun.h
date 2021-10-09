#ifndef HELPER_FUN_H
#define HELPER_FUN_H

#include "temp_and_humidity_sensor.h"
#include "lorawan_comm.h"

/*
    init builtin leds
*/
void initLEDs();


/*
    control blue LED
*/
void blueLED(uint8_t onOff);


/*
    control green LED
*/
void greenLED(uint8_t onOff);


/*
    print temp and humidity
*/
void printSensorDataDebugMsg(TempAndHumididtySensor sensor);


/*
    print error msg
*/
void printSensorErrorDebugMsg(uint8_t error_code);


/*
    print LoRa send error msg
*/
void printLoraSendErrorMsg(LoRaWanCommunication::LoraErrors error_code);

#endif // HELPER_FUN_H