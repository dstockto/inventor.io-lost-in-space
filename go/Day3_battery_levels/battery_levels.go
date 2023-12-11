package main

import (
	"machine"
	"time"
)

func main() {
	cabinLightsPin := machine.D12
	cabinLightsPin.Configure(machine.PinConfig{Mode: machine.PinOutput})

	cabinSwitchPin := machine.D2
	cabinSwitchPin.Configure(machine.PinConfig{Mode: machine.PinInput})

	for {
		if cabinSwitchPin.Get() {
			cabinLightsPin.High()
			time.Sleep(1500 * time.Millisecond)
			cabinLightsPin.Low()
			time.Sleep(200 * time.Millisecond)
		} else {
			cabinLightsPin.Low()
		}
	}
}
