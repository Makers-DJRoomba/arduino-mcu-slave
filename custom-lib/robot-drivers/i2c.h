#ifndef I2C_H
#define I2C_H

/* Wrapper class of I2S library for samd-core */
// may not be necessary, but we can see if this will help
class I2C {
  public:
    I2C(const int pin); 
    void begin(); // initialize communication with pi/vice versa
    void end();

    // look into how we can make it easy to read/write commands
    // i.e. read raw byte command in function and return action,
    // such as "turn left" or something similar, which is also
    // easily interpreted

  private:
    // helper functions/variables if necessary
}

#endif