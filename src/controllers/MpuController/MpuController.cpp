#include "MpuController.h"

void MpuController::setup() {
  while (!mpu.begin()) {
    Serial.println("No se pudo encontrar el chip MPU6050");
    delay(5000);
  }

  Serial.println("MPU6050 encontrado");

  // Configurar MPU
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void MpuController::update() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp); 

  mpuReadingsDocument.clear();
  mpuReadingsJson = "";
  
  JsonObject rotation = mpuReadingsDocument.createNestedObject("rotation");
  JsonObject acceleration = mpuReadingsDocument.createNestedObject("acceleration");

  acceleration["x"] = a.acceleration.x;
  acceleration["y"] = a.acceleration.y;
  acceleration["z"] = a.acceleration.z;

  rotation["x"] = g.gyro.x;
  rotation["y"] = g.gyro.y;
  rotation["z"] = g.gyro.z;

  serializeJson(mpuReadingsDocument, mpuReadingsJson);
}

std::string MpuController::getJson() {
  return mpuReadingsJson;
}