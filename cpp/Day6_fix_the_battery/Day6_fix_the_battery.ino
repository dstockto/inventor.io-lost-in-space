// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_PIN = A0;  // we pick an analog pin (defined in Arduino.h)

// These two constants set the minimum and maximum delay times for oue blinking LED
// The type "unsigned int" represents numbers from 0 to 65535.  Another name you may
// see for this type is "uint16_t".  We need this since these delay values can be
// greater than the biggest number a byte can represent (255).
const unsigned int MIN_DELAY = 50;   // 50 ms shortest blink delay
const unsigned int MAX_DELAY = 500;  // 500 ms longest blink delay

// One time setup
void setup() {
	// We will blink our build in LED based on amount of light received from our photoresistor
	pinMode(LED_BUILTIN, OUTPUT);       // output since we will control the built in LED
	pinMode(PHOTORESISTOR_PIN, INPUT);  // input value from analog pin connected to photoresistor

	Serial.begin(115200);  // This initializes the Serial Monitor and sets the speed to 9600 bits per second
}

// The loop() function is called over and over when sketch is run.
void loop() {
	unsigned int light_value = analogRead(PHOTORESISTOR_PIN);   // light value from 0 to 1024
	Serial.print("Light value: ");  // Display label string to serial monitor
	Serial.print(light_value);      // display the value read from our photoresistor

	static unsigned int darkest_light = light_value;    // this is the lowest value returned by the photoresistor
	static unsigned int brightest_light = light_value;  // this is the highest value returned by the photoresistor

	if (light_value < darkest_light) {  // If value is LESS THAN ('<') the darkest...
		darkest_light = light_value;      // ...then save current value as our new darkest value
	}
	if (light_value > brightest_light) {  // If value is GREATER THAN ('>') the brightest...
		brightest_light = light_value;      // ...then save current value as our new brightest value
	}

	unsigned int delay_value = map(light_value, darkest_light, brightest_light, MAX_DELAY, MIN_DELAY);
	Serial.print(", Delay value: ");  // display label after light_value
	Serial.println(delay_value);      // display delay_value returned by map() function with newline

	digitalWrite(LED_BUILTIN, HIGH);  // Turn on LED
	delay(delay_value);               // Leave on delay_value milliseconds
	digitalWrite(LED_BUILTIN, LOW);   // Turn off LED
	delay(delay_value);               // Leave off delay_value milliseconds
}