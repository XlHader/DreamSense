#include "LedController.h"
#include <Arduino.h>

void LedController::setup() {
  pinMode(LED_PIN, OUTPUT);
}

void LedController::turnOff() {
  digitalWrite(LED_PIN, LOW);
}

void LedController::turnOn() {
  digitalWrite(LED_PIN, HIGH);
}

bool LedController::letStateOn() {
  return digitalRead(LED_PIN) == HIGH;
}