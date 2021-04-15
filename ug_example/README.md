
# xHPTDC8 User Guide Example

This directory contains a project to compile the C++ example show in the user guide of the cronologic xHPTDC8 time-to-digital converter.

You can download the user guide from the [product web page](https://www.cronologic.de/products/tdcs/xhptdc8-pcie).

# The Project 

## About
The Solution and Project are created using Microsoft Visual Studio 2019, as a Console App

## Project Environments and Configurations
- The Target Exectuable name is `xhptdc8_ugex.exe`
- Project Settings -> Include Directories : `..\..\..\lib\include` is added.
- Configuration that is related to `Dummy Library` links to the .lib file in its corresponsing `x_NN_dummy` directory.

| Configuration | Environment   | Output Directory | Linked Library | Library Directory |
| ------------- |-------------  |----------------- | -------------  | -------------------- |
| Debug         | x64           | ug_example_msvscpp\x64\Debug | xhptdc8_driver_64.lib | ..\\..\\..\\lib\\x64 | 
| DebugDummy    | x64           | ug_example_msvscpp\x64\DebugDummy | xhptdc8_driver_64.lib | ..\\..\\..\\lib\\x64dummy | 
| Release       | x64           | ug_example_msvscpp\x64\Release | xhptdc8_driver_64.lib | ..\\..\\..\\lib\\x64 | 
| ReleaseDummy  | x64           | ug_example_msvscpp\x64\ReleaseDummy | xhptdc8_driver_64.lib | ..\\..\\..\\lib\\x64dummy | 
| Debug         | Win32         | ug_example_msvscpp\Debug | xhptdc8_driver.lib | ..\\..\\..\\lib\\x86 | 
| DebugDummy    | Win32         | ug_example_msvscpp\DebugDummy | xhptdc8_driver.lib | ..\\..\\..\\lib\\x86dummy | 
| Release       | Win32         | ug_example_msvscpp\Release | xhptdc8_driver.lib | ..\\..\\..\\lib\\x86 | 
| ReleaseDummy  | Win32         | ug_example_msvscpp\ReleaseDummy | xhptdc8_driver.lib | ..\\..\\..\\lib\\x86dummy | 

### Debug|x64
For this build sepcifically, a post-build action is added to faciliated the debugging:
```CMD
copy "..\..\..\lib\x64\xhptdc8_driver_64.dll" "$(TargetDir)"
```
## Building Using MS Visual Studio
Nothing special, just:
1. Using MS Visual Studio compatible version, open the solution file: `\ug_example_msvscpp\ug_example_msvscpp.sln`
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit _Build ug_example_msvscpp_, and check the built executable file in the corresponsing directory as per the [table above](https://github.com/cronologic-de/xhptdc8_babel/edit/main/ug_example/README.md#Project_Environments_and_Configurations).

## Running the sample
### Using Dummy Library
To run the executable file using _Dummy Library_: 
- Copy the corresponding _platform_ DLL from the _Library Directory_ as per the [table above](https://github.com/cronologic-de/xhptdc8_babel/edit/main/ug_example/README.md#Project_Environments_and_Configurations) to the executable directory. For instance, for _x64 Release_ exe, just copy the DLL _xhptdc8_driver_64.dll_ from _..\\..\\..\\lib\\x64dummy_.
- Run the exe from Windows command

## Debugging the sample
Nothing special about using MS Visual Studio in debugging the project, just go ahead using MS Visual Studio debugger.

### Debug Dummy Library
When using _Dummy Library_, you can build the _Debug Configuration_ of _xhptdc8_driver_64.dll_, and copy it in the executable file directory, you can then go into the _Dummy Library_ code as well while debugging the sample.


