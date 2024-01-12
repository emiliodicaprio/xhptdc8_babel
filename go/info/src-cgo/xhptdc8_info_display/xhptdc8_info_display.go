/**
Functions that wrap and call the xhptdc8_driver APIs
*/

package xhptdc8_info_display

/*
	#cgo CFLAGS: -Wall -g -I../../../../include/
	#cgo CPPFLAGS: -Wall -g -I../../../../include/
	#cgo amd64 LDFLAGS: -L./ -l:../../../../lib/x64dummy/xhptdc8_driver_64.lib
	#include "xhptdc8_interface.h"
*/
import "C"

import (
	"encoding/json"
	"fmt"
	"strings"
	"unsafe"
)

//_____________________________________________________________________________
// Global
//
type Crono_bool_t uint8
type Crono_int_t int32
type Crono_uint_t uint32
type Crono_float_t float32
type Crono_double_t float64

type Xhptdc8_manager_init_parameters struct {
	Version            Crono_int_t
	Buffer_size        int64
	Variant            Crono_int_t
	Device_type        Crono_int_t
	Dma_read_delay     Crono_int_t
	Multiboard         Crono_bool_t
	Use_ext_clock      Crono_bool_t
	Ignore_calibration Crono_bool_t
}

func Init_globals() (err_code int) {
	// Initialize driver
	var params C.xhptdc8_manager_init_parameters
	var error_code C.int
	error_code = C.xhptdc8_init(&params)
	if error_code != C.XHPTDC8_OK {
		fmt.Println("Error initializing the device:", error_code)
		return -1
	}
	return 1
}

//_____________________________________________________________________________
// xhptdc8_static_info
type Hex_Uint Crono_uint_t

type Xhptdc8_static_info struct {
	Size                  Crono_int_t
	Version               Crono_int_t
	Board_id              Crono_int_t
	Driver_revision       string
	Driver_build_revision Crono_int_t
	Firmware_revision     Crono_int_t
	Board_revision        Crono_int_t
	Board_configuration   Crono_int_t
	Subversion_revision   Crono_int_t
	Chip_id               [2]Hex_Uint
	Board_serial          Crono_float_t // Converted to float from 8.24
	Flash_serial_high     Hex_Uint
	Flash_serial_low      Hex_Uint
	Flash_valid           byte
	Calibration_date      string // Converted to string from []byte
}

type Xhptdc8_static_info_brief struct {
	Size                  Crono_int_t `json:"-"`
	Version               Crono_int_t `json:"-"`
	Board_id              Crono_int_t
	Driver_revision       string
	Driver_build_revision Crono_int_t
	Firmware_revision     Crono_int_t
	Board_revision        Crono_int_t
	Board_configuration   Crono_int_t
	Subversion_revision   Crono_int_t
	Chip_id               [2]Hex_Uint
	Board_serial          Crono_float_t
	Flash_serial_high     Hex_Uint
	Flash_serial_low      Hex_Uint
	Flash_valid           byte
	Calibration_date      string
}

func (uintVal Hex_Uint) MarshalJSON() ([]byte, error) {
	jsonValue := fmt.Sprintf("\"0x%0x\"", uintVal)
	return []byte(jsonValue), nil
}

// extern "C" int xhptdc8_get_static_info(xhptdc8_manager hMgr, int index, xhptdc8_static_info* info)
func Xhptdc8_get_static_info(device_index int, static_info *Xhptdc8_static_info) (error_code int) {
	var static_info_C C.xhptdc8_static_info
	error_code = (int)(C.xhptdc8_get_static_info((C.int)(device_index), &static_info_C))
	if error_code == C.XHPTDC8_OK {
		static_info.Board_configuration = (Crono_int_t)(static_info_C.board_configuration)
		static_info.Board_id = (Crono_int_t)(static_info_C.board_id)
		static_info.Board_revision = (Crono_int_t)(static_info_C.board_revision)
		static_info.Board_serial = (Crono_float_t)(fixed824_to_float((Crono_int_t)(static_info_C.board_serial)))
		convert_byte_ptr_to_string((*rune)(unsafe.Pointer(&(static_info_C.calibration_date[0]))), &static_info.Calibration_date) // Conversion
		static_info.Chip_id[0] = (Hex_Uint)(static_info_C.chip_id[0])
		static_info.Chip_id[1] = (Hex_Uint)(static_info_C.chip_id[1])
		static_info.Driver_build_revision = (Crono_int_t)(static_info_C.driver_build_revision)
		Driver_revision := (Crono_int_t)(static_info_C.driver_revision)
		Major := (Driver_revision >> 16) & 0xff
		Minor := (Driver_revision >> 8) & 0xff
		Revision := Driver_revision & 0xff
		static_info.Driver_revision = fmt.Sprintf("%d.%d.%d", Major, Minor, Revision)
		static_info.Firmware_revision = (Crono_int_t)(static_info_C.firmware_revision)
		static_info.Flash_serial_high = (Hex_Uint)(static_info_C.flash_serial_high)
		static_info.Flash_serial_low = (Hex_Uint)(static_info_C.flash_serial_low)
		static_info.Flash_valid = (byte)(static_info_C.flash_valid)
		static_info.Size = (Crono_int_t)(static_info_C.size)
		static_info.Subversion_revision = (Crono_int_t)(static_info_C.subversion_revision)
		static_info.Version = (Crono_int_t)(static_info_C.version)
	}
	return error_code
}

/**
Prerequisites:
  init_golobals() is called
*/
func Display_static_info(device_index int, show_details bool, display_json_only bool) (error_code int, sys_err error) {
	var info Xhptdc8_static_info
	error_code = Xhptdc8_get_static_info(device_index, &info)
	if error_code != C.XHPTDC8_OK {
		return error_code, sys_err
	}
	var formatted_struct []byte
	if show_details {
		formatted_struct, _ = json.MarshalIndent(info, "", "  ")
	} else {
		formatted_struct, _ = json.MarshalIndent((*Xhptdc8_static_info_brief)(unsafe.Pointer(&info)), "", "  ")
	}
	if !display_json_only {
		fmt.Println("static_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index)
	}
	fmt.Println(strings.ToLower(string(formatted_struct)))

	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_temperature_info_brief

type Xhptdc8_temperature_info struct {
	Size    Crono_int_t
	Version Crono_int_t
	Tdc     [2]Crono_float_t
}

type Xhptdc8_temperature_info_brief struct {
	Size    Crono_int_t `json:"-"`
	Version Crono_int_t `json:"-"`
	Tdc     [2]Crono_float_t
}

/**
Prerequisites:
  init_golobals() is called
*/
func Display_temperature_info(device_index int, show_details bool, display_json_only bool) (error_code int, sys_err error) {
	var info C.xhptdc8_temperature_info
	error_code = (int)(C.xhptdc8_get_temperature_info((C.int)(device_index), &info))
	if error_code != C.XHPTDC8_OK {
		return error_code, sys_err
	}
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

	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_get_fast_info

type Xhptdc8_fast_info struct {
	Size             Crono_int_t
	Version          Crono_int_t
	Fpga_rpm         Crono_int_t
	Alerts           Crono_int_t
	Pcie_pwr_mgmt    Crono_int_t
	Pcie_link_width  Crono_int_t
	Pcie_max_payload Crono_int_t
	State            Crono_int_t
}

type Xhptdc8_fast_info_brief struct {
	Size             Crono_int_t `json:"-"`
	Version          Crono_int_t `json:"-"`
	Fpga_rpm         Crono_int_t
	Alerts           Crono_int_t
	Pcie_pwr_mgmt    Crono_int_t
	Pcie_link_width  Crono_int_t
	Pcie_max_payload Crono_int_t
	State            Crono_int_t
}

/**
Prerequisites:
  init_golobals() is called
*/
func Display_fast_info(device_index int, show_details bool, display_json_only bool) (error_code int, sys_err error) {
	var info C.xhptdc8_fast_info
	error_code = (int)(C.xhptdc8_get_fast_info((C.int)(device_index), &info))
	if error_code != C.XHPTDC8_OK {
		return error_code, sys_err
	}
	var formatted_struct []byte
	if show_details {
		formatted_struct, _ = json.MarshalIndent((*Xhptdc8_fast_info)(unsafe.Pointer(&info)), "", "  ")
	} else {
		formatted_struct, _ = json.MarshalIndent((*Xhptdc8_fast_info_brief)(unsafe.Pointer(&info)), "", "  ")
	}
	if !display_json_only {
		fmt.Println("fast_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index)
	}
	fmt.Println(strings.ToLower(string(formatted_struct)))

	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_clock_info

type Xhptdc8_clock_info struct {
	Size          Crono_int_t
	Version       Crono_int_t
	Cdce_locked   Crono_bool_t
	Cdce_version  Crono_int_t
	Use_ext_clock Crono_bool_t
	Fpga_locked   Crono_bool_t
}

type Xhptdc8_clock_info_brief struct {
	Size          Crono_int_t `json:"-"`
	Version       Crono_int_t `json:"-"`
	Cdce_locked   Crono_bool_t
	Cdce_version  Crono_int_t
	Use_ext_clock Crono_bool_t
	Fpga_locked   Crono_bool_t
}

/**
Prerequisites:
  init_golobals() is called
*/
func Display_clock_info(device_index int, show_details bool, display_json_only bool) (error_code int, sys_err error) {
	var info C.xhptdc8_clock_info
	error_code = (int)(C.xhptdc8_get_clock_info((C.int)(device_index), &info))
	if error_code != C.XHPTDC8_OK {
		return error_code, sys_err
	}

	var formatted_struct []byte
	if show_details {
		formatted_struct, _ = json.MarshalIndent((*Xhptdc8_clock_info)(unsafe.Pointer(&info)), "", "  ")
	} else {
		formatted_struct, _ = json.MarshalIndent((*Xhptdc8_clock_info_brief)(unsafe.Pointer(&info)), "", "  ")
	}
	if !display_json_only {
		fmt.Println("clock_info of xHPTDC8 serial", Get_device_serial(device_index), "at index", device_index)
	}
	fmt.Println(strings.ToLower(string(formatted_struct)))

	return error_code, sys_err
}

//_____________________________________________________________________________
/**
Prerequisites:
  init_golobals() is called
*/
func Get_device_serial(device_index int) (board_serial float32) {
	var info C.xhptdc8_static_info
	error_code := (int)(C.xhptdc8_get_static_info((C.int)(device_index), &info))
	if error_code == C.XHPTDC8_OK {
		return float32(fixed824_to_float((Crono_int_t)(info.board_serial)))
	} else {
		fmt.Println("Error getting device static information: ", error_code)
		return 0
	}
}

func Get_devices_count() (devices_count int) {
	var error_code C.int
	var error_message *C.char
	devices_count_p := (int)(C.xhptdc8_count_devices(&error_code, &error_message))
	if devices_count_p < 1 {
		fmt.Println("System Error: ", error_code)
		return 0
	}
	return int(devices_count_p)
}

func Clean_up() {
	C.xhptdc8_close()
}
