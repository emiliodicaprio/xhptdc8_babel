# xHPTDC8 Dummy Driver
This is the source code for the dummy libraries that can be found in the /lib/ directory of this repository.
They implmeent the same API as the driver for the xHPTDC8 and are intended to allow development without access to the hardware.

 The dummy driver can be link to any program that can link to the real driver library. Calls to the driver functions will return data that is consistent with the driver documentation in the User Guide that can be found on the [xHPTDC8 product page](https://www.cronologic.de/products/tdcs/xhptdc8-pcie).

## Emulation
The dummy driver mostly does not emulate the behaviour of the xHPTDC. Most fields in the info structures return constant values.

Some emulations of the device behaviour is done:

### driver states
The state of the driver returns the actual state depending on teh calls to *_init(), *_close(), *_start_capture() and *_stop_capture().

## tdc data
The dummy driver emulates a situation where one start and one stop hit appear at a rate of 1kHz. To do this, the dummy driver maintains track of how the millieconds that are elapsed since the call to *_start_capture().

### grouping mode
The driver keeps track of how many times *_read() has been called. 

If the number of calls is less than the number of milliseconds the call returns 2. Otherwise it returns 0.

The buffer is filled with to entries of structure TDCHit. 
````C++
num_calls = // the number of times *_read() has been called since *_start_capture()
normal = //random number with mean = 5000 and standard deviation = 30
buffer[0].time = num_calls * 1000000000;
buffer[1].time = num_calls * 1000000000 + normal;
buffer[0].channel = 0
buffer[1].channel = 1
buffer[0].type = 1
buffer[1].type = 1
buffer[0].bin = 0
buffer[1].bin = 0
```

### non grouping mode
The driver keeps track of how many milliseconds habe been passed since the last call to *_read() in variable ms_since_last_call.

The call returns `N=min(ms_since_last_call * 2, buffer_size)`.

The buffer is filled with 'N' entries with the following data:
````C++
num_calls = // the number of times *_read() has been called since *_start_capture()
normal =    //random number with mean = 5000 and standard deviation = 30
buffer[i+0].time = (ms_since_last_call + i) * 1000000000;
buffer[i+1].time = (ms_since_last_call + i) * 1000000000 + normal;
buffer[i+0].channel = 0
buffer[i+1].channel = 1
buffer[i+0].type = 1
buffer[i+1].type = 1
buffer[i+0].bin = 0
buffer[i+1].bin = 0
```


