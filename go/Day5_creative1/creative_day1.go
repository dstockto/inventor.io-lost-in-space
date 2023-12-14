package main

import (
	"machine"
	"time"
)

// inputPins are the Arduino pins that are connected to a DIP switch. They order is in DIP switch
// numbered order - 1, 2, 3
var inputPins = []machine.Pin{
	machine.D4,
	machine.D3,
	machine.D2,
}

// outputPins are the Arduino pins that are connected to LEDs. The order of the pins in the array
// determines the order in which the LEDs are controlled.
var outputPins = []machine.Pin{
	machine.D13,
	machine.D12,
	machine.D11,
	machine.D10,
	machine.D9,
	machine.D8,
	machine.D7,
}
var delay = 25 * time.Millisecond
var mode = 0

// main is the entry point of the program
// It configures the input and output pins,
// defines a list of animation modes,
// continuously loops through the animation modes and performs the animations based on the calculated pin value.
// It also updates the animation mode every 10 loops.
func main() {
	for _, p := range inputPins {
		p.Configure(machine.PinConfig{Mode: machine.PinInput})
	}
	for _, p := range outputPins {
		p.Configure(machine.PinConfig{Mode: machine.PinOutput})
	}

	modes := []func(int){
		animatePins,
		bounce,
		backBounce,
		outIn,
		inOut,
	}

	loops := 0
	for {
		var value int
		value = calcPins()

		animator := modes[mode]
		if value != 0 {
			animator(value)
		} else {
			time.Sleep(100 * time.Millisecond)
		}

		loops++

		if loops%10 == 0 {
			mode = mode + 1
			mode %= len(modes)
			println("Mode: ", mode)
		}
		time.Sleep(8 * delay)
	}
}

// outIn animates the output pins in the "out-in" pattern.
// The function takes an integer value, which determines the number of pins to be animated.
//
// For each iteration, the function turns on the pins symmetrically from both ends,
// with the leftmost and rightmost pins being the first to turn on.
// It then waits for a duration of `2 * delay`.
//
// After that, the function turns off the pins symmetrically from both ends,
// with the leftmost and rightmost pins being the first to turn off.
// It then waits for a duration of `delay`.
func outIn(value int) {
	for i := 0; i < value/2+1; i++ {
		left := i
		right := value - i - 1
		outputPins[left].High()
		outputPins[right].High()
		time.Sleep(delay * 2)
	}

	for i := 0; i < value/2+1; i++ {
		left := i
		right := value - i - 1
		outputPins[left].Low()
		outputPins[right].Low()
		time.Sleep(delay)
	}
}

// inOut is a function that performs an in-out animation on the outputPins based on the value passed as a parameter.
// The in-out animation involves turning on and off the pins from the outer edges towards the center and vice versa.
// The number of pins to animate is determined by the value parameter.
// The animation is achieved by setting the pins to a high state (on) using the High() method, and then delaying for the specified duration.
// The outer pins are turned on first, followed by the inner pins.
// After turning on the pins, a delay is introduced using the time.Sleep() function.
// Then the pins are set to a low state (off) using the Low() method, and another delay is introduced.
// This process is repeated for the specified number of times obtained from (value-1)/2.
//
// Example usage:
//
//	value := 5
//	inOut(value)
//
// The above usage will perform an in-out animation on the outputPins using the first 5 pins in the outputPins list.
// The pins will be turned on and off in a sequential manner, starting from the outermost pins towards the center and vice versa.
func inOut(value int) {
	for i := 0; i <= (value-1)/2; i++ {
		left := (value-1)/2 - i
		right := value/2 + i
		outputPins[left].High()
		outputPins[right].High()
		time.Sleep(delay)
	}

	for i := 0; i <= (value-1)/2; i++ {
		left := (value-1)/2 - i
		right := value/2 + i
		outputPins[left].Low()
		outputPins[right].Low()
		time.Sleep(delay)
	}
}

// animatePins animates the outputPins based on the given value.
// The value determines the number of pins to animate.
// Each pin is set to a high state, one by one, with a delay of `delay` between each pin.
// After setting all the pins to a high state, they are set to a low state, one by one, with the same delay between
// each pin.
func animatePins(value int) {
	if value == 0 {
		return
	}

	for i := 0; i < value; i++ {
		outputPins[i].High()
		time.Sleep(delay)
	}

	for i := 0; i < value; i++ {
		outputPins[i].Low()
		time.Sleep(delay)
	}
}

// bounce animates the outputPins by turning them on and off sequentially in a bouncing pattern.
// It takes an integer value as input, which determines the number of outputPins to animate.
// The function uses a for loop to turn on the outputPins one by one and then turn them off in reverse order.
// Each pin is toggled on for a short delay (delay/2) before moving to the next pin.
// After that, each pin is toggled off in reverse order with the same short delay.
// If the input value is zero, the function exits immediately without animating the pins.
// The function uses the outputPins and delay variables, which should be declared and initialized before calling this function.
func bounce(value int) {
	if value == 0 {
		return
	}

	for i := 0; i < value; i++ {
		outputPins[i].High()
		time.Sleep(delay / 2)
	}

	for i := value - 1; i >= 0; i-- {
		outputPins[i].Low()
		time.Sleep(delay / 2)
	}
}

// backBounce animates the output pins by turning them on and off in a reverse order.
// The number of pins to animate is determined by the value passed to the function.
// The value must be greater than 0.
// The pins are turned on starting from the pin with index value-1 and moving towards pin 0.
// Each pin is turned on for a period of delay/2 and then turned off.
// After all pins are turned on and off, the animation is complete.
// The delay between each pin change is controlled by the global variable 'delay'.
func backBounce(value int) {
	if value == 0 {
		return
	}

	for i := value - 1; i >= 0; i-- {
		outputPins[i].High()
		time.Sleep(delay / 2)
	}
	for i := 0; i < value; i++ {
		outputPins[i].Low()
		time.Sleep(delay / 2)
	}
}

// calcPins calculates the total value of input pins
// by iterating over the inputPins slice and checking if each pin's value is true.
// If the pin's value is true, the corresponding pin value in the total is incremented by the current pinVal.
// Finally, it returns the total value as an integer.
func calcPins() int {
	pinVal := 1
	total := 0
	for _, p := range inputPins {
		if p.Get() {
			total += pinVal
		}
		pinVal *= 2
	}
	return total
}
