
# Readout Tool

## About
New Users shall have a command line tool where they can gather data directly from the device to test it without having to write specific code.
This shall reside in a new sub directory and be both a tool for end users and a code example for users.

The readout tool enables the user to provide YAML configuration file(s) to configure the device(s) before reading hits from.

Output format could be either cvs or binary.


## Source Code Project 
The project is created using Rust.

### An Overview
The project files include `binding.rs` file that is generated using `bindgen`. `bindgen` uses [build.rs](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/build.rs) to generate the `binding.rs` file while linked to both `xhptdc8_driver` and `xhptdc8_util` libraries, and included [wrapper.h](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/wrapper.h) that includes `xhptdc8_util.h` which includes `xhptdc8_interface.h` in its turn.

`binding.rs` has all xhptdc8 APIs and structures definitions needed by the readout tool.

The project is developed on Windows 10, and is built for both `x86` and `x64` platforms:
```CMD
cargo 1.52.0 (69767412a 2021-04-21)

clang version 12.0.0
Target: x86_64-pc-windows-msvc
&
Target: i686-pc-windows-msvc
```

### Project Environments and Configurations
#### bindgen
For `bindgen` to work properly:
1. Make sure you installed `LLVM` for `clang.dll` and `libclang.dll`.
2. Set `bin` directory on the path.
3. Set `LIBCLANG_PATH` to `bin`, or you get error when using `cargo check` similar to:
```CMD
--- stderr
  thread 'main' panicked at 'Unable to find libclang: "couldn\'t find any valid shared libraries matching: [\'clang.dll\', \'libclang.dll\'], set the `LIBCLANG_PATH` 
environment variable to a path where one of these files can be found (invalid: [(C:\\Program Files\\LLVM\\bin\\libclang.dll: invalid DLL (64-bit))])"', C:\Users\basse\.cargo\registry\src\github.com-1285ae84e5963aae\bindgen-0.58.1\src/lib.rs:2057:31
```
Download from [LLVM Releases from github](https://github.com/llvm/llvm-project/releases), or [LLVM Download](https://releases.llvm.org/download.html)

_Note_: using `mingw64` or `mingw32` to build `bindgen` generates the following error:
```CMD
--- stderr
  thread 'main' panicked at 'Unable to find libclang: "the `libclang` shared library at F:/Work/mingw32\\bin\\clang.dll could not be opened: LoadLibraryExW failed"', C:\Users\basse\.cargo\registry\src\github.com-1285ae84e5963aae\bindgen-0.58.1\src/lib.rs:2057:31
  note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
```

#### Cross-platform Compilation
Make sure a proper `rustup target`, corresponding to the platform you want to buil the readout tool for, is installed and set to default. e.g.
```CMD
rustup install stable-i686-pc-windows-gnu
rustup default stable-i686-pc-windows-gnu
cargo build
```

### Packages
#### main
* The main file `main.rs` is responsible for the main flow of the application.
* [readout_aux](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/src/readout_aux.rs) has all the calls to the driver and util APIs.

#### C FFI Wrapping
Used `bindgen` to build the `bindings.rs` wrapper file.
* Added the following to `Cargo.toml`
```TOML
[package]
build = "build.rs"

[build-dependencies]
bindgen = "0.58.1"
```
* Created [build.rs](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/build.rs) on the project folder.
   - Used `#cfg` to define parameters of every platform
   ```RUST
   #[cfg(target_arch="x86")]
   static RUSTC_LINK_SEARCH : &str = "cargo:rustc-link-search=../../lib/x86dummy/" ;
   
   #[cfg(target_arch="x86_64")]
   static RUSTC_LINK_SEARCH : &str = "cargo:rustc-link-search=../../lib/x64dummy/" ;
   ```
   - Used [wrapper.h](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/wrapper.h) to include the needed headers.
   - Saves `bindings.rs` (x86) and `bindings_64.rs`(x64) on [.\rust\readout\src\bindings](https://github.com/cronologic-de/xhptdc8_babel/tree/main/rust/readout/src/bindings). 
 
* Included the generated `bingings.rs` file in the code, in [readout_aux](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/src/readout_aux.rs).
```RUST
#[cfg(target_arch="x86")]
include!("./bindings/bindings.rs"); // Must = corresponding BINDINGS_FILE_NAME 

#[cfg(target_arch="x86_64")]
include!("./bindings/bindings_64.rs");  // Must = corresponding BINDINGS_FILE_NAME 
```
* C Library functions are called directly in `unsafe` block, e.g.
```RUST
let mut static_info = xhptdc8_static_info::default() ;
let error_code: i32 ;
unsafe {
    error_code = xhptdc8_get_static_info(g_mgr, device_index, &mut static_info) ;
}
```
* Implemented `Default` trait for the used structures for easy initialization. e.g.
```RUST
impl Default for xhptdc8_adc_channel {
    fn default () -> xhptdc8_adc_channel {
        xhptdc8_adc_channel{enable:0, watchdog_readout:0, watchdog_interval:0, trigger_threshold:0.0}
    }
}
```

#### clap
`clap` crate is used for command line processing. 

`cargo.toml` has the following dependency for it:
```YAML
[dependencies]
clap = "2"
```

##### Useful Links
* https://github.com/clap-rs/clap/tree/v2.33.0
* https://docs.rs/clap/2.33.3/clap/ 
* https://docs.rs/clap/2.31.0/clap/struct.Arg.html

#### indicatif
`indicatif` crate is used to display a progress bar that displays the progress while reading hits.

`cargo.toml` has the following dependency for it:
```YAML
[dependencies]
indicatif = {version = "*", features = ["rayon"]}
```

#### Useful Links
* https://docs.rs/indicatif/0.15.0/indicatif/


### Building the Code (64-bit)
#### Prerequisites
1. 64-bit compiler with both `clang.dll` and `libclang.dll` are found. 
2. `LLVM` for 64 bit is installed.
3. LLVM `bin` directory on the PATH.
4. `LIBCLANG_PATH` is set to LLVM `bin`.
5. `rustup target`, e.g. `stable-x86_64-pc-windows-msvc`, is installed and set as default.

#### Steps
just use the usual
```CMD
cargo build
```

### Building the Code (32-bit)
#### Prerequisites
1. 32-bit compiler with both `clang.dll` and `libclang.dll` are found. 
2. `LLVM` for 32 bit is installed.
3. LLVM `bin` directory on the PATH.
4. `LIBCLANG_PATH` is set to LLVM `bin`.
5. `rustup target`, e.g. `stable-i686-pc-windows-msvc`, is installed and set as default.

#### Steps
just use the usual
```CMD
cargo build
```

### github Building Action
github [Building Action: Readout Tool Build](https://github.com/cronologic-de/xhptdc8_babel/edit/main/.github/workflows/readout_build.yml) is created to build `readout` project as following:
1. It builds the code automatically with relevant code update.
2. It creates the following files:

#### Notes
##### Building Using Pre-installed mingw
Using `mingw64` installed on C:\msys64\mingw64\bin and `mingw32` installed on C:\msys64\mingw32\bin, although have both clang.dll and libclang.dll, fail. 
We get the following errors:
```CMD
 --- stderr
  thread 'main' panicked at 'Unable to find libclang: "the `libclang` shared library at C:\\msys64\\mingw64\\bin\\libclang.dll could not be opened: LoadLibraryExW failed"', C:\Users\runneradmin\.cargo\registry\src\github.com-1ecc6299db9ec823\bindgen-0.58.1\src/lib.rs:2057:31
Should use LLVM

Same for 32
--- stderr
  thread 'main' panicked at 'Unable to find libclang: "the `libclang` shared library at C:\\msys64\\mingw32\\bin\\libclang.dll could not be opened: LoadLibraryExW failed"', C:\Users\runneradmin\.cargo\registry\src\github.com-1285ae84e5963aae\bindgen-0.58.1\src/lib.rs:2057:31
```
So, the solution is to use LLVM instead.

##### Building Win32
I didn't find github action to donwnload and install `LLVM Win32`, so I had to do that manually.
* `powershell` caused the issues mentioned below, so I had to use `cmd` instead.
* Running the following using `cmd`:
  ```YAML
    - name: Install LLVM Win32
      run: |
        curl https://github.com/llvm/llvm-project/releases/download/llvmorg-12.0.0/LLVM-12.0.0-win32.exe -o "C:\Temp\LLVM_Win32.exe
        C:\Temp\LLVM_Win32.exe /S
  ```
  Generates the following error:
  ```CMD
  The system cannot execute the specified program.
  ```
  Although it runs successfully on my local machine.
* Only the scrept found in the action works successfully.

##### Using powershell
Using `powershell`, for a reason or another, doesn't install the LLVM Win32 exe when run on github action environment, while it is installed successfully locally on my machine; on the contrary, `cmd` does. Both the following scripts don't install it:
```YAML
- name: Download and Install LLVM Win32
  run: | 
    wget https://prereleases.llvm.org/win-snapshots/LLVM-12.0.0-6923b0a7-win32.exe -OutFile "C:\Temp\LLVM_Win32.exe"
    C:\Temp\LLVM_Win32.exe /S
```
and
```YAML
- name: Download and Install LLVM Win32
  run: | 
    wget https://github.com/llvm/llvm-project/releases/download/llvmorg-12.0.0/LLVM-12.0.0-win32.exe -OutFile "C:\Temp\LLVM_Win32.exe"
    C:\Temp\LLVM_Win32.exe /S
```

## Using the Readout Tool
All details are found [on wiki](https://github.com/cronologic-de/xhptdc8_babel/wiki/using_readout_tool)

### Usage

```CMD
USAGE:
    xhptdc8_readout.exe [FLAGS] [OPTIONS]

FLAGS:
    -b, --binary     The content of the TDCHit structure bit by bit, so 96 bits per hit. Default is csv.
        --csv        (Default) One line of text per hit, seperated by commas, "time, channel, type, bin"
    -l, --log        Enable to display log message.
    -h, --help       Prints help information
    -V, --version    Prints version information

OPTIONS:
    -c, --config <YAML_FILE>...    A list of YAML files for the configuration.
    -f, --filesno <NUMBER>         The number of files to be written. Default is 0.
    -n, --hitsno <HITS_NUMBER>     The number of hits per file. Default is 10,000.
    -o, --output <FILE>            The file to which the output will be written. Default is "output.csv"
```

### Output Format
The readout output files are generated in one of two formats: `csv` or `binary`.
#### csv 
The output files will be in csv format when either _no format is specified in command line_ or _--csv_ is specified.
Format is: One line of text per hit, seperated by commas: `time, channel, type, bin`

#### binary
The output files will be in binary format when either _-b_ or _--binary_ is specified in the command line parameters.
Format is: Just the content of the `TDCHit` structure bit by bit. So `96 bits per hit`, in the following order: _time, channel, type, bin_.

Note that _the representation of every value is set as a byte array in big-endian (network) byte order_.


