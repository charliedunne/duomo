/**
 * @addtogroup Data
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
 * @file Data.cpp
 * @brief (see Data.h)
 * @details (see Data.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided Interface */
#include "Data.h"

/* System libraries */
#include <iostream>

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

Data::Data() :Data("") {

}

Data::Data(std::string dataName) : _dataName(dataName) {

	_rawValue = 0;
	_value = 0;
}

Data::~Data() {
	// TODO Auto-generated destructor stub
}


std::string Data::getDataName() {

	return _dataName;
}

std::string Data::mqttMessage() {

	/* String with the MQTT message */
	std::string mqttMessage;

	/* Build the message */
	mqttMessage.append("{\"");
	mqttMessage.append(_dataName);
	mqttMessage.append("\": ");
	mqttMessage.append(std::to_string(_value));
	mqttMessage.append("}");

	return mqttMessage;
}

void Data::logData() {

	std::cout << _dataName << ": " << _value << "%; " << _rawValue << " (RAW);" << std::endl;
}

void Data::setDataName(const std::string &dataName) {
	_dataName = dataName;
}

int Data::getRawValue() const {
	return _rawValue;
}

void Data::setRawValue(int rawValue) {
	_rawValue = rawValue;

	/* Compute calibrated value */
	calibrate();
}

float Data::getValue() const {
	return _value;
}

void Data::setValue(float value) {
	_value = value;
}

void Data::calibrate() {

	/* Just copy RAW data into calibrated data */
	_value = _rawValue;
}

/**
 * @brief Obtain the Id
 * @return ID
 */
int Data::getId() const {
	return id;
}

/**
 * @brief Set the ID
 * @param[in] id to set
 */
void Data::setId(int id) {
	this->id = id;
}

/**
 * @} (Data)
 */
