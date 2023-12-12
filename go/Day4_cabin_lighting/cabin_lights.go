package main

import (
	"machine"
)

func main() {
	cabinSwitch := machine.D2
	cockpitSwitch := machine.D3
	storageSwitch := machine.D4

	cabinLights := machine.D10
	cockpitLights := machine.D11
	storageLights := machine.D12

	lightMap := map[machine.Pin]machine.Pin{
		cabinSwitch:   cabinLights,
		cockpitSwitch: cockpitLights,
		storageSwitch: storageLights,
	}

	for s, l := range lightMap {
		s.Configure(machine.PinConfig{Mode: machine.PinInput})
		l.Configure(machine.PinConfig{Mode: machine.PinOutput})
	}

	for {
		for s, l := range lightMap {
			if s.Get() {
				l.High()
			} else {
				l.Low()
			}
		}
	}
}
