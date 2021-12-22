// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#include "windows.h"
#include <stdlib.h>
#include "xhptdc8_util.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#pragma warning(disable: 4047)
HINSTANCE hInstance = (HINSTANCE)&__ImageBase;
#pragma warning(default: 4047)
#define ERR_MSG_SRC_SIZE    256
static char err_msg_rc[ERR_MSG_SRC_SIZE];

const char* xhptdc8_get_err_message(int err_code)
{
    WCHAR err_msg_rcw[ERR_MSG_SRC_SIZE];
    if (LoadString(hInstance, err_code, err_msg_rcw, ERR_MSG_SRC_SIZE)) {
        // Code is found 
        size_t i;
        wcstombs_s(&i, err_msg_rc, ERR_MSG_SRC_SIZE, err_msg_rcw, ERR_MSG_SRC_SIZE -1);
    }
    else
    {
        // Code is not found 
        strcpy_s(err_msg_rc, ERR_MSG_SRC_SIZE, "Error Code Not Found!");
    }
    return err_msg_rc;
}
