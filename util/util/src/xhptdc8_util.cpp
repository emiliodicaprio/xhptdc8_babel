#include "xHPTDC8_interface.h"
#include "xhptdc8_util.h"
#include <stdio.h>
#include <cstring> 

const static size_t MaxErrorMessageSize = 10000;
static char lastErrorMessage[MaxErrorMessageSize];
static char ERR_MSG_INTERNAL_ERR[15] = { "Internal Error" };
static char ERR_MSG_INVALID_ARGS[18] = { "Invalid arguments" };
const char* xhptdc8_get_all_error_messages(crono_bool_t include_ok, crono_bool_t fixed_length)
{
	int written_bytes = 0;
	lastErrorMessage[0] = 0;	// Reset

#define APPEND_MSG(index, msg) \
	{ snprintf(lastErrorMessage + written_bytes, MaxErrorMessageSize - written_bytes - 1, "%d, \"%s\"\n", index, msg); \
	written_bytes = strlen(lastErrorMessage);}

	char* count_err_message;
	int count_err_code;
	int devices_count = xhptdc8_count_devices(&count_err_code, (const char**)&count_err_message);
	if (count_err_code != XHPTDC8_OK)
	{
		snprintf(lastErrorMessage, MaxErrorMessageSize - 1, 
			"-2, \"count_devices() returned error <%d> %s in get_all_error_messages().\"\n", count_err_code, count_err_message); 
		written_bytes = strlen(lastErrorMessage) ;
	}
	for (int board_index = 0; board_index < XHPTDC8_MANAGER_DEVICES_MAX; board_index++)
	{
#define ERR_MSG_DEVICE_COUNT "Could not retrieve error message."

		if (board_index >= devices_count)
		// Board is not installed
		{
			if (fixed_length)
			// Outputs a line for 8 boards, even if there are less boards in the system
			{
				if (count_err_code != XHPTDC8_OK)
				{
					APPEND_MSG(board_index, ERR_MSG_DEVICE_COUNT);
				}
				else
				{
					APPEND_MSG(board_index, "Board does not exist.");
				}
				continue ;
			}
			else 
			// No more boards in the system, and fixed_length is false
			{
				break;
			}
		}
		if (count_err_code != XHPTDC8_OK)
		{
			APPEND_MSG(board_index, ERR_MSG_DEVICE_COUNT);
			continue ;
		}
		const char* err_msg = xhptdc8_get_last_error_message(board_index);
		if (err_msg[0] == 0)
		// No error (message) for this device
		{
			if (include_ok) 
			// Outputs a line even if the board or the manager has no error
			{
				APPEND_MSG(board_index, "OK");
			}
		}
		else
		// There is an error
		{
			APPEND_MSG(board_index, err_msg);
		}
	}
	return lastErrorMessage;
}
