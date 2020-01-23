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
  SerialTalker st(9600);
  //setup();

  // 0 = stop
  // 1 = left
  // 2 = right
  // 3 = forward
  // 4 = backward
  // MotorA = right, MotorB = left
  // note: right motor wiring is flipped

  char buf[3] = {' ',' ',' '};

  for (;;)
  {
    int cmd = st.readInt(buf, 3);

    st.send(cmd);

    yield(); // yield run usb background task

    if (serialEventRun) serialEventRun();
  }

  return 0;
}
