//
// Header file containing main definitions of the DLL needed by Dummy APIs
//

#ifndef XHPTDC8_DUMMY_H
#define XHPTDC8_DUMMY_H

#define VER_FILE_VERSION_STR	"0.0.18"
#define VER_FILE_VERSION		0x000012
#define VERSION_BUILD			1

#define XHPTDC8_VETO_OFF		0
#define XHPTDC8_VETO_INSIDE		1
#define XHPTDC8_VETO_OUTSIDE	2

#ifdef __cplusplus
extern "C" {
#endif

const char* InvalidDevMgr = "Invalid device manager!";
const char MSG_OK[3] = { "OK" };
const char lastErrorMessageDummy[20] = "Last Error Message!";

#ifdef __cplusplus
}
#endif

#endif

