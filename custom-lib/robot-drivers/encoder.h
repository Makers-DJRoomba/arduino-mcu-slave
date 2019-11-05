#ifndef ENCODER_H
#define ENCODER_H

/* Rotary Encoders */
class Encoder {
  public:
    Encoder(const int pin); 
    int getEncoderVal();

  private:
    // helper functions/variables if necessary
};

#endif