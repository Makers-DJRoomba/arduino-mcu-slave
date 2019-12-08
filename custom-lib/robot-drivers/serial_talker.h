#ifndef SERIAL_TALKER_H
#define SERIAL_TALKER_H

class SerialTalker {
  public:
    SerialTalker(int baud_rate);
    ~SerialTalker();
    // template<typename T> 
    std::size_t send(int data);
    std::size_t read(char* buf);
};

#endif // SERIAL_TALKER_H