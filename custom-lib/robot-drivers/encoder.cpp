#include "Arduino.h"
#undef max
#undef min
#include "encoder.h"
#include "constants.h"

void cbUpdateTickDiff(uint32_t pinHandle) {
  Encoder* targetEncoder = pinHandleRegister[pinHandle];
  if(targetEncoder != NULL){
    targetEncoder->_updateTickDiff();
  }
}

void cbEncoderTimeOut(TimerHandle_t timerHandle){
  Encoder* targetEncoder = timerHandleRegister[timerHandle];
  if(targetEncoder != NULL){
    targetEncoder->_encoderTimeOut();
  }
}


// https://www.electroschematics.com/arduino-optical-position-rotary-encoder/
// http://www.ekt2.com/pdf/412_CH_SMART_SHAFT_ENCODER_KIT.pdf

Encoder::Encoder(const int pin)
  : _pin(pin), _last_tick(xTaskGetTickCount()) {

  _timerHandle = xTimerCreate ( /* Just a text name, not used by the RTOS
                     kernel. */
                     "Timer",
                     /* The timer period in ticks, must be
                     greater than 0. */
                     0.3 * configTICK_RATE_HZ,
                     /* The timer will auto-reload themselves
                     when they expire. */
                     pdTRUE,
                     /* The ID is used to store a count of the
                     number of times the timer has expired, which
                     is initialised to 0. */
                     ( void * ) 0,
                     /* Each timer calls the same callback when
                     it expires. */
                     (TimerCallbackFunction_t) &cbEncoderTimeOut
                   );

  pinMode(_pin, INPUT);

  _pinIntHandle = attachInterrupt(_pin, (voidFuncPtr) &cbUpdateTickDiff, RISING);
  
  registerTimerHandle(_timerHandle);
  registerPinIntHandle(_pinIntHandle);

  xTimerStart(_timerHandle, 0);  
}

Encoder::~Encoder() {
  detachInterrupt(_pin);
  xTimerStop(_timerHandle, 0);
  unregisterTimerHandle(_timerHandle);
  unregisterPinIntHandle(_pinIntHandle);
}

TimerHandle_t Encoder::getTimerHandle(){
  return _timerHandle;
}

uint32_t Encoder::getPinIntHandle(){
  return _pinIntHandle;
}

TickType_t Encoder::getTickDiff() {
  return _tick_diff;
}

float Encoder::getSpeed() {
  float time_elapsed = ((float)_tick_diff) / configTICK_RATE_HZ; // seconds per slit

  // formula = (NumTicks*DistancePerClick)/elapsed_time
  // units: (tick distance)/s
  if(time_elapsed > 0)
    return DistancePerSlit / time_elapsed;
  else
    return 0;
}

void Encoder::_updateTickDiff() {
  xTimerReset(_timerHandle, 0);
  portTickType new_tick = xTaskGetTickCountFromISR();
  _tick_diff = new_tick - _last_tick;
  _last_tick = new_tick;
}

void Encoder::_encoderTimeOut(){
  _tick_diff = 0;
  _last_tick = xTaskGetTickCountFromISR();
}

void Encoder::registerTimerHandle(TimerHandle_t handle){
  timerHandleRegister[handle] = this;
}

void Encoder::registerPinIntHandle(uint32_t handle){
  pinHandleRegister[handle] = this;
}

void Encoder::unregisterTimerHandle(TimerHandle_t handle){
  timerHandleRegister[handle] = NULL;
}

void Encoder::unregisterPinIntHandle(uint32_t handle){
  pinHandleRegister[handle] = NULL;
}