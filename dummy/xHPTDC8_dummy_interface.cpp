//
// 
#include "pch.h"
#include "xHPTDC8_dummy_interface.h"
#include "xHPTDC8_interface.h"

//_____________________________________________________________________________
// Driver Information APIs
// 

/*
* Returns the driver version, same format as xhptdc8_static_info.driver_revision. 
* This function does not require a xHPTDC8 board to be present.
*/
extern "C" int xhptdc8_get_driver_revision()
{
	return 0;
}

/*
* Returns the driver version including SVN build revision as a string.
*/
extern "C" const char* xhptdc8_get_driver_revision_str()
{
	return VER_FILE_VERSION_STR;	
}

/*
* Returns the number of boards present in the system that are supported by this driver.
*/
extern "C" int xhptdc8_count_devices(int* error_code, char** error_message)
{
	if (nullptr == error_code)
		return XHPTDC8_INVALID_ARGUMENTS;
	
	if (nullptr == error_message)
		return XHPTDC8_INVALID_ARGUMENTS;

	*error_code = 0;
	*error_message = (char*)MSG_OK; //$$ Memory allocation? Mention that in the guide.
	return 1;
}

//_____________________________________________________________________________
// Initialization APIs
//

/*
* Finalizes the driver for this device.
*/
extern "C" int xhptdc8_close(xhptdc8_manager* xhptdc8_mgr)
{
	return XHPTDC8_OK;
}

/*
* Sets up the standard parameters.Gets a set of default parameters for xhptdc8_init().This must
* cronologic GmbH& Co.KG 12 xHPTDC8 User Guide 1.8.0_draft_5 always be used 
* to initialize the xhptdc8_init_parameter() structure.
*/
extern "C" int xhptdc8_get_default_init_parameters(xhptdc8manager_init_parameters* init)
{
	if (nullptr == init)
		return XHPTDC8_INVALID_ARGUMENTS;

	init->version = XHPTDC8_API_VERSION;
	init->buffer_size = 0; // the default size of 16 MByte is used
	init->variant = 0;
	init->device_type = CRONO_DEVICE_XHPTDC8 ;
	init->dma_read_delay = 0;
	init->multiboard = 0;
	init->use_ext_clock = 0; //0 use internal reference
	init->ignore_calibration = 0;

	return XHPTDC8_OK;
}

/*
* Opens and initializes the xHPTDC8 board with the given index. 
* The user must provide pointers to memory locations where the driver 
* can store return values.
* error_code shall point to an integer for the error code.
* error_message must point to a pointer to char.The driver will allocate
* a buffer for zero terminated error messages and store the address of the
* buffer in the location provided by the user.
* The paramter params is a structure of type xhptdc8_init_parameters that 
* must be completely initialized.
*/
extern "C" xhptdc8_manager* init(xhptdc8manager_init_parameters* params,
	int* error_code, char** error_message)
{
	if (nullptr != error_message)
		*error_message = (char*)lastErrorMessageDummy;

	if (nullptr == error_code)
		return nullptr;

	if (nullptr == params)
	{
		*error_code = XHPTDC8_INVALID_ARGUMENTS;
		return nullptr;
	}

	params->version = XHPTDC8_API_VERSION;
	params->buffer_size = 0;
	params->variant = 0;
	params->device_type = CRONO_DEVICE_XHPTDC8; 
	params->dma_read_delay = 0;
	params->multiboard = 0;
	params->use_ext_clock = 0; //0 use internal reference
	params->ignore_calibration = 0;
	//$$ review return
	return XHPTDC8_OK;
}

//_____________________________________________________________________________
// Status Information APIs
//

/*
* Returns the type of the device as CRONO_DEVICE_XHPTDC8.
*/
extern "C" int xhptdc8_get_device_type(xhptdc8_manager* xhptdc8_mgr)
{
	return CRONO_DEVICE_XHPTDC8;
}

/*
* Returns most recent error message.
*/
extern "C" const char* xhptdc8_get_last_error_message(xhptdc8_manager* xhptdc8_mgr)
{
	if (nullptr == xhptdc8_mgr)
		return InvalidDevMgr;

	return lastErrorMessageDummy;
}

/*
* Returns fast dynamic information.
* This call gets a structure that contains dynamic information that can 
* be obtained within a few microseconds.
*/
extern "C" int xhptdc8_get_fast_info(xhptdc8_manager* xhptdc8_mgr, int index,
		xhptdc8_fast_info* info)
{
	if (nullptr == xhptdc8_mgr)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (index < 0)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == info)
		return XHPTDC8_INVALID_ARGUMENTS;

	info->size = sizeof(xhptdc8_fast_info);
	info->version = XHPTDC8_FAST_INFO_VERSION;

	info->alerts = 0 ;
	info->fpga_rpm = 0 ;
	info->pcie_pwr_mgmt = 0 ; // Always 0.
	info->pcie_link_width = 1 ; // Should always be 1 for the xHPTDC8.
	info->pcie_max_payload = 0 ;
	info->state = XHPTDC8_DEVICE_STATE_CREATED; // Dummy value
	
	return XHPTDC8_OK;
}

/*
* Returns configuration changes. 
* Gets a structure that contains information that changes indirectly due to configuration changes.
*/
extern "C" int xhptdc8_get_param_info(xhptdc8_manager* xhptdc8_mgr, int index,
	xhptdc8_param_info* info)
{
	if (nullptr == xhptdc8_mgr)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (index < 0)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == info)
		return XHPTDC8_INVALID_ARGUMENTS;

	info->size = sizeof(xhptdc8_param_info);
	info->version = XHPTDC8_PARAM_INFO_VERSION;
	info->binsize = 0;
	info->channels = XHPTDC8_TDC_CHANNEL_COUNT; // 8
	info->channel_mask = 0;
	info->total_buffer = 0;

	return XHPTDC8_OK;
}

/*
* Contains static information.
* Gets a structure that contains information about the board that 
* does not change during run time.
*/
extern "C" int xhptdc8_get_static_info(xhptdc8_manager* xhptdc8_mgr, int index,
	xhptdc8_static_info* info)
{
	if (nullptr == xhptdc8_mgr)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (index < 0)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == info)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == info->calibration_date)
		return XHPTDC8_INVALID_ARGUMENTS;

	info->size = sizeof(xhptdc8_static_info);
	info->version = XHPTDC8_STATIC_INFO_VERSION;
	info->board_id = 10;
	info->driver_revision = VER_FILE_VERSION;
	info->driver_build_revision = VERSION_BUILD; //$$ check that
	info->firmware_revision = 0;
	info->board_revision = 0;
	info->board_configuration = 0;
	info->subversion_revision = 0;
	info->chip_id[0] = 0;
	info->chip_id[1] = 0;
	info->board_serial = 0;
	info->flash_serial_high = 0;
	info->flash_serial_low = 0;
	info->flash_valid = 0;
	strcpy_s(info->calibration_date, "2020-01-01 00:00");

	return XHPTDC8_OK;
}

/*
* Get temperature measurements from multiple sources on the board.
*/
extern "C" int xhptdc8_get_temperature_info(xhptdc8_manager* xhptdc8_mgr, int index,
	xhptdc8_temperature_info* info)
{
	if (nullptr == xhptdc8_mgr)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (index < 0)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == info)
		return XHPTDC8_INVALID_ARGUMENTS;

	info->size = sizeof(xhptdc8_temperature_info);
	info->version = XHPTDC8_TEMP_INFO_VERSION;
	info->tdc[0] = (float)(65.0);
	info->tdc[1] = (float)(65.0);
	info->fpga = 65;

	return XHPTDC8_OK;
}

/*
* Get information on clocking configuration an status.
*/
extern "C" int xhptdc8_get_clock_info(xhptdc8_manager* xhptdc8_mgr, int index,
	xhptdc8_clock_info* info)
{
	if (nullptr == xhptdc8_mgr)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (index < 0)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == info)
		return XHPTDC8_INVALID_ARGUMENTS;

	info->size = sizeof(xhptdc8_clock_info);
	info->version = XHPTDC8_CLOCK_INFO_VERSION;
	info->cdce_locked = 0;
	info->cdce_version = 0;
	info->clock_source = XHPTDC8_CLK_OSC;
	info->fpga_locked = 0;

	return XHPTDC8_OK;
}

//_____________________________________________________________________________
// ConfigurationAPIs
//

/*
* Configures the xHPTDC8 manager.
*/
extern "C" int xhptdc8_configure(xhptdc8_manager* xhptdc8_mgr, xhptdc8_manager_configuration* config)
{
	if (nullptr == xhptdc8_mgr)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == config)
		return XHPTDC8_INVALID_ARGUMENTS;

	// For *_configure() you just return the status code and ignore the configuration.
	return XHPTDC8_OK;
}

/*
* Gets current configuration.Copies the current configuration to the specified config pointer.
*/
extern "C" int xhptdc8_get_current_configuration(xhptdc8_manager* xhptdc8_mgr,
	xhptdc8_manager_configuration* config)
{
	if (nullptr == xhptdc8_mgr)
		return XHPTDC8_INVALID_ARGUMENTS;

	if (nullptr == config)
		return XHPTDC8_INVALID_ARGUMENTS;

	config->size = sizeof(xhptdc8_manager_configuration);
	config->version = XHPTDC8_MANAGER_CONFIG_VERSION;
	for (int device_index = 0; device_index < XTDC8MANAGER_DEVICES_MAX; device_index++)
	{
		config->device_configs[device_index].size = sizeof(xhptdc8_device_configuration);
		config->device_configs[device_index].version = XHPTDC8_DEVICE_CONFIG_VERSION;
		config->device_configs[device_index].auto_trigger_period = 0;
		config->device_configs[device_index].auto_trigger_random_exponent = 0;
		config->device_configs[device_index].tdc_mode = XHPTDC8_TDC_MODE_GROUPED;

		for (int channel_index = 0; channel_index < XHPTDC8_TDC_CHANNEL_COUNT; channel_index++)
		{
			config->device_configs[device_index].dc_offset[channel_index] =
				XHPTDC8_DC_OFFSET_P_NIM;
		}
		for (int trigger_index = 0; trigger_index< XHPTDC8_TRIGGER_COUNT; trigger_index++)
		{
			config->device_configs[device_index].trigger[trigger_index].falling = 0 ;
			config->device_configs[device_index].trigger[trigger_index].rising = 0;
		}
		for (int gating_block_index = 0; gating_block_index < XHPTDC8_GATE_COUNT; gating_block_index++)
		{
			config->device_configs[device_index].gating_block[gating_block_index].mode = XHPTDC8_TIGER_OFF;
			config->device_configs[device_index].gating_block[gating_block_index].negate = false ;
			config->device_configs[device_index].gating_block[gating_block_index].retrigger = false ;
			config->device_configs[device_index].gating_block[gating_block_index].extend = false ;
			config->device_configs[device_index].gating_block[gating_block_index].start = 0;
			config->device_configs[device_index].gating_block[gating_block_index].stop = 0;
			config->device_configs[device_index].gating_block[gating_block_index].sources = XHPTDC8_TRIGGER_SOURCE_A;
		}
		for (int tiger_block_index = 0; tiger_block_index < XHPTDC8_TIGER_COUNT; tiger_block_index ++)
		{
			config->device_configs[device_index].tiger_block[tiger_block_index].mode = XHPTDC8_TIGER_OFF;
			config->device_configs[device_index].tiger_block[tiger_block_index].negate = false;
			config->device_configs[device_index].tiger_block[tiger_block_index].retrigger = false;
			config->device_configs[device_index].tiger_block[tiger_block_index].extend = false;
			config->device_configs[device_index].tiger_block[tiger_block_index].start = 0;
			config->device_configs[device_index].tiger_block[tiger_block_index].stop = 0;
			config->device_configs[device_index].tiger_block[tiger_block_index].sources = XHPTDC8_TRIGGER_SOURCE_A;
		}
		for (int channel_index = 0; channel_index < XHPTDC8_TDC_CHANNEL_COUNT; channel_index++)
		{
			config->device_configs[device_index].channel[channel_index].enable = false;
			config->device_configs[device_index].channel[channel_index].rising = false;
		}
		config->device_configs[device_index].skip_alignment = false;
		config->device_configs[device_index].alignment_source = XHPTDC8_ALIGN_TIGER;
	}

	config->grouping.trigger_channel = 0;
	config->grouping.zero_channel = -1;
	config->grouping.zero_channel_offset = 0;
	config->grouping.range_start = 0;
	config->grouping.range_stop = 0;
	config->grouping.trigger_deadtime = 0;
	config->grouping.require_window_hit = false;
	config->grouping.window_start = 0;
	config->grouping.window_stop = 0;
	config->grouping.veto_mode = XHPTDC8_VETO_OFF; 
	config->grouping.veto_start = 0;
	config->grouping.veto_stop = 0;
	config->grouping.veto_relative_to_zero = false;
	config->grouping.overlap = false;

	config->bin_to_ps = NULL;

	return XHPTDC8_OK;
}

/*
* Gets default configuration.
* Copies the default configuration to the specified config pointer.
*/
extern "C" int xhptdc8_get_default_configuration(xhptdc8_manager* xhptdc8_mgr,
	xhptdc8_manager_configuration* config)
{
	return xhptdc8_get_current_configuration(xhptdc8_mgr, config);
}
