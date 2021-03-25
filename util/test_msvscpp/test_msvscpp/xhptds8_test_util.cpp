// test_msvscpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "xhptdc8_util.h"
#include "xhptdc8_interface.h"

void test_apply_yaml_all_keys_structure();
void test_apply_yaml_breif_sample();

/*
* String has all keys of the manager_config structure
*/
char mngr_all_keys_sample[1213] =
{
" manager_config: \n"
"  device_configs: \n"
"   - \n"
"    auto_trigger_period : 20 \n"
"    auto_trigger_random_exponent : 20 \n"
"    trigger_threshold : \n"
"     - 0.3499 \n"
"     - 0.35 \n"
"     - 0.36666 \n"
"    trigger : \n"
"     - \n"
"      falling : false \n"
"      rising : true \n"
"    gating_block : \n"
"     - \n"
"      mode : 1 \n"
"      negate : true \n"
"      retrigger : true \n"
"      extend : true \n"
"      start : 10 \n"
"      stop : 190 \n"
"      sources : 1 \n"
"    tiger_block : \n"
"     - \n"
"      mode : 2 \n"
"      negate : true \n"
"      retrigger : true \n"
"      extend : true \n"
"      start : 20 \n"
"      stop : 200 \n"
"      sources : 2 \n"
"    channel : \n"
"     - \n"
"      enable : true\n"
"      rising : true \n"
"    adc_channel : \n"
"     enable : true \n"
"     watchdog_readout : true \n"
"     watchdog_interval : 5 \n"
"     trigger_threshold : 6 \n"
"    skip_alignment : true \n"
"    alignment_source : 1 \n"
"  grouping : \n"
"   enabled : true \n"
"   trigger_channel : 3 \n"
"   zero_channel : 2 \n"
"   zero_channel_offset : 1 \n"
"   range_start : 12345 \n"
"   range_stop : 23456 \n"
"   trigger_deadtime : 25 \n"
"   require_window_hit : true \n"
"   window_start : 10 \n"
"   window_stop : 20 \n"
"   veto_mode : 2 \n"
"   veto_start : 30 \n"
"   veto_stop : 40 \n"
"   veto_relative_to_zero : true \n"
"   overlap : true \n"
};

char mngr_brief_sample[447] =
{
" manager_config: \n"
"  device_configs: \n"
"   - \n"
"    trigger : \n"
"     - \n"
"      falling : false \n"
"      rising : true \n"
"    trigger_threshold : \n"
"     - 0.3499 \n"
"     - 0.35 \n"
"     - 0.36666 \n"
"    gating_block : \n"
"     - \n"
"      mode : 1 \n"
"      negate : true \n"
"    auto_trigger_period : 20 \n"
"   - \n"
"    trigger : \n"
"     - \n"
"      falling : true \n"
"      rising : false \n"
"    channel : \n"
"     - \n"
"      enable : true\n"
"      rising : false \n"
"  grouping : \n"
"   enabled : true \n"
};

int main()
{
	test_apply_yaml_all_keys_structure();
	test_apply_yaml_breif_sample();
}

void test_apply_yaml(char* src)
{
	xhptdc8_manager hMgr;
	xhptdc8_manager_init_parameters* params = NULL;
	int error_code;
	char* error_message = NULL;
	xhptdc8_init(&hMgr, params, &error_code, (const char**)&error_message);
	xhptdc8_manager_configuration* cfg = new xhptdc8_manager_configuration;
	xhptdc8_get_default_configuration(hMgr, cfg);
	xhptdc8_apply_yaml(cfg, src);
	xhptdc8_configure(hMgr, cfg);
	delete cfg;
}
void test_apply_yaml_all_keys_structure()
{
	test_apply_yaml(mngr_all_keys_sample);
}
void test_apply_yaml_breif_sample()
{
	test_apply_yaml(mngr_brief_sample);
}