#include "Arduino.h"
#include "motor_driver.h"

MotorDriver::MotorDriver(const int motorA_In1, const int motorA_In2, 
                         const int motorB_In3, const int motorB_In4, 
                         int baseSpeed) {
  // implement here
}

void MotorDriver::driveMotorA(const int motorA_In1, const int motorA_In2, int speed) {
  // implement here
}

void MotorDriver::driveMotorA(const int motorA_In1, const int motorA_In2) {
  // implement here
}

void MotorDriver::driveMotorB(const int motorB_In3, const int motorB_In4, int speed) {
  // implement here
}

void MotorDriver::driveMotorB(const int motorB_In3, const int motorB_In4) {
  // implement here
}

int MotorDriver::speedToAnalogVal(int speed) {
  // convert speed to 0-255 value to analogWriteVal
}
