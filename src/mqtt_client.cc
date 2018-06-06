#include "mqtt_client.h"

MqttClient::MqttClient(string broker_address, int broker_port,
  BluetoothService *bluetooth_service) {
  //assign data
  m_status = -1;
  m_broker_port = broker_port;
  m_broker_address = broker_address;
  m_bluetooth_serivce = bluetooth_service;

  //init mqtt
  lib_init();

  //connect to broker
  connect(m_broker_address.c_str(), m_broker_port, KEEP_ALIVE);
}

MqttClient::~MqttClient() {
  //clean up
  lib_cleanup();
  cout << "Delete mqtt client" << endl;
}

int MqttClient::is_connected() {
  return m_status;
}

void MqttClient::subscribe_topics(vector<string> topics) {
  //check status
  if(!m_status) {
    //loop list of topics
    for (size_t i = 0; i < topics.size(); i++) {
      //subcribe topic
      subscribe(NULL, topics[i].c_str());
    }
  } else {
    cout << "Mqtt client is disconnected, could not subcribe topics" << endl;
  }
}

void MqttClient::publish_message(string topic, string message) {
  //publish message to topic
  if(!m_status) {
    char buffer[MESSAGE_BUFFER_SIZE];
    sprintf(buffer, "%s", message.c_str());
    publish(NULL, topic.c_str(), message.length(), buffer);
    cout << "public message = " << message << ", topic = " << topic << endl;
  } else {
    cout << "Mqtt client disconnected, could not publish message" << endl;
  }
}

void MqttClient::on_error() {
  //log error
  m_status = -1;
  cout << "Mqtt client is error" << endl;
}

void MqttClient::on_connect(int rc) {
  //handle on connect
  m_status = rc;
  string msg = "Mqtt client is connected with rc = ";
  msg.append(to_string(rc));
  cout << msg << endl;
}

void MqttClient::on_publish(int rc) {
  //handle on publish
  string msg = "Mqtt client published message with rc = ";
  msg.append(to_string(rc));
  cout << msg << endl;
}

void MqttClient::on_disconnect(int rc) {
  //handle on disconnect
  m_status = rc;
  string msg = "Mqtt client is disconnected with rc = ";
  msg.append(to_string(rc));
  cout << msg << endl;
  
  //re-connect mqtt client
  reconnect();
}

void MqttClient::on_unsubscribe(int rc) {
  //handle on unsubscribe
  string msg = "Mqtt client is unsubscribed with rc = ";
  msg.append(to_string(rc));
  cout << msg << endl;
}

void MqttClient::on_log(int level, const char * message) {
  //handle on log
  string msg = "Mqtt client logs with level = ";
  msg.append(to_string(level));
  msg.append(", message = ");
  msg.append(message);
  cout << msg << endl;
}

void MqttClient::on_message(const struct mosquitto_message *message) {
  //handle on message
  char buffer[MESSAGE_BUFFER_SIZE];
  sprintf(buffer, "%s",static_cast<char*>(message->payload));
  string msg = "Mqtt client is received a message with content = ";
  msg.append(buffer);
  cout << msg << endl;
}

void MqttClient::on_subscribe(int mode, int qos_count, const int *granted_qos){
  //handle on subscribe
  string msg = "Mqtt client is subcribed with mode = ";
  msg.append(to_string(mode));
  msg.append(", qos count = ");
  msg.append(to_string(qos_count));
  msg.append(", granted qos = ");
  msg.append((char *)granted_qos);
  cout << msg << endl;
}
