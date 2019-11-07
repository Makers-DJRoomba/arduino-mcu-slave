#ifndef ENCODER_H
#define ENCODER_H

/* Rotary Encoders */
class Encoder {
  public:
    Encoder(const int pin);
    ~Encoder(); 
    float getSpeed();

  private:
    static void countTick();
    static int _ticks = 0;
    int _old_ticks = 0;
    unsigned long _old_time;
    const int _pin;
  };

#endif