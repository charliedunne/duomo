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

Sensor::Sensor() {

}

Sensor::Sensor(std::string sensorName) {

	/* Set the sensor name */
	_sensorName = sensorName;
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

void Sensor::setName(std::string sensorName) {
	_sensorName = sensorName;
}

std::string& Sensor::getName(void) {
	return _sensorName;
}

/**
 * @} (Sensor)
 */
