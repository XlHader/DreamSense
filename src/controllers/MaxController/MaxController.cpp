#include "MaxController.h"

void MaxController::setup() {
  Serial.println("Inicializando sensor MAX30105...");
  
  while (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("No se pudo encontrar un sensor MAX30105. Verifique la conexión del sensor.");
    delay(5000);
  }

  Serial.println("Sensor MAX30105 inicializado.");

  particleSensor.setup(0x02, MAX_BRIGHTNESS, 400, 411, 4096); //Configure sensor with these settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
}

void MaxController::update() {
  static unsigned long previousMillis = 0;
  const unsigned long interval = 500; // Intervalo de tiempo deseado entre las mediciones en milisegundos

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

    //read the first 100 samples, and determine the signal range
    for (byte i = 0 ; i < bufferLength ; i++) {
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample
    }

    //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

    // Actualizar los valores en el objeto JSON o realizar cualquier otra operación necesaria
    maxReadingsDocument.clear();
    maxReadingsJson = "";

    JsonObject heartRateObj = maxReadingsDocument.createNestedObject("heartRate");
    heartRateObj["bpm"] = heartRate;
    heartRateObj["valid"] = validHeartRate;

    JsonObject spo2Obj = maxReadingsDocument.createNestedObject("spo2");
    spo2Obj["value"] = spo2;
    spo2Obj["valid"] = validSPO2;

    serializeJson(maxReadingsDocument, maxReadingsJson);

    // Imprimir los resultados o realizar cualquier otra acción
    Serial.println("Ritmo cardíaco: " + String(heartRate));
    Serial.println("Saturación de oxígeno: " + String(spo2));
  }
}

std::string MaxController::getJson() {
  return maxReadingsJson;
}
