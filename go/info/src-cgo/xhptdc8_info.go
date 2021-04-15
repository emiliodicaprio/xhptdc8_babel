package main

/**
Package:
- Generate the executable file.
- Process the command line.
- Display the general information.
- Call the Driver APIs wrapper `INFODSP "xhptdc8_info/xhptdc8_info_display"`.

Refer to https://github.com/cronologic-de/xhptdc8_babel/edit/main/go/info/src-cgo/README.md for more information.
*/
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
		clean_up()
		return
	case 0:
		// No valid TDC passed in command line
		display_about()
		display_devices_serials()
		display_help()
		display_devices_static_infos()
		display_footer()
		clean_up()
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
	clean_up()
}
