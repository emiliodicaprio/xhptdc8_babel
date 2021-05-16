
# Readout Tool

## About
New Users shall have a command line tool where they can gather data directly from the device to test it without having to write specific code.
This shall reside in a new sub directory and be both a tool for end users and a code example for users.

## Source Code Project 
The project is created u=using Rust.

### Project Environments and Configurations

### Packages
#### main

#### C FFI Wrapping
Used `bindgen` to build the `bindings.rs` wrapper file.
1. Added the following to `Cargo.toml`
```TOML
[package]
build = "build.rs"
authors = ["Bassem-Ramzy <75851720+Bassem-Ramzy@users.noreply.github.com>"]

[build-dependencies]
bindgen = "0.58.1"
```
2. Created [build.rs](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/build.rs) on the project folder.
   - Used `#cfg` to define parameters of every platform
   ```RUST
   #[cfg(target_arch="x86")]
   static RUSTC_LINK_SEARCH : &str = "cargo:rustc-link-search=../../lib/x86dummy/" ;
   
   #[cfg(target_arch="x86_64")]
   static RUSTC_LINK_SEARCH : &str = "cargo:rustc-link-search=../../lib/x64dummy/" ;
   ```
   - Used [wrapper.h](https://github.com/cronologic-de/xhptdc8_babel/blob/main/rust/readout/wrapper.h) to include the needed headers.
   - Saves `bindings.rs` (x86) and `bindings_64.rs`(x64) on [.\rust\readout\src\bindings](https://github.com/cronologic-de/xhptdc8_babel/tree/main/rust/readout/src/bindings). 

### Building the Code (64-bit)
#### Prerequisites
1. 

#### Steps
1. 
