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
 * @file XmlParser.cpp
 * @brief (see XmlParser.h)
 * @details (see XmlParser.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided Interface */
#include "XmlParser.h"

/* System libraries */
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdexcept>
#include <algorithm>

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

XmlParser::XmlParser(const std::string xmlFile) {

	/* Initialize the object */
	init(xmlFile);
}

void XmlParser::init(const std::string xmlFile) {

	/* File handler */
	std::ifstream xmlFileHandler(xmlFile);

	/* Initial Parse of the XML */
	if (xmlFileHandler.is_open()) {

		/* Temporal buffer to dump the content of the XML File */
		std::stringstream xmlBuffer;
		xmlBuffer << xmlFileHandler.rdbuf();
		xmlFileHandler.close();

		/* Content of the XML */
		_xmlContent = xmlBuffer.str();

		/* Parse the file */
		_xml.parse<0>(&_xmlContent[0]);

		/* Save the roots */
		_rAppConf = _xml.first_node("app_config");
		_rEnvConf = _xml.first_node("env_config");

		/* Parse Application configuration */
		for (rapidxml::xml_node<> *pNode = _rAppConf->first_node(); pNode;
				pNode = pNode->next_sibling()) {

			/* Parse sensors */
			if (!std::string(pNode->name()).compare("sensors")) {

				for (rapidxml::xml_node<> *pSubNode = pNode->first_node();
						pSubNode; pSubNode = pSubNode->next_sibling()) {

					/* Push back the sensor XML root handler to the internal vector */
					_xmlSensorsData.push_back(pSubNode);
				}
			}

			/* Parse actuators */

			/**
			 * @TODO
			 */
		}

	} else {

		std::stringstream msg;
		msg << "File '" << xmlFile << "' not found!";
		throw std::runtime_error(msg.str());
	}

	/* Parse environment configuration */
	/** @TODO */
}

XmlParser::~XmlParser() {
	// TODO Auto-generated destructor stubs
}

std::vector<std::string> XmlParser::getListOfSensorClasses() {

	/* Vector of strings with the list of sensor classes */
	std::vector<std::string> list;

	for (auto it = _xmlSensorsData.begin(); it != _xmlSensorsData.end(); ++it) {
		/* Pointer to the node */
		rapidxml::xml_node<> *root = *it;

		list.push_back(root->first_attribute("class")->value());
	}

	return list;
}

std::string XmlParser::getSensorName(int id) {

	/* XML Root */
	rapidxml::xml_node<> *root = _xmlSensorsData[id];

	/* String to return */
	std::string name = root->first_node("name")->value();

	return name;
}

int XmlParser::getSensorMaxRuns(int id) {

	/* XML Root */
	rapidxml::xml_node<> *root = _xmlSensorsData[id];

	/* Value to return */
	int maxRuns = 0;

	/* String with the value from XML */
	std::string data = root->first_node("maxRuns")->value();

	/* only fill maxRuns if there are data, if not left it as 0 */
	if (!data.empty())
	{
		maxRuns = std::stoi(data);
	}

	return maxRuns;
}

int XmlParser::getSensorSoundingPeriod(int id) {

	/* XML Root */
	rapidxml::xml_node<> *root = _xmlSensorsData[id];

	/* Value to return */
	int soundingPeriod = 0;

	/* String with the value from XML */
	std::string data = root->first_node("soundingPeriod")->value();

	/* Check if there is unit attribute 'unit' */
	if (root->first_node("soundingPeriod")->first_attribute("unit") != NULL)
	{

		/* Temporal storage of the attribute value */
		std::string unit = root->first_node("soundingPeriod")->first_attribute("unit")->value();

		/* only fill maxRuns if there are data, if not left it as 0 */
		if (!unit.compare("s"))
		{
			soundingPeriod = stoi(data) * 1000;
		}
		else if (!unit.compare("ms"))
		{
			soundingPeriod = stoi(data);
		}
		else
		{
			/** @TODO Exception NOT_SUPPORTED */
		}
	} else {

		soundingPeriod = stoi(data);
	}

	return soundingPeriod;
}

int XmlParser::getSensorOffsetTime(int id) {

	/* XML Root */
	rapidxml::xml_node<> *root = _xmlSensorsData[id];

	/* Value to return */
	int offsetTime = 0;

	/* String with the value from XML */
	std::string data = root->first_node("offsetTime")->value();

	/* Check if there is unit attribute 'unit' */
	if (root->first_node("offsetTime")->first_attribute("unit") != NULL)
	{

		/* Temporal storage of the attribute value */
		std::string unit = root->first_node("offsetTime")->first_attribute("unit")->value();

		/* only fill maxRuns if there are data, if not left it as 0 */
		if (!unit.compare("s"))
		{
			offsetTime = stoi(data) * 1000;
		}
		else if (!unit.compare("ms"))
		{
			offsetTime = stoi(data);
		}
		else
		{
			/** @TODO Exception NOT_SUPPORTED */
		}
	} else {

		offsetTime = stoi(data);
	}

	return offsetTime;
}

int XmlParser::getSensorGpioPin(int id) {

	/* XML Root */
	rapidxml::xml_node<> *root = _xmlSensorsData[id];

	/* Value to return */
	int gpioPin = 0;

	/* String with the value from XML */
	std::string data = root->first_node("gpioPin")->value();

	/* only fill maxRuns if there are data, if not left it as 0 */
	if (!data.empty())
	{
		gpioPin = std::stoi(data);
	}

	return gpioPin;
}

std::string XmlParser::getSensorTopic(int id) {

	/* XML Root */
	rapidxml::xml_node<> *root = _xmlSensorsData[id];

	/* String to return */
	std::string name = root->first_node("topic")->value();

	return name;
}

void XmlParser::parseSensors(rapidxml::xml_node<> *root) {

	/* Get the class (lowercase) */
	std::string sensorClass = root->first_attribute("class")->value();
	std::transform(sensorClass.begin(), sensorClass.end(), sensorClass.begin(),
			[](unsigned char c) {
				return std::tolower(c);
			});

	if (!sensorClass.compare("dht11")) {
		for (rapidxml::xml_node<> *pNode = root->first_node(); pNode; pNode =
				pNode->next_sibling()) {

			/* Fill the data to the temporal union */
			//data.dht11.common.name = std::string(pNode->value());
			std::cout << pNode->name() << std::endl;
		}
	} else {

		std::stringstream msg;
		msg << "Sensor Class '" << sensorClass << "' not supported!";
		throw std::runtime_error(msg.str());
	}

//	std::cout << root->first_attribute("class")->value() << std::endl;
}

/**
 * @} (XmlParser)
 */

