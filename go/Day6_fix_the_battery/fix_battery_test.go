package main

import "testing"

func Test_mapValue(t *testing.T) {
	type args struct {
		val    uint16
		lo     uint16
		hi     uint16
		delay  int
		delay2 int
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		{
			name: "below min",
			args: args{
				val:    0,
				lo:     10,
				hi:     100,
				delay:  5,
				delay2: 10,
			},
			want: 5,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := mapValue(tt.args.val, tt.args.lo, tt.args.hi, tt.args.delay, tt.args.delay2); got != tt.want {
				t.Errorf("mapValue() = %v, want %v", got, tt.want)
			}
		})
	}
}
