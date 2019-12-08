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
#include <robot-drivers/serial_talker.h>
#include <robot-drivers/motor_driver.h>

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

  // SerialTalker me(9600);

  // in1, in2, in3, in4, enA, enB, duty cycle
  MotorDriver md = MotorDriver(11, 10, 9, 6, 12, 5, 100);
  Serial.begin(9600);

  // make it go forward
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  //setup();

  // 0 = stop
  // 1 = left
  // 2 = right
  // 3 = forward
  // 4 = backward


  // MotorA = right, MotorB = left
  // right motor is flipped

  for (;;)
  {

    if (Serial.available() > 0) {
      char data = Serial.read();

      int cmd = data - '0';
      switch (cmd) {
        case 0:
          // stop
          md.driveMotorA(0);
          md.driveMotorB(0);
          break;

        case 1:
          // left
          md.driveMotorA(100);
          md.driveMotorB(0);
          break;

        case 2:
          // right
          md.driveMotorA(0);
          md.driveMotorB(100);
          break;

        case 3:
          // forward
          md.driveMotorA(100);
          md.driveMotorB(100);
          break;

        case 4:
          // backward
          md.driveMotorA(-100);
          md.driveMotorB(-100);
          break;
      }

      Serial.println(data);
    }
    // analogWrite(12, 255);

    // md.driveMotorA(100);
    // md.driveMotorB(100);

    // Serial.println("yum yum data taste good. I read ur bad code. Fuck haha profanity");

    // me.read(recv_buf);
    // me.send(recv_buf[0] - '0');

    delay(1000);

    yield(); // yield run usb background task

    if (serialEventRun) serialEventRun();
  }

  return 0;
}
