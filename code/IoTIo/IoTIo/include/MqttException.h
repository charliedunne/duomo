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
 * @file MqttException.h
 * @brief Exception class for the MQTT API
 * @details
 *
 */

#ifndef MQTTEXCEPTION_H_
#define MQTTEXCEPTION_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

/* System libraries */
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


/* *****************************************************************************
 *  MACROS
 * ****************************************************************************/

/** @brief Macro to be used for throwing an exception */
#define THROW_MQTT(arg) throw MqttException(arg, __FILE__, __LINE__)

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class MqttException: public std::runtime_error {

private:

	/** @brief Message to be printed out when error */
	std::string msg;

public:

	/** @brief Remove default constructor */
	MqttException() = delete;

	/**
	 * @brief Constructor. Note that
	 * @param mqttErrorCode Error code provided by MQTT PAHO API
	 */
	MqttException(const int mqttErrorCode, const char *file, int line);

	/** @brief default destructor */
	virtual ~MqttException();

	/**
	 * @brief Overload of the what function that shall print an error message
	 * along with the error code provided by MQTT API
	 * @return Error Message.
	 */
	const char* what() const throw ();
};

#endif /* MQTTEXCEPTION_H_ */

/**
 * @} (MqttException)
 */
