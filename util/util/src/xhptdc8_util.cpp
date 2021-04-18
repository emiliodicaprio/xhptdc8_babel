#include "pch.h"
#include "xhptdc8_interface.h"
#include "xhptdc8_util.h"
#include <stdio.h>

const static size_t MaxErrorMessageSize = 10000;
static char lastErrorMessage[MaxErrorMessageSize];
static char ERR_MSG_INTERNAL_ERR[15] = { "Internal Error" };
const char* xhptdc8_get_all_error_messages(xhptdc8_manager hMgr, crono_bool_t include_ok, crono_bool_t fixed_length)
{
	char* count_err_message;
	int count_err_code;
	int devices_count = xhptdc8_count_devices(&count_err_code, (const char**)&count_err_message);
	if (count_err_code != 0)
	{
		strcpy_s(lastErrorMessage, MaxErrorMessageSize, ERR_MSG_INTERNAL_ERR);
		return lastErrorMessage;
	}
	lastErrorMessage[0] = 0;	// Reset

	for (int written_bytes = 0 , board_index = 0; board_index < XHPTDC8_MANAGER_DEVICES_MAX; board_index++)
	{
		written_bytes = strlen(lastErrorMessage);
		const char* err_msg = xhptdc8_get_last_error_message(hMgr, board_index);
		if (	(board_index >= devices_count) // Board is not installed
			&&	(!fixed_length)	// DONOT: Outputs a line for 8 boards, even if there are less boards in the system
			)
		{
			break;
		}
		if (err_msg[0] == 0)
		// No error (message) for this device
		{
			if (include_ok) 
			// Outputs a line even if the board or the manager has no error
			{
				snprintf(lastErrorMessage + written_bytes, MaxErrorMessageSize - written_bytes - 1,
					"%d, %d, %s\n", board_index, 0, "OK");
			}
		}
		else
		// There is an error
		{
			snprintf(lastErrorMessage + written_bytes, MaxErrorMessageSize - written_bytes - 1,
				"%d, %d, %s\n", board_index, 0, err_msg);
		}
	}
	return lastErrorMessage;
}
