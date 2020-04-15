/**
 * @addtogroup MqttException
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
 * @file MqttException.cpp
 * @brief (see MqttException.h)
 * @details (see MqttException.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided Interface */
#include "MqttException.h"

/* System libs */
#include <sstream>

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

MqttException::MqttException(const int mqttErrorCode, const char *file,
		int line) :
		std::runtime_error("MQTT_RunTimeError") {

	std::ostringstream outputStream;

	outputStream << "[" << file << ":" << line << "] " << "MQTT Error Code = "
			<< mqttErrorCode;

	msg = outputStream.str();

}

MqttException::~MqttException() {
	/* Do nothing */
}

const char* MqttException::what() const throw () {

	return msg.c_str();
}

/**
 * @} (MqttException)
 */
