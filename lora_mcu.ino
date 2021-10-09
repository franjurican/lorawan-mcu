#include <timers.h>
#include "temp_and_humidity_sensor.h"
#include "helper_fun.h"
#include "lorawan_comm.h"
#include "data_gathering.h"

#define TEMP_AND_HUM_TIMER_PERIOD_MS 5000

DataGathering collector;

void setup()
{
  	// start and wait for serial to connect, init leds
  	Serial.begin(115200);
	initLEDs();
  	while(!Serial){}
  	blueLED(HIGH);

  
	// init sensor and communication objects
	collector.RAK1901 = new TempAndHumididtySensor();
	collector.lora_node = new LoRaWanCommunication();

	if(collector.RAK1901 == NULL || collector.lora_node == NULL)
	{
		Serial.println(F("Pogreska prilikom kreiranja senzora i komunikacijskih objekata!"));
		while(1)
		{	
			// show error by blinking green LED
			greenLED(HIGH);
			delay(250);
			greenLED(LOW);
			delay(250);
		}
	}


	// start sensor
	uint32_t ID;
	if((ID = collector.RAK1901->startSensor()) == -1)
	{
		Serial.println(F("Pogreska prilikom spajanja na RAK1901!"));
		while(1)
		{	
			// show error by blinking green LED
			greenLED(HIGH);
			delay(500);
			greenLED(LOW);
			delay(500);
		}
	}
	else 
	{
		Serial.print(F("Uspjesno spojen na RAK1901, ID = "));
		Serial.println(ID, HEX);
	}


	// init LoRaWan comm module
	if(collector.lora_node->init() != LoRaWanCommunication::LORA_OK)
	{
		Serial.print(F("Pogreska kod inicijalizacije LoRaWan modula"));
		while(1)
		{	
			// show error by blinking green LED
			greenLED(HIGH);
			delay(1000);
			greenLED(LOW);
			delay(1000);
		}
	}
	else
	{
		Serial.println(F("Uspjesno inicijaliziran LoRaWAN modul"));
	}


	// create and start timers for data gathering 
	collector.temp_and_humidity_timer = xTimerCreate("temp_and_hum", pdMS_TO_TICKS(TEMP_AND_HUM_TIMER_PERIOD_MS), 
																		pdTRUE, NULL, collector.tempAndHumiditySensorCallback);

	if(collector.temp_and_humidity_timer == NULL || xTimerStart(collector.temp_and_humidity_timer, 0) != pdPASS)
	{
		Serial.print(F("Pogreska kod kreiranja i pokretanja timer-a"));
		while(1)
		{	
			// show error by blinking green LED
			greenLED(HIGH);
			delay(2000);
			greenLED(LOW);
			delay(2000);
		}
	}
	else
	{
		Serial.println(F("Timer uspjesno kreiran i pokrenut!"));
	}
}


void loop()
{	
	// all job is done in timers and tasks
}
