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
 * @brief Abstract class for sensor implementation.
 * @details This class shall create a periodic thread
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

	/** @brief Sounding Period in milliseconds [ms] */
	unsigned int _soundingPeriod;

public:

	Sensor();

	/**
	 * @brief Constructor with sensor name
	 */
	Sensor(const std::string &sensorName);

	/**
	 * @brief Constructor with sensor name and sounding period
	 */
	Sensor(const std::string &sensorName, const unsigned int soundingPeriod);

	/**
	 * @brief Destructor
	 */
	virtual ~Sensor();

	/**
	 * @brief Get the sensor name assigned
	 *
	 * @return Reference to Sensor Name
	 */
	const std::string& getSensorName() const;

	/**
	 * @brief Set the name of the sensor
	 *
	 * @param[in] sensorName Name of the sensor to provide
	 *
	 * @return void
	 */
	void setSensorName(const std::string &sensorName);

	/**
	 * @brief Get the Sounding Period
	 * @return Number of milliseconds [ms] for the Sounding Period configured
	 */
	unsigned int getSoundingPeriod() const;

	/**
	 * @brief Set the Sounding Period
	 * @param[in] soundingPeriod Sounding Period in milliseconds [ms]
	 */
	void setSoundingPeriod(const unsigned int soundingPeriod);

	/**
	 * @brief Abstract class to be implemented in derived classes where the logic
	 * of every sounding period shall be implemented
	 */
	virtual void thread() = 0;

};

#endif /* SENSOR_H_ */

/**
 * @} (Sensor)
 */
