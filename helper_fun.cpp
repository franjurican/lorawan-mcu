#include "helper_fun.h"

void initLEDs()
{
    pinMode(LED_BLUE, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	digitalWrite(LED_BLUE, LOW);
	digitalWrite(LED_GREEN, LOW);
}


void blueLED(uint8_t onOff)
{
    digitalWrite(LED_BLUE, onOff);
}


void greenLED(uint8_t onOff)
{
    digitalWrite(LED_GREEN, onOff);
}


void printSensorDataDebugMsg(TempAndHumididtySensor sensor) 
{	
    // broj mjerenja
    static int count = 1;

    // header and msg
    String header_msg = " Mjerenje " + String(count) + " ";
    String output = "Temperatura: " + sensor.getTemperatureAsString() + ", vlaga: " + sensor.getHumidityAsString();

    // len
	uint output_len = output.length();
    uint header_len = header_msg.length();

    // header space
    uint space = output_len - header_len;
    uint left_space = (space % 2) ? space/2 + 1 : space/2;
    uint right_space = space/2;

    // print header
    Serial.println();

    for(int i = 0; i < left_space; i++) {
        Serial.print(F("="));
    }

    Serial.print(header_msg);

    for(int i = 0; i < right_space; i++) {
        Serial.print(F("="));
    }

    Serial.println();

    // print msg
    Serial.println(output);

    for(int i = 0; i < output_len; i++) {
        Serial.print(F("="));
    }

    Serial.println();

    // increment count
    count++;
}


void printSensorErrorDebugMsg(uint8_t error_code)
{
    Serial.print(F("Pogreska kod osvjezavanja podataka: "));

    switch (error_code)
	{
		case TempAndHumididtySensor::DATA_ERROR_READING:
			Serial.println(F("DATA_ERROR_READING"));
			break;

		case TempAndHumididtySensor::DATA_ERROR_ALL:
			Serial.println(F("DATA_ERROR_ALL"));
			break;
			
		case TempAndHumididtySensor::DATA_ERROR_TEMP:
			Serial.println(F("DATA_ERROR_TEMP"));
			break;

		case TempAndHumididtySensor::DATA_ERROR_HUM:
			Serial.println(F("DATA_ERROR_HUM"));
			break;
	}
}

void printLoraSendErrorMsg(LoRaWanCommunication::LoraErrors error_code)
{
    Serial.print(F("Pokreska kod slanja LoRa paketa: "));
		switch (error_code)
		{
			case LoRaWanCommunication::LORA_DATA_SIZE:
				Serial.println(F("LORA_DATA_SIZE"));
				break;

			case LoRaWanCommunication::LORA_NOT_JOINED:
				Serial.println(F("LORA_NOT_JOINED"));
				break;

			case LoRaWanCommunication::LORA_SEND_ERROR:
				Serial.println(F("LORA_SEND_ERROR"));
				break;
		}
}
