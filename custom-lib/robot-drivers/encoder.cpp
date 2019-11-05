#include "Arduino.h"
#include "encoder.h"

// https://www.electroschematics.com/arduino-optical-position-rotary-encoder/
// http://www.ekt2.com/pdf/412_CH_SMART_SHAFT_ENCODER_KIT.pdf
Encoder::Encoder(const int pin) {
  pinMode(pin, INPUT);
  attachInterrupt(pin, [&_revolutions](){ _revolutions++; }, RISING);
}

int Encoder::getEncoderVal() {
  // do some work here to make sure value safe
  // and do any necessary calculations
  return _revolutions;
}