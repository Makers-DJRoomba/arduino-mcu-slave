#include "Arduino.h"
#include "encoder.h"
#include "constants.h"

// https://www.electroschematics.com/arduino-optical-position-rotary-encoder/
// http://www.ekt2.com/pdf/412_CH_SMART_SHAFT_ENCODER_KIT.pdf
Encoder::Encoder(const int pin)
  : _pin(pin), _old_time(millis()) {
  pinMode(_pin, INPUT);
  attachInterrupt(_pin, countTick, RISING);

  // maybe can do this way and get rid of extra function
  // attachInterrupt(_pin, [&_ticks]() { _ticks++; }, RISING);
}

Encoder::~Encoder() {
  _ticks = 0;
  detachInterrupt(_pin);
}

float Encoder::getSpeed() {
  unsigned long time = millis();

  // calculate number of ticks counted since last measure
  int tick_interval           = _ticks - _old_ticks;
  unsigned long time_interval = time - _old_time;
  
  // save current values as "old" values for next iteration
  _old_ticks = _ticks;
  _old_time  = time;

  // formula = (NumTicks*DistancePerClick)/elapsed_time
  // units: (tick distance)/s
  return tick_interval*DistancePerClick/(time_interval/1000.0f);
}

static void countTick() {
  _ticks++;
}
