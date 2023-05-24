#include <Arduino.h>

#include "controllers/BluetoothController/BluetoothController.h"
#include "controllers/MpuController/MpuController.h"
#include "controllers/LedController/LedController.h"

BluetoothController bluetoothController;
MpuController mpuController;
LedController ledController;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  ledController.setup(); 
  mpuController.setup();
  bluetoothController.setup();
}

void loop() {
  if (bluetoothController.deviceConnected && ledController.letStateOn()) {
    Serial.println("Realizando lectura de datos de los sensores.");
    mpuController.update();
    bluetoothController.setMpuCharacteristicValue(mpuController.getJson());
    delay(5000);
  }

  if (!bluetoothController.deviceConnected && !ledController.letStateOn()) {
    Serial.println("En espera de conexión bluetooth.");
    delay(5000);
  }

  if (bluetoothController.deviceConnected && !ledController.letStateOn()) {
    Serial.println("Conectado al dispositivo pero en espera de activación del led.");
    delay(5000);
  }
}