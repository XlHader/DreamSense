#include "BluetoothController.h"

bool BluetoothController::deviceConnected = false;

void BluetoothController::setup() {
  // Inicializar BLE
  BLEDevice::init(DEVICE_NAME);
  BLEServer *espServer = BLEDevice::createServer();
  espServer->setCallbacks(new ServerCallbackHandler());

  // Configurar servicios y características
  configureLedService(espServer);
  configureMpuService(espServer);

  // Iniciar servicios
  startServices(espServer);

  // Configurar y comenzar la publicidad
  configureAndStartAdvertising();
}

void BluetoothController::setMpuCharacteristicValue(std::string value) {
  mpuCharacteristic->setValue(value);
  mpuCharacteristic->notify();
}