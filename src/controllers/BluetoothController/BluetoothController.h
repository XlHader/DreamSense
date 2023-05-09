#ifndef BLUETOOTH_CONTROLLER_H

#define BLUETOOTH_CONTROLLER_H

#include <string>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "handlers/ServerHandler/ServerCallbackHandler.h"
#include "handlers/LedHandler/LedCallbackHandler.h"

class BluetoothController {
public:
  void setup();
  void setMpuCharacteristicValue(std::string value);
  
  static bool deviceConnected;
  
private:
  const std::string LED_SERVICE_UUID = "00001825-0000-1000-8000-00805f9b34fb";
  const std::string LED_CHARACTERISTIC_UUID = "00002a56-0000-1000-8000-00805f9b34fb";
  const std::string MPU_SERVICE_UUID = "6a4ef4e8-5f42-4703-8966-0528516cbd76";
  const std::string MPU_CHARACTERISTIC_UUID = "6a4ef4e2-5f42-4703-8966-0528516cbd76";
  const std::string DEVICE_NAME = "DreamSense";

  BLECharacteristic *ledCharacteristic;
  BLECharacteristic *mpuCharacteristic;

  void configureLedService(BLEServer *espServer) {
    BLEService *ledService = espServer->createService(LED_SERVICE_UUID);
    ledCharacteristic = ledService->createCharacteristic(
        LED_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);
    ledCharacteristic->setValue("0");
    ledCharacteristic->setCallbacks(new LedCallbackHandler());
    ledService->start();
  }

  void configureMpuService(BLEServer *espServer) {
    BLEService *mpuService = espServer->createService(MPU_SERVICE_UUID);
    mpuCharacteristic = mpuService->createCharacteristic(
        MPU_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);
    mpuCharacteristic->setValue("{}");
    mpuService->start();
  }

  void startServices(BLEServer *espServer) {
    espServer->startAdvertising();
  }

  void configureAndStartAdvertising() {
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(LED_SERVICE_UUID);
    pAdvertising->addServiceUUID(MPU_SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
  }
};

#endif
