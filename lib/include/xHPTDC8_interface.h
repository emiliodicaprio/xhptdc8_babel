//
// Header file containing structs and #defines specific for the xHPTDC8
// The current driver version for xHPTDC8 devices is 0.10.0.0
//

/*! \file
*	\brief The functions provided by the API are declared in xHPTDC8_interface.h.
*
*	The API is a DLL with C linkage.
*/
#ifndef XHPTDC8_INTERFACE_H
#define XHPTDC8_INTERFACE_H

#include "crono_interface.h"

/*! \defgroup constants Constants
*/
/*!	\defgroup initialization Initialization
*@{
*/
/*! \defgroup initfuncts Functions for Initialization
* @{
*/
/*! \defgroup defclose #defines for xhptdc8_close()
*
*	xhptdc8_close() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*! \defgroup definit #defines for xhptdc8_init()
*
*	xhptdc8_init() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*/
/*! \defgroup defdefinpar #defines for xhptdc8_get_default_init_parameters()
*
*	xhptdc8_get_default_init_parameters() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*/
/*!@}*/
/*! \defgroup device Structure xhptdc8_device
*/
/*!	\defgroup initparamsstruct Structure xhptdc8manager_init_parameters
*	\brief struct for the initialization of the xHPTDC8
*
*	this structure MUST be completely INITIALIZED
*	@{
*/
/*!	\defgroup apiversion #define for version
*/
/*! \defgroup buffertype #defines for buffer_type
*  \brief type of buffer
*/
/*! \defgroup devicetype #define for device_type
*/
/*!@}*/
/*!@}*/
/*!	\defgroup status Status Information
*	@{
*/
/*! \defgroup statfuncts Functions for Information Retrieval
*	\brief Functions for getting detailed information about the xHPTDC8 board.
*
*	The driver provides functions to retrieve detailed information on the type of board,
*	it's configuration, settings and state. The information is split according to its scope
*	and the computational requirements to query the information from the board.
*@{
*/
/*!	\defgroup defparaminfo #defines for xhptdc8_get_param_info()
*
*	xhptdc8_get_param_info() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!	\defgroup defstatinfo #defines for xhptdc8_get_static_info()
*
*	xhptdc8_get_static_info() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!	\defgroup deffastinfo #defines for xhptdc8_get_fast_info()
*
*	xhptdc8_get_fast_info() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!	\defgroup defslowinfo #defines for xhptdc8_get_slow_info()
*
*	xhptdc8_get_slow_info() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!@}*/
/*!	\defgroup staticinfo Structure xhptdc8_static_info
*	\brief Structure contains static information
*
*	This structure contains information about the board that does not change during run time.
*	It is provided by the function @link statfuncts xhptdc8_get_static_info() @endlink.
*/
/*! \defgroup paraminfo Structure xhptdc8_param_info
*	\brief contains configuration changes
*
*	Structure filled by @link statfuncts xhptdc8_get_param_info() @endlink. This structure
*	contains information that change indirectly due to configuration changes.
*/
/*!	\defgroup fastinfo Structure xhptdc8_fast_info
*	\brief contains fast dynamic information
*
*	This call returns a structure that contains dynamic information that can be obtained
*	within a few microseconds.
*/
/*!@}*/
/*! \defgroup configuration Configuration
*	\brief Configuration of xHPTDC8
*	@{
*/
/*!	\defgroup conffuncts Configuration Functions
*	\brief Functions for the configuration of xHPTDC8
*
*	The device is configured with a configuration structure. The user should first obtain a structure
*	that contains the default settings of the device read from an on board ROM, then modify the
*	structure as needed for the user application and use the result to configure the device.
* @{
*/
/*! \defgroup defconf #defines for xhptdc8_configure()
*
*	xhptdc8_configure() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*! \defgroup defdefconf #defines for xhptdc8_get_default_configuration()
*
*	xhptdc8_get_default_configuration() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*! \defgroup defcurconf #defines for xhptdc8_get_current_configuration()
*
*	xhptdc8_get_current_configuration() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_OK @endlink
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!@}*/
/*! \defgroup confstruct Structure xhptdc8_device_configuration
*	\brief	contains configuration information
*
*	This structure contains the configuration information. It is used in conjunction with
*	@link conffuncts xhptdc8_get_default_configuration(), xhptdc8_get_current_configuration()
*	and xhptdc8_configure() @endlink
*
*	Internally it uses the structures @link trigger xhptdc8_trigger @endlink and @link tiger
*	xhptdc8_tiger_block @endlink
* @{
*/
/*!	\defgroup defdcoffset #defines for dc_offset
*	\brief dc_offset values for various signal standards
*
*	used by @link xhptdc8_device_configuration xhptdc8_device_configuration @endlink.
*/
/*!@}*/
/*! \defgroup trigger Structure xhptdc8_trigger
*	\brief contains trigger settings
*/
/*! \defgroup tiger Structure xhptdc8_tiger_block
*	\brief contains settings of timing generator
* @{
*/
/*!	\defgroup  deftriggersource #defines for sources
*	\brief	mask for choosing the trigger source
*/
/*!@}*/
/*! \defgroup channel Structure xhptdc8_channel
*	\brief contains TDC channel settings
*/
/*!@}*/
/*! \defgroup runtime Run Time Control
*	\brief control functions during run time
*	@{
*/
/*!	\defgroup defstartcap #defines for xhptdc8_start_capture()
*
*	xhptdc8_start_capture() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!	\defgroup defstopcap #defines for xhptdc8_stop_capture()
*
*	xhptdc8_stop_capture() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!	\defgroup defpausecap #defines for xhptdc8_pause_capture()
*
*	xhptdc8_pause_capture() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!	\defgroup defcontcap #defines for xhptdc8_continue_capture()
*
*	xhptdc8_continue_capture() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!@}*/
/*!	\defgroup mainread Readout
*	@{
*/
/*! \defgroup readout Functions for Readout
*	\brief functions for data readout
*	@{
*/
/*! \defgroup defack #defines for xhptdc8_acknowledge()
*
*	xhptdc8_acknowledge() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*! \defgroup defread #defines for xhptdc8_read_hits()
*
*	xhptdc8_read_hits() returns one of the listed values, else
*	- @link funcerrors XHPTDC8_INVALID_DEVICE @endlink
*/
/*!@}*/
/*!	\defgroup readin Structure xhptdc8_read_in
*	\brief The parameters of the read commands
*/
/*! \defgroup strucreadout Structure xhptdc8_read_out
* @{
*/
/*! \defgroup deferror #defines for error_code
*	\brief error code
*/
/*!@}*/
/*!@}*/
/*!	\defgroup funcerrors Function Errors
*
*	All ERRORS must be positive, because the upper byte is used by crono_tools
*/
/*! \defgroup packflags	Packet Flags
*	\brief flags of the packet reporting error conditions
*/

/*! \ingroup apiversion	*/
#define XHPTDC8_API_VERSION 1
#define XHPTDC8_STATIC_INFO_VERSION 1
#define XHPTDC8_FAST_INFO_VERSION 2
#define XHPTDC8_PARAM_INFO_VERSION 1
#define XHPTDC8_TEMP_INFO_VERSION 3
#define XHPTDC8_CLOCK_INFO_VERSION 1
#define XHPTDC8_DEVICE_CONFIG_VERSION 3
#define XHPTDC8_MANAGER_CONFIG_VERSION 1


#define XHPTDC8_DEFAULT_BUFFER_SIZE 0x400000				// 4 MB

/*! \ingroup devices count maximum for grouping	*/
#define	XHPTDC8MANAGER_DEVICES_MAX 8

/*! \ingroup constants Constants
* @{
*/
/*! \brief the number of analog input channels
*
* used by
* - @link confstruct xhptdc8_device_configuration::dc_offset @endlink
* - @link confstruct xhptdc8_device_configuration::channel @endlink
*/
#define XHPTDC8_TDC_CHANNEL_COUNT 8
/*! \brief the number of gates
*
* used by
* - @link confstruct xhptdc8_device_configuration::gating_block[] @endlink
*/
#define XHPTDC8_GATE_COUNT 8
/*! \brief the number of timing generators
*
* used by
* - @link confstruct xhptdc8_device_configuration::gating_block[] @endlink
*/
#define XHPTDC8_TIGER_COUNT 9
/*! \brief the number of triggers.
*
*	Two per analog input, one per digital input plus some specials.
*
*	used by
*	- @link confstruct xhptdc8_device_configuration::trigger[] @endlink
*/
#define XHPTDC8_TRIGGER_COUNT 16		// including "config" for AUTO and ONE
/*!@}*/

/*! \ingroup buffertype
*@{
*/
#define XHPTDC8_BUFFER_ALLOCATE		0	//!< either allocated (only option currently)
#define XHPTDC8_BUFFER_USE_PHYSICAL	1	//!< or physical
/*!@}*/

/*! \ingroup defdcoffset
*@{
*/
#define XHPTDC8_THRESHOLD_BASELINE		+1.32
#define XHPTDC8_THRESHOLD_P_NIM			+0.35
#define XHPTDC8_THRESHOLD_P_CMOS		+1.18
#define XHPTDC8_THRESHOLD_P_LVCMOS_33	+1.18
#define XHPTDC8_THRESHOLD_P_LVCMOS_25	+1.18
#define XHPTDC8_THRESHOLD_P_LVCMOS_18	+0.90
#define XHPTDC8_THRESHOLD_P_TTL			+1.18
#define XHPTDC8_THRESHOLD_P_LVTTL_33	+1.18
#define XHPTDC8_THRESHOLD_P_LVTTL_25	+1.18
#define XHPTDC8_THRESHOLD_P_SSTL_3		+1.18
#define XHPTDC8_THRESHOLD_P_SSTL_2		+1.18
#define XHPTDC8_THRESHOLD_N_NIM			-0.35
#define XHPTDC8_THRESHOLD_N_CMOS		-1.32
#define XHPTDC8_THRESHOLD_N_LVCMOS_33	-1.32
#define XHPTDC8_THRESHOLD_N_LVCMOS_25	-1.25
#define XHPTDC8_THRESHOLD_N_LVCMOS_18	-0.90
#define XHPTDC8_THRESHOLD_N_TTL			-1.32
#define XHPTDC8_THRESHOLD_N_LVTTL_33	-1.32
#define XHPTDC8_THRESHOLD_N_LVTTL_25	-1.25
#define XHPTDC8_THRESHOLD_N_SSTL_3		-1.32
#define XHPTDC8_THRESHOLD_N_SSTL_2		-1.25
/*!@}*/

/*!\ingroup deftriggersource
*	@{
*/
#define XHPTDC8_TRIGGER_SOURCE_NONE				0x00000000	// all sources ignored
#define XHPTDC8_TRIGGER_SOURCE_A				0x00000001	// 0
#define XHPTDC8_TRIGGER_SOURCE_B				0x00000002	// 1
#define XHPTDC8_TRIGGER_SOURCE_C				0x00000004	// 2
#define XHPTDC8_TRIGGER_SOURCE_D				0x00000008	// 3
#define XHPTDC8_TRIGGER_SOURCE_E				0x00000010	// 4
#define XHPTDC8_TRIGGER_SOURCE_F				0x00000020	// 5
#define XHPTDC8_TRIGGER_SOURCE_G				0x00000040	// 6
#define XHPTDC8_TRIGGER_SOURCE_H				0x00000080	// 7
#define XHPTDC8_TRIGGER_SOURCE_TDC1_SYNC		0x00000100	// 8
#define XHPTDC8_TRIGGER_SOURCE_TDC2_SYNC		0x00000200	// 9
#define XHPTDC8_TRIGGER_SOURCE_TDC_EXT_SYNC		0x00000400	// 10
#define XHPTDC8_TRIGGER_SOURCE_ADC1_CNV			0x00000800	// 11
#define XHPTDC8_TRIGGER_SOURCE_ADC2_CNV			0x00001000	// 12
//unused										0x00002000	// 13
#define XHPTDC8_TRIGGER_SOURCE_AUTO				0x00004000	// 14
#define XHPTDC8_TRIGGER_SOURCE_ONE				0x00008000	// 15
/*!@}*/

#define XHPTDC8_TDCHIT_TYPE_RISING						  1
#define XHPTDC8_TDCHIT_TYPE_ERROR						  2		// some error occured
#define XHPTDC8_TDCHIT_TYPE_ERROR_TIMESTAMP_LOST		  4		// at least one TDC timestamp missing due to full buffers (second level Fifo)
#define XHPTDC8_TDCHIT_TYPE_ERROR_ROLLOVER_LOST			  8		// internal rollover flag lost, timestamps invalid
#define XHPTDC8_TDCHIT_TYPE_ERROR_PACKETS_LOST			 16		// at least one TDC timestamp missing due to full buffers (DMA pipeline stalled)
#define XHPTDC8_TDCHIT_TYPE_ERROR_SHORTENED				 32		// at least one TDC timestamp missing due to full buffers (DMA pipeline stalled)
#define XHPTDC8_TDCHIT_TYPE_ERROR_DMA_FIFO_FULL			 64		// at least one TDC timestamp missing due to full buffers (DMA Fifo full)
#define XHPTDC8_TDCHIT_TYPE_ERROR_HOST_BUFFER_FULL		128 	// at least one TDC timestamp missing due to full buffers (ring buffer full)
#define XHPTDC8_TDCHIT_TYPE_ADC_INTERNAL				  1 	// ADC data recorded by internal trigger
#define XHPTDC8_TDCHIT_TYPE_ADC_ERROR					  2		// some error occured
#define XHPTDC8_TDCHIT_TYPE_ADC_ERROR_UNUSED			  4		// unused error flag
#define XHPTDC8_TDCHIT_TYPE_ADC_ERROR_INVALID_TRIGGER	  8		// ADC trigger pulse violated timing requirements, data may be invalid
#define XHPTDC8_TDCHIT_TYPE_ADC_ERROR_DATA_LOST			 16		// at least one ADC sample missing due to full buffers


/*!	\ingroup funcerrors
*	@{
*/
/*! \brief no error encountered
*
* used by
*	- @link defclose xhptdc8_close() @endlink
*	- @link definit xhptdc8_init() @endlink
*	- @link defdefinpar xhptdc8_get_default_init_parameters() @endlink
*	- @link defparaminfo xhptdc8_get_param_info() @endlink
*	- @link defstatinfo xhptdc8_get_static_info() @endlink
*	- @link deffastinfo xhptdc8_get_fast_info() @endlink
*	- @link defdefconf xhptdc8_get_default_configuration() @endlink
*	- @link defcurconf xhptdc8_get_current_configuration() @endlink
*/
#define XHPTDC8_OK							CRONO_OK
#define XHPTDC8_WINDRIVER_NOT_FOUND			CRONO_WINDRIVER_NOT_FOUND
#define XHPTDC8_DEVICE_NOT_FOUND			CRONO_DEVICE_NOT_FOUND
#define XHPTDC8_NOT_INITIALIZED				CRONO_NOT_INITIALIZED
#define XHPTDC8_WRONG_STATE					CRONO_WRONG_STATE
#define XHPTDC8_INVALID_DEVICE				CRONO_INVALID_DEVICE
#define XHPTDC8_BUFFER_ALLOC_FAILED			CRONO_BUFFER_ALLOC_FAILED
#define XHPTDC8_TDC_NO_EDGE_FOUND			CRONO_TDC_NO_EDGE_FOUND
#define XHPTDC8_INVALID_BUFFER_PARAMETERS	CRONO_INVALID_BUFFER_PARAMETERS
#define XHPTDC8_INVALID_CONFIG_PARAMETERS	CRONO_INVALID_CONFIG_PARAMETERS
#define XHPTDC8_TDC_ALIGNMENT_FAILED		CRONO_WINDOW_CALIBRATION_FAILED
#define XHPTDC8_HARDWARE_FAILURE			CRONO_HARDWARE_FAILURE
#define XHPTDC8_INVALID_ADC_MODE			CRONO_INVALID_ADC_MODE
#define XHPTDC8_SYNCHRONIZATION_FAILED		CRONO_SYNCHRONIZATION_FAILED
#define XHPTDC8_DEVICE_OPEN_FAILED			CRONO_DEVICE_OPEN_FAILED
#define XHPTDC8_INTERNAL_ERROR				CRONO_INTERNAL_ERROR
#define XHPTDC8_CALIBRATION_FAILURE			CRONO_CALIBRATION_FAILURE
#define XHPTDC8_INVALID_ARGUMENTS			CRONO_INVALID_ARGUMENTS

/*! \ingroup fastinfo
 * \brief device states
*/
#define XHPTDC8_DEVICE_STATE_CREATED		CRONO_DEVICE_STATE_CREATED
#define XHPTDC8_DEVICE_STATE_INITIALIZED	CRONO_DEVICE_STATE_INITIALIZED
#define XHPTDC8_DEVICE_STATE_CONFIGURED		CRONO_DEVICE_STATE_CONFIGURED
#define XHPTDC8_DEVICE_STATE_CAPTURING		CRONO_DEVICE_STATE_CAPTURING
#define XHPTDC8_DEVICE_STATE_PAUSED			CRONO_DEVICE_STATE_PAUSED
#define XHPTDC8_DEVICE_STATE_CLOSED			CRONO_DEVICE_STATE_CLOSED

/*!	\brief invalid pointer
*
*	The pointer given to a xHPTDC8 driver function was not a valid pointer
*	used by
*	- @link defclose xhptdc8_close() @endlink
*	- @link defstatinfo xhptdc8_get_static_info() @endlink
*	- @link defparaminfo xhptdc8_get_param_info() @endlink
*	- @link defslowinfo xhptdc8_get_slow_info() @endlink
*	- @link deffastinfo xhptdc8_get_fast_info() @endlink
*	- @link defconf xhptdc8_configure() @endlink
*	- @link defdefconf xhptdc8_get_default_configuration() @endlink
*	- @link defcurconf xhptdc8_get_current_configuration() @endlink
*	- @link defstartcap xhptdc8_start_capture() @endlink
*	- @link defstopcap xhptdc8_stop_capture() @endlink
*	- @link defpausecap xhptdc8_pause_capture() @endlink
*	- @link defcontcap xhptdc8_continue_capture() @endlink
*	- @link defread xhptdc8_read_hits() @endlink
*/
/*!@}*/

/*! \ingroup defparaminfo
*/
/*!	\brief	when a capture on a closed card is called
*
* else @link funcerrors XHPTDC8_OK @endlink
*/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifdef XHPTDC8_DRIVER_EXPORTS
#define XHPTDC8_API __declspec(dllexport)
#else
#define XHPTDC8_API __declspec(dllimport)
#endif
#else
#define __int64 long long
#define XHPTDC8_API 
#endif

#define crono_bool_t unsigned char

	/*!\ingroup device
	* \brief struct storing properties of the device in use
	*/
	typedef struct {
		/*! \brief xHPTDC8
		*/
		void * xhptdc8manager;
	} xhptdc8_manager;


	/*!	\ingroup initparamsstruct
	*	\brief struct for the initialization of the xHPTDC8Manager
	*
	*	this structure MUST be completely INITIALIZED
	*/
	typedef struct {
		/* that is increased when the definition of the structure is changed. The increment can be larger than one
		*	to match driver version numbers or similar. Set to 0 for all versions up to first release.
		*/
		/*! \brief the version number
		*
		*	must be set to @link apiversion XHPTDC8_API_VERSION @endlink
		*/
		int version;

		/*!	\brief The minimum size of the DMA buffer.
		*
		*	If set to 0 the default size of 16MB is used.
		*	For the xHPTDC8 only the first entry is used.
		*/
		__int64 buffer_size;

		/*! \brief A variant, for reconfiguring the chip for future extension
		*
		*/
		int variant;

		/*! \brief A constant for the different devices of cronologic CRONO_DEVICE_*.
		*
		*	Initialized by @link initialization xhptdc8_get_default_init_parameters() @endlink.
		*	Must be left unchanged. Please refer to @link devicetype #define for device_type @endlink.
		*/
		int device_type;

		/*! \brief The update delay of the writing pointer after a packet has been send over PCIe.
		*
		*	The base unit is 16 to 32 ns.
		*/
		int dma_read_delay;

		/*! \brief Several xHPTDC8 are used in sync.
		*
		*  If set to 1 enable multiboard operation.
		*  If set to 0 disable multiboard operation.
		*/
		int multiboard;

		/*! \brief Select external 10 MHz reference.
		*
		*  If set to 1 use external 10 MHz reference.
		*  If set to 0 use internal reference.
		*/
		int use_ext_clock;

		/*!
		*/
		int ignore_calibration;

	} xhptdc8manager_init_parameters; //$$ renamed to hp

	/*!	\ingroup initparamsstruct
	*	\brief struct for the initialization of the xHPTDC8Manager
	*
	*	this structure MUST be completely INITIALIZED
	*/
	typedef struct {

		/*
		*
		*/
		/*! \brief
		*
		*
		*/
		long long time;

		/*!	\brief
		*
		*
		*
		*/
		unsigned char channel;

		/*! \brief
		*
		*/
		unsigned char type;

		/*! \brief
		*
		*
		*
		*/
		unsigned short bin;

	} TDCHit;

	/*!	\ingroup readout
	*	\brief Reads packets from the board
	*
	*	Return values are listed @link defread here @endlink.
	*	\param *xhptdc8_mgr is type xhptdc8_manager
	*	\param *hit_buf is type TDCHit
	*	\param read_max is type size_t
	*/
	XHPTDC8_API int xhptdc8_read_hits(xhptdc8_manager *xhptdc8_mgr, TDCHit* hit_buf, size_t read_max);

	/*!	\ingroup initfuncts
	*	\brief finalize the driver for this device
	*
	*	Return values are listed @link defclose here @endlink.
	*	\param *xhptdc8_mgr is type @link xhptdc8_manager xhptdc8_manager @endlink
	*/
	XHPTDC8_API int xhptdc8_close(xhptdc8_manager *xhptdc8_mgr);

	/*!	\ingroup runtime
	*	\brief start timing generator
	*	\param *xhptdc8_mgr is type @link xhptdc8_manager xhptdc8_manager @endlink
	*/
	XHPTDC8_API int xhptdc8_start_tiger(xhptdc8_manager *xhptdc8_mgr, int index);

	/*!	\ingroup runtime
	*	\brief stop timing generator
	*	\param *xhptdc8_mgr is type @link xhptdc8_manager xhptdc8_manager @endlink
	*/
	XHPTDC8_API int xhptdc8_stop_tiger(xhptdc8_manager *xhptdc8_mgr, int index);

	/*!	\ingroup runtime
	*	\brief start data acquisition
	*
	*	Return values are listed @link defstartcap here @endlink.
	*	\param *xhptdc8_mgr is type @link xhptdc8_manager xhptdc8_manager @endlink
	*/
	XHPTDC8_API int xhptdc8_start_capture(xhptdc8_manager *xhptdc8_mgr);

	/*!	\ingroup runtime
	*	\brief	pause data acquisition
	*
	*	Return values are listed @link defpausecap here @endlink.
	*	\param *xhptdc8_mgr is type @link xhptdc8_manager xhptdc8_manager @endlink
	*/
	XHPTDC8_API int xhptdc8_pause_capture(xhptdc8_manager *xhptdc8_mgr);

	/*!	\ingroup runtime
	*	\brief resume data acquisition
	*
	*	Call this to resume data acquisition after a call to xhptdc8_pause_capture.
	*	Return values are listed @link defcontcap here @endlink.
	*	\param *xhptdc8_mgr is type @link xhptdc8_manager xhptdc8_manager @endlink
	*/
	XHPTDC8_API int xhptdc8_continue_capture(xhptdc8_manager *xhptdc8_mgr);

	/*!	\ingroup runtime
	*	\brief	stop data acquisition
	*
	*	Return values are listed @link defstopcap here @endlink.
	*	\param *xhptdc8_mgr is type @link xhptdc8_manager xhptdc8_manager @endlink
	*/
	XHPTDC8_API int xhptdc8_stop_capture(xhptdc8_manager *xhptdc8_mgr);


	/*! \ingroup staticinfo
	*	\brief Structure contains static information
	*
	*	This structure contains information about the board that does not change during run time.
	*	It is provided by the function @link statfuncts xhptdc8_get_static_info() @endlink.
	*/
	typedef struct {

		int size; //!< The number of bytes occupied by the structure
		/*	A version number that is increased when the definition of the structure is changed.
		*	The increment can be larger than one to match driver version numbers or similar.
		*	Set to 0 for all versions up to first release.
		*/
		int version; //!< The version number
		/*!	\brief ID of the board.
		*
		*	This value is passed to the constructor. It is reflected in the	output data.
		*/
		int board_id;
		/*!	\brief encoded version number
		*
		*	The lower three bytes contain a triple level hierarchy of version numbers.
		*	E.g. 0x010103 codes version 1.1.3.
		*
		*	A change in the first digit generally requires
		*	a recompilation of user applications. Change in the second digit denote significant
		*	improvements or changes that don't break compatibility and the third digit changes
		*	with minor bugfixes and the like.
		*/
		int driver_revision;
		/*!	\brief SVN revision of the driver build
		*/
		int driver_build_revision;
		/*	This can be read from a register.
		*/
		int firmware_revision; //!< Revision number of the FPGA configuration.
		/*!	\brief board revision number
		*
		*	The board revision number can be read from a register. It is a four bit number
		*	that changes when the schematic of the board is changed.
		*	- 0: Experimental first board Version. Labeled "Rev. 1"
		*	- 2: First commercial Version. Labeled "Rev. 2"
		*/
		int board_revision;
		/*!	\brief Describes the schematic configuration of the board.
		*
		*	The same board schematic can be populated in multiple variants. This is a eight
		*	bit code that can be read from a register.
		*/
		int board_configuration;
		/*	A number to track builds of the firmware in more detail than the firmware revision. It changes
		*	with every change in the firmware, even if there is no visible effect for the user. The subversion
		*	revision number can be read from a register.
		*/
		int subversion_revision; //!< Subversion revision id of the FPGA configuration.
		/*  This is the chipID as read from the 16 bit TDC chip id register at SPI address 0x83.
		*	This value should be cached.
		*/
		int chip_id[2]; //!< 16bit factory ID of the TDC chip.
		/*!	\brief Serial number
		*
		*	with year and running number in 8.24 format. The number is identical to the one
		*	printed on the silvery sticker on the board.
		*/
		int board_serial;
		unsigned int flash_serial_high;	//!< high 32 bits of 64 bit manufacturer serial number of the flash chip
		unsigned int flash_serial_low;	//!< low 32 bits of 64 bit manufacturer serial number of the flash chip
		/*!	\brief Flash data is valid and in use
		*
		*	If not 0 the driver found valid calibration data in the flash on the board and is using it.
		*/
		int flash_valid;

		/*! \brief calibration date
		*
		* DIN EN ISO 8601 string YYYY-MM-DD HH:DD describing the time when the card was calibrated.
		*/
		char calibration_date[20];
	} xhptdc8_static_info;

	/*! \ingroup statfuncts
	*	\brief contains static information
	*
	*	Gets a structure that contains information about the board that does not change during
	*	run time. Return values are listed @link defstatinfo here @endlink.
	*	\param *xhptdc8_mgr of type xhptdc8_manager
	*	\param *info of type xhptdc8_static_info
	*/
	XHPTDC8_API int xhptdc8_get_static_info(xhptdc8_manager *xhptdc8_mgr, int index, xhptdc8_static_info* info);

	/*! \ingroup fastinfo
	*	\brief contains fast dynamic information
	*
	*	This call returns a structure that contains dynamic information that can be obtained
	*	within a few microseconds.
	*/
	typedef struct {
		int size; //!< The number of bytes occupied by the structure
		/*	A version number that is increased when the definition of the structure is changed.
		The increment can be larger than one to match driver version numbers or similar. Set
		to 0 for all versions up to first release.
		*/
		int version; //!< The version number
		/*! \brief Speed of the FPGA fan.
		*
		* Reports 0, if no fan is present.
		*/
		int fpga_rpm;
		/*!	\brief Alert bits from temperature sensor and the system monitor
		*
		*	- bit 0:	TDC over temperature alarm
		*/
		int alerts;
		/*! \brief organizes power supply of PCIe lanes.
		*/
		int pcie_pwr_mgmt;
		int pcie_link_width; //!< Number of PCIe lanes the card uses.
		/*!	\brief Maximum size for a single PCIe transaction
		*  in bytes. Depends on system configuration.
		*/
		int pcie_max_payload;
		//!< Current state of the device
		/*! \brief current state of the device, i.e. CAPTURING, PAUSED, etc.
		*/
		int state;
	} xhptdc8_fast_info;

	/*! \ingroup statfuncts
	*	\brief returns fast dynamic information
	*
	*	This call gets a structure that contains dynamic information that can be obtained within a
	*	few microseconds. Return values are listed @link deffastinfo here @endlink.
	*	\param *xhptdc8_mgr of type xhptdc8_manager
	*	\param *info of type xhptdc8_fast_info
	*/
	XHPTDC8_API int xhptdc8_get_fast_info(xhptdc8_manager *xhptdc8_mgr, int index, xhptdc8_fast_info * info);

	/*! \ingroup paraminfo
	*	\brief contains configuration changes
	*
	*	Structure filled by @link statfuncts xhptdc8_get_param_info() @endlink. This structure
	*	contains information that change indirectly due to configuration changes.
	*/
	typedef struct {
		int size; //!< The number of bytes occupied by the structure
		/* is increased when the definition of the structure is changed.
		The increment can be larger than one to match driver version numbers or similar. Set
		to 0 for all versions up to first release.
		*/
		int version; //!< The version number
		/*!	\brief Binsize (in ps) of the measured TDC data.
		*
		*	The TDC main clk is running at a frequency of 76.8 GHz
		*  resulting in a binsize of ~13.0208 ps.
		*/
		double binsize;
		/*!	\brief Number of channels in the current TDC mode
		*
		* Currently fixed at 8.
		*/
		int channels;
		/*! \brief bit assignment of each enabled input channel.
		*
		*	Mask assigns a certain bit to each enabled input channel.
		*/
		int channel_mask;
		__int64 total_buffer; //!< The total amount of DMA buffer in bytes.
	} xhptdc8_param_info;

	/*! \ingroup statfuncts
	*	\brief returns configuration changes
	*
	*	Gets a structure that contains information that changes indirectly due to configuration
	*	changes. Return values are listed @link defparaminfo here @endlink.
	*	\param *xhptdc8_mgr of type xhptdc8_manager
	*	\param *info of type xhptdc8_device
	*/
	XHPTDC8_API int xhptdc8_get_param_info(xhptdc8_manager *xhptdc8_mgr, int index, xhptdc8_param_info* info);


	/*! \ingroup tempinfo
	*	\brief contains temperature measurements
	*
	*	CAVE: TDC temp diode takes about 2.5 us after wakeup from power down to provide a valid measurement
	*	Structure filled by @link statfuncts xhptdc8_get_temperature_info() @endlink.
	*/
	typedef struct {
		int size; //!< The number of bytes occupied by the structure
		/* is increased when the definition of the structure is changed.
		The increment can be larger than one to match driver version numbers or similar. Set
		to 0 for all versions up to first release.
		*/
		int version;	//!< The version number
		float tdc[2];	//!< Temperature read from each TDC's internal diode
		int fpga;		//!< Temperature read from the FPGA's internal ring oscillator
	} xhptdc8_temperature_info;

	XHPTDC8_API int xhptdc8_get_temperature_info(xhptdc8_manager *xhptdc8_mgr, int index, xhptdc8_temperature_info* info);

	//!< external 10 MHz provided at J12 (no longer supported)
#define XHPTDC8_CLK_J12 1
	//!< internal 10 MHz oscillator
#define XHPTDC8_CLK_OSC 2
	//!< external 10 MHz provided at the internal LEMO connector 
#define XHPTDC8_CLK_LEMO 4

	/*! \ingroup tempinfo
	*	\brief contains temperature measurements
	*
	*	Structure filled by @link statfuncts xhptdc8_get_temperature_info() @endlink.
	*/
	typedef struct {
		int size; //!< The number of bytes occupied by the structure
		/* is increased when the definition of the structure is changed.
		The increment can be larger than one to match driver version numbers or similar. Set
		to 0 for all versions up to first release.
		*/
		int version;				//!< The version number
		crono_bool_t cdce_locked;	//!< CDCE62005 PLL locked
		int cdce_version;			//!< CDCE62005 version
		int clock_source;			//!< 1: J12 clock, 2: internal 10 MHz, 4: LEMO clock
		crono_bool_t fpga_locked;	//!< FPGA datapath PLL locked
	} xhptdc8_clock_info;

	XHPTDC8_API int xhptdc8_get_clock_info(xhptdc8_manager *xhptdc8_mgr, int index, xhptdc8_clock_info* info);

	/*! \ingroup readout
	*	\brief returns most recent error message
	*	\param *device_manager is type xhptdc8_manager
	*/
	XHPTDC8_API const char* xhptdc8_get_last_error_message(xhptdc8_manager *xhptdc8_mgr);

	/*!	\ingroup readout
	*	\brief returns the type of the device
	*
	*	@link devicetype CRONO_DEVICE_XHPTDC8 @endlink
	*/
	XHPTDC8_API int xhptdc8_get_device_type(xhptdc8_manager *xhptdc8_mgr);

	/*!	\ingroup channel
	*	\brief Contains TDC channel settings
	*/
	typedef struct {
		crono_bool_t enable;			//!< Enable TDC channel.
		crono_bool_t rising;			//!< Set whether to record rising or falling edges.
	} xhptdc8_channel;

	/*! \brief Gate deactivated */
#define XHPTDC8_GATE_OFF 0 
	/*! \brief Gate activated */
#define XHPTDC8_GATE_ON 1
	/*! \brief TiGeR deactivated */
#define XHPTDC8_TIGER_OFF 0
	/*! \brief Pulse height approx. 2 V. LEMO only usable as output */
#define XHPTDC8_TIGER_OUTPUT 1
	/*! \brief Pulse height approx. 1 V. LEMO may be used as input with OR function when external pulse rate is low. */
#define XHPTDC8_TIGER_BIDI 2
	/*! \brief bipolar pulse */
#define XHPTDC8_TIGER_BIPOLAR 3
	/*! \brief maximum length of bipolar TiGeR pulses */
#define XHPTDC8_TIGER_MAX_BIPOLAR_PULSE_LENGTH 15
	/*!	\ingroup gating
	*	\brief contains settings of gating block
	*/
	typedef struct {
		/*! \brief activates tiger block
		*
		* TiGer output buffer is tristated if not enabled
		*
		*  default value: false
		*/
		int mode;
		/*! \brief set pulse polarity
		*
		*  default value: false
		*/
		crono_bool_t negate;
		/*!	\brief enables/disables retrigger setting
		*
		*	If retriggering is enabled the timer is reset to the value of the start
		*	parameter, whenever the input signal is set while waiting to reach the stop time.
		*
		*  default value: false
		*/
		crono_bool_t retrigger;
		crono_bool_t extend;				//!< not implemented
		/*! \brief Precursor
		*
		*  Number of 6.6ns clock cycles before the tiger output goes active
		*	relative to the trigger signal.
		*/
		int start;
		/*! \brief postcursor
		*
		*  Number of 6.6ns clock cycles before the tiger output goes inactive
		*	relative to the trigger signal.
		*/
		int stop;
		/*!	\brief mask for choosing the trigger source
		*
		*	A bit mask with a bit set for all trigger sources that can trigger this channel. Default is
		*	XHPTDC8_TRIGGER_SOURCE_A. One can choose a from a source @link deftriggersource here @endlink.
		*/
		int sources;
	} xhptdc8_tiger_block;

	/* low res trigger config */
	/*!\ingroup trigger
	*	\brief contains trigger settings
	*/
	typedef struct {
		crono_bool_t falling;	//!< triggers on falling edges
		crono_bool_t rising;	//!< triggers on rising edges
	} xhptdc8_trigger;

	/* ADC channel config */
	/*!\ingroup adccfg
	*	\brief contains ADC channel settings
	*/
	typedef struct {
		crono_bool_t enable;					//!< enable ADC measurements
		crono_bool_t watchdog_readout;			//!< send watchdog measurements

		int watchdog_interval;					//!< number of 150 MHz clock cycles between watchdog triggers
		double trigger_offset;					//!< trigger threshold of ADC sample trigger
	} xhptdc8_adc_channel;

	//!< use TiGeR pulse for alignment (pulses are present on LEMO inputs during alignment).
#define XHPTDC8_ALIGN_TIGER 0
	//!< use internal alignment pins for alignment (no pulses are present on LEMO inputs during alignment).
#define XHPTDC8_ALIGN_PIN 1
	//!< use internal alignment pins for alignment and do not disable after alignment (internal use only).
#define XHPTDC8_ALIGN_RESERVED 2


	/*! \ingroup grpconfstruct Structure xhptdc8_grouping_configuration
	* /brief Configure the optional grouping functionality
	*
	*/
	struct xhptdc8_grouping_configuration { //$$ Changed
		/*! \brief Das ist der Kanel auf den Getriggert wird.
		*/
		int trigger_channel; // <= i32TriggerChannel

		/*! \brief  -1 für disable; Ansonsten kanal relativ zu dem die Zeiten berechnet werden.
		*/	
		int zero_channel;// <= i32TimeZeroChannel
					
		/*! \brief Der Nullpunkt wird um dieses Intervall nach einer Flanke auf dem 0 - Kanal gesetzt.
		*/
		__int64 zero_channel_offset; // <= i64OffsetTimeZeroChannel_ps
		
		/*! \brief Der Anfang des Zeitbereichs für die Gruppe.
		*/
		__int64 range_start; // <= i64GroupRangeStart_ps
		
		/*! \brief Das Ende des Zeitbereichs für die Gruppe.
		*/
		__int64 range_stop; // <= i64GroupRangeEnd_ps
		
		/*! \brief Nach einem Trigger wird so lange wie hier eingestellt ist keine Gruppe erzeugt.
		* Vorschlag: Entfällt, das geht mit einem Gating - Block auf dem Trigger - Kanal.Dann muss es intern auf 0 gesetzt werden.
		*/
		__int64 trigger_deadtime; // <= i64TriggerDeadTime_ps
			
		/*! \brief Gruppe wird nur erzeugt, wenn im folgenden Zeitfenster mindestens ein Hit ist.
		*/
		crono_bool_t require_window_hit; // <= i32AdvancesTriggger Channel
		/*! \brief 
		*/
		__int64 window_start;// <= i64AdvancedTriggerChannelWindowStart_ps;
		/*! \brief 
		*/
		__int64 window_stop; // <= i64AdvancedTriggerChannelWindowStop_ps;

		/*! \brief (Hierfür braucht es noch defines)
		XHPTDC8_VET_OFF 0 = kein VETO
		XHPTDC8_VET_INSIDE 1 = alles zwischen veto_start und veto_stop wird verworfen
		XHPTDC8_VET_OUTSIDE 2 = alles außerhalb veto_start und veto_stop wird verworfen		
		*/
		crono_bool_t veto_mode; // <= iUseVeto
		/*! \brief Das soll in ps angegeben werden.Es ist verwirrend, da die Einheit zu wecheln.Wir können es intern umrechnen, wenn wir den eigentlich code nicht anfassen wollen.
		*/
			__int64 veto_start; // <= i64VetoStart_bins
		/*! \brief Das soll in ps angegeben werden.Es ist verwirrend, da die Einheit zu wecheln.Wir können es intern umrechnen, wenn wir den eigentlich code nicht anfassen wollen.
		*/
		__int64 veto_stop; // <= i64VetoStop_bins
			
		/*! \brief Angaben des veto fensters sind relativ zum 0 - Kanal
		*/
		crono_bool_t veto_relative_to_zero; // <= bVetoIsRelativeToTimeZeroChannel;
		
			/*! \brief Muss auf false bleiben, kann später mal benutzt werden, um auch überlappende Gruppen zu erzeugen
			*/
		bool overlap = false; // <= bAllowOverlap;

		/*
		*/
		bool enable = false; 
		
	} ; //$$ Removed xhptdc8_grouping_configuration


	/*! \ingroup confstruct Structure xhptdc8_device_configuration
	*	\brief	contains configuration information
	*
	*	This structure contains the configuration information. It is used in conjunction with
	*	@link conffuncts xhptdc8_get_default_configuration(), xhptdc8_get_current_configuration()
	*	and xhptdc8_configure() @endlink
	*
	*	Internally it uses the structures @link trigger xhptdc8_trigger @endlink and @link tiger
	*	xhptdc8_tiger_block @endlink
	*/
	typedef struct {
		/*! \brief The number of bytes occupied by the structure
		*/
		int size; //!< The number of bytes occupied by the structure
				  /*! \brief A version number
				  *
				  * that is increased when the definition of the structure is changed. The increment
				  * can be larger than one to match driver version numbers or similar. Set to 0 for
				  * all versions up to first release.
				  */
		int version;
		/** \brief component to create a trigger either periodically or randomly.
		*
		*  To be exact, there are two parameters M = @link auto_trigger_period auto_trigger_period @endlink
		*	and N = @link auto_trigger_random_exponent auto_trigger_random_exponent @endlink
		*	that result in a distance between triggers of
		*
		*		T = 1 + M + [1...2^N]
		*
		*	clock cycles.
		*
		*		0 <= M < 2^32
		*
		*		0 <= N < 32
		*
		*  there is no enable or reset as the usage of this trigger can be configured in the channels.
		*/
		///@{
		int auto_trigger_period;
		/** \brief component to create a trigger either periodically or randomly.
		*
		*  To be exact, there are two parameters M = @link auto_trigger_period auto_trigger_period @endlink
		*	and N = @link auto_trigger_random_exponent auto_trigger_random_exponent @endlink
		*	that result in a distance between triggers of
		*
		*		T = 1 + M + [1...2^N]
		*
		*	clock cycles.
		*
		*		0 <= M < 2^32
		*
		*		0 <= N < 32
		*
		*  there is no enable or reset as the usage of this trigger can be configured in the channels.
		*/
		int auto_trigger_random_exponent;
		///@}

		/*! \brief Set DAC channels for A - H.
		*
		*	dc_offset[0 - 3] : TDC 1 A - D
		*	dc_offset[4 - 7] : TDC 2 A - D
		*
		*	Set to a value between -1.32V and +1.98V. This should be close to 50% of the height of your pulses on
		*	the inputs. Examples for various signaling standards are defined in @link defdcoffset #defines for
		*	dc_offset @endlink. The inputs are AC coupled. This means that for pulse inputs the absolute voltage is
		*	not important. it is rather the relative pulse amplitude that causes the input circuits to switch.
		*	dc_offset for an input must be set to the relative switching voltage for the input standard in use. If
		*	the pulses are negative, a negative switching threshold must be set and vice versa.
		*/
		double thresholds[XHPTDC8_TDC_CHANNEL_COUNT];
		xhptdc8_trigger trigger[XHPTDC8_TRIGGER_COUNT]; //!< Configuration of external trigger sources
		xhptdc8_tiger_block gating_block[XHPTDC8_GATE_COUNT]; //!< configuration of the gating blocks
		xhptdc8_tiger_block tiger_block[XHPTDC8_TIGER_COUNT]; //!< configuration of the timing generator blocks
		xhptdc8_channel channel[XHPTDC8_TDC_CHANNEL_COUNT]; //!< configure polaritiy, type and threshold for the TDC channels

		/*! \brief Configure ADC channel.
		*/
		xhptdc8_adc_channel adc_channel;

		/*! \brief Configure TDC alignemet
		*
		*  If set to 1 skip TDC calibration.
		*  If set to 0 do TDC calibration (default).
		*/
		crono_bool_t skip_alignment;

		/*! \brief Select TDC alignment source
		* If set to XHPTDC8_ALIGN_TIGER use TiGeR pulse for alignment (pulses are present on LEMO inputs during alignment).
		* If set to XHPTDC8_ALIGN_PIN use internal alignment pins for alignment (no pulses are present on LEMO inputs during alignment).
		* If set to XHPTDC8_ALIGN_RESERVED use internal alignment pins for alignment and do not disable after alignment (internal use only).
		*/
		int alignment_source;

	} xhptdc8_device_configuration;


	/*! \ingroup confstruct Structure xhptdc8_manager_configuration
	*	\brief	contains global configuration information
	*
	*	This structure contains the global configuration information. It is used in conjunction with
	*	@link conffuncts xhptdc8_get_default_configuration(), xhptdc8_get_current_configuration()
	*	and xhptdc8_configure() @endlink
	*
	*	Internally it uses the structures @link grouping xhptdc8_grouping_configuration @endlink and @link device_configs
	*	xhptdc8_device_configuration @endlink
	*/
	typedef struct {
		/*! \brief The number of bytes occupied by the structure
		*/
		int size; //!< The number of bytes occupied by the structure
				  /*! \brief A version number
				  *
				  * that is increased when the definition of the structure is changed. The increment
				  * can be larger than one to match driver version numbers or similar. Set to 0 for
				  * all versions up to first release.
				  */
		int version;
		
		/** \brief xhptdc_device_configuration device_configs
		*
		*/
		xhptdc8_device_configuration device_configs[XHPTDC8MANAGER_DEVICES_MAX];

		/** \brief xhptdc8_grouping_configuration grouping
		*
		*/
		xhptdc8_grouping_configuration grouping;

		void* bin_to_ps;	//$$ added from user guide

	} xhptdc8_manager_configuration;

	/*!	\ingroup conffuncts
	*	\brief gets default manager configuration
	*
	*	Copies the default configuration to the specified config pointer. Return values are listed @link defdefconf here @endlink.
	*	\param *xhptdc8_mgr of type xhptdc8_manager
	*	\param *manager_config of type xhptdc8_manager_configuration
	*/
	XHPTDC8_API int xhptdc8_get_default_configuration(xhptdc8_manager *xhptdc8_mgr, xhptdc8_manager_configuration *mgr_config);
	/*!	\ingroup conffuncts
	*	\brief gets current manager configuration
	*
	*	Copies the current configuration to the specified config pointer. Return values are listed @link defcurconf here @endlink.
	*	\param *xhptdc8_mgr of type xhptdc8_manager
	*	\param *mgr_config of type xhptdc8_manager_configuration
	*/
	XHPTDC8_API int xhptdc8_get_current_configuration(xhptdc8_manager *xhptdc8_mgr, xhptdc8_manager_configuration *mgr_config);
	/*!	\ingroup conffuncts
	*	\brief configures xHPTDC8 device
	*
	*	Return values are listed @link defconf here @endlink.
	*	\param *xhptdc8_mgr of type xhptdc8_manager
	*	\param *manager_config of type xhptdc8_manager_configuration
	*/
	/* the config information is copied, so can be changed after the
	called */
	XHPTDC8_API int xhptdc8_configure(xhptdc8_manager *xhptdc8_mgr, xhptdc8_manager_configuration *mgr_config);


	/*!	\ingroup initfuncts
	*	\brief Return the number of boards that are supported by this driver in the system.
	*	\param *error_code is type int
	*	\param **error_message is type const char
	*/
	XHPTDC8_API int xhptdc8_count_devices(int *error_code, char** error_message);

	/*!	\ingroup initfuncts
	* @{
	*/
	/*!	\brief Sets up the standard parameters
	*
	*	Gets a set of default parameters for @link xhptdc8_init xhptdc8_init() @endlink . This must always
	*	be used to initialize the @link initparamsstruct xhptdc8manager_init_parameter() @endlink structure.
	*	Return values are listed @link defdefinpar here @endlink.
	*	\param init is type *xhptdc8manager_init_parameters
	*/
	XHPTDC8_API int xhptdc8_get_default_init_parameters(xhptdc8manager_init_parameters *init); //$$ struct renamed to hp

	/*!	\brief Open and initialize the xHPTDC8 board with the given index.
	*
	*	With error_code and error_message the user must provide pointers where error information should be
	*	written by the driver. Return values are listed @link definit here @endlink.
	*	\param *params type xhptdc8manager_init_parameters
	*	\param *error_code is type int
	*	\param **error_message is type char. The buffer for the error message has to contain at least 80 chars.
	*/
	XHPTDC8_API xhptdc8_manager *xhptdc8_init(xhptdc8manager_init_parameters *params, int *error_code, const char** error_message);

	/*!	\ingroup statfuncts
	*	\brief Returns the driver version, same format as xhptdc8_static_info::driver_revision
	*/
	XHPTDC8_API int xhptdc8_get_driver_revision();

	/*!	\ingroup statfuncts
*	\brief Returns the driver version including SVN build revision as a string with format x.y.z.svn
	*/
	XHPTDC8_API const char* xhptdc8_get_driver_revision_str();

	/*! \brief
	*/
	XHPTDC8_API const char* xhptdc8_device_state_to_str(int state);

#ifdef __cplusplus
}
#endif

#endif
