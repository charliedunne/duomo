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
 * @file LinearAnalogData.h
 * @brief 
 * @details
 *
 */

#ifndef LINEARANALOGDATA_H_
#define LINEARANALOGDATA_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

#include <Data.h>

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class LinearAnalogData: public Data {

private:

	/**
	 * @brief Slope of the linear equation in the form y = mx + a
	 */
	float _m;

	/**
	 * @brief Offset in the linear equation in the form y = mx + a
	 */
	float _a;

	/**
	 * @brief Virtual function that converts the RAW data (<b>_rawValue</b>)
	 * into calibrated value and place it in <b>_value</b>
	 *
	 * @attention Note that this function is automatically called by
	 * <b>setRawValue()</b> so it is not required to call it, just define custom
	 * implementation in derived classes.
	 */
	virtual void calibrate();

public:

	/**
	 * @brief Default constructor
	 */
	LinearAnalogData();

	/**
	 * @brief Constructor with name
	 *
	 * @param[in] dataName String with the name for the data, usefull for
	 * reporting and logging purposes
	 * @param[in] m Slope of the linear equation in the form y = mx + a
	 * @param[in] a Offset of the linear equation in the form y = mx + a
	 */
	LinearAnalogData(std::string dataName, float m, float a);

	/**
	 * @brief Destructor
	 */
	virtual ~LinearAnalogData();
};

#endif /* LINEARANALOGDATA_H_ */

/**
 * @} (LinearAnalogData)
 */
