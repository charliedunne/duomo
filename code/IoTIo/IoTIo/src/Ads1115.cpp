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
 * @file Ads1115.cpp
 * @brief (see Ads1115.h)
 * @details (see Ads1115.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided Interface */
#include "Ads1115.h"

/* WiringPi */
#include <wiringPi.h>
#include <ads1115.h>

/* Data types */

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/


Ads1115::~Ads1115() {
	// TODO Auto-generated destructor stub
}

void Ads1115::operation() {


}

Ads1115::Ads1115() : Sensor("Ads1115", 1000) {


}

int Ads1115::registerData(void) {

	/* Return code */
	int iRetCode = 0;



	return iRetCode;
}


/**
 * @} (Ads1115)
 */
