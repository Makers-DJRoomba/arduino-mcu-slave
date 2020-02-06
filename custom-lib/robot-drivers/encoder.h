#ifndef ENCODER_H
#define ENCODER_H
#include <FreeRTOS_SAMD21.h>
#undef max
#undef min
#include <unordered_map>


/* Rotary Encoders */
class Encoder {

  public:
    Encoder(const int pin);
    ~Encoder(); 
    float getSpeed();
    void _updateTickDiff();
    void _encoderTimeOut();
    void registerTimerHandle(TimerHandle_t);
    void registerPinIntHandle(uint32_t);
    void unregisterTimerHandle(TimerHandle_t);
    void unregisterPinIntHandle(uint32_t);
    uint32_t getPinIntHandle();
    TimerHandle_t getTimerHandle();
    TickType_t getTickDiff();
  private:
    portTickType _last_tick = 0;
    portTickType _tick_diff = 0;
    TimerHandle_t _timerHandle;
    uint32_t _pinIntHandle;
    const int _pin;
  };

static std::unordered_map<TimerHandle_t, Encoder*> timerHandleRegister;
static std::unordered_map<uint32_t, Encoder*> pinHandleRegister;

void cbUpdateTickDiff(uint32_t pinHandle);
void cbEncoderTimeOut(TimerHandle_t timerHandle);

#endif