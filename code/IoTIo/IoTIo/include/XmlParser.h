/**
 * @addtogroup XmlParser
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
 * @file XmlParser.h
 * @brief 
 * @details
 *
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

/* XML Library */
#include "rapidxml.hpp"

/* System libraries */
#include <iostream>
#include <vector>

/* *****************************************************************************
 *  TYPES DECLARATION
 * ****************************************************************************/

///**
// * @brief Sensor common data structure
// */
//struct SensorCommon
//{
//	/** @brief Class of the sensor (Dht11, ds182, etc...) there must be
//	 * a specific C++ class created for it in the IoTIo library
//	 */
//	std::string type;
//
//	/** @brief Name of the sensor */
//	std::string name;
//
//	/** @brief Maximum runs the sensor will work autonomously */
//	unsigned int maxRuns;
//
//	/** @brief Sounding period in milliseconds [ms] */
//	unsigned int soundingPeriod;
//
//	/** @brief Offset time for the start in milliseconds [ms] */
//	unsigned int offsetTime;
//};
//
///**
// * @brief Dht11 data structure
// */
//struct Dht11
//{
//	/** @brief Common sensor data */
//	struct SensorCommon common;
//
//	/** @brief GPIO Pin to what the sensor is connected to */
//	unsigned int gpioPin;
//
//	/** @brief Access token to upload data to Thingsboard */
//	std::string accesToken;
//
//	/** @brief Thingsboard topic */
//	std::string topic;
//};
//
///**
// * @brief other data
// */
//struct Ds128
//{
//	int i;
//};
//
///**
// * @brief Union for all the sensors data
// */
//union SensorData
//{
//	/** @brief Data for Dht11 */
//	struct Dht11 dht11asad;
//
//	/** @brief Other sensor types */
//	struct Ds128 i;
//};

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class XmlParser {

private:

	/** @brief XML Handler */
	rapidxml::xml_document<> _xml;

	/** @brief XML Content into a string */
	std::string _xmlContent;

	/** @brief Pointer to the root of the tag <app_config> */
	rapidxml::xml_node<> * _rAppConf = NULL;

	/** @brief Pointer to the root of the tag <env_config> */
	rapidxml::xml_node<> * _rEnvConf = NULL;

	/** @brief Vector of Dht11 sensors */
	std::vector<rapidxml::xml_node<> *> _xmlSensorsData;


public:

	/**
	 * @brief Default constructor in case you have to declare the object
	 * before having the @b xmlFile
	 */
	XmlParser() {};

	/**
	 * @brief Constructor with the xml file
	 * @param[in] xmlFile Path/file of the xml configuration
	 */
	XmlParser(const std::string xmlFile);

	/**
	 * @brief Init function in case you have to initialize the object after
	 * its construction
	 *
	 * @param[in] xmlFile Path/file of the xml configuration
	 */
	void init(const std::string xmlFile);

	/**
	 * @brief This function shall return a vector of strigs with the class
	 * types of each of the sensors found in the XML file
	 *
	 * @return Vector of strings with the sensor classes ordered as was
	 * presented in the XML file
	 */
	std::vector<std::string> getListOfSensorClasses();

	/**
	 * @brief Get sensor name
	 *
	 * @param[in] id Id of the sensor to get information from
	 *
	 * @return string with the name
	 */
	std::string getSensorName(int id);

	/**
	 * @brief Get sensor Max Runs
	 *
	 * @param[in] id Id of the sensor to get information from
	 *
	 * @return integer with the maximum number of runs specified
	 */
	int getSensorMaxRuns(int id);

	/**
	 * @brief Get sensor Sounding Period
	 *
	 * @param[in] id Id of the sensor to get information from
	 *
	 * @return integer with the Sounding Period in milliseconds [ms]
	 */
	int getSensorSoundingPeriod(int id);

	/**
	 * @brief Get sensor Offset Time
	 *
	 * @param[in] id Id of the sensor to get information from
	 *
	 * @return integer with the Offset Time in milliseconds [ms]
	 */
	int getSensorOffsetTime(int id);

	/**
	 * @brief Get GPIO Pin
	 *
	 * @param[in] id Id of the sensor to get information from
	 *
	 * @return integer GPIO pin identifier
	 */
	int getSensorGpioPin(int id);

	/**
	 * @brief Get topic to write to using MQTT
	 *
	 * @param[in] id Id of the sensor to get information from
	 *
	 * @return string with the MQTT Topic
	 */
	std::string getSensorTopic(int id);

	/**
	 * @brief Default destructor
	 */
	virtual ~XmlParser();

private:

	void parseSensors(rapidxml::xml_node<> * root);
};

#endif /* XMLPARSER_H_ */

/**
 * @} (XmlParser)
 */


