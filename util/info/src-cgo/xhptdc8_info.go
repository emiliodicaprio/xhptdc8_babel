package main

/*
	// _____________________________
	// Compilation and Linking Flags
	//
	#cgo CFLAGS:  -I../../../lib/include/
	#cgo LDFLAGS: -L../../../lib/x64dummy/ -lxhptdc8_driver_64

	// _____________________________
	// Include and globals
	//
	#include <stdio.h>
	#include <stdlib.h>
	#include "xhptdc8_interface.h"

	void testFunc() {
		fprintf(stdout, "Just Test") ;
	}
	int float_to_fixed(float inp)
	{
		return (int)(inp * (1 << 24));
	}

	float fixed_to_float(int inp)
	{
    	return ((float)inp) / (1 << 24);
	}
*/
import "C"
import "fmt"

func main() {
	// cs := C.CString("Hello from stdio")
	fixed_val := C.float_to_fixed(21.108)
	float_val := C.fixed_to_float(354133472)
	x := ((float32)(8388608) / (1 << 24))
	y := (int)(x * (1 << 24))
	fmt.Println(fixed_val)
	fmt.Println(float_val)
	fmt.Println(x)
	fmt.Println(y)
	C.testFunc()
}
