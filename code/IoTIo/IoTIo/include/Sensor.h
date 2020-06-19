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
 * @file Sensor.h
 * @brief Abstract class for sensor implementation.
 * @details This class shall create a periodic thread
 *
 */

#ifndef SENSOR_H_
#define SENSOR_H_

/* *****************************************************************************
 *  INCLUDES
 * ****************************************************************************/

/* System libraries */
#include <string>
#include <thread>

/* PAHO MQTT Library */
extern "C" {
#include "MQTTClient.h"
}

/* *****************************************************************************
 *  CLASS DECLARATION
 * ****************************************************************************/

class Sensor {

private:

	/** @brief Sensor Name for displaying purposes */
	std::string _sensorName;

	/** @brief Sounding Period in milliseconds [ms] */
	unsigned int _soundingPeriod;

	/** @brief Offset in milliseconds [ms] */
	unsigned int _offsetTime;

	/** @brief Number of executions of the main thread, 0 means unlimited */
	unsigned int _maxRuns;

	/** @brief Runs counter */
	unsigned int _runsCounter;

	/** @brief Number of times the threadBody has bee executed */
	unsigned long long _execCntr;

	/** @brief Thread object */
	std::thread _thread;

	/**
	 * @brief Thread body to be called in every step.
	 * @note Note that this function shall call internally to the pure virtual
	 * function @b operation and then shall perform a sleep of the @ _soundingPeriod
	 */
	void threadBody();

	/** @brief MQTT Handler */
	MQTTClient _mqttHandler = NULL;

	/** @brief MQTT Publish timeout */
	const unsigned long MQTT_TIMEOUT = 1000L;

protected:

	/*
	 * MQTT Configuration
	 */

	/** @TODO All these data should come from an xml file */

	/** @brief API Key to connect */
	std::string _accessToken = "LIRMyALH8x164XD3a4kWz";

	/** @brief Topic */
	std::string _topic = "v1/devices/me/telemetry";

protected:

	/*
	 * Note that the pure virtual function must be declared prior to the destructor
	 * (I don't know why)
	 */

	/**
	 * @brief Abstract class to be implemented in derived classes where the logic
	 * of every sounding period shall be implemented
	 */
	virtual void operation() = 0;

public:

	/* Constructors */

	/** @brief Delete default constructor */
	//Sensor() = delete;

	/**
	 * @brief No copy constructor for this class
	 */
	//Sensor(const Sensor&) = delete;

	/**
	 * @brief No assignment operation for this class
	 */
	Sensor& operator=(const Sensor&) = delete;

	/**
	 * @brief Constructor with sensor name and sounding period
	 */
	Sensor(const std::string &sensorName, const unsigned int soundingPeriod);

	/**
	 * @brief Constructor with only sensor name
	 */
	Sensor(const std::string &sensorName) :
			Sensor(sensorName, 0) {
	}
	;

	/* Destructors */

	/**
	 * @brief Destructor
	 */
	virtual ~Sensor();

	/* Sets and Gets */

	/**
	 * @brief Get the sensor name assigned
	 *
	 * @return Reference to Sensor Name
	 */
	const std::string& getSensorName() const;

	/**
	 * @brief Set the name of the sensor
	 *
	 * @param[in] sensorName Name of the sensor to provide
	 *
	 * @return void
	 */
	void setSensorName(const std::string &sensorName);

	/**
	 * @brief Get the Sounding Period
	 * @return Number of milliseconds [ms] for the Sounding Period configured
	 */
	unsigned int getSoundingPeriod() const;

	/**
	 * @brief Set the Sounding Period
	 * @param[in] soundingPeriod Sounding Period in milliseconds [ms]
	 */
	void setSoundingPeriod(const unsigned int soundingPeriod);

	/**
	 * @brief Obtain the Maximum number of Runs of configured
	 * @return Maximum runs configured, 0 means infinite
	 */
	unsigned int getMaxRuns() const;

	/**
	 * @brief Get the value of the Executions Counter
	 *
	 * @return Number of times the main thread has been executed.
	 */
	unsigned long long getExecCntr() const;

	/**
	 * @brief Set the maximum number of runs allowed
	 * @param[in] maxRuns Number of Maximum runs, 0 means infinite.
	 */
	void setMaxRuns(const unsigned int maxRuns);

	/* Threading operations */

	/**
	 * @brief Start the thread operation
	 * @note that the thread shall be executed as many times as it is defined
	 * by the private member @b _maxRuns, after that the thread ends its own
	 * execution. You can restart the thread again by calling this function
	 * again.
	 */
	void run();

	/**
	 * @brief join operation
	 */
	void join();

private:

	/* MQTT */

	/**
	 * @brief This function shall create the MQTT Handler resources and
	 * initialize them.
	 *
	 * @param[in] address String with the hostname (or IP address).
	 * @param[in] port Port to connect to.
	 * @return Return code
	 * @retval 0 if the operation was SUCCESS
	 * @retval # if the operation produce an error. The value returned is the
	 * MQTT error code
	 */
	int mqttInit(const std::string address, const unsigned int port);

	/**
	 * @brief Establish the connection with the remote
	 * @param[in] accessToken String with the API key to connect to.
	 * @return Return code
	 * @retval 0 if the operation was SUCCESS
	 * @retval # if the operation produce an error. The value returned is the
	 * MQTT error code
	 */
	int mqttConnect(const std::string accessToken);

	/**
	 * @brief Publish a MQTT message into an specific topic
	 * @param[in] topic String with the destination topic
	 * @param[in] message Message to publish (as string)
	 * @return Return code
	 * @retval 0 if the operation was SUCCESS
	 * @retval # if the operation produce an error. The value returned is the
	 * MQTT error code
	 */
	int mqttPublish(const std::string topic, const std::string message);

	/**
	 * @brief Down the MQTT connection
	 * @retval 0 if the operation was SUCCESS
	 * @retval # if the operation produce an error. The value returned is the
	 * MQTT error code
	 */
	int mqttDisconnect(void);

	/**
	 * @brief Destroy and free the MQTT API resources
	 */
	void mqttDestroy(void);

public:

	/**
	 * @brief Configure the MQTT connection. Note that this function contains
	 * as default parameters the hostname and the port, if none are provided
	 * by the user they shall be @i localhost and @i 1883 respectively.
	 * @attention Note that this MQTT link has been developed to be used for
	 * @b Thingsboard however some configuration is let to the user so it
	 * can be used with other systems.
	 * @param[in] accessToken string with the API key of the remote target
	 * @param[in] hostname Name or IP of the remote. Default @i localhost
	 * @param[in] port Port to be used in the communication. Default @i 1883
	 *
	 * @throws This function can throw a @b MqttException that shall also
	 * provides information about the PAHO MQTT error code.
	 */
	void configureMqtt(const std::string accessToken,
			const std::string hostname = "localhost", const unsigned int port =
					1883);

	/**
	 * @brief Send an MQTT message to an specific topic
	 * @param[in] topic String with the topic to write in
	 * @param[in] message Message to be sent
	 *
	 * @throws This function can throw a @b MqttException that shall also
	 * provides information about the PAHO MQTT error code.
	 */
	void sendMqttMessage(const std::string topic, const std::string message);

	/**
	 * @brief Get the Access Token Key
	 * @return Access Token key
	 */
	const std::string& getAccessToken() const;

	/**
	 * @brief Set the Access Token Key
	 * @param[in] accessToken String with the Access token key
	 */
	void setAccessToken(const std::string &accessToken);

	/**
	 * @brief Get the Topic used for sending the MQTT messages
	 * @return string with the topic requested
	 */
	const std::string& getTopic() const;

	/**
	 * @brief Set the Topic to send the MQTT message to
	 * @param[in] topic string with the topic
	 */
	void setTopic(const std::string &topic);
};

#endif /* SENSOR_H_ */

/**
 * @} (Sensor)
 */
