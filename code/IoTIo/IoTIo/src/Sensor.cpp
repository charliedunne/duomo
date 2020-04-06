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

/* System libraries */
#include <chrono>

#ifdef DEBUG
#include <iostream>
#endif /* DEBUG */


/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

Sensor::Sensor(const std::string &sensorName,
		const unsigned int soundingPeriod) {

	/* Set the sensor name */
	_sensorName = sensorName;

	/* Set the default Sounding value */
	_soundingPeriod = soundingPeriod;

	/* Maximum Number of runs, by default unlimited */
	_maxRuns = 0;

	/* Initialize runs counter */
	_runsCounter = _maxRuns;

	/* Initialize the number of thread counter */
	_execCntr = 0;
}

Sensor::~Sensor() {

	/* Wait for the finalization of the thread */
	if (_thread.joinable()) {
		_thread.join();
	}
}

/* *****************************************************************************
 * SETs and GETs
 * ****************************************************************************/

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

unsigned int Sensor::getMaxRuns() const {
	return _maxRuns;
}

void Sensor::setMaxRuns(const unsigned int maxRuns) {

	/* Set the Maximum runs configured */
	_maxRuns = maxRuns;
}

unsigned long long Sensor::getExecCntr() const {
	return _execCntr;
}

/* *****************************************************************************
 * THREAD RELATED METHODS
 * ****************************************************************************/

void Sensor::run() {

	/* Reset the runs Counter */
	_runsCounter = _maxRuns;

	/* Spawn the thread */
	this->_thread = std::thread([=] {this->threadBody();});
}

void Sensor::join() {
	_thread.join();
}

void Sensor::threadBody() {

	/* In the case of _maxRuns = 0, fake the _runsCounter */
	if (_maxRuns == 0)
	{
		_runsCounter = 1;
	}

	while (_runsCounter > 0) {

#ifdef DEBUG
		std::cout << "<START> operation()" << std::endl;
#endif /* DEBUG */

#ifdef DEBUG
	std::cout << "[" << _execCntr << "] " << _sensorName << std::endl;
#endif /* DEBUG */

		/* Run the user define operations */
		/**
		 * @TODO Add exception management
		 */
		operation();

#ifdef DEBUG
		std::cout << "<END> operation()" << std::endl;
#endif /* DEBUG */

		/* Decrease runs counter (if applicable) */
		if (_maxRuns > 0)
		{
			_runsCounter--;
		}

		/* Wait for the next cycle */
		std::this_thread::sleep_for(std::chrono::milliseconds(_soundingPeriod));

		/* Increment thread counter */
		_execCntr++;
	}
}


/**
 * @} (Sensor)
 */
