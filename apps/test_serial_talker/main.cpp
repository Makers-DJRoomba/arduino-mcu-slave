/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"
#include <string.h>
#include <test-lib/blink_test.h>
#include <robot-drivers/robot_drivers.h>

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Initialize C library
extern "C" void __libc_init_array(void);

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
  init();

  __libc_init_array();

  initVariant();

  delay(1);

#if defined(USE_TINYUSB)
  Adafruit_TinyUSB_Core_init();
#elif defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif

  // in1, in2, in3, in4, enA, enB, duty cycle
  MotorDriver md = MotorDriver(11, 10, 9, 6, 12, 5, 100);
  // SerialTalker st(9600);
  Serial.begin(9600);
  //setup();

  // 0 = stop
  // 1 = left
  // 2 = right
  // 3 = forward
  // 4 = backward
  // MotorA = right, MotorB = left
  // note: right motor wiring is flipped

  char buf[3] = {' ',' ',' '};


  int integerValue=0;
  bool negativeNumber=false; // track if number is negative
  char incomingByte;

  for (;;)
  {
    // std::size_t bytes_read = st.readInt(buf, 3);

    // int cmd = atoi(buf);

    if (Serial.available() > 0) {   // something came across serial
      integerValue = 0;         // throw away previous integerValue
      negativeNumber = false;  // reset for negative
      while(1) {            // force into a loop until 'n' is received
        incomingByte = Serial.read();
        if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
        if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
        if (incomingByte == '-') {
          negativeNumber=true;
          continue;
        }
        integerValue *= 10;  // shift left 1 decimal place
        // convert ASCII to integer, add, and shift left 1 decimal place
        integerValue = ((incomingByte - 48) + integerValue);
      }
      if (negativeNumber)
        integerValue = -integerValue;
      Serial.println(integerValue);   // Do something with the value
    }

    // st.send(buf);

    yield(); // yield run usb background task

    if (serialEventRun) serialEventRun();
  }

  return 0;
}
