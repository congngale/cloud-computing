#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <vector>
#include <iostream>
#include <mosquittopp.h>
#include "bluetooth_service.h"

#define KEEP_ALIVE 60
#define MESSAGE_BUFFER_SIZE 2048

using namespace std;
using namespace mosqpp;

class MqttClient : public mosquittopp {
	public:
		MqttClient(string broker_address, int broker_port, 
		  BluetoothService *bluetooth_service);
		~MqttClient();
		int is_connected(void);
		void subscribe_topics(vector<string> topics);
		void publish_message(string topic, string message);

	private:
		int m_status;
		int m_broker_port;
		string m_client_id;
		string m_broker_address;
		BluetoothService *m_bluetooth_serivce;

		void on_error(void);
		void on_connect(int rc);
		void on_publish(int rc);
		void on_disconnect(int rc);
		void on_unsubscribe(int rc);
		void on_log(int level, const char * message);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
};

#endif //MQTT_CLIENT_H
