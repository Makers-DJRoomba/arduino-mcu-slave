#include "Arduino.h"
#include "motor_driver.h"

MotorDriver::MotorDriver(const int in1, const int in2, const int in3, const int in4,
                         const int enA, const int enB, int duty_cycle)
  : _motorA_in1(in1), _motorA_in2(in2), _motorB_in3(in3), _motorB_in4(in4),
    _motorA_EN(enA), _motorB_EN(enB), _base_duty_cycle(duty_cycle) {
  pinMode(_motorA_EN, OUTPUT);
  pinMode(_motorB_EN, OUTPUT);
  pinMode(_motorA_in1, OUTPUT);
  pinMode(_motorA_in2, OUTPUT);
  pinMode(_motorB_in3, OUTPUT);
  pinMode(_motorB_in4, OUTPUT);
}

void MotorDriver::driveMotorA(int percent_duty_cycle) {
  int actual_PWM = toAnalogValue(percent_duty_cycle);
  
  if (percent_duty_cycle < 0) {            // If value is given then we move backward
    motorAbackward();
    analogWrite(_motorA_EN, -actual_PWM);  // Send PWM signal to motor A
  }
  else {                                   // otherwise move forward
    motorAforward();
    analogWrite(_motorA_EN, actual_PWM);   // Send PWM signal to motor A
  }
}

// runs using _base_duty_cycle
void MotorDriver::driveMotorA() {
  int actual_PWM = toAnalogValue(_base_duty_cycle);
  
  if (_base_duty_cycle < 0) {              // If value is given then we move backward
    actual_PWM = -actual_PWM;
    motorAbackward();
    analogWrite(_motorA_EN, -actual_PWM);  // Send PWM signal to motor A
  }
  else {                                   // otherwise move forward
    motorAforward();
    analogWrite(_motorA_EN, actual_PWM);   // Send PWM signal to motor A
  }
}

void MotorDriver::driveMotorB(int percent_duty_cycle) {
  int actual_PWM = toAnalogValue(percent_duty_cycle);
  
  if (percent_duty_cycle < 0) {            // If value is given then we move backward
    motorBbackward();
    analogWrite(_motorB_EN, -actual_PWM);  // Send PWM signal to motor B
  }
  else {                                   // otherwise move forward
    motorBforward();
    analogWrite(_motorB_EN, actual_PWM);   // Send PWM signal to motor B
  }
}

// runs using _base_duty_cycle
void MotorDriver::driveMotorB() {
  int actual_PWM = toAnalogValue(_base_duty_cycle);

  if (_base_duty_cycle < 0) {              // If value is given then we move backward
    motorBbackward();
    analogWrite(_motorB_EN, -actual_PWM);  // Send PWM signal to motor B
  }
  else {                                   // otherwise move forward
    motorBforward();
    analogWrite(_motorB_EN, actual_PWM);   // Send PWM signal to motor B
  }
}

int MotorDriver::toAnalogValue(int percent_duty_cycle) {
  return 255*percent_duty_cycle/100;
}

void MotorDriver::motorAforward() {
  digitalWrite(_motorA_in1, LOW);
  digitalWrite(_motorA_in2, HIGH);
}

void MotorDriver::motorAbackward() {
  digitalWrite(_motorA_in1, HIGH);
  digitalWrite(_motorA_in2, LOW);
}

void MotorDriver::motorBforward() {
  digitalWrite(_motorB_in3, LOW);
  digitalWrite(_motorB_in4, HIGH);
}

void MotorDriver::motorBbackward() {
  digitalWrite(_motorB_in3, HIGH);
  digitalWrite(_motorB_in4, LOW);
}
