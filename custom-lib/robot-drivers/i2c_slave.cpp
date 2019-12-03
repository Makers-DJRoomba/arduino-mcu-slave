#include "Arduino.h"
#include <Wire.h>

I2CSlave::I2CSlave(uint8_t my_address) {
  Wire.begin(my_address);
  Wire.onRequest(SendDataToMaster);
  Wire.onReceive(RegisterMasterCommand);
}

int I2CSlave::getMotorDriverCmd() {
  return motor_driver_cmd;
}

void I2CSlave::SendDataToMaster() {
  // Initially receive int specifying 
  // what data to respond with
  while (Wire.available()) {
    int device_type = Wire.read();
  }

  // Send back the correct data
  switch (device_type) {
    case Device::ENCODER:
      Wire.write(RequestHolder.encoder_speed)
      break;

    case Device::ULTRASONIC:
      Wire.write(RequestHolder.ranger_dist);
      break;

    case Device::IMU:
      Wire.write(RequestHolder.imu_data)
      break;

    default:
      Wire.write(-1)
  }
}

void I2CSlave::RegisterMasterCommand() {
  while (Wire.available()) {
    motor_driver_cmd = Wire.read();
  }
}