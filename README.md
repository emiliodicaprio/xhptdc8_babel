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
    ├── rust/       # utility to capture data into a file, written in Rust
    ├── ug_example/ # c++ example of how to use the driver
    └── util/       # utility functions common to all wrappers
(created by [tree.nathanfriend.io](https://tree.nathanfriend.io/?s=(%27optJs!(%27fancy!true~fullPaF!false~traiNngSlash!true)~Ee!(%27Ee!%27dL%2F*E0of6L%20Nbrary-enabl0developmentDFiQrepositoryGiFout7ccess-Thardware4goK3-Nst2formatJ7bout2stalOd6evices9inDgolang4includeK.8T5HoBTC6MBAPI4NbK*real7nd6L6MBNbraries7nd%2054rustU-captur0data2to7HiO9enDRust4ug_exampO%2F%208c%2B%2B%20exampl0of%20how-us0TdMr4utilUHunctJQcommon-allGrappers4%27)~versJ!%271%27)*...8-%20to%20.%20%200e%20Din3%20*utiNty4%5Cn5headeBfiOs6%20d7%20a8%23%209%2CGrittBr%20D2%20EsourcFthG%20wH%20fJionK%2F.LummyMriveNliOleQs%20TF0U%2F3%01UTQONMLKJHGFEDB987654320.-*)

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available ot others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.
