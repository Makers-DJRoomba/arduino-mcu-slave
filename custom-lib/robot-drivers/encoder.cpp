#include "Arduino.h"
#include "encoder.h"

#include <FreeRTOS_SAMD21.h>

// https://www.electroschematics.com/arduino-optical-position-rotary-encoder/
// http://www.ekt2.com/pdf/412_CH_SMART_SHAFT_ENCODER_KIT.pdf
Encoder::Encoder(const int pin) {
  pinMode(pin, INPUT);

  static int arg = pin;

  xTaskCreate(increment,          // task function
              "Poll Encoder",     // ID string
              128,                // stack size
              &arg,               // parameters
              DEFAULT_PRIORITY,   // priority 
              &increment_Task);   // function handle

  // create semaphore for accessing tick value
  tick_Semaphore = xSemaphoreCreateMutex();

  // could do it this way with an interrupt instead
  // attachInterrupt(pin, [&_ticks](){ _ticks++; }, RISING);
}

Encoder::~Encoder() {
  if (increment_Task != NULL)
    vTaskDelete(increment_Task);
  vSemaphoreDelete(tick_Semaphore);
  _ticks = 0;
}

int Encoder::getValue() {
  if (tick_Semaphore != NULL) {

    // will block until _ticks can be returned, 
    // otherwise there is an error returned using -1
    if (xSemaphoreTake(tick_Semaphore, portMAX_DELAY) == pdTRUE) {
      return _ticks;
      xSemaphoreGive(tick_Semaphore);
    } else {
      return -1;
    }
  }
}

static void Encoder::increment(void* pin) {
  int pin = *(int*)pin; 
  int pin_state = 0;
  int old_pin_state = 0;

  for (;;) {
    pin_state = digitalRead(pin);

    // increment on low to high transition
    if ((old_pin_state == LOW) && (pin_state == HIGH)) {
      if (tick_Semaphore != NULL) {

        // if semaphore not locked, increment _ticks and give back lock
        if (xSemaphoreTake(tick_Semaphore, portMAX_DELAY) == pdTRUE) {
          _ticks++;
          xSemaphoreGive(tick_Semaphore);
        }
      }
    }

    old_pin_state = pin_state;
  }
}




