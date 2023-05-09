#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

class LedController {
  public:
    void setup();
    bool letStateOn();
    static void turnOn();
    static void turnOff();

  private:
    static const int LED_PIN = 2;
};

#endif
