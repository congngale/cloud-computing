#include "bluetooth_service.h"

#include <tinyb.hpp>

#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <csignal>

#define LIGHT_CONTROL_UUID "0000ffe5-0000-1000-8000-00805f9b34fb" 
#define LIGHT_CHARACTERITISTIC "0000ffe9-0000-1000-8000-00805f9b34fb"

using namespace tinyb;

BluetoothService::BluetoothService(string device_mac) {
  //set device mac
  m_device_mac = device_mac;

  //start service
  try {
    p_manager = BluetoothManager::get_bluetooth_manager();
  } catch(const runtime_error& e) {
    cerr << "Error while initializing libtinyb: " << e.what() << endl;
    throw exception();
  }

  /* Start the discovery of devices */
  bool ret = p_manager->start_discovery();
  cout << "Started = " << (ret ? "true" : "false") << endl;

  for (int i = 0; i < 15; ++i) {
    cout << "Discovered devices: " << endl;
	
    /* Get the list of devices */
    auto list = p_manager->get_devices();

    for (auto it = list.begin(); it != list.end(); ++it) {
      cout << "Class = " << (*it)->get_class_name() << " ";
      cout << "Path = " << (*it)->get_object_path() << " ";
      cout << "Name = " << (*it)->get_name() << " ";
      cout << "Connected = " << (*it)->get_connected() << " " << endl;

      /* Search for the device with the address given as a parameter to the program */
      if ((*it)->get_address() == m_device_mac)
	p_led = (*it).release();
      }

      /* Free the list of devices and stop if the device was found */
      if (p_led != nullptr) break;
	
      /* If not, wait and try again */
      this_thread::sleep_for(chrono::seconds(4));
      cout << endl;
  }
  
  /* Stop the discovery (the device was found or number of tries ran out */
  ret = p_manager->stop_discovery();
  cout << "Stopped = " << (ret ? "true" : "false") << endl;

  if (p_led == nullptr) {
    cout << "Could not find device " << m_device_mac << endl;
    throw exception();
  }

  /* Connect to the device and get the list of services exposed by it */
  p_led->connect();
  cout << "Discovered services: " << endl;
  while (true) {
    /* Wait for the device to come online */
    this_thread::sleep_for(chrono::seconds(4));

    auto list = p_led->get_services();
    if (list.empty()) continue;

    for (auto it = list.begin(); it != list.end(); ++it) {
      cout << "Class = " << (*it)->get_class_name() << " ";
      cout << "Path = " << (*it)->get_object_path() << " ";
      cout << "UUID = " << (*it)->get_uuid() << " ";
      cout << "Device = " << (*it)->get_device().get_object_path() << " ";
      cout << endl;

      /* Search for the temperature service, by UUID */
      if ((*it)->get_uuid() == LIGHT_CONTROL_UUID)
        p_light_service = (*it).release();
      }
      break;
    }

    if (p_light_service == nullptr) {
        cout << "Could not find service " << LIGHT_CONTROL_UUID << endl;
        throw exception();
    }

    /* If there is a temperature service on the device with the given UUID,
     * get it's characteristics, by UUID again */
    auto list = p_light_service->get_characteristics();
    std::cout << "Discovered characteristics: " << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
      cout << "Class = " << (*it)->get_class_name() << " ";
      cout << "Path = " << (*it)->get_object_path() << " ";
      cout << "UUID = " << (*it)->get_uuid() << " ";
      cout << "Service = " << (*it)->get_service().get_object_path() << " ";
      cout << endl;

      if ((*it)->get_uuid() == LIGHT_CHARACTERITISTIC) {
        p_light_control = (*it).release();
      }
    }

    if (p_light_control == nullptr) {
      cout << "Could not find characteristics." << std::endl;
      throw exception();
    }
}

BluetoothService::~BluetoothService() {
  //empty destructor
}

void BluetoothService::turn_on() {
  //turn on
  p_light_control->write_value(on);
}

void BluetoothService::turn_off() {
  //turn off
  p_light_control->write_value(off);
}

void BluetoothService::set_warm(unsigned char value) {
  //update value
  warm[4] = value;

  //set warm
  p_light_control->write_value(warm);
}

void BluetoothService::set_rgb(unsigned char r, unsigned char g,
  unsigned char b) {
  //update value
  rgb[1] = r;
  rgb[2] = g;
  rgb[3] = b;

  //set rgb
  p_light_control->write_value(rgb);
}

void BluetoothService::disconnect() {
  /* Disconnect from the device */
  try {
    p_led->disconnect();
  } catch (exception &e) {
    cout << "Error: " << e.what() << endl;
  }
}
