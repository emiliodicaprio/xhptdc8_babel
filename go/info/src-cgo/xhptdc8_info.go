package main

func main() {
	// Initialize the driver
	if init_globals() == -1 {
		// Error initializing driver
		display_about()
		display_help()
		display_footer()
		return
	}
	switch process_command_line() {
	case -1:
		// Error processing command line
		display_about()
		display_devices_serials()
		display_help()
		display_footer()
		return
	case 0:
		// No valid TDC passed in command line
		display_about()
		display_devices_serials()
		display_help()
		display_devices_static_infos()
		display_footer()
		return
	}
	if !(*g_CmdLine_Flags.output_json_only) {
		display_about()
		display_devices_serials()
	}
	display_info()
	if !(*g_CmdLine_Flags.output_json_only) {
		display_footer()
	}
}
