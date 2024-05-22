#include ".\errors.h"
const char *xhptdc8_get_err_message(int err_code) {
    switch (err_code) {
    case XHPTDC8_APPLY_YAML_ERR_EMPTY_CONF_MNGR:
        return "Element 'device_configs' is not found in YAML";
    case XHPTDC8_APPLY_YAML_ERR_NO_CONF_MNGR:
        return "Element 'manager_config' is not found in YAML";
    case XHPTDC8_APPLY_YAML_INVALID_ARGUMENT:
        return "Invalid argument to the APIS";
    case XHPTDC8_APPLY_YAML_INVALID_AUTO_TRIG_PRD:
        return "Invalid value of 'auto_trigger_period'";
    case XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF:
        return "A function is called with 'device_configs' node of no children";
    case XHPTDC8_APPLY_YAML_INVALID_CONFS_STRUTC:
        return "'device_configs' is not an array map, or index is invalid";
    case XHPTDC8_APPLY_YAML_ERR_CONFS_EXCEED_MAX:
        return "'device_configs' array index exceeds XHPTDC8_MANAGER_DEVICES_MAX";
    case XHPTDC8_APPLY_YAML_INVALID_THRESHOLD_STRUCT:
        return "'trigger_threshold' is not an array map, or index is invalid";
    case XHPTDC8_APPLY_YAML_INVALID_THRESHOLD:
        return "Invalid value of 'trigger_threshold' array element";
    case XHPTDC8_APPLY_YAML_THRESHOLDS_EXCEED_MAX:
        return "'trigger_threshold' array index exceeds XHPTDC8_TDC_CHANNEL_COUNT";
    case XHPTDC8_APPLY_YAML_INVALID_ALGNMT_OFFSTAT:
        return "Invalid value of 'alignment_off_state'";
    case XHPTDC8_APPLY_YAML_INVALID_ALGNMT_SRCE:
        return "Invalid value of 'alignment_source'";
    case XHPTDC8_APPLY_YAML_INVALID_SKIP_ALGNMT:
        return "Invalid value of 'skip_alignment'";
    case XHPTDC8_APPLY_YAML_INVALID_AUTO_TRIG_RAND:
        return "Invalid value of 'auto_trigger_random_exponent'";
    case XHPTDC8_APPLY_YAML_GTBLCK_INVALID_START:
        return "Invalid 'gating_block' value of 'start'";
    case XHPTDC8_APPLY_YAML_GTBLCK_INVALID_RETRIG:
        return "Invalid 'gating_block' value of 'retrigger'";
    case XHPTDC8_APPLY_YAML_GTBLCK_INVALID_NEGATE:
        return "Invalid 'gating_block' value of 'negate'";
    case XHPTDC8_APPLY_YAML_GTBLCK_INVALID_MODE:
        return "Invalid 'gating_block' value of 'mode'";
    case XHPTDC8_APPLY_YAML_ERR_GTBLCK_EXCEED_MAX:
        return "'gating_block' array index exceeds XHPTDC8_GATE_COUNT";
    case XHPTDC8_APPLY_YAML_ERR_TRIGGER_EXCEED_MAX:
        return "'trigger' array index exceeds XHPTDC8_TRIGGER_COUNT";
    case XHPTDC8_APPLY_YAML_INVALID_TRIGGER_STRUCT:
        return "'trigger' is not an array map, or index is invalid";
    case XHPTDC8_APPLY_YAML_INVALID_TRIGGER_RISING:
        return "Invalid 'trigger' value of 'rising'";
    case XHPTDC8_APPLY_YAML_INVALID_TRIGGER_FALL:
        return "Invalid 'trigger' value of 'falling'";
    case XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_ENABLE:
        return "Invalid 'adc_channel' value of 'enable'";
    case XHPTDC8_APPLY_YAML_INVALID_CHANNEL_STRUCT:
        return "'channel' is not an array map, or index is invalid";
    case XHPTDC8_APPLY_YAML_INVALID_CHANNEL_RISING:
        return "Invalid 'channel' value of 'rising'";
    case XHPTDC8_APPLY_YAML_INVALID_CHANNEL_ENABLE:
        return "Invalid 'channel' value of 'enable'";
    case XHPTDC8_APPLY_YAML_ERR_CHANNELS_EXCEED_MAX:
        return "'channel' array index exceeds XHPTDC8_TDC_CHANNEL_COUNT";
    case XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STRUCT:
        return "'gating_block' is not an array map, or index is invalid";
    case XHPTDC8_APPLY_YAML_GTBLCK_INVALID_SOURCES:
        return "Invalid 'gating_block' value of 'sources'";
    case XHPTDC8_APPLY_YAML_GTBLCK_STOP_B4_START:
        return "Invalid 'gating_block' value of 'stop' which is earlier than 'start'";
    case XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP:
        return "Invalid 'gating_block' value of 'stop'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_TRIGDT:
        return "Invalid 'grouping' value of 'trigger_deadtime'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_ZEROCHOFF:
        return "Invalid 'grouping' value of 'zero_channel_offset'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_ZEROCH:
        return "Invalid 'grouping' value of 'zero_channel'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_TRIGCH:
        return "Invalid 'grouping' value of 'trigger_channel'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_ENABLED:
        return "Invalid 'grouping' value of 'enabled'";
    case XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_TRTHRESH:
        return "Invalid 'adc_channel' value of 'trigger_threshold'";
    case XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_WDI:
        return "Invalid 'adc_channel' value of 'watchdog_interval'";
    case XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_WDRO:
        return "Invalid 'adc_channel' value of 'watchdog_readout'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETO_STOP:
        return "Invalid 'grouping' value of 'veto_stop'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETO_START:
        return "Invalid 'grouping' value of 'veto_start'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_WINDO_STOP:
        return "Invalid 'grouping' value of 'window_stop'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_WINDO_START:
        return "Invalid 'grouping' value of 'window_start'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_RANGE_STOP:
        return "Invalid 'grouping' value of 'range_stop'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_RANGE_START:
        return "Invalid 'grouping' value of 'range_start'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETORZERO:
        return "Invalid 'grouping' value of 'veto_relative_to_zero'";
    case XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETOMD:
        return "Invalid 'grouping' value of 'veto_mode'";
    case XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_STRUCT:
        return "'tiger_block' is not an array map, or index is invalid";
    case XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_SOURCES:
        return "Invalid 'tiger_block' value of 'sources'";
    case XHPTDC8_APPLY_YAML_TGRBLCK_STOP_B4_START:
        return "Invalid 'tiger_block' value of 'stop' which is earlier than 'start'";
    case XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_STOP:
        return "Invalid 'tiger_block' value of 'stop'";
    case XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_START:
        return "Invalid 'tiger_block' value of 'start'";
    case XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_RETRIG:
        return "Invalid 'tiger_block' value of 'retrigger'";
    case XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_NEGATE:
        return "Invalid 'tiger_block' value of 'negate'";
    case XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_MODE:
        return "Invalid 'tiger_block' value of 'mode'";
    case XHPTDC8_APPLY_YAML_ERR_TGRBLCKS_EXCEED_MAX:
        return "'tiger_block' array index exceeds XHPTDC8_TIGER_COUNT";
    default:
        return "Error not found";
    }
}