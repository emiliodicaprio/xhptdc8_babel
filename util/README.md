
# util_msvscpp Project

## About
Windows DLL that provides utility functionalities for xHPTDC8 Driver

## Microsoft Visual Studio Project 
The Solution and Project are created using Microsoft Visual Studio 2019

### Project Environments and Configurations
- Project Settings -> Include Directories : `..\..\include;..\..\..\lib\include;.\ryml_src;` is added.
- Project Settings -> Preprocessor Definitions: `XHPTDC8_UTIL_EXPORTS` is defined.

| Configuration | Environment   | Output Directory | Library Name    |
| ------------- |-------------  |----------------- | --------------- |
| Debug         | x64           | ..\\..\\lib\\x64    | xhptdc8_util_64 |  
| Release       | x64           | ..\\..\\lib\\x64    | xhptdc8_util_64 |  
| Debug         | Win32         | ..\\..\\lib\\x86    | xhptdc8_util    |  
| Release       | Win32         | ..\\..\\lib\\x86    | xhptdc8_util    |  
* You can change the output directory if you want to keep both the release and debug versions of the DLL concurrently

### External Libraries
The project uses the source code of the following libraries for YAML parser:
- https://github.com/biojppm/rapidyaml (main parser project)
- https://github.com/biojppm/c4core (needed by rapidyaml)
- https://github.com/biojppm/debugbreak/ (needed by rapidyaml)
- https://github.com/fastfloat/fast_float (needed by rapidyaml)

With the following actions:
- The source code of those libraries is downloaded and is added to the project.
- External project files are set to **Precompiled Header**: _Not Using Precompiled Headers_

### Building Using MS Visual Studio
Nothing special, just:
1. Using MS Visual Studio compatible version, open the solution file: `/util/util_msvscpp/util_msvscpp.sln`
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit _Build util_, and check the .lib & .dll files in the corresponsing directory as per the table above.

## Using the Utility Library

### Compile & Link Settings
In order to call functions from the utility library, you need to do the following:
1. Include `util/include/xhptdc8_util.h`
2. Link to the corresponsing library version on `util/lib/x86` or `util/lib/x64`

### xhptdc8_apply_yaml 
The purpose of this repository is to make using the [xHPTDC8 time-to-digital converter](https://www.cronologic.de/products/tdcs/xhptdc8-pcie) simpler to use for end users.

Setting up the xhptdc8_manager_configuration structure is rather complicated. This shall be simplified by allowing to apply YAML files to the structure.
So the workflow for the user would be:

```C++
xhptdc8_manager_configuration *cfg = new xhptdc8_manager_configuration;
xhptdc8_get_default_configuration(xhptdc8_mgr, cfg);
xhptdc8_apply_yaml(cfg, yaml_string);
xhptdc8_configure(hptdc8_mgr, cfg); 
```

The YAML can describe an incomplete structure.  When a structure member is present it is overwritten with the value from the YAML. Members that are missing in the YAML are left unchanged.

This API is of the following signature:
```C
int xhptdc8_apply_yaml(xhptdc8_manager_configuration* cfg, const char* yaml_string);
```

#### Simple Sample YAML:
```YAML
manager_config: 
 device_configs: 
  0: 
   auto_trigger_period : 20
   trigger : 
     falling : false 
     rising : true 
   trigger_threshold : 
    0: 0.3499 
    1: 0.35 
    2: 0.36666 
   gating_block : 
    0: 
     mode : 1 
     negate : true 
  1: 
   trigger : 
    0: 
     falling : true 
     rising : false 
   channel : 
    0: 
     enable : true
     rising : false 
 grouping : 
  enabled : true 
```

With debugging output as following:
```
Applied yaml on node child ([0] auto_trigger_period: 20) integer value
Applied yaml on node child ([0] trigger_threshold: 0.349900) integer value
Applied yaml on node child ([0] trigger_threshold: 0.350000) integer value
Applied yaml on node child ([0] trigger_threshold: 0.366660) integer value
Applied yaml on node child ([trigger] falling: false) bool value
Applied yaml on node child ([trigger] rising: true) bool value
Applied yaml on node child ([0] mode: 1) integer value
Applied yaml on node child ([0] negate: true) bool value
Applied yaml on node child ([0] falling: true) bool value
Applied yaml on node child ([0] rising: false) bool value
Applied yaml on node child ([0] enable: true) bool value
Applied yaml on node child ([0] rising: false) bool value
Applied yaml on node child ([grouping] enabled: true) bool value
```

#### Sample YAML with features
This sample shows how to use Anchors and Aliases, as well as the how it is possible to just modify an element in the middle of the array.
```YAML
threshold : &COMMON_THRESHOLD "120" # Anchor
trigger_threshold : &CMOS # Another anchor
 0: 0.3499 
manager_config: 
 device_configs: 
  0: 
   trigger : 
     falling : false 
     rising : true 
   trigger_threshold : *CMOS # Alias will be substituted by 0.3499
   adc_channel: 
    enable : true 
    watchdog_readout : true 
    watchdog_interval: 5 
    trigger_threshold : *COMMON_THRESHOLD # Alias will be substituted by 120
  1: 
   trigger_threshold : 
    1: 0.3499 # Start with the second element, leave the first to default
    2: 0.35 
    3: 0.36666 
   channel : 
    1: # Set the second channel configuration, leave the rest to default values
     enable : true
     rising : false 
```
With debugging output as following:
```
Applied yaml on node child ([0] trigger_threshold: 0.349900) integer value
Applied yaml on node child ([trigger] falling: false) bool value
Applied yaml on node child ([trigger] rising: true) bool value
Applied yaml on node child ([adc_channel] enable: true) bool value
Applied yaml on node child ([adc_channel] watchdog_readout: true) bool value
Applied yaml on node child ([adc_channel] watchdog_interval: 5) integer value
Applied yaml on node child ([adc_channel] trigger_threshold: 120.000000) integer value
Applied yaml on node child ([1] trigger_threshold: 0.349900) integer value
Applied yaml on node child ([1] trigger_threshold: 0.350000) integer value
Applied yaml on node child ([1] trigger_threshold: 0.366660) integer value
Applied yaml on node child ([1] enable: true) bool value
Applied yaml on node child ([1] rising: false) bool value
```

#### All Elements YAML
Here is the complete elements of the manager configuration sturcture, including sample values; you can copy your YAML elements from the YAML below, just keep the spaces before the elements, and refer to both the user guide and the [xHPTDC8_interface.h](/lib/include/xHPTDC8_interface.h "xHPTDC8_interface.h") xhptdc8_interface.h for the members specifications:

```YAML
manager_config: 
 device_configs: 
  0: 
   auto_trigger_period : 20 
   auto_trigger_random_exponent : 20 
   trigger_threshold : 
    0: 0.3499 
    1: 0.35 
    2: 0.36666 
   trigger : 
    0: 
     falling : false 
     rising : true 
   gating_block : 
    0: 
     mode : 1 
     negate : true 
     retrigger : true 
     extend : true 
     start : 10 
     stop : 190 
     sources : 1 
   tiger_block : 
    0:
     mode : 2 
     negate : true 
     retrigger : true 
     extend : true 
     start : 20 
     stop : 200 
     sources : 2 
   channel : 
    0: 
     enable : true
     rising : true 
   adc_channel : 
    enable : true 
    watchdog_readout : true 
    watchdog_interval : 5 
    trigger_threshold : 6 
   skip_alignment : true 
   alignment_source : 1 
 grouping : 
  enabled : true 
  trigger_channel : 3 
  zero_channel : 2 
  zero_channel_offset : 1 
  range_start : 12345 
  range_stop : 23456 
  trigger_deadtime : 25 
  require_window_hit : true 
  window_start : 10 
  window_stop : 20 
  veto_mode : 2 
  veto_start : 30 
  veto_stop : 40 
  veto_relative_to_zero : true 
  overlap : true 
```

#### Assigning the the values to multiple substructures
YAML allows to reused definitions from one place of the structure multiple times without writing them all over again.
This can be useful to set multiple boards to the same setting or multiple channels of one board.
This [this website](http://blogs.perl.org/users/tinita/2019/05/reusing-data-with-yaml-anchors-aliases-and-merge-keys.html) for a very short description how this works.

# test_msvscpp Project

## About
Windows Console Application that is used to provide sample code and data for calling the Utility DLL Functions

## Microsoft Visual Studio Project 
The Solution and Project are created using Microsoft Visual Studio 2019

### Project Environments and Configurations
### Building Using MS Visual Studio
### Running the Application
