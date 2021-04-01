// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the UTILMSVSCPP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// UTILMSVSCPP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef UTILMSVSCPP_EXPORTS
#define UTILMSVSCPP_API __declspec(dllexport)
#else
#define UTILMSVSCPP_API __declspec(dllimport)
#endif

// This class is exported from the dll
class UTILMSVSCPP_API Cutilmsvscpp {
public:
	Cutilmsvscpp(void);
	// TODO: add your methods here.
};

extern UTILMSVSCPP_API int nutilmsvscpp;

UTILMSVSCPP_API int fnutilmsvscpp(void);
