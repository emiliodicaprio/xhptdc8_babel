package xhptdc8_wrapper

import (
	"fmt"
	"strings"
	"syscall"
	"unsafe"
)

//_____________________________________________________________________________
// Global Variables
//
const (
	XHPTDC8_OK              = 0
	XHPTDC8_DRIVER_DLL_NAME = "xhptdc8_driver_64.dll"
)

//_____________________________________________________________________________
// xhptdc8_manager_init_parameters
// xhptdc8_get_default_init_parameters
// Xhptdc8_init

type Xhptdc8_manager_init_parameters struct {
	Version            int
	Buffer_size        int64
	Variant            int
	Device_type        int
	Dma_read_delay     int
	Multiboard         uint8
	Use_ext_clock      uint8
	Ignore_calibration uint8
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
	Size                  int
	Version               int
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

// extern "C" int xhptdc8_get_static_info(xhptdc8_manager hMgr, int index,
//	xhptdc8_static_info* info)
func Xhptdc8_get_static_info(hMgr uintptr, device_index int, info *Xhptdc8_static_info) (error_code uintptr, sys_err error) {

	// Initializations
	const API_NAME = "xhptdc8_get_static_info"

	// Load the driver
	var xhptdc8_driver = syscall.MustLoadDLL(XHPTDC8_DRIVER_DLL_NAME)
	defer xhptdc8_driver.Release()

	// Load and call the function
	xhptdc8_func := xhptdc8_driver.MustFindProc(API_NAME)

	error_code, _, sys_err = xhptdc8_func.Call(
		uintptr(hMgr),
		uintptr(device_index),
		uintptr(unsafe.Pointer(info)))

	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_temperature_info_brief
// xhptdc8_get_temperature_info
//
type Xhptdc8_temperature_info struct {
	Size    int
	Version int
	Tdc     [2]float32
	Fpga    int
}

// extern "C" int xhptdc8_get_temperature_info(xhptdc8_manager hMgr, int index,
// 		xhptdc8_temperature_info* info)
func Xhptdc8_get_temperature_info(hMgr uintptr, device_index int, temp *Xhptdc8_temperature_info) (error_code uintptr, sys_err error) {

	// Initializations
	const API_NAME = "xhptdc8_get_temperature_info"

	// Load the driver
	var xhptdc8_driver = syscall.MustLoadDLL(XHPTDC8_DRIVER_DLL_NAME)
	defer xhptdc8_driver.Release()

	// Load and call the function
	xhptdc8_func := xhptdc8_driver.MustFindProc(API_NAME)

	error_code, _, sys_err = xhptdc8_func.Call(
		uintptr(hMgr),
		uintptr(device_index),
		uintptr(unsafe.Pointer(temp)))

	return error_code, sys_err
}

//_____________________________________________________________________________
// xhptdc8_get_fast_info
// Xhptdc8_fast_info

type Xhptdc8_fast_info struct {
	Size             int
	Version          int
	Fpga_rpm         int
	Alerts           int
	Pcie_pwr_mgmt    int
	Pcie_link_width  int
	Pcie_max_payload int
	State            int
}

// XHPTDC8_API int xhptdc8_get_fast_info(xhptdc8_manager hMgr, int index, xhptdc8_fast_info * info);
func Xhptdc8_get_fast_info(hMgr uintptr, device_index int, fasr_info *Xhptdc8_fast_info) (error_code uintptr, sys_err error) {

	// Initializations
	const API_NAME = "xhptdc8_get_fast_info"

	// Load the driver
	var xhptdc8_driver = syscall.MustLoadDLL(XHPTDC8_DRIVER_DLL_NAME)
	defer xhptdc8_driver.Release()

	// Load and call the function
	xhptdc8_func := xhptdc8_driver.MustFindProc(API_NAME)

	error_code, _, sys_err = xhptdc8_func.Call(
		uintptr(hMgr),
		uintptr(device_index),
		uintptr(unsafe.Pointer(fasr_info)))

	return error_code, sys_err
}
