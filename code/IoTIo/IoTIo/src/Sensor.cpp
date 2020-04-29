/**
 * @addtogroup Sensor
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
 * @file Sensor.cpp
 * @brief (see Sensor.h)
 * @details (see Sensor.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Provided interface */
#include "Sensor.h"

/* System libraries */
#include <chrono>

#ifdef DEBUG
#include <iostream>
#endif /* DEBUG */

/* Exceptions */
#include "MqttException.h"

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/

Sensor::Sensor(const std::string &sensorName,
		const unsigned int soundingPeriod) {

	/* Set the sensor name */
	_sensorName = sensorName;

	/* Set the default Sounding value */
	_soundingPeriod = soundingPeriod;

	/* Offset time */
	_offsetTime = 0;

	/* Maximum Number of runs, by default unlimited */
	_maxRuns = 0;

	/* Initialize runs counter */
	_runsCounter = _maxRuns;

	/* Initialize the number of thread counter */
	_execCntr = 0;
}

Sensor::~Sensor() {

	/* Wait for the finalization of the thread */
	if (_thread.joinable()) {
		_thread.join();
	}

	/* Destroy the MQTT resources if the are allocated */
	if (_mqttHandler != NULL)
	{
		mqttDestroy();
	}
}

/* *****************************************************************************
 * SETs and GETs
 * ****************************************************************************/

unsigned int Sensor::getSoundingPeriod() const {

	return _soundingPeriod;
}

void Sensor::setSoundingPeriod(unsigned int soundingPeriod) {
	_soundingPeriod = soundingPeriod;
}

const std::string& Sensor::getSensorName() const {
	return _sensorName;
}

void Sensor::setSensorName(const std::string &sensorName) {
	_sensorName = sensorName;
}

unsigned int Sensor::getMaxRuns() const {
	return _maxRuns;
}

void Sensor::setMaxRuns(const unsigned int maxRuns) {

	/* Set the Maximum runs configured */
	_maxRuns = maxRuns;
}

unsigned long long Sensor::getExecCntr() const {
	return _execCntr;
}

/* *****************************************************************************
 * THREAD RELATED METHODS
 * ****************************************************************************/

void Sensor::run() {

	/* Reset the runs Counter */
	_runsCounter = _maxRuns;

	/* Spawn the thread */
	this->_thread = std::thread([=] {this->threadBody();});
}

void Sensor::join() {
	_thread.join();
}

void Sensor::threadBody() {

	/* In the case of _maxRuns = 0, fake the _runsCounter */
	if (_maxRuns == 0) {
		_runsCounter = 1;
	}

	/* Apply the offset time configured */
	std::this_thread::sleep_for(std::chrono::milliseconds(_offsetTime));

	while (_runsCounter > 0) {

#ifdef DEBUG
		std::cout << "<START> operation()" << std::endl;
#endif /* DEBUG */

#ifdef DEBUG
		std::cout << "[" << _execCntr << "] " << _sensorName << std::endl;
#endif /* DEBUG */

		/* Run the user define operations */
		/**
		 * @TODO Add exception management
		 */
		operation();

#ifdef DEBUG
		std::cout << "<END> operation()" << std::endl;
#endif /* DEBUG */

		/* Decrease runs counter (if applicable) */
		if (_maxRuns > 0) {
			_runsCounter--;
		}

		/* Wait for the next cycle */
		std::this_thread::sleep_for(std::chrono::milliseconds(_soundingPeriod));

		/* Increment thread counter */
		_execCntr++;
	}
}

int Sensor::mqttInit(const std::string address, const unsigned int port) {

	/* Return code for the MQTT API */
	int mqttRetCode = MQTTCLIENT_SUCCESS;

	/* Address URL */
	std::string addressUrl;

	/* Generate the address url */
	addressUrl.append("tcp://");
	addressUrl.append(address);
	addressUrl.append(":");
	addressUrl.append(std::to_string(port));

	/* Create the handler */
	mqttRetCode = MQTTClient_create(&_mqttHandler, addressUrl.c_str(),
			_sensorName.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL);

	return mqttRetCode;
}

int Sensor::mqttConnect(const std::string accessToken) {

	/* Return code for the MQTT API */
	int mqttRetCode = MQTTCLIENT_SUCCESS;

	/* Options structure for the MQTT API */
	MQTTClient_connectOptions connOptions =
	MQTTClient_connectOptions_initializer;

	/* Set-up the default options */
	connOptions.keepAliveInterval = 20;
	connOptions.cleansession = 1;
	connOptions.username = accessToken.c_str();

	/* Establish the connection */
	mqttRetCode = MQTTClient_connect(_mqttHandler, &connOptions);

	return mqttRetCode;

}

int Sensor::mqttPublish(const std::string topic, const std::string message) {

	/* Return code for the MQTT API */
	int mqttRetCode = MQTTCLIENT_SUCCESS;

	/* Token for MQTT */
	int token = -1;

	/* Container for the message */
	MQTTClient_message mqttMessage = MQTTClient_message_initializer;

	/* Fill the MQTT message */
	mqttMessage.payload = (void *)message.c_str();
	mqttMessage.payloadlen = message.length();
	mqttMessage.qos = 1;
	mqttMessage.retained = 0;

	/* Publish the message */
	mqttRetCode = MQTTClient_publishMessage(_mqttHandler, topic.c_str(), &mqttMessage,
					&token);

	/* Wait for the delivery of the message */
	if (mqttRetCode == MQTTCLIENT_SUCCESS)
	{
		mqttRetCode = MQTTClient_waitForCompletion(_mqttHandler, token, MQTT_TIMEOUT);
	}

	return mqttRetCode;
}

int Sensor::mqttDisconnect(void) {

	/* Return code for the MQTT API */
	int mqttRetCode = MQTTCLIENT_SUCCESS;

	/* Disconnect */
	mqttRetCode = MQTTClient_disconnect(_mqttHandler, MQTT_TIMEOUT);

	return mqttRetCode;
}

void Sensor::mqttDestroy(void) {

	MQTTClient_destroy(&_mqttHandler);
}

void Sensor::configureMqtt(const std::string accessToken,
		const std::string hostname, const unsigned int port) {

	/* Return code for the MQTT API */
	int mqttRetCode = MQTTCLIENT_SUCCESS;

	/* Allocation of resources */
	mqttRetCode = mqttInit(hostname, port);

	if (mqttRetCode != MQTTCLIENT_SUCCESS)
	{
		THROW_MQTT(mqttRetCode);
	}

	/*
	 *  Establish the connection
	 */

	if (mqttRetCode == MQTTCLIENT_SUCCESS)
	{
		mqttRetCode = mqttConnect(accessToken);

		if (mqttRetCode != MQTTCLIENT_SUCCESS)
		{
			THROW_MQTT(mqttRetCode);
		}
	}
}

void Sensor::sendMqttMessage(const std::string topic,
		const std::string message) {

	/* Return code for the MQTT API */
	int mqttRetCode = MQTTCLIENT_SUCCESS;

	/* Send the message */
	mqttRetCode = mqttPublish(topic, message);

	if (mqttRetCode != MQTTCLIENT_SUCCESS)
	{
		THROW_MQTT(mqttRetCode);
	}
}

/**
 * @} (Sensor)
 */
