/**
 * @addtogroup Ads1115
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
 * @file Ads1115.cpp
 * @brief (see Ads1115.h)
 * @details (see Ads1115.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided Interface */
#include <Ads1115Dev.h>

/* WiringPi */
extern "C" {
#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "ads1115.h"
}


/* Data types */
#include "LinearAnalogData.h"

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/


Ads1115Dev::~Ads1115Dev() {

	/* Free the memory associated with each data type */
	for (std::vector<std::unique_ptr<Data>>::iterator it = _data.begin(); it != _data.end(); ++it)
	{
		Data memory = *it->release();

		delete &memory;
	}
}

void Ads1115Dev::operation() {

	std::string mqttMessage;

	/*
	 * Register the data from different sensors
	 */
	registerData();

	/*
	 * Generate the MQTT message for every device connected to the Ads1115 and deliver it
	 */
	for (std::vector<std::unique_ptr<Data>>::iterator it = _data.begin(); it != _data.end(); ++it)
	{
		/* Generate MQTT message */
		mqttMessage = it->get()->mqttMessage();

		/* Deliver MQTT message to the appropriate topic */
		sendMqttMessage(_topic, mqttMessage);
	}

}

Ads1115Dev::Ads1115Dev() : Sensor("Ads1115", 1000) {

	/* Initialize WiringPi library to access Ads1115 */
	wiringPiInit();
}

void Ads1115Dev::addDevice(std::string name, uint8_t addrOffset, int m, int a) {

	/* Create Data object */
	_data.emplace_back(std::move(new LinearAnalogData(name, m, a)));

	/* Set the ID of the device just added */
	_data.end()->get()->setId(addrOffset);

}

int Ads1115Dev::registerData(void) {

	/* Return code */
	int iRetCode = 0;

	for (std::vector<std::unique_ptr<Data>>::iterator it = _data.begin(); it != _data.end(); ++it)
	{
		/* Recover data from sensor and save it as raw value */
		it->get()->setRawValue(wiringPiRead(it->get()->getId()));
	}

	return iRetCode;
}

void Ads1115Dev::wiringPiInit(void) {

	/** @TODO Exception if the the initialization fails */
	ads1115Setup(_i2cAddrs * 4, _i2cAddrs);
}

int Ads1115Dev::wiringPiRead(uint8_t pin) {

	return analogRead((_i2cAddrs * 4) + pin);
}


/**
 * @} (Ads1115)
 */
