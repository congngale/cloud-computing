#ifndef BLUETOOTH_SERVICE_H
#define BLUETOOTH_SERVICE_H

#include <vector>
#include <iostream>
#include <tinyb.hpp>

using namespace std;
using namespace tinyb;

class BluetoothService {
  public:
    BluetoothService(string device_mac);
    ~BluetoothService();
    
    void turn_on(void);
    void turn_off(void);
    void disconnect(void);
    void set_warm(unsigned char value);
    void set_rgb(unsigned char r, unsigned char g, unsigned char b);

  private:
    string m_device_mac;
    BluetoothDevice *p_led = NULL;
    BluetoothManager *p_manager = nullptr;
    BluetoothGattService *p_light_service = NULL;
    BluetoothGattCharacteristic *p_light_control = nullptr;
    vector<unsigned char> on {0xcc, 0x23, 0x33};
    vector<unsigned char> off {0xcc, 0x24, 0x33};
    //update byte 1 - 2 - 3 for RGB value
    vector<unsigned char> rgb {0x56, 0x0a, 0x11, 0x31, 0x00, 0xf0, 0xaa};
    //update byte 4
    vector<unsigned char> warm {0x56, 0x00, 0x00, 0x00, 0x12, 0x0f, 0xaa};
};

#endif //BLUETOOTH_SERVICE_H
