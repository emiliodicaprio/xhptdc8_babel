// xhptdc8_user_guide_example.cpp : Example application for the xHPTDC8

#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#include "crono_interface.h"
#include "xHPTDC8_interface.h"

typedef unsigned int uint32;
#if defined(_WIN32) || defined(_WIN64)
typedef unsigned __int64 uint64;
#define crono_sleep(x) Sleep(x)
#else
#include <unistd.h>
#define crono_sleep(x) usleep(1000 * x)
#endif
int exit_on_fail(int status, const char* message);
const int MAX_TRYS_TO_READ_HITS = 1000;

// create a manager object that provides access to all xHPTDC8 in the system
int initialize_xhptdc8(int buffer_size) {
	// prepare initialization
	xhptdc8_manager_init_parameters params;

	xhptdc8_get_default_init_parameters(&params);
	params.buffer_size = buffer_size;

	int error_code;
	char* error_msg = NULL;
	error_code = xhptdc8_init(&params);
	exit_on_fail(error_code, error_msg);
	return error_code;
}

int get_device_count() {
	int error_code;
	char* error_msg;

	int device_count = xhptdc8_count_devices(&error_code, (const char**)&error_msg); 
	exit_on_fail(error_code, error_msg);
	return device_count;
}

int configure_xhptdc8(int device_count) {
	xhptdc8_manager_configuration* mgr_cfg = new xhptdc8_manager_configuration;
	xhptdc8_get_default_configuration(mgr_cfg);
	int general_offset = 50, epsilon = 4;

	// configure all devices with an identical configuration
	for (int device_index = 0; device_index < device_count; device_index++) {
		for (int channel_index = 0; channel_index < XHPTDC8_TDC_CHANNEL_COUNT; channel_index++)
		{
			mgr_cfg->device_configs[device_index].trigger_threshold[channel_index] 
				= XHPTDC8_THRESHOLD_N_NIM;
			mgr_cfg->device_configs[device_index].channel[channel_index].enable = true;
		}
		mgr_cfg->device_configs[device_index].adc_channel.enable = 1;
		mgr_cfg->device_configs[device_index].adc_channel.watchdog_readout = 0;
		mgr_cfg->device_configs[device_index].adc_channel.trigger_threshold 
			= XHPTDC8_THRESHOLD_N_NIM;

		// configure an auto trigger at 150 kHz
		mgr_cfg->device_configs[device_index].auto_trigger_period = 1000;
		mgr_cfg->device_configs[device_index].auto_trigger_random_exponent = 0;

		// set all TiGers to create a short pulse for every auto trigger 
		for (int block_index = 0; block_index < XHPTDC8_TDC_CHANNEL_COUNT; block_index++)
		{
			int channel_offset = block_index * 2;
			mgr_cfg->device_configs[device_index].tiger_block[block_index].extend = false;
			mgr_cfg->device_configs[device_index].tiger_block[block_index].negate = false;
			mgr_cfg->device_configs[device_index].tiger_block[block_index].retrigger = false;
			mgr_cfg->device_configs[device_index].tiger_block[block_index].sources
				= XHPTDC8_TRIGGER_SOURCE_AUTO;
			mgr_cfg->device_configs[device_index].tiger_block[block_index].mode = XHPTDC8_TIGER_BIPOLAR;

			// every channel pulses a little later than the previous channel, for one clock cycle
			mgr_cfg->device_configs[device_index].tiger_block[block_index].start = general_offset +  channel_offset;
			mgr_cfg->device_configs[device_index].tiger_block[block_index].stop = general_offset + channel_offset + 1;

			// block trigger that is outside start-stop range
			mgr_cfg->device_configs[device_index].gating_block[block_index].negate = false;
			mgr_cfg->device_configs[device_index].gating_block[block_index].sources = XHPTDC8_TRIGGER_SOURCE_AUTO;
			mgr_cfg->device_configs[device_index].gating_block[block_index].mode = XHPTDC8_GATE_ON;
			mgr_cfg->device_configs[device_index].gating_block[block_index].start = general_offset + channel_offset - epsilon;
			mgr_cfg->device_configs[device_index].gating_block[block_index].stop = general_offset + channel_offset + epsilon + 1;
		}
	}
	return xhptdc8_configure(mgr_cfg);
}


void print_device_information() {
	xhptdc8_static_info staticinfo;
	printf("-------------------------\n");
	for (int i = 0; i < get_device_count(); i++) {
		xhptdc8_get_static_info(i, &staticinfo);
		printf("Board Serial         : %d.%d\n", staticinfo.board_serial >> 24, staticinfo.board_serial & 0xffffff);
		printf("Board Configuration  : %d\n", staticinfo.board_configuration);
		printf("Board Revision       : %d\n", staticinfo.board_revision);
		printf("Firmware Revision    : %d.%d\n", staticinfo.firmware_revision, staticinfo.subversion_revision);
		printf("Driver Revision      : %d.%d.%d\n", ((staticinfo.driver_revision >> 16) & 255), ((staticinfo.driver_revision >> 8) & 255), (staticinfo.driver_revision & 255));
		printf("Driver SVN Revision  : %d\n", staticinfo.driver_build_revision);
	}
}

void print_hit(TDCHit* hit) {
	bool adc_data = ((hit->channel % 10) == 8) || ((hit->channel % 10) == 9);
	if (hit->type & XHPTDC8_TDCHIT_TYPE_ERROR)
		printf("Error:\n");

	printf("Channel %u - Time %llu - Type %x", hit->channel, hit->time, hit->type);
	if (adc_data)
		printf(" - ADC Data : %d", (int)(hit->bin));

	printf("\n");
}

// call read_hits() once per millisecond until there is some data or max count of trials
int poll_for_hits(TDCHit* hit_buffer, size_t events_per_read) {
	int trys_to_read_hits = 0;
	while (trys_to_read_hits < MAX_TRYS_TO_READ_HITS) {
		unsigned long hit_count = xhptdc8_read_hits(hit_buffer, events_per_read);
		if (hit_count)
			return hit_count;
		crono_sleep(1);
		trys_to_read_hits++;
	}
	if (trys_to_read_hits == MAX_TRYS_TO_READ_HITS)
		printf("not enough data, check trigger source and device configuration\n");
	return trys_to_read_hits;
}


// fetch hits from the board by polling
void read_hits_wrapper(int events_per_read) {
	int total_event_count = events_per_read * 10000;

	TDCHit* hit_buffer = new TDCHit[events_per_read];

	int total_events = 0;
	while (total_events < total_event_count) {
		unsigned long hit_count = poll_for_hits(hit_buffer, events_per_read);

		for (unsigned int i = 0; i < hit_count; i++)
		{
			TDCHit* hit = &(hit_buffer[i]);
			print_hit(hit);
			if ((total_events++ % 100) == 0)
				printf("Sum: %d - Packet events: %d\n", total_events, hit_count);
		}
	}

	delete[] hit_buffer;
}

// utility function to check for error, print error message and exit
int exit_on_fail(int status, const char* message) {
	if (status == XHPTDC8_OK)
		return status;
	printf("%s: %s\n", message, xhptdc8_get_last_error_message(0));
	exit(1);
}

int main(int argc, char* argv[]) {
	printf("cronologic xhptdc8_user_guide_example using driver: %s\n", xhptdc8_get_driver_revision_str());
	printf("\n\nThis is illustrating the usage of an xHPTDC8 examplary with internal triggering\n");
	int error_code = initialize_xhptdc8(8 * 1024 * 1024);
    
	exit_on_fail(
		//configure all devices with that manager
		configure_xhptdc8(get_device_count()),
		"Could not configure.");

	print_device_information();

	exit_on_fail(
		//start measurement
		xhptdc8_start_capture(),
		"Could not start capturing.");

	exit_on_fail(
		//start TiGer-functionality
		xhptdc8_start_tiger(0),
		"Could not start TiGer.");

	//collect measured data
	read_hits_wrapper(10000);

	exit_on_fail(
		//stop measurement
		xhptdc8_stop_capture(),
		"Could not stop capturing.");

	exit_on_fail(
		//close manager
		xhptdc8_close(),
		"Could not close devices-manager.");

	return 0;
}
