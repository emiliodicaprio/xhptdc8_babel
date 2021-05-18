# RUST POC DLL

## About
Proof of Concept of creating a DLL with Rust and calling it from C or C++.

## Source Code Project 
The DLL is created using Rust.
The POC Test Application is created using C++.

### POCLib Project Environments and Configurations
Adding the following section to `Cargo.toml` to build dynamically linked library:
```TOML
[lib]
crate-type = ["cdylib"]
```

### Test_POCLib Project Environments and Configurations
The Solution and Project are created using Microsoft Visual Studio 2019.
  * Project Settings -> General -> Output Directory : ..\..\target\debug. The output of the DLL.
  * Project Settings -> Linker -> Input => Additional Dependencies : poclib.dll.lib is added.

### Building Test_POCLib Using MS Visual Studio
Project can be built using the following MSVS files:
2. [Solution File: test_poclib.sln](./rust/poclib/test_poclib.sln)
1. [Project File: test_poclib.vcxproj](./rust/poclib/test_poclib/test_poclib/test_poclib.vcxproj)

Nothing special, just:
1. Using MS Visual Studio compatible version, open one of the project or solution files mentioned above.
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit _Build util_, and check the .lib & .dll files in the corresponsing directory as per the table above.

## APIS
Imported in C files:
```C
extern "C" {
	XHPTDC8_API_IMP void set_TDCHit(TDCHit* hit);
	XHPTDC8_API_IMP void get_TDCHit(TDCHit* hit);
	XHPTDC8_API_IMP void set_Str(char* str);
	XHPTDC8_API_IMP void get_Str(char* str, unsigned char size);
}
```
