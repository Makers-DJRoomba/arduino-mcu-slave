#define enA 9                        //Motor A enable                       
#define in1 4                        //Motor A directional pin
#define in2 5                        //Motor A directional pin
#define enB 10                       //Motor B enable
#define in3 6                        //Motor B directional pin
#define in4 7                        //Motor B directional pin

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  //setting motorspeed to 0 on either pin will cause no movement and allow boombot to turn/rotate
  //motorspeed value is PWM from 0 to 255, 0 is no speed and 255 is full speed
  move_boombot_forward(motorSpeedA, motorSpeedB) {
    Motor_A_forward();
    Motor_B_forward();
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  }

  move_boombot_backward(motorSpeedA, motorSpeedB) {
    Motor_A_backward();
    Motor_B_backward();
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  }
  

}


// Seperate Functions
void Motor_A_forward(void) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void Motor_A_backward(void) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void Motor_B_forward(void) {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Motor_B_backward(void) {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
