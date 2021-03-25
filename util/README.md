
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

Sample YAML:
```YAML
 manager_config: 
  device_configs: 
   - 
    trigger : 
     - 
      falling : false 
      rising : true 
    trigger_threshold : 
     - 0.3499 
     - 0.35 
     - 0.36666 
    gating_block : 
     - 
      mode : 1 
      negate : true 
    auto_trigger_period : 20 
   - 
    trigger : 
     - 
      falling : true 
      rising : false 
    channel : 
     - 
      enable : true
      rising : false 
  grouping : 
   enabled : true 
```

# test_msvscpp Project

## About
Windows Console Application that is used to provide sample code and data for calling the Utility DLL Functions

## Microsoft Visual Studio Project 
The Solution and Project are created using Microsoft Visual Studio 2019

### Project Environments and Configurations
### Building Using MS Visual Studio
### Running the Application
