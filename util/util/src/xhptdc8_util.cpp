#include "xhptdc8_util.h"
#include "xHPTDC8_interface.h"
#include <cstring>
#include <stdio.h>

const static size_t MaxErrorMessageSize = 10000;
static char lastErrorMessage[MaxErrorMessageSize];
static char ERR_MSG_INTERNAL_ERR[15] = {"Internal Error"};
static char ERR_MSG_INVALID_ARGS[18] = {"Invalid arguments"};
const char *xhptdc8_get_all_error_messages(crono_bool_t include_ok, crono_bool_t fixed_length) {
    int written_bytes = 0;
    lastErrorMessage[0] = 0; // Reset

#define APPEND_MSG(index, msg)                                                                                         \
    {                                                                                                                  \
        snprintf(lastErrorMessage + written_bytes, MaxErrorMessageSize - written_bytes - 1, "%d, \"%s\"\n", index,     \
                 msg);                                                                                                 \
        written_bytes = static_cast<int>(strlen(lastErrorMessage));                                                    \
    }

    char *count_err_message;
    int count_err_code;
    int devices_count = xhptdc8_count_devices(&count_err_code, (const char **)&count_err_message);
    if (count_err_code != XHPTDC8_OK) {
        snprintf(lastErrorMessage, MaxErrorMessageSize - 1,
                 "-2, \"count_devices() returned error <%d> %s in get_all_error_messages().\"\n", count_err_code,
                 count_err_message);
        written_bytes = static_cast<int>(strlen(lastErrorMessage));
    }
    for (int board_index = 0; board_index < XHPTDC8_MANAGER_DEVICES_MAX; board_index++) {
#define ERR_MSG_DEVICE_COUNT "Could not retrieve error message."

        if (board_index >= devices_count)
        // Board is not installed
        {
            if (fixed_length)
            // Outputs a line for 8 boards, even if there are less boards in the system
            {
                if (count_err_code != XHPTDC8_OK) {
                    APPEND_MSG(board_index, ERR_MSG_DEVICE_COUNT);
                } else {
                    APPEND_MSG(board_index, "Board does not exist.");
                }
                continue;
            } else
            // No more boards in the system, and fixed_length is false
            {
                break;
            }
        }
        if (count_err_code != XHPTDC8_OK) {
            APPEND_MSG(board_index, ERR_MSG_DEVICE_COUNT);
            continue;
        }
        const char *err_msg = xhptdc8_get_last_error_message(board_index);
        if (err_msg[0] == 0)
        // No error (message) for this device
        {
            if (include_ok)
            // Outputs a line even if the board or the manager has no error
            {
                APPEND_MSG(board_index, "OK");
            }
        } else
        // There is an error
        {
            APPEND_MSG(board_index, err_msg);
        }
    }
    return lastErrorMessage;
}

int xhptdc8_updage_config_for_grouping_mode(int index, xhptdc8_manager_configuration *mgr_cfg, float threshold,
                                            int64_t range_start, int64_t range_stop, crono_bool_t rising /*=false*/,
                                            crono_bool_t ingore_empty_events /*=false*/) {
    if (nullptr == mgr_cfg || index < 0) {
        return CRONO_INVALID_ARGUMENTS;
    }
    // All 8 TDC channels are enabled
    for (int i = 0; i < XHPTDC8_TDC_CHANNEL_COUNT; i++) {
        mgr_cfg->device_configs[index].channel[i].enable = true;
    }
    // Grouping is enabled
    mgr_cfg->grouping.enabled = true;
    mgr_cfg->grouping.trigger_channel = 0;
    mgr_cfg->grouping.zero_channel = -1;
    mgr_cfg->grouping.zero_channel_offset = 0;
    mgr_cfg->grouping.trigger_deadtime = 0;
    mgr_cfg->grouping.window_hit_channels = 0;
    mgr_cfg->grouping.trigger_channel_bitmask = 0;
    mgr_cfg->grouping.veto_mode = 0;
    mgr_cfg->grouping.overlap = false;
    mgr_cfg->grouping.range_start = range_start;
    mgr_cfg->grouping.range_stop = range_stop;

    // Copy threshold to trigger_threshold for all channels
    for (int i = 0; i < XHPTDC8_TDC_CHANNEL_COUNT; i++) {
        mgr_cfg->device_configs[index].trigger_threshold[i] = threshold;
    }

    // `rising` is copied to channel[i].rising of each channel
    // if true, sets the trigger structure of each channel to rising=true, falling= false.
    // If false, set the structure to rising=false, falling=true
    for (int i = 0; i < XHPTDC8_TRIGGER_COUNT; i++) {
        mgr_cfg->device_configs[index].trigger[i].rising = rising;
        mgr_cfg->device_configs[index].trigger[i].falling = !rising;
    }

    return CRONO_OK;
}
