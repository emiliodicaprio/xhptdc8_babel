use std::ffi::CStr;
use std::os::raw::c_char;
use std::ffi::CString ;

#[derive(Debug)]
struct HoldsANumber(u8);

pub struct TDCHit {
    pub time: i64,
    pub bin: u16,
    pub channel: u8,
    pub type_: u8,
} 

#[no_mangle]
pub extern "C" fn set_TDCHit(hit: *mut TDCHit) {
    unsafe {
        println!("RUST DLL: API set_TDCHit is called with struct info: \n- time: {}\n- bin: {}\n- channel: {}\n- type: {}", 
            (*hit).time, (*hit).bin, (*hit).channel, (*hit).type_) ;
        }
}

#[no_mangle]
pub extern "C" fn get_TDCHit(hit: &mut TDCHit) {
    hit.time = 987654321;
    hit.bin = 65000 ;
    hit.channel = 1;
    hit.type_ = 255 ;
    println!("RUST DLL: API get_TDCHit is called to fill struct with info: \n- time: {}\n- bin: {}\n- channel: {}\n- type: {}", 
        hit.time, hit.bin, hit.channel, hit.type_) ;
}

#[no_mangle]
pub extern "C" fn set_Str(str: *mut c_char) {
    unsafe {
        let str_rust = CStr::from_ptr(str);
        println!("RUST DLL: API set_Str is called with string info: \n- String: {:?}", str_rust) ;
    }
}

#[no_mangle]
pub extern "C" fn get_Str(str: *mut c_char, size : u8) {
    unsafe {
        let cs = CString::new("This is a test string from Rust!").unwrap();
        println!("RUST DLL: API get_Str is called to fill string with info: \n- String: {:?}", cs) ;
        let len = std::cmp::min(cs.as_bytes_with_nul().len(), size as usize);
        std::ptr::copy_nonoverlapping(cs.as_ptr(), str, len);
    }
}
