#include "Arduino.h"
#include "serial_talker.h"

// https://www.baldengineer.com/arduino-multi-digit-integers.html
SerialTalker::SerialTalker(int baud_rate) { Serial.begin(baud_rate); }
SerialTalker::~SerialTalker() { Serial.end(); }

std::size_t SerialTalker::read(char* buf, int len) {
  while (!Serial.available()) {} // wait to receive data
  std::size_t bytes_read = Serial.readBytesUntil('\n', buf, len);

  return bytes_read;
}
