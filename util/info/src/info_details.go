package main

import "fmt"

func display_help() {
	msg := `
-v            show size and version information for all selected structures
-static       show static_info
-temp         show temperature_info
-temperature  show_temperature_info
-fast         show fast_info
-param        show param_info
-clock        show clock_info
-all          show all infos structures
`
	fmt.Println(msg)
}
