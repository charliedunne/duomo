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
 * @file Sensor.cpp
 * @brief (see Sensor.h)
 * @details (see Sensor.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided interface */
#include "Sensor.h"

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

Sensor::Sensor(const std::string &sensorName) {

	/* Set the sensor name */
	_sensorName = sensorName;

	/* Set the default Sounding value */
	_soundingPeriod = 0;
}

Sensor::Sensor(const std::string &sensorName,
		const unsigned int soundingPeriod) {

	/* Set the sensor name */
	_sensorName = sensorName;

	/* Set the default Sounding value */
	_soundingPeriod = soundingPeriod;
}

Sensor::~Sensor() {

	/* Wait for the finalization of the thread */
//	_thread.join();
}

unsigned int Sensor::getSoundingPeriod() const {

	return _soundingPeriod;
}

void Sensor::setSoundingPeriod(unsigned int soundingPeriod) {
	_soundingPeriod = soundingPeriod;
}

const std::string& Sensor::getSensorName() const {
	return _sensorName;
}

void Sensor::setSensorName(const std::string &sensorName) {
	_sensorName = sensorName;
}

void Sensor::run() {
	_thread = std::thread(Sensor::operation, this);
}

void Sensor::join() {
	_thread.join();
}

/**
 * @} (Sensor)
 */
