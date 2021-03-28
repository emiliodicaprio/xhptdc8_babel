#include ".\util_msvscpp\pch.h"
#include "xhptdc8_util_yaml.h"

using namespace std;

void list_ryml_children(const ryml::NodeRef* node)
{
    int children_count = node->num_children();
    std::string key_buff;
    std::string val_buff;
    char buff[1024];
    for (int child_index = 0; child_index < children_count; child_index++)
    {
        ryml::NodeRef child = node->child(child_index);
        
        if (child.has_key())
            _get_node_key_name_internal(&child, &key_buff);
        else 
            (key_buff.assign("N/A")) ;
        
        if (child.has_val())
            _get_node_val_internal(&child, &val_buff);
        else
            val_buff.assign("N/A");
        
        sprintf_s(buff, 1024, "Key=<%s>, Val=<%s>", key_buff.c_str(), val_buff.c_str());
    }
}

/*
* Checks if the node is array and children are structured as map or not, e.g.
* 0:  
*  element: value
* 1:
*  element: value 
* Validates that the first child is a map whose key is number
* It considers the element key = -1 as an array map
* 
* Return:   true : node is array map
*           false: node is not array map, or error 
*/
crono_bool_t _is_node_array_map(const ryml::NodeRef* pNode)
{
    if (!RYML_NODE_EXISTS(*pNode))
        return false;

    if (pNode->num_children() < 1)
        return false;

    ryml::NodeRef first_child_node = pNode->child(0);
    if (!RYML_NODE_EXISTS(first_child_node))
        return false;

    if (    (!first_child_node.has_key())
        ||  (first_child_node.has_val()))
        return false;

    std::string first_child_key_name;
    _get_node_key_name_internal(&first_child_node, &first_child_key_name);
    try {
        int child_index = stoi(first_child_key_name.c_str());
        return true;
    }
    catch (...) {
        return false;
    }
}

/*
* Caller ensures the the node has key
*/
int _get_node_key_name_internal(const ryml::NodeRef* pNode, std::string* key_name)
{
    int key_len = pNode->key().len;
    std::string undelimited_key_name = pNode->key().data();
    *key_name = undelimited_key_name.substr(0, key_len);
    return 1;
}

/*
* Caller ensures the the node has key
* Return node key name as integer in case of success,
*        -1: Error
*/
int _get_node_key_name_toi_internal(const ryml::NodeRef* pNode)
{
    int key_len = pNode->key().len;
    std::string undelimited_key_name = pNode->key().data();
    std::string key_name = undelimited_key_name.substr(0, key_len);
    try {
        int key_name_toi = stoi(key_name.c_str());
        if (key_name_toi < 0)
            return -1;
        return key_name_toi;
    }
    catch (...) {
        return -1;
    }
    return 1;
}

/*
* Caller ensures the the node has value
*/
int _get_node_val_internal(const ryml::NodeRef* pNode, std::string* val)
{
    int val_len = pNode->val().len;
    std::string undilimited_val = pNode->val().data();
    *val = undilimited_val.substr(0, val_len);
    return 1;
}

/*
* Caller ensures the the node has value
* Return true : *pVal has an integral value
*        false: error converting value 
*/
crono_bool_t _node_val_toi_internal(const ryml::NodeRef* pNode, int* pVal)
{
    std::string val;
    _get_node_val_internal(pNode, &val);
    try {
        *pVal = stoi(val.c_str());
        return true;
    }
    catch (...)
    {
        return false;
    }
}

/*
* Caller ensures the the node has value
* Return true : *pVal has a double value
*        false: error converting value
*/
crono_bool_t _node_val_tod_internal(const ryml::NodeRef* pNode, double* pVal)
{
    std::string val;
    _get_node_val_internal(pNode, &val);
    try {
        *pVal = stod(val.c_str());
        return true;
    }
    catch (...)
    {
        return false;
    }
}

/*
* Caller ensures the the node has value
* Return true : *pVal has a long long value
*        false: error converting value
*/
crono_bool_t _node_val_toll_internal(const ryml::NodeRef* pNode, long long * pVal)
{
    std::string val;
    _get_node_val_internal(pNode, &val);
    try {
        *pVal = stoll(val.c_str());
        return true;
    }
    catch (...)
    {
        return false;
    }
}

/*
* Return number of configurations passed in the configuration manager 
* config_mngr_node, with the device_configs node in device_configs_node, 
* or, error in case of error
* 
* Return N (>0) : Count of configurations in device_configs_node
*        -ve    : Error
*/
int xhptdc8_yaml_get_configs_count(const ryml::NodeRef* config_mngr_node, ryml::NodeRef* device_configs_node)
{
    if (nullptr == config_mngr_node || nullptr == device_configs_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ( !RYML_NODE_EXISTS(*config_mngr_node))
    {
        return XHPTDC8_APPLY_YAML_ERR_NO_CONF_MNGR;
    }
    if (config_mngr_node->num_children() < 1)
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_CONF_MNGR;
    }
    (*device_configs_node) = (*config_mngr_node)[YAML_XHPTDC8_DEVICE_CONFIGS_NAME];
    if ( !RYML_NODE_EXISTS(*device_configs_node))
    {
        return XHPTDC8_APPLY_YAML_ERR_NO_DEV_CONFS;
    }
    int configs_count = device_configs_node->num_children();
    if (0 == configs_count)
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONFS;
    }
    if (configs_count > XHPTDC8_MANAGER_DEVICES_MAX)
    {
        return XHPTDC8_APPLY_YAML_ERR_CONFS_EXCEED_MAX;
    }
    /*
    * device_configs MUST by a map 
    */
    if (!_is_node_array_map(device_configs_node))
    {
        return XHPTDC8_APPLY_YAML_ERR_INVALID_CONFS_STRUTC;
    }
    return configs_count;
}

/*
* Return 0: Not found/no impact, no error
*        N: Count of successfully updated thresholds 
*       -ve: Error
*/
int xhptdc8_apply_trigger_threshold_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    VALIDATE_APPLY_YAMAL_PARAMS;

    ryml::NodeRef trigger_threshold_node = (*device_config_node).find_child("trigger_threshold");
    if (!RYML_NODE_EXISTS(trigger_threshold_node))
    {
        return 0;
    }
    int trigger_thresholds_count = 0;
    trigger_thresholds_count = trigger_threshold_node.num_children();
    if ( trigger_thresholds_count <= 0 )
    // Empty thresholds, accepted
    {
        return 0;
    }
    if (trigger_thresholds_count > XHPTDC8_TDC_CHANNEL_COUNT)
    {
        return XHPTDC8_APPLY_YAML_THRESHOLDS_EXCEED_MAX;
    }
    // Check "-1" in the first item, apply on all
    crono_bool_t apply_first_on_all_elements = false;
    double val_to_apply_on_all_elements;
    ryml::NodeRef threshold_first_item_node = trigger_threshold_node.child(0);
    int threshold_index_in_cfg = _get_node_key_name_toi_internal(&threshold_first_item_node);
    if (-1 == threshold_index_in_cfg)
    {
        apply_first_on_all_elements = true;
        if (!_node_val_tod_internal(&threshold_first_item_node, &val_to_apply_on_all_elements))
        {
            return XHPTDC8_APPLY_YAML_INVALID_THRESHOLD;
        }
        if ((val_to_apply_on_all_elements < -1.32) || (val_to_apply_on_all_elements > 1.18))
        {
            return XHPTDC8_APPLY_YAML_INVALID_THRESHOLD;
        }
        
        trigger_thresholds_count = XHPTDC8_TDC_CHANNEL_COUNT;

        VERBOSE_DEBUG_MSG("Applying -1 element <%d> on all <%s> elements, ignoring all the rest if found\n", 
            val_to_apply_on_all_elements, "trigger_threshold");
    }
    // Loop on the elements
    for (int threshold_index = 0; threshold_index < trigger_thresholds_count; threshold_index++)
    {
        double val;
        if (apply_first_on_all_elements)
        {
            val = val_to_apply_on_all_elements;
            threshold_index_in_cfg = threshold_index;
        }
        else
        {
            // Get threshold value
            ryml::NodeRef threshold_item_node;
            threshold_item_node = trigger_threshold_node.child(threshold_index);
            threshold_index_in_cfg = _get_node_key_name_toi_internal(&threshold_item_node);

            VALIDATE_ARRAY_INDEX(threshold_index_in_cfg, XHPTDC8_TDC_CHANNEL_COUNT,
                XHPTDC8_APPLY_YAML_INVALID_THRESHOLD_STRUCT, XHPTDC8_APPLY_YAML_THRESHOLDS_EXCEED_MAX);

            if (!_node_val_tod_internal(&threshold_item_node, &val))
            {
                return XHPTDC8_APPLY_YAML_INVALID_THRESHOLD;
            }
            if ((val < -1.32) || (val > 1.18))
            {
                return XHPTDC8_APPLY_YAML_INVALID_THRESHOLD;
            }
        }
        // Apply value
        device_config->trigger_threshold[threshold_index_in_cfg] = val;
        VERBOSE_DEBUG_MSG_YAML_APPLIED_D(*device_config_node, "trigger_threshold", val);
    }
    return trigger_thresholds_count;
}

/*
* Return 0: Not found/no impact, no error
*        N: Count of successfully updated trigger
*       -ve: Error
*/
int xhptdc8_apply_trigger_yaml(const ryml::NodeRef* device_config_node,
        xhptdc8_device_configuration* device_config)
{
    VALIDATE_APPLY_YAMAL_PARAMS;

    ryml::NodeRef trigger_node = (*device_config_node).find_child("trigger");
    if (!RYML_NODE_EXISTS(trigger_node))
    {
        return 0;
    }

    int trigger_children_count = 0;
    trigger_children_count = trigger_node.num_children();
    VALIDATE_CHILDREN_COUNT(trigger_children_count, XHPTDC8_TRIGGER_COUNT, 
        XHPTDC8_APPLY_YAML_ERR_TRIGGERS_EXCEED_MAX);

    crono_bool_t is_array_map = _is_node_array_map(&trigger_node);
    if (is_array_map)
    {
        // Check "-1" in the first item, apply on all
        crono_bool_t apply_first_on_all_elements = false;
        ryml::NodeRef trigger_first_item_node = trigger_node.child(0);
        int trigger_index_in_cfg = _get_node_key_name_toi_internal(&trigger_first_item_node);
        if (-1 == trigger_index_in_cfg)
        {
            apply_first_on_all_elements = true;
            trigger_children_count = XHPTDC8_TRIGGER_COUNT;

            VERBOSE_DEBUG_MSG("Applying -1 element on all <%s> elements, ignoring all the rest if found\n",
                "trigger");
        }
        // Apply values 
        ryml::NodeRef child_node;
        for (int trigger_index = 0; trigger_index < trigger_children_count; trigger_index++)
        {
            if (apply_first_on_all_elements)
            {
                child_node = trigger_first_item_node ;
                trigger_index_in_cfg = trigger_index;
            }
            else
            {
                child_node = trigger_node.child(trigger_index);
                trigger_index_in_cfg = _get_node_key_name_toi_internal(&child_node);

                VALIDATE_ARRAY_INDEX(trigger_index_in_cfg, XHPTDC8_TRIGGER_COUNT,
                    XHPTDC8_APPLY_YAML_INVALID_TRIGGERS_STRUCT, XHPTDC8_APPLY_YAML_ERR_TRIGGERS_EXCEED_MAX);
            }
            APPLY_CHILD_BOOL_VALUE(child_node, "falling",
                device_config->trigger[trigger_index_in_cfg].falling, XHPTDC8_APPLY_YAML_INVALID_TRIGGERS_FALL);

            APPLY_CHILD_BOOL_VALUE(child_node, "rising",
                device_config->trigger[trigger_index_in_cfg].rising, XHPTDC8_APPLY_YAML_INVALID_TRIGGERS_RISING);
        }
    }
    else
    // Is map with only the values for the first array element 
    {
        APPLY_CHILD_BOOL_VALUE(trigger_node, "falling",
            device_config->trigger[0].falling, XHPTDC8_APPLY_YAML_INVALID_TRIGGERS_FALL);

        APPLY_CHILD_BOOL_VALUE(trigger_node, "rising",
            device_config->trigger[0].rising, XHPTDC8_APPLY_YAML_INVALID_TRIGGERS_RISING);
    }
    return trigger_children_count;
}

/*
* Return 0: Not found/no impact, no error
*        N: Count of successfully updated channel
*       -ve: Error
*/
int xhptdc8_apply_channel_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    VALIDATE_APPLY_YAMAL_PARAMS;

    ryml::NodeRef channel_node = (*device_config_node).find_child("channel");
    if (!RYML_NODE_EXISTS(channel_node))
    {
        return 0;
    }
    int channel_children_count = 0;
    channel_children_count = channel_node.num_children();
    VALIDATE_CHILDREN_COUNT(channel_children_count, XHPTDC8_TDC_CHANNEL_COUNT,
        XHPTDC8_APPLY_YAML_ERR_CHANNELS_EXCEED_MAX);

    crono_bool_t is_array_map = _is_node_array_map(&channel_node);
    if (is_array_map)
    {
        // Check "-1" in the first item, apply on all
        crono_bool_t apply_first_on_all_elements = false;
        ryml::NodeRef channel_first_item_node = channel_node.child(0);
        int channel_index_in_cfg = _get_node_key_name_toi_internal(&channel_first_item_node);
        if (-1 == channel_index_in_cfg)
        {
            apply_first_on_all_elements = true;
            channel_children_count = XHPTDC8_TDC_CHANNEL_COUNT;

            VERBOSE_DEBUG_MSG("Applying -1 element on all <%s> elements, ignoring all the rest if found\n",
                "channel");
        }
        // Apply values 
        ryml::NodeRef child_node;
        for (int channel_index = 0; channel_index < channel_children_count; channel_index++)
        {
            if (apply_first_on_all_elements)
            {
                child_node = channel_first_item_node;
                channel_index_in_cfg = channel_index;
            }
            else
            {
                child_node = channel_node.child(channel_index);
                channel_index_in_cfg = _get_node_key_name_toi_internal(&child_node);

                VALIDATE_ARRAY_INDEX(channel_index_in_cfg, XHPTDC8_TDC_CHANNEL_COUNT,
                    XHPTDC8_APPLY_YAML_INVALID_CHANNEL_STRUCT, XHPTDC8_APPLY_YAML_ERR_CHANNELS_EXCEED_MAX);
            }
            APPLY_CHILD_BOOL_VALUE(child_node, "enable",
                device_config->channel[channel_index_in_cfg].enable, XHPTDC8_APPLY_YAML_INVALID_CHANNEL_ENABLE);

            APPLY_CHILD_BOOL_VALUE(child_node, "rising",
                device_config->channel[channel_index_in_cfg].rising, XHPTDC8_APPLY_YAML_INVALID_CHANNEL_RISING);
        }
    }
    else
    // Is map with the values of only the first array element 
    {
        if (channel_children_count > 2)
        {
            return XHPTDC8_APPLY_YAML_INVALID_CHANNEL_STRUCT;
        }
        APPLY_CHILD_BOOL_VALUE(channel_node, "enable",
            device_config->channel[0].enable, XHPTDC8_APPLY_YAML_INVALID_CHANNEL_ENABLE);

        APPLY_CHILD_BOOL_VALUE(channel_node, "rising",
            device_config->channel[0].rising, XHPTDC8_APPLY_YAML_INVALID_CHANNEL_RISING);
    }
    return channel_children_count;
}

/*
* Return 0: Not found/no impact, no error
*        1: Successful applying
*       -ve: Error
*/
int xhptdc8_apply_adc_channel_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    VALIDATE_APPLY_YAMAL_PARAMS;

    ryml::NodeRef adc_channel_node = (*device_config_node).find_child("adc_channel");
    if (!RYML_NODE_EXISTS(adc_channel_node))
    {
        return 0;
    }
    // enable
    APPLY_CHILD_BOOL_VALUE(adc_channel_node, "enable",
        device_config->adc_channel.enable, XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_ENABLE);

    // watchdog_readout
    APPLY_CHILD_BOOL_VALUE(adc_channel_node, "watchdog_readout",
        device_config->adc_channel.watchdog_readout, XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_WDRO);

    // watchdog_interval
    APPLY_CHILD_INTEGER_VALUE(adc_channel_node, "watchdog_interval", val > 0,
        device_config->adc_channel.watchdog_interval, XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_WDI);

    // trigger_threshold
    APPLY_CHILD_DOUBLE_VALUE(adc_channel_node, "trigger_threshold", val > 0,
        device_config->adc_channel.trigger_threshold, XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_TRTHRESH);

    return 1;
}

/*
* Return 0: Not found/no impact, no error
*        N: Count of successfully updated gate_block
*       -ve: Error
*/
int xhptdc8_apply_gating_block_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    VALIDATE_APPLY_YAMAL_PARAMS;

    ryml::NodeRef gating_block_node = (*device_config_node).find_child("gating_block");
    if (!RYML_NODE_EXISTS(gating_block_node))
    {
        return 0;
    }

    int gating_block_children_count = 0;
    gating_block_children_count = gating_block_node.num_children();
    VALIDATE_CHILDREN_COUNT(gating_block_children_count, XHPTDC8_GATE_COUNT,
        XHPTDC8_APPLY_YAML_ERR_GATE_BLOCK_EXCEED_MAX);

    crono_bool_t is_array_map = _is_node_array_map(&gating_block_node);
    if (is_array_map)
    {
        // Check "-1" in the first item, apply on all
        crono_bool_t apply_first_on_all_elements = false;
        ryml::NodeRef gating_block_first_item_node = gating_block_node.child(0);
        int gating_block_index_in_cfg = _get_node_key_name_toi_internal(&gating_block_first_item_node);
        if (-1 == gating_block_index_in_cfg)
        {
            apply_first_on_all_elements = true;
            gating_block_children_count = XHPTDC8_GATE_COUNT;

            VERBOSE_DEBUG_MSG("Applying -1 element on all <%s> elements, ignoring all the rest if found\n",
                "gating_block");
        }
        // Apply values 
        ryml::NodeRef child_node;
        for (int gating_block_index = 0; gating_block_index < gating_block_children_count; gating_block_index++)
        {
            if (apply_first_on_all_elements)
            {
                child_node = gating_block_first_item_node;
                gating_block_index_in_cfg = gating_block_index;
            }
            else
            {
                child_node = gating_block_node.child(gating_block_index);
                gating_block_index_in_cfg = _get_node_key_name_toi_internal(&child_node);

                VALIDATE_ARRAY_INDEX(gating_block_index_in_cfg, XHPTDC8_GATE_COUNT,
                    XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STRUCT, XHPTDC8_APPLY_YAML_ERR_GATE_BLOCK_EXCEED_MAX);
            }
            // mode
            ryml::NodeRef mode_node = child_node.find_child("mode");
            if (RYML_NODE_EXISTS_AND_HAS_VAL(mode_node))
            {
                int val;
                if (!_node_val_toi_internal(&mode_node, &val))
                {
                    return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_MODE;
                }
                switch (val) {
                case XHPTDC8_TIGER_OFF:
                case XHPTDC8_TIGER_OUTPUT:
                case XHPTDC8_TIGER_BIDI:
                case XHPTDC8_TIGER_BIPOLAR:
                    device_config->gating_block[gating_block_index_in_cfg].mode = val;
                    VERBOSE_DEBUG_MSG_YAML_APPLIED_I(child_node, "mode", val);
                    break;
                default:
                    return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_MODE;
                }
            }
            // negate
            APPLY_CHILD_BOOL_VALUE(child_node, "negate",
                device_config->gating_block[gating_block_index_in_cfg].negate, XHPTDC8_APPLY_YAML_GTBLCK_INVALID_NEGATE);

            // retrigger
            APPLY_CHILD_BOOL_VALUE(child_node, "retrigger",
                device_config->gating_block[gating_block_index_in_cfg].retrigger, XHPTDC8_APPLY_YAML_GTBLCK_INVALID_RETRIG);

            // Ignore "extend", not implemented
            // start
            APPLY_CHILD_INTEGER_VALUE(child_node, "start",
                ((0 <= val) && (val <= (65536 - 1))), device_config->gating_block[gating_block_index_in_cfg].start,
                XHPTDC8_APPLY_YAML_GTBLCK_INVALID_START);

            // stop
            ryml::NodeRef stop_node = child_node.find_child("stop");
            if (RYML_NODE_EXISTS_AND_HAS_VAL(stop_node))
            {
                int val;
                if (!_node_val_toi_internal(&stop_node, &val))
                {
                    return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP;
                }
                if ((0 <= val) && (val <= (65536 - 1)))
                {
                    if (val < device_config->gating_block[gating_block_index_in_cfg].start)
                    {
                        return XHPTDC8_APPLY_YAML_GTBLCK_STOP_B4_START;
                    }
                    else
                    {
                        device_config->gating_block[gating_block_index_in_cfg].stop = val;
                        VERBOSE_DEBUG_MSG_YAML_APPLIED_I(gating_block_node, "stop", val);
                    }
                }
                else
                {
                    return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP;
                }
            }
            // sources
            APPLY_CHILD_INTEGER_VALUE(child_node, "sources", val > 0,
                device_config->gating_block[gating_block_index_in_cfg].sources,
                XHPTDC8_APPLY_YAML_GTBLCK_INVALID_SOURCES);
        }
    }
    else
    // Is map with the values of only the first array element 
    {
        // mode
        ryml::NodeRef mode_node = gating_block_node.find_child("mode");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(mode_node))
        {
            int val;
            if (!_node_val_toi_internal(&mode_node, &val))
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_MODE;
            }
            switch (val) {
            case XHPTDC8_TIGER_OFF:
            case XHPTDC8_TIGER_OUTPUT:
            case XHPTDC8_TIGER_BIDI:
            case XHPTDC8_TIGER_BIPOLAR:
                device_config->gating_block[0].mode = val;
                VERBOSE_DEBUG_MSG_YAML_APPLIED_I(gating_block_node, "mode", val);
                break;
            default:
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_MODE;
            }
        }
        // negate
        APPLY_CHILD_BOOL_VALUE(gating_block_node, "negate",
            device_config->gating_block[0].negate, XHPTDC8_APPLY_YAML_GTBLCK_INVALID_NEGATE);

        // retrigger
        APPLY_CHILD_BOOL_VALUE(gating_block_node, "retrigger",
            device_config->gating_block[0].retrigger, XHPTDC8_APPLY_YAML_GTBLCK_INVALID_RETRIG);

        // Ignore "extend", not implemented
        // start
        APPLY_CHILD_INTEGER_VALUE(gating_block_node, "start",
            ((0 <= val) && (val <= (65536 - 1))), device_config->gating_block[0].start,
            XHPTDC8_APPLY_YAML_GTBLCK_INVALID_START);

        // stop
        ryml::NodeRef stop_node = gating_block_node.find_child("stop");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(stop_node))
        {
            int val;
            if (!_node_val_toi_internal(&stop_node, &val))
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP;
            }
            if ((0 <= val) && (val <= (65536 - 1)))
            {
                if (val < device_config->gating_block[0].start)
                {
                    return XHPTDC8_APPLY_YAML_GTBLCK_STOP_B4_START;
                }
                else
                {
                    device_config->gating_block[0].stop = val;
                    VERBOSE_DEBUG_MSG_YAML_APPLIED_I(gating_block_node, "stop", val);
                }
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP;
            }
        }
        // sources
        APPLY_CHILD_INTEGER_VALUE(gating_block_node, "sources", val > 0,
            device_config->gating_block[0].sources,
            XHPTDC8_APPLY_YAML_GTBLCK_INVALID_SOURCES);
    }
    return gating_block_children_count;
}

/*
* Return 0: Not found/no impact, no error
*        N: Count of successfully updated tiger_block
*       -ve: Error
*/
int xhptdc8_apply_tiger_block_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    VALIDATE_APPLY_YAMAL_PARAMS;

    ryml::NodeRef tiger_block_node = (*device_config_node).find_child("tiger_block");
    if (!RYML_NODE_EXISTS(tiger_block_node))
    {
        return 0;
    }

    int tiger_block_children_count = 0;
    tiger_block_children_count = tiger_block_node.num_children();
    VALIDATE_CHILDREN_COUNT(tiger_block_children_count, XHPTDC8_TIGER_COUNT,
        XHPTDC8_APPLY_YAML_ERR_TGRBLCK_EXCEED_MAX);

    crono_bool_t is_array_map = _is_node_array_map(&tiger_block_node);
    if (is_array_map)
    {
        // Check "-1" in the first item, apply on all
        crono_bool_t apply_first_on_all_elements = false;
        ryml::NodeRef tiger_block_first_item_node = tiger_block_node.child(0);
        int tiger_block_index_in_cfg = _get_node_key_name_toi_internal(&tiger_block_first_item_node);
        if (-1 == tiger_block_index_in_cfg)
        {
            apply_first_on_all_elements = true;
            tiger_block_children_count = XHPTDC8_TIGER_COUNT;

            VERBOSE_DEBUG_MSG("Applying -1 element on all <%s> elements, ignoring all the rest if found\n",
                "tiger_block");
        }
        // Apply values 
        ryml::NodeRef child_node;
        for (int tiger_block_index = 0; tiger_block_index < tiger_block_children_count; tiger_block_index++)
        {
            if (apply_first_on_all_elements)
            {
                child_node = tiger_block_first_item_node;
                tiger_block_index_in_cfg = tiger_block_index;
            }
            else
            {
                child_node = tiger_block_node.child(tiger_block_index);
                tiger_block_index_in_cfg = _get_node_key_name_toi_internal(&child_node);

                VALIDATE_ARRAY_INDEX(tiger_block_index_in_cfg, XHPTDC8_TIGER_COUNT,
                    XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_STRUCT, XHPTDC8_APPLY_YAML_ERR_TGRBLCK_EXCEED_MAX);
            }
            // mode
            ryml::NodeRef mode_node = child_node.find_child("mode");
            if (RYML_NODE_EXISTS_AND_HAS_VAL(mode_node))
            {
                int val;
                if (!_node_val_toi_internal(&mode_node, &val))
                {
                    return XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_MODE;
                }
                switch (val) {
                case XHPTDC8_TIGER_OFF:
                case XHPTDC8_TIGER_OUTPUT:
                case XHPTDC8_TIGER_BIDI:
                case XHPTDC8_TIGER_BIPOLAR:
                    device_config->tiger_block[tiger_block_index_in_cfg].mode = val;
                    VERBOSE_DEBUG_MSG_YAML_APPLIED_I(tiger_block_node, "mode", val);
                    break;
                default:
                    return XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_MODE;
                }
            }
            // negate
            APPLY_CHILD_BOOL_VALUE(child_node, "negate",
                device_config->tiger_block[tiger_block_index_in_cfg].negate, XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_NEGATE);

            // retrigger
            APPLY_CHILD_BOOL_VALUE(child_node, "retrigger",
                device_config->tiger_block[tiger_block_index_in_cfg].retrigger, XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_RETRIG);

            // Ignore "extend", not implemented
            // start
            APPLY_CHILD_INTEGER_VALUE(child_node, "start",
                ((0 <= val) && (val <= (65536 - 1))), device_config->tiger_block[tiger_block_index_in_cfg].start,
                XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_START);

            // stop
            ryml::NodeRef stop_node = child_node.find_child("stop");
            if (RYML_NODE_EXISTS_AND_HAS_VAL(stop_node))
            {
                int val;
                if (!_node_val_toi_internal(&stop_node, &val))
                {
                    return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP;
                }
                if ((0 <= val) && (val <= (65536 - 1)))
                {
                    if (val < device_config->tiger_block[tiger_block_index_in_cfg].start)
                    {
                        return XHPTDC8_APPLY_YAML_TGRBLCK_STOP_B4_START;
                    }
                    else
                    {
                        device_config->tiger_block[tiger_block_index_in_cfg].stop = val;
                        VERBOSE_DEBUG_MSG_YAML_APPLIED_I(tiger_block_node, "stop", val);
                    }
                }
                else
                {
                    return XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_STOP;
                }
            }
            // sources
            APPLY_CHILD_INTEGER_VALUE(child_node, "sources", val > 0,
                device_config->tiger_block[tiger_block_index_in_cfg].sources,
                XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_SOURCES);
        }
    }
    else
    // Is map with the values of only the first array element 
    {
        // mode
        ryml::NodeRef mode_node = tiger_block_node.find_child("mode");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(mode_node))
        {
            int val;
            if (!_node_val_toi_internal(&mode_node, &val))
            {
                return XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_MODE;
            }
            switch (val) {
            case XHPTDC8_TIGER_OFF:
            case XHPTDC8_TIGER_OUTPUT:
            case XHPTDC8_TIGER_BIDI:
            case XHPTDC8_TIGER_BIPOLAR:
                device_config->tiger_block[0].mode = val;
                VERBOSE_DEBUG_MSG_YAML_APPLIED_I(tiger_block_node, "mode", val);
                break;
            default:
                return XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_MODE;
            }
        }
        // negate
        APPLY_CHILD_BOOL_VALUE(tiger_block_node, "negate",
            device_config->tiger_block[0].negate, XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_NEGATE);

        // retrigger
        APPLY_CHILD_BOOL_VALUE(tiger_block_node, "retrigger",
            device_config->tiger_block[0].retrigger, XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_RETRIG);

        // Ignore "extend", not implemented
        // start
        APPLY_CHILD_INTEGER_VALUE(tiger_block_node, "start",
            ((0 <= val) && (val <= (65536 - 1))), device_config->tiger_block[0].start,
            XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_START);

        // stop
        ryml::NodeRef stop_node = tiger_block_node.find_child("stop");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(stop_node))
        {
            int val;
            if (!_node_val_toi_internal(&stop_node, &val))
            {
                return XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_STOP;
            }
            if ((0 <= val) && (val <= (65536 - 1)))
            {
                if (val < device_config->tiger_block[0].start)
                {
                    return XHPTDC8_APPLY_YAML_TGRBLCK_STOP_B4_START;
                }
                else
                {
                    device_config->tiger_block[0].stop = val;
                    VERBOSE_DEBUG_MSG_YAML_APPLIED_I(tiger_block_node, "stop", val);
                }
            }
            else
            {
                return XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_STOP;
            }
        }
        // sources
        APPLY_CHILD_INTEGER_VALUE(tiger_block_node, "sources", val > 0,
            device_config->tiger_block[0].sources,
            XHPTDC8_APPLY_YAML_TGRBLCK_INVALID_SOURCES);
    }
    return tiger_block_children_count;
}

/*
* Return 0: Not found/no impact, no error
*        1: Successful applying
*       -ve: Error
*/
int xhptdc8_apply_grouping_yaml(const ryml::NodeRef* config_mngr_node,
        xhptdc8_manager_configuration* manager_config)
{
    if (nullptr == manager_config || nullptr == config_mngr_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ( !RYML_NODE_EXISTS(*config_mngr_node) )
    {
        return XHPTDC8_APPLY_YAML_ERR_NO_CONF_MNGR;
    }
    ryml::NodeRef grouping_node = (*config_mngr_node).find_child("grouping");
    if (!RYML_NODE_EXISTS(grouping_node))
    {
        return 0;
    }
    // enabled
    APPLY_CHILD_BOOL_VALUE(grouping_node, "enabled",
        manager_config->grouping.enabled, XHPTDC8_APPLY_YAML_INVALID_GROUPING_ENABLED);

    // trigger_channel
    APPLY_CHILD_INTEGER_VALUE(grouping_node, "trigger_channel", 
        (val > 0) && (val < XHPTDC8_TDC_CHANNEL_COUNT),
        manager_config->grouping.trigger_channel, XHPTDC8_APPLY_YAML_INVALID_GROUPING_TRIGCH);

    // zero_channel
    APPLY_CHILD_INTEGER_VALUE(grouping_node, "zero_channel",
        ((val > 0) || (-1 == val)) && (val < XHPTDC8_TDC_CHANNEL_COUNT),
        manager_config->grouping.zero_channel, XHPTDC8_APPLY_YAML_INVALID_GROUPING_ZEROCH);

    // zero_channel_offset
    APPLY_CHILD_DOUBLE_VALUE(grouping_node, "zero_channel_offset",
        (val > 0), manager_config->grouping.zero_channel_offset, XHPTDC8_APPLY_YAML_INVALID_GROUPING_ZEROCHOFF);

    // range_start
    APPLY_CHILD_LONGLONG_VALUE(grouping_node, "range_start",
        true, manager_config->grouping.range_start, XHPTDC8_APPLY_YAML_INVALID_GROUPING_RANGE_START);

    // range_stop
    APPLY_CHILD_LONGLONG_VALUE(grouping_node, "range_stop",
        true, manager_config->grouping.range_stop, XHPTDC8_APPLY_YAML_INVALID_GROUPING_RANGE_STOP);

    // trigger_deadtime
    APPLY_CHILD_LONGLONG_VALUE(grouping_node, "trigger_deadtime",
        true, manager_config->grouping.trigger_deadtime, XHPTDC8_APPLY_YAML_INVALID_GROUPING_TRIGDT);

    // require_window_hit
    APPLY_CHILD_BOOL_VALUE(grouping_node, "require_window_hit",
        manager_config->grouping.require_window_hit, XHPTDC8_APPLY_YAML_INVALID_GROUPING_REQWINHIT);

    // window_start
    APPLY_CHILD_LONGLONG_VALUE(grouping_node, "window_start",
        true, manager_config->grouping.window_start, XHPTDC8_APPLY_YAML_INVALID_GROUPING_WINDO_START);

    // window_stop
    APPLY_CHILD_LONGLONG_VALUE(grouping_node, "window_stop",
        true, manager_config->grouping.window_stop, XHPTDC8_APPLY_YAML_INVALID_GROUPING_WINDO_STOP);

    // veto_mode
    APPLY_CHILD_INTEGER_VALUE(grouping_node, "veto_mode",
        (val == 0) || (val == 1) || (val == 2),
        manager_config->grouping.veto_mode, XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETOMD);

    // veto_start
    APPLY_CHILD_LONGLONG_VALUE(grouping_node, "veto_start",
        true, manager_config->grouping.veto_start, XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETO_START);

    // veto_stop
    APPLY_CHILD_LONGLONG_VALUE(grouping_node, "veto_stop",
        true, manager_config->grouping.veto_stop, XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETO_STOP);

    // veto_relative_to_zero
    APPLY_CHILD_BOOL_VALUE(grouping_node, "veto_relative_to_zero",
        manager_config->grouping.veto_relative_to_zero, XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETORZERO);

    // overlap, unsupported, ignore
    return 1;
}

/*
* Return 1: Success, no error
*       -ve: Error
*/
int xhptdc8_apply_device_config_yaml(const ryml::NodeRef* device_config_node,
        xhptdc8_device_configuration* device_config)
{
    VALIDATE_APPLY_YAMAL_PARAMS;

    // auto_trigger_periods
#ifdef _DEBUG
    list_ryml_children(device_config_node);
#endif

    // auto_trigger_period
    APPLY_CHILD_INTEGER_VALUE((*device_config_node), "auto_trigger_period", val > 0,
        device_config->auto_trigger_period, XHPTDC8_APPLY_YAML_INVALID_AUTO_TRIG_PRD);

    // auto_trigger_random_exponent
    APPLY_CHILD_INTEGER_VALUE((*device_config_node), "auto_trigger_random_exponent", val > 0,
        device_config->auto_trigger_random_exponent, XHPTDC8_APPLY_YAML_INVALID_AUTO_TRIG_RAND);

    int result;
    // trigger_threshold
    result = xhptdc8_apply_trigger_threshold_yaml(device_config_node, device_config);
    if (result < 0)
    {
        return result;
    }
    // trigger
    result = xhptdc8_apply_trigger_yaml(device_config_node, device_config);
    if (result < 0)
    {   
        return result;
    }
    // gating_block
    result = xhptdc8_apply_gating_block_yaml(device_config_node, device_config);
    if (result < 0)
    {
        return result;
    }
    // tiger_block
    result = xhptdc8_apply_tiger_block_yaml(device_config_node, device_config);
    if (result < 0)
    {
        return result;
    }
    // channel
    result = xhptdc8_apply_channel_yaml(device_config_node, device_config);
    if (result < 0)
    {
        return result;
    }
    // adc_channel
    result = xhptdc8_apply_adc_channel_yaml(device_config_node, device_config);
    if (result < 0)
    {
        return result;
    }
    // skip_alignment
    APPLY_CHILD_BOOL_VALUE((*device_config_node), "skip_alignment", device_config->skip_alignment,
        XHPTDC8_APPLY_YAML_INVALID_SKIP_ALGNMT);

    // alignment_source
    APPLY_CHILD_INTEGER_VALUE((*device_config_node), "alignment_source", 
        (0 == val) || (1 == val) || (2 == val),
        device_config->alignment_source, XHPTDC8_APPLY_YAML_INVALID_ALGNMT_SRCE);

    return 1;
}

/*
* Whatever values provided in yaml_string will overwrite the corresponsing 
* value in configs, members that are not referenced in yaml_string will be left
* unchanged in configs
* 
* Return N  : Count of device configurations updated
*       -ve : Error
*/

int xhptdc8_apply_yaml(xhptdc8_manager_configuration* manager_config, const char* yaml_string)
{
    int configs_count = 0;

    // Validate inputs
    if (nullptr == manager_config)
        return XHPTDC8_INVALID_ARGUMENTS;

    if (nullptr == yaml_string)
        return XHPTDC8_INVALID_ARGUMENTS;

    // Parse YAML String and build the tree
    c4::substr config_mngr_src((char*)yaml_string, strlen(yaml_string)) ;
    ryml::Tree config_mngr_tree = ryml::parse(config_mngr_src);
    config_mngr_tree.resolve();
    
    // Get and validate Cofiguration Manager node
    ryml::NodeRef device_configs_node;
    ryml::NodeRef config_mngr_node = config_mngr_tree[YAML_XHPTDC8_MANAGER_CONFIG_NAME];
    if (!RYML_NODE_EXISTS(config_mngr_node))
    {
        return XHPTDC8_APPLY_YAML_ERR_NO_CONF_MNGR;
    }

    // Loop on the device configurations and apply the passed data
    configs_count = xhptdc8_yaml_get_configs_count(&config_mngr_node, &device_configs_node);
    if (configs_count < 0)
    // Error 
    {
        return configs_count;
    }
    // Check "-1" in the first item, apply on all
    crono_bool_t apply_first_on_all_elements = false;
    ryml::NodeRef device_configs_first_item_node = device_configs_node.child(0);
    int device_configs_children_count;
    int device_config_index_in_cfg = _get_node_key_name_toi_internal(&device_configs_first_item_node);
    if (-1 == device_config_index_in_cfg)
    {
        apply_first_on_all_elements = true;
        device_configs_children_count = XHPTDC8_MANAGER_DEVICES_MAX;

        VERBOSE_DEBUG_MSG("Applying -1 element on all <%s> elements, ignoring all the rest if found\n",
            YAML_XHPTDC8_MANAGER_CONFIG_NAME);
    }
    // Apply values 
    // Loop on the YAML configurations
    ryml::NodeRef device_config_node;
    int device_index_in_cfg;
    for (int config_index = 0; config_index < configs_count; config_index++)
    {
        if (apply_first_on_all_elements)
        {
            device_config_node = device_configs_first_item_node;
            device_index_in_cfg = config_index;
        }
        else
        {
            device_config_node = device_configs_node.child(config_index);
            device_index_in_cfg = _get_node_key_name_toi_internal(&device_config_node);

            VALIDATE_ARRAY_INDEX(device_index_in_cfg, XHPTDC8_MANAGER_DEVICES_MAX,
                XHPTDC8_APPLY_YAML_ERR_EMPTY_CONF_MNGR, XHPTDC8_APPLY_YAML_ERR_CONFS_EXCEED_MAX);
        }
        int result = xhptdc8_apply_device_config_yaml(&device_config_node,
                &(manager_config->device_configs[device_index_in_cfg]));
        if (result < 0)
        {
            return result;
        }
    }
    int result = xhptdc8_apply_grouping_yaml(&config_mngr_node, manager_config);
    if (result < 0)
    // Error
    {
        return result;
    }

    return configs_count;
}
