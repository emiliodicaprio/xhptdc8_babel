
# util Project

## About
Windows DLL that provides utility functionalities for xHPTDC8 Driver

## Microsoft Visual Studio Project 
The Solution and Project are created using Microsoft Visual Studio 2019.</br>
The project structure follows [our standard project folder structure](https://github.com/cronologic-de/xhptdc8_babel/wiki/project_folder_structure).

### Project Environments and Configurations
- Project Settings -> Include Directories : `..\..\include;..\..\..\lib\include;.\ryml_src;` is added.
- Project Settings -> Preprocessor Definitions: `XHPTDC8_UTIL_EXPORTS` is defined.
- Project Settings -> Preprocessor Definitions: `XHPTDC8_VERBOSE_DEBUG` is defined for _Debug Configurations_ only.
- `Output Directory` is left as the Visual Studio _Default_ Project Settings.

| Config. | Env.  | Output Directory on github                      | Library Name    |
| ------- |------ | -----------------------------------------       | --------------  |
| Debug   | x64   | ..\\..\\..\\lib\x64dummy\; ..\\..\\..\\lib\x64\ | xhptdc8_util_64.dll |  
| Release | x64   | ..\\..\\..\\lib\x64dummy\; ..\\..\\..\\lib\x64\ | xhptdc8_util_64.dll |  
| Debug   | Win32 | ..\\..\\..\\lib\x86dummy\; ..\\..\\..\\lib\x86\ | xhptdc8_util.dll    |  
| Release | Win32 | ..\\..\\..\\lib\x86dummy\; ..\\..\\..\\lib\x86\ | xhptdc8_util.dll    |  
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
Project can be built using the following MSVS files:
1. [Project File: util.vcxproj](./util/msvscpp/util.vcxproj)
2. [Solution File: util.sln](./util/msvscpp/util.sln)
3. [xhptdc8_util_projects Solution File: xhptdc8_util_projects.sln](./msvscpp/xhptdc8_util_projects.sln)

Building the library locally is directing the output to the `dummy` corresponding output folder, as it's expected to be tested first using the `Dummy Library`. However, you can set the output directory to any other one from the project settings.

Nothing special, just:
1. Using MS Visual Studio compatible version, open one of the project or solution files mentioned above.
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit _Build util_, and check the .lib & .dll files in the corresponsing directory as per the table above.

### github Building Action
github [Building Action: Util Library MSBuild](https://github.com/cronologic-de/xhptdc8_babel/blob/main/.github/workflows/util_msbuild.yml) is created to build `util` project as following:
1. Using MSBuild.
2. It builds the code automatically with relevant code update.
3. It builds the `Release` configuration of both `x86` and `x64` environments.
4. It copies and checkin the output DLL and LIB files to _folder Output Directory on github_ mentioned in section _Project Environments and Configurations_.

## Using the Utility Library

### Compile & Link Settings
In order to call functions from the utility library, you need to do the following:
1. Include `/lib/include/xhptdc8_util.h`
2. Link to the corresponsing library version on `/lib/x86` or `/lib/x64`

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

#### Specifications
##### General 
- YAML String should comply with the standard YAML format

##### xHPTDC8-Specific
`manager_config` Arrays shall be implemented as maps not as sequences. The reason is that it shall be possible to assign only part of the array, which is not possible for sequences.

Array index starts with 0 (or -1), and should be less than the maximum array size defined in [xHPTDC8_interface.h](../lib/include/xHPTDC8_interface.h).</br>
_For example_: `trigger` array could have trigger index starting -1 to 15 (`XHPTDC8_TRIGGER_COUNT` - 1)
```YAML
manager_config: 
 device_configs: 
  0: 
   trigger : 
    0: 
     falling : false 
     rising : true 
```

When an element is repeated, then the _first_ occurance value will apply, and the rest will be ignored.</br>
_For example_: in the follwoing YAML, `rising` will be applied as _true_ 
```YAML
manager_config: 
 device_configs: 
  0: 
   trigger : 
    0: 
     rising : true 
     rising : false 
```

If the key (index) of YAML array element is `-1`, and no other value is presented, then the `-1` value is applied to all array elements.</br> 
_For example_: in the following YAML, `auto_trigger_period` will be set to 20 in _all the devices_.
```YAML
manager_config:
 device_configs:
  -1:
   auto_trigger_period : 20
```

If both `-1` and other values are specified, the `-1` shall be applied first, then the other values.</br>
_For example_: in the following YAML, all devices will have `auto_trigger_period` set to 20, except the device of index 5 which will have its `auto_trigger_period` set to 50.
```YAML
manager_config:
 device_configs:
  -1:
   auto_trigger_period : 20
  5:
   auto_trigger_period : 50
```

If both `-1` and other values are specified, the `-1` will not apply (neither partially nor fully) on the other values.</br>
_For example_: in the following YAML, trigger of index 0 will have `rising` as true, however, it's value `falling` will be left AS IS and not affected by `falling : false` of element -1. 
```YAML
manager_config: 
 device_configs: 
  0: 
   trigger : 
    -1: 
     rising : false 
     falling : false 
    0:
     rising : true 
```

When providing a key index of `-1`, it MUST be the first element in the array.</br>
_For example_: the following YAML generates error, as element -1 is mentioned but doesn't come first.
```YAML
manager_config:
 device_configs:
  0:
   auto_trigger_period : 50
  -1:
   auto_trigger_period : 20
```

Anchors and Aliases are supported.</br>
_For example_: in the following YAML, _all_ devices configurations will have the trigger of index 2 (the third) with values `rising:  true` and `falling: false`, while all other triggers will have `rising:  false` and `falling: true`.
```YAML
rising_trigger: &rising_trigger
 rising:  true
 falling: false

falling_trigger: &falling_trigger
 rising:  false
 falling: true

manager_config:
 device_configs:
  -1:
   trigger:
    -1: *falling_trigger
    2: *rising_trigger
```

Values that do not match both the element data type (defined in [xHPTDC8_interface.h](../lib/include/xHPTDC8_interface.h)) and the value reange (defined in the User Guide) will generate error and stop processing.</br>
_For example_: in the following YAML, an error will be generated because of the value `mode` of `tiger_block`, as it accepts only values [0, 1, 2, 3].
```YAML
manager_config: 
 device_configs: 
  0: 
   tiger_block : 
    1:
     mode : 4 
```

Values of parameters that are _not implemented_, will be ignored.</br>
_For example_: in the following YAML, `extend` value will be ignored.
```YAML
manager_config: 
 device_configs: 
  0: 
   tiger_block : 
    1:
     mode : 1 
     extend : true 
```

Boolean values are either `true` or `false` (in small letters), any other value will be considered an error (e.g. "0", "1", "True", "TRUE", "False", "FALSE"). 

It's allowed to have `grouping` _only_ without having `device_configs` in the YAML string.</br>
_For example_: the following YAML is valid.
```YAML
manager_config: 
 grouping: 
  enabled : true
```


#### Samples

##### All Elements YAML
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
### display_all_error_messages
The driver function `get_last_error_message()` needs to be provided with an index that selects the manager or one of the boards, that can be inconvenient. 
A new utilitt function is added to provide a method that returns the error messages from _all_ boards.

This API is of the following signature:
```C
int display_all_error_messages(crono_bool_t include_ok, crono_bool_t fixed_length)
```

#### Specifications
The function has two parameters:
1. `include_ok` outputs a line even if the board or the manager has no error.
2. `fixed_length` outputs a line for 8 boards, even if there are less boards in the system.

Returns a pointer to the error messages, the pointer should not be deallocated using `delete` or similar deallocation functions. 

#### Samples

##### With include_ok=true, fixed_length=true
Normal output is:
```CMD
0, "OK"
1, "Board does not exist"
2, "Board does not exist"
3, "Board does not exist"
4, "Board does not exist"
5, "Board does not exist"
6, "Board does not exist"
7, "Board does not exist"
```

#### Passing an invalid hMgr
Output is:
```CMD
-1, "Invalid arguments"
0, "Manager is invalid!"
1, "Board does not exist"
2, "Board does not exist"
3, "Board does not exist"
4, "Board does not exist"
5, "Board does not exist"
6, "Board does not exist"
7, "Board does not exist"
```

___________________________


# util_unit_test Project

## About
Microsoft Visual Studio C++ Test Project to test the util library functionalities.
Test Cases are created in the project, and are configured to test the Dummy Library, however, they can be reconfigured to run on the Driver.

## Microsoft Visual Studio Project 
The Solution and Project are created using Microsoft Visual Studio 2019. </br>
The project structure follows [our standard project folder structure](https://github.com/cronologic-de/xhptdc8_babel/wiki/project_folder_structure). Since it's a native VS Testing Project and has no source code, so it has no sub-folders "src" & "msvscpp".

### Project Environments and Configurations
- `util` DLL is added as `Reference`
- Project Settings -> Include Directories : `..\..\lib\include` is added.
- `Output Directory` is left as the Visual Studio _Default_ Project Settings.

| Config. | Env.  | Library Directory                       | Linker Input    |
| ------- |-----  |-----------------                        | --------------- |
| Debug   | x64   | ..\\..\\..\lib\x64dummy;..\\..\lib\x64; | xhptdc8_util_64.lib;xhptdc8_driver_64.lib |  
| Release | x64   | ..\\..\\..\lib\x64dummy;..\\..\lib\x64; | xhptdc8_util_64.lib;xhptdc8_driver_64.lib |  
| Debug   | Win32 | ..\\..\\..\lib\x86dummy;..\\..\lib\x86; | xhptdc8_util.lib;xhptdc8_driver.lib    |  
| Release | Win32 | ..\\..\\..\lib\x86dummy;..\\..\lib\x86; | xhptdc8_util.lib;xhptdc8_driver.lib    |  

### Building Using MS Visual Studio
Nothing special, just:
1. Using MS Visual Studio compatible version, open the solution file: `/util/util_msvscpp/util_msvscpp.sln`
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit _Build util_, and check the .lib files are found in the corresponsing directory as per the table above.

## Running the test
### Prereuiqistes
The following files are needed to be copied to the build _output directory_, carefully select the DLL related to the same platform you are building `util_test` for:
1. xhptdc8_util.dll/xhptdc8_util_64.dll
2. xhptdc8_driver.dll/xhptdc8_driver_64.dll

### Run
Nothing special, just select the underlying test, and hit run 

## Test Cases structure & design
Guidleines as per `namespace apply_yaml`:
- A file (or more) is created for every util API.
- Test Cases are divided into groups (Classes):
  - Happy Scenario. 
  - Special Scenario.
  - Functionality Scenario (e.g. tiger_block, channel, etc..).

![Test Cases Tree](https://github.com/cronologic-de/xhptdc8_babel/blob/main/util/docs/yaml_reader/TestCasesTree.JPG)

___________________________

# util_test Project

## About
Windows Console Application that is used to provide sample code and data for calling the Utility DLL Functions

```
-----------------------------------------------------------------------------
                 xHPTDC8 Utility Testing Application
-----------------------------------------------------------------------------
This program helps testing xHPTDC8 utility functions provided in "util"
library.

Command line flags:

-yamlentry : allows the user to enter YAML of device configuration, and calls
             the corresponding util API "xhptdc8_apply_yaml", then displays
             the results. User can then validate the entered YAML syntax and
             effect.

-help      : displays this help.


This is an open source application under Mozilla Public License 2.0
It can be downloaded from https://github.com/cronologic-de/xhptdc8_babel
```
## Microsoft Visual Studio Project 
The Solution and Project are created using Microsoft Visual Studio 2019. </br>
The project structure follows [our standard project folder structure](https://github.com/cronologic-de/xhptdc8_babel/wiki/project_folder_structure).

### Project Environments and Configurations
- Project Settings -> Include Directories : `..\..\..\lib\include;..\..\include;` is added.
- `Output Directory` is left as the Visual Studio _Default_ Project Settings.

| Config. | Env.   | Library Directory                       | Linker Input                           | Target Name              |
| ------- |------  | --------------------------------------- | -------------------------------------- | ------------------------ |
| Debug   | x64    | ..\\..\\..\lib\x64dummy;..\\..\lib\x64; | xhptdc8_util.lib;xhptdc8_driver_64.lib | xhptdc8_util_test_64.exe | 
| Release | x64    | ..\\..\\..\lib\x64dummy;..\\..\lib\x64; | xhptdc8_util.lib;xhptdc8_driver_64.lib | xhptdc8_util_test_64.exe | 
| Debug   | Win32  | ..\\..\\..\lib\x86dummy;..\\..\lib\x86; | xhptdc8_util.lib;xhptdc8_driver.lib    | xhptdc8_util_test.exe    | 
| Release | Win32  | ..\\..\\..\lib\x86dummy;..\\..\lib\x86; | xhptdc8_util.lib;xhptdc8_driver.lib    | xhptdc8_util_test.exe    | 

### Building Using MS Visual Studio
Project can be built using the following MSVS files:
1. [Project File: util_test.vcxproj](./util_test/msvscpp/util_test.vcxproj)
2. [Solution File: util_test.sln](./util_test/msvscpp/util_test.sln)
3. [xhptdc8_util_projects Solution File: xhptdc8_util_projects.sln](./msvscpp/xhptdc8_util_projects.sln)

Nothing special, just:
1. Using MS Visual Studio compatible version, open the solution file: `/util/util_msvscpp/util_msvscpp.sln`
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit _Build util_, and check the .lib & .dll files are found in the corresponsing directory as per the table above.

### github Building Action
github [Building Action: Util Test MSBuild](https://github.com/cronologic-de/xhptdc8_babel/blob/main/.github/workflows/util_test_msbuild.yml) is created to build `util_test` project as following:
1. Using MSBuild.
2. It builds the code automatically with relevant code update.
3. It builds the `Release` configuration of both `x86` and `x64` environments.
4. It copies and checkin the output EXE files to './util/bin/x86' or './util/bin/x64' corresponding directory.

### Running the Application
* Make sure you have both `xhptdc8_util.dll/xhptdc8_util_64.dll` and `xhptdc8_driver.dll/xhptdc8_driver_64.dll` _corresponding Platform DLL_ in the application output directory.

#### YAML Entry Testing
Selecting the flag `-yamlentry` when running the application, as following:
```
xhptdc8_util_test.exe -yamlentry
```
Will display the following message:

```
-----------------------------------------------------------------------------
                 xHPTDC8 Utility Testing Application
-----------------------------------------------------------------------------
This program helps testing xHPTDC8 utility functions provided in "util"
library.

YAML Entry.
Please enter yaml of device configuration (4096 character maximum)
To submit the string: press [Tab] then [Enter]:
```

Entring the following YAML example:
```YAML
manager_config:
 device_configs:
  0:
   trigger :
    0:
     rising : true
```

Then, pressing [Tab] then [Enter] using the keyboard, will display the results to be:
```
-----------------------------------------------------------------------------
                 xHPTDC8 Utility Testing Application
-----------------------------------------------------------------------------
This program helps testing xHPTDC8 utility functions provided in "util"
library.

YAML Entry.
Please enter yaml of device configuration (4096 character maximum)
To submit the string: press [Tab] then [Enter]:
manager_config:
 device_configs:
  0:
   trigger :
    0:
     rising : true


Calling xhptdc8_apply_yaml...

Applied yaml node ([0]) on conifguation (rising) boolean value (true)
```
