package main

/*
 This file has the functions of package main that directly access
 xhptdc8_info_display package and xhptdc8_wrapper package
*/
import (
	"flag"
	"fmt"
	"sort"
	"strconv"
	"strings"
	INFODSP "xhptdc8_info/xhptdc8_info_display"
)

type CmdLine_Flags_T struct {
	show_version_and_size *bool
	show_static_info      *bool
	show_temp_info        *bool
	show_temperature_info *bool
	show_fast_info        *bool
	show_clock_info       *bool
	show_all_info         *bool
	output_json_only      *bool
}

type Device_Serial_T struct {
	Index       int
	Serial      float32
	Is_selected bool // true if passed in the command line using `-tdc`
}

// String Array Flags for custom implementation of flag.Var to allow multiple
// TDCs in command line
type strArrFlags []string

// A list of the passed TDCs values in flags
var flags_tdcs strArrFlags

//_____________________________________________________________________________
// Global
//
var g_CmdLine_Flags = CmdLine_Flags_T{}

// Initialized by init_globals()
var g_Devices_Serials []Device_Serial_T
var g_Devices_Serials_Sorted []Device_Serial_T
var g_Devices_Count int = -1

//_____________________________________________________________________________
// Functions
//
func init_globals() (err_code int) {

	err_code = INFODSP.Init_globals()
	if err_code == -1 {
		return -1
	}
	// Get devices count & initialize the related global variables
	g_Devices_Count = INFODSP.Get_devices_count()
	if g_Devices_Count <= 0 {
		return -1
	}
	for device_index := 0; device_index < g_Devices_Count; device_index++ {
		device_serial := Device_Serial_T{
			device_index, // Index in array `Device_Serial_T` and in driver
			INFODSP.Get_device_serial(device_index),
			false, // Initialized as "not selected"
		}
		g_Devices_Serials = append(g_Devices_Serials_Sorted, device_serial)
		g_Devices_Serials_Sorted = append(g_Devices_Serials_Sorted, device_serial)
	}
	// Sort the devices in `g_Devices_Serials_Sorted` for display purpose
	if g_Devices_Count > 0 {
		sort.Slice(g_Devices_Serials_Sorted[:], func(i, j int) bool {
			return g_Devices_Serials_Sorted[i].Serial < g_Devices_Serials_Sorted[j].Serial
		})
	}
	return 1
}

func display_about() {
	msg :=
		`-----------------------------------------------------------------------------
               xHPTDC8 Information Utility Application                       
-----------------------------------------------------------------------------`
	fmt.Println(msg)
}

func display_footer() {
	msg :=
		`-----------------------------------------------------------------------------
                          End of Application                       
-----------------------------------------------------------------------------`
	fmt.Println(msg)
}

func display_help() {
	// Must be the same like process_command_line()
	msg := `
About the application
Command:
  xhptdc8_info.exe [TDC] [Flags]
Usage: 
  [TDC]   is either an integer as the index of the TDC, or a serial number of the TDC
		  passed as a value of the flag -tdc, i.e. -tdc=[TDC]	
  [Flags] Can be one or more of the following flags:
          -v            show size and version information for all selected structures
          -static       show static_info
          -temp         show temperature_info
          -temperature  show_temperature_info
          -fast         show fast_info
          -clock        show clock_info
          -all          show all infos structures
          -h            show this help
          -d            output requested data in JSON only with no headers

`
	fmt.Println(msg)
}

/**
Prerequisites:
  init_golobals() is called
*/
func process_command_line() (err_code int) {
	// Must be the same like display_help()
	flag.Var(&flags_tdcs, "tdc", "is either an integer as the index of the TDC, or a serial number of the TDC, can be repeated")
	g_CmdLine_Flags.show_version_and_size = flag.Bool("v", false,
		"show size and version information for all selected structures")
	g_CmdLine_Flags.show_static_info = flag.Bool("static", false, "show static_info")
	g_CmdLine_Flags.show_temp_info = flag.Bool("temp", false, "show temperature_info")
	g_CmdLine_Flags.show_temperature_info = flag.Bool("temperature", false,
		"show_temperature_info")
	g_CmdLine_Flags.show_fast_info = flag.Bool("fast", false, "show fast_info")
	g_CmdLine_Flags.show_clock_info = flag.Bool("clock", false, "show clock_info")
	g_CmdLine_Flags.show_all_info = flag.Bool("all", false,
		"show all infos structures")
	g_CmdLine_Flags.output_json_only = flag.Bool("d", false,
		"output requested data in JSON only with no headers")
	flag.Parse()

	// Get the selected TDCs information, validate them, and update
	// `Is_selected` in the corresponding element of `g_Devices_Serials`
	var sel_devices_cout = len(flags_tdcs)
	if sel_devices_cout == 0 {
		// No command line arguments
		fmt.Println("Info: No device selected, will print information for all installed devices.")
	}
	if sel_devices_cout > g_Devices_Count {
		fmt.Println("Error: Number of entered TDCs <", sel_devices_cout,
			"> is greater than installed number of TDCs <", g_Devices_Count, ">")
		return 0
	}
	var tdc_arg_f float64
	var sel_device_is_found bool
	var err error
	for sel_device_index := 0; sel_device_index < sel_devices_cout; sel_device_index++ {

		// Initialize for every selected device
		sel_device_is_found = false

		// Get the selectd TDC value (index, or serial), and validate its format
		tdc_arg := flags_tdcs[sel_device_index]
		if tdc_arg_f, err = strconv.ParseFloat(tdc_arg, 32); err != nil {
			fmt.Println("Error: Invalid TDC value <", tdc_arg, ">, Error: ", err)
			return -1
		}

		// Check the selected TDC format
		if strings.Contains(tdc_arg, ".") {
			// Serial Number is entered
			for device_index := 0; device_index < g_Devices_Count; device_index++ {
				if g_Devices_Serials[device_index].Serial == float32(tdc_arg_f) {
					// Set the `Is_selected` value in corresponding element in
					// `g_Devices_Serials`
					g_Devices_Serials[device_index].Is_selected = true
					sel_device_is_found = true
				}
			}
			// Check if device is not installed
			if !sel_device_is_found {
				fmt.Println("Error: Serial number entered <", tdc_arg, ">", "is not found.")
				return -1
			}
			// fmt.Println("Board serial selected is: <", tdc_arg, "> of index <", device_index, ">")
		} else {
			// Index is entered as a number, starts @ 0
			if int(tdc_arg_f) >= g_Devices_Count || int(tdc_arg_f) < 0 {
				fmt.Println("Error: Board index entered <", tdc_arg,
					"> greater than the installed devices last index, or is invalid.")
				return -1
			}
			// Set the `Is_selected` value in corresponding element in
			// `g_Devices_Serials`
			g_Devices_Serials[int(tdc_arg_f)].Is_selected = true
			fmt.Println("Board index selected is: <", int(tdc_arg_f), ">")
		}
	}
	return 1
}

/**
Prerequisites:
  init_golobals() is called
*/
func display_info() {
	var error_code int
	var sys_err error
	var no_print_option_selected = false
	var no_device_selected = false

	// Check the selected TDCs
	if len(flags_tdcs) == 0 {
		no_device_selected = true
	}

	// Check print options passed in the command line
	if *g_CmdLine_Flags.show_all_info {
		// All information to be printed
		// Set all to true
		*g_CmdLine_Flags.show_static_info = true
		*g_CmdLine_Flags.show_temp_info = true
		*g_CmdLine_Flags.show_temperature_info = true
		*g_CmdLine_Flags.show_fast_info = true
		*g_CmdLine_Flags.show_clock_info = true
	} else {
		if !*(g_CmdLine_Flags.show_static_info) &&
			!*(g_CmdLine_Flags.show_temp_info) &&
			!*(g_CmdLine_Flags.show_temperature_info) &&
			!*(g_CmdLine_Flags.show_fast_info) &&
			!*(g_CmdLine_Flags.show_clock_info) {
			// No print option is selected, set the flag
			no_print_option_selected = true
		}
	}

	// Loop on all installed devices and display info for the selected one(s)
	for device_index := 0; device_index < g_Devices_Count; device_index++ {
		if g_Devices_Serials[device_index].Is_selected || no_device_selected {
			// Either the device is selected in command line, or no device is selected
			// Print the options

			// If no print option is selected in the command line, then print the -static
			// information of the device
			if no_print_option_selected {
				error_code, sys_err = INFODSP.Display_static_info(
					g_Devices_Serials[device_index].Index,
					*g_CmdLine_Flags.show_version_and_size, *g_CmdLine_Flags.output_json_only)
				if error_code != 0 {
					fmt.Println("Error displaying static info: ", error_code, sys_err)
				}
				continue // No need to check other print options
			}

			// Check selected print options
			if *g_CmdLine_Flags.show_clock_info {
				error_code, sys_err = INFODSP.Display_clock_info(
					g_Devices_Serials[device_index].Index,
					*g_CmdLine_Flags.show_version_and_size, *g_CmdLine_Flags.output_json_only)
				if error_code != 0 {
					fmt.Println("Error displaying clock info: ", error_code, sys_err)
				}
			}
			if *g_CmdLine_Flags.show_fast_info {
				error_code, sys_err = INFODSP.Display_fast_info(
					g_Devices_Serials[device_index].Index,
					*g_CmdLine_Flags.show_version_and_size, *g_CmdLine_Flags.output_json_only)
				if error_code != 0 {
					fmt.Println("Error displaying fast info: ", error_code, sys_err)
				}
			}
			if *g_CmdLine_Flags.show_static_info {
				error_code, sys_err = INFODSP.Display_static_info(
					g_Devices_Serials[device_index].Index,
					*g_CmdLine_Flags.show_version_and_size, *g_CmdLine_Flags.output_json_only)
				if error_code != 0 {
					fmt.Println("Error displaying static info: ", error_code, sys_err)
				}
			}
			if *g_CmdLine_Flags.show_temp_info {
				error_code, sys_err = INFODSP.Display_temperature_info(
					g_Devices_Serials[device_index].Index,
					*g_CmdLine_Flags.show_version_and_size, *g_CmdLine_Flags.output_json_only)
				if error_code != 0 {
					fmt.Println("Error displaying temp info: ", error_code, sys_err)
				}
			} else if *g_CmdLine_Flags.show_temperature_info {
				error_code, sys_err = INFODSP.Display_temperature_info(
					g_Devices_Serials[device_index].Index,
					*g_CmdLine_Flags.show_version_and_size, *g_CmdLine_Flags.output_json_only)
				if error_code != 0 {
					fmt.Println("Error displaying temp info: ", error_code, sys_err)
				}
			}
		}
	}
}

/**
Prerequisites:
  init_golobals() is called
*/
func display_devices_serials() {
	fmt.Println()
	fmt.Println("Installed Devices Serials for", g_Devices_Count, "TDC(s):")
	for device_index := 0; device_index < g_Devices_Count; device_index++ {
		fmt.Println(device_index+1, ") index:", g_Devices_Serials_Sorted[device_index].Index,
			"xHPTDC8 serial", g_Devices_Serials_Sorted[device_index].Serial)
	}
	fmt.Println()
}

/**
Display all devices static informations
*/
func display_devices_static_infos() {
	fmt.Println()
	fmt.Println("Static Information of all TDC(s):")
	for device_index := 0; device_index < g_Devices_Count; device_index++ {
		INFODSP.Display_static_info(device_index, true, false)
	}
	fmt.Println()
}

func clean_up() {
	INFODSP.Clean_up()
}

//_____________________________________________________________________________
// Custom implementation of flag.Value for multiple TDCs
//
func (i *strArrFlags) String() string {
	return "String Array representation"
}
func (i *strArrFlags) Set(value string) error {
	*i = append(*i, value)
	return nil
}
