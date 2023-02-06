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

[lib.rs](./src/lib.rs) has all the exported function.

### Building POCLib
#### x64
Using `cargo build` will build the dll and lib on the folder "/rust/poclib/target/debug".

### Test_POCLib Project Environments and Configurations
#### x64 
The Solution and Project are created using Microsoft Visual Studio 2019.
  * Project Settings -> General -> Output Directory : ..\\..\\target\\debug. The output of the DLL.
  * Project Settings -> Linker -> Input -> Additional Dependencies : poclib.dll.lib is added.
  * Project Settings -> VC++ Directories -> Library Directories: ..\\..\\target\\debug; is added
#### x86 
The Solution and Project are created using Microsoft Visual Studio 2019.
  * Project Settings -> General -> Output Directory : ..\\..\\x86\\debug. The output of the DLL.
  * Project Settings -> Linker -> Input -> Additional Dependencies : poclib.dll.lib is added.
  * Project Settings -> VC++ Directories -> Library Directories: ..\\..\\x86\\debug; is added

### Building Test_POCLib Using MS Visual Studio
Project can be built using the following MSVS files:
1. [Solution File: test_poclib.sln](./test_poclib/test_poclib.sln)
2. [Project File: test_poclib.vcxproj](./test_poclib/test_poclib/test_poclib.vcxproj)

Nothing special, just:
1. Using MS Visual Studio compatible version, open one of the project or solution files mentioned above.
2. Select the needed _Configuration_ and _Environment_ to build.
3. Hit _Build util_, and check the .lib & .dll files in the corresponsing directory as per the table above.

## APIS
Imported in C files:
```C
#define XHPTDC8_API_IMP __declspec(dllimport)
extern "C" {
	XHPTDC8_API_IMP void set_TDCHit(TDCHit* hit);
	XHPTDC8_API_IMP void get_TDCHit(TDCHit* hit);
	XHPTDC8_API_IMP void set_Str(char* str);
	XHPTDC8_API_IMP void get_Str(char* str, unsigned char size);
}
```

In Rust, APIs hould be defined as `pub extern "C"` with `no_mangle`, e.g.
```RUST
#[no_mangle]
pub extern "C" fn get_Str(str: *mut c_char, size : u8) {
.
}
```
