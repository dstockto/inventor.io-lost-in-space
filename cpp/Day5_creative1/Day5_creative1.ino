#include <Arduino.h>

typedef void (* AnimationFunction)(int);

// Arduino pins connected to the DIP switch - Order is switch 1, 2, 3
int inputPins[] = { 4, 3, 2 };

// Arduino pins connected to a series of LEDs
int outputPins[] = { 13, 12, 11, 10, 9, 8, 7 };
// The initial delay time is used to keep each animation cycle roughly the same regardless of how many LEDs are chosen,
// meaning if you trigger just one LED then it will blink for 230ms, but if there's 7 on, then each will get 30ms.
int initialDelayTime = 210;
int delayTime = 30;  // Delay in milliseconds
int mode = 0;

void animatePins(int value);
void bounce(int value);
void backBounce(int value);
void outIn(int value);
void inOut(int value);

// Using custom type here - it could also be done by using mode with a switch statement, but this way it's possible
// to create another animation function of the same shape and then just add it to the array below.
AnimationFunction animationFunctions[] = { animatePins, bounce, backBounce, outIn, inOut };

int numFunctions = sizeof(animationFunctions)/sizeof(animationFunctions[0]);

int loops = 0;

/**
 * @brief Initializes the input and output pins.
 *
 * This function initializes the pins defined in the inputPins and outputPins arrays.
 * It sets the mode of each input pin to INPUT and each output pin to OUTPUT using the pinMode function.
 *
 * @see inputPins
 * @see outputPins
 * @see pinMode
 */
void setup()
{
	// Initialize input pins
	for (int i = 0; i<sizeof(inputPins)/sizeof(inputPins[0]); i++) {
		pinMode(inputPins[i], INPUT);
	}

	// Initialize output pins
	for (int i = 0; i<sizeof(outputPins)/sizeof(outputPins[0]); i++) {
		pinMode(outputPins[i], OUTPUT);
	}
}


/**
 * \brief Calculates the value of input pins connected to a DIP switch.
 *
 * This function calculates the value of input pins connected to a DIP switch,
 * where each pin represents a binary digit. The pins' values are determined
 * by the state of the corresponding switch. If a switch is turned on (HIGH),
 * the pin's value is added to the total value. The final total value is the
 * sum of the values of all the pins.
 *
 * \return The total value calculated from the input pins.
 *
 * \note This function assumes the inputPins array is properly defined. The
 * inputPins array should contain the Arduino pins connected to the DIP switch
 * in order, starting from switch 1 and going up to switch n.
 */
int calcPins()
{
	int pinVal = 1;
	int total = 0;
	for (int i = 0; i<sizeof(inputPins)/sizeof(inputPins[0]); i++) {
		if (digitalRead(inputPins[i])==HIGH) {
			total += pinVal;
		}
		pinVal *= 2;
	}
	return total;
}

/**
 * @brief Executes the main looping logic for the application.
 *
 * This function calculates the value of the pins using the calcPins function, then based on the
 * calculated value, determines the delay time for the animation. It selects the appropriate
 * AnimationFunction based on the current mode and calls it with the calculated value as the
 * argument. If the calculated value is 0, it adds a short delay and continues to the next loop.
 * Every 10 loops, it increments the mode variable and prints the new mode to the Serial monitor.
 * Finally, it delays for 8 times the calculated delay time before starting the next loop.
 */
void loop()
{
	int value = calcPins();
	if (value!=0) {
		delayTime = initialDelayTime / value;
		AnimationFunction animation = animationFunctions[mode];
		animation(value);
	} else {
		delay(100);
	}

	loops++;
	if (loops%10==0) {
		mode = (mode+1)%5;
		Serial.print("Mode: ");
		Serial.println(mode);
	}
	delay(8*delayTime);
}

/**
 * @brief Animates multiple pins by turning them on and off in sequence.
 *
 * The function takes an integer value as an argument and animates the pins by turning them on and off in sequence.
 * It uses the digitalwrite() function to set the pins to HIGH and LOW states.
 * The pins to be animated are specified by the outputPins[] array.
 *
 * @param value The number of pins to be animated.
 */
void animatePins(int value)
{
	for (int i = 0; i<value; i++) {
		digitalWrite(outputPins[i], HIGH);
		delay(delayTime);
	}

	for (int i = 0; i<value; i++) {
		digitalWrite(outputPins[i], LOW);
		delay(delayTime);
	}
}

/**
 * Bounces a specified number of LEDs connected to Arduino pins.
 *
 * The function turns on the LEDs one by one in a sequence, and then turns them off in reverse order, creating a bouncing effect.
 *
 * @param value The number of LEDs to bounce.
 */
void bounce(int value)
{
	for (int i = 0; i<value; i++) {
		digitalWrite(outputPins[i], HIGH);
		delay(delayTime/2);
	}

	for (int i = value-1; i>=0; i--) {
		digitalWrite(outputPins[i], LOW);
		delay(delayTime/2);
	}
}

/**
 * @brief Bounces the LEDs connected to Arduino pins in a back and forth pattern.
 *
 * This function turns on the LEDs one by one from the specified index to the first LED,
 * and then turns them off in reverse order to create a bouncing effect.
 * The LEDs are controlled using the digitalWrite function.
 *
 * @param value The number of LEDs to bounce.
 */
void backBounce(int value)
{
	for (int i = value-1; i>=0; i--) {
		digitalWrite(outputPins[i], HIGH);
		delay(delayTime/2);
	}

	for (int i = 0; i<value; i++) {
		digitalWrite(outputPins[i], LOW);
		delay(delayTime/2);
	}
}

/**
 * @brief Writes values to outputPins to create an in-out pattern.
 *
 * This function writes values to the outputPins array to create an out->in pattern of
 * turning on and off LEDs connected to Arduino pins. The pattern starts with turning
 * on the outermost LEDs and progressively turns on and off the LEDs towards the center.
 *
 * @param value The number of LEDs to be controlled.
 *
 * @note The outputPins array must be defined before calling this function.
 * @note The delayTime variable must be defined before calling this function.
 *
 * @warning The value parameter must be a positive integer.
 *
 * @see https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
 * @see https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
 */
void outIn(int value)
{
	for (int i = 0; i<value/2+1; i++) {
		int left = i;
		int right = value-i-1;
		digitalWrite(outputPins[left], HIGH);
		digitalWrite(outputPins[right], HIGH);
		delay(2*delayTime);
	}

	for (int i = 0; i<value/2+1; i++) {
		int left = i;
		int right = value-i-1;
		digitalWrite(outputPins[left], LOW);
		digitalWrite(outputPins[right], LOW);
		delay(delayTime);
	}
}

/**
 * @brief Lights up and turns off LEDs in a specific pattern based on the input value.
 *
 * This function lights up and turns off LEDs connected to the Arduino pins in a pattern.
 * The LEDs are lit up and turned off in sequence, starting from the outermost LEDs and moving towards the center.
 * The delay between the LED changes is set by the `delayTime` variable.
 *
 * @param value The number of LEDs to light up and turn off.
 */
void inOut(int value)
{
	for (int i = 0; i<=(value-1)/2; i++) {
		int left = (value-1)/2-i;
		int right = value/2+i;
		digitalWrite(outputPins[left], HIGH);
		digitalWrite(outputPins[right], HIGH);
		delay(delayTime);
	}

	for (int i = 0; i<=(value-1)/2; i++) {
		int left = (value-1)/2-i;
		int right = value/2+i;
		digitalWrite(outputPins[left], LOW);
		digitalWrite(outputPins[right], LOW);
		delay(delayTime);
	}
}
