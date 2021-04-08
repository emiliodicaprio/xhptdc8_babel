package main

import (
	"fmt"
	INFODISP "xhptdc8_info/xhptdc8_info_display"
	WRAPPER "xhptdc8_info/xhptdc8_wrapper"
)

func main() {
	// WRAPPER.Display_default_init_parameters(false)
	display_help()

	// Initialize the driver
	var params WRAPPER.Xhptdc8_manager_init_parameters
	var error_code int
	var error_message string
	var p_hMgr uintptr
	WRAPPER.Xhptdc8_init(&p_hMgr, &params, &error_code, &error_message)

	INFODISP.Display_static_info(p_hMgr, 0, false)
	fmt.Println("End of program")
}
