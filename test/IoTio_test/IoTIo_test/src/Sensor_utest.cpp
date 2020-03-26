/**
 * @addtogroup Sensor_utest
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
 * @file Sensor_utest.cpp
 * @brief (see Sensor_utest.h)
 * @details (see Sensor_utest.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* gTest */
#include "gtest/gtest.h"

/* SWUT */
#include "Sensor.h"

/* *****************************************************************************
 * TEST DECLARATIONS
 * ****************************************************************************/

/**
 * @brief Stub in order to be able to test methods of an abstract class
 *
 */
class StubSensor: public Sensor {
public:

	/* Derive the Base class Constructors */
	using Sensor::Sensor;

	/* Stub for the thread (not used) */
	void thread() {
	}

};

/**
 * @brief Check the constructor with name
 */
TEST(Sensor, NameConstructor) {
	/* Creation of the object */
	StubSensor sensor("MySensor");

	/* Check Name */
	ASSERT_EQ(sensor.getSensorName(), "MySensor");

	/* Check Default sounding period */
	ASSERT_EQ(sensor.getSoundingPeriod(), (unsigned int )0);
}

/**
 * @brief Check the constructor with name and sounding period
 */
TEST(Sensor, NameAndSoundingConstructor) {
	/* Sounding Period */
	unsigned int soundingPeriod = 2000;

	/* Creation of the object */
	StubSensor sensor("Sensor_1", soundingPeriod);

	/* Check Name */
	ASSERT_EQ(sensor.getSensorName(), "Sensor_1");

	/* Check Default sounding period */
	ASSERT_EQ(sensor.getSoundingPeriod(), soundingPeriod);
}

/**
 * @} (Sensor_utest)
 */
