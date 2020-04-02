/**
 * @addtogroup Dht11
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
 * @file Dht11.h
 * @brief 
 * @details
 *
 */

#ifndef DHT11_H_
#define DHT11_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

#include <Sensor.h>

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class Dht11: public Sensor {

private:

	const unsigned int _gpioPin;

	float _temperature;
	float _humidity;

	/* Derive Constructors */

	using Sensor::Sensor;

public:

	/*
	 * Constructors and Destructors
	 */

	/**
	 * @brief No copy constructor for this class. There is no sense that
	 * there are two instances of the same object since it is associated
	 * to a specific gpio pin.
	 */
	Dht11(const Dht11 &) = delete;

	/**
	 * @brief Constructor
	 *
	 * @param[in] sensorName User name for the sensor (string)
	 * @param[in] soundingPeriod Period to what the sensor shall be evaluated
	 */
	Dht11(const std::string &sensorName, const unsigned int soundingPeriod, const unsigned int gpioPin);


	/**
	 * @brief Destructor
	 */
	virtual ~Dht11();

	/**
	 * @brief Definition of the abstract class method operation() that contains
	 * the logic to retrieve information from sensor.
	 */
	virtual void operation();

	/*
	 * Get and Set Functions
	 */
	/**
	 * @brief Get Humidity previously registered
	 * @attention Note that this function shall not trigger the read of the
	 * sensor itself, it only retrieve the data previously stored in the class
	 * member. In order to retrieve data from the sensor the function
	 * @b registerData() must be called.
	 * @return Humidity
	 */
	float getHumidity() const;

	/**
	 * @brief Get the Temperature value previously registered
	 * @attention Note that this function shall not trigger the read of the
	 * sensor itself, it only retrieve the data previously stored in the class
	 * member. In order to retrieve data from the sensor the function
	 * @b registerData() must be called.
	 * @return Temperature
	 */
	float getTemperature() const;


	/*
	 * Operational Functions
	 */

private:

	/**
	 * @brief Private function that shall extract the temperature and humidity values
	 * from the sensor and shall place them in the private members @b _temperature
	 * and @b _humidity respectively
	 *
	 * @return Return code
	 * @retval 0 (OK) if the values are captured correctly
	 * @retval -1 (ERROR) if the values were not obtained.
	 */
	int registerData(void);
};

#endif /* DHT11_H_ */

/**
 * @} (Dht11)
 */
