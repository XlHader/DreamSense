#ifndef MPU_CONTROLLER_H
#define MPU_CONTROLLER_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <string>

class MpuController {
  public:
    void setup();
    void update();
    std::string getJson();

  private: 
    Adafruit_MPU6050 mpu;
    StaticJsonDocument<128> mpuReadingsDocument;
    std::string mpuReadingsJson = "";

};

#endif