#ifndef ENCODER_H
#define ENCODER_H
#include <FreeRTOS_SAMD21.h>

/* Rotary Encoders */
class Encoder {
  public:
    Encoder(const int pin);
    ~Encoder(); 
    float getSpeed();
    void _updateTickDiff();
    void _encoderTimeOut();

  private:
    TimerHandle_t _encoderTimer;
    portTickType _last_tick;
    portTickType _tick_diff;
    const int _pin;
  };

static void cbUpdateTickDiff(Encoder* srcEncoder);
static void cbEncoderTimeOut(Encoder* srcEncoder);

#endif