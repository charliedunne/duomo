/**
 * @addtogroup LinearAnalogData
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
 * @file LinearAnalogData.cpp
 * @brief (see LinearAnalogData.h)
 * @details (see LinearAnalogData.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided Interface */
#include "LinearAnalogData.h"

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

LinearAnalogData::LinearAnalogData() : LinearAnalogData("", 0 , 0) {
	// TODO Auto-generated constructor stub
}

LinearAnalogData::LinearAnalogData(std::string dataName, float m, float a) : Data(dataName) {

	/* Initialize coefficients */
	_m = m;
	_a = a;
}

LinearAnalogData::~LinearAnalogData() {
	// TODO Auto-generated destructor stub
}

void LinearAnalogData::calibrate() {

	/* Implementation of the linear equation in the form y = mx + a */
	_value = _m * _rawValue + _a;
}

/**
 * @} (LinearAnalogData)
 */
