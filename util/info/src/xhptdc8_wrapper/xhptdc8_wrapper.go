package xhptdc8_wrapper

import (
	"fmt"
	"strings"
	"syscall"
	"unsafe"
)

type Crono_bool_t uint8
type Crono_int_t int32
type Crono_uint_t uint32
type Crono_float_t float32
type Crono_double_t float64

//_____________________________________________________________________________
// Global
//
const (
	XHPTDC8_OK              = 0
	XHPTDC8_DRIVER_DLL_NAME = "xhptdc8_driver_64.dll"
)

func xhptdc8_get_info_by_index(api_name string, hMgr uintptr, device_index int, info_struct uintptr) (error_code uintptr, sys_err error) {

	// Load the driver
	var xhptdc8_driver = syscall.MustLoadDLL(XHPTDC8_DRIVER_DLL_NAME)
	defer xhptdc8_driver.Release()

	// Load and call the function
	xhptdc8_func := xhptdc8_driver.MustFindProc(api_name)

	error_code, _, sys_err = xhptdc8_func.Call(
		uintptr(hMgr),
		uintptr(device_index),
		uintptr(info_struct))

	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_manager_init_parameters
// xhptdc8_get_default_init_parameters
// Xhptdc8_init

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

// DLL Function: extern "C" int xhptdc8_get_default_init_parameters(xhptdc8_manager_init_parameters* init)
func Xhptdc8_get_default_init_parameters(init *Xhptdc8_manager_init_parameters) (error_code uintptr, sys_err error) {

	// Initializations
	const API_NAME = "xhptdc8_get_default_init_parameters"

	// Load the driver
	var xhptdc8_driver = syscall.MustLoadDLL(XHPTDC8_DRIVER_DLL_NAME)
	defer xhptdc8_driver.Release()

	// Load and call the function
	xhptdc8_func, sys_err := xhptdc8_driver.FindProc(API_NAME)
	if sys_err != nil {
		fmt.Println("Error finding API: <", API_NAME, ">, Error: <", sys_err.Error(), ">")
		return error_code, sys_err
	}
	error_code, _, sys_err = xhptdc8_func.Call(
		uintptr(unsafe.Pointer(init)))

	// Check returns
	if sys_err != nil {
		if !strings.Contains(sys_err.Error(), "successfully") {
			fmt.Println("Error calling API: <", API_NAME, ">, Error: <", sys_err.Error(), ">")
			return error_code, sys_err
		}
	}
	if error_code != XHPTDC8_OK {
		fmt.Println("API call: <", API_NAME, ">, Returned Error Code: <", error_code, ">")
	}
	fmt.Println("API call: <", API_NAME, ">, Is Successful")

	// Return
	return error_code, sys_err
}

// XHPTDC8_API void xhptdc8_init(xhptdc8_manager *p_hMgr,
//	 	xhptdc8_manager_init_parameters *params, int *error_code, const char** error_message);
func Xhptdc8_init(p_hMgr *uintptr, params *Xhptdc8_manager_init_parameters, error_code *int, error_message *string) (sys_err error) {

	// Initializations
	const API_NAME = "xhptdc8_init"

	// Load the driver
	var xhptdc8_driver = syscall.MustLoadDLL(XHPTDC8_DRIVER_DLL_NAME)
	defer xhptdc8_driver.Release()

	// Load and call the function
	xhptdc8_func := xhptdc8_driver.MustFindProc(API_NAME)

	error_messagByte := '1' // Just any intialization
	error_messageByteP := &error_messagByte

	dummyVal := '1' // Just any intialization
	*p_hMgr = (uintptr)(unsafe.Pointer(&dummyVal))

	xhptdc8_func.Call(
		uintptr(unsafe.Pointer(p_hMgr)),
		uintptr(unsafe.Pointer(params)),
		uintptr(unsafe.Pointer(error_code)),
		uintptr(unsafe.Pointer(&error_messageByteP)))

	resultStrInBytes := *(*[1024]byte)(unsafe.Pointer(error_messageByteP))
	(*error_message) = ""
	for strIndex := 0; strIndex < 1024; strIndex++ {
		if resultStrInBytes[strIndex] == 0 {
			break
		}
		(*error_message) += string(resultStrInBytes[strIndex])
	}
	return syscall.GetLastError()
}

//_____________________________________________________________________________
// xhptdc8_static_info
// xhptdc8_get_static_info

type Xhptdc8_static_info struct {
	Size                  Crono_int_t
	Version               Crono_int_t
	Board_id              Crono_int_t
	Driver_revision       Crono_int_t
	Driver_build_revision Crono_int_t
	Firmware_revision     Crono_int_t
	Board_revision        Crono_int_t
	Board_configuration   Crono_int_t
	Subversion_revision   Crono_int_t
	Chip_id               [2]Crono_int_t
	Board_serial          Crono_int_t
	Flash_serial_high     Crono_uint_t
	Flash_serial_low      Crono_uint_t
	Flash_valid           byte
	Calibration_date      string
}

type Xhptdc8_static_info_C struct {
	Size                  Crono_int_t
	Version               Crono_int_t
	Board_id              Crono_int_t
	Driver_revision       Crono_int_t
	Driver_build_revision Crono_int_t
	Firmware_revision     Crono_int_t
	Board_revision        Crono_int_t
	Board_configuration   Crono_int_t
	Subversion_revision   Crono_int_t
	Chip_id               [2]Crono_int_t
	Board_serial          Crono_int_t
	Flash_serial_high     Crono_uint_t
	Flash_serial_low      Crono_uint_t
	Flash_valid           byte
	Calibration_date      [20]byte
}

// extern "C" int xhptdc8_get_static_info(xhptdc8_manager hMgr, int index, xhptdc8_static_info* info)
func Xhptdc8_get_static_info(hMgr uintptr, device_index int, static_info *Xhptdc8_static_info) (error_code uintptr, sys_err error) {
	var static_info_C Xhptdc8_static_info_C
	error_code, sys_err = xhptdc8_get_info_by_index("xhptdc8_get_static_info", hMgr, device_index, uintptr(unsafe.Pointer(&static_info_C)))
	if error_code == XHPTDC8_OK {
		static_info.Board_configuration = static_info_C.Board_configuration
		static_info.Board_id = static_info_C.Board_id
		static_info.Board_revision = static_info_C.Board_revision
		static_info.Board_serial = static_info_C.Board_serial
		convert_byte_array_to_string(static_info_C.Calibration_date[:], &static_info.Calibration_date) // Conversion
		static_info.Chip_id = static_info_C.Chip_id
		static_info.Driver_build_revision = static_info_C.Driver_build_revision
		static_info.Driver_revision = static_info_C.Driver_revision
		static_info.Firmware_revision = static_info_C.Firmware_revision
		static_info.Flash_serial_high = static_info_C.Flash_serial_high
		static_info.Flash_serial_low = static_info_C.Flash_serial_low
		static_info.Flash_valid = static_info_C.Flash_valid
		static_info.Size = static_info_C.Size
		static_info.Subversion_revision = static_info_C.Subversion_revision
		static_info.Version = static_info_C.Version
	}
	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_temperature_info_brief
// xhptdc8_get_temperature_info
//
type Xhptdc8_temperature_info struct {
	Size    Crono_int_t
	Version Crono_int_t
	Tdc     [2]Crono_float_t
	Fpga    Crono_int_t
}

// extern "C" int xhptdc8_get_temperature_info(xhptdc8_manager hMgr, int index,
// 		xhptdc8_temperature_info* info)
func Xhptdc8_get_temperature_info(hMgr uintptr, device_index int, temp_info *Xhptdc8_temperature_info) (error_code uintptr, sys_err error) {
	return xhptdc8_get_info_by_index("xhptdc8_get_temperature_info", hMgr, device_index, uintptr(unsafe.Pointer(temp_info)))
}

//_____________________________________________________________________________
// xhptdc8_get_fast_info
// Xhptdc8_fast_info

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

// XHPTDC8_API int xhptdc8_get_fast_info(xhptdc8_manager hMgr, int index, xhptdc8_fast_info * info);
func Xhptdc8_get_fast_info(hMgr uintptr, device_index int, fast_info *Xhptdc8_fast_info) (error_code uintptr, sys_err error) {
	return xhptdc8_get_info_by_index("xhptdc8_get_fast_info", hMgr, device_index, uintptr(unsafe.Pointer(fast_info)))
}

//_____________________________________________________________________________
// xhptdc8_get_param_info
// xhptdc8_param_info

type Xhptdc8_param_info struct {
	Size         Crono_int_t
	Version      Crono_int_t
	Binsize      Crono_double_t
	Channels     Crono_int_t
	Channel_mask Crono_int_t
	Total_buffer int64
}

// extern "C" int xhptdc8_get_param_info(xhptdc8_manager hMgr, int index, xhptdc8_param_info* info)
func Xhptdc8_get_param_info(hMgr uintptr, device_index int, param_info *Xhptdc8_param_info) (error_code uintptr, sys_err error) {
	return xhptdc8_get_info_by_index("xhptdc8_get_param_info", hMgr, device_index, uintptr(unsafe.Pointer(param_info)))
}

//_____________________________________________________________________________
// xhptdc8_get_clock_info
// xhptdc8_clock_info

type Xhptdc8_clock_info struct {
	Size          Crono_int_t
	Version       Crono_int_t
	Cdce_locked   Crono_bool_t
	Cdce_version  Crono_int_t
	Use_ext_clock Crono_bool_t
	Fpga_locked   Crono_bool_t
}

// XHPTDC8_API int xhptdc8_get_clock_info(xhptdc8_manager hMgr, int index, xhptdc8_clock_info* info);
func Xhptdc8_get_clock_info(hMgr uintptr, device_index int, clock_info *Xhptdc8_clock_info) (error_code uintptr, sys_err error) {
	return xhptdc8_get_info_by_index("xhptdc8_get_clock_info", hMgr, device_index, uintptr(unsafe.Pointer(clock_info)))
}
