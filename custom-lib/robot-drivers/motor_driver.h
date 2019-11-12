#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

/* L298N Motor Driver 
 * Specifically used for driving 2 motors and not just one.
 */
class MotorDriver {
  public:
    MotorDriver(const int in1, const int in2, const int in3, const int in4, 
                const int enA, const int enB, int duty_cycle=0);
    void driveMotorA(int percent_duty_cycle);
    void driveMotorA();
    void driveMotorB(int percent_duty_cycle);
    void driveMotorB();

  private:
    // Pins: can later define as macros once we know what the feather m4 pinouts will be
    const int _motorA_EN;
    const int _motorB_EN;
    const int _motorA_in1;
    const int _motorA_in2;
    const int _motorB_in3;
    const int _motorB_in4;

    int _base_duty_cycle;

    int toAnalogValue(int percent_duty_cycle);
    void motorAforward();
    void motorAbackward();
    void motorBforward();
    void motorBbackward();
};

#endif