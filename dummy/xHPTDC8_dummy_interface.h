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

#define DUMMY_DEVICES_COUNT		1	// MUST BE <= XHPTDC8_MANAGER_DEVICES_MAX

#ifdef __cplusplus
extern "C" {
#endif

	namespace ManagerState {
		enum  Enum
		{
			UNINITIALIZED = 0,
			INITIALIZED = 1,
			CONFIGURED = 2,
			CAPTURING = 3,
			PAUSED = 4
		};
	}

	namespace DeviceState {
		// Should be equal to corresponding CRONO_DEVICE_STATE_xxx macro
		enum Enum
		{
			CREATED = CRONO_DEVICE_STATE_CREATED,
			INITIALIZED = CRONO_DEVICE_STATE_INITIALIZED,
			CONFIGURED = CRONO_DEVICE_STATE_CONFIGURED,
			CAPTURING = CRONO_DEVICE_STATE_CAPTURING,
			PAUSED = CRONO_DEVICE_STATE_PAUSED,
			CLOSED = CRONO_DEVICE_STATE_CLOSED
		};
	}

	typedef struct xhptdc8_dummy_manager_ xhptdc8_dummy_manager;
	struct xhptdc8_dummy_manager_
	{
		xhptdc8_manager_init_parameters params;
		xhptdc8_static_info staticInfo;
		ManagerState::Enum state;
		DeviceState::Enum dev_state;
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
		uint8_t* user_flash = NULL;
		// Board user flash size
		uint32_t user_flash_size = 0;
	} ;

	const char MSG_OK[3] = { "OK" };

#ifdef __cplusplus
}
#endif

int _init_static_info_internal(xhptdc8_static_info* info);
void _set_last_error_internal(const char* errString);
void _set_last_error_printf_internal(const char* format, ...);
int _read_hits_for_groups_internal(TDCHit* hit_buf, size_t size);
int _read_hits_for_NO_groups_internal(TDCHit* hit_buf, size_t size);
const char* _GetManagerStateMessage(ManagerState::Enum code);

/**
* Only one device is supported in the Dummy Library, so, index should be always 0
*/
#define CHECK_VALID_DEVICE(index) {if ((index < 0) || (index >= DUMMY_DEVICES_COUNT)) return XHPTDC8_INVALID_DEVICE ; }

#define CHECK_MANAGER_STATE(s)	\
	{ if(mngr.state != (s)) 	\
		{	_set_last_error_printf_internal("xHPTDC8Manager is %s: expected state is %s", \
				_GetManagerStateMessage(mngr.state), _GetManagerStateMessage(s));	\
			return XHPTDC8_WRONG_STATE; \
		}	\
	}
#define CHECK_MANAGER_STATE_OR(s1, s2) \
	{ if(! (mngr.state == (s1) || mngr.state == (s2)))	\
		{	_set_last_error_printf_internal("xHPTDC8Manager is %s: expected state is %s or %s", \
				_GetManagerStateMessage(mngr.state), _GetManagerStateMessage(s1), _GetManagerStateMessage(s2) ); \
			return XHPTDC8_WRONG_STATE; \
		}	\
	}

#endif
