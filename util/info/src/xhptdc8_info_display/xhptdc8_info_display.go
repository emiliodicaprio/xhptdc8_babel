package xhptdc8_info_display

import (
	"encoding/json"
	"fmt"
	WRAPPER "xhptdc8_info/xhptdc8_wrapper"
)

//_____________________________________________________________________________
// xhptdc8_manager_init_parameters

type Xhptdc8_manager_init_parameters_brief struct {
	Version            int   `json:"-"`
	Buffer_size        int64 `json:"-"`
	Variant            int
	Device_type        int
	Dma_read_delay     int
	Multiboard         WRAPPER.Crono_bool_t
	Use_ext_clock      WRAPPER.Crono_bool_t
	Ignore_calibration WRAPPER.Crono_bool_t
}

func Display_default_init_parameters(display_brief bool) (error_code uintptr, sys_err error) {
	var init WRAPPER.Xhptdc8_manager_init_parameters
	error_code, sys_err = WRAPPER.Xhptdc8_get_default_init_parameters(&init)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if display_brief {
			init_brief := (*Xhptdc8_manager_init_parameters_brief)(&init)
			formatted_struct, _ = json.MarshalIndent(init_brief, "", "  ")
		} else {
			formatted_struct, _ = json.MarshalIndent(init, "", "  ")
		}
		fmt.Println("Default Initialization Parameters 'xhptdc8_manager_init_parameters'")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_static_info

type Xhptdc8_static_info_brief struct {
	Size                  int `json:"-"`
	Version               int `json:"-"`
	Board_id              int
	Driver_revision       int
	Driver_build_revision int
	Firmware_revision     int
	Board_revision        int
	Board_configuration   int
	Subversion_revision   int
	Chip_id               [2]int
	Board_serial          int
	Flash_serial_high     uint
	Flash_serial_low      uint
	Flash_valid           byte
	Calibration_date      [20]byte
}

func Display_static_info(hMgr uintptr, device_index int, display_brief bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_static_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_static_info(hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if display_brief {
			info_brief := (*Xhptdc8_static_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		} else {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		}
		fmt.Println("Static Information 'xhptdc8_static_info'")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_temperature_info_brief

type Xhptdc8_temperature_info_brief struct {
	Size    int `json:"-"`
	Version int `json:"-"`
	Tdc     [2]float32
	Fpga    int
}

func Display_temperature_info(hMgr uintptr, device_index int, display_brief bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_temperature_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_temperature_info(hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if display_brief {
			info_brief := (*Xhptdc8_temperature_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		} else {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		}
		fmt.Println("Temprature Information 'xhptdc8_temperature_info'")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_get_fast_info

type Xhptdc8_fast_info_brief struct {
	Size             int `json:"-"`
	Version          int `json:"-"`
	Fpga_rpm         int
	Alerts           int
	Pcie_pwr_mgmt    int
	Pcie_link_width  int
	Pcie_max_payload int
	State            int
}

func Display_fast_info(hMgr uintptr, device_index int, display_brief bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_fast_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_fast_info(hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if display_brief {
			info_brief := (*Xhptdc8_fast_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		} else {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		}
		fmt.Println("Fast Information 'xhptdc8_fast_info'")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_param_info

type Xhptdc8_param_info_brief struct {
	Size         int     `json:"-"`
	Version      int     `json:"-"`
	Binsize      float64 // Double
	Channels     int
	Channel_mask int
	Total_buffer int64
}

func Display_param_info(hMgr uintptr, device_index int, display_brief bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_param_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_param_info(hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if display_brief {
			info_brief := (*Xhptdc8_param_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		} else {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		}
		fmt.Println("Param Information 'Xhptdc8_param_info'")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_param_info

type Xhptdc8_clock_info_brief struct {
	Size          int `json:"-"`
	Version       int `json:"-"`
	Cdce_locked   WRAPPER.Crono_bool_t
	Cdce_version  int
	Use_ext_clock WRAPPER.Crono_bool_t
	Fpga_locked   WRAPPER.Crono_bool_t
}

func Display_clock_info(hMgr uintptr, device_index int, display_brief bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_clock_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_clock_info(hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if display_brief {
			info_brief := (*Xhptdc8_clock_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		} else {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		}
		fmt.Println("Clock Information 'xhptdc8_param_info'")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}
