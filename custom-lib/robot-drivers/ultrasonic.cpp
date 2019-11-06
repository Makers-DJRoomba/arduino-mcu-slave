#include "Arduino.h"
#include "ultrasonic.h"

#include <FreeRTOS_SAMD21.h>

// https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
UltrasonicRanger::UltrasonicRanger(const int trig_pin,
                                   const int echo_pin) {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Params = {trig_pin, echo_pin};

  xTaskCreate(pulseOut,           // task function
              "Continous Pulses", // ID string
              128,                // stack alloced to task
              &params,            // parameters to task function
              PRIORITY_HERE,      // priority
              &pulse_Task);       // task handle name

  duration_Mutex = xSemaphoreCreateMutex();
}

UltrasonicRanger::~UltrasonicRanger() {
  if (pulse_Task != NULL)
    vTaskDelete(pulse_Task);
  vSemaphoreDelete(duration_Mutex);
}

unsigned long UltrasonicRanger::getDistance() {
  unsigned long distance = 0;

  if (duration_Mutex != NULL) {
    if (xSemaphoreTake(duration_Mutex, portMAX_DELAY) == pdTRUE) {
      distance = SpeedOfSound_cm_us * _duration/2; // define speed of sound
      xSemaphoreGive(duration_Mutex);
    }
  }

  return distance;
}

void UltrasonicRanger::init() {
  vTaskStartScheduler();
}

static void UltrasonicRanger::pulseOut(void* Params) {
  int trig_pin = ((taskParameter*)Params)->trig_pin;
  int echo_pin = ((taskParameter*)Params)->echo_pin;

  _duration = 0;

  for (;;) {
    // sensor triggered by 10 second high pulse
    digitalWrite( ((taskParameter*)Params)->trig_pin, HIGH );
    delayMicroseconds(10);
    digitalWrite( ((taskParameter*)Params)->trig_pin, LOW );

    // if _duration variable not locked, then write to it
    // will block until variable acquired
    if (duration_Mutex != NULL) {
      if (xSemaphoreTake(duration_Mutex, portMAX_DELAY) == pdTRUE) {
    
        // measure time between pulses in microseconds
        _duration = pulseIn( ((taskParameter*)Params)->echo_pin, HIGH );
        xSemaphoreGive(duration_Mutex);
      }
    }

    // delay of 50ms in between readings
    delay(50);
  }
}

