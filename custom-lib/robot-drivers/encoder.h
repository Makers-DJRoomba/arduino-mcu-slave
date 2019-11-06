#ifndef ENCODER_H
#define ENCODER_H

/* Rotary Encoders */
class Encoder {
  public:
    Encoder(const int pin);
    ~Encoder(); 
    float getSpeed();

  private:
    static void timePerTick();
    static unsigned long _time;
    static unsigned long _old_time;
    const int _pin;
  };

#endif