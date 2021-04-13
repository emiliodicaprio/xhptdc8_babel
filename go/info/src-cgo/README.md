
# Info-Tool

## About
It's a programm that provides _human readable output_ on the TDCs available in the system.

## Source Code Project 
The project files are created as [Go](https://golang.org/) files.

### Project Environments and Configurations
The current code is:
1. Including the [xhptdc8_interface.h](https://github.com/cronologic-de/xhptdc8_babel/blob/main/lib/include/xHPTDC8_interface.h).
2. Linked to x64 library (e.g. Dummy Library x64).

xhptdc8 APIs are called using [CGO](https://golang.org/pkg/cmd/cgo/), as following:
```GO
/*
	#cgo CFLAGS: -Wall -g -I../../../../lib/include/
	#cgo LDFLAGS: -L./ -l:../../../../lib/x64dummy/xhptdc8_driver_64.lib
	#include "xhptdc8_interface.h"
*/
import "C"
```

### Packages
#### main
- Generate the executable file.
- Process the command line.
- Display the general information.
- Call the Driver APIs wrapper `INFODSP "xhptdc8_info/xhptdc8_info_display"`.

#### xhptdc8_info_display
- Link the driver library.
- Wrap the needed APIs and structures.
- Apply any data conversion needed between Go & C (DLL).

### Building the Code
#### Prerequisites
1. Go installed on your local machine.
2. Just make sure you have the latest files of `\lib\include\` and `\lib\x64dummy\` on your local machine.

#### Steps
1. 
```CMD
go build .\xhptdc8_info.go .\info_aux.go
```
2. Run `xhptdc8_info.exe` (generated from previous step)

N.B. I used go version go1.16.2 windows/amd64.

## Using the Info Tool
All details are found [on wiki](https://github.com/cronologic-de/xhptdc8_babel/wiki/using_info_tool)
