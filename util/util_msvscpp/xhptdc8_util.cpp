#include "pch.h"
#include "crono_interface.h"
#include "xHPTDC8_interface.h"
#include "xhptdc8_util.h"
#include "ryml.hpp"
#include <string>

using namespace std;
int _get_node_key_name_internal(const ryml::NodeRef* pNode, std::string* buff);
int _get_node_val_internal(const ryml::NodeRef* pNode, std::string* buff);

#define RYML_NODE_EXISTS(ryml_node) ((ryml_node).valid() && !((ryml_node).is_seed()))
#define RYML_NODE_EXISTS_AND_HAS_VAL(ryml_node) \
    (   (ryml_node).valid() \
    && !((ryml_node).is_seed()) \
    && (ryml_node).has_val()    )

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
*/
int _node_val_toi_internal(const ryml::NodeRef* pNode)
{
    std::string val;
    _get_node_val_internal(pNode, &val);
    return stoi(val.c_str());
}

/*
* Caller ensures the the node has value
*/
double _node_val_tod_internal(const ryml::NodeRef* pNode)
{
    std::string val;
    _get_node_val_internal(pNode, &val);
    return stod(val.c_str());
}

/*
* Caller ensures the the node has value
*/
long long _node_val_toll_internal(const ryml::NodeRef* pNode)
{
    std::string val;
    _get_node_val_internal(pNode, &val);
    return stoll(val.c_str());
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
    if (nullptr == device_config || nullptr == device_config_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ((!RYML_NODE_EXISTS(*device_config_node)) || (device_config_node->num_children() <= 0))
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF;
    }
    ryml::NodeRef trigger_threshold_node = (*device_config_node).find_child("trigger_threshold");
    if (!RYML_NODE_EXISTS(trigger_threshold_node))
    {
        return 0;
    }
    int trigger_thresholds_count = 0;
    trigger_thresholds_count = trigger_threshold_node.num_children();
    if ( trigger_thresholds_count <= 0 )
    {
        return 0;
    }
    if (trigger_thresholds_count > XHPTDC8_TDC_CHANNEL_COUNT)
    {
        return XHPTDC8_APPLY_YAML_THRESHOLDS_EXCEED_MAX;
    }
    for (int threshold_index = 0; threshold_index < trigger_thresholds_count; threshold_index++)
    {
        ryml::NodeRef threshold_item_node = trigger_threshold_node[threshold_index];
        double val = _node_val_tod_internal(&threshold_item_node);
        if ((val < -1.32) || (val > 1.18))
        {
            return XHPTDC8_APPLY_YAML_INVALID_THRESHOLD;
        }
        device_config->trigger_threshold[threshold_index] = val;
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
    if (nullptr == device_config || nullptr == device_config_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ((!RYML_NODE_EXISTS(*device_config_node)) || (device_config_node->num_children() <= 0))
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF;
    }
    ryml::NodeRef trigger_node = (*device_config_node).find_child("trigger");
    if (!RYML_NODE_EXISTS(trigger_node))
    {
        return 0;
    }
    int triggers_count = 0;
    triggers_count = trigger_node.num_children();
    if (triggers_count <= 0)
    {
        return 0;
    }
    if (triggers_count > XHPTDC8_TRIGGER_COUNT)
    {
        return XHPTDC8_APPLY_YAML_TRIGGERS_EXCEED_MAX;
    }
    for (int trigger_index = 0; trigger_index < triggers_count; trigger_index++)
    {
        ryml::NodeRef falling_node = trigger_node[trigger_index].find_child("falling");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(falling_node))
        {
            c4::csubstr val = falling_node.val();
            if (!val.compare("false"))
            {
                device_config->trigger[trigger_index].falling = false;
            }
            else if (!val.compare("true"))
            {
                device_config->trigger[trigger_index].falling = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_INVALID_TRIGGERS_FALL;
            }
        }
        ryml::NodeRef rising_node = trigger_node[trigger_index].find_child("rising");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(rising_node))
        {
            c4::csubstr val = rising_node.val();
            if (!val.compare("false"))
            {
                device_config->trigger[trigger_index].rising = false;
            }
            else if (!val.compare("true"))
            {
                device_config->trigger[trigger_index].rising = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_INVALID_TRIGGERS_RISING;
            }
        }
    }
    return triggers_count;
}

/*
* Return 0: Not found/no impact, no error
*        N: Count of successfully updated channel
*       -ve: Error
*/
int xhptdc8_apply_channel_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    if (nullptr == device_config || nullptr == device_config_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ((!RYML_NODE_EXISTS(*device_config_node)) || (device_config_node->num_children() <= 0))
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF;
    }
    ryml::NodeRef channel_node = (*device_config_node).find_child("channel");
    if (!RYML_NODE_EXISTS(channel_node))
    {
        return 0;
    }
    int channels_count = 0;
    channels_count = channel_node.num_children();
    if (channels_count <= 0)
    {
        return 0;
    }
    if (channels_count > XHPTDC8_TDC_CHANNEL_COUNT)
    {
        return XHPTDC8_APPLY_YAML_CHANNELS_EXCEED_MAX;
    }
    for (int channel_index = 0; channel_index < channels_count; channel_index++)
    {
        ryml::NodeRef falling_node = channel_node[channel_index].find_child("falling");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(falling_node))
        {
            c4::csubstr val = falling_node.val();
            if (!val.compare("false"))
            {
                device_config->channel[channel_index].enable = false;
            }
            else if (!val.compare("true"))
            {
                device_config->channel[channel_index].enable = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_INVALID_CHANNEL_ENABLE;
            }
        }
        ryml::NodeRef rising_node = channel_node[channel_index].find_child("rising");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(rising_node))
        {
            c4::csubstr val = rising_node.val();
            if (!val.compare("false"))
            {
                device_config->channel[channel_index].rising = false;
            }
            else if (!val.compare("true"))
            {
                device_config->channel[channel_index].rising = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_INVALID_CHANNEL_RISING;
            }
        }
    }
    return channels_count;
}

/*
* Return 0: Not found/no impact, no error
*        1: Successful applying
*       -ve: Error
*/
int xhptdc8_apply_adc_channel_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    if (nullptr == device_config || nullptr == device_config_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ((!RYML_NODE_EXISTS(*device_config_node)) || (device_config_node->num_children() <= 0))
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF;
    }
    ryml::NodeRef adc_channel_node = (*device_config_node).find_child("adc_channel");
    if (!RYML_NODE_EXISTS(adc_channel_node))
    {
        return 0;
    }
    // enable
    ryml::NodeRef enable_node = adc_channel_node.find_child("enable");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(enable_node))
    {
        c4::csubstr val = enable_node.val();
        if (!val.compare("false"))
        {
            device_config->adc_channel.enable = false;
        }
        else if (!val.compare("true"))
        {
            device_config->adc_channel.enable = true;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_ENABLE;
        }
    }
    // watchdog_readout
    ryml::NodeRef watchdog_readout_node = adc_channel_node.find_child("watchdog_readout");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(watchdog_readout_node))
    {
        c4::csubstr val = watchdog_readout_node.val();
        if (!val.compare("false"))
        {
            device_config->adc_channel.watchdog_readout = false;
        }
        else if (!val.compare("true"))
        {
            device_config->adc_channel.watchdog_readout = true;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_WDRO;
        }
    }
    // watchdog_interval
    ryml::NodeRef watchdog_interval_node = adc_channel_node.find_child("watchdog_interval");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(watchdog_interval_node))
    {
        int val = _node_val_toi_internal(&watchdog_interval_node);
        if (val > 0)
        {
            device_config->adc_channel.watchdog_interval = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_WDI;
        }
    }
    // trigger_threshold
    ryml::NodeRef trigger_threshold_node = adc_channel_node.find_child("trigger_threshold");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(trigger_threshold_node))
    {
        double val = _node_val_tod_internal(&trigger_threshold_node);
        if (val > 0)
        {
            device_config->adc_channel.trigger_threshold = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_ADC_CHANNEL_TRTHRESH;
        }
    }
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
    if (nullptr == device_config || nullptr == device_config_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ((!RYML_NODE_EXISTS(*device_config_node)) || (device_config_node->num_children() <= 0))
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF;
    }
    ryml::NodeRef gating_block_node = (*device_config_node).find_child("gating_block");
    if (!RYML_NODE_EXISTS(gating_block_node))
    {
        return 0;
    }
    int gating_blocks_count = 0;
    gating_blocks_count = gating_block_node.num_children();
    if (gating_blocks_count <= 0)
    {
        return 0;
    }
    if (gating_blocks_count > XHPTDC8_GATE_COUNT)
    {
        return XHPTDC8_APPLY_YAML_GATE_BLOCK_EXCEED_MAX;
    }
    for (int gating_block_index = 0; gating_block_index < gating_blocks_count; gating_block_index++)
    {
        // mode
        ryml::NodeRef mode_node = gating_block_node[gating_block_index].find_child("mode");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(mode_node))
        {
            int val = _node_val_toi_internal(&mode_node);
            switch(val) {
                case XHPTDC8_TIGER_OFF:
                case XHPTDC8_TIGER_OUTPUT: 
                case XHPTDC8_TIGER_BIDI:
                case XHPTDC8_TIGER_BIPOLAR: 
                    device_config->gating_block[gating_block_index].mode = val;
                    break;
                default: 
                    return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_MODE;
            }
        }
        // negate
        ryml::NodeRef negate_node = gating_block_node[gating_block_index].find_child("negate");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(negate_node))
        {
            c4::csubstr val = negate_node.val();
            if (!val.compare("false"))
            {
                device_config->gating_block[gating_block_index].negate = false;
            }
            else if (!val.compare("true"))
            {
                device_config->gating_block[gating_block_index].negate = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_NEGATE;
            }
        }
        // retrigger
        ryml::NodeRef retrigger_node = gating_block_node[gating_block_index].find_child("retrigger");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(retrigger_node))
        {
            c4::csubstr val = retrigger_node.val();
            if (!val.compare("false"))
            {
                device_config->gating_block[gating_block_index].retrigger = false;
            }
            else if (!val.compare("true"))
            {
                device_config->gating_block[gating_block_index].retrigger = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_RETRIG;
            }
        }
        // Ignore "extend", not implemented
        // start
        ryml::NodeRef start_node = gating_block_node[gating_block_index].find_child("start");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(start_node))
        {
            int val = _node_val_toi_internal(&start_node);
            if ( (0 <= val) && (val <= (65536-1)) )   
            {
                device_config->gating_block[gating_block_index].start = val;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_START;
            }
        }
        // stop
        ryml::NodeRef stop_node = gating_block_node[gating_block_index].find_child("stop");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(stop_node))
        {
            int val = _node_val_toi_internal(&stop_node);
            if ((0 <= val) && (val <= (65536 - 1)))
            {
                if (val < device_config->gating_block[gating_block_index].start)
                {
                    return XHPTDC8_APPLY_YAML_GTBLCK_STOP_B4_START;
                }
                else
                {
                    device_config->gating_block[gating_block_index].stop = val;
                }
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP;
            }
        }
        // sources
        ryml::NodeRef sources_node = gating_block_node[gating_block_index].find_child("sources");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(sources_node))
        {
            int val = _node_val_toi_internal(&sources_node);
            if ( val >= 0 )
            {
                device_config->gating_block[gating_block_index].sources = val;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_SOURCES;
            }
        }
    }
    return gating_blocks_count;
}

/*
* Return 0: Not found/no impact, no error
*        N: Count of successfully updated tiger_block
*       -ve: Error
*/
int xhptdc8_apply_tiger_block_yaml(const ryml::NodeRef* device_config_node,
    xhptdc8_device_configuration* device_config)
{
    if (nullptr == device_config || nullptr == device_config_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if ((!RYML_NODE_EXISTS(*device_config_node)) || (device_config_node->num_children() <= 0))
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF;
    }
    ryml::NodeRef tiger_block_node = (*device_config_node).find_child("tiger_block");
    if (!RYML_NODE_EXISTS(tiger_block_node))
    {
        return 0;
    }
    int tiger_blocks_count = 0;
    tiger_blocks_count = tiger_block_node.num_children();
    if (tiger_blocks_count <= 0)
    {
        return 0;
    }
    if (tiger_blocks_count > XHPTDC8_TIGER_COUNT)
    {
        return XHPTDC8_APPLY_YAML_GATE_BLOCK_EXCEED_MAX;
    }
    for (int tiger_block_index = 0; tiger_block_index < tiger_blocks_count; tiger_block_index++)
    {
        // mode
        ryml::NodeRef mode_node = tiger_block_node[tiger_block_index].find_child("mode");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(mode_node))
        {
            int val = _node_val_toi_internal(&mode_node);
            switch (val) {
            case XHPTDC8_TIGER_OFF:
            case XHPTDC8_TIGER_OUTPUT:
            case XHPTDC8_TIGER_BIDI:
            case XHPTDC8_TIGER_BIPOLAR:
                device_config->tiger_block[tiger_block_index].mode = val;
                break;
            default:
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_MODE;
            }
        }
        // negate
        ryml::NodeRef negate_node = tiger_block_node[tiger_block_index].find_child("negate");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(negate_node))
        {
            c4::csubstr val = negate_node.val();
            if (!val.compare("false"))
            {
                device_config->tiger_block[tiger_block_index].negate = false;
            }
            else if (!val.compare("true"))
            {
                device_config->tiger_block[tiger_block_index].negate = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_NEGATE;
            }
        }
        // retrigger
        ryml::NodeRef retrigger_node = tiger_block_node[tiger_block_index].find_child("retrigger");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(retrigger_node))
        {
            c4::csubstr val = retrigger_node.val();
            if (!val.compare("false"))
            {
                device_config->tiger_block[tiger_block_index].retrigger = false;
            }
            else if (!val.compare("true"))
            {
                device_config->tiger_block[tiger_block_index].retrigger = true;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_RETRIG;
            }
        }
        // Ignore "extend", not implemented
        // start
        ryml::NodeRef start_node = tiger_block_node[tiger_block_index].find_child("start");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(start_node))
        {
            int val = _node_val_toi_internal(&start_node);
            if ((0 <= val) && (val <= (65536 - 1)))
            {
                device_config->tiger_block[tiger_block_index].start = val;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_START;
            }
        }
        // stop
        ryml::NodeRef stop_node = tiger_block_node[tiger_block_index].find_child("stop");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(stop_node))
        {
            int val = _node_val_toi_internal(&stop_node);
            if ((0 <= val) && (val <= (65536 - 1)))
            {
                if (val < device_config->tiger_block[tiger_block_index].start)
                {
                    return XHPTDC8_APPLY_YAML_GTBLCK_STOP_B4_START;
                }
                else
                {
                    device_config->tiger_block[tiger_block_index].stop = val;
                }
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_STOP;
            }
        }
        // sources
        ryml::NodeRef sources_node = tiger_block_node[tiger_block_index].find_child("sources");
        if (RYML_NODE_EXISTS_AND_HAS_VAL(sources_node))
        {
            int val = _node_val_toi_internal(&sources_node);
            if (val >= 0)
            {
                device_config->tiger_block[tiger_block_index].sources = val;
            }
            else
            {
                return XHPTDC8_APPLY_YAML_GTBLCK_INVALID_SOURCES;
            }
        }
    }
    return tiger_blocks_count;
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
    ryml::NodeRef enabled_node = grouping_node.find_child("enabled");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(enabled_node))
    {
        c4::csubstr val = enabled_node.val();
        if (!val.compare("false"))
        {
            manager_config->grouping.enabled = false;
        }
        else if (!val.compare("true"))
        {
            manager_config->grouping.enabled = true;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_ENABLED;
        }
    }
    // trigger_channel
    ryml::NodeRef trigger_channel_node = grouping_node.find_child("trigger_channel");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(trigger_channel_node))
    {
        int val = _node_val_toi_internal(&trigger_channel_node);
        if ((val > 0) && (val < XHPTDC8_TDC_CHANNEL_COUNT))
        {
            manager_config->grouping.trigger_channel = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_TRIGCH;
        }
    }
    // zero_channel
    ryml::NodeRef zero_channel_node = grouping_node.find_child("zero_channel");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(zero_channel_node))
    {
        int val = _node_val_toi_internal(&zero_channel_node);
        if (((val > 0) || (-1 == val)) && (val < XHPTDC8_TDC_CHANNEL_COUNT))
        {
            manager_config->grouping.zero_channel = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_ZEROCH;
        }
    }
    // zero_channel_offset
    ryml::NodeRef zero_channel_offset_node = grouping_node.find_child("zero_channel_offset");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(zero_channel_offset_node))
    {
        long long val = _node_val_toll_internal(&zero_channel_offset_node);
        if ( val > 0 )
        {
            manager_config->grouping.zero_channel_offset = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_ZEROCHOFF;
        }
    }
    // range_start
    ryml::NodeRef range_start_node = grouping_node.find_child("range_start");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(range_start_node))
    {
        long long val = _node_val_toll_internal(&range_start_node);
        manager_config->grouping.range_start = val;
    }
    // range_stop
    ryml::NodeRef range_stop_node = grouping_node.find_child("range_stop");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(range_stop_node))
    {
        long long val = _node_val_toll_internal(&range_stop_node);
        manager_config->grouping.range_stop = val;
    }
    // trigger_deadtime
    ryml::NodeRef trigger_deadtime_node = grouping_node.find_child("trigger_deadtime");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(trigger_deadtime_node))
    {
        long long val = _node_val_toll_internal(&trigger_deadtime_node);
        if (val > 0)
        {
            manager_config->grouping.trigger_deadtime = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_TRIGDT;
        }
    }
    // require_window_hit
    ryml::NodeRef require_window_hit_node = grouping_node.find_child("require_window_hit");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(require_window_hit_node))
    {
        c4::csubstr val = require_window_hit_node.val();
        if (!val.compare("false"))
        {
            manager_config->grouping.require_window_hit = false;
        }
        else if (!val.compare("true"))
        {
            manager_config->grouping.require_window_hit = true;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_REQWINHIT;
        }
    }
    // window_start
    ryml::NodeRef window_start_node = grouping_node.find_child("window_start");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(window_start_node))
    {
        long long val = _node_val_toll_internal(&window_start_node);
        manager_config->grouping.window_start = val;
    }
    // window_stop
    ryml::NodeRef window_stop_node = grouping_node.find_child("window_stop");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(window_stop_node))
    {
        long long val = _node_val_toll_internal(&window_stop_node);
        manager_config->grouping.window_stop = val;
    }
    // veto_mode
    ryml::NodeRef veto_mode_node = grouping_node.find_child("veto_mode");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(veto_mode_node))
    {
        int val = _node_val_toi_internal(&veto_mode_node);
        if ( (val == 0) || (val == 1) || (val == 2) )
        {
            manager_config->grouping.veto_mode = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETOMD;
        }
    }
    // veto_start
    ryml::NodeRef veto_start_node = grouping_node.find_child("veto_start");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(veto_start_node))
    {
        long long val = _node_val_toll_internal(&veto_start_node);
        manager_config->grouping.veto_start = val;
    }
    // veto_stop
    ryml::NodeRef veto_stop_node = grouping_node.find_child("veto_stop");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(veto_stop_node))
    {
        long long val = _node_val_toll_internal(&veto_stop_node);
        manager_config->grouping.veto_stop = val;
    }
    // veto_relative_to_zero
    ryml::NodeRef veto_relative_to_zero_node = grouping_node.find_child("veto_relative_to_zero");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(veto_relative_to_zero_node))
    {
        c4::csubstr val = veto_relative_to_zero_node.val();
        if (!val.compare("false"))
        {
            manager_config->grouping.veto_relative_to_zero = false;
        }
        else if (!val.compare("true"))
        {
            manager_config->grouping.veto_relative_to_zero = true;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_GROUPING_VETORZERO;
        }
    }
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
    if (nullptr == device_config || nullptr == device_config_node)
    {
        return XHPTDC8_APPLY_YAML_INVALID_ARGUMENT;
    }
    if (   (!RYML_NODE_EXISTS(*device_config_node)) || (device_config_node->num_children() <= 0) )
    {
        return XHPTDC8_APPLY_YAML_ERR_EMPTY_DEV_CONF;
    }
    // auto_trigger_period
#ifdef _DEBUG
    list_ryml_children(device_config_node);
#endif

    ryml::NodeRef auto_trigger_period_node = (*device_config_node).find_child("auto_trigger_period");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(auto_trigger_period_node))
    {
        int val = _node_val_toi_internal(&auto_trigger_period_node);
        if (val >= 0)
        {
            device_config->auto_trigger_period = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_AUTO_TRIG_PRD;
        }
    }
    // auto_trigger_period
    ryml::NodeRef ch = (*device_config_node).find_child("auto_trigger_random_exponent");
    bool b = RYML_NODE_EXISTS_AND_HAS_VAL(ch) ;
    ryml::NodeRef auto_trigger_random_exponent_node = 
            (*device_config_node).find_child("auto_trigger_random_exponent");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(auto_trigger_random_exponent_node))
    {
        int val = _node_val_toi_internal(&auto_trigger_random_exponent_node);
        if (val >= 0)
        {
            device_config->auto_trigger_random_exponent = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_AUTO_TRIG_RAND;
        }
    }
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
    ryml::NodeRef skip_alignment_node = (*device_config_node).find_child("skip_alignment");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(skip_alignment_node))
    {
        c4::csubstr val = skip_alignment_node.val();
        if (!val.compare("false"))
        {
            device_config->skip_alignment = false;
        }
        else if (!val.compare("true"))
        {
            device_config->skip_alignment = true;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_SKIP_ALGNMT;
        }
    }
    // alignment_source
    ryml::NodeRef alignment_source_node = (*device_config_node).find_child("alignment_source");
    if (RYML_NODE_EXISTS_AND_HAS_VAL(alignment_source_node))
    {
        int val = _node_val_toi_internal(&alignment_source_node);
        if ((0 == val) || (1 == val) || (2 == val))
        {
            device_config->alignment_source = val;
        }
        else
        {
            return XHPTDC8_APPLY_YAML_INVALID_ALGNMT_SRCE;
        }
    }
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
    // Loop on the YAML configurations
    for (int config_index = 0; config_index < configs_count; config_index++)
    {
        ryml::NodeRef device_config_node = device_configs_node[config_index];
        int result = xhptdc8_apply_device_config_yaml(&device_config_node,
                &(manager_config->device_configs[config_index]));
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
