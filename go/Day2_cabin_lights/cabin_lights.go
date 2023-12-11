package main

import (
	"machine"
	"time"
)

func main() {
	cabinLightsPin := machine.D12
	cabinLightsPin.Configure(machine.PinConfig{Mode: machine.PinOutput})

	for {
		cabinLightsPin.High()
		time.Sleep(1000 * time.Millisecond)
		cabinLightsPin.Low()
		time.Sleep(100 * time.Millisecond)
	}
}
