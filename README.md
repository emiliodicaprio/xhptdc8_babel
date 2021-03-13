# xhptdc8_babel
Wrappers, Utilities and Examples for using the xHPTDC8 with various programming languages.

The windows driver for the  [xHPTDC8](https://www.cronologic.de/products/tdcs/xhptdc8-pcie)  time-to-digital converter (TDC) is a DLL with C linkage. Not because C would be a particularily good choice to write your TDC application in, but because it ensures the best compatibility with different programming languages and compilers.

This repository is intended to host wrappers to make the driver avilable in various programming languages. 

Eventually you will also find utility functions such as default configurations for different use cases in this repository as well as example code.

## Directory Structure

    .
    ├── lib/      # real and dummy driver libraries and header files
    ├── util/     # utility functions common to all wrappers
    └── python/   # python wrapper around driver and utilities
(created by [tree.nathanfriend.io](https://tree.nathanfriend.io/?s=(%27options!(%27fancy!true~fullPath!false~trailingSlash!true)~6(%276%27lib%2F4*real-dummy2%20libraries-header%20files%5Cn5%2F.*5ity%20functions%20common%20to3ll0s%5Cnpython%2F*python03round2-5ities%27)~version!%271%27)*4%23%20-3nd%204%200%20wrapper2%20driver3%20a4.%205util6source!%01654320.-*)

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available ot others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.
