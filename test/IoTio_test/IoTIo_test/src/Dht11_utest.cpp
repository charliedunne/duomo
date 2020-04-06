/**
 * @addtogroup Dht11_utest
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
 * @file Dht11_utest.cpp
 * @brief 
 * @details
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* gTest */
#include "gtest/gtest.h"

/* SWUT */
#include "Dht11.h"

/* Stubs */
#include "wiringPi.h"

/* *****************************************************************************
 * STUBS
 * ****************************************************************************/

int wiringPiSetup(void) {
	return 0;
}

void pinMode(int pin, int mode) {
}

void digitalWrite(int pin, int value) {
}

void delay(unsigned int howLong) {

}

int digitalRead(int pin) {

	return rand() % 2;
}

void         delayMicroseconds (unsigned int howLong) {}



/* *****************************************************************************
 * TESTS DEFINITION
 * ****************************************************************************/

TEST(Dht11, Constructor) {
	/* Creation of the object */
	Dht11 sensor { "DHT11", 1000, 7 };

	/* Check Default values after initialization */
	ASSERT_EQ(sensor.getSensorName(), "DHT11");
	ASSERT_EQ(sensor.getSoundingPeriod(), (unsigned int )1000);
	ASSERT_EQ(sensor.getHumidity(), 0.0);
	ASSERT_EQ(sensor.getTemperature(), 0.0);

}

TEST(Dht11, Thread) {

	/* Object creation */
	Dht11 sensor("DHT11", 0, 7);

	/* Set the number of runs to 1 */
	//sensor.setMaxRuns(1);

	/* Run the thread */
	sensor.run();

	/* Join waiting for the finalization of the thread */
	sensor.join();

	std::cout << "Humidity = " << sensor.getHumidity() << " %; Temperature = " << sensor.getTemperature() << " ºC" << std::endl;

	ASSERT_EQ(sensor.getHumidity(), 0.0);
	ASSERT_EQ(sensor.getTemperature(), 0.0);
}

/**
 * @} (Dht11_utest)
 */
