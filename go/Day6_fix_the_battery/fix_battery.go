package main

import (
	"machine"
	"time"
)

var minDelay = 50
var maxDelay = 500

func main() {
	// I am not completely sure this is working the same or similar enough to the CPP version.
	// Using print to output to the serial monitor seems to be a little broken since it only
	// outputs a few times and then seems to just dump zeros. It definitely seems to react
	// to light, but it's hard to say for sure if my ardMap function behaves like the original
	// arduino map function in the CPP version. It was also tough to figure out how to even
	// get the analog pin read to work.

	machine.InitADC()

	led := machine.LED
	led.Configure(machine.PinConfig{Mode: machine.PinOutput})

	sensor := machine.ADC{Pin: machine.ADC0}
	sensor.Configure(machine.ADCConfig{})

	hi := sensor.Get()
	lo := hi - 1

	for {
		val := sensor.Get()
		if val > hi {
			hi = val
		}
		if val < lo {
			lo = val
		}

		delay := ardMap(int(val), int(lo), int(hi), maxDelay, minDelay)

		led.High()
		time.Sleep(time.Millisecond * time.Duration(delay))
		led.Low()
		time.Sleep(time.Millisecond * time.Duration(100))
	}
}

// mapValue takes a value of val along with an expected range of values between lo and high. It maps
// the incoming value to a value between delay and delay2. If val is lower than lo then the returned
// value should be delay. If it's higher than high it should return delay2. If the val is between
// lo and high then it should be mapped to a value between delay and delay2 according to how close
// it is to lo or high. The mapping of values should be linearly proportional.
func mapValue(val uint16, lo uint16, hi uint16, delay int, delay2 int) int {
	if val <= lo {
		return delay
	} else if val >= hi {
		return delay2
	} else {
		return int(val-lo)*((delay2-delay)/(int(hi-lo))) + delay
	}
}

func ardMap(x, inMin, inMax, outMin, outMax int) int {
	scale := float64(outMax-outMin) / float64(inMax-inMin)
	result := float64(x-inMin)*scale + float64(outMin)
	return int(result)
}
