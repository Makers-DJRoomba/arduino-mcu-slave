#include "Arduino.h"
#include "encoder.h"
#include "constants.h"

// https://www.electroschematics.com/arduino-optical-position-rotary-encoder/
// http://www.ekt2.com/pdf/412_CH_SMART_SHAFT_ENCODER_KIT.pdf

typedef void (*DiffFuncPtr)();
typedef void (*TimeFuncPtr)(void *);
Encoder::Encoder(const int pin)
  : _pin(pin), _last_tick(xTaskGetTickCount()) {

  auto cbTimeOut  = [this](){ cbEncoderTimeOut(this); };
  auto cbTickDiff = [this](){ cbUpdateTickDiff(this); };

  _encoderTimer = xTimerCreate ( /* Just a text name, not used by the RTOS
                     kernel. */
                     "Timer",
                     /* The timer period in ticks, must be
                     greater than 0. */
                     0.2 * configTICK_RATE_HZ,
                     /* The timer will auto-reload themselves
                     when they expire. */
                     pdTRUE,
                     /* The ID is used to store a count of the
                     number of times the timer has expired, which
                     is initialised to 0. */
                     ( void * ) 0,
                     /* Each timer calls the same callback when
                     it expires. */
                     (TimeFuncPtr)&cbTimeOut
                   );

  pinMode(_pin, INPUT);

  attachInterrupt(_pin, (DiffFuncPtr)&cbTickDiff, RISING);
  xTimerStart(_encoderTimer, 10);  
}

Encoder::~Encoder() {
  detachInterrupt(_pin);
  xTimerStop(_encoderTimer, 10);
}

float Encoder::getSpeed() {
  float time_elapsed = _tick_diff / configTICK_RATE_HZ; // seconds per slit

  // formula = (NumTicks*DistancePerClick)/elapsed_time
  // units: (tick distance)/s
  if(time_elapsed > 0)
    return DistancePerSlit / time_elapsed;
  else
    return 0;
}

void Encoder::_updateTickDiff() {
  xTimerReset(_encoderTimer, 10);
  portTickType new_tick = xTaskGetTickCountFromISR();
  _tick_diff = new_tick - _last_tick;
  _last_tick = new_tick;
}

void Encoder::_encoderTimeOut(){
  _tick_diff = 0;
}

void cbUpdateTickDiff(Encoder* srcEncoder) {
  srcEncoder->_updateTickDiff();
}

void cbEncoderTimeOut(Encoder* srcEncoder){
  srcEncoder->_encoderTimeOut();
}
