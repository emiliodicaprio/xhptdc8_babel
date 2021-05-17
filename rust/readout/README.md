
# Readout Tool

## About
New Users shall have a command line tool where they can gather data directly from the device to test it without having to write specific code.
This shall reside in a new sub directory and be both a tool for end users and a code example for users.

## Source Code Project 
The project is created u=using Rust.

### Project Environments and Configurations
* For `bindgen` to work properly:
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

### Packages
#### main

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
### Building the Code (64-bit)
#### Prerequisites
1. 

#### Steps
1. 
