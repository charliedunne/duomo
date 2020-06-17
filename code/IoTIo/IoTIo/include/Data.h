/**
 * @addtogroup Data
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
 * @file Data.h
 * @brief 
 * @details
 *
 */

#ifndef DATA_H_
#define DATA_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

#include <string>

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class Data {

private:
	/**
	 * @brief String with the user defined data name.
	 */
	std::string _dataName;

	/**
	 * @brief Raw data
	 */
	int _rawValue;

	/**
	 * @brief Calibrated data
	 */
	float _value;

public:

	/**
	 * @brief No default constructor
	 */
	Data();

	/**
	 * @brief Constructor given the name of the data.
	 * @note Data name is just a user defined name for the data instance,
	 * the type of data and the content is defined in derived classes.
	 */
	Data(std::string dataName);

	/**
	 * @brief destructor
	 */
	virtual ~Data();

public:

	/**
	 * @brief Return an string with the data Name
	 *
	 * @return String with the data name
	 */
	std::string  getDataName();

	/**
	 * @brief Create MQTT Message. This function shall build the mqtt message
	 * to be delivered.
	 *
	 * @attention Note that this function contains the default behaviour for
	 * this function, since it is virtual the behavior can be changed in
	 * derived classes.
	 *
	 * @return An string with the mqtt message to be delivered.
	 */
	virtual std::string mqttMessage();

	/**
	 * @brief Logging output data. This function prints out the data name
	 * and the value of the data into stdout.
	 */
	void logData();

	/**
	 * @brief Set data name
	 * @param[in] dataName Name of the data
	 */
	void setDataName(const std::string &dataName);

	/**
	 * @brief Get RAW value
	 * @return RAW value
	 */
	int getRawValue() const;

	/**
	 * @brief Set RAW value
	 * @attention When this function is executed, it is internally executed the
	 * <b>calibrate()</b> function that converts RAW data into calibrated data
	 * and place it in <b>_value</b>. Note that <b>calibrate()</b> is a virtual
	 * function which default implementation does NOT do anything.
	 * @param[in] rawValue RAW value
	 */
	void setRawValue(int rawValue);

	/**
	 * @brief Get the calibrated value of the data
	 * @return calibrated value
	 */
	float getValue() const;

	/**
	 * @brief Set the calibrated value of the data
	 * @param[in] value Calibrated value
	 */
	void setValue(float value);

private:

	/**
	 * @brief Virtual function that converts the RAW data (<b>_rawValue</b>)
	 * into calibrated value and place it in <b>_value</b>
	 *
	 * @attention Note that this function is automatically called by
	 * <b>setRawValue()</b> so it is not required to call it, just define custom
	 * implementation in derived classes.
	 */
	virtual void calibrate();
};

#endif /* DATA_H_ */

/**
 * @} (Data)
 */
