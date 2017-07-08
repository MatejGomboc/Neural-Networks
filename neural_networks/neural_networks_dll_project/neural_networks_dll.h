// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the NEURAL_NETWORKS_DLL_PROJECT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NEURAL_NETWORKS_DLL_PROJECT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef NEURAL_NETWORKS_DLL_PROJECT_EXPORTS
#define NEURAL_NETWORKS_DLL_PROJECT_API __declspec(dllexport)
#else
#define NEURAL_NETWORKS_DLL_PROJECT_API __declspec(dllimport)
#endif

extern "C" NEURAL_NETWORKS_DLL_PROJECT_API int fnneural_networks_dll_project(void);
