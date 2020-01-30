#ifndef SERIAL_TALKER_H
#define SERIAL_TALKER_H

#include <utility>

class SerialTalker {
  public:
    SerialTalker(int baud_rate);
    ~SerialTalker();
    template<typename T> std::size_t write(T data);
    std::size_t available();
    std::pair<int, int> readMotorSpeeds();
};

template<typename T>
std::size_t SerialTalker::write(T data) { return Serial.println(data); }

#endif // SERIAL_TALKER_H