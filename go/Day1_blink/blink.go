package main

import (
	"machine"
	"time"
)

func main() {
	builtIn := machine.LED
	builtIn.Configure(machine.PinConfig{Mode: machine.PinOutput})

	for {
		builtIn.High()
		time.Sleep(100 * time.Millisecond)
		builtIn.Low()
		time.Sleep(100 * time.Millisecond)
	}
}
