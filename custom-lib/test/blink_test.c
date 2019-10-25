#include "blink_test.h"

void blink(int delay_ms){
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
    delay(delay_ms);
    digitalWrite(13, LOW);
    delay(delay_ms);
}