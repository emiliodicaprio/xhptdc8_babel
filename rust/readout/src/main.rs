#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!("../target/debug/build/Debug-4799d6a7a6519e9c/out/bindings.rs");

fn main() {
    println!("Hello, world!");
    test_lib() ;
}

fn test_lib() {
    unsafe {
        let mut params = xhptdc8_manager_init_parameters { version : 0 , buffer_size : 0 , variant : 0 ,
            device_type : 0 , dma_read_delay : 0 , multiboard: 0, use_ext_clock: 0, ignore_calibration: 0 };

        xhptdc8_get_default_init_parameters(&mut params);
        print!("Paramters: version: {} & dma_read_delay: {}", params.version, params.dma_read_delay ) ;
    }
}
