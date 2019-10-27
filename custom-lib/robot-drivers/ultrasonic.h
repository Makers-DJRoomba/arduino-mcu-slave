#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class UltrasonicRanger {
  public:
    UltrasonicRanger(const int pin); 
    int getDistance();

  private:
    // helper functions/variables if necessary
}

#endif