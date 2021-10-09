#ifndef TEMP_AND_HUMIDITY_SENSOR_H
#define TEMP_AND_HUMIDITY_SENSOR_H
#include <Arduino.h>
#include <SparkFun_SHTC3.h>
#include <Wire.h>

class TempAndHumididtySensor
{
    private:
        int32_t ID = -1;
        uint32_t baudrate;
        SHTC3 sensor;

    public:
        /*
            Enumeration describing possible data reading errors.
            DATA_OK - everything is OK
            DATA_ERROR_TEMP - humidity data is OK, but CRC failed for temperature data (temperature data is corrupted)
            DATA_ERROR_HUM - temperature data is OK, but CRC failed for humidity data (humidity data is corrupted)
            DATA_ERROR_ALL - CRC failed for humidity and temperature data (all data is corrupted)
            DATA_ERROR_READING - failed to read data
        */
        enum DataReadingErrors {DATA_OK, DATA_ERROR_TEMP, DATA_ERROR_HUM, DATA_ERROR_ALL, DATA_ERROR_READING};

        /*
            Create sensor object.
            @param baudrate - I2C bus speed
        */
        TempAndHumididtySensor(uint32_t baudrate = 400000);


        /*
            Start sensor.
            @param I2C bus (two wire object)
            @return sensor ID on success, -1 on error
        */
        int32_t startSensor(TwoWire &busI2C = Wire);


        /*
            Get temperature and humidity from sensor.
            @return DATA_OK(0) on success, positive number on error (check DataReadingErrors enum)
        */
        uint8_t updateSensorMeasurement();


        /*
            Get temperature as bytes.
            @return temperature
        */
        uint16_t getRawTemperature();


        /*
            Get humidity as bytes.
            @return humidity
        */
        uint16_t getRawHumidity();


        /*
            Get temperature.
            @return temperature
        */
        float getTemperature();


        /*
            Get humidity.
            @return humidity
        */
        float getHumidity();


        /*
            Get temperature as string.
            @return temperature
        */
        String getTemperatureAsString();


        /*
            Get humidity as string.
            @return humidity
        */
        String getHumidityAsString();
};

#endif // TEMP_AND_HUMIDITY_SENSOR_H