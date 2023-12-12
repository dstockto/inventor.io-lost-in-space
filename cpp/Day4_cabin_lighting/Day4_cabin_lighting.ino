#include <Arduino.h>

const int CABIN_SWITCH_PIN = 2;

const int STORAGE_SWITCH_PIN = 3;

const int COCKPIT_SWITCH_PIN = 4;

const int CABIN_LIGHTS_PIN = 10;

const int STORAGE_LIGHTS_PIN = 11;

const int COCKPIT_LIGHTS_PIN = 12;

void setup()
{
	pinMode(STORAGE_SWITCH_PIN, INPUT);
	pinMode(COCKPIT_SWITCH_PIN, INPUT);
	pinMode(CABIN_SWITCH_PIN, INPUT);

	pinMode(STORAGE_LIGHTS_PIN, OUTPUT);
	pinMode(COCKPIT_LIGHTS_PIN, OUTPUT);
	pinMode(CABIN_LIGHTS_PIN, OUTPUT);
}

void loop()
{
	digitalWrite(STORAGE_LIGHTS_PIN, digitalRead(STORAGE_SWITCH_PIN));
	digitalWrite(COCKPIT_LIGHTS_PIN, digitalRead(COCKPIT_SWITCH_PIN));
	digitalWrite(CABIN_LIGHTS_PIN, digitalRead(CABIN_SWITCH_PIN));
}
