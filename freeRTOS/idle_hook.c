
#include <FreeRTOS.h>
//#include <Arduino.h>

void  __attribute__((weak)) vApplicationIdleHook( void ) 
{
    // Optional commands, can comment/uncomment below
    //SERIAL.print("."); //print out dots in terminal, we only do this when the RTOS is in the idle state
    vNopDelayMS(100);
}
