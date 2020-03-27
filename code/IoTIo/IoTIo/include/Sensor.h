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

/* System libraries */
#include <string>
#include <thread>

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class Sensor {

private:

	/** @brief Sensor Name for displaying purposes */
	std::string _sensorName;

	/** @brief Sounding Period in milliseconds [ms] */
	unsigned int _soundingPeriod;

	/** @brief Number of executions of the main thread, 0 means unlimited */
	unsigned int _maxRuns;

	/** @brief Runs counter */
	unsigned int _runsCounter;

	/** @brief Thread object */
	std::thread _thread;

	/**
	 * @brief Thread body to be called in every step.
	 * @note Note that this function shall call internally to the pure virtual
	 * function @b operation and then shall perform a sleep of the @ _soundingPeriod
	 */
	void threadBody();

protected:

	/*
	 * Note that the pure virtual function must be declared prior to the destructor
	 * (I don't know why)
	 */

	/**
	 * @brief Abstract class to be implemented in derived classes where the logic
	 * of every sounding period shall be implemented
	 */
	virtual void operation() = 0;

public:

	/* Constructors */

	/** @brief Delete default constructor */
	Sensor() = delete;

	/**
	 * @brief No copy constructor for this class
	 */
	Sensor(const Sensor&) = delete;

	/**
	 * @brief No assignment operation for this class
	 */
	Sensor& operator=(const Sensor&) = delete;

	/**
	 * @brief Constructor with sensor name and sounding period
	 */
	Sensor(const std::string &sensorName, const unsigned int soundingPeriod);

	/**
	 * @brief Constructor with only sensor name
	 */
	Sensor(const std::string &sensorName) : Sensor(sensorName, 0) {};

	/* Destructors */

	/**
	 * @brief Destructor
	 */
	virtual ~Sensor();

	/* Sets and Gets */

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
	 * @brief Obtain the Maximum number of Runs of configured
	 * @return Maximum runs configured, 0 means infinite
	 */
	unsigned int getMaxRuns() const;

	/**
	 * @brief Set the maximum number of runs allowed
	 * @param[in] maxRuns Number of Maximum runs, 0 means infinite.
	 */
	void setMaxRuns(const unsigned int maxRuns);

	/* Threading operations */

	/**
	 * @brief Start the thread operation
	 * @note that the thread shall be executed as many times as it is defined
	 * by the private member @b _maxRuns, after that the thread ends its own
	 * execution. You can restart the thread again by calling this function
	 * again.
	 */
	void run();

	/**
	 * @brief join operation
	 */
	void join();

};

#endif /* SENSOR_H_ */

/**
 * @} (Sensor)
 */
