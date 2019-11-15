#include "Arduino.h"
#include "encoder.h"
#include "constants.h"
#include <FreeRTOS_SAMD21.h>

// https://www.electroschematics.com/arduino-optical-position-rotary-encoder/
// http://www.ekt2.com/pdf/412_CH_SMART_SHAFT_ENCODER_KIT.pdf
Encoder::Encoder(const int pin)
  : _pin(pin), _last_tick(xTaskGetTickCount()) {
  pinMode(_pin, INPUT);
  attachInterrupt(_pin, updateTickDiff, RISING);

  //TODO: Implement timer for timing out when robot isn't moving
}

Encoder::~Encoder() {
  detachInterrupt(_pin);
}

float Encoder::getSpeed() {
  float time_elapsed = _tick_diff / configTICK_RATE_HZ; // seconds per slit

  // formula = (NumTicks*DistancePerClick)/elapsed_time
  // units: (tick distance)/s
  if(_time_elapsed > 0)
    return DistancePerSlit / _time_elapsed;
  else
    return -1;
}

static void updateTickDiff() {
  portTickType new_tick = xTaskGetTickCountFromISR();
  tick_diff = new_tick - _last_tick;
  _last_tick = new_tick;
}
