#include "rtos_blink_test.h"

void blink(int delay_ms){
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
    vTaskDelay(delay_ms);
    digitalWrite(13, LOW);
    vTaskDelay(delay_ms);
}