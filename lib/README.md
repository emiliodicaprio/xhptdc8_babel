# xHPTDC driver libraries

This directory contains the windows C libraries that the projects in the other directories link to.
These files are provided here for more convenient development and might be out of date. For production use please use the files provided with the latest driver download provided on the [xHPTDC8 product page](https://www.cronologic.de/products/tdcs/xhptdc8-pcie.)

## Files

<dl>
    <dt>include/xhptdc8_interface.h</dt>
        <dd> This header file must be included when linking to any of the libraries.<dd>
    <dt>include/crono_interface.h</dt>
        <dd> This header is included by xhptdc8_interface.h.<dd>
    <dt>x*/.dll</dt>
        <dd>Dynamic Link Libraries with C linkage that can be bound to at run time are compile time.</dd>
    <dt>x*/.lib</dt>
        <dd>Information for a compiler compiling a project that is using the corresponding DLL. This is not a static library.</dd>
    <dt>x64*/xhptdc8_driver_64.*</dt>
        <dd>Libraries for 64 bit windows</dd>
    <dt>x86*/xhptdc8_driver.*</dt>
        <dd>Libraries for 32 bit windows</dd>
    <dt>x*dummy/*</dt>
        <dd>Dummy driver to be used for development whithout access to the actual hardware. The sources for this are in this repository in the /dummy/ directory. The binaries are provided here to allows developing in one of the other supported languages without installing a C compiler.</dd>
</dl>