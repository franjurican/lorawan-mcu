#include "temp_and_humidity_sensor.h"

TempAndHumididtySensor::TempAndHumididtySensor(uint32_t baudrate) : baudrate(baudrate), sensor()
{
}


int32_t TempAndHumididtySensor::startSensor(TwoWire &busI2c)
{   
    // start I2C bus
    busI2c.begin();
    busI2c.setClock(baudrate);

    // start sensor (get sensor ID)
    if(sensor.begin(busI2c) != SHTC3_Status_Nominal)
    {   
        this->ID = -1;
        return -1;
    }

    // CRC ID
    if(!sensor.passIDcrc)
    {
        this->ID = -1;
        return -1;
    }
    else
    {
        this->ID = sensor.ID;
        return sensor.ID;
    }
}


uint8_t TempAndHumididtySensor::updateSensorMeasurement() 
{
    // send cmd on I2C
    sensor.update();

    // check read status code
    if(sensor.lastStatus != SHTC3_Status_Nominal)
        return DATA_ERROR_READING;

    // check if data is corrupted (CRC)
    if(!sensor.passTcrc && !sensor.passRHcrc)
        return DATA_ERROR_ALL;
    else if(!sensor.passTcrc)
        return DATA_ERROR_TEMP;
    else if(!sensor.passRHcrc)
        return DATA_ERROR_HUM;
    else
        return DATA_OK;
}


uint16_t TempAndHumididtySensor::getRawTemperature() 
{
    return sensor.T;
}


uint16_t TempAndHumididtySensor::getRawHumidity() 
{
    return sensor.RH;
}


float TempAndHumididtySensor::getTemperature()
{
    return sensor.toDegC();
}


float TempAndHumididtySensor::getHumidity()
{
    return sensor.toPercent();
}


String TempAndHumididtySensor::getTemperatureAsString()
{
    return String(this->getTemperature(), 2);
}


String TempAndHumididtySensor::getHumidityAsString()
{
    return String(this->getHumidity(), 2);
}