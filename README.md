# xhptdc8_babel
Wrappers, Utilities and Examples for using the xHPTDC8 with various programming languages.

The windows driver for the  [xHPTDC8](https://www.cronologic.de/products/tdcs/xhptdc8-pcie)  time-to-digital converter (TDC) is a DLL with C linkage. Not because C would be a particularily good choice to write your TDC application in, but because it ensures the best compatibility with different programming languages and compilers.

This repository is intended to host wrappers to make the driver avilable in various programming languages. 

Eventually you will also find utility functions such as default configurations for different use cases in this repository as well as example code.

## Directory Structure

    .
    ├── dummy/      # source of dummy library to enable development in this repository without access to the hardware
    ├── go/         # utility to list information about installed devices, writtin in golang
    ├── include/    # the header files for the C driver API
    ├── lib/        # real and dummy driver libraries and header files
    ├── bin/        # driver runtime files
    ├── rust/       # utility to capture data into a file, written in Rust
    ├── ug_example/ # c++ example of how to use the driver
    └── util/       # utility functions common to all wrappers

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available ot others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.

## Notes
- The provided `/bin/xhptdc8_update_firmware` file is used only for Linux. To update firmware under Windows, please use `FirmwareGUI` supplied with the driver.