#include "Arduino.h"
#include "serial_talker.h"

// https://www.baldengineer.com/arduino-multi-digit-integers.html
SerialTalker::SerialTalker(int baud_rate) { Serial.begin(baud_rate); }
SerialTalker::~SerialTalker() { Serial.end(); }

int SerialTalker::readInt(char* buf, int len) {
  int sign = 1;
  char first_byte;

  while (!Serial.available()) {} // wait to receive data

  first_byte = Serial.read();
  if (first_byte == -1)
    return -1;
  else if (first_byte == '-')
    sign = -1;

  std::size_t bytes_read = Serial.readBytesUntil('\n', buf, len);

  return sign*atoi(buf);
}
