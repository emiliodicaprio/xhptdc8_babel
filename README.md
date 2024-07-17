# xhptdc8_babel
Wrappers, Utilities and Examples for using the xHPTDC8 with various programming languages.

The Windows driver for the [xHPTDC8](https://www.cronologic.de/products/tdcs/xhptdc8-pcie) time-to-digital converter (TDC) is a DLL with C linkage.  C offers particularly good compatibility with different programming languages and compilers.

This repository is intended to host wrappers to make the driver available in various programming languages. 

Eventually you will also find utility functions such as default configurations for different use cases in this repository as well as example code.

## Directory Structure

    .
    ├── dummy/      # source of dummy library to enable development in this repository without access to the hardware
    ├── go/         # utility to list information about installed devices, writtin in golang
    ├── include/    # the header files for the C driver API/sub-projects
    ├── lib/        # real and dummy driver/sub-projects libraries.
    ├── bin/        # driver/sub-project runtime files
    ├── rust/       # utility to capture data into a file, written in Rust
    ├── ug_example/ # c++ example of how to use the driver
    └── util/       # utility functions common to all wrappers

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available to others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the before-mentioned license.

## User Guide Example

A User Guide Example is provided in [./ug_example/](./ug_example/).

Follow the instructions within the directory on how to compile and run the example on Windows or Linux.


## Notes
The provided `/bin/xhptdc8_update_firmware` file is used only for Linux. To update firmware under Windows, please use `FirmwareGUI` supplied with the driver.