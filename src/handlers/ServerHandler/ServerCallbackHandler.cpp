#include "ServerCallbackHandler.h"

void ServerCallbackHandler::onConnect(BLEServer *pServer) {
  BluetoothController::deviceConnected = true;
}

void ServerCallbackHandler::onDisconnect(BLEServer *pServer) {
  BluetoothController::deviceConnected = false;
}