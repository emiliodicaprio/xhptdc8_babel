
# Info-Tool

## About
It's a program that provides _human readable output_ about the TDCs available in the system.

## Source Code Project 
The project files are created as [Go](https://golang.org/) files.

### Project Environments and Configurations
The current code:
1. Includes the [xhptdc8_interface.h](https://github.com/cronologic-de/xhptdc8_babel/blob/main/include/xHPTDC8_interface.h).
2. Links to x64 library (e.g. Dummy Library x64).

xhptdc8 APIs are called using [CGO](https://golang.org/pkg/cmd/cgo/), as following:
```GO
/*
	#cgo CFLAGS: -Wall -g -I../../../../include/
	#cgo CPPFLAGS: -Wall -g -I../../../../include/	
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

### Building the Code (64-bit)
#### Prerequisites
1. `Go` is installed on your local machine.
2. Just make sure you have the latest files of `\include\` and `\lib\x64dummy\` on your local machine.

#### Steps
1. Using `cmd`, cd to `\Path\To\Project\go\info\src-cgo`, and run:
```CMD
go build -o xhptdc8_info_64.exe .\xhptdc8_info.go .\info_aux.go
```
2. Run `xhptdc8_info_64.exe` (generated from previous step). N.B. Driver DLL should be on the path/same folder.

N.B. I used go version go1.16.2 windows/amd64.

## Using the Info Tool
All details are found [on wiki](https://github.com/cronologic-de/xhptdc8_babel/wiki/using_info_tool)

## The wrapper

### Data Types
The following data types are defined for the compatibility between Go structure and C structure:
```Go
type Crono_bool_t uint8
type Crono_int_t int32
type Crono_uint_t uint32
type Crono_float_t float32
type Crono_double_t float64
```
Using Go `int` data type, for example, mapped to driver `int` will cause data inconsistency for the difference in the int data size between them.

### The Structures
The library structures are wrapped in Go structures for the following reasons:
1. Having the first letter in the member name in upper case, for `json.MarshalIndent` to be able to handle it by JSON and display the structure values properly.
2. Simplificiation of code that displays the information with or without the structure version and size (option `-v` in command-line paramters).

```Go
type Xhptdc8_temperature_info struct {
	Size    Crono_int_t
	Version Crono_int_t
	Tdc     [2]Crono_float_t
	Fpga    Crono_int_t
}

type Xhptdc8_temperature_info_brief struct {
	Size    Crono_int_t `json:"-"`
	Version Crono_int_t `json:"-"`
	Tdc     [2]Crono_float_t
	Fpga    Crono_int_t
}
```

Two _identical_ versions of every structure are defined: the structure and the `xxxx_brief` structure, with the following notes:
1. The only difference is in JSON annotation ``json:"-"`` in the `xxxx_brief` version.
2. `xxxx_brief` is used with `-v` command-line option is not defined, while the normal structure version is used if defined.
3. First letter of both the structure name and memebrs name are in upper case to be exported so `json.MarshalIndent` displays information properly.

### The APIs
Thanks to CGO, the APIs are called directly from within the code, for instance, to call the `xhptdc8_get_temperature_info()`, we write the following code:
```GO
var info C.xhptdc8_temperature_info
error_code = (int)(C.xhptdc8_get_temperature_info((C.int)(device_index), &info))
```
Just:
- Use the `C` version of the structure as an argument.
- Type cast the Go integer value (device_index) to the corresponding C type `C.int`

### Display the Structures
A very neat feature in Go packages is to print out the strcuture information in JSON format, that important for the following reasons:
1. It's a human readable format.
2. When application is run by machines and scripts, it's very easy and standard to parse the output information.

`json.MarshalIndent` is used for that purpose.

With code looks like the following:
```GO
var formatted_struct []byte
if show_details {
	formatted_struct, _ = json.MarshalIndent((*Xhptdc8_temperature_info)(unsafe.Pointer(&info)), "", "  ")
} else {
	formatted_struct, _ = json.MarshalIndent((*Xhptdc8_temperature_info_brief)(unsafe.Pointer(&info)), "", "  ")
}
if !display_json_only {
	fmt.Println("temperature_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index)
}
fmt.Println(strings.ToLower(string(formatted_struct)))
```
- The C structure is type casted to the corresponding "JSON-Compatible" GO Structure based on `-v` option (`show_details`), it's either casted to Go struct, or its `xxxx_brief` version.
- The Go structure version is formatted using `json.MarhsallIndent` to `formatted_struct`, which is converted all in lower case back again later on (using `ToLower`), as: _Except for Go, all languages using the tool use lower case struct members. Therefore the JSON output should also be in lower case_.

### The flow
1. The application first initializes the driver using:
```GO
func init_globals() (err_code int) {
    err_code = INFODSP.Init_globals()
    .
    .
```

`init_globals` both:
- Initializes the xhptdc8 driver.
- Initializes the global variables: 
```GO
var g_Devices_Serials []Device_Serial_T
var g_Devices_Serials_Sorted []Device_Serial_T
var g_Devices_Count int = -1
```

2. Parses and procesess the command line:
And initializes the following global variables:
```GO
var g_CmdLine_Flags = CmdLine_Flags_T{}
```
Where `g_CmdLine_Flags` is the controller of all information that should be displayed by the application.

3. Then displays the underlying information as per the options the user passed in the command line.

### Special Cases
#### `xhptdc8_static_info` Data Conversion
The function `Xhptdc8_get_static_info` is provided specially for static_info, for data/format conversion for:
- `board_serial`: 8.24 format conversion from int to float, using `fixed824_to_float` custom function.
- `calibration_date`: Date in bytes to String, using `convert_byte_ptr_to_string` custom function.

#### Display Value as Hexadecimal
It was [required](/../../issues/45) to display `Chip_id`, `Flash_serial_high`, and `Flash_serial_low` as hexadecimal value; for that, the following updates are applied:
1. Added a new type `Hex_Uint`.
2. Defined all variables needed to be displayed as hexadecimal for this type.
3. Customized `MarshalJSON` for this type in `func (uintVal Hex_Uint) MarshalJSON() ([]byte, error)`
