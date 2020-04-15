/**
 * @addtogroup Dht11
 *
 * @{
 *
 * @copyright Carlos Valle Torres, 2020
 * 
 * This source file is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @file Dht11.cpp
 * @brief (see Dht11.h)
 * @details (see Dht11.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided Interface */
#include "Dht11.h"

/* System libraries */
#include <iostream>

/* wiringPi library to manage GPIO */
extern "C" {
#include <wiringPi.h>
}

/* *****************************************************************************
 * PRIVATE CONSTANTS
 * ****************************************************************************/

/**
 * @brief Maximum number of readings attempts over the input of the DHT11/22
 * sensor until the aiData is supposed to be obtained.
 */
#define MAX_TIMINGS 85

/**
 * @brief Default value for the number of times the code shall attempt the
 * read of the sensor data before ignoring this reading step.
 */
#define DEFAULT_TIMEOUT_COUNTER 5

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

Dht11::Dht11(const std::string &sensorName, const unsigned int soundingPeriod,
		const unsigned int gpioPin) :
		Sensor::Sensor(sensorName, soundingPeriod), _gpioPin(gpioPin), _timeoutCounters(
		DEFAULT_TIMEOUT_COUNTER) {

	/* Set internal members */
	_temperature = 0.0;
	_humidity = 0.0;

	/* Initialize WiringPi Library */
	wiringPiSetup();

	/* Set-up the MQTT connection */
	configureMqtt(_accessToken);

}

Dht11::~Dht11() {
	/* Do nothing */
}

void Dht11::operation() {

	/* Return code from regiterData */
	int iRetCode = 0;

	/* String with the MQTT message */
	std::string mqttMessage;

	/* Get the data from sensor, Lock until obtain a valid result */
	do {
		iRetCode = registerData();
		_timeoutCounters--;
	} while ((iRetCode != 0) && (_timeoutCounters > 0));

#ifdef DEBUG
	std::cout << "Temp = " << _temperature << " C; Humidity = " << _humidity
			<< " %;" << std::endl;
#endif /* DEBUG */

	/*
	 * After obtaining the data, send it via MQTT to ThingsBoard
	 */

	/* Build the message */
	mqttMessage.append("{\"temperature\": ");
	mqttMessage.append(std::to_string(_temperature));
	mqttMessage.append(", \"humidity\": ");
	mqttMessage.append(std::to_string(_humidity));
	mqttMessage.append("}");

#ifdef DEBUG
	std::cout << "MQTT_Message: " << mqttMessage << std::endl;
#endif /* DEBUG */

	sendMqttMessage(_topic, mqttMessage);
}

float Dht11::getHumidity() const {
	return _humidity;
}

float Dht11::getTemperature() const {
	return _temperature;
}

int Dht11::registerData(void) {

	/* Return code */
	int iRetCode = 0;

	/* Temporal containers for the raw aiData from sensor */
	int aiData[5] = { 0, 0, 0, 0, 0 };

	/* ui8Counter of readings of the DHT11/22 sensor */
	uint8_t ui8Counter = 0;

	/* Temporal container for the "last state" of the output signal */
	uint8_t ui8LastState = HIGH;

	/* General purpose indexes */
	uint8_t ui8TimingCounter = 0;
	uint8_t ui8BitCounter = 0;

	/*
	 * Pull pin down for 18 milliseconds
	 */

	/* Configure GPIO pin for output */
	pinMode(_gpioPin, OUTPUT);

	/* Write a LOW in the gpio PIN */
	digitalWrite(_gpioPin, LOW);

	/* Wait for 18 milliseconds */
	delay(18);

	/* Change pin mode for input */
	pinMode(_gpioPin, INPUT);

	/*
	 * Detect change and read aiData
	 */

	for (ui8TimingCounter = 0; ui8TimingCounter < MAX_TIMINGS;
			ui8TimingCounter++) {

		/* Reset the counter in every timing cycle */
		ui8Counter = 0;

		/* Wait for the transition */
		while (digitalRead(_gpioPin) == ui8LastState) {

			ui8Counter++;

			delayMicroseconds(1);

			/*
			 * Finish the iteration if there are more than 255 iterations
			 * without transition detection
			 */
			if (ui8Counter == 255) {
				break;
			}
		}

		/* Read the bit after the trasition @TODO WHY? */
		ui8LastState = digitalRead(_gpioPin);

		/* Go to the next timing cycle if there was no transition */
		if (ui8Counter == 255) {
			break;
		}

		/* Save the aiData, ignoring first 3 transitions */
		if ((ui8TimingCounter >= 4) && (ui8TimingCounter % 2 == 0)) {
			/* shove each bit into the storage bytes */

			aiData[ui8BitCounter / 8] <<= 1;

			if (ui8Counter > 50)
				aiData[ui8BitCounter / 8] |= 1;

			ui8BitCounter++;
		}
	}

	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 */
	if ((ui8BitCounter >= 40)
			&& (aiData[4]
					== ((aiData[0] + aiData[1] + aiData[2] + aiData[3]) & 0xFF))) {

#ifdef DEBUG
		std::cout << "Data = [" << aiData[0] << ", " << aiData[1] << ", "
				<< aiData[2] << ", " << aiData[3] << ", " << aiData[4] << "];"
				<< std::endl;
#endif /* DEBUG */

		/* Humidity */
		_humidity = (float) ((aiData[0] << 8) + aiData[1]) / 10;
		if (_humidity > 100) {
			_humidity = aiData[0];	// for DHT11
		}

		/* Temperature */
		_temperature = (float) (((aiData[2] & 0x7F) << 8) + aiData[3]) / 10;
		if (_temperature > 125) {
			_temperature = aiData[2];	// for DHT11
		}
		if (aiData[2] & 0x80) {
			_temperature = -_temperature;
		}
	} else {

		iRetCode = -1;
	}

	return iRetCode;

}

/**
 * @} (Dht11)
 */
