#include "Arduino.h"
#include "serial_talker.h"

SerialTalker::SerialTalker(int baud_rate) { Serial.begin(baud_rate); }
SerialTalker::~SerialTalker() { Serial.end(); }

// template<typename T>
std::size_t SerialTalker::send(int data) {
  if (Serial.available() > 0) {
    return Serial.println(data);
  }
  return 0;
}

std::size_t SerialTalker::read(char* buf) {
  char data;
  int i = 0;

  while (data != '\n') {
    if (Serial.available() > 0) {
      // return Serial.readBytesUntil('\n', buf, len);
      data = Serial.read();
      buf[i] = data;
      i++;
    }
  }

  return 0;
}
