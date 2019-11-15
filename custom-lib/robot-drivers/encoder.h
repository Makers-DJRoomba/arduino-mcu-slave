#ifndef ENCODER_H
#define ENCODER_H

/* Rotary Encoders */
class Encoder {
  public:
    Encoder(const int pin);
    ~Encoder(); 
    float updateSpeed();

  private:
    static void updateTickDiff()
    portTickType _last_tick;
    portTickType _tick_diff;
    const int _pin;
  };

#endif