// msvscpp.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "msvscpp.h"


// This is an example of an exported variable
MSVSCPP_API int nmsvscpp=0;

// This is an example of an exported function.
MSVSCPP_API int fnmsvscpp(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Cmsvscpp::Cmsvscpp()
{
    return;
}
