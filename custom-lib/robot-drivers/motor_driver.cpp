#include "Arduino.h"
#include "motor_driver.h"

MotorDriver::MotorDriver(const int In1, const int In2, 
                         const int In3, const int In4, const int enA, const int enB,
                         int dutycycle)
                         :motorA_EN(enA), motorB_EN(enB), motorA_In1(In1),
                         motorA_In2(In2), motorB_In3(In3), motorB_In4(In4),
                         baseDutyCycle(dutycycle) {
  // implement here
  pinMode(motorA_EN, OUTPUT);
  pinMode(motorB_EN, OUTPUT);
  pinMode(motorA_In1, OUTPUT);
  pinMode(motorA_In2, OUTPUT);
  pinMode(motorB_In3, OUTPUT);
  pinMode(motorB_In4, OUTPUT);
}

void MotorDriver::driveMotorA(int percentDutyCycle) {
  // implement here
	int actual_PWM;
	actual_PWM = 255*(percentDutyCycle/100);
	if(percentDutyCycle < 0) {						//If value is given then we move backward
		actual_PWM = actual_PWM*-1;
		motorAbackward();
	    analogWrite(motorA_EN, actual_PWM); // Send PWM signal to motor A
	}
	else {											//otherwise move forward
		motorAforward();
	    analogWrite(motorA_EN, actual_PWM); // Send PWM signal to motor A
	}
}

// runs using baseDutyCycle
void MotorDriver::driveMotorA() {
  // implement here
	int actual_PWM;
	actual_PWM = 255*(baseDutyCycle/100);
	if(baseDutyCycle < 0) {						//If value is given then we move backward
		actual_PWM = actual_PWM*-1;
		motorAbackward();
	    analogWrite(motorA_EN, actual_PWM); // Send PWM signal to motor A
	}
	else {											//otherwise move forward
		motorAforward();
	    analogWrite(motorA_EN, actual_PWM); // Send PWM signal to motor A
	}
}

void MotorDriver::driveMotorB(int percentDutyCycle) {
  // implement here
	int actual_PWM;
	actual_PWM = 255*(percentDutyCycle/100);
	if(percentDutyCycle < 0) {						//If value is given then we move backward
		actual_PWM = actual_PWM*-1;
	    motorBbackward();
	    analogWrite(motorB_EN, actual_PWM); // Send PWM signal to motor B
	}
	else {											//otherwise move forward
	    motorBforward();
	    analogWrite(motorB_EN, actual_PWM); // Send PWM signal to motor B
	}
}

// runs using baseDutyCycle
void MotorDriver::driveMotorB() {
  // implement here
	int actual_PWM;
	actual_PWM = 255*(baseDutyCycle/100);
	if(baseDutyCycle < 0) {						//If value is given then we move backward
		actual_PWM = actual_PWM*-1;
	    motorBbackward();
	    analogWrite(motorB_EN, actual_PWM); // Send PWM signal to motor B
	}
	else {											//otherwise move forward
	    motorBforward();
	    analogWrite(motorB_EN, actual_PWM); // Send PWM signal to motor B
	}
}

void MotorDriver::motorAforward() {
  digitalWrite(motorA_In1, LOW);
  digitalWrite(motorA_In2, HIGH);
}

void MotorDriver::motorAbackward() {
  digitalWrite(motorA_In1, HIGH);
  digitalWrite(motorA_In2, LOW);
}

void MotorDriver::motorBforward() {
  digitalWrite(motorB_In3, LOW);
  digitalWrite(motorB_In4, HIGH);
}

void MotorDriver::motorBbackward() {
  digitalWrite(motorB_In3, HIGH);
  digitalWrite(motorB_In4, LOW);
}
