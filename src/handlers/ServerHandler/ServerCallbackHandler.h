#ifndef SERVER_CALLBACK_HANDLER_H
#define SERVER_CALLBACK_HANDLER_H

#include <BLEServer.h>
#include "controllers/BluetoothController/BluetoothController.h"

class ServerCallbackHandler : public BLEServerCallbacks {
public:
  void onConnect(BLEServer *pServer);
  void onDisconnect(BLEServer *pServer);
};

#endif
