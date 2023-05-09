#ifndef LED_CALLBACK_HANDLER_H
#define LED_CALLBACK_HANDLER_H

#include <BLECharacteristic.h>
#include "controllers/LedController/LedController.h"

class LedCallbackHandler : public BLECharacteristicCallbacks {
public:
  void onWrite(BLECharacteristic *ledCharacteristic);
};

#endif
