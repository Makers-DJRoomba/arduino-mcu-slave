#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

/* L298N Motor Driver 
 * Specifically used for driving 2 motors and not just one.
 */
class MotorDriver {
  public:
    MotorDriver(const int In1, const int In2, 
                const int In3, const int In4, const int enA, const int enB,
                int baseDutyCycle=0); // can change baseSpeed to real value once we know how it is calculated
    void driveMotorA(int percentDutyCycle);
    void driveMotorA();
    void driveMotorB(int percentDutyCycle);
    void driveMotorB();

  private:
    // Pins: can later define as macros once we know what the feather m4 pinouts will be
    const int motorA_EN;
    const int motorB_EN;
    const int motorA_In1;
    const int motorA_In2;
    const int motorB_In3;
    const int motorB_In4;

    int baseDutyCycle;
    
    void motorAforward();
    void motorAbackward();
    void motorBforward();
    void motorBbackward();

    // add any other variables/helper functions you may need
};

#endif