# xhptdc8_babel
Wrappers, Utilities and Examples for using the xHPTDC8 with various programming languages.

The windows driver for the  [xHPTDC8](https://www.cronologic.de/products/tdcs/xhptdc8-pcie)  time-to-digital converter (TDC) is a DLL with C linkage. Not because C would be a particularily good choice to write your TDC application in, but because it ensures the best compatibility with different programming languages and compilers.

This repository is intended to host wrappers to make the driver avilable in various programming languages. 

Eventually you will also find utility functions such as default configurations for different use cases in this repository as well as example code.

## Directory Structure

    .
    ├── lib/      # real and dummy driver libraries and header files
    ├── dummy/    # dummy library to enable development in this repository without access to the hardware
    ├── util/     # utility functions common to all wrappers
    └── python/   # python wrapper around driver and utilities
(created by [tree.nathanfriend.io](https://tree.nathanfriend.io/?s=(%27options!(%27fancy!true~fullPath!false~trailingSlash!true)~8(%278%27lib09*real-62drivBlibraries-headBfiles56y0*62library.enable%20development%20inDhiCrepositor2without4ccess.the%20hardware570%20*7it2functionCcommon.all3s5python%2F*python34rouAdriver-7ities%27)~version!%271%27)*9%20%23%20-4A.Do%200%2F%202y%203%20wrapper4%20a5%5Cn6dumm7util8source!9%20%20And%20Ber%20Cs%20D%20t%01DCBA987654320.-*)

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available ot others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.
