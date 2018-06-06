#include "mqtt_client.h"
#include "bluetooth_service.h"

#define PORT 1883
#define BROKER "iot.eclipse.org"
#define LED_MAC "F8:1D:78:60:3D:96"

int main(void) {
  //create bluetooth service
  BluetoothService bluetooth_service(LED_MAC);

  //create mqtt client
  MqttClient mqtt_client(BROKER, PORT, &bluetooth_service);

  while(1) {
    //loop mqtt
    mqtt_client.loop(0);
  }
}
