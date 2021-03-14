// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MSVSCPP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MSVSCPP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MSVSCPP_EXPORTS
#define MSVSCPP_API __declspec(dllexport)
#else
#define MSVSCPP_API __declspec(dllimport)
#endif

// This class is exported from the dll
class MSVSCPP_API Cmsvscpp {
public:
	Cmsvscpp(void);
	// TODO: add your methods here.
};

extern MSVSCPP_API int nmsvscpp;

MSVSCPP_API int fnmsvscpp(void);
