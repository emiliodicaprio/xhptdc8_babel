
# util_msvscpp Project

## About
Windows DLL that provides utility functionalities for xHPTDC8 Driver

## Microsoft Visual Studio Project 

### Project Environments and Configurations
- Project Settings -> Include Directories : `..\..\include;..\..\..\lib\include;.\ryml_src;` is added.
| Configuration | Environment   | Output Directory | Library Name    |
| ------------- |-------------  |----------------- | --------------- |
| Debug         | x64           | ..\..\lib\x64    | xhptdc8_util_64 |  
| Release       | x64           | ..\..\lib\x64    | xhptdc8_util_64 |  
| Debug         | Win32         | ..\..\lib\x86    | xhptdc8_util    |  
| Release       | Win32         | ..\..\lib\x86    | xhptdc8_util    |  
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
3. Hit _Build ug_example_msvscpp_, and check the .lib & .dll files in the corresponsing directory as per the table above.

## YAML Functions Usage

# test_msvscpp Project
## About
Windows Console Application that is used to provide sample code and data for calling the Utility DLL Functions
## Microsoft Visual Studio Project 
### Project Environments and Configurations
### Building Using MS Visual Studio
### Running the Application
