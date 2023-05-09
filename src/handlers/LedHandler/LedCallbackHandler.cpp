#include "LedCallbackHandler.h"

void LedCallbackHandler::onWrite(BLECharacteristic *ledCharacteristic) {
  std::string value = ledCharacteristic->getValue();

  if (value.length() < 0)
    return;

  value[0] == '1'
    ? LedController::turnOn()
    : LedController::turnOff();
}
