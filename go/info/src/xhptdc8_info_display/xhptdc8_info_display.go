package xhptdc8_info_display

import (
	"encoding/json"
	"fmt"
	WRAPPER "xhptdc8_info/xhptdc8_wrapper"
)

//_____________________________________________________________________________
// Global
//

var g_hMgr uintptr // Define the handle to manager as a pointer (void*)

/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Init_globals() (err_code int) {
	// Initialize driver, g_hMgr
	var params WRAPPER.Xhptdc8_manager_init_parameters
	var error_code int
	var error_message string
	var sys_err error
	g_hMgr, sys_err = WRAPPER.Xhptdc8_init(&params, &error_code, &error_message)
	if g_hMgr == 0 {
		fmt.Println("Error initializing the device:", sys_err, ", Error:", error_code, error_message)
		return -1
	}
	return 1
}

//_____________________________________________________________________________
// xhptdc8_manager_init_parameters

type Xhptdc8_manager_init_parameters_brief struct {
	Version            WRAPPER.Crono_int_t `json:"-"`
	Buffer_size        int64               `json:"-"`
	Variant            WRAPPER.Crono_int_t
	Device_type        WRAPPER.Crono_int_t
	Dma_read_delay     WRAPPER.Crono_int_t
	Multiboard         WRAPPER.Crono_bool_t
	Use_ext_clock      WRAPPER.Crono_bool_t
	Ignore_calibration WRAPPER.Crono_bool_t
}

/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Display_default_init_parameters(show_details bool) (error_code uintptr, sys_err error) {
	var init WRAPPER.Xhptdc8_manager_init_parameters
	error_code, sys_err = WRAPPER.Xhptdc8_get_default_init_parameters(&init)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if show_details {
			formatted_struct, _ = json.MarshalIndent(init, "", "  ")
		} else {
			init_brief := (*Xhptdc8_manager_init_parameters_brief)(&init)
			formatted_struct, _ = json.MarshalIndent(init_brief, "", "  ")
		}
		fmt.Println("Default Initialization Parameters 'xhptdc8_manager_init_parameters'")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_static_info

type Xhptdc8_static_info_brief struct {
	Size                  WRAPPER.Crono_int_t `json:"-"`
	Version               WRAPPER.Crono_int_t `json:"-"`
	Board_id              WRAPPER.Crono_int_t
	Driver_revision       WRAPPER.Crono_int_t
	Driver_build_revision WRAPPER.Crono_int_t
	Firmware_revision     WRAPPER.Crono_int_t
	Board_revision        WRAPPER.Crono_int_t
	Board_configuration   WRAPPER.Crono_int_t
	Subversion_revision   WRAPPER.Crono_int_t
	Chip_id               [2]WRAPPER.Crono_int_t
	Board_serial          WRAPPER.Crono_float_t
	Flash_serial_high     WRAPPER.Crono_uint_t
	Flash_serial_low      WRAPPER.Crono_uint_t
	Flash_valid           byte
	Calibration_date      string
}

/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Display_static_info(device_index int, show_details bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_static_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_static_info(g_hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if show_details {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		} else {
			info_brief := (*Xhptdc8_static_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		}
		fmt.Println("static_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index, ":")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_temperature_info_brief

type Xhptdc8_temperature_info_brief struct {
	Size    WRAPPER.Crono_int_t `json:"-"`
	Version WRAPPER.Crono_int_t `json:"-"`
	Tdc     [2]WRAPPER.Crono_float_t
	Fpga    WRAPPER.Crono_int_t
}

/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Display_temperature_info(device_index int, show_details bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_temperature_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_temperature_info(g_hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if show_details {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		} else {
			info_brief := (*Xhptdc8_temperature_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		}
		fmt.Println("temperature_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index, ":")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_get_fast_info

type Xhptdc8_fast_info_brief struct {
	Size             WRAPPER.Crono_int_t `json:"-"`
	Version          WRAPPER.Crono_int_t `json:"-"`
	Fpga_rpm         WRAPPER.Crono_int_t
	Alerts           WRAPPER.Crono_int_t
	Pcie_pwr_mgmt    WRAPPER.Crono_int_t
	Pcie_link_width  WRAPPER.Crono_int_t
	Pcie_max_payload WRAPPER.Crono_int_t
	State            WRAPPER.Crono_int_t
}

/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Display_fast_info(device_index int, show_details bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_fast_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_fast_info(g_hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if show_details {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		} else {
			info_brief := (*Xhptdc8_fast_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		}
		fmt.Println("fast_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index, ":")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_param_info

type Xhptdc8_param_info_brief struct {
	Size         WRAPPER.Crono_int_t `json:"-"`
	Version      WRAPPER.Crono_int_t `json:"-"`
	Binsize      WRAPPER.Crono_double_t
	Channels     WRAPPER.Crono_int_t
	Channel_mask WRAPPER.Crono_int_t
	Total_buffer int64
}

/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Display_param_info(device_index int, show_details bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_param_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_param_info(g_hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if show_details {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		} else {
			info_brief := (*Xhptdc8_param_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		}
		fmt.Println("param_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index, ":")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_param_info

type Xhptdc8_clock_info_brief struct {
	Size          WRAPPER.Crono_int_t `json:"-"`
	Version       WRAPPER.Crono_int_t `json:"-"`
	Cdce_locked   WRAPPER.Crono_bool_t
	Cdce_version  WRAPPER.Crono_int_t
	Use_ext_clock WRAPPER.Crono_bool_t
	Fpga_locked   WRAPPER.Crono_bool_t
}

/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Display_clock_info(device_index int, show_details bool) (error_code uintptr, sys_err error) {
	var info WRAPPER.Xhptdc8_clock_info
	error_code, sys_err = WRAPPER.Xhptdc8_get_clock_info(g_hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		var formatted_struct []byte
		if show_details {
			formatted_struct, _ = json.MarshalIndent(info, "", "  ")
		} else {
			info_brief := (*Xhptdc8_clock_info_brief)(&info)
			formatted_struct, _ = json.MarshalIndent(info_brief, "", "  ")
		}
		fmt.Println("clock_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index, ":")
		fmt.Println(string(formatted_struct))
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
/**
Prerequisites:
  init_golobals() is called, and g_hMgr is valid
*/
func Get_device_serial(device_index int) (board_serial float32) {
	var info WRAPPER.Xhptdc8_static_info
	error_code, sys_err := WRAPPER.Xhptdc8_get_static_info(g_hMgr, device_index, &info)
	if error_code == WRAPPER.XHPTDC8_OK {
		return float32(info.Board_serial)
	} else {
		fmt.Println("Error getting device static information: ", sys_err)
		return 0
	}
}

func Get_devices_count() (devices_count int) {
	var error_code int
	var error_message string
	devices_count_p, sys_err := WRAPPER.Xhptdc8_count_devices(&error_code, &error_message)
	if devices_count_p < 1 {
		if sys_err != nil {
			fmt.Println("System Error: ", sys_err)
			return 0
		}
	}
	return int(devices_count_p)
}

func Clean_up() {
	//$$

}
