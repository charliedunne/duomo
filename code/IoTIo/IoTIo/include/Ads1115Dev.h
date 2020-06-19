/**
 * @addtogroup Ads1115
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
 * @file Ads1115.h
 * @brief 
 * @details
 *
 */

#ifndef ADS1115DEV_H_
#define ADS1115DEV_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

/* System Libraries */
#include <vector>

/* Parent Classes */
#include <Sensor.h>

/* Data interface */
#include "Data.h"

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class Ads1115Dev: public Sensor {

private:

	/**
	 * @brief Array of the i2c Addresses of the ADS1115 bard.
	 *
	 * @attention Note that the Addresses are hard-coded and constant for all
	 * the chips
	 */
	const uint8_t _i2cAddrs = 0x48;

	/**
	 * @brief Array of the four Analog signals connected to the board
	 */
	std::vector<std::unique_ptr<Data>> _data;

	/**
	 * @brief list of TOKENs for each device connected to the Ads1115
	 */
	std::vector<std::string> _tokens;

	/**
	 * @brief list of TOPICs for each device connected to the Ads1115
	 */
	std::vector<std::string> _topics;

public:

	/**
	 * @brief Private Constructor. It is a singleton class
	 */
	Ads1115Dev();

	/**
	 * @brief Private Constructor. It is a singleton class
	 */
	Ads1115Dev(std::string name, int soundingPeriod, int i2cAddress);

	virtual ~Ads1115Dev();

	/**
	 * @brief Definition of the abstract class method operation() that contains
	 * the logic to retrieve information from sensor.
	 */
	virtual void operation();

	/**
	 * @brief This function is used to register (add) a new device connected
	 * to the Ads1115.
	 *
	 * @param[in] name String with the sensor name (for logging/reporting
	 * purposes)
	 * @param[in] addrOffset Identifier of the pin where the device is
	 * connected to [1..4]
	 * @param[in] m Slope of the linear equation in the form y = mx + a
	 * @param[in] a Offset of the linear equation in the form y = mx + a
	 */
	void addDevice(std::string name, uint8_t addrOffset, int m, int a);


	/*
	 * Get and Set Functions
	 */

private:

	/**
	 * @brief Private function that shall extract the raw values
	 * from the sensor and shall place them in the private vector @b _outputs
	 *
	 * @attention Note that this function shall perform a registration of all
	 * the devices connected to the container Ads1115
	 *
	 * @return Return code
	 * @retval 0 (OK) if the values are captured correctly
	 * @retval -1 (ERROR) if the values were not obtained.
	 */
	int registerData(void);

	/**
	 * @brief WiringPI initialization so the Ads115 device can be operated
	 *
	 */
	void wiringPiInit(void);

	/**
	 * @brief WiringPI extraction of RAW value for a specific pin
	 *
	 * @param[in] pin Pin number to obtain the data from
	 * @return Raw value (integer) of the data registered
	 */
	int wiringPiRead(uint8_t pin);


protected:

	/*
	 * Function associated to the data type of each port (To be implemented
	 * in derived classes)
	 */

	//virtual


};

#endif /* ADS1115DEV_H_ */

//
// Make a singleton design where only one instance of the object is done
//
//
//#include <iostream>
//#include <errno.h>
//#include <wiringPi.h>
//#include <wiringPiI2C.h>
//#include <ads1115.h>
//#include <unistd.h>
//
//int main()
//{
//  int fd, result, value;
//
//  result = ads1115Setup(80, 0x48);
//  std::cout << "Output of [1] ads1115Setup(): " << result << std::endl;
//
//
//  //  fd = wiringPiI2CSetup(0x48);
//
//  //  if (fd == -1)
//  //    {
//  //      std::cout << "Error in wiringPiI2CSetup()" << std::endl;
//  //      std::exit(-1);
//  //    }
//
//
//  while (1)
//    {
//      value = analogRead(80);
//      std::cout << "Value[A1]: " << value << std::endl;
//      value = analogRead(80 + 1);
//      std::cout << "Value[A2]: " << value << std::endl;
//      value = analogRead(80 + 2);
//      std::cout << "Value[A3]: " << value << std::endl;
//      value = analogRead(80 + 3);
//      std::cout << "Value[A4]: " << value << std::endl;
//
//      usleep(1000000);
//    }
//
//}


/**
 * @} (Ads1115)
 */
