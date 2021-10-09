#include "data_gathering.h"
#include "helper_fun.h"

/*
	init static members
*/
TempAndHumididtySensor *DataGathering::RAK1901 = NULL;
LoRaWanCommunication *DataGathering::lora_node = NULL;
TimerHandle_t DataGathering::temp_and_humidity_timer = NULL;


void DataGathering::tempAndHumiditySensorCallback(TimerHandle_t xTimer)
{
	static int errors = 0;
	uint32_t t1 = micros();

	// update sensor data
	uint8_t error_code = DataGathering::RAK1901->updateSensorMeasurement();

	if(error_code == TempAndHumididtySensor::DATA_OK)
	{
		printSensorDataDebugMsg(*RAK1901);
	}
	else
	{
		printSensorErrorDebugMsg(error_code);
		return;
	}


	// create LoRaWAN msg
	String temp = DataGathering::RAK1901->getTemperatureAsString();
	String hum = DataGathering::RAK1901->getHumidityAsString();
	String output = "T: " +  temp + ", RH: " + hum;


	//send LoRaWAN msg
	LoRaWanCommunication::LoraErrors error_lora = DataGathering::lora_node->send((uint8_t *)output.c_str(), output.length());

    if(error_lora != LoRaWanCommunication::LORA_OK)
	{
		printLoraSendErrorMsg(error_lora);
		errors++;
	}

	Serial.printf("Pogreske: %d\n", errors);
	Serial.printf("Vrijeme izvrsavanja: %d [us]\n", micros() - t1);
}