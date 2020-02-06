#include "Arduino.h"
#include "serial_talker.h"

// https://www.baldengineer.com/arduino-multi-digit-integers.html
SerialTalker::SerialTalker(int baud_rate) { Serial.begin(baud_rate); }
SerialTalker::~SerialTalker() { Serial.end(); }

std::size_t SerialTalker::available() { return Serial.available(); }

/* Receives serial data in the following format:
 * 
 *            "int1,int2\n"
 *
 * Will terminate read once the '\n' character has been found. 
 * Int pair is separated by a comma and may be positive or negative. 
 * 
 * Returns a std::pair object where both elements are ints.
 * pair.first  = left wheel speed
 * pair.second = right wheel speed
 */
std::pair<int, int> SerialTalker::readMotorSpeeds() {
  int final_int  = 0;
  int first_int  = 0; 
  int second_int = 0;
  bool negative  = false;
  char recvd_byte;

  // loop until '\n' is received
  while(1) {
    recvd_byte = Serial.read();

    if (recvd_byte == -1) continue;  // if no characters are in the buffer read() returns -1
    if (recvd_byte == '\n') {        // done receiving all ints, exit while loop
      if (negative)
        final_int = -final_int;
      second_int = final_int;
      break;
    }
    if (recvd_byte == '-') {
      negative = true;
      continue;
    }
    if (recvd_byte == ',') {         // finished receiving first int in message
      if (negative)
        final_int = -final_int;
      first_int = final_int;
      final_int = 0;
      negative  = false;
      continue;
    }
    final_int *= 10;  // shift left 1 decimal place

    // convert from ASCII to integer, add, and shift left 1 decimal place
    final_int = ((recvd_byte - 48) + final_int);
  }

  return std::make_pair(first_int, second_int);
}
