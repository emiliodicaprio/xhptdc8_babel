//
// Header file containing main definitions of the DLL needed by Dummy APIs
//

#ifndef XHPTDC8_DUMMY_H
#define XHPTDC8_DUMMY_H

#define VER_FILE_VERSION_STR	"0.0.18"
#define VER_FILE_VERSION		0x000012
#define VERSION_BUILD			1

#define XHPTDC8_VETO_OFF		0
#define XHPTDC8_VETO_INSIDE		1
#define XHPTDC8_VETO_OUTSIDE	2

#define DUMMY_DEVICES_COUNT		1

#ifdef __cplusplus
extern "C" {
#endif

	enum ManagerState
	{
		CREATED = 0,
		INITIALIZED = 1,
		CONFIGURED = 2,
		CAPTURING = 3,
		PAUSED = 4,
		CLOSED = 5
	};

	typedef struct xhptdc8_dummy_manager_ xhptdc8_dummy_manager;
	struct xhptdc8_dummy_manager_
	{
		xhptdc8_manager_init_parameters params;
		xhptdc8_static_info staticInfo;
		int state;
		xhptdc8_manager_configuration p_mgr_cfg;
		/*
		In Milliseconds
		*/
		long start_capture_time;
		/*
		Saves time captured because of call of pause() or stop()
		*/
		long captured_stored_time;
		/*
		Number of calls to xhptdc8_read_hits()
		How many times *_read() has been called.
		*/
		long read_hits_count;
		/*
		Timestamp of calling *_read() function
		*/
		long last_read_time;

		const static size_t MaxErrorMessageSize = 10000;
		char last_error_message[MaxErrorMessageSize];

		// Board user flash
		unsigned char* user_flash = NULL;
		// Board user flash size
		int user_flash_size = 0;
	} ;

	const char* InvalidDevMgr = "Invalid device manager!";
	const char MSG_OK[3] = { "OK" };

	crono_bool_t xhptdc8_is_valid_manager(xhptdc8_manager xhptdc8_mgr);
	crono_bool_t xhptdc8_is_valid_device_index(xhptdc8_manager xhptdc8_mgr, int index);


#ifdef __cplusplus
}
#endif

int init_static_info_internal(xhptdc8_static_info* info);
void _set_last_error_internal(xhptdc8_manager xhptdc8_mgr, const char* format, ...);
int _xhptdc8_read_hits_for_groups_internal(xhptdc8_dummy_manager* mngr, TDCHit* hit_buf, size_t size);
int _xhptdc8_read_hits_for_NO_groups_internal(xhptdc8_dummy_manager* mngr, TDCHit* hit_buf, size_t size);
crono_bool_t _xhptdc8_is_valid_device_index_inernal(xhptdc8_manager xhptdc8_mgr, int index);

#endif
