#ifndef SERIAL_TALKER_H
#define SERIAL_TALKER_H

class SerialTalker {
  public:
    SerialTalker(int baud_rate);
    ~SerialTalker();
    template<typename T> std::size_t send(T data);
    int readInt(char* buf, int len);
};

template<typename T>
std::size_t SerialTalker::send(T data) {
  if (Serial.available() > 0) {
    return Serial.println(data);
  }
  return 0;
}

#endif // SERIAL_TALKER_H