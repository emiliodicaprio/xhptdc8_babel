package main

func main() {

	// Initialize the driver
	// defer WRAPPER.Xhptdc8_close(hMgr) C Error
	display_about()
	if init_globals() == -1 {
		// Error initializing driver
		display_help()
		display_footer()
		return
	}
	display_devices_serials()
	switch process_command_line() {
	case -1:
		// Error initializing driver
		display_help()
		display_footer()
		return
	case 0:
		// No valid TDC passed
		display_help()
		display_devices_static_infos()
		display_footer()
		return
	}
	display_info()
	display_footer()
}
