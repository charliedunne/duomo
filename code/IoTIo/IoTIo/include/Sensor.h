/**
 * @addtogroup Sensor
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
 * @file Sensor.h
 * @brief 
 * @details
 *
 */

#ifndef SENSOR_H_
#define SENSOR_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

#include <string>

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class Sensor {
private:

	/** @brief Sensor Name for displaying purposes */
	std::string _sensorName;


public:

	/**
	 * @brief Constructor with no arguments
	 *
	 */
	Sensor();

	/**
	 * @brief Constructor with sensor name
	 */
	Sensor(std::string sensorName);

	/**
	 * @brief Destructor
	 */
	virtual ~Sensor();

	/**
	 * @brief Set the name of the sensor
	 *
	 * @param[in] sensorName Name of the sensor to provide
	 *
	 * @return void
	 */
	void setName(std::string sensorName);

	/**
	 * @brief Get the sensor name assigned
	 *
	 * @return Reference to Sensor Name
	 */
	std::string & getName(void);


};

#endif /* SENSOR_H_ */

/**
 * @} (Sensor)
 */
