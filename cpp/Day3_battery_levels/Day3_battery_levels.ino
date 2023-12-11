#include <Arduino.h>

const int CABIN_LIGHTS_PIN = 12;
const int CABIN_SWITCH_PIN = 2;

void setup() {
	pinMode(CABIN_LIGHTS_PIN, OUTPUT);
	pinMode(CABIN_SWITCH_PIN, INPUT);
}

void loop() {
	digitalWrite(CABIN_LIGHTS_PIN, digitalRead(CABIN_SWITCH_PIN));
}