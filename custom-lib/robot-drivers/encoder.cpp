#include "Arduino.h"
#include "encoder.h"
#include "constants.h"

// https://www.electroschematics.com/arduino-optical-position-rotary-encoder/
// http://www.ekt2.com/pdf/412_CH_SMART_SHAFT_ENCODER_KIT.pdf
Encoder::Encoder(const int pin)
  : _pin(pin) {
  pinMode(_pin, INPUT);
  attachInterrupt(_pin, timePerTick, RISING);

  // maybe can do this way and get rid of extra function
  // attachInterrupt(_pin, [this]() { _old_time = _time; _time = millis(); }, RISING);
}

Encoder::~Encoder() {
  _ticks = 0;
  detachInterrupt(_pin);
}

float Encoder::getSpeed() {
  // formula = (NumTicks*DistancePerClick)/elapsed_time
  // assume 1 tick passed between each interrupt
  // units: (tick distance)/s
  return DistancePerClick/(_time / 1000.0f - _old_time / 1000.0f);
}

static void timePerTick() {
  _old_time = _time;  
  _time     = millis();
}
