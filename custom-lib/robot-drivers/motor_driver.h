#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

/* L298N Motor Driver 
 * Specifically used for driving 2 motors and not just one.
 */
class MotorDriver {
  public:
    MotorDriver(const int motorA_In1, const int motorA_In2, 
                const int motorB_In3, const int motorB_In4, 
                int baseSpeed=0); // can change baseSpeed to real value once we know how it is calculated
    void driveMotorA(const int motorA_In1, const int motorA_In2, int speed);
    void driveMotorA(const int motorA_In1, const int motorA_In2);
    void driveMotorB(const int motorB_In3, const int motorB_In4, int speed);
    void driveMotorB(const int motorB_In3, const int motorB_In4);

  private:
    const int motorA_EN;
    const int motorB_EN;
    int motorA_speed;
    int motorB_speed;

    // return value from 0-255 for analogWrite(), which is used for PWM
    int speedToAnalogVal(int speed);
}

#endif