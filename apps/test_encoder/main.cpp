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
#include <robot-drivers/encoder.h>
#include <test-lib/blink_test.h>
#include <FreeRTOS_SAMD21.h> //samd21

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Initialize C library
extern "C" void __libc_init_array(void);

TaskHandle_t Handle_aTask;

static void threadA( void *pvParameters ) 
{
  Encoder* encoder = (Encoder *) pvParameters;
  portTickType tick_diff = 0;
  pinMode(13, OUTPUT);
  float speed = 0;
  // delete ourselves.
  Serial.println("Thread A: STARTING");
  for(;;){
    //loop();
    digitalWrite(13, HIGH);
    vTaskDelay(500);
    digitalWrite(13, LOW);
    vTaskDelay(500);
    tick_diff = encoder->getTickDiff();
    // speed = encoder->getSpeed();
    //if (serialEventRun) serialEventRun();
    yield(); // yield run usb background task
    if (serialEventRun) serialEventRun();
  }
}
  

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
  
  Encoder encoder = Encoder(4);
  Serial.begin(115200);

  vNopDelayMS(500); // prevents usb driver crash on startup, do not omit this
  while (!Serial) ;  // Wait for Serial terminal to open port before starting program

  Serial.printf("Pin Interrupt Handle: %d\n", encoder.getPinIntHandle());
  Serial.printf("Timer Handle: %p\n", encoder.getTimerHandle());

  Serial.println("");
  Serial.println("******************************");
  Serial.println("        Program start         ");
  Serial.println("******************************");
  xTaskCreate(threadA,     "Task A",       512, (void *) &encoder, tskIDLE_PRIORITY + 1, &Handle_aTask);
  Serial.println("Starting task scheduler");
  vTaskStartScheduler();
  for (;;);

  return 0;
}
