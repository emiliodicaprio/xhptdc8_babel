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
    ├── ug_example/ # c++ example of how to use the driver
    └── python/     # python wrapper around driver and utilities
(created by [tree.nathanfriend.io](https://tree.nathanfriend.io/?s=(%27options!(%27fancy!true~fullPa9!false~trailingSlash!true)~C(%27C%27lib23*real.708ies.headF%20files472*78y-enabl5development%20in%209iGrepositorEwi9outAccess-95hardware4B2%20*BitEfunctionGcommon-all6s4ug_example2Dc%2B%2B%20exampl5of%20how-us59e04py9on%2F*py9on6Around0.Bities%27)~vFsion!%271%27)*33%20D-%20to%20.And%200%20drivF2%2F%203%20%204%5Cn5e%206%20wrappF7dummy8%20librar9thA%20aButilCsource!D%23%20Ey%20FerGs%20%01GFEDCBA987654320.-*)

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available ot others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.
