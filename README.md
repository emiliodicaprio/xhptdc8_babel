# xhptdc8_babel
Wrappers, Utilities and Examples for using the xHPTDC8 with various programming languages.

The windows driver for the  [xHPTDC8](https://www.cronologic.de/products/tdcs/xhptdc8-pcie)  time-to-digital converter (TDC) is a DLL with C linkage. Not because C would be a particularily good choice to write your TDC application in, but because it ensures the best compatibility with different programming languages and compilers.

This repository is intended to host wrappers to make the driver avilable in various programming languages. 

Eventually you will also find utility functions such as default configurations for different use cases in this repository as well as example code.

## Directory Structure

    .
    ├── lib/        # real and dummy driver libraries and header files
    ├── dummy/      # dummy library to enable development in this repository without access to the hardware
    ├── util/       # utility functions common to all wrappers
    └── ug_example/ # c++ example of how to use the driver
(created by [tree.nathanfriend.io](https://tree.nathanfriend.io/?s=(%27options!(%27fancy!true~fullPath!false~trailingSlash!true)~6(%276%27lib%2F.*real352driver%20libraries3header%20files45y%2F*52library-enabl0development%20inBhiArepositor2without9ccess-th0hardware4util7*utilit2functionAcommon-all%20wrappers4ug_example78c%2B%2B%20exampl0of%20how-us0th0driver%27)~version!%271%27)*...8-Bo%20.%20%200e%202y%2039nd%204%5Cn5dumm6source!7%2F%208%23%209%20aAs%20B%20t%01BA987654320.-*)

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available ot others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.
