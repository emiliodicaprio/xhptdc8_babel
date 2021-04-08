package main

import (
	"flag"
	"fmt"
	INFODSP "xhptdc8_info/xhptdc8_info_display"
	WRAPPER "xhptdc8_info/xhptdc8_wrapper"
)

func main() {

	// argsWithProg := os.Args
	// argsWithoutProg := os.Args[1:]

	show_version_and_size := flag.Bool("v", false, "show size and version information for all selected structures")
	show_static_info := flag.Bool("static", false, "show static_info")
	show_temp_info := flag.Bool("temp", false, "show temperature_info")
	show_temperature_info := flag.Bool("temperature", false, "show_temperature_info")
	show_fast_info := flag.Bool("fast", false, "show fast_info")
	show_param_info := flag.Bool("param", false, "show param_info")
	show_clock_info := flag.Bool("clock", false, "show clock_info")
	show_all_info := flag.Bool("all", false, "show all infos structures")
	flag.Parse()

	var params WRAPPER.Xhptdc8_manager_init_parameters
	var error_code int
	var error_message string
	var hMgr uintptr // Define the handle to manager as a pointer (void*)
	WRAPPER.Xhptdc8_init(&hMgr, &params, &error_code, &error_message)

	if *show_all_info {
		*show_static_info = true
		*show_temp_info = true
		*show_temperature_info = true
		*show_fast_info = true
		*show_param_info = true
		*show_clock_info = true
	}
	if *show_clock_info {
		INFODSP.Display_clock_info(hMgr, 0, *show_version_and_size)
	}
	if *show_fast_info {
		INFODSP.Display_fast_info(hMgr, 0, *show_version_and_size)
	}
	if *show_param_info {
		INFODSP.Display_param_info(hMgr, 0, *show_version_and_size)
	}
	if *show_static_info {
		INFODSP.Display_static_info(hMgr, 0, *show_version_and_size)
	}
	if *show_temp_info {
		INFODSP.Display_temperature_info(hMgr, 0, *show_version_and_size)
	}
	if *show_temperature_info {
		INFODSP.Display_temperature_info(hMgr, 0, *show_version_and_size)
	}

	// display_help()
	// Initialize the driver
	/*	var params WRAPPER.Xhptdc8_manager_init_parameters
		var error_code int
		var error_message string
		var p_hMgr uintptr // Define the handle to manager as a pointer (void*)
		WRAPPER.Xhptdc8_init(&p_hMgr, &params, &error_code, &error_message)

		INFODSP.Display_static_info(p_hMgr, 0, false)
		INFODSP.Display_clock_info(p_hMgr, 0, false)
		INFODSP.Display_fast_info(p_hMgr, 0, false)
		INFODSP.Display_param_info(p_hMgr, 0, false)
		INFODSP.Display_temperature_info(p_hMgr, 0, true)
		INFODSP.Display_default_init_parameters(false)
	*/
	fmt.Println("End of program")
}
