
# `util` Project

## About
- A library that provides utility functionalities for xHPTDC8 Driver. It supports both Windows and Linux.
- Outputs are `xhptdc8_util.dll` and `xhptdc8_util.lib` for Windows, and `libxhptdc8_util.so` for Ubuntu/Debian.
- Output folders are the root shared folders [`/lib`](./lib) (for `.lib`) and [`/bin`](./bin) (for `.dll` and `.so`).

### Project Environments and Configurations
- Project Settings -> Include Directories : `..\..\include;..\..\..\include;.\ryml_src;` is added.
- Project Settings -> Preprocessor Definitions: `XHPTDC8_UTIL_EXPORTS` is defined.
- Project Settings -> Preprocessor Definitions: `XHPTDC8_VERBOSE_DEBUG` is defined for _Debug Configurations_ only.

### External Libraries
The project uses the source code of the following libraries for YAML parser:
- https://github.com/biojppm/rapidyaml (main parser project)
- https://github.com/biojppm/c4core (needed by rapidyaml)
- https://github.com/biojppm/debugbreak/ (needed by rapidyaml)
- https://github.com/fastfloat/fast_float (needed by rapidyaml)

With the following actions:
- The source code of those libraries is downloaded and is added to the project.
- External project files are set to **Precompiled Header**: _Not Using Precompiled Headers_

## Build the project 
- Follow the steps in [Build CMake-based project](#build-cmake-based-project).
- Note that the output folder is the same for both release and debug builds.

### `github` Building Action
`github` [Building Actions: `Check-Util-Library`, `Util-Library-Win` and `Util-Library-Linux`](https://github.com/cronologic-de/xhptdc8_babel/blob/main/.github/workflows/build_all.yml) is created to build `util` project as following:
1. Using `CMake`.
2. It builds the code automatically with relevant code update.
3. It builds the `Release` configuration.
4. It checks in the output (`.dll` and `.lib` for Windows, `.so` for Linux) file(s) to the repository.

## Using the Utility Library

### Compile & Link Settings
In order to call functions from the utility library, you need to do the following:
1. Include [`/include/xhptdc8_util.h`](./include/xhptdc8_util.h).
2. Link to [`/lib/xhptdc8_util.lib`](./lib/xhptdc8_util.lib) for Windows, or [`/bin/libxhptdc8_util.so`](.//bin/libxhptdc8_util.so) for Linux.

### `xhptdc8_apply_yaml`
The purpose of this repository is to make using the [xHPTDC8 time-to-digital converter](https://www.cronologic.de/products/tdcs/xhptdc8-pcie) simpler to use for end users.

Setting up the `xhptdc8_manager_configuration` structure is rather complicated. This shall be simplified by allowing to apply YAML files to the structure.
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

Array index starts with 0 (or -1), and should be less than the maximum array size defined in [xHPTDC8_interface.h](../include/xHPTDC8_interface.h).</br>
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

Values that do not match both the element data type (defined in [xHPTDC8_interface.h](../include/xHPTDC8_interface.h)) and the value reange (defined in the User Guide) will generate error and stop processing.</br>
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
Here is the complete elements of the manager configuration sturcture, including sample values; you can copy your YAML elements from the YAML below, just keep the spaces before the elements, and refer to both the user guide and the [xHPTDC8_interface.h](/include/xHPTDC8_interface.h "xHPTDC8_interface.h") xhptdc8_interface.h for the members specifications:

```YAML
manager_config:
 device_configs:
  0:                                  # configuration for the first device
   auto_trigger_period : 200
   auto_trigger_random_exponent : 20
   trigger_threshold :
    0: -0.3499
    1: -0.35
   trigger :
    0:
     falling : true
     rising : false
    1:
     falling : true
     rising : false
   gating_block :
    0:
     mode : 0
     negate : true
     retrigger : true
     extend : true
     start : 10
     stop : 190
     sources : 1
   tiger_block :
    0:
     mode : 0
     negate : true
     retrigger : true
     extend : true
     start : 20
     stop : 200
     sources : 2
   channel :
    0:
     enable : true
     rising : false
    1:
     enable : true
     rising : false
   adc_channel :
    enable : true
    watchdog_readout : false
    watchdog_interval : 500
    trigger_threshold : -0.35
   skip_alignment : false
   alignment_source : 1
   alignment_off_state : 0

 grouping :                           # grouping configuration
  enabled : true
  trigger_channel : 0
  trigger_channel_bitmask : 0
  range_start : 0
  range_stop : 123456
  trigger_deadtime : 1000
  zero_channel : -1
  zero_channel_offset : 0
  window_hit_channels : -1
  window_start : 10
  window_stop : 20000
  veto_mode : 0
  veto_start : 30
  veto_stop : 40
  veto_active_channels : -1
  veto_relative_to_zero : true
  ignore_empty_events : false
  overlap : false
...                                   # end of configuration data
```
### `display_all_error_messages`
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
```
* Assuming that boards number is 6, as per `XHPTDC8_MANAGER_DEVICES_MAX`

##### With include_ok=true, fixed_length=false
Normal output is:
```CMD
-----------------------------------------------------------------------------
                 xHPTDC8 Utility Testing Application
-----------------------------------------------------------------------------
This program helps testing xHPTDC8 utility functions provided in "util"
library.

0, "OK"
```

##### With include_ok=false, fixed_length=true
Normal output is:
```CMD
-----------------------------------------------------------------------------
                 xHPTDC8 Utility Testing Application
-----------------------------------------------------------------------------
This program helps testing xHPTDC8 utility functions provided in "util"
library.

1, "Board does not exist."
2, "Board does not exist."
3, "Board does not exist."
4, "Board does not exist."
5, "Board does not exist."
```

### `xhptdc8_update_config_for_grouping_mode`
Setting up the `xhptdc8_manager_configuration` structure is rather complicated. This API simplifies updating it to use the "Grouping mode".

**Structure updates**

It updates the structure as following:
- All 8 TDC channels are enabled.
- Grouping is enabled 
- `trigger_channel` = 0
- `zero_channel` = -1 
- `zero_channel_offset` = 0
- `trigger_deadtime` = 0
- `window_hit_channels` =0
- `trigger_channel_bitmask` = 0
- `veto_mode` = 0
- `overlap` = false

Structure updates as per the arguments values:
- `threshold`: is copied to `trigger_threshold` for all channels.
- `range_start` and `range_stop`: are copied to `range_start` and `range_stop`.
- `rising` (default is `false`): this value is copied to `channel[i].rising` of each channel.
   - If `true`, it sets the trigger structure of each channel to `rising`=true, `falling`=false.
   - If `false`, it sets the trigger structure of each channel to `rising`=false, `falling`=true.
- `ingore_empty_events` (default is `false`): is copied to `ignore_empty_events`.

**Signature**

This API is of the following signature:
```C
XHPTDC8_UTIL_API int xhptdc8_update_config_for_grouping_mode(int index, xhptdc8_manager_configuration *mgr_cfg,
                                                             float threshold, int64_t range_start, int64_t range_stop,
                                                             crono_bool_t rising = false,
                                                             crono_bool_t ingore_empty_events = false);
```

**Prerequisites**

- `mgr_cfg` memory is allocated and initialized. Initialization to default values is an option.

**Return**

- `CRONO_OK`: Successfully updated values in `mgr_cfg`.
- `CRONO_INVALID_ARGUMENTS`: if any argument is invalid.

___________________________

# `util_unit_test` Project

## About
Microsoft Visual Studio C++ Test Project to test `util` library functionalities.
Test Cases are created in the project, and are configured to test the driver library, however, they can be reconfigured to run on the Dummy Library.

## Microsoft Visual Studio Project
The Solution and Project are created using Microsoft Visual Studio 2019. </br>
The project structure follows [our standard project folder structure](https://github.com/cronologic-de/xhptdc8_babel/wiki/project_folder_structure). Since it's a native VS Testing Project and has no source code, so it has no sub-folders "src" & "msvscpp".

### Project Environments and Configurations
- Project solution is `util_unit_test.sln`.
- Project Settings -> Include Directories : `..\..\include` is added.
- `Output Directory` is left as the Visual Studio _Default_ Project Settings.

| Config. | Env.  | Library Directory                       | Linker Input    |
| ------- |-----  |-----------------                        | --------------- |
| Debug   | x64   | ..\\..\\..\lib\dummy;..\\..\bin; | xhptdc8_util.lib;xhptdc8_driver_64.lib |
| Release | x64   | ..\\..\\..\lib\dummy;..\\..\bin; | xhptdc8_util.lib;xhptdc8_driver_64.lib |

### Building Using MS Visual Studio
Nothing special, just:
1. Using MS Visual Studio compatible version, open the solution file: `/util/util_unit_test/util_unit_test.sln`
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit *Build util_unit_test*, and check the .lib files are found in the corresponsing directory as per the table above.

## Running the test
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

### Log Message
In case you needed to log message, you can use the following:
```C
Logger::WriteMessage(err_messages_str.c_str());
```

___________________________

# `util_test` Project

## About
- A console application that is used to provide sample code and data for calling the Utility Library Functions, for both Windows and Linux.
- Output is `xhptdc8_util_test.exe` for Windows, and `xhptdc8_util_test` for Ubuntu/Debian.
- Output folder is the root shared folder [`/bin`](./bin).

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

-errmsg    : displays error messages.

-help      : displays this help.


This is an open source application under Mozilla Public License 2.0
It can be downloaded from https://github.com/cronologic-de/xhptdc8_babel
```

### Project Environments and Configurations
- Project Settings -> Include Directories : `..\..\..\include;..\..\include;` is added.

### Building Using MS Visual Studio
- Follow the steps in [Build CMake-based project](#build-cmake-based-project).
- Note that the output folder is the same for both release and debug builds.

### github Building Action
github [Building Actions: `Check-Util-Test`, `Util-Test-Win`, and  `Util-Test-Linux`](https://github.com/cronologic-de/xhptdc8_babel/blob/main/.github/workflows/build_all.yml) are created to build `util_test` project as following:
1. Using `CMake`.
2. It builds the code automatically with relevant code update.
3. It builds the `Release` configuration.
4. It checks in the output executable files to the repository.

### Usage

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

Applied yaml node ([0]) on configuration (rising) boolean value (true)
```

* Notes: 
  - If there is any error from the API, it will then be displayed in the last line. 
  - The detailed action in the last line is displayed only when `xhptdc8_util.dll` is built in Debug mode.

#### Error Message Testing
Selecting the flag `-errmsg` when running the application, calls the API with options: `include_ok=false`, `fixed_length=true`, as following:
```
xhptdc8_util_test.exe -errmsg
```
Will display the following message:

```
-----------------------------------------------------------------------------
                 xHPTDC8 Utility Testing Application
-----------------------------------------------------------------------------
This program helps testing xHPTDC8 utility functions provided in "util"
library.

0, "OK"
1, "Board does not exist."
2, "Board does not exist."
3, "Board does not exist."
4, "Board does not exist."
5, "Board does not exist."
```

* Assuming that Number of Boards are 6 (= `XHPTDC8_MANAGER_DEVICES_MAX`)


---

# Build `CMake`-based project

## Build using `CMake`
In a terminal, navigate to `<path\to\project\folder>\tools` and run the following command:
| Platform          | Configuration | Configure CMake command                           | Compile & Link Command                            | 
| ----------------- | ------------- | ----------------------------------------------    | ------------------------------------------------- | 
| **Windows x86_64**| Release       | `cmake -B ..\build\bfR -A x64`                    | `cmake --build ..\build\bfR --config Release`     | 
| **Windows x86_64**| Debug         | `cmake -B ..\build\bfD -A x64`                    | `cmake --build ..\build\bfD --config Debug`       | 
| **Linux x86_64**  | Release       | `cmake -B ../build/bfR -DCMAKE_BUILD_TYPE=Release`| `cmake --build ../build/bfR`                      | 
| **Linux x86_64**  | Debug         | `cmake -B ../build/bfD -DCMAKE_BUILD_TYPE=Debug`  | `cmake --build ../build/bfD`                      | 

* Output folder is determined by every project documentation.
* Build folder path (e.g. `../build/bfR`) is relative to project `tools` folder.
* You can change the build/output directory from `CMakeLists.txt` file.

> **Note**
> - The default configuration is `Debug` on Windows, and `Release` on Linux.

## Build Using Visual Studio
It is mainly done using `CMakeSettings.json` file provided in project `tools` folder, that uses the projects `CMakeLists.txt`.

**Prerequisites**
- Visual Studio 2019 or later
- [C++ CMake tools for Windows](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio#installation)

  You can install these from the _Visual Studio Installer_ under 
  _Desktop development with C++_.

**Open and configure the project**
1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the project folder, e.g., `xhptdc8_driver\util\util`.
4. If a "CMake Integration" message _to enable Visual Studio's CMake support with this workspace_ is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to `<path\to\project\folder>\tools`, and open `CMakeLists.txt` file.

**Compile and Link**

Select `Build -> Build All` from the menu bar (or any standard Visual Studio way to build the project).

**Project Environments and Configurations**

The target executable name is `xhptdc8_ugex.exe`.

| Configuration     | `CMakeSettings` | `Build root`                     | `CMake generator`     | 
| ----------------- | --------------- | -------------------------------- | --------------------- | 
| **x86_64 Debug**  | x64-Debug       | `${projectDir}\..\build\bfvsD`   | Visual Studio 17 2022 Win64 | 
| **x86_64 Release**| x64-Release     | `${projectDir}\..\build\bfvsR`   | Visual Studio 17 2022 Win64 | 

> **Note**<br>
> - The provided file builds the project using Visual Studio 2022, however, you can change `generator` in [`CMakeSettings.json`](./tools/CMakeSettings.json) to any other Visual Studio generator you have on your machine.