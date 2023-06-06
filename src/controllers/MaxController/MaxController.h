#ifndef MAX_CONTROLLER_H
#define MAX_CONTROLLER_H

#include <string>
#include <MAX30105.h>
#include <heartRate.h>
#include <spo2_algorithm.h>
#include <ArduinoJson.h>

/**
 * Controlador para el sensor MAX30105. Se calculará el ritmo cardiaco y la saturación de oxígeno en la sangre por un buen
 * algoritmo pero no muy complejo, el cual se encuentra en la librería heartRate.h 
*/
class MaxController
{
public:
  void setup();
  void update();
  std::string getJson();

private:
  MAX30105 particleSensor;
  const int MAX_BRIGHTNESS = 255;
  uint32_t irBuffer[100]; // Infrared LED sensor data
  uint32_t redBuffer[100]; // Red LED sensor data
  int32_t bufferLength; //data length
  int32_t spo2; //SPO2 value
  int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
  int32_t heartRate; //heart rate value
  int8_t validHeartRate; //indicator to show if the heart rate calculation is valid
  StaticJsonDocument<128> maxReadingsDocument;
  std::string maxReadingsJson = "";
};

#endif